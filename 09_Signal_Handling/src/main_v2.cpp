#include <iostream>
#include <csignal>
#include <unistd.h>
#include <cstring>
void handler(int sig)
{
    char msg[]= "Received the Ctrl + C\n";
    write(1,msg,strlen(msg));
}
int main()
{
    signal(SIGINT, handler);
    pid_t pid = getpid();

    while (true)
    {
        std::cout << "To terminate : kill " << pid << std::endl;
        std::cout << "Skip Delusion. U r alright :)\n";
        unsigned int remaining_time = 1;
        while (remaining_time > 0)
        {
            remaining_time = sleep(remaining_time);
        }
    }
}