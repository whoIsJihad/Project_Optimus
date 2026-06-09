#include<iostream>
class Circular_Queue{
    int capacity;
    int size;
    int front;
    int back;
    int* arr;    
    public :
    Circular_Queue(int c) : capacity(c),front(0),back(0),size(0){
        arr=new int[capacity];

    }
    void push(int ele){
        if(size==capacity-1) return;
        arr[back]=ele;
        back= (back+1)%capacity;
        size++;
    }

    int pop(){
        if(size==0) return -1;
        int ele=arr[front];
        front=(front+1)%capacity;
        size--;
        return ele;
    }

    void print(){
        int n=size;
        int start=front;
        if(n==0) return;
        std::cout<<"Queue : ";
        while(n--){
            std::cout<<arr[start]<<" ";
            start=(start+1)%capacity;
        }
        std::cout<<std::endl;
    }
    ~Circular_Queue(){
        delete [] arr;
    }
};

int main(){
    // Circular_Queue c(8);    
}