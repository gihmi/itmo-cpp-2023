// Задание: реализуйте функции стандартной библиотеки


#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "myfunc.h"

//global variables

/*****************************************************/

char case_up(char c)
{
/*    if (c >= 'a' && c <= 'z')
        return c - ('a' - 'A');
    else
        return c;
*/
       return  c >= 'a' && c <= 'z' ? c - ('a' - 'A') : c;
}

/*****************************************************/

int symbol_count(const char *str, char symb)
{
    int cnt; //var to count symbols
    for (cnt = 0; *str != '\0'; str++) {
        if (*str == symb)
            cnt++;
    }
    return cnt;
}

/*****************************************************/


int get_and_zero(int *var)
{
    int temp = *var;
    *var = 0;
    return temp;
}

/*****************************************************/

int getline_m(char *s, int lim)
{
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
        s[i] = c;
    }
    if (c == '\n') {
        s[i++] = c;
    }
    s[i] = '\0';
    return i;
}

/*****************************************************/

void reverse(char *string)
{
    int length = 0;
    while (string[length] != '\0') { // find string length
        length++;
    }
    length--; //adjust length for indexing

    int fb = 0; //count from beginning
    int temp = 0;
    while (length != fb) {
        temp = string[length];
        string[length] = string[fb];
        string[fb] = temp;
        length--;
        fb++;
    }
}

/*****************************************************/

int htoi(const char *s) {
    int i, n;
    i = n = 0;
    while (s[i] == '0' || s[i] == 'x' || s[i] == 'X') //check if string started with "0x" or "0X"
        i++;
    while (s[i]) {
        if (s[i] >= '0' && s[i] <= '9')
            n = 16 * n + (s[i] - '0');
        else if (s[i] >= 'a' && s[i] <= 'f')
            n = 16 * n + (s[i] - 'a');
        else if (s[i] >= 'A' && s[i] <= 'F')
            n = 16 * n + (s[i] - 'A');
        else
            return -1;
        i++;
    }
    return n;
}

/*****************************************************/

void squeeze(char *string, int smbl) {
    int ind1, ind2;
    for (ind1 = ind2 = 0; string[ind1] != '\0'; ind1++) {
        if (string[ind1] != smbl)
            string[ind2++] = string[ind1];
    }
    string[ind2] = '\0';
}

/*****************************************************/

void squeeze_str(char *string, char *span) { //delete  and squeeze
    int ind1, ind2, flag;
    flag = 0;
    for (ind1 = ind2 = 0; string[ind1] != '\0'; ind1++) {
        for (int i = 0; span[i]; i++) {
            if (string[ind1] == span[i])
                flag = 1;
        };
        if (!flag)
            string[ind2++] = string[ind1];
        flag = 0;
    }
    string[ind2] = '\0';
}

unsigned getbits (unsigned x, int p, int n) {
    return (x >> (p+1-n)) & ~(~0 << n);
}

/*****************************************************/

unsigned setbits (unsigned x, int p, int n, unsigned y) {
    p -= n; //calculate position
    n = pow (2,n)  - 1; //calculate mask
    y &= n;
    y <<= p; //shift to position
    return (x | y); //swap bits
}

/*****************************************************/

int binsearch(int num, int size)
{
	int low = 0;
	int high = size - 1;
	int mid;
	/*
	while (low != high) {
		mid = ceil((low + high) / 2);
		if (num < mid)
			high = mid - 1;
		else
			low = mid;
	}
	if (num == high)
		return num;
	return -1;
	*/
	while (low <= high) {
		mid = (low + high) / 2;
		if (num < mid)
			high = mid - 1;
		else
			low = mid + 1;
	}
	if (num == high)
		return num;
	else 
		return -1;
}

/*****************************************************/

void escape(const char *src, char *dest) // replace esc seq characters with real esc seq
{
    while (*src) {
        if (*src != '\\') {
            *dest++ = *src++;
        }
        else
            switch (*(src+1))
            {
            case 't':
                *dest = '\t';
                src += 2, dest++;
                break;
            case 'n':
                *dest = '\n';
                src += 2, dest++;
                break;
            default:
                *dest++ = *src++;
                break;
            }
    }
 *dest = '\0';
}

/*****************************************************/

int itoa (int n, char *str, int wd) /* convert n to characters in str */
{ 
    int i, sign, fc;
    if ((sign = n) < 0)
        n  = -n;
    i = 0;
    fc = 0; // variabe to count field width
    do {
        str[i++] = n %10 + '0';
        fc++;
    } while ((n /= 10) > 0);
    if (sign < 0) {
        str[i++] = '-';
        fc++;
    }
    wd -= fc; // calc width to fill with blanks
    while (wd > 0) {
        str[i++] = '*';
        wd--;
    }
    str[i] = '\0';
    reverse(str);
    return 0;
}

/*****************************************************/

int word_count(char *str) //count words in parameter,
{
    int IN = 0;
    int wrd = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 33 && str[i] <= 126) {
            if(IN == 0) {
                IN = 1;
                wrd++;
            }
        }
        if (str[i] == ' ')
            IN = 0;

    }
    return wrd;
}

/*****************************************************/

char *substring(char *str, char *subs)
{
    if (strlen(subs) > strlen(str))
        return NULL;
    for(; *str != 0; str += 1) {
        if (*str != *subs)
            continue;
        for (int i = 0;;i++) {
            if (subs[i] == 0)
                return str;
            if (str[i] != subs[i])
                break;
        }
    }
    return NULL;
}

/*****************************************************/

char* swap(char* input, int size) {     //swap substring
    int temp = 0;
    int first = 0;
    int last = size - 1;
    while (first < last) {
        temp = input[first];
        input[first] = input[last];
        input[last] = temp;
        first++;
        last--;
    }
    return *input;
}


