#include <iostream>
#include <vector>

class othello_board{
    private:
        std::vector<std::vector<int>> board; //オセロ盤 白:1 黒:-1 空:0
        int disks, disks_white, disks_black; //石の数

    public:
        othello_board();
        void show(); //盤面表示コンソールデバッグ用
        void set_board_default(); //オセロ盤セット
        void set_board(std::vector<std::vector<int>> board_); //オセロ盤セット（任意）
        std::vector<std::vector<int>> get_board(); //盤面取得
        bool judge_place_able(int disk_); //オセロ設置可能判定（設置できる場所があるか）
        std::vector<std::pair<int, int>> get_place_able(int disk_); //オセロ設置可能場所取得
        bool judge_place_able(std::pair<int, int> place_, int disk_); //オセロ設置可能判定（その場所が設置できるか）
        void place_disk(std::pair<int, int> place_, int disk_); //オセロ設置
        int get_disks_all(); //オセロの数取得
        int get_disks(int disk_); //オセロの数取得
        int get_disks_white(); //白の数取得
        int get_disks_black(); //黒の数取得
};

othello_board::othello_board()
{
    board = std::vector<std::vector<int>>(8, std::vector<int>(8, 0));
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

void othello_board::set_board_default()
{
    board[3][3] = 1;
    board[3][4] = -1;
    board[4][3] = -1;
    board[4][4] = 1;
}

void othello_board::set_board(std::vector<std::vector<int>> board_)
{
    board = board_;
}

std::vector<std::vector<int>> othello_board::get_board()
{
    return board;
}
