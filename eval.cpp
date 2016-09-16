//
// int eval( char * s );
//
// evaluate fully parenthesized in-order expressions for + and - operands
// such as ((19 - (21 + 3)) + ((1+ 3)+(2+31))
//

#include <cassert>
#include <stdio.h>

int eval_paren(char * & s);
int eval_num(char * & s);
int eval(char * s);
void skip_spc(char * & s);

void skip_spc(char * & s)
{
    while (*s == ' ') s++;
}

int eval_num(char * & s)
{
    skip_spc( s );
    if (*s == '(') {
        ++s;
        return eval_paren( s );
    }
    int v = 0;
    while (*s >= '0' && *s <= '9') {
        v = 10 * v + *s - '0';
        s++;
    }
    return v;
}

int eval_paren(char * & s)
{
    int l = eval_num( s );

    skip_spc( s );
    char op = *s++;
    assert( op == '+' || op == '-' );
    
    int r = eval_num( s );

    skip_spc( s );
    assert( *s == ')' );
    ++s;

    return op == '+' ? l + r : l - r;
}
        
int eval(char * s)
{
    skip_spc( s );
    assert(*s == '(');
    ++s;
    return eval_paren(s);
}

int main(int argc, char ** argv)
{
    if (argc > 1) {
        int n = eval(argv[1]);
        printf("%s => %d\n", argv[1], n);
    }
    return 0;
}
