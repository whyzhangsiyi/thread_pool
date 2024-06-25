#include"threadPool.hpp"
#include<iostream>
int main(){



    // ziggy::threadPool tp;

    ziggy::task<int,int,int> tk([](int a,int b){std::cout<<"a= "<<a<<"b=  " <<b<<std::endl;return 9;});
    tk(2,4);

    int ret=tk.wait_get();
    std::cout<<ret;

}   