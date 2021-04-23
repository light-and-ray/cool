#include <cool/all.hpp>
using namespace cool;
using std::cout;
#include <vector>


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

    setCyrillic();
    println();
    println("Êëàññíàÿ", "Cool");
    println();

    for (int i : range(0, 20))
    {
        print(i);
    }
    println(); println();

    std::vector v = { "a", "b", "6", "g" };

    for (auto& [i, x] : enumerate(v))
    {
        cout << "v[%s] = %s\n"_f % i % x;
    }
    println();
}

/*
 
Out:

    num = 5 num = 11 num = 7 num = 13 num = 11 num = 10

    s 1.500000 s 1.500000 s 1.500000 s 1.500000

    Привет Cool

    num = 5 num = 11 num = 7 num = 13 num = 11 num = 10

    0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19

    v[0] : a
    v[1] : b
    v[2] : 6
    v[3] : g


    
*/
