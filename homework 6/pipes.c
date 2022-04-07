#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


struct stack{
    int top;
    double items[100];
};
int stack[100];
int counter = 0;

void push(int value);
int pop();


double ev(char str[]);
void epush(struct stack *ps, double x);
double epop(struct stack *ps);
double oper(int symb, double op1, double op2);



void push(int value){
	stack[counter++] = value;
}
int pop(){
	if (counter == 0) return 0;
	return stack[--counter];
}
double ev(char str[]){
	int c,i;
	double opnd1,opnd2,value;
	struct stack opndstk;
	opndstk.top=-1;
	for(i=0;(c=str[i])!='\0';i++){
		if(isdigit(c)) epush(&opndstk,(double) (c-'0'));
		else{
			opnd2=epop(&opndstk);
			opnd1=epop(&opndstk);
			value=oper(c,opnd1,opnd2);
			epush(&opndstk,value);
		}
	}
	return (epop(&opndstk));
}
void epush(struct stack *ps, double x){
	ps->items[++(ps->top)]=x;
}

double epop(struct stack *ps){
	return(ps->items[ps->top--]);
}

double oper(int symb, double op1, double op2){
	switch(symb)
	{
		case '+':return(op1+op2);
		case '-':return(op1-op2);
		case '*':return(op1*op2);
		case '/':return(op1/op2);
	}
}
int main(int argc, char** argv){
    if (argc != 2) {
        printf("%s", "Usage error.\n");
        return 1;
    }
const char* path= "/receive_request";
if (mkfifo(path, 0666) == -1) {
        perror("fifo make");
        return 1;
    }
    const int fd = open(path, O_WRONLY);
    if (fd == -1) {
        perror("fifo open");
        return 1;
    }
    write(fd, argv[1], strlen(argv[1]));
    close(fd);
    return 0;
}
