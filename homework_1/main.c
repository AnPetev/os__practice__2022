
#include<stdio.h>
#include <stddef.h>
#include<string.h>
#include  "printutilities.h"


int main(int argc,char** argv){
    char* mess="Hello world";
    print_string(mess,strlen(mess));
    print_integer(21);
    print_double(1.45);
    return 0;
}