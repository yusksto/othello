#include <iostream>
#include <vector>
#include <cmath>
#include <cstdint>
#include <algorithm>
#include <limits>
#include <time.h>
#include <omp.h>

class othello_ai
{
    public:
        othello_ai(std::vector<std::vector<double>> parameter_, int mode_, int depth_min_, int time_max_); //othello_aiセット
        std::pair<int, int> get_place_ai(std::vector<std::vector<int>> board_vector_, int disk_); //ai設置場所取得

    private:
        //変数
        std::vector<std::vector<double>> parameter; //盤面評価パラメータ [-1:1]
        int mode; //aiモード 1:最強 -1:最弱
        int depth_min; //探索最低深度 [0:)
        int time_max; //探索最大時間 [ms]

        //関数
        std::pair<int64_t, int64_t> convert_vector_to_bitboard(std::vector<std::vector<int>> board_vector_); //vectorからbitboardへ変換
        std::pair<int, int> convert_bitboard_to_pair(int64_t bitboard_); //bitboardからpairへ変換
        std::vector<int64_t> get_place_able(std::pair<int64_t, int64_t> bitboard_); //設置可能場所取得
        std::pair<int64_t, int64_t> get_board_placed(std::pair<int64_t, int64_t> bitboard_, int64_t place_); //設置後盤面取得
        double alphabeta(std::pair<int64_t, int64_t> bitboard_, int depth_, clock_t time_start_, double alpha_, double beta_); //αβ探索
        double evaluation(std::pair<int64_t, int64_t> bitboard_); //評価関数
        int get_disks_able(std::pair<int64_t, int64_t> bitboard_); //設置可能場所数取得
        int get_disks_all(std::pair<int64_t, int64_t> bitboard_); //石の数取得
        int get_disks(int64_t bitboard_); //石の数取得

        //その他定数、活性化関数
        const double inf = std::numeric_limits<double>::infinity();
        double f_1(double x); //f_1[0:1], x[0:1]
        double f_2(double x); //f_2[0:1], x[0:1]
        double f_3(double x); //f_3[0:1], x[0:1]
};

othello_ai::othello_ai(std::vector<std::vector<double>> parameter_, int mode_, int depth_min_, int time_max_)
{
    parameter = parameter_;
    mode = mode_;
    depth_min = depth_min_;
    time_max = time_max_;
}

std::pair<int64_t, int64_t> othello_ai::convert_vector_to_bitboard(std::vector<std::vector<int>> board_vector_)
{

}

std::pair<int, int> othello_ai::convert_bitboard_to_pair(int64_t bitboard_)
{

}

std::pair<int, int> othello_ai::get_place_ai(std::vector<std::vector<int>> board_vector_, int disk_)
{
    std::pair<int64_t, int64_t> bitboard = convert_vector_to_bitboard(board_vector_);
    std::vector<int64_t> r = get_place_able(bitboard);
    const int size = r.size();
    std::vector<double> val(size);
#pragma omp parallel for
    for (int i = 0; i < size; i++)
    {
        val[i] = mode * -alphabeta(get_board_placed(bitboard, r[i]), depth_min, std::clock(), -inf, inf);
    }
    std::vector<std::pair<double, int64_t>> s(size);
    for (int i = 0; i < size; i++)
    {
        s[i] = std::make_pair(val[i], r[i]);
    }
    sort(s.begin(), s.end(), std::greater<std::pair<double, std::pair<int, int>>>());
    return convert_bitboard_to_pair(s[0].second);
}

std::vector<int64_t> othello_ai::get_place_able(std::pair<int64_t, int64_t> bitboard_)
{
    
}

std::pair<int64_t, int64_t> othello_ai::get_board_placed(std::pair<int64_t, int64_t> bitboard_, int64_t place_)
{
    
}

double othello_ai::alphabeta(std::pair<int64_t, int64_t> bitboard_, int depth_, clock_t time_start_, double alpha_, double beta_)
{
    std::vector<int64_t> r = get_place_able(bitboard_);
    if (r.empty() || depth_ <= 0 || std::clock() - time_start_ > time_max)
    {
        return evaluation(bitboard_);
    }
    for (const auto& e : r)
    {
        alpha_ = std::max(alpha_, -alphabeta(get_board_placed(bitboard_, e), depth_ - 1, time_start_, -beta_, -alpha_));
        if (alpha_ >= beta_)
        {
            return alpha_;
        }
    }
    return alpha_;
}

double othello_ai::evaluation(std::pair<int64_t, int64_t> bitboard_)
{
    double n = double(get_disks_all(bitboard_)) / 64.; //盤面進行度 [0:1]

    //盤面配置良さ s_1[-1:1]
    double s_1 = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            //s_1 += double(disk) * double(board[i][j]) * parameter[i][j] / 64.;
        }
    }
    s_1 *= f_1(f_1(pow(f_1(n), 4)));

    //石の数 s_2[-1:1]
    int disks_0 = get_disks(bitboard_.first);
    int disks_1 = get_disks(bitboard_.second);
    double s_2 = 0;
    if (disks_0 != 0 || disks_1 != 0)
    {
        s_2 = double(disks_0 - disks_1) / double(disks_0 + disks_1) * (1 - f_1(f_1(pow(f_1(n), 4))));
    }

    //設置可能場所数 s_3[-1:1]
    int disks_able_0 = get_disks_able(bitboard_);
    int disks_able_1 = get_disks_able(bitboard_);
    double s_3 = 0;
    if (disks_able_0 != 0 || disks_able_1 != 0)
    {
        s_3 = double(disks_able_0 - disks_able_1) / double(disks_able_0 + disks_able_1) * f_3(n);
    }

    return s_1 + s_2 + s_3;
}

int othello_ai::get_disks_able(std::pair<int64_t, int64_t> bitboard_)
{
    
}

int othello_ai::get_disks_all(std::pair<int64_t, int64_t> bitboard_)
{
    
}

int othello_ai::get_disks(int64_t bitboard_)
{
    
}

double othello_ai::f_1(double x)
{
    return pow(x, 2) * (-2 * x + 3);
}

double othello_ai::f_2(double x)
{
    return pow(x, 2);
}

double othello_ai::f_3(double x)
{
    return 16 * pow(x, 4) - 32 * pow(x, 3) + 16 * pow(x, 2);
}
