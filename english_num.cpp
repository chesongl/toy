#include <list>
#include <iostream>
#include <algorithm>

using namespace std;

const char * ones[] = {
    "zero", "one", "two", "three", "four",
    "five", "six", "seven", "eight", "nine",
    "ten", "eleven", "twelve", "thirteen",
    "fourteen", "fifteen", "sixteen", "seventeen",
    "eighteen", "nineteen" };

const char * ten_scale[] = {
    "twenty",
    "thirty",
    "forty",
    "fifty",
    "sixty",
    "seventy",
    "eighty",
    "ninety" };

const char * thousand_scale[] = {
    "thousand",
    "million",
    "billion",
    "trillion",
    "quadrillion",
    "quintillion",
    "sextillion",
};

const char * hundred = "hundred";
const char * negative = "negative";
const char * comma = ",";
const char * space = " ";
const char * and = "and";
const char * dash = "-";

typedef list<const char*> num_list_t;

void engnum_19(int64_t n, num_list_t & num_list)
{
    num_list.push_back(ones[n]);
}

void engnum_99(int64_t n, num_list_t & num_list)
{
    if (n / 10 == 0 || n / 10 == 1) {
	engnum_19(n % 20, num_list);
    } else {
	num_list.push_back(ten_scale[n / 10 - 2]);
	if (n % 10 > 0) {
	    num_list.push_back(dash);
	    engnum_19(n % 10, num_list);
	}
    }
}

void engnum_999(int64_t n, num_list_t & num_list)
{
    if (n < 100) {
	engnum_99(n, num_list);
    } else {
	engnum_19(n / 100, num_list);
	num_list.push_back(space);
	num_list.push_back(hundred);
	if (n % 100 > 0) {
	    num_list.push_back(space);
	    num_list.push_back(and);
	    num_list.push_back(space);
	    engnum_99(n % 100, num_list);
	}
    }
}

void engnum(int64_t n, num_list_t & num_list)
{
    if (n == 0) {
	num_list.push_back(ones[0]);
	return;
    }
    
    if (n < 0) {
	num_list.push_back(negative);
	num_list.push_back(space);
	n = -n;
    }

    bool first = true;
    for (int i = _countof(thousand_scale) - 1; i >= 0; --i) {
	int64_t scale = pow(1000, i + 1);
	int64_t part_1000 = n / scale;
	n %= scale;
	if (part_1000 > 0) {
	    if (!first) {
		num_list.push_back(space);
	    }
	    engnum_999( part_1000, num_list );
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
	engnum_999( n, num_list );
    }
}

int main(int argc, char** argv)
{
    if (argc > 1) {
	int64_t lower = atoll(argv[1]);
	int count = 1;
	if (argc > 2) {
	    count = atoi(argv[2]);
	}
	for (int64_t i = 0; i < count; ++i) {
	    int64_t n = lower + i;
	    num_list_t num_list;
	    engnum( n, num_list );	    
	    cout << n << "\t" << "\"";
	    for_each( num_list.begin(),
		      num_list.end(),
		      [] (const char * s) {
			  cout << s;
		      });
	    cout << "\"" << endl;
	}
    }
}
