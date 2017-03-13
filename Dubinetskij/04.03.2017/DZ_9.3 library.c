/*Задание 3:
Разработайте программу «Библиотека». Создайте структуру «Книга» (название, автор,
издательство, жанр). Создайте массив из 10 книг. Реализуйте для него следующие
возможности:
Редактировать книгу
Печать всех книг
Поиск книг по автору
Поиск книги по названию
Сортировка массива по названию книг
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define BOOK_IN_LIBRARY 10
#define BOOK_FILD_LENGTH 50

/*Для главного меню*/
#define PRINT_BOOK '1'
#define FIND_AUTOR_BOOK '2'
#define FIND_NAME_BOOK '3'
#define SORT_BOOK '4'
#define EDIT_BOOK '5'
#define ESC '\x1b'
/*Для меню редактирования*/
#define EDIT_NAME '1'
#define EDIT_AUTOR '2'
#define EDIT_PUBLISHER '3'
#define EDIT_GENRE '4'
/*Для меню вида редактирования*/
#define UPPER '1'
#define LOWER '2'
#define WRITE_NEW '3'
/*Выбор поля для сортировки*/
#define NO_SORTED '0'
#define SORTED_BY_NAME '1'
#define SORTED_BY_AUTOR '2'
#define SORTED_BY_AUTOR_PUBLISHER '3'
#define SORTED_BY_AUTOR_GENRE '4'
/*Для идентификации полей книги*/
#define ALL '0'
#define NAME '1'
#define AUTOR '2'
#define PUBLISHER '3'
#define GENRE '4'
#define ID '5'

void printBooks(struct book Linrary[], int bookInLibrary);
void bookNameSort(struct book Linrary[], int bookInLibrary);
void reverseBookInLibraru(struct book Linrary[], int bookInLibrary);
void replaseBook(struct book Linrary[], int positionFirstBook, int positionSecondBook);
int filtrByFild(struct book Linrary[], int bookInLibrary, int fildNumber);
void bookEdit(struct book Linrary[], int bookInLibrary, int editedBook);
void bookFildEdit(char* bookFild, char fild);
void getNumber(int* userNumber);
char* getFildName(int fildNumber);
void showMainMenu();
void showEditMenu();
void showMethodOfEditMenu();
char menuChoice();
char menuEditChoice();
char menuMethodOfEditChoise();

/*Книга*/
struct book
{
	char name[BOOK_FILD_LENGTH];
	char autor[BOOK_FILD_LENGTH];
	char publisher[BOOK_FILD_LENGTH];
	char genre[BOOK_FILD_LENGTH];
	bool isShowed;
	int id;
};

int main()
{
	/*Библиотека книг*/
	struct book bookLibrary[BOOK_IN_LIBRARY] =
	{ "Don Quixote",                "Cervantes",        "Francisco de Robles",  "Novel",				true,	1,
		"A Tale of Two Cities",       "Dickens",          "Chapman & Hall",       "Historical novel",		true,	2,
		"The Alchemist",              "Coelho",           "HarperTorch",          "Adventure, fantasy",	true,	3,
		"The Little Prince",          "Saint-Exupery",    "Reynal & Hitchcock",   "Philosophic",			true,	4,
		"Harry Potter",               "Rowling",          "Bloomsbury",           "Fantasy",				true,	5,
		"Dream of the Red Chamber",   "Cao Xueqin",       "Gao E",                "Novel",				true,	6,
		"Alice in Wonderland",        "Carroll",          "Macmillan",            "Children's fiction",	true,	7,
		"The Young Guard",            "Fadeyev",          "Pioneer Pravda",       "Novel",				true,	8,
		"Dune",                       "Herbert",          "Chilton Books",        "Novel",				true,	9,
		"The Secret",                 "Byrne",            "Atria Books",          "Self-help",			true,	10
	};

	char pointOfMainMenuChoising = NULL;	//Выбранный пункт главного меню
	char librurySorted = NO_SORTED;			//Поле по которому отсортированы книги в библиотеке
	bool isMainMenuShowing = false;			//Признак отображения главного меню

	while(true)
	{
		if(isMainMenuShowing == true)
		{
			pointOfMainMenuChoising = menuChoice();
		}
		showMainMenu();

		if(isMainMenuShowing == false)
		{
			pointOfMainMenuChoising = menuChoice();
			isMainMenuShowing = true;
		}

		switch(pointOfMainMenuChoising)
		{
		case PRINT_BOOK:
			filtrByFild(bookLibrary, BOOK_IN_LIBRARY, ALL);
			break;
		case FIND_AUTOR_BOOK:
			filtrByFild(bookLibrary, BOOK_IN_LIBRARY, ALL);
			printBooks(bookLibrary, BOOK_IN_LIBRARY);
			filtrByFild(bookLibrary, BOOK_IN_LIBRARY, AUTOR);
			showMainMenu();
			break;
		case FIND_NAME_BOOK:
			filtrByFild(bookLibrary, BOOK_IN_LIBRARY, ALL);
			printBooks(bookLibrary, BOOK_IN_LIBRARY);
			filtrByFild(bookLibrary, BOOK_IN_LIBRARY, NAME);
			showMainMenu();
			break;
		case SORT_BOOK:
			if(librurySorted != SORTED_BY_NAME)
			{
				bookNameSort(bookLibrary, BOOK_IN_LIBRARY);
				librurySorted = SORTED_BY_NAME;
			}
			else
			{
				reverseBookInLibraru(bookLibrary, BOOK_IN_LIBRARY);
			}
			break;
		case EDIT_BOOK:
			filtrByFild(bookLibrary, BOOK_IN_LIBRARY, ALL);								//убрать фильтр со списка книг
			printBooks(bookLibrary, BOOK_IN_LIBRARY);
			int bookPositionInLibrary = filtrByFild(bookLibrary, BOOK_IN_LIBRARY, ID);	//Позиция книги в библиотеке
			bookEdit(bookLibrary, BOOK_IN_LIBRARY, bookPositionInLibrary);
			isMainMenuShowing = false;
			continue;
		case ESC:
			return 0;
		default:
			break;
		}
		printBooks(bookLibrary, BOOK_IN_LIBRARY);
	}
}

/*Печать книг*/
void printBooks(struct book Linrary[], int bookInLibrary)
{
	printf("%2s%8s %21s %17s %15s\n\n", "Id", "Name", "Autor", "Publisher", "Genre");
	for(int i = 0; i < bookInLibrary; i++)
	{
		if(Linrary[i].isShowed == true)
		{
			printf("%-2i%-25s%-14s%-20s%s\n", Linrary[i].id, Linrary[i].name, Linrary[i].autor, Linrary[i].publisher, Linrary[i].genre);
		}
	}
}

/*Сортировка книг по возрастанию (метод Шелла)*/
void bookNameSort(struct book Linrary[], int bookInLibrary)
{
	for(int i = bookInLibrary / 2; i > 0; i /= 2)
	{
		for(int j = i; j < bookInLibrary; j++)
		{
			for(int k = j - i; ((k >= 0) && (strcmp(Linrary[k].name, Linrary[k + i].name) > 0)); k -= i)
			{
				replaseBook(Linrary, k, k + i);
			}
		}
	}
}

/*Изменение порядка книг в библиотеке на противоположный*/
void reverseBookInLibraru(struct book Linrary[], int bookInLibrary)
{
	struct book tempBook;
	for(int i = 0; (i < bookInLibrary / 2) && (i != bookInLibrary - 1 - i); i++)
	{
		tempBook = Linrary[i];
		Linrary[i] = Linrary[bookInLibrary - 1 - i];
		Linrary[bookInLibrary - 1 - i] = tempBook;
	}
}

/*Перестановка местами двух книг*/
void replaseBook(struct book Linrary[], int positionFirstBook, int positionSecondBook)
{
	struct book temp = Linrary[positionFirstBook];
	Linrary[positionFirstBook] = Linrary[positionSecondBook];
	Linrary[positionSecondBook] = temp;
}

/*Фильтр библиотеке по выбранному полю.
Возвращает ID книги, если фильтрация производится по ID,
либо колличество найденных книг в противном случае.*/
int filtrByFild(struct book Linrary[], int bookInLibrary, int fildNumber)
{
	union bookUnion
	{
		char filtr[BOOK_FILD_LENGTH];
		int	bookID;
	};
	int bookPositionOrCount = 0;	//Позиция книги в библиотеке либо колличество найденных книг
	union bookUnion filterOrID;		//ID книги либо фильтр

	if(fildNumber != ALL)
	{
		char* fildName = getFildName(fildNumber);	//название поля книги
		printf("\nEnter %s book: ", fildName);
		(fildNumber == ID) ? getNumber(&filterOrID.bookID) : gets(filterOrID.filtr);
		printf("\n");
	}

	for(int i = 0; i < bookInLibrary; i++)
	{
		switch(fildNumber)
		{
		case ALL:
			Linrary[i].isShowed = true;
			bookPositionOrCount++;
			break;
		case NAME:
			if(Linrary[i].isShowed = strstr(Linrary[i].name, filterOrID.filtr))
			{
				bookPositionOrCount++;
			}
			break;
		case AUTOR:
			if(Linrary[i].isShowed = strstr(Linrary[i].autor, filterOrID.filtr))
			{
				bookPositionOrCount++;
			}
			break;
		case PUBLISHER:
			if(Linrary[i].isShowed = strstr(Linrary[i].publisher, filterOrID.filtr))
			{
				bookPositionOrCount++;
			}
			break;
		case GENRE:
			if(Linrary[i].isShowed = strstr(Linrary[i].genre, filterOrID.filtr))
			{
				bookPositionOrCount++;
			}
			break;
		case ID:
			if(Linrary[i].isShowed = (Linrary[i].id == filterOrID.bookID))
			{
				bookPositionOrCount = i;
			}
			break;
		default:
			break;
		}
	}
	return bookPositionOrCount;
}

/*Редактирование выбранной книги*/
void bookEdit(struct book Linrary[], int bookInLibrary, int editedBook)
{
	while(true)
	{
		showEditMenu();
		printBooks(Linrary, BOOK_IN_LIBRARY, true);

		switch(menuEditChoice())
		{
		case EDIT_NAME:
			bookFildEdit(Linrary[editedBook].name, NAME);
			break;
		case EDIT_AUTOR:
			bookFildEdit(Linrary[editedBook].autor, AUTOR);
			break;
		case EDIT_PUBLISHER:
			bookFildEdit(Linrary[editedBook].publisher, PUBLISHER);
			break;
		case EDIT_GENRE:
			bookFildEdit(Linrary[editedBook].genre, GENRE);
			break;
		case ESC:
			return;
		default:
			break;
		}
	}
}

/*Редактирование выбранного поля книги.*/
void bookFildEdit(char* bookFild, char fild)
{
	char* fildName = getFildName(fild);

	while(true)
	{
		showMethodOfEditMenu();
		printf("\%s book: %s\n", fildName, bookFild);

		switch(menuMethodOfEditChoise())
		{
		case UPPER:
			strupr(bookFild);
			break;
		case LOWER:
			strlwr(bookFild);
			break;
		case WRITE_NEW:
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

/*Получение от пользователя одного целого числа*/
void getNumber(int* userNumber)
{
	char check; 					//колличество успешно считанных значений
	do
	{
		check = scanf("%i", userNumber);
		while(getchar() != '\n') {}
		if((check == 1) && (*userNumber <= BOOK_IN_LIBRARY) && (*userNumber > 0))
		{
			break;
		}
		printf("Incorrect number. Pleasee try again.\n");
	} while(true);
}

/*Получение названия поля книги*/
char* getFildName(int fildNumber)
{
	char* fildName = "";	//название поля книги
	switch(fildNumber)
	{
	case NAME:
		fildName = "Name";
		break;
	case AUTOR:
		fildName = "Autor";
		break;
	case PUBLISHER:
		fildName = "Publisher";
		break;
	case GENRE:
		fildName = "Genre";
		break;
	case ID:
		fildName = "ID";
	default:
		break;
	}
	return fildName;
}

/*Отобрзить главное меню*/
void showMainMenu()
{
	system("cls");
	printf("1   Print list of books\n");
	printf("2   Find book by autor\n");
	printf("3   Find book by name\n");
	printf("4   Sort books by name\n");
	printf("5   Edit book\n");
	printf("ESC EXIT.\n\n");
}

/*Отобразить меню редактирования книги*/
void showEditMenu()
{
	system("cls");
	printf("1   Edit name book\n");
	printf("2   Edit autor book\n");
	printf("3   Edit publisher book\n");
	printf("4   Edit genre book\n");
	printf("ESC Back to previous Menu.\n\n");
}

/*Отобразить меню выбора способа редактирования книги*/
void showMethodOfEditMenu()
{
	system("cls");
	printf("1   Change to upper\n");
	printf("2   Change to lower\n");
	printf("3   Write the new value\n");
	printf("ESC Back to previous Menu.\n\n");
}

/*Выбор пункта главного меню*/
char menuChoice()
{
	while(true)
	{
		char pressKey = getch(); //нажатая клавиша
		switch(pressKey)
		{
		case PRINT_BOOK:
		case FIND_AUTOR_BOOK:
		case FIND_NAME_BOOK:
		case SORT_BOOK:
		case EDIT_BOOK:
		case ESC:
			return pressKey;
		default:
			break;
		}
	}
}

/*Выбор пункта меню редактирования*/
char menuEditChoice()
{
	char pressKey = getch(); //нажатая клавиша
	while(true)
	{
		switch(pressKey)
		{
		case EDIT_NAME:
		case EDIT_AUTOR:
		case EDIT_PUBLISHER:
		case EDIT_GENRE:
		case ESC:
			return pressKey;
		default:
			break;
		}
	}
}

/*Выбор пункта меню способа редактирования*/
char menuMethodOfEditChoise()
{
	char pressKey = getch(); //нажатая клавиша
	while(true)
	{
		switch(pressKey)
		{
		case UPPER:
		case LOWER:
		case WRITE_NEW:
		case ESC:
			return pressKey;
		default:
			break;
		}
	}
}
