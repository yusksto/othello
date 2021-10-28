#include "Eigen/Eigen"
#include <vector>

class othello_ai{
    public:
        othello_ai(std::vector<std::vector<int>> parameter_, int mode_); //othello_aiセット
        std::pair<int, int> get_place_ai(std::vector<std::vector<int>> board_, int disk_); //設置場所取得

    private:
        std::vector<std::vector<int>> board; //盤面
        std::vector<std::vector<int>> parameter; //盤面評価パラメータ
        int mode; //aiモード

        bool judge_place_able(int disk_); //設置可能判定
        std::vector<std::pair<int, int>> get_place_able(int disk_); //設置可能場所取得
        std::vector<std::vector<int>> get_board_placed(std::vector<std::vector<int>> board_, std::pair<int, int> place_, int disk_); //設置後盤面取得



    
};

othello_ai::othello_ai(std::vector<std::vector<int>> parameter_, int mode_){
    board = std::vector<std::vector<int>>(8, std::vector<int>(8, 0));
    parameter = parameter_;
    mode = mode_;
}

std::pair<int, int> othello_ai::get_place_ai(std::vector<std::vector<int>> board_, int disk_){
    board = board_;











}

std::vector<std::pair<int, int>> othello_ai::get_place_able(int disk_){
    std::vector<std::pair<int, int>> r;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            bool can_place = false;

            //右
            if (i + 1 < 7 && board[i + 1][j] == -disk_)
            {
                for (int k = 1; i + k < 8; k++)
                {
                    if (board[i + k + 1][j] == disk_)
                    {
                        can_place = true;
                        break;
                    }
                    else if(board[i + k + 1][j] == 0)
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
            if (i - 1 > 0 && board[i - 1][j] == -disk_)
            {
                for (int k = 1; i - k > 0; k++)
                {
                    if (board[i - k - 1][j] == disk_)
                    {
                        can_place = true;
                        break;
                    }
                    else if(board[i - k - 1][j] == 0)
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




}

