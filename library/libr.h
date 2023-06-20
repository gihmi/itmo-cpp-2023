#define SIZE_AUTHOR 35
#define SIZE_NAME 88
#define CAP 20

typedef struct BOOK *pBook;
enum eCategory {PROSE=1, POETRY, SCIENCE};
enum menu {add=1, view, del, sort};

struct CARD_INDEX {
    pBook *pB;
    size_t count;
    size_t cap;
};

struct BOOK {
    char author[SIZE_AUTHOR];
    char name[SIZE_NAME];
    unsigned short year;
    float price;
    eCategory category;
};

pBook *changeIndexSize(pBook *, size_t, size_t);
void menuPrint(void);
int addBook(CARD_INDEX *);
int viewBook(CARD_INDEX *);
void clear(void);
int load_data(FILE *, CARD_INDEX *);
int write_data(FILE *, CARD_INDEX *);
int deleteBook(CARD_INDEX *);
void swapBook(pBook *, pBook *);
void sortBook(CARD_INDEX *, size_t, int (*) (pBook, pBook));
int compAuthor(pBook, pBook);
int compName(pBook, pBook);
int compYear(pBook, pBook);
int compPrice(pBook, pBook);
int compCat(pBook, pBook);
