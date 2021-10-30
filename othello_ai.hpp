#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <time.h>

class othello_ai
{
    public:
        othello_ai(std::vector<std::vector<int>> parameter_, int mode_, int depth_min_, double time_max_); //othello_aiセット
        std::pair<int, int> get_place_ai(std::vector<std::vector<int>> board_, int disk_); //ai設置場所取得

    private:
        std::vector<std::vector<int>> parameter; //盤面評価パラメータ
        int mode; //aiモード 1:最強 -1:最弱
        int depth_min; //探索最低深度
        double time_max; //探索最大時間[ms]
        const double inf = std::numeric_limits<double>::infinity();

        std::vector<std::pair<int, int>> get_place_able(std::vector<std::vector<int>> board_, int disk_); //設置可能場所取得
        std::vector<std::vector<int>> get_board_placed(std::vector<std::vector<int>> board_, std::pair<int, int> place_, int disk_); //設置後盤面取得
        double alphabeta(std::vector<std::vector<int>> board_, int disk_, int depth_, clock_t time_start_, double alpha_, double beta_);
        double evaluation(std::vector<std::vector<int>> board_, int disk_);


};

othello_ai::othello_ai(std::vector<std::vector<int>> parameter_, int mode_, int depth_min_, double time_max_)
{
    parameter = parameter_;
    mode = mode_;
    depth_min = depth_min_;
    time_max = time_max_;
}

std::pair<int, int> othello_ai::get_place_ai(std::vector<std::vector<int>> board_, int disk_)
{
    std::vector<std::pair<int, int>> r = get_place_able(board_, disk_);
    std::vector<double> val(r.size());
    for (int i = 0; i < r.size(); i++)
    {
        val[i] = alphabeta(get_board_placed(board_, r[i], disk_), disk_ * -1, depth_min, std::clock(), -inf, inf);
    }
    double val_max = -inf;
    int j;
    for (int i = 0; i < r.size(); i++)
    {
        if (val_max < val[i])
        {
            val_max = val[i];
            j = i;
        }
    }
    return r[j];
}

std::vector<std::pair<int, int>> othello_ai::get_place_able(std::vector<std::vector<int>> board_, int disk_)
{
    std::vector<std::pair<int, int>> r;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            bool can_place = false;
            //右
            if (i < 6 && board_[i + 1][j] == -disk_)
            {
                for (int k = 2; i + k < 8; k++)
                {
                    if (board_[i + k][j] == disk_)
                    {
                        can_place = true;
                        break;
                    }
                    else if(board_[i + k][j] == 0)
                    {
                        break;
                    }
                }
                if (can_place == true)
                {
                    r.push_back(std::make_pair(i, j));
                    continue;
                }
            }
            //左
            if (i > 1 && board_[i - 1][j] == -disk_)
            {
                for (int k = 2; i - k > 0; k++)
                {
                    if (board_[i - k][j] == disk_)
                    {
                        can_place = true;
                        break;
                    }
                    else if(board_[i - k][j] == 0)
                    {
                        break;
                    }
                }
                if (can_place == true)
                {
                    r.push_back(std::make_pair(i, j));
                    continue;
                }
            }
            //下
            if (j < 6 && board_[i][j + 1] == -disk_)
            {
                for (int k = 2; j + k < 8; k++)
                {
                    if (board_[i][j + k] == disk_)
                    {
                        can_place = true;
                        break;
                    }
                    else if(board_[i][j + k] == 0)
                    {
                        break;
                    }
                }
                if (can_place == true)
                {
                    r.push_back(std::make_pair(i, j));
                    continue;
                }
            }
            //上
            if (j > 1 && board_[i][j - 1] == -disk_)
            {
                for (int k = 2; j - k > 0; k++)
                {
                    if (board_[i][j - k] == disk_)
                    {
                        can_place = true;
                        break;
                    }
                    else if(board_[i][j - k] == 0)
                    {
                        break;
                    }
                }
                if (can_place == true)
                {
                    r.push_back(std::make_pair(i, j));
                    continue;
                }
            }
            //右下
            if (i < 6 && j < 6 && board_[i + 1][j + 1] == -disk_)
            {
                for (int k = 2; i + k < 8 || j + k < 8; k++)
                {
                    if (board_[i + k][j + k] == disk_)
                    {
                        can_place = true;
                        break;
                    }
                    else if(board_[i + k][j + k] == 0)
                    {
                        break;
                    }
                }
                if (can_place == true)
                {
                    r.push_back(std::make_pair(i, j));
                    continue;
                }
            }
            //左上
            if (i > 1 && j > 1 && board_[i - 1][j - 1] == -disk_)
            {
                for (int k = 2; i - k > 0 || j - k > 0; k++)
                {
                    if (board_[i - k][j - k] == disk_)
                    {
                        can_place = true;
                        break;
                    }
                    else if(board_[i - k][i - k] == 0)
                    {
                        break;
                    }
                }
                if (can_place == true)
                {
                    r.push_back(std::make_pair(i, j));
                    continue;
                }
            }
            //左下
            if (i > 0 && j < 6 && board_[i - 1][j + 1] == -disk_)
            {
                for (int k = 2; i - k > 0 || j + k < 8; k++)
                {
                    if (board_[i - k][j + k] == disk_)
                    {
                        can_place = true;
                        break;
                    }
                    else if(board_[i - k][j + k] == 0)
                    {
                        break;
                    }
                }
                if (can_place == true)
                {
                    r.push_back(std::make_pair(i, j));
                    continue;
                }
            }
            //右上
            if (i < 6 && j > 0 && board_[i + 1][j - 1] == -disk_)
            {
                for (int k = 2; i + k < 8 || j - k > 0; k++)
                {
                    if (board_[i + k][j - k] == disk_)
                    {
                        can_place = true;
                        break;
                    }
                    else if(board_[i + k][j - k] == 0)
                    {
                        break;
                    }
                }
                if (can_place == true)
                {
                    r.push_back(std::make_pair(i, j));
                    continue;
                }
            }
        }
    }
    return r;
}

std::vector<std::vector<int>> othello_ai::get_board_placed(std::vector<std::vector<int>> board_, std::pair<int, int> place_, int disk_)
{
    board_[place_.first][place_.second] = disk_;
    //右
    if (board_[place_.first + 1][place_.second] == -disk_)
    {
        for (int i = 2; place_.first + i < 8; i++)
        {
            if (board_[place_.first + i][place_.second] == disk_)
            {
                for (int j = 1; j < i; j++)
                {
                    board_[place_.first + j][place_.second] *= -1;
                }
                break;
            }
            else if(board_[place_.first + i][place_.second] == 0)
            {
                break;
            }
        }
    }
    //左
    if (board_[place_.first - 1][place_.second] == -disk_)
    {
        for (int i = 2; place_.first - i > 0; i++)
        {
            if (board_[place_.first - i][place_.second] == disk_)
            {
                for (int j = 1; j < i; j++)
                {
                    board_[place_.first - j][place_.second] *= -1;
                }
                break;
            }
            else if(board_[place_.first - i][place_.second] == 0)
            {
                break;
            }
        }
    }
    //下
    if (board_[place_.first][place_.second + 1] == -disk_)
    {
        for (int i = 2; place_.first + i < 8; i++)
        {
            if (board_[place_.first][place_.second + i] == disk_)
            {
                for (int j = 1; j < i; j++)
                {
                    board_[place_.first][place_.second + j] *= -1;
                }
                break;
            }
            else if(board_[place_.first][place_.second + i] == 0)
            {
                break;
            }
        }
    }
    //上
    if (board_[place_.first][place_.second - 1] == -disk_)
    {
        for (int i = 2; place_.first - i > 0; i++)
        {
            if (board_[place_.first][place_.second - i] == disk_)
            {
                for (int j = 1; j < i; j++)
                {
                    board_[place_.first][place_.second - j] *= -1;
                }
                break;
            }
            else if(board_[place_.first][place_.second - i] == 0)
            {
                break;
            }
        }
    }
    //右下
    if (board_[place_.first + 1][place_.second + 1] == -disk_)
    {
        for (int i = 2; place_.first + i < 8 || place_.second + i < 8; i++)
        {
            if (board_[place_.first + i][place_.second + i] == disk_)
            {
                for (int j = 1; j < i; j++)
                {
                    board_[place_.first + j][place_.second + j] *= -1;
                }
                break;
            }
            else if(board_[place_.first + i][place_.second + i] == 0)
            {
                break;
            }
        }
    }
    //左上
    if (board_[place_.first - 1][place_.second - 1] == -disk_)
    {
        for (int i = 2; place_.first - i > 0 || place_.second - i > 0; i++)
        {
            if (board_[place_.first - i][place_.second - i] == disk_)
            {
                for (int j = 1; j < i; j++)
                {
                    board_[place_.first - j][place_.second - j] *= -1;
                }
                break;
            }
            else if(board_[place_.first - i][place_.second - i] == 0)
            {
                break;
            }
        }
    }
    //左下
    if (board_[place_.first - 1][place_.second + 1] == -disk_)
    {
        for (int i = 2; place_.first - i > 0 || place_.second + i < 8; i++)
        {
            if (board_[place_.first - i][place_.second + i] == disk_)
            {
                for (int j = 1; j < i; j++)
                {
                    board_[place_.first - j][place_.second + j] *= -1;
                }
                break;
            }
            else if(board_[place_.first - i][place_.second + i] == 0)
            {
                break;
            }
        }
    }
    //左上
    if (board_[place_.first + 1][place_.second - 1] == -disk_)
    {
        for (int i = 2; place_.first + i < 8 || place_.second - i > 0; i++)
        {
            if (board_[place_.first + i][place_.second - i] == disk_)
            {
                for (int j = 1; j < i; j++)
                {
                    board_[place_.first + j][place_.second - j] *= -1;
                }
                break;
            }
            else if(board_[place_.first + i][place_.second - i] == 0)
            {
                break;
            }
        }
    }
    return board_;
}

double othello_ai::alphabeta(std::vector<std::vector<int>> board_, int disk_, int depth_, clock_t time_start_, double alpha_, double beta_)
{
    std::vector<std::pair<int, int>> r = get_place_able(board_, disk_);
    if (!r.empty() || (depth_ == 0 && std::clock() - time_start_ > time_max))
    {
        return evaluation(board_, disk_);
    }
    for (const auto& e : r)
    {
        alpha_ = std::max(alpha_, -alphabeta(get_board_placed(board_, e, disk_), disk_ * -1, depth_ - 1, time_start_,  -beta_, -alpha_));
        if(alpha_ >= beta_)
        {
            return alpha_;
        }
    }
    return alpha_;
}

double othello_ai::evaluation(std::vector<std::vector<int>> board_, int disk_)
{
    return 0.;
}
