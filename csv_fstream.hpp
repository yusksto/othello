#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class csv_fstream
{
    public:
        std::vector<std::vector<std::string>> input_csv(std::string filename_);
        void output_csv(std::string filename_, std::vector<std::vector<std::string>> data_);
};

std::vector<std::vector<std::string>> csv_fstream::input_csv(std::string filename_)
{
    std::ifstream ifs(filename_);
    
}

void csv_fstream::output_csv(std::string filename_, std::vector<std::vector<std::string>> data_)
{

}
