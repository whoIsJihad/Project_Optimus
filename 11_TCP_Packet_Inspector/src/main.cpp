#include <iostream>
#include <fstream>
#include <string>

// written by deepseek R1

int main() {
    std::ifstream file("pcap.txt");
    std::string line;
    short int cnt=1;
    while (std::getline(file, line)) {
        // Skip tcpdump startup lines
        if (line.find("tcpdump:") == 0) continue;
        if (line.find("listening on") != std::string::npos) continue;
        if (line.find("packets captured") != std::string::npos) break;
        
        // Find timestamp
        size_t space = line.find(' ');
        if (space == std::string::npos) continue;
        std::string timestamp = line.substr(0, space);
        
        // Find src/dst
        size_t arrow = line.find(" > ");
        if (arrow == std::string::npos) continue;
        
        // Work backwards to find src start (after "IP ")
        size_t ip_pos = line.find("IP ");
        if (ip_pos == std::string::npos) continue;
        std::string src = line.substr(ip_pos + 3, arrow - (ip_pos + 3));
        
        // Find dst end (before space after dst)
        size_t dst_end = line.find(' ', arrow + 3);
        std::string dst = line.substr(arrow + 3, dst_end - (arrow + 3));
        
        // Find length
        size_t len_pos = line.find("length ");
        std::string len_str = line.substr(len_pos + 7);
        std::cout<< "\nEntry no :"<<cnt++<<std::endl;

        // Replace len extraction with:
        size_t paren_open = line.rfind('(');
        size_t paren_close = line.rfind(')');
        if (paren_open != std::string::npos && paren_close != std::string::npos) {
            len_str = line.substr(paren_open + 1, paren_close - paren_open - 1);
        }
        std::cout << timestamp << " | " << src << " -> " << dst << " | len=" << len_str << "\n";
    }
    return 0;
}