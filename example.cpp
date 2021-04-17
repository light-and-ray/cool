#include <cool/all.hpp>
using namespace cool;


int main()
{
    int num;

    loop
    {
        num = random(5, 15);
        if (num == 6 or num == 8) break;
        print(COOL_INFO(num));
    }

    println(); println();

    std::string s = "s";
    println((s + " " + 1.5 + " ") * 4);

}

/*
 
    Вывод:

    num = 5 num = 11 num = 7 num = 13 num = 11 num = 10

    s 1.500000 s 1.500000 s 1.500000 s 1.500000

*/