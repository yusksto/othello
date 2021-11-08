#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class csv_fstream
{
    public:
        bool can_open(std::string filename_);
        std::vector<std::vector<std::string>> input_csv(std::string filename_);
        void output_csv(std::string filename_, std::vector<std::vector<std::string>> data_);
};

bool csv_fstream::can_open(std::string filename_)
{
    std::fstream fs(filename_);
    if (fs.is_open())
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::vector<std::vector<std::string>> csv_fstream::input_csv(std::string filename_)
{

}

void csv_fstream::output_csv(std::string filename_, std::vector<std::vector<std::string>> data_)
{

}
