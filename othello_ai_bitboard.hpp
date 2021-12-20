#include <iostream>
#include <vector>
#include <cmath>
#include <cstdint>
#include <algorithm>
#include <limits>
#include <time.h>
#include <omp.h>

class othello_ai_bitboard
{
public:
    othello_ai_bitboard(std::vector<std::vector<double>> parameter_, int mode_, int depth_min_, int time_max_); //othello_ai_bitboardセット
    std::pair<int, int> get_place_ai(std::vector<std::vector<int>> vectorboard_, int disk_); //ai設置場所取得

private:
    //変数
    std::vector<std::vector<double>> parameter; //盤面評価パラメータ [-1:1]
    int mode; //aiモード 1:最強 -1:最弱
    int depth_min; //探索最低深度 [0:)
    int time_max; //探索最大時間 [ms]

    clock_t t_start; // αβ探索時間計測用
    bool isTimeout; // αβ探索打ち切り用

    //関数
    std::pair<uint64_t, uint64_t> convert_vectorboard_to_bitboard(std::vector<std::vector<int>> vectorboard_, int disk_); //vector<vector>からbitboardへ変換
    uint64_t get_legalboard(std::pair<uint64_t, uint64_t> bitboard_); //合法手bitboard作成
    std::vector<uint64_t> convert_legalboard_to_putboard(uint64_t legalboard_); //合法手boardからvector<指手board>へ変換
    std::pair<int, int> convert_putboard_to_pair(uint64_t putboard_); //bitboardからpairへ変換
    std::pair<uint64_t, uint64_t> get_bitboard_placed(std::pair<uint64_t, uint64_t> bitboard_, uint64_t putboard_); //設置後盤面取得
    double alphabeta(std::pair<uint64_t, uint64_t> bitboard_, int depth_, double alpha_, double beta_); //αβ探索
    double evaluation(std::pair<uint64_t, uint64_t> bitboard_); //評価関数

    int get_disks(std::pair<uint64_t, uint64_t> bitboard_); //石の数取得
    int get_disks(uint64_t bitboard_); //石の数取得

    //その他定数、活性化関数
    const double inf = std::numeric_limits<double>::infinity();
    double f_1(double x); //f_1[0:1], x[0:1]
    double f_2(double x); //f_2[0:1], x[0:1]
    double f_3(double x); //f_3[0:1], x[0:1]
};

othello_ai_bitboard::othello_ai_bitboard(std::vector<std::vector<double>> parameter_, int mode_, int depth_min_, int time_max_)
{
    parameter = parameter_;
    mode = mode_;
    depth_min = depth_min_;
    time_max = time_max_;
}

std::pair<int, int> othello_ai_bitboard::get_place_ai(std::vector<std::vector<int>> vectorboard_, int disk_)
{
    std::pair<uint64_t, uint64_t> bitboard = convert_vectorboard_to_bitboard(vectorboard_, disk_);
    uint64_t legalboard = get_legalboard(bitboard);
    std::vector<uint64_t> putboard = convert_legalboard_to_putboard(legalboard);
    const int size = get_disks(legalboard);
    std::vector<double> val(size);
    std::vector<double> tmp(size);

    // 反復深化深さ優先探索
    t_start = clock();
    isTimeout = false;
    int depth = 0;
    while (!isTimeout)
    {
//#pragma omp parallel for
        for (int i = 0; i < size; i++)
        {
            tmp[i] = -alphabeta(get_bitboard_placed(bitboard, putboard[i]), depth, -inf, inf);
        }
        if (!isTimeout)
        {
            for (int i = 0; i < size; i++)
            {
                val[i] = tmp[i];
            }
        }
        depth++;
    }

    std::vector<std::pair<double, uint64_t>> s(size);
    for (int i = 0; i < size; i++)
    {
        s[i] = std::make_pair(val[i], putboard[i]);
    }
    sort(s.begin(), s.end(), std::greater<std::pair<double, uint64_t>>());
    return convert_putboard_to_pair(s[0].second);
}

inline std::pair<uint64_t, uint64_t> othello_ai_bitboard::convert_vectorboard_to_bitboard(std::vector<std::vector<int>> vectorboard_, int disk_)
{
    uint64_t bitboard_1 = 0x0000000000000000;
    uint64_t bitboard_2 = 0x0000000000000000;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            bitboard_1 <<= 1;
            bitboard_2 <<= 1;
            if (vectorboard_[i][j] == disk_)
            {
                bitboard_1 |= 0x0000000000000001;
            }
            else if (vectorboard_[i][j] == -disk_)
            {
                bitboard_2 |= 0x0000000000000001;
            }
        }
    }
    return { bitboard_1, bitboard_2 };
}

inline uint64_t othello_ai_bitboard::get_legalboard(std::pair<uint64_t, uint64_t> bitboard_)
{
    const uint64_t horizon  = bitboard_.second & 0x7e7e7e7e7e7e7e7e;
    const uint64_t vertical = bitboard_.second & 0x00FFFFFFFFFFFF00;
    const uint64_t allside  = bitboard_.second & 0x007e7e7e7e7e7e00;
    const uint64_t blankboard = ~(bitboard_.first | bitboard_.second);
    uint64_t tmp = 0x0000000000000000;
    uint64_t legalboard = 0x0000000000000000;

    //左
    tmp = horizon & (bitboard_.first << 1);
    tmp |= horizon & (tmp << 1);
    tmp |= horizon & (tmp << 1);
    tmp |= horizon & (tmp << 1);
    tmp |= horizon & (tmp << 1);
    tmp |= horizon & (tmp << 1);
    legalboard = blankboard & (tmp << 1);

    //右
    tmp = horizon & (bitboard_.first >> 1);
    tmp |= horizon & (tmp >> 1);
    tmp |= horizon & (tmp >> 1);
    tmp |= horizon & (tmp >> 1);
    tmp |= horizon & (tmp >> 1);
    tmp |= horizon & (tmp >> 1);
    legalboard |= blankboard & (tmp >> 1);

    //上
    tmp = vertical & (bitboard_.first << 8);
    tmp |= vertical & (tmp << 8);
    tmp |= vertical & (tmp << 8);
    tmp |= vertical & (tmp << 8);
    tmp |= vertical & (tmp << 8);
    tmp |= vertical & (tmp << 8);
    legalboard |= blankboard & (tmp << 8);

    //下
    tmp = vertical & (bitboard_.first >> 8);
    tmp |= vertical & (tmp >> 8);
    tmp |= vertical & (tmp >> 8);
    tmp |= vertical & (tmp >> 8);
    tmp |= vertical & (tmp >> 8);
    tmp |= vertical & (tmp >> 8);
    legalboard |= blankboard & (tmp >> 8);

    //右斜め上
    tmp = allside & (bitboard_.first << 7);
    tmp |= allside & (tmp << 7);
    tmp |= allside & (tmp << 7);
    tmp |= allside & (tmp << 7);
    tmp |= allside & (tmp << 7);
    tmp |= allside & (tmp << 7);
    legalboard |= blankboard & (tmp << 7);

    //左斜め上
    tmp = allside & (bitboard_.first << 9);
    tmp |= allside & (tmp << 9);
    tmp |= allside & (tmp << 9);
    tmp |= allside & (tmp << 9);
    tmp |= allside & (tmp << 9);
    tmp |= allside & (tmp << 9);
    legalboard |= blankboard & (tmp << 9);

    //右斜め下
    tmp = allside & (bitboard_.first >> 9);
    tmp |= allside & (tmp >> 9);
    tmp |= allside & (tmp >> 9);
    tmp |= allside & (tmp >> 9);
    tmp |= allside & (tmp >> 9);
    tmp |= allside & (tmp >> 9);
    legalboard |= blankboard & (tmp >> 9);

    //左斜め下
    tmp = allside & (bitboard_.first >> 7);
    tmp |= allside & (tmp >> 7);
    tmp |= allside & (tmp >> 7);
    tmp |= allside & (tmp >> 7);
    tmp |= allside & (tmp >> 7);
    tmp |= allside & (tmp >> 7);
    legalboard |= blankboard & (tmp >> 7);
    return legalboard;
}

inline std::pair<int, int> othello_ai_bitboard::convert_putboard_to_pair(uint64_t putboard_)
{
    uint64_t tmp = 0x8000000000000000;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (putboard_ & tmp)
            {
                return std::make_pair(i, j);
            }
            tmp >>= 1;
        }
    }
}

inline std::vector<uint64_t> othello_ai_bitboard::convert_legalboard_to_putboard(uint64_t legalboard_)
{
    std::vector<uint64_t> putboard(get_disks(legalboard_));
    uint64_t tmp = 0x0000000000000000;
    int i = 0;
    while (legalboard_)
    {
        tmp = -int64_t(legalboard_) & legalboard_;
        putboard[i] = tmp;
        legalboard_ ^= tmp;
        i++;
    }
    return putboard;
}

inline std::pair<uint64_t, uint64_t> othello_ai_bitboard::get_bitboard_placed(std::pair<uint64_t, uint64_t> bitboard_, uint64_t putboard_)
{
    uint64_t horizon  = bitboard_.second & 0x7e7e7e7e7e7e7e7e;
    uint64_t vertical = bitboard_.second & 0x00FFFFFFFFFFFF00;
    uint64_t allside  = bitboard_.second & 0x007e7e7e7e7e7e00;
    uint64_t rev  = 0x0000000000000000;
    uint64_t rev_ = 0x0000000000000000;
    uint64_t tmp  = 0x0000000000000000;

    //反転石rev
    //左
    tmp = horizon & (putboard_ << 1);
    while (tmp)
    {
        rev_ |= tmp;
        tmp = horizon & (tmp << 1);
    }
    if (bitboard_.first & (rev_ << 1))
    {
        rev |= rev_;
    }

    //右
    rev_ = 0x0000000000000000;
    tmp = horizon & (putboard_ >> 1);
    while (tmp)
    {
        rev_ |= tmp;
        tmp = horizon & (tmp >> 1);
    }
    if (bitboard_.first & (rev_ >> 1))
    {
        rev |= rev_;
    }

    //上
    rev_ = 0x0000000000000000;
    tmp = vertical & (putboard_ << 8);
    while (tmp)
    {
        rev_ |= tmp;
        tmp = vertical & (tmp << 8);
    }
    if (bitboard_.first & (rev_ << 8))
    {
        rev |= rev_;
    }

    //下
    rev_ = 0x0000000000000000;
    tmp = vertical & (putboard_ >> 8);
    while (tmp)
    {
        rev_ |= tmp;
        tmp = vertical & (tmp >> 8);
    }
    if (bitboard_.first & (rev_ >> 8))
    {
        rev |= rev_;
    }

    //右斜め上
    rev_ = 0x0000000000000000;
    tmp = allside & (putboard_ << 7);
    while (tmp)
    {
        rev_ |= tmp;
        tmp = allside & (tmp << 7);
    }
    if (bitboard_.first & (rev_ << 7))
    {
        rev |= rev_;
    }

    //左斜め上
    rev_ = 0x0000000000000000;
    tmp = allside & (putboard_ << 9);
    while (tmp)
    {
        rev_ |= tmp;
        tmp = allside & (tmp << 9);
    }
    if (bitboard_.first & (rev_ << 9))
    {
        rev |= rev_;
    }

    //右斜め下
    rev_ = 0x0000000000000000;
    tmp = allside & (putboard_ >> 9);
    while (tmp)
    {
        rev_ |= tmp;
        tmp = allside & (tmp >> 9);
    }
    if (bitboard_.first & (rev_ >> 9))
    {
        rev |= rev_;
    }

    //左斜め下
    rev_ = 0x0000000000000000;
    tmp = allside & (putboard_ >> 7);
    while (tmp)
    {
        rev_ |= tmp;
        tmp = allside & (tmp >> 7);
    }
    if (bitboard_.first & (rev_ >> 7))
    {
        rev |= rev_;
    }

    //反転
    bitboard_.first ^= putboard_ | rev;
    bitboard_.second ^= rev;
    return std::make_pair(bitboard_.second, bitboard_.first);
}

inline double othello_ai_bitboard::alphabeta(std::pair<uint64_t, uint64_t> bitboard_, int depth_, double alpha_, double beta_)
{
    uint64_t legalboard = get_legalboard(bitboard_);
    
    if (depth_ <= 0)
    {
        return evaluation(bitboard_);
    }
    else if (std::clock() - t_start > time_max)
    {
        isTimeout = true;
        return evaluation(bitboard_);
    }
    else if (!legalboard)
    {
        std::pair<uint64_t, uint64_t> bitboard = std::make_pair(bitboard_.second, bitboard_.first);
        legalboard = get_legalboard(bitboard);
        if (!legalboard)
        {
            return evaluation(bitboard_);
        }
        else
        {
            return std::max(alpha_, -alphabeta(bitboard, depth_ - 1, -beta_, -alpha_));
        }
    }
    else
    {
        uint64_t putboard = 0x0000000000000000;
        while (legalboard)
        {
            putboard = -int64_t(legalboard) & legalboard;
            alpha_ = std::max(alpha_, -alphabeta(get_bitboard_placed(bitboard_, putboard), depth_ - 1, -beta_, -alpha_));
            if (alpha_ >= beta_)
            {
                return alpha_;
            }
            legalboard ^= putboard;
        }
        return alpha_;
    }
}

inline double othello_ai_bitboard::evaluation(std::pair<uint64_t, uint64_t> bitboard_)
{
    double n = double(get_disks(bitboard_)) / 64.; //盤面進行度 [0:1]

    //盤面配置良さ s_1[-1:1]
    double s_1 = 0;
    uint64_t tmp = 0x8000000000000000;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (bitboard_.first & tmp)
            {
                s_1 += parameter[i][j] / 64.;
            }
            else if (bitboard_.second & tmp)
            {
                s_1 -= parameter[i][j] / 64.;
            }
            tmp >>= 1;
        }
    }
    s_1 *= (1 - f_1(f_1(pow(f_1(n), 4))));
    
    //石の数 s_2[-1:1]
    int disks_0 = get_disks(bitboard_.first);
    int disks_1 = get_disks(bitboard_.second);
    double s_2 = 0;
    if (!disks_0)
    {
        s_2 = -inf;
    }
    else if(!disks_1)
    {
        s_2 = inf;
    }
    else
    {
        s_2 = double(disks_0 - disks_1) / double(disks_0 + disks_1) * f_1(f_1(pow(f_1(n), 4)));
    }

    //設置可能場所数 s_3[-1:1]
    int disks_able_0 = get_disks(get_legalboard(bitboard_));
    int disks_able_1 = get_disks(get_legalboard(std::make_pair(bitboard_.second, bitboard_.first)));
    double s_3 = 0;
    if (disks_able_0 || disks_able_1)
    {
        s_3 = double(disks_able_0 - disks_able_1) / double(disks_able_0 + disks_able_1) * f_3(n);
    }
    
    return mode * (s_1 + s_2 + s_3);
}

inline int othello_ai_bitboard::get_disks(std::pair<uint64_t, uint64_t> bitboard_)
{
    uint64_t bitboard = bitboard_.first | bitboard_.second;
    bitboard = (bitboard & 0x5555555555555555) + ((bitboard & 0xAAAAAAAAAAAAAAAA) >> 1);
    bitboard = (bitboard & 0x3333333333333333) + ((bitboard & 0xCCCCCCCCCCCCCCCC) >> 2);
    bitboard = (bitboard & 0x0F0F0F0F0F0F0F0F) + ((bitboard & 0xF0F0F0F0F0F0F0F0) >> 4);
    bitboard = (bitboard & 0x00FF00FF00FF00FF) + ((bitboard & 0xFF00FF00FF00FF00) >> 8);
    bitboard = (bitboard & 0x0000FFFF0000FFFF) + ((bitboard & 0xFFFF0000FFFF0000) >> 16);
    bitboard = (bitboard & 0x00000000FFFFFFFF) + ((bitboard & 0xFFFFFFFF00000000) >> 32);
    return int(bitboard);
}

inline int othello_ai_bitboard::get_disks(uint64_t bitboard_)
{
    bitboard_ = (bitboard_ & 0x5555555555555555) + ((bitboard_ & 0xAAAAAAAAAAAAAAAA) >> 1);
    bitboard_ = (bitboard_ & 0x3333333333333333) + ((bitboard_ & 0xCCCCCCCCCCCCCCCC) >> 2);
    bitboard_ = (bitboard_ & 0x0F0F0F0F0F0F0F0F) + ((bitboard_ & 0xF0F0F0F0F0F0F0F0) >> 4);
    bitboard_ = (bitboard_ & 0x00FF00FF00FF00FF) + ((bitboard_ & 0xFF00FF00FF00FF00) >> 8);
    bitboard_ = (bitboard_ & 0x0000FFFF0000FFFF) + ((bitboard_ & 0xFFFF0000FFFF0000) >> 16);
    bitboard_ = (bitboard_ & 0x00000000FFFFFFFF) + ((bitboard_ & 0xFFFFFFFF00000000) >> 32);
    return int(bitboard_);
}

inline double othello_ai_bitboard::f_1(double x)
{
    return pow(x, 2) * (-2 * x + 3);
}

inline double othello_ai_bitboard::f_2(double x)
{
    return pow(x, 2);
}

inline double othello_ai_bitboard::f_3(double x)
{
    return 16 * pow(x, 4) - 32 * pow(x, 3) + 16 * pow(x, 2);
}
