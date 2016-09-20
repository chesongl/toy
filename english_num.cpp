#include <list>
#include <iostream>
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

void engnum_99(int64_t n, num_list_t & num_list)
{
    if (n < 20) {
        num_list.push_back(ones[n]);
    } else {
	num_list.push_back(ten_scale[n / 10]);
	if (n % 10 > 0) {
	    num_list.push_back(dash);
            num_list.push_back(ones[n % 10]);
	}
    }
}

void engnum_999(int64_t n, num_list_t & num_list)
{
    if (n > 100) {
        num_list.push_back(ones[n / 100]);
	num_list.push_back(space);
	num_list.push_back(hundred);
	if (n % 100 > 0) {
	    num_list.push_back(space);
	    num_list.push_back(and);
	    num_list.push_back(space);
	}
    }
    engnum_99(n % 100, num_list);
}

void engnum(int64_t n, num_list_t & num_list)
{
    if (n == 0) {
	num_list.push_back(ones[0]);
	return;
    }
    
    int bias_one = 0;
    if (n < 0) {
	num_list.push_back(negative);
	num_list.push_back(space);
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
		num_list.push_back(space);
	    }
	    engnum_999(hundreds, num_list);
	    num_list.push_back(space);
	    num_list.push_back(thousand_scale[i]);
	    if (n > 0) {
		num_list.push_back(comma);
	    }
	    first = false;
	}
    }
    if (n > 0) {
	if (!first) {
	    num_list.push_back(space);
	}
	engnum_999(n + bias_one, num_list);
    }
}

string engnum(int64_t n)
{
    string numstr;
    num_list_t nums;
    engnum(n, nums);
    for_each(nums.begin(),
             nums.end(),
             [&numstr] (const char * s) {
                 numstr += s;
             });
    return numstr;
}

void print_engnum(int64_t n)
{
    cout << n << "\n\"" << engnum(n).c_str() << "\"" << endl;
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
