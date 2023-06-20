#include <cstdio>
#include <cstring>
#include "libr.h"

using namespace std;
const char *BOOK_FORMAT_IN = \
"{\n\t\"Author\": \"%[^\"]\",\n\t\"Name\": \"%[^\"]\",\n\t\"Year\": %d,\n\t\"Price\": %f,\n\t\"Category\": %d\n}\n";
const char *BOOK_FORMAT_OUT = \
"{\n\t\"Author\": \"%s\",\n\t\"Name\": \"%s\",\n\t\"Year\": %d,\n\t\"Price\": %f,\n\t\"Category\": %d\n}\n";


int load_data(FILE *fp, CARD_INDEX *pCard)
{
    size_t pos = 0;
    int c = fgetc(fp);
    if (c == EOF) {
        puts("File empty, nothing to load");
        return 0;
    } else {
        ungetc(c, fp);
    }
    while(!feof(fp)) {
        pCard->pB[pos] = new struct BOOK;
        fscanf(fp, BOOK_FORMAT_IN, pCard->pB[pos]->author, pCard->pB[pos]->name, &pCard->pB[pos]->year, &pCard->pB[pos]->price, &pCard->pB[pos]->category);
        pos++;
    }
    pCard->count = pos;
    fclose(fp);
    return 1;
}

int write_data (FILE *fp, CARD_INDEX *pCard)
{
    printf("Number of books: %lld\n", pCard->count);
    for (size_t pos = 0; pos < pCard->count; pos++) {
        fprintf(fp, BOOK_FORMAT_OUT, pCard->pB[pos]->author, pCard->pB[pos]->name, pCard->pB[pos]->year, pCard->pB[pos]->price, pCard->pB[pos]->category);
    }
    fclose(fp);
    return 1;
}

pBook *changeIndexSize(pBook *arr_old, size_t size_old, size_t size_new)
{
    pBook *arr_new = new pBook[size_new];           
    for (size_t c = 0; c < size_old; c++) {         
        arr_new[c] = arr_old[c];
    };
    delete(arr_old);                                
    return arr_new;
}

void menuPrint(void)
{
printf( "Menu:\n"
        "1 - Add new book\n" 
        "2 - View books\n"
        "3 - Delete book\n"
        "4 - Sort by author\n"
        "5 - Sort by name\n"
        "6 - Sort by year\n"
        "7 - Sort by price\n"
        "8 - Sort by category\n"
        "9 - Save and exit\n\n" );
}

int addBook(CARD_INDEX *pCard)
{
    if(pCard->count >= pCard->cap){
        size_t size_new = (pCard->cap + 10);
        printf("New library size: %lld\n", size_new);
        pCard->pB = changeIndexSize(pCard->pB, pCard->cap, size_new);
        pCard->cap = size_new;
    }

    size_t pos = pCard->count;
    pCard->pB[pos] = new struct BOOK;
    fflush(stdin);
    printf("Author:");
    fgets(pCard->pB[pos]->author, SIZE_AUTHOR, stdin);
    strtok(pCard->pB[pos]->author, "\n");
    printf("Book name:");
    fgets(pCard->pB[pos]->name, SIZE_NAME, stdin);
    strtok(pCard->pB[pos]->name, "\n");
    printf("Year:");
    fscanf(stdin, "%hd", &pCard->pB[pos]->year);
    fflush(stdin);
    printf("Price:");
    fscanf(stdin, "%f", &pCard->pB[pos]->price);
    fflush(stdin);
    printf("Choose category:\n"
           "1-Prose\n"
           "2-Poetry\n"
           "3-Science\n");   
    fscanf(stdin, "%d", (int*) &pCard->pB[pos]->category);
    fflush(stdin);
    puts("Book added");
    puts("++++++++++");
    pCard->count = pos + 1;
    return 1;
}

void clear(void) 
{    
    while ( getchar() != '\n' );
}

int viewBook(CARD_INDEX *pCard)
{
    printf("\x1B[2J\x1B[H");
    int id = 1;
    printf ("%-5s%-30s%-30s%-10s%-10s%-10s\n", "ID", "Author", "Name", "Year", "Price", "Category");
    for (size_t c = 0; c < pCard->count; c++) {
        printf("%-5d%-30s%-30s%-10d%-10.2f%d\n", id++, pCard->pB[c]->author, pCard->pB[c]->name, pCard->pB[c]->year, pCard->pB[c]->price, pCard->pB[c]->category);
    }
    puts("");
    return 1;
}

int deleteBook(CARD_INDEX *pCard)
{
    int pos = 0;
    int count = pCard->count; 
    viewBook(pCard);
    puts("Choose ID to delete a book");
    fflush(stdin);
    pos = getchar() - 48;

    printf("Deleting book ID:%d\n", pos);
    
    if (pos <= 0 || pos > count) {
        puts("Wrong ID\n");
        return 0;
    }
    pos--;                               //deincrement "pos" because ID starts from 1
    delete(pCard->pB[pos]);
    count--;
    while (pos < count) {
        pCard->pB[pos] = pCard->pB[pos+1];
        pos++;
    }
    pCard->count--;
    printf("%s\n\n", "Book deleted");
    return 1;
}

void swapBook(pBook *x, pBook *y)
{
    pBook temp = *x;
    *x = *y;
    *y = temp;
}

void sortBook (CARD_INDEX *pCard, size_t size, int (*comp) (pBook, pBook))
{
    for (size_t j = 0; j < size; j++) {
        for (size_t i = 0; i < size - j - 1 ; i++) {
            if ((comp(pCard->pB[i], pCard->pB[i+1])) > 0)
                swapBook(&pCard->pB[i], &pCard->pB[i+1]);
        }
    }
}

int compAuthor(pBook x, pBook y)
{
    return strcasecmp(x->author, y->author);
}

int compName(pBook x, pBook y)
{
    return strcasecmp(x->name, y->name);
}

int compYear(pBook x, pBook y)
{
    return x->year - y->year;
}

int compPrice(pBook x, pBook y)
{
    return (int) x->price - y->price;
}

int compCat(pBook x, pBook y)
{
    return (eCategory) x->category - y->category;
}
