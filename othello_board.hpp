#include <iostream>
#include <vector>
class othello_board {
private:
    std::vector<std::vector<int>> board; //オセロ盤 白:1 黒:-1 空:0
    int disks, disks_white, disks_black; //石の数

public:
    othello_board();
    void show(); //盤面表示コンソールデバッグ用 （終了）
    void set_board_default(); //オセロ盤セット　（終了）
    void set_board(std::vector<std::vector<int>> board_); //オセロ盤セット（任意）
    std::vector<std::vector<int>> get_board(); //盤面取得（終了）
    std::vector<std::pair<int, int>> get_place_able(int disk_); //オセロ設置可能場所取得（終了）
    bool judge_place_able(int disk_); //オセロ設置可能判定（設置できる場所があるか）
    bool judge_place_able(std::pair<int, int> place_, int disk_); //オセロ設置可能判定（その場所が設置できるか）
    void place_disk(std::pair<int, int> place_, int disk_); //オセロ設置
    int get_disks_all(); //オセロの数取得(終了)
    int get_disks(int disk_); //オセロの数取得(終了)
    int get_disks_white(); //白の数取得
    int get_disks_black(); //黒の数取得
};

othello_board::othello_board()
{
    board = std::vector<std::vector<int>>(8, std::vector<int>(8, 0));
    board[3][3] = 1;
    board[3][4] = -1;
    board[4][3] = -1;
    board[4][4] = 1;
    
    disks = 0;
    disks_white = 0;
    disks_black = 0;
}

void othello_board::show()
{
    for (const auto& e1 : board)
    {
        for (const auto& e2 : e1)
        {
            std::cout << e2 << " ";
        }
        std::cout << std::endl;
    }
}

void othello_board::set_board_default()//オセロ盤セット
{
    board = std::vector<std::vector<int>>(8, std::vector<int>(8, 0));
    board[3][3] = 1;
    board[3][4] = -1;
    board[4][3] = -1;
    board[4][4] = 1;
}

void othello_board::set_board(std::vector<std::vector<int>> board_)//任意のやつ
{
    board = board_;
}

std::vector<std::vector<int>> othello_board::get_board()//盤面取得
{
    return board;
}

std::vector<std::pair<int, int>> othello_board::get_place_able(int disk_)//設置可能場所取得
{
    std::vector<std::pair<int, int>> r;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j] != 0)
            {
                continue;
            }
            bool can_place = false;
            //右
            if (i < 6 && board[i + 1][j] == -disk_)
            {
                for (int k = 2; i + k < 8; k++)
                {
                    if (board[i + k][j] == disk_)
                    {
                        can_place = true;
                        break;
                    }
                    else if (board[i + k][j] == 0)
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
            if (i > 1 && board[i - 1][j] == -disk_)
            {
                for (int k = 2; i - k > -1; k++)
                {
                    if (board[i - k][j] == disk_)
                    {
                        can_place = true;
                        break;
                    }
                    else if (board[i - k][j] == 0)
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
            if (j < 6 && board[i][j + 1] == -disk_)
            {
                for (int k = 2; j + k < 8; k++)
                {
                    if (board[i][j + k] == disk_)
                    {
                        can_place = true;
                        break;
                    }
                    else if (board[i][j + k] == 0)
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
            if (j > 1 && board[i][j - 1] == -disk_)
            {
                for (int k = 2; j - k > -1; k++)
                {
                    if (board[i][j - k] == disk_)
                    {
                        can_place = true;
                        break;
                    }
                    else if (board[i][j - k] == 0)
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
            if (i < 6 && j < 6 && board[i + 1][j + 1] == -disk_)
            {
                for (int k = 2; i + k < 8 && j + k < 8; k++)
                {
                    if (board[i + k][j + k] == disk_)
                    {
                        can_place = true;
                        break;
                    }
                    else if (board[i + k][j + k] == 0)
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
            if (i > 1 && j > 1 && board[i - 1][j - 1] == -disk_)
            {
                for (int k = 2; i - k > -1 && j - k > -1; k++)
                {
                    if (board[i - k][j - k] == disk_)
                    {
                        can_place = true;
                        break;
                    }
                    else if (board[i - k][i - k] == 0)
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
            if (i > 1 && j < 6 && board[i - 1][j + 1] == -disk_)
            {
                for (int k = 2; i - k > -1 && j + k < 8; k++)
                {
                    if (board[i - k][j + k] == disk_)
                    {
                        can_place = true;
                        break;
                    }
                    else if (board[i - k][j + k] == 0)
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
            if (i < 6 && j > 1 && board[i + 1][j - 1] == -disk_)
            {
                for (int k = 2; i + k < 8 && j - k > -1; k++)
                {
                    if (board[i + k][j - k] == disk_)
                    {
                        can_place = true;
                        break;
                    }
                    else if (board[i + k][j - k] == 0)
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
}//設置可能の判定

bool othello_board::judge_place_able(int disk_) //オセロ設置可能判定（設置できる場所があるか）
{
    std::vector<std::pair<int, int>> r = get_place_able(disk_);
    if (r.size() == 0) 
    {
        return false;
    }
    return true;
}

bool othello_board::judge_place_able(std::pair<int, int> place_, int disk_)//オセロ設置可能場所取得
{
    std::vector<std::pair<int, int>> r = get_place_able(disk_);
    for (int i = 0; i < r.size(); i++)
    {
        if (r[i].first == place_.first && r[i].second == place_.second)
        {
            return true;
        }
    }
    return false;
}

void othello_board::place_disk(std::pair<int, int> place_, int disk_)//オセロ設置
{
    board[place_.first][place_.second] = disk_;
    //右
    if (place_.first < 6 && board[place_.first + 1][place_.second] == -disk_)
    {
        for (int i = 2; place_.first + i < 8; i++)
        {
            if (board[place_.first + i][place_.second] == disk_)
            {
                for (int j = 1; j < i; j++)
                {
                    board[place_.first + j][place_.second] *= -1;
                }
                break;
            }
            else if (board[place_.first + i][place_.second] == 0)
            {
                break;
            }
        }
    }
    //左
    if (place_.first > 1 && board[place_.first - 1][place_.second] == -disk_)
    {
        for (int i = 2; place_.first - i > -1; i++)
        {
            if (board[place_.first - i][place_.second] == disk_)
            {
                for (int j = 1; j < i; j++)
                {
                    board[place_.first - j][place_.second] *= -1;
                }
                break;
            }
            else if (board[place_.first - i][place_.second] == 0)
            {
                break;
            }
        }
    }
    //下
    if (place_.second < 6 && board[place_.first][place_.second + 1] == -disk_)
    {
        for (int i = 2; place_.second + i < 8; i++)
        {
            if (board[place_.first][place_.second + i] == disk_)
            {
                for (int j = 1; j < i; j++)
                {
                    board[place_.first][place_.second + j] *= -1;
                }
                break;
            }
            else if (board[place_.first][place_.second + i] == 0)
            {
                break;
            }
        }
    }
    //上
    if (place_.second > 1 && board[place_.first][place_.second - 1] == -disk_)
    {
        for (int i = 2; place_.second - i > -1; i++)
        {
            if (board[place_.first][place_.second - i] == disk_)
            {
                for (int j = 1; j < i; j++)
                {
                    board[place_.first][place_.second - j] *= -1;
                }
                break;
            }
            else if (board[place_.first][place_.second - i] == 0)
            {
                break;
            }
        }
    }
    //右下
    if (place_.first < 6 && place_.second < 6 && board[place_.first + 1][place_.second + 1] == -disk_)
    {
        for (int i = 2; place_.first + i < 8 && place_.second + i < 8; i++)
        {
            if (board[place_.first + i][place_.second + i] == disk_)
            {
                for (int j = 1; j < i; j++)
                {
                    board[place_.first + j][place_.second + j] *= -1;
                }
                break;
            }
            else if (board[place_.first + i][place_.second + i] == 0)
            {
                break;
            }
        }
    }
    //左上
    if (place_.first > 1 && place_.second > 1 && board[place_.first - 1][place_.second - 1] == -disk_)
    {
        for (int i = 2; place_.first - i > -1 && place_.second - i > -1; i++)
        {
            if (board[place_.first - i][place_.second - i] == disk_)
            {
                for (int j = 1; j < i; j++)
                {
                    board[place_.first - j][place_.second - j] *= -1;
                }
                break;
            }
            else if (board[place_.first - i][place_.second - i] == 0)
            {
                break;
            }
        }
    }
    //左下
    if (place_.first > 1 && place_.second < 6 && board[place_.first - 1][place_.second + 1] == -disk_)
    {
        for (int i = 2; place_.first - i > -1 && place_.second + i < 8; i++)
        {
            if (board[place_.first - i][place_.second + i] == disk_)
            {
                for (int j = 1; j < i; j++)
                {
                    board[place_.first - j][place_.second + j] *= -1;
                }
                break;
            }
            else if (board[place_.first - i][place_.second + i] == 0)
            {
                break;
            }
        }
    }
    //左上
    if (place_.first < 6 && place_.second > 1 && board[place_.first + 1][place_.second - 1] == -disk_)
    {
        for (int i = 2; place_.first + i < 8 && place_.second - i > -1; i++)
        {
            if (board[place_.first + i][place_.second - i] == disk_)
            {
                for (int j = 1; j < i; j++)
                {
                    board[place_.first + j][place_.second - j] *= -1;
                }
                break;
            }
            else if (board[place_.first + i][place_.second - i] == 0)
            {
                break;
            }
        }
    }
}

int othello_board::get_disks_all() //オセロの数取得
{
    int disks = 0;
    for (const auto& e1 : board)
    {
        for (const auto& e2 : e1)
        {
            if (e2 != 0)
            {
                disks++;
            }
        }
    }
    return disks;
}

int othello_board::get_disks(int disk_) //オセロの数取得
{
    int disks = 0;
    for (const auto& e1 : board)
    {
        for (const auto& e2 : e1)
        {
            if (e2 == disk_)
            {
                disks++;
            }
        }
    }
    return disks;
}

int othello_board::get_disks_white() //白の数取得
{
    int disks = 0;
    for (const auto& e1 : board)
    {
        for (const auto& e2 : e1)
        {
            if (e2 == 1)
            {
                disks++;
            }
        }
    }
    return disks;
}

int othello_board::get_disks_black() //黒の数取得
{
    int disks = 0;
    for (const auto& e1 : board)
    {
        for (const auto& e2 : e1)
        {
            if (e2 == -1)
            {
                disks++;
            }
        }
    }
    return disks;
}