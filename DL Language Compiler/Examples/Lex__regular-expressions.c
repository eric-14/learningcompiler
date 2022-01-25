//USING REGULAR EXPRESSIONS FOR SYNTAX ANALYSIS

//input to flex thus generating a C program in defualt 

typedef enum {
    t_constant = 1000, t_string_literal,t_right_assign,
    t_left_assign,t_add_assign, t_sub_assign,
    t_mul_assign, t_div_assign
}

letter [a-zA-Z]
digit [0-9]
letter_0r_digit [a-zA-Z0-9]
white_space [ /t/n]
other .

%% 
{white_space}+  ;
{letter}{letter_or_digit}*  return 1;
{digit}+    return 2;
{other} return 3;

%%

int main(){
    int lextoken;
    // while stops when yytext returns 0 to indicate end of file
    while ( lextoken = yylex())
        printf("%d - %s\n",lextoken, yytext);
        //flex has variable yytext that contains the string that matched the regular expression
}

// called when yykex encounters the end of file 
// return 0 indicates that yyle should continue and yyywrao will have opened a new file for processing
//This is a mechanism for allowing input from multiple files 
int yywrap(){
    return 1;
}