/*Задание 3:  Разработайте программу «Библиотека».
Создайте структуру «Книга» (название, автор, издательство, жанр).
Создайте массив из 10 книг.
Реализуйте для него следующие возможности:
- Редактировать книгу
- Печать всех книг
- Поиск книг по автору
- Поиск книги по названию
- Сортировка массива по названию книг */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>


#define MAXBOOKS 10
#define MAX_SIZE_CHAR_BOOK 40
#define EDIT '1'
#define PRINT '2'
#define SEARCH '3'
#define SORTN '4'
#define ESC '\x1b'

#define EDIT_TITLE '1'
#define EDIT_AUTHOR '2'
#define EDIT_GENRE '3'
#define EDIT_PUBLISHER '4'

#define ALL '0'
#define NAME '1'
#define AUTOR '2'
#define PUBLISHER '3'
#define GENRE '4'
#define ID '5'

#define CHANGE '1'

struct book
{
	char title[MAX_SIZE_CHAR_BOOK];
	char author[MAX_SIZE_CHAR_BOOK];
	char genre[MAX_SIZE_CHAR_BOOK];
	char publisher[MAX_SIZE_CHAR_BOOK];
	int number;
	bool isShowed;
};

char menu();
void menuShowing();
void changeBooks(struct book* library, int editedBook, int bookCount);
void printAllBook(struct book* library, int bookCount);
void bookSearch(struct book library[], int bookCount);
void sortArrayName(struct book library[], int bookCount);
void deleteChar(char keyWord[], int size);
void showEditMenu();
void bookFildEdit(char* bookFild, char fild);
int returnPosition(struct book library[], int bookCount, int positionBook);
int filtrByFild(struct book Library[], int bookInLibrary, int fildNumber);
void getNumber(int* userNumber);
char menuEditChoice();
char menuMethodOfEditChoise();
char* getFildName(int fildNumber);
void showMethodOfEditMenu();


int main()
{
	struct book library[MAXBOOKS] =
	{
		"The Hobbit", "J. R. R. Tolkien", "High fantasy", "George Allen & Unwin", 1, true,
		"The Great Gatsby", "F. Scott Fitzgerald", "Novel","Charles Scribner's Sons", 2, true,
		"The Catcher in the Rye", "J. D. Salinger", "Realistic fiction", "Little", 3, true,
		"The Fault in Our Stars", "John Green", "Young adult novel", "Dutton Books", 4, true,
		"1984", "George Orwell", "Dystopian", "Secker & Warburg", 5, true,
		"Diary of a Wimpy Kid", "Jeff Kinney", "Comedy", "Amulet Books", 6, true,
		"The Lord of the Rings", "J. R. R. Tolkien", "Adventure", "George Allen & Unwin", 7, true,
		"The Hunger Games", "Suzanne Collins", "Dystopian", "Scholastic", 8, true,
		"Anna Karenina", "Leo Tolstoy", "Realist novel", "The Russian Messenger", 9, true,
		"The End of Eternity", "Isaac Asimov", "Science fiction", "Doubleday", 10, true
	};
	int bookCount = 0;
	char choicingMenu = 0;

	while (true)
	{
		if (choicingMenu != 0)
		{
			choicingMenu = menu();
		}


		menuShowing();

		if (choicingMenu == 0)
		{
			choicingMenu = menu();
		}

		switch (choicingMenu)
		{
		case EDIT:
			returnPosition(library, MAX_SIZE_CHAR_BOOK, ALL);
			printAllBook(library, MAXBOOKS);
			int bookPositionInLibrary = returnPosition(library, MAX_SIZE_CHAR_BOOK, ID);
			changeBooks(library, MAXBOOKS, bookPositionInLibrary);
			break;
		case PRINT:
			printAllBook(library, MAXBOOKS);
			break;
		case SEARCH:
			bookSearch(library, bookCount);
			break;
		case SORTN:
			sortArrayName(library, bookCount);
			break;
		case ESC:
			return 0;
		}
	}
}

char menu()
{
	while (true)
	{
		switch (_getch())
		{
		case EDIT:
		case PRINT:
		case SEARCH:
		case SORTN:
		case ESC:
			return _getch();
		default:
			break;
		}
	}
}

void menuShowing()
{
	system("cls");
	puts("\tWelcome to the Library\n");
	puts("Select the action:\n");
	printf("1. Change books\n");
	printf("2. Print all Books\n");
	printf("3. Search books\n");
	printf("4. Sort by author\n");
	printf("ESC. To close the Library\n");
}

void  changeBooks(struct book* library, int editedBook, int numberEditedBook)
{
	while (true)
	{
		showEditMenu();
		printAllBook(library, MAXBOOKS);

		switch (menuEditChoice())
		{
		case EDIT_TITLE:
			bookFildEdit(library[numberEditedBook].title, NAME);
			break;
		case EDIT_AUTHOR:
			bookFildEdit(library[numberEditedBook].author, AUTOR);
			break;
		case EDIT_PUBLISHER:
			bookFildEdit(library[numberEditedBook].publisher, PUBLISHER);
			break;
		case EDIT_GENRE:
			bookFildEdit(library[numberEditedBook].genre, GENRE);
			break;
		case ESC:
			return;
		default:
			break;
		}
	}
}

void bookFildEdit(char* bookFild, char fild)
{
	char* fildName = getFildName(fild);

	while (true)
	{
		showMethodOfEditMenu();
		printf("%s book: %s\n", fildName, bookFild);
		switch (menuMethodOfEditChoise())
		{
		case CHANGE:
			printf("Write the new %s book: ", fildName);
			gets(bookFild);
			break;
		case ESC:
			return;
		default:
			break;
		}
	}
}

char menuMethodOfEditChoise()
{
	while (true)
	{
		char pressKey = getch();
		switch (pressKey)
		{
		case CHANGE:
		case ESC:
			return pressKey;
		default:
			break;
		}
	}
}

char* getFildName(int fildNumber)
{
	char* fildName = "";	//название поля книги
	switch (fildNumber)
	{
	case NAME:
		fildName = "name";
		break;
	case AUTOR:
		fildName = "autor";
		break;
	case PUBLISHER:
		fildName = "publisher";
		break;
	case GENRE:
		fildName = "genre";
		break;
	case ID:
		fildName = "number";
	default:
		break;
	}
	return fildName;
}

void showEditMenu()
{
	system("cls");
	printf("1. Edit title book\n");
	printf("2. Edit autor book\n");
	printf("3. Edit publisher book\n");
	printf("4. Edit genre book\n");
	printf("ESC. Back to previous Menu.\n\n");
}

void showMethodOfEditMenu()
{
	system("cls");
	printf("1. Change book title\n");
	printf("ESC. Back to previous Menu.\n");
}

char menuEditChoice()
{
	while (true)
	{
		char pressKey = getch();
		switch (pressKey)
		{
		case EDIT_TITLE:
		case EDIT_AUTHOR:
		case EDIT_PUBLISHER:
		case EDIT_GENRE:
		case ESC:
			return pressKey;
		default:
			break;
		}
	}
}


int returnPosition(struct book library[], int bookInLibrary, int fildNumber)
{
	int	bookNumber;

	int bookPosition = 0;


	if (fildNumber != ALL)
	{
		char* fildName = getFildName(fildNumber);	//название поля книги
		printf("\nEnter %s book: ", fildName);
		if (fildNumber == ID)
		{
			getNumber(&bookNumber);
		}
		printf("\n");
	}



	for (int i = 0; i < MAXBOOKS; i++)
	{
		switch (fildNumber)
		{
		case ALL:
			library[i].isShowed = true;
			bookPosition++;
			break;
		case ID:
			if (library[i].isShowed = (library[i].number == bookNumber))
			{
				bookPosition = i;
			}
			break;
		default:
			break;
		}
	}
	return bookPosition;
}


void getNumber(int* userNumber)
{
	char check; 					//колличество успешно считанных значений
	do
	{
		check = scanf("%i", userNumber);
		while (getchar() != '\n') {}
		if ((check == 1) && (*userNumber <= MAXBOOKS) && (*userNumber > 0))
		{
			break;
		}
		printf("Incorrect number. Pleasee try again.\n");
	} while (true);
}

void sortArrayName(struct book library[], int bookCount)
{
	struct book abc;
	printf("Sorted by title");
	for (int i = 0; i < MAXBOOKS - 1; i++)
	{
		for (int j = 0; j < MAXBOOKS - 1 - i; j++)
		{
			if (strcmp(library[j].title, library[j + 1].title) > 0)
			{
				abc = library[j];
				library[j] = library[j + 1];
				library[j + 1] = abc;
			}
		}
	}
	printAllBook(library, MAX_SIZE_CHAR_BOOK);
}

void printAllBook(struct book* library, int bookCount)
{
	printf("%2s %8s %28s %20s %24s\n\n", "Number", "Title", "Autor", "Genre", "Publisher");
	for (int i = 0; i < MAXBOOKS; i++)
	{
		printf("%-9i %-28s %-20s %-20s %s\n", library[i].number, library[i].title, library[i].author, library[i].genre, library[i].publisher);
	}
}

void bookSearch(struct book library[],
	int bookCount)
{
	int sizeWord = 0;
	char criteria;
	char word[MAX_SIZE_CHAR_BOOK];
	int found = 0;

	printAllBook(library, bookCount);

	printf("Enter search criteria (1 - search for author; 2 - for title):\n");
	criteria = _getche();

	printf("\nEnter the key word which you want to find :");

	fflush(stdin);
	fgets(word, MAX_SIZE_CHAR_BOOK, stdin);

	deleteChar(word, sizeWord);

	if (criteria == 49)
	{
		for (int i = 0; i < MAXBOOKS; i++)
		{
			if (_stricmp(word, library[i].author) == 0)
			{
				found = 1;
				printf("%-9i %-28s %-20s %-20s %s\n", library[i].number, library[i].title, library[i].author, library[i].genre, library[i].publisher);
			}

		}
	}
	else if (criteria == 50)
	{
		for (int i = 0; i < MAXBOOKS; i++)
		{
			if (_stricmp(word, library[i].title) == 0)
			{
				found = 1;
				printf("%-9i %-28s %-20s %-20s %s\n", library[i].number, library[i].title, library[i].author, library[i].genre, library[i].publisher);
			}

		}
	}
	if (!found)
	{
		printf("Book with the same name is not found");
	}
}

void deleteChar(char word[], int sizeWord)
{
	for (int i = 0; i < MAX_SIZE_CHAR_BOOK; i++)
	{
		if (word[i] == '\n')
		{
			word[i] = '\0';
			break;
		}
	}
}
