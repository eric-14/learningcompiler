#include <string>
#include <vector>

class registers
{
private:
    int no_treg = 20;
   typedef struct temp_reg{
        std::string name;
        int value;
    }treg;
    typedef struct used_cache{
        std::vector<treg> ucache;
    }ucache;

    typedef struct free_cache{
        std::vector<treg> fcache;
    }fcache;


public:
    registers(int no_treg);
    int usize(){
        ucache->ucache.length();
    }
    int fsize(){
        fcache->fcache.length();
    }
    treg unusede_reg(){
        fcache->fcache.pop_back();
    }
    ~registers();
};

registers::registers(int no_treg)
{
    int i = 0;
    while(i =< treg){
        //trying to add a variable string
        treg reg = {`reg${i}`,0};
        fcache.fcache.push(reg);
        i++;
    }
}

registers::~registers()
{
}

//intializing all my free registers

registers t_regs;

typedef enum{
    R_REG,
    R_GLOBAL, 
    R_LOCAL, 
    R_CONTS, 
    R_NONE
}regtags;
/*Structure returned by the cg function*/
typedef struct regstruct{
    regtags regtype; 
    int regvalue;
}a3token;


regtags genreg(){
    //start with a default  free registers
    //triying to get an empty register
    try
    {
        return t_regs.un_used_reg()
    }
    /*
    Throw an error when there is not register 
    But first try to handle the error by try to free used registers

    */ 
    
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
     
}

a3token cg(astptr p){
    int nodetype;
    a3token noresult = {R_NONE , -1};
    astptr left, right;

    if(p==NULL) return noresult; 

    nodetype = p->asttype;

    switch(nodetype){
        case N_PLUS:

        break;

        case N_MINUS:

        case N_MUL:

        case N_DIV:

        case N_FNCALL:
            t=cg(p->p1);  //deal with arguments. p1 is the list of arguments 
            /*
            astdat1 field is the index of the symb; table entry defining this function.
            
            */
            printf("call %s\n",symtable[p->astdata1].symname);

            t=genreg();     //may need a new register for the result
            opreg(t); printtf("="); opereg(returnreg); printf("\n");
            return t;

        case N_IF:
            l1 = genlab();
            cnode = p->p1;

            t2 = cg(cnode->p1);
            t3 =cg(cnode->p2);

            printf("if ("); opreg(t2); invcondtion(cnode); opreg(t3);

            printf(") goto 1 %d\n",11); //jump to the else part or end of statement 

            t=cg(p->p2);
            if(p->p3 != NULL){
                l2 = genlab();
                printf("goto 1%d\n",11);
                t=cg(p->p3);
                printf("i%d:\n",12);
            }
            else
                printf("1%d:\n",11);
            
            return noresult;

        case N_WHILE:
        //while statement is implememted the same as if statement 
        case N_SWITCH:
        //A simple approach is to regard the use of if....then..else if 
        /*
        For switch statements with many cases, this may not result in high performance code

        The range and number of case values are important in deciding on a more efficient implementation strategy. 
        1.jump table can be used
        2. Some sort of binary search algorithm 

        */





        default break;
    }
    left=p->p1;
    right=p->p2;

    //returns the identity of the next unused temporary register
    t=genreg();

    //FUnction to clear registers especially temp registers once they have been used 


    //i think this implementation is wrong since it will form a loop that ends
    //at the end of the program with the only values in the registers the values of the last two variables.

    t2 = cg(left);
    t3= cg(right);

    //outputs an argument for the machine instructions
    //  either a temporary register,a register storing a variable or an integer constant
    //opreg function after getting the value of the nodes it decides whether to store the value in a temporary register, 
    //permanent register or return a constant value

    //returned three address coode
    opreg(t); printf("="); opreg(t2); outop(nodetype); opreg(t3);

    //outop funtion the arithmetic instruction for the node is output usin

    printf("\n");
    return t;
}


//