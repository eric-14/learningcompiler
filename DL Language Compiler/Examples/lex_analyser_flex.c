//needs code to link to the syntax analyser and defining token names
// comment() -- is not coded to read the end of the comment


//definitions is constructed to simply improve the readability of the code
%{
    int lexnumval;
    char lexident[MAXIDLEN+1]


}%

%%
letter  [a-z]
digit   [0-9]
letter_or_digit [a-z0-9]
white_space [ /t/n]
other   .

%%
// order of the rules has to be checked 
//reserve words have to be matched 
//before the identifiers to prevent input such as else being recognised as an identifier
// first rule that is matched takes precedence 



"=="    return EQSYM;
"<="    return LESYM;
">="    return GESYM;
"!="    return NESYM;

else    return ELSESYM;
if      return IFSYM;
int     return INTSYM;
print   return PRINTSYM;
read    return READSYM;
return  return RETURNSYM;
while   return WHILESYM;

{letter}{letter_or_digit}*  return IDENTIFIER;

{digit}+        {   lexnumval = atoi(yytext);
                    return CONSTANT;
                }

"/*"            {comment();}
{white_space}+  ;

{other}     return yytext[0];
