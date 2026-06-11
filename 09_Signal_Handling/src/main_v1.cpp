#include<iostream>
#include<csignal>
#include<unistd.h>

void handler(int sig){
    std::cout<<"Received "<<sig<<std::endl;
    //read ../Tutorial/bug1.md to understand why std::cout inside signal handler is not okay 
}
int main(){
    signal(SIGINT,handler);
    pid_t pid=getpid();

    while(true){
        std::cout<<"To terminate : kill "<<pid<<std::endl;
        std::cout<<"Skip Delusion. U r alright :)\n";
        sleep(1);
    }
}