#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
std::string trim(const std::string &str)
{
    const std::string whitespace = " \t\n\r\f\v";

    size_t start = str.find_first_not_of(whitespace);
    if (start == std::string::npos)
    {
        return ""; // string is all whitespace
    }

    size_t end = str.find_last_not_of(whitespace);
    return str.substr(start, end - start + 1);
}
int main()
{
    std::ifstream ifs("config.txt");
    int line_cnt = 1;
    if (!ifs)
    {
        std::cerr << "Config file doesnt exist \n";
    }
    std::string str;
    std::vector<std::string> configs;
    std::map<std::string, std::string> mp;
    while (getline(ifs, str))
    {

        std::string line;
        line = trim(str);
        if (line.empty() || line[0] == '#')
            continue;

        // tokenise and put it into the map

        size_t pos;
        if ((pos = line.find('=')) != std::string::npos)
        {
            mp[line.substr(0,pos)] = line.substr(pos + 1);
        }
        else 
        {
            std::cout << line_cnt << " : format <key>:<value>\n ";
        }

        //go to next line
        line_cnt++;
       
    }
    ifs.close();


    mp["port"]="9090";
    mp["max_connection"]="100";
    //open file to write 

    std::ofstream ofs("config.txt");
    for(auto entry:mp){
        ofs<<entry.first<<"="<<entry.second<<"\n";
    }
    ofs.close();

}