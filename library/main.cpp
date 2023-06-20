#include <cstdio>
#include <cstdlib>
#include "libr.h"

using namespace std;

int main()
{	
	struct CARD_INDEX c_index;
	c_index.pB = new pBook[CAP];
	c_index.count = 0;
	c_index.cap = CAP;
    
	FILE *libfile = fopen("lib.txt", "r");
	if(!libfile) {
		puts("Cant open file");
		return 1;
	}
	load_data(libfile, &c_index);
	
	while (true) {
		menuPrint();
		fflush(stdin);
		switch (getchar()) {
		// Описания "магических" чисeл в функции menuPrint
		case '1':
			addBook(&c_index);
			break;
		case '2':
			viewBook(&c_index);
			break;
		case '3':
			deleteBook(&c_index);
			break;
		case '4':
			sortBook(&c_index, c_index.count, compAuthor);
			break;
		case '5':
			sortBook(&c_index, c_index.count, compName);
			break;
		case '6':
			sortBook(&c_index, c_index.count, compYear);
			break;
		case '7':
			sortBook(&c_index, c_index.count, compPrice);
			break;
		case '8':
			sortBook(&c_index, c_index.count, compCat);
			break;
		case '9':
			libfile = fopen("lib.txt", "w");
			write_data(libfile, &c_index);
			return 0;
		default:
			break;
		}
	}

}