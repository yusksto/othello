#include <iostream>
#include <vector>
#include "Eigen/Eigen"

class othello_ai
{
    public:
        othello_ai(std::vector<std::vector<int>> parameter_, int mode_); //othello_aiセット
        std::pair<int, int> get_place_ai(std::vector<std::vector<int>> board_, int disk_); //ai設置場所取得

    private:
        std::vector<std::vector<int>> parameter; //盤面評価パラメータ
        int mode; //aiモード

        std::vector<std::pair<int, int>> get_place_able(std::vector<std::vector<int>> board_, int disk_); //設置可能場所取得
        std::vector<std::vector<int>> get_board_placed(std::vector<std::vector<int>> board_, std::pair<int, int> place_, int disk_); //設置後盤面取得



    
};

othello_ai::othello_ai(std::vector<std::vector<int>> parameter_, int mode_)
{
    parameter = parameter_;
    mode = mode_;
}

std::pair<int, int> othello_ai::get_place_ai(std::vector<std::vector<int>> board_, int disk_)
{











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
                for (int k = 1; i + k < 8; k++)
                {
                    if (board_[i + k + 1][j] == disk_)
                    {
                        can_place = true;
                        break;
                    }
                    else if(board_[i + k + 1][j] == 0)
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
                for (int k = 1; i - k > 0; k++)
                {
                    if (board_[i - k - 1][j] == disk_)
                    {
                        can_place = true;
                        break;
                    }
                    else if(board_[i - k - 1][j] == 0)
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
                for (int k = 1; j + k < 8; k++)
                {
                    if (board_[i][j + k + 1] == disk_)
                    {
                        can_place = true;
                        break;
                    }
                    else if(board_[i][j + k + 1] == 0)
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
                for (int k = 1; j - k > 0; k++)
                {
                    if (board_[i][j - k - 1] == disk_)
                    {
                        can_place = true;
                        break;
                    }
                    else if(board_[i][j - k - 1] == 0)
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
                for (int k = 1; i + k < 8 || j + k < 8; k++)
                {
                    if (board_[i + k + 1][j + k + 1] == disk_)
                    {
                        can_place = true;
                        break;
                    }
                    else if(board_[i + k + 1][j + k + 1] == 0)
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
                for (int k = 1; i - k > 0 || j - k > 0; k++)
                {
                    if (board_[i - k - 1][j - k - 1] == disk_)
                    {
                        can_place = true;
                        break;
                    }
                    else if(board_[i - k - 1][i - k - 1] == 0)
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
                for (int k = 1; i - k > 0 || j + k < 8; k++)
                {
                    if (board_[i - k - 1][j + k + 1] == disk_)
                    {
                        can_place = true;
                        break;
                    }
                    else if(board_[i - k - 1][j + k + 1] == 0)
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
                for (int k = 1; i + k < 8 || j - k > 0; k++)
                {
                    if (board_[i + k + 1][j - k - 1] == disk_)
                    {
                        can_place = true;
                        break;
                    }
                    else if(board_[i + k + 1][j - k - 1] == 0)
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
    //右
    if (board_[place_.first + 1][place_.second] == -disk_)
    {
        for (int i = 1; place_.first + i < 8; i++)
        {
            if (board_[place_.first + i + 1][place_.second] == disk_)
            {
                for (int j = 1; j < i; j++)
                {
                    board_[place_.first + j + 1][place_.second] *= -1;
                }
                
            }
            else if(board_[place_.first + i + 1][place_.second] == 0)
            {
                break;
            }
        }
    }
    //左
    if (i > 1 && board_[i - 1][j] == -disk_)
    {
        for (int k = 1; i - k > 0; k++)
        {
            if (board_[i - k - 1][j] == disk_)
            {
                can_place = true;
                break;
            }
            else if(board_[i - k - 1][j] == 0)
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
        for (int k = 1; j + k < 8; k++)
        {
            if (board_[i][j + k + 1] == disk_)
            {
                can_place = true;
                break;
            }
            else if(board_[i][j + k + 1] == 0)
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
        for (int k = 1; j - k > 0; k++)
        {
            if (board_[i][j - k - 1] == disk_)
            {
                can_place = true;
                break;
            }
            else if(board_[i][j - k - 1] == 0)
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
        for (int k = 1; i + k < 8 || j + k < 8; k++)
        {
            if (board_[i + k + 1][j + k + 1] == disk_)
            {
                can_place = true;
                break;
            }
            else if(board_[i + k + 1][j + k + 1] == 0)
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
        for (int k = 1; i - k > 0 || j - k > 0; k++)
        {
            if (board_[i - k - 1][j - k - 1] == disk_)
            {
                can_place = true;
                break;
            }
            else if(board_[i - k - 1][i - k - 1] == 0)
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
        for (int k = 1; i - k > 0 || j + k < 8; k++)
        {
            if (board_[i - k - 1][j + k + 1] == disk_)
            {
                can_place = true;
                break;
            }
            else if(board_[i - k - 1][j + k + 1] == 0)
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
}