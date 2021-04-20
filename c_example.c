#include <cool/c/print.h>
#include <cool/c/using_print.h>

int main()
{
    cool_println("Cool", "lib");
    
    print_sep = "-";

    for (int i = 0; i < 7; i++)
    {
        print(i + 1);
    }

    printlnn(); printlnn();

    char* few = "few";

    print_sep = " ";

    println("This", "support", few, "types", 2, 2.574, 10u);
    printlnn();

    println("Up to 12 params:");
    println(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12);

}

int main()
{
    println(5, "C11", "_Generic", 14.5, "Any type, any number!", 1.2f);
    printlnn();

//  prints: 5 C11 _Generic 14.5000 Any type, any number! 2.0000

    print_sep = "; ";

    for (int i = 0; i < 7; i++)
    {
        print(i + 1);
    }

}




#include <cool/c/unusing_print.h>

/*

Out:

    Cool lib
    1-2-3-4-5-6-7-

    This support few types 2 2.5740 0010

    Up to 12 params:
    1 2 3 4 5 6 7 8 9 10 11 12

*/
