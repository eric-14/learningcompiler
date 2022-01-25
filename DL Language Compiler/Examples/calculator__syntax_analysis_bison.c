%{
#include <stdio.h>
#include <ctype.h>

void yyerror(char*);
int yylex(void);

int ival;
%}

%token CONSTANT 

%%
calculation:
    expr '\n' { printf("%d\n",$1); }

expr:
    term { $$ = $1; } // $$ ---> the symbol for the head of production
    | expr '+' term { $$ = $1 + $3; /*$$ = newnode(N_PLUS,0,$1,$3); INTEGER constant indicating the type of node, value of the node, left subtree, right subtree*/} //$1 --> expr $3---> term ---the third symbol of the grammar
    | expr '-' term { $$ = $1 - $3; /* $$ = newnode(N_MINUS, 0,$1,$3)*/}
    
term:
    factor { $$ = $1; }
    | term '*' factor {$$ = $1 * $3;} // $$ = newnode(N_MUL,0,$1,$3)
    | term '/' factor { $$ = $1 / $3;}// $$ = newnode(N_DIV, 0,$1,$3)

factor:
    CONSTANT { $$ = ival;} // $$ = newnode(N_INTEGER, ival, NULL, NULL)
    | '(' expr ')' { $$ = $2; }

%%

void yyerror(char *s){
    printf("***%s\n",s);
}

int yylex(){
    int ch;
    ch = getchar();
    while (ch==' ') ch = getchar();
    if (isdigit(ch)){
        ival =0;
        while(isdigit(ch)){
            ival = ival*10+(int) ch - (int) '0';
        }
        ungetc(ch,stdin);
        return CONSTANT;
    }
    else return ch;
}

int main(){
    return yyparse();
}