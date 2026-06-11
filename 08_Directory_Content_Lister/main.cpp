
#include <filesystem>
#include <iostream>
using namespace std;
using namespace std::filesystem;
void print(path p)
{
    // if p points to a file , print its name and size
    if (is_regular_file(p))
    {
        uintmax_t size = file_size(p);
        cout << "File name : " <<p <<" , Size : "<<size<<endl;

        return;
    }
    if (is_directory(p))
    {
        cout << p << endl;
        for (const auto &entry : directory_iterator(p))
        {
            print(entry.path());
        }
        return;
    }

    // if p is a dir , print its name, size and call print for all its children
}
int main(int argc,char * argv[])
{
    if(argc!=2){
        cout<<"Usage : ./main <filepath> \n";
        return 1;
    }
    // Define the directory path to list files from
    path p = argv[1];
    print(p);
    return 0;
}