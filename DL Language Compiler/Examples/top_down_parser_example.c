#include <stdio.h>
#include <stdlib.h>

int ch;
/*
    LANGUAGE

    S -> Az/z
    A -> xA/B
    B -> y


*/

void error(char *msg){
    printf("Error - found character %c - %s\n",ch,msg);
    exit(1);
}

void b(){
    if(ch == 'y') ch = getchar();
    else error ("y expected");

}

void a(){
    if(ch == 'x') {
        ch = getchar();
        a();
    }else b();
}
void s(){
    if (ch == 'z') ch = getchar();
    else{
        a();
        if (ch != 'z') error("z expected");
        else ch = getchar();
    }
    printf("Success!\n");
}

int main(int argc, char *argv[]){
    ch = getchar();
    s();
    return 0;
}
