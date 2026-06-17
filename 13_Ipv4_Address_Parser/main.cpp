#include <iostream>
#include <string>
#include <cstdint>
#include <cctype>
#include <algorithm>

struct addrinfo
{
    uint32_t ip;
    uint16_t port;
};
bool isNumeric(const std::string &str)
{
    return !str.empty() && std::all_of(str.begin(), str.end(),::isdigit);
}
bool check_octet(const std::string &str){
    if(!isNumeric(str)) return false;
    uint32_t number = std::stoi(str);
    return number>=0 && number <= 255;
}
bool validate_addr(struct addrinfo *addr_, std::string addr)
{
    size_t colonPosition = addr.find(':');
    if (colonPosition == std::string::npos)
    {
        return false;
    }
    if (addr.find(':', colonPosition + 1) != std::string::npos)
    {
        return false;
    }
    size_t first_dot= addr.find('.');
    if(first_dot==std::string::npos){
        return false;
    }
    std::string octet1=addr.substr(0,first_dot);

    size_t second_dot= addr.find('.',first_dot+1);
    if(second_dot==std::string::npos){
        return false;
    }
    std::string octet2=addr.substr(first_dot+1,second_dot-first_dot-1);
    
    size_t third_dot= addr.find('.',second_dot+1);
    if(third_dot==std::string::npos){
        return false;
    }
    std::string octet3=addr.substr(second_dot+1,third_dot-second_dot-1);
// git rm -r --cached directory/
// git commit -m "Stop tracking directory"
    std::string octet4= addr.substr(third_dot+1,colonPosition-third_dot-1);
    std::string port_string=addr.substr(colonPosition+1);
    if( !check_octet(octet1) || !check_octet(octet2) || !check_octet(octet3) || !check_octet(octet4)) return false;
    uint32_t o1=stoi(octet1);
    uint32_t o2=stoi(octet2);
    uint32_t o3=stoi(octet3);
    uint32_t o4=stoi(octet4);
    uint32_t ip=o1 << 24 | o2 << 16 | o3 << 8 | o4;
    if(!isNumeric(port_string)) return false;
    int port=stoi(port_string);
    if(port<0 || port > 65535) return false;
    addr_->ip=ip;
    addr_->port=port;
    return true;
}
int main()
{
    std::string addr= "192.168.1.-1:80";
    struct addrinfo st;
    bool valid=validate_addr(&st,addr);
    if(valid==false){
        std::cout<<"Invalid address and port\n";
    }
    else{
        std::cout<<"Valid address and port \n";
        std::cout<<st.ip<<std::endl;
        std::cout<<st.port<<std::endl;
    }
}