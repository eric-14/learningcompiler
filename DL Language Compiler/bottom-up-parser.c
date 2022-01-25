%{
    #include "direcog__defs.h"//defines any function 
    // prototypes required and can contain #include derictives for other (system) header files
%}

%token CONSTANT IDENTIFIER LESYM EQSYM GESYM NESYM ELSESYM IFSYM

%token INTSYM PRINTSYM READSYM RETURNSYM WHILESYM


%union {
    int sval;
    astptr psval;
    char *strval;
}
//TERMINAL SYMBOLS HAVE TO BE DECLARED (WITH THEIR TYPE) USING %TOKEN AND non-terminals
// are given a type using the %type declaration
%token <sval> CONSTANT 
%token <sval> IDENTITIER 
%token <sval> ELSESYM 
%token <sval> IFSYM 
%token <sval> LESYM

%type <psval> program 
%type <psval> declarations 
%type <psval> declaration
%type <sval> relop 
%type <strval> idntifier 
%type <sval> constant



%%

program:
    block
        { syntrace ("program - without declararions"); }
    | declarations block 
        { syntrace("program - with declararions");}

functiondeclaration:
    IDENTIFIER '(' ')' ';' FUNCTIONBODY
                    { syntrace("functiondeclaration - no args"); } 
    
    | IDENTIFIER '(' arglist ')' ';' functionbody
                        {syntrace("functiondeclaration - with args");}

statementlist:
    statement { syntrace("statementlist");
        $$ = newnode(N_SLIST, 0,$1, NULL,NULL);}
    | statement ';' statementlist {
        syntrace("statementlist");
        $$ = newnode(N_SLIST, 0, $1, $3,NULL;
    }
    //error recovery 
    | error ';' { $$ = NULL;}
    | error '}' { $$ = NULL;}
vardeflist:
    vardec { syntrace("vardeflist"); $$=NULL;}
    | vardec ',' vardeflist { syntace("vardeflist"); $$=NULL;}

vardec:
    idenitifier { syntrace("vardec"); insertid($1, S_INT,1); $$=NULL; }
    | identifier '[' constant ']' {
        syntrace("vardec");
        insertid($1,S_ARRAY,$3);
        $$=NULL;
    }

ifstatement:
    IFSYM '(' bexpression ')' block ELSESYM block 
            { syntrace("ifelsestatement");
            $$ = newnode(N_IF,0 , $3, $5,NULL);}
    | IFSYM '(' bexpression ')' block 
            { syntrace("ifstatement");
             $$  = newnode(N_IF, 0, $3, $5);
            }

expression:// converting the expression to its tree node
    expression addingop term { syntrace("expression");
            $$ = newnode($2, 0, $1,$3,NULL);
    } 
    | term { syntrace("expression - just term");
        if ($1 == N_MINUS)
            $$ = newnode(N_MINUS< 0, $2,NULL,NULL);
    }
    | addingop term { syntrace("expression - unary op");}              

%%

void syntrace(char *s){
    if(TRACE){
        fprintf(stdout,"%s\n",s);
    }
}
void yyerror(char *s){
    printf("%s on the line %d\n",s,yylineno);
}
int main ( int argc, char *argv[])
{
    if(yyparse==0){syntrace("Recognizer Succeeds");}
    return 0;
}
