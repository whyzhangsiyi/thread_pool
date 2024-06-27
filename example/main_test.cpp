#include <iostream>
#include"any.hpp"
#include"task.hpp"
int main()
{

    any r(8);

    std::cout<<r.cast_<long>()<<std::endl;
    

}