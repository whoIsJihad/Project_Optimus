#include <iostream>

class ArenaAllocator
{
    char *buffer;
    size_t capacity;
    size_t offset;

public:
    ArenaAllocator(size_t capacity): offset(0),capacity(capacity)
    {
        buffer = new char[capacity];
    }
    void *allocate_memory(size_t chunk)
    {
        if(offset+chunk>capacity) return nullptr;
        void * chunk_addr= (void*)(buffer + offset);
        offset+=chunk;
        return chunk_addr;
    }
    void print_state(){
        std::cout<<"Internal state of allocator \n";
        std::cout<<"Offset : "<<offset<<"\nCapacity : "<< capacity<<"\nBuffer :"<< (void*)buffer<<std::endl;
    }
    ~ArenaAllocator()
    {
        delete[] buffer;
    }
};

int main(){
    // ArenaAllocator aa(100);
    // aa.print_state();
    // void * first = aa.allocate_memory(16);
    // aa.print_state();
    // void * second = aa.allocate_memory(32);
    // aa.print_state();
    // void * third = aa.allocate_memory(1);
    // aa.print_state();
    // void * fourth=aa.allocate_memory(1);
    // std::cout<<first<<std::endl;
    // std::cout<<second<<std::endl;
    // std::cout<<third<<std::endl;
    // std::cout<<fourth<<std::endl;
}