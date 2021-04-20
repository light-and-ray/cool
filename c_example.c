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

#include <cool/c/unusing_print.h>
