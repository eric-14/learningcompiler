typedef enum {
        R_REG, R_GLOBAL, R_LOCAL, R_CONST, R_NONE
} regtags;// r5, vg5, v15, 5 , nothing returned

//structure returned by the cg function

typedef struct regstruct {
    regtags retype;

    int regvalue; //which register or integer value of constant

} a3token;

a3token cg (astptr p)
{
    int nodetype;
    a3token noresult = {R_NONE - 1};
    astptr left,right;

    if (p == NULL) return noresult;

    nodetype = p->astype;

    switch (nodetype){
        case N_PLUS:
        case N_MINUS:
        case N_MUL:
        case N_DIV:
            left= p->p1;
            right= p->p2;
            t=genreg(); // returns the identity (as an a3token)
            //of the next unused temporary register.
            //code is generated for the left and right subtrees of the node and the
            //arithmetic instruction for the node is output uisng the outop function

            t2=cg(left);
            t3=cg(right);

            opreg(t); printf("="); opreg(t2);

            return t;


    }
}