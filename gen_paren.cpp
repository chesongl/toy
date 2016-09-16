//
// generate balanced parenthesis for given n
//
// e.g.
// gen_paren 3
// ((()))
// (()())
// (())()
// ()(())
// ()()()
// 
#include <stdio.h>
#include <stdlib.h>

void gen_paren(char * s, char * p, int n, int open, int close)
{
    if (open + close == 2 * n) {
        puts(s);
        return;
    }
    if (open < n) {
        *p = '(';
        gen_paren( s, p + 1, n, open + 1, close );
    }
    if (close < open) {
        *p = ')';
        gen_paren( s, p + 1, n, open, close + 1 );
    }
}

void gen_paren(int n)
{
    char * s = new char[2 * n + 1];
    *(s + 2 * n) = '\0';
    gen_paren(s, s, n, 0, 0);
    delete [] s;
}

int main(int argc, char ** argv)
{
    if (argc > 1) {
        gen_paren( atoi( argv[1] ) );
    }
    return 0;
}
