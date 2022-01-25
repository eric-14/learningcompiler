// astdata2 -- used to indicate whether a variable 
//has been declared locally or globally

typedef struct tnode *astptr;

typedef struct tnode {
    int asttype;
    int astdata1, astdata2;
    astptr p1,p2,p3;
} astnode;


void program(){
    syntrace("<program>");
    if (token== opencurlsym) block();
    else{
        declarations();
        block();
    }
}

void declarations(){
    syntrace("<declarations");
    declaration();

    while(token != opencurlsym)
        declaration();
}

void vardec(){
    syntrace("<vardec>");
    if(token != identifiersym)
        error("identifier expected in vardec\n");
    else{
        token = lex();
        if (token != constantsym){
            error("need array size\n");
        }else{
            token=lex();
            if ( token != closesuaresym){
                error("need close square bracket in array declaration\n");
            }else{
                token = lex();
            }
        }
    }

}
void statement(){
    syntrace("<statement>");
    switch (token)
    {
    case identifiersym:
        assignment();
        break;
    case ifsym:
        ifstatement();
        break;
    case whilesym:
        whilestatement();
        break;
     case opencurlsym:
        block();
        break;
     case printsym:
        printstatement();
        break;
     case readsym:
        readstatement();
        break;
     case returnsym:
        returnstatement();
        break;
    default:
        break;
    }
}

astptr expression(){
    astrptr pfirst;
    astrptr term2;
    int startingtoken, nodetype;

    syntrace("<expression>");

    startingtoken=plussym

    if((token==plussym) || (token==minussym)){
        startingtoken=token;
        token = lex();
    }
    pfirst=term();
    if (startingtoken==minussym){
        pfirst=newnode(N_UMINUS,0,pfirst,NULL,NULL);
    }
    term();

    while((token==plussym) || (token == minussym)){
        if(token==plussym) nodetype=N_PLUS; else nodetype = N_MINUS
        token=lex();
        term2=term();
        pfirst=newnode(nodetype,0,pfirst,term2, NULL);
    }
    return pfirst;
}

astptr whilestatement(){
    astrptr pbexp=NULL;
    astrptr pwhile=NULL;

    syntrace("whilestatement");

    if(token != whilesym) error("while expected\n");
    else{
        token=lex();
        if(token != openbracketsym) error("open bracket after while expected\n");
        else{
            token=lex();
            pbexp=bexpression();//boolean expression
            if(token != closebracketsym)
                error("close bracket in while expected\n");
            else{
                token= lex();
                pwhile = newnode(N_WHILE, 0, pbexp, block(),NULL);
            }
        }
    }
    return pwhile;
}


// generating a human-readable tree
/*
case N_IF:
    printf("N_IF  - if, conditiion:\n");
    printtree(xx->p1, depth+1);
    tabout(depth);
    printf("N_IF - if, thenpart:\n");
    printtree(xx->p2,depth+1);
    tabout(depth);
    printf("N_IF - if, elsepart:\n");
    printtree(xx->p3,depth+1);
    break;
*/