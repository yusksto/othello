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
    std::ifstream ifs(filename_);
    if (!ifs) {
        std::vector<std::vector<std::string>> data;
        return data;
    }

    std::vector<std::vector<std::string>> data;
    std::string buf;
    while (std::getline(ifs, buf)) {
        if (buf.size() == 0) break;
        std::istringstream iss(buf);
        std::vector<std::string> tmp;
        while (std::getline(iss, buf, ','))
        {
            tmp.push_back(buf);
        }
        data.push_back(tmp);
    }
    return data;
}




void csv_fstream::output_csv(std::string filename_, std::vector<std::vector<std::string>> data_)
{
    std::ofstream ofs(filename_);
    for (int i = 0; i < data_.size(); i++) {
        for (int j = 0; j < data_[i].size(); j++) {
            ofs << data_[i][j] << ",";
        }
        ofs << std::endl;
    }
}
