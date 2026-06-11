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
    void *allocate_memory(size_t chunk, size_t alignment)
    {
        //aligning the mem address
        size_t rem= offset % alignment;
        if(rem!=0){
            offset+=(alignment-rem);
        }


        if(offset+chunk>capacity) return nullptr;
        void * chunk_addr= (void*)(buffer + offset);
        offset+=chunk;
        return chunk_addr;
    }

    void reset(){
        offset=0;
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
    
}