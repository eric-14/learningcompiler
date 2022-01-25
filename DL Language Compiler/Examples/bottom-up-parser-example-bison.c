%{
    #include <stdio.h>

    void yyerror(char*);
    int yylex(void);
%}

%%

S:
    A   'z' { printf("s->Az, done\n");}
    |       'z' { printf("S->z, done\n");}

A:
    'x' A { printf("A->xA\n"); }
    |  B {printf("A->B\n"); }

B:
    'y' { printf("B ->y\n");}

%%
void yyerror(char *s);
{
    printf("***%%s\n",s);
}

int yylex(){
    int ch;
    ch=getchar();
    while (ch == "\n") ch=getchar();
    return ch;
}

int main(){
    if (yyparse()==0) printf("parsing successful\n");
    else printf("parsing failure\n");

    return 0;
}