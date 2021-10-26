#include "Eigen/Eigen"
#include <vector>

class othello_ai{
    private:
        Eigen::MatrixXi convert_vector_to_matrix(std::vector<std::vector<int>> vector);
        std::vector<std::vector<int>> convert_matrix_to_vector(Eigen::MatrixXi matrix);

        bool judge_place_able(int disk);
        std::vector<std::pair<int, int>> get_place_able(int disk);




    public:
        std::vector<int> get_place_ai(std::vector<std::vector<int>> board, int disk);

};



Eigen::MatrixXi othello_ai::convert_vector_to_matrix(std::vector<std::vector<int>> vector){
    Eigen::MatrixXi matrix(8,8); 
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            matrix(i,j) = vector[i][j];
        }   
    }
    return matrix;
}

std::vector<std::vector<int>> othello_ai::convert_matrix_to_vector(Eigen::MatrixXi matrix){
    std::vector<std::vector<int>> vector = std::vector<std::vector<int>>(8,std::vector<int>(8,0));
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            vector[i][j] = matrix(i,j);
        }   
    }
    return vector;
}

std::vector<std::pair<int, int>> othello_ai::get_place_able(int disk){
    std::pair<int, int> r;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            
        }
        
    }
    



}

std::vector<int> othello_ai::get_place_ai(std::vector<std::vector<int>> board, int disk){












}