//DIRECT METHOD OF LEXICAL ANALYSIS 


#define MAXIDLEN 30

typedef enum{
    elsesym,ifsym,intsym,printsym,readsym,returnsym,
    whilesym,semicolonsym,commasym,opencurlsym,closecurlsym,
    opensquaresym,closesquaresym, openbracketsym,closebarcetsym,
    dividesym,multiplysym,plusym,minussym,assignsym,
    eqsym,nesym,ltsym,lesym,gtsym,gesym,eofsym,
    constantsym, identifiersym,errorsym
} lextokens;

lextokens lex();

char identifier[MAXIDLEN+1];
char ch;

//whitespace

while( white(ch)) ch=getchar();

//Single character tokens 

switch(ch){
        case ";": lextoken = semicolonsym; ch =getchar(); break;
        case ",": lextoken = commasym; ch =getchar(); break;
        case "+": lextoken = plussym; ch =getchar(); break;
        case "-": lextoken = minussym; ch =getchar(); break;
        case "/": lextoken = dividesym; ch =getchar(); break;
        case "*": lextoken = multiplysym; ch =getchar(); break;
        case "(": lextoken = openbracketsym; ch =getchar(); break;
        case ")": lextoken = closebracketsym; ch =getchar(); break;
        case "{": lextoken = opencurlsym; ch =getchar(); break;
        case "}": lextoken = closecurlsym; ch =getchar(); break;
        case "[": lextoken = opensquaresym; ch =getchar(); break;
        case "]": lextoken = closesquaresym; ch =getchar(); break;
        case EOF: lextoken = eofsym; break;
        case "<":
          ch = getchar();
          if (ch == "="){
              lextoken = lesym;
              ch = getchar();
          }else{
              lextoken = ltsym;
          }break;

        case ">": 
            ch =getchar(); 
            if( ch=="="){
                lextoken = gesym;
                ch = getchar();
            }else{
                lextoken = gtsym;
            }
            break;
        case "=":
            ch = getchar();
            if(ch == "="){
                lextoken = eqsym;
                ch = getchar();
            }else{
                lextoken = assignsym;
               
            }break;
        case "!":
            ch = getchar();
            if (ch != "="){
                fprintf(stderr,"***Error - expected = after ! (%c)\n",ch)
                lextoken = errorsym;
            }else{
                lextoken = nesym;
                ch = getchar();
            }break;

        // Identifiers and reserved words

        case 'a':case 'b':case 'c':case 'd':case 'e':case 'f':case 'h':
        case 'i':case 'j':case 'k':case 'l':case 'm':case 'n':
        case 'o':case 'p':case 'q':case 'r':case 's':case 't':case 'u':
        case 'v':case 'w':case 'x':case 'y':case 'z':

        {
            int i = 0;
            // When you hit a white space stop
            while(islower(ch) || isdigit(ch)){
                if(i < MAXIDLEN) identifier[i++] = ch;
                ch = getchar();
            }
            identifier[i] = '/0';

            //more efficient algorithm for identifiers and reserved words

            if (strcmp(identifier,"else")==0) lextoken = elsesym;
            else if (strcmp(identifier,"if")==0) lextoken = ifsym;
            else if (strcmp(identifier,"int")==0) lextoken = intsym;
            else if (strcmp(identifier,"print")==0) lextoken = printsym;
            else if (strcmp(identifier,"read")==0) lextoken = readsym;
            else if (strcmp(identifier,"return")==0) lextoken = returnsym;
            else if (strcmp(identifier,"while")==0) lextoken = whilesym;
            else lextoken = identifiersym;
            break;

        }

        //integer constants
        case "0":case "1":case "2":case "3":case "4":case "5":case "6":case "7":
        case "8":case "9":
        {
            ival = 0;
            while(isdigit(ch)) {
                ival = ival*10 + ch - '0';
                ch = getchar();
            }
            lextoken = constantsym;
            break;
        }
        case "0":case "1":case "2":case "3":case "4":case "5":case "6":case "7":
        case "8":case "9":
            {
                int overflow = 0;
                ival = 0;
                while(isdigit(ch)){
                    if(ival > INT_MAX/10)  overflow = 1;
                    else if (ival*10 > (INT_MAX - ch + '0')) overflow = 1;
                    else ival = ival*10 + ch - '0';
                    ch = getchar();
                }
                if (overflow){
                    lextoken = constantsym;
                    ival = INT_MAX;
                    fprintf(stderr,"integer constant overflow\n");
                }
                else lextoken = constantsym;
                break;


            }
        
        //comments
        // this lex does dont handle nested comments i.e /* Hi /* hello */ */
        
        case '/':
            ch = getchar();
            if (ch == "*"){
                incomment = 1;
                ch = getchar();
                while (incomment){
                    if (ch == EOF){
                       fprintf(stderr,"warning - end of file in comment\n ");
                       incomment = 0;
                    }else if (ch == '*'){
                        ch = getchar();
                        if (ch == '/'){
                            ch = getchar();
                            incomment = 0;
                        }
                    }
                    else ch = getchar();
                    
                }
                lextoken =  lex();

                
            }
            else lextoken = dividesym;
            break;

            //This code does not and should not handle nested comments, so that the lexical
            //analyser will deal with input of the form 

            //By treating the input as a a comment terminated by the first * / and then returning a
            //multiplysym and then a dividesym 
        
        default:
            fprintf(stderr,"***Unexpected character %c\n",ch);
            lextoken = errorsym;
            break;
        


}







