/*Доделайте программу «Библиотека». Дополните программу следующими возможностями:
•  Чтение книг из файла при старте программы
•  Запись книг в файл по выходу из программы*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>


enum MenuMain
{
	PRINT_BOOK = '1',
	FIND_AUTOR_BOOK = '2',
	FIND_NAME_BOOK = '3',
	SORT_BOOK = '4',
	EDIT_BOOK = '5',
	ESC = '\x1b',
};
enum MenuEdit
{
	EDIT_NAME = '1',
	EDIT_AUTOR = '2',
	EDIT_PUBLISHER = '3',
	EDIT_GENRE = '4',
};
enum MenuEditType
{
	UPPER = '1',
	LOWER = '2',
	WRITE_NEW = '3',
};
enum SortedType
{
	NO_SORTED = '0',
	SORTED_BY_NAME = '1',
	SORTED_BY_AUTOR = '2',
	SORTED_BY_AUTOR_PUBLISHER = '3',
	SORTED_BY_AUTOR_GENRE = '4',
};
enum BookFild
{
	ALL = '0',
	NAME = '1',
	AUTOR = '2',
	PUBLISHER = '3',
	GENRE = '4',
	ID = '5',
	BOOK_FILD_LENGTH = 50,
	BOOK_FILD_COUNT = 5,

};

struct book* readLibraryFromFile(char* fileName, int* bookInLibrary);
void saveLibrary(char* fileName, struct book* library, int bookInLibrary);
void closeLibrary(struct book* library, int bookInLibrary);
void printBooks(struct book* library, int bookInLibrary);
void bookNameSort(struct book* library, int bookInLibrary);
void reverseBookInLibrary(struct book* library, int bookInLibrary);
void replaseBook(struct book* library, int positionFirstBook, int positionSecondBook);
int filtrByFild(struct book* library, int bookInLibrary, int fildNumber);
void bookEdit(struct book* library, int bookInLibrary, int editedBook);
void bookFildEdit(char* bookFild, char fild);
void getNumber(int* userNumber, int bookInLibrary);
char* getFildName(int fildNumber);
void showMainMenu();
void showEditMenu();
void showMethodOfEditMenu();
char menuChoice();
char menuEditChoice();
char menuMethodOfEditChoise();
bool isPointerEmpty(struct book* library);

/*книга*/
struct book
{
	int id;
	char* name;
	char* autor;
	char* publisher;
	char* genre;
	bool isShowed;
};

int main(int argc, char* argv[])
{
	char* fileName = "Library.txt";		// Имя файла
	int bookInLibrary = 0;				// Число книг в библиотеке
	struct book* bookLibrary = NULL;	// Библиотека книг

	bookLibrary = readLibraryFromFile(fileName, &bookInLibrary);	//Чтение библиотеки из файла

	char pointOfMainMenuChoising = 0;	//Выбранный пункт главного меню
	char librarySorted = NO_SORTED;		//Поле по которому отсортированы книги в библиотеке
	bool isMainMenuShowing = false;		//Признак отображения главного меню

	while (true)
	{
		if (isMainMenuShowing == true)
		{
			pointOfMainMenuChoising = menuChoice();
		}
		showMainMenu();

		if (isMainMenuShowing == false)
		{
			pointOfMainMenuChoising = menuChoice();
			isMainMenuShowing = true;
		}

		switch (pointOfMainMenuChoising)
		{
		case PRINT_BOOK:
			filtrByFild(bookLibrary, bookInLibrary, ALL);
			break;
		case FIND_AUTOR_BOOK:
			filtrByFild(bookLibrary, bookInLibrary, ALL);
			printBooks(bookLibrary, bookInLibrary);
			filtrByFild(bookLibrary, bookInLibrary, AUTOR);
			showMainMenu();
			break;
		case FIND_NAME_BOOK:
			filtrByFild(bookLibrary, bookInLibrary, ALL);
			printBooks(bookLibrary, bookInLibrary);
			filtrByFild(bookLibrary, bookInLibrary, NAME);
			showMainMenu();
			break;
		case SORT_BOOK:
			if (librarySorted != SORTED_BY_NAME)
			{
				bookNameSort(bookLibrary, bookInLibrary);
				librarySorted = SORTED_BY_NAME;
			}
			else
			{
				reverseBookInLibrary(bookLibrary, bookInLibrary);
			}
			break;
		case EDIT_BOOK:
			filtrByFild(bookLibrary, bookInLibrary, ALL);								//убрать фильтр со списка книг
			printBooks(bookLibrary, bookInLibrary);
			int bookPositionInLibrary = filtrByFild(bookLibrary, bookInLibrary, ID);	//Позиция книги в библиотеке
			bookEdit(bookLibrary, bookInLibrary, bookPositionInLibrary);
			isMainMenuShowing = false;
			continue;
		case ESC:
			return 0;
		default:
			break;
		}
		printBooks(bookLibrary, bookInLibrary);
	}

	saveLibrary(fileName, bookLibrary, bookInLibrary);	// Запись библиотеки в файл
	closeLibrary(bookLibrary, bookInLibrary);			// Освобождение памяти
}

/*Считать библиотеку из файла*/
struct book* readLibraryFromFile(char* fileName, int* booksCount)
{
	FILE* fileLibrary = fopen(fileName, "r");		// Открытый для чтения файл
	if (fileLibrary == NULL)
	{
		printf("Error open file %s", fileName);
		exit(1);
	}
	struct book* library = NULL;

	char readString[BOOK_FILD_LENGTH * BOOK_FILD_COUNT];	// Считанная из файла строка
	char* book[BOOK_FILD_COUNT];			// Массив из полей полученной из файла книги
	char* bookFild;			// Поле книги
	int sizeBook = 0;		// Размер книги в памяти

	for (int i = 0; !feof(fileLibrary); i++)
	{
		fgets(readString, BOOK_FILD_LENGTH * BOOK_FILD_COUNT, fileLibrary);
		bookFild = strtok(readString, ";\n");	// Разбиение строки на поля по разделителям
		for (int j = 0; j < 5; j++)
		{
			if (bookFild == NULL)
			{
				break;
			}
			book[j] = bookFild;
			bookFild = strtok('\0', ";\n");
		}
		sizeBook += (sizeof(book) + 4);

		library = (struct book*)realloc(library, sizeBook);
		if (isPointerEmpty(library))
			return 1;

		library[i].id = atoi(book[0]);

		library[i].name = malloc(strlen(book[1]) + 1);
		strcpy(library[i].name, book[1]);

		library[i].autor = malloc(strlen(book[2]) + 1);
		strcpy(library[i].autor, book[2]);

		library[i].publisher = malloc(strlen(book[3]) + 1);
		strcpy(library[i].publisher, book[3]);

		library[i].genre = malloc(strlen(book[4]) + 1);
		strcpy(library[i].genre, book[4]);

		library[i].isShowed = true;

		(*booksCount)++;
	};
	fclose(fileLibrary);

	return library;
}

/*Сохранить библиотеку в файл*/
void saveLibrary(char* fileName, struct book* library, int bookInLibrary)
{
	FILE* fileLibrary = fopen(fileName, "w");		// Открытый для записи файл
	if (fileLibrary == NULL)
	{
		printf("Error open file %s", fileName);
		exit(1);
	}

	for (int i = 0; i < bookInLibrary; i++)
	{
		fprintf(fileLibrary, "%i;%s;%s;%s;%s;\n",
			library[i].id, library[i].name, library[i].autor, library[i].publisher, library[i].genre);
	}
	fclose(fileLibrary);
}

/*Освобождает память в "куче" выделенную для хранения библиотеки*/
void closeLibrary(struct book* library, int bookInLibrary)
{
	for (char i = 0; i < bookInLibrary; i++)
	{
		free(library[i].name);
		free(library[i].autor);
		free(library[i].publisher);
		free(library[i].genre);
	}
	free(library);
}

/*Печать книг*/
void printBooks(struct book* library, int bookInLibrary)
{
	if (isPointerEmpty(library))
	{
		return;
	}
	printf("%2s%8s %21s %17s %15s\n\n", "Id", "Name", "Autor", "Publisher", "Genre");
	for (int i = 0; i < bookInLibrary; i++)
	{
		if (library[i].isShowed == true)
		{
			printf("%-2i%-25s%-14s%-20s%s\n", library[i].id, library[i].name, library[i].autor, library[i].publisher, library[i].genre);
		}
	}
}

/*Сортировка книг по возрастанию (метод Шелла)*/
void bookNameSort(struct book* library, int bookInLibrary)
{
	if (isPointerEmpty(library))
	{
		return;
	}
	for (int i = bookInLibrary / 2; i > 0; i /= 2)
	{
		for (int j = i; j < bookInLibrary; j++)
		{
			for (int k = j - i; ((k >= 0) && (strcmp(library[k].name, library[k + i].name) > 0)); k -= i)
			{
				replaseBook(library, k, k + i);
			}
		}
	}
}

/*Изменение порядка книг в библиотеке на противоположный*/
void reverseBookInLibrary(struct book* library, int bookInLibrary)
{
	if (isPointerEmpty(library))
	{
		return;
	}
	struct book tempBook;
	for (int i = 0; (i < bookInLibrary / 2) && (i != bookInLibrary - 1 - i); i++)
	{
		tempBook = library[i];
		library[i] = library[bookInLibrary - 1 - i];
		library[bookInLibrary - 1 - i] = tempBook;
	}
}

/*Перестановка местами двух книг*/
void replaseBook(struct book* library, int positionFirstBook, int positionSecondBook)
{
	if (isPointerEmpty(library))
	{
		return;
	}
	struct book temp = library[positionFirstBook];
	library[positionFirstBook] = library[positionSecondBook];
	library[positionSecondBook] = temp;
}

/*Фильтр библиотеке по выбранному полю.
Возвращает ID книги, если фильтрация производится по ID,
либо колличество найденных книг в противном случае.*/
int filtrByFild(struct book* library, int bookInLibrary, int fildNumber)
{
	if (isPointerEmpty(library))
	{
		return -1;
	}
	union bookUnion
	{
		char filtr[BOOK_FILD_LENGTH];
		int	bookID;
	};
	int bookPositionOrCount = 0;	//Позиция книги в библиотеке либо колличество найденных книг
	union bookUnion filterOrID;		//ID книги либо фильтр

	if (fildNumber != ALL)
	{
		char* fildName = getFildName(fildNumber);	//название поля книги
		printf("\nEnter %s book: ", fildName);
		if (fildNumber == ID)
		{
			getNumber(&filterOrID.bookID, bookInLibrary);
		}
		else
		{
			gets(filterOrID.filtr);
		}
		printf("\n");
	}

	for (int i = 0; i < bookInLibrary; i++)
	{
		switch (fildNumber)
		{
		case ALL:
			library[i].isShowed = true;
			bookPositionOrCount++;
			break;
		case NAME:
			if (library[i].isShowed = strstr(library[i].name, filterOrID.filtr))
			{
				bookPositionOrCount++;
			}
			break;
		case AUTOR:
			if (library[i].isShowed = strstr(library[i].autor, filterOrID.filtr))
			{
				bookPositionOrCount++;
			}
			break;
		case PUBLISHER:
			if (library[i].isShowed = strstr(library[i].publisher, filterOrID.filtr))
			{
				bookPositionOrCount++;
			}
			break;
		case GENRE:
			if (library[i].isShowed = strstr(library[i].genre, filterOrID.filtr))
			{
				bookPositionOrCount++;
			}
			break;
		case ID:
			if (library[i].isShowed = (library[i].id == filterOrID.bookID))
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
void bookEdit(struct book* library, int bookInLibrary, int editedBook)
{
	if (isPointerEmpty(library))
	{
		return;
	}
	while (true)
	{
		showEditMenu();
		printBooks(library, bookInLibrary);

		switch (menuEditChoice())
		{
		case EDIT_NAME:
			bookFildEdit(library[editedBook].name, NAME);
			break;
		case EDIT_AUTOR:
			bookFildEdit(library[editedBook].autor, AUTOR);
			break;
		case EDIT_PUBLISHER:
			bookFildEdit(library[editedBook].publisher, PUBLISHER);
			break;
		case EDIT_GENRE:
			bookFildEdit(library[editedBook].genre, GENRE);
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

	while (true)
	{
		showMethodOfEditMenu();
		printf("%s book: %s\n", fildName, bookFild);

		switch (menuMethodOfEditChoise())
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
void getNumber(int* userNumber, int bookInLibrary)
{
	char check; 					//колличество успешно считанных значений
	do
	{
		check = scanf("%i", userNumber);
		while (getchar() != '\n') {}
		if ((check == 1) && (*userNumber <= bookInLibrary) && (*userNumber > 0))
		{
			break;
		}
		printf("Incorrect number. Pleasee try again.\n");
	} while (true);
}

/*Получение названия поля книги*/
char* getFildName(int fildNumber)
{
	char* fildName = "";	//название поля книги
	switch (fildNumber)
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
	while (true)
	{
		char pressKey = getch(); //нажатая клавиша
		switch (pressKey)
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
	while (true)
	{
		char pressKey = getch(); //нажатая клавиша
		switch (pressKey)
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
	while (true)
	{
		char pressKey = getch(); //нажатая клавиша
		switch (pressKey)
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

bool isPointerEmpty(struct book* library)
{
	if (library == NULL)
	{
		printf("\nSomething went wrong. Pointer for Library is empty.\n");
		return true;
	}
	return false;
}