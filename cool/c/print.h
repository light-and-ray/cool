#ifndef COOL_C_PRINT_H
#define COOL_C_PRINT_H

#include <stdarg.h>
#include <stdio.h>

#define COOL_HIDDEN_INT 0
#define COOL_HIDDEN_STRING 1
#define COOL_HIDDEN_FLOAT 2
#define COOL_HIDDEN_DOUBLE 3
#define COOL_HIDDEN_CHAR 4
#define COOL_HIDDEN_UINT 5
#define COOL_HIDDEN_LONG 6
#define COOL_HIDDEN_VOID 7

int cool_hidden_types[12];
int cool_hidden_last = 0;

void cool_hidden_add_int()
{
    cool_hidden_types[cool_hidden_last] = COOL_HIDDEN_INT;
    cool_hidden_last += 1;
}

void cool_hidden_add_string()
{
    cool_hidden_types[cool_hidden_last] = COOL_HIDDEN_STRING;
    cool_hidden_last += 1;
}

void cool_hidden_add_float()
{
    cool_hidden_types[cool_hidden_last] = COOL_HIDDEN_FLOAT;
    cool_hidden_last += 1;
}

void cool_hidden_add_double()
{
    cool_hidden_types[cool_hidden_last] = COOL_HIDDEN_DOUBLE;
    cool_hidden_last += 1;
}

void cool_hidden_add_char()
{
    cool_hidden_types[cool_hidden_last] = COOL_HIDDEN_CHAR;
    cool_hidden_last += 1;
}

void cool_hidden_add_uint()
{
    cool_hidden_types[cool_hidden_last] = COOL_HIDDEN_UINT;
    cool_hidden_last += 1;
}

void cool_hidden_add_long()
{
    cool_hidden_types[cool_hidden_last] = COOL_HIDDEN_LONG;
    cool_hidden_last += 1;
}

void cool_hidden_add_void()
{
    cool_hidden_types[cool_hidden_last] = COOL_HIDDEN_VOID;
    cool_hidden_last += 1;
}




#define cool_hidden_add(x)          \
    _Generic((x),       \
    int: cool_hidden_add_int,       \
    char*: cool_hidden_add_string, \
    float: cool_hidden_add_float, \
    double: cool_hidden_add_double, \
    char: cool_hidden_add_char, \
    unsigned int: cool_hidden_add_uint, \
    long: cool_hidden_add_long, \
    default: cool_hidden_add_void \
)()

#define COOL_CAST(T, x) *((T*) (x))

void cool_hidden_print(char* sep, int n, ...)
{
    va_list argptr;
    va_start(argptr, n);

    void* x;

    for (int i = 0; i < n; i++)
    {
        switch (cool_hidden_types[i])
        {
        case COOL_HIDDEN_INT:
            x = &va_arg(argptr, int);
            printf("%d%s", COOL_CAST(int, x), sep);
            break;

        case COOL_HIDDEN_STRING:
            x = &va_arg(argptr, char*);
            printf("%s%s", COOL_CAST(char*, x) , sep);
            break;

        case COOL_HIDDEN_FLOAT:
            x = &va_arg(argptr, float);
            printf("%.4f%s", COOL_CAST(float, x), sep);
            break;

        case COOL_HIDDEN_DOUBLE:
            x = &va_arg(argptr, double);
            printf("%.4f%s", COOL_CAST(double, x), sep);
            break;

        case COOL_HIDDEN_CHAR:
            x = &va_arg(argptr, char);
            printf("%c%s", COOL_CAST(char, x), sep);
            break;

        case COOL_HIDDEN_UINT:
            x = &va_arg(argptr, unsigned int);
            printf("%.4u%s", COOL_CAST(unsigned int, x), sep);
            break;

        case COOL_HIDDEN_VOID:
            printf("unsupported type%s", sep);
            break;

        default:
            printf("Internal COOL/CPRINT error line: %d in %s", __LINE__, __FILE__);
            break;
        } 
    }

    va_end(argptr);
    cool_hidden_last = 0;
}

char* cool_print_sep = " ";

//hide this a big part of code
#if 1 

#define cool_print_12(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, ...)   \
    cool_hidden_add(x1); \
    cool_hidden_add(x2); \
    cool_hidden_add(x3); \
    cool_hidden_add(x4); \
    cool_hidden_add(x5); \
    cool_hidden_add(x6); \
    cool_hidden_add(x7); \
    cool_hidden_add(x8); \
    cool_hidden_add(x9); \
    cool_hidden_add(x10); \
    cool_hidden_add(x11); \
    cool_hidden_add(x12); \
    cool_hidden_print(cool_print_sep, 12, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12)

#define cool_print_11(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, ...)   \
    cool_hidden_add(x1); \
    cool_hidden_add(x2); \
    cool_hidden_add(x3); \
    cool_hidden_add(x4); \
    cool_hidden_add(x5); \
    cool_hidden_add(x6); \
    cool_hidden_add(x7); \
    cool_hidden_add(x8); \
    cool_hidden_add(x9); \
    cool_hidden_add(x10); \
    cool_hidden_add(x11); \
    cool_hidden_print(cool_print_sep, 11, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11)

#define cool_print_10(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, ...)   \
    cool_hidden_add(x1); \
    cool_hidden_add(x2); \
    cool_hidden_add(x3); \
    cool_hidden_add(x4); \
    cool_hidden_add(x5); \
    cool_hidden_add(x6); \
    cool_hidden_add(x7); \
    cool_hidden_add(x8); \
    cool_hidden_add(x9); \
    cool_hidden_add(x10); \
    cool_hidden_print(cool_print_sep, 10, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10)

#define cool_print_9(x1, x2, x3, x4, x5, x6, x7, x8, x9, ...)   \
    cool_hidden_add(x1); \
    cool_hidden_add(x2); \
    cool_hidden_add(x3); \
    cool_hidden_add(x4); \
    cool_hidden_add(x5); \
    cool_hidden_add(x6); \
    cool_hidden_add(x7); \
    cool_hidden_add(x8); \
    cool_hidden_add(x9); \
    cool_hidden_print(cool_print_sep, 9, x1, x2, x3, x4, x5, x6, x7, x8, x9)

#define cool_print_8(x1, x2, x3, x4, x5, x6, x7, x8, ...)   \
    cool_hidden_add(x1); \
    cool_hidden_add(x2); \
    cool_hidden_add(x3); \
    cool_hidden_add(x4); \
    cool_hidden_add(x5); \
    cool_hidden_add(x6); \
    cool_hidden_add(x7); \
    cool_hidden_add(x8); \
    cool_hidden_print(cool_print_sep, 8, x1, x2, x3, x4, x5, x6, x7, x8)

#define cool_print_7(x1, x2, x3, x4, x5, x6, x7, ...)   \
    cool_hidden_add(x1); \
    cool_hidden_add(x2); \
    cool_hidden_add(x3); \
    cool_hidden_add(x4); \
    cool_hidden_add(x5); \
    cool_hidden_add(x6); \
    cool_hidden_add(x7); \
    cool_hidden_print(cool_print_sep, 7, x1, x2, x3, x4, x5, x6, x7)

#define cool_print_6(x1, x2, x3, x4, x5, x6, ...)   \
    cool_hidden_add(x1); \
    cool_hidden_add(x2); \
    cool_hidden_add(x3); \
    cool_hidden_add(x4); \
    cool_hidden_add(x5); \
    cool_hidden_add(x6); \
    cool_hidden_print(cool_print_sep, 6, x1, x2, x3, x4, x5, x6)


#define cool_print_5(x1, x2, x3, x4, x5, ...)   \
    cool_hidden_add(x1); \
    cool_hidden_add(x2); \
    cool_hidden_add(x3); \
    cool_hidden_add(x4); \
    cool_hidden_add(x5); \
    cool_hidden_print(cool_print_sep, 5, x1, x2, x3, x4, x5)

#define cool_print_4(x1, x2, x3, x4, ...)   \
    cool_hidden_add(x1); \
    cool_hidden_add(x2); \
    cool_hidden_add(x3); \
    cool_hidden_add(x4); \
    cool_hidden_print(cool_print_sep, 4, x1, x2, x3, x4)

#define cool_print_3(x1, x2, x3, ...)   \
    cool_hidden_add(x1); \
    cool_hidden_add(x2); \
    cool_hidden_add(x3); \
    cool_hidden_print(cool_print_sep, 3, x1, x2, x3)

#define cool_print_2(x1, x2, ...)   \
    cool_hidden_add(x1); \
    cool_hidden_add(x2); \
    cool_hidden_print(cool_print_sep, 2, x1, x2)

#define cool_print_1(x, ...)   \
    cool_hidden_add(x); \
    cool_hidden_print(cool_print_sep, 1, x)


#endif //hide this a big part of code

//#define COOL_HAS_COMMA(_0, _1, _2, ...) _2

/*
#define cool_print(...)\
        COOL_HAS_COMMA(__VA_ARGS__,\
            cool_print_(__VA_ARGS__ , COOL_RSEQ_N()),\
            printf(cool_cprint_sep))
            */

#define cool_print(...) \
	cool_print_(__VA_ARGS__ , COOL_RSEQ_N())


#define cool_print_(...) \
	COOL_ARG_N(__VA_ARGS__)

#define COOL_ARG_N( \
    _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
    _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
    _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
    _61,_62,_63, n, ...) \
                        \
    cool_print_##n(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11,_12)

#define COOL_RSEQ_N() \
    63,62,61,60,59,58,57,56,55,54,53,52,51,50, \
    49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30, \
    29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10, \
    9,8,7,6,5,4,3,2,1,0


#define cool_println(...) \
    cool_print(__VA_ARGS__);\
    printf("\n")

#define cool_printlnn() printf("\n")

#endif // !COOL_CPRINT_H
