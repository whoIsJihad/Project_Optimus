#include <iostream>
#include <fstream>
#include <iomanip>

int main(int argc, char *argv[])
{
    std::string filepath ;
    if (argc == 2)
    {
        filepath = argv[1];
    }
    else
    {
        std::cout << "Usage : hexdump <filepath> " << std::endl;
        return 1;
    }

    // open a file in bin mode
    std::ifstream ifs(filepath, std::ios::binary);

    // Check if opened correctly
    if (!ifs)
    {
        std::cerr << "Error in opening file " << std::endl;
        return 1;
    }

    // declare a buffer of size n
    char buffer[1024];
    // offset to print in a better way
    size_t off = 0;

    // char count to print offset and 16 char
    int char_cnt = 0;

    int line_break = 0;
    while (1)
    {
        ifs.read(buffer, 1024);
        int read_bytes = ifs.gcount();
        if (read_bytes == 0)
            break;
        for (int i = 0; i < read_bytes; i++)
        {
            unsigned char byte = buffer[i];
            if (char_cnt == 0)
            
            {
            // start of line    
                std::cout<<"offset  ";
                std::cout << std::hex << std::setw(16) << std::setfill('0') << off;
                std::cout << std::dec << std::setfill(' ') << " : ";
             

            }

            std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)byte << std::dec << "\t";
            char_cnt++;
            if (char_cnt == 16)
            {
                // end of line
                char_cnt = 0;
                std::cout << std::endl;
                off += 16;
            }
        }
    }

    ifs.close();

    return 0;
}
