/*
loop forever :
for top - of - stack symbol , s , and next input symbol , a case
action of T [s , a ]
shift x : ( x is a STATE number )
push a , then x on the top of the stack and
advance ip to point to the next input symbol .
reduce y : ( y is a PRODUCTION number )
Assume that the production is of the form
A == > beta
pop 2 * | beta | symbols of the stack . At this
point the top of the stack should be a state number ,
say s ’ , push A , then goto of T [ s ’ ,A ] ( a state number )
on the top of the stack . Output the production
A == > beta .
accept :
return --- a successful parse .
default :
error --- the input string is not in the language .*/
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int k = 0, z = 0, i = 0, j = 0, c = 0;
char input[16], ac[20], stk[15], act[10];

void check();

int main() {

    printf("GRAMMAR is E->E+E \n E->E*E \n E->(E) \n E->id \n");
    printf("Enter input string: ");
    scanf("%s", input);

    c = strlen(input);
    strcpy(act, "SHIFT->");
    printf("stack \t input \t action");
    for(k = 0, i = 0; j < c; k++, i++, j++) {
        if(input[j] == 'i' && input[j + 1] == 'd') {
            stk[i] = input[j];
            stk[i + 1] = input[j + 1];
            stk[i + 2] = '\0';
            input[j] = ' ';
            input[j + 1] = ' ';
            printf("\n$%s\t%s$\t%sid", stk, input, act);
                check();
        }
        else {
            stk[i] = input[j];
            stk[i + 1] = '\0';
            input[j] = ' ';
            printf("\n$%s\t%s$\t%ssymbols", stk, input, act);
                check();
        }
    }
}


void check() {

    strcpy(ac, "REDUCE TO E");
    for(z = 0; z < c; z++) {
        if(stk[z] == 'i' && stk[z + 1] == 'd') {
            stk[z] = 'E';
            stk[z + 1] = '\0';
            printf("\n$%s\t%s$\t%s", stk, input, ac);
            j++;
        }
    }

    for(z = 0; z < c; z++) {
       if(stk[z] == 'E' && stk[z + 1] == '+' && stk[z+2] == 'E') {
           stk[z] = 'E';
           stk[z + 1] = '\0';
           stk[z + 2] = '\0';
           printf("\n$%s\t%s$\t%s", stk, input, ac);
           i = i - 2;
        }
    }

    for(z = 0; z < c; z++) {
        if(stk[z] == 'E' && stk[z + 1] == '*' && stk[z + 2] == 'E') {
            stk[z] = 'E';
            stk[z + 1] = '\0';
            stk[z + 1] = '\0';
            printf("\n$%s\t%s$\t%s", stk, input, ac);
            i = i - 2;
         }
    }

    for(z = 0; z < c; z++) {
        if(stk[z] == '(' && stk[z + 1] == 'E' && stk[z + 2] == ')') {
            stk[z] = 'E';
            stk[z + 1] = '\0';
            stk[z + 1] = '\0';
            printf("\n$%s\t%s$\t%s", stk, input, ac);
            i = i - 2;
        }
    }
}
