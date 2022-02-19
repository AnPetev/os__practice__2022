#include <stddef.h>
#include <stdio.h>

#include "printutilities.h"

void print_string( const char* str,const int size){
    printf("%s%d",str,size);
}
void print_integer(const int int_value){
    printf("%d",int_value);

}
void print_double(const double double_value){
    printf("%f",double_value);
}