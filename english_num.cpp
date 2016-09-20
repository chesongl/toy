#include <list>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

const char * ones[] = {
    "zero",     "one",     "two",       "three",    "four",
    "five",     "six",     "seven",     "eight",    "nine",
    "ten",      "eleven",  "twelve",    "thirteen", "fourteen",
    "fifteen",  "sixteen", "seventeen", "eighteen", "nineteen" };

const char * ten_scale[] = {
    "N/A",    "N/A", // 0, 10
    "twenty", "thirty",
    "forty",  "fifty",
    "sixty",  "seventy",
    "eighty", "ninety" };

const char * thousand_scale[] = {
    "thousand",    "million",
    "billion",     "trillion",
    "quadrillion", "quintillion",
    /* "sextillion" */ };

const char * hundred  = "hundred";
const char * negative = "negative";
const char * comma    = ",";
const char * space    = " ";
const char * and      = "and";
const char * dash     = "-";

typedef list<const char*> num_list_t;

void engnum_99(int64_t n, stringstream & s)
{
    if (n < 20) {
	s << ones[n];
    } else {
	s << ten_scale[n / 10];
	if (n % 10 > 0) {
	    s << dash << ones[n % 10];
	}
    }
}

void engnum_999(int64_t n, stringstream & s)
{
    if (n >= 100) {
	s << ones[n / 100] << space << hundred;
	if (n % 100 > 0) {
	    s << space << and << space;
	}
    }
    if (n % 100 > 0) {
        engnum_99(n % 100, s);
    }    
}

void engnum(int64_t n, stringstream & s)
{
    if (n == 0) {
	s << ones[0];
	return;
    }
    
    int bias_one = 0;
    if (n < 0) {
	s << negative << space;
        //  INT64_MIN is not addressable by the positive number.
        if (n == INT64_MIN) {
            bias_one = 1;
            n = -(n + 1);
        } else {
            n = -n;
        }
    }

    bool first = true;
    for (int i = _countof(thousand_scale) - 1; i >= 0; --i) {
	int64_t scale = pow(1000, i + 1);
	int64_t hundreds = n / scale;
	n %= scale;
	if (hundreds > 0) {
	    if (!first) {
		s << space;
	    }
	    engnum_999(hundreds, s);
	    s << space
	      << thousand_scale[i];	    
	    if (n > 0) {
		s << comma;
	    }
	    first = false;
	}
    }
    if (n > 0) {
	if (!first) {
	    s << space;
	}
	engnum_999(n + bias_one, s);
    }
}

string engnum(int64_t n)
{
    stringstream ss;
    engnum(n, ss);
    return ss.str();
}

void print_engnum(int64_t n)
{
    cout << n << " \"" << engnum(n).c_str() << "\"" << endl;
}

int main(int argc, char** argv)
{
    cout.imbue(locale("en-US"));
    if (argc > 1) {
	int64_t lower = atoll(argv[1]);
	int count = 1;
	if (argc > 2) {
	    count = atoi(argv[2]);
	}
	for (int64_t i = 0; i < count; ++i) {
	    print_engnum(lower + i);
	}
    } else {
        print_engnum(INT64_MAX);
        print_engnum(INT64_MIN);
        print_engnum(UINT64_MAX);
        print_engnum(INT32_MAX);
        print_engnum(INT32_MIN);
        print_engnum(UINT32_MAX);
        print_engnum(INT16_MAX);
        print_engnum(INT16_MIN);
        print_engnum(UINT16_MAX);
    }
}
