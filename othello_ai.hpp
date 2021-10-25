#include "Eigen/Eigen"
#include　<vector>

Eigen::MatrixXi convert_vector_to_matrix(std::vector<std::vector<int>>);
std::vector<std::vector<int>> convert_matrix_to_vector(Eigen::MatrixXi);

Eigen::MatrixXi convert_vector_to_matrix(std::vector<std::vector<int>> vector){
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

std::vector<std::vector<int>> convert_matrix_to_vector(Eigen::MatrixXi matrix){
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