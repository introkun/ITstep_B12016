/*Разработайте программу учета BlueRay дисков(название, директор, год) с
использованием очереди(FIFO).Реализуйте функции для очереди :
•  Вставка в конец очереди
•  Печать всей очереди
•  Получение первого элемента из очереди и его удаление из нее
•  Чтение первого элемента из очереди без удаления
•  Проверка пустоты очереди
Задание реализовать с использованием массивов структур, выделенных с
использованием динамической памяти.*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

enum
{
	DISK_IN_COLLECTION = 5,
	PRINT_QUEUE = '1',
	ADD_DISK = '2',
	SHOW_DISK = '3',
	SHOW_AND_REMOVE_DISK = '4',
	GET_COUNT = '5',
	ESC = '\x1b',
	MIN_YEAR_OF_DISK = 1950,
	THIS_YEAR = 2017,
};
/*BluRay диск с указателем на следующий диск в очереди*/
struct diskBluRay
{
	char* name;					// Имя диска
	char* directory;			// Категория диска
	short year;					// Год выпуска
	struct diskBluRay* next;	// Указатель на следующий диск в очереди
};

struct diskBluRay* init();
struct diskBluRay* getBluRayCollections();
void printQueue(struct diskBluRay* queue);
struct diskBluRay* addDisk(struct diskBluRay* disk);
struct diskBluRay* delDisk(struct diskBluRay* disk);
void showDisk(struct diskBluRay* disk);
void freeMamory(struct diskBluRay* disk);
int getCountOfDisk(struct diskBluRay* disk);
char* getFildOfDisk(char* printString);
void getYear(short* year);
char menuChoice();
void showMainMenu();

int main()
{
	struct diskBluRay* queue = getBluRayCollections();	// очередь BluRay дисков

	char pointOfMainMenuChoising = 0;	// Выбранный пункт главного меню
	bool isMainMenuShowing = false;		// Признак отображения главного меню
	int diskCount = 0;					// Дисков в очереди

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
		case PRINT_QUEUE:
			printQueue(queue);
			break;
		case ADD_DISK:
			queue = addDisk(queue);
			printf("\nDisk added.\n");
			break;
		case SHOW_DISK:
			showDisk(queue);
			break;
		case SHOW_AND_REMOVE_DISK:
			diskCount = getCountOfDisk(queue);
			if (diskCount != 0)
			{
				showDisk(queue);
				queue = delDisk(queue);
				getCountOfDisk(queue);
				printf("\nFirst disk in queue is removed.\nRemain the %i disks.\n", diskCount-1);
			}
			else
			{
				printf("Queue of BluRay disks is empty.\n");
			}
			break;
		case GET_COUNT:
		{
			diskCount = getCountOfDisk(queue);
			if (diskCount != 0)
			{
				printf("In queue is %i BluRay disk.\n", diskCount);
			}
			else
			{
				printf("Queue of BluRay disks is empty.\n");
			}
			break;
		}
		case ESC:
			return 0;
		default:
			break;
		}
		printf("\nChoice point of menu...");
	}
	freeMamory(queue);
}

/*Выделение памяти в "куче" под диск */
struct diskBluRay* init()
{
	return malloc(sizeof(struct diskBluRay));
};

/*Получение очереди BluRay дисков.
Возвращает указатель на начало очереди.*/
struct diskBluRay* getBluRayCollections()
{
	struct diskBluRay collection[DISK_IN_COLLECTION] =			// Имеющаяся коллекция дисков
	{{"Doctor Strange", "Disney", 2017},
	{"Psycho", "Universal Studios", 1960},
	{"Life", "BBC", 2009},
	{"Toy Story 3", "PIXAR", 2010},
	{"The Lord of the Rings", "New Line Cinema",2001}};

	struct diskBluRay* diskQueue = init();
	struct diskBluRay* headQueue = diskQueue;

	/*Заполнение очереди дисками из имеющейся базы дисков*/
	for (int i = 0; i < DISK_IN_COLLECTION; i++)
	{
		diskQueue->name = (char*)malloc(strlen(collection[i].name) + 1);
		strcpy(diskQueue->name, collection[i].name);

		diskQueue->directory = (char*)malloc(strlen(collection[i].directory) + 1);
		strcpy(diskQueue->directory, collection[i].directory);

		diskQueue->year = collection[i].year;

		diskQueue->next = (i != DISK_IN_COLLECTION - 1) ? init() : NULL;
		diskQueue = diskQueue->next;
	}
	return headQueue;
}

/*Вывод всей очереди дисков на дисплей*/
void printQueue(struct diskBluRay* queue)
{
	printf("%10s%24s%15s\n\n", "Name", "Derectory", "Year");
	while (queue != NULL)
	{
		printf("%-25s%-20s%-5i\n", queue->name, queue->directory, queue->year);
		queue = queue->next;
	}
}

/*Добавление диска в конец очереди.
Возвращает указатель на начало очереди.*/
struct diskBluRay* addDisk(struct diskBluRay* disk)
{
	struct diskBluRay* headQueue;
	if (disk != NULL)
	{
		headQueue = disk;
		/*Поиск последнего диска в очереди*/
		while (disk->next != NULL)
		{
			disk = disk->next;
		}
		disk->next = init();
		disk = disk->next;
	}
	else
	{
		disk = init();
		headQueue = disk;
	}
	disk->name = getFildOfDisk("Disk name : ");
	disk->directory = getFildOfDisk("Disk directory: ");
	getYear(&disk->year);
	disk->next = NULL;
	return headQueue;
}


/*Удалить первый диск в очереди.
Возвращает указатель на новое начало очереди.*/
struct diskBluRay* delDisk(struct diskBluRay* disk)
{
	struct diskBluRay* headQueue = NULL; // указатель на начало очереди
	if (disk != NULL)
	{
		headQueue = disk->next;
		free(disk->name);
		free(disk->directory);
		free(disk);
	}
	return disk = headQueue;
}

/*Показать первый диск в очереди*/
void showDisk(struct diskBluRay* disk)
{
	if (disk != NULL)
	{
		printf("%10s%24s%15s\n\n", "Name", "Derectory", "Year");
		printf("%-25s%-20s%-5i\n", disk->name, disk->directory, disk->year);
	}
}

/*Освобождение памяти*/
void freeMamory(struct diskBluRay* disk)
{
	while (delDisk(disk) != NULL) {}
}

/*Возвращает колличество дисков в очереди*/
int getCountOfDisk(struct diskBluRay* disk)
{
	int count = 0;
	while (disk != NULL)
	{
		disk = disk->next;
		count++;
	}
	return count;
}

/*Получение строки от пользователя с сохранением ее в "куче"*/
char* getFildOfDisk(char* printString)
{
	printf("%s", printString);
	char gotUserString[50];	//полученная от пользователя информация
	gets(gotUserString);
	char* string = malloc(strlen(gotUserString) + 1);
	strcpy(string, gotUserString);
	return string;
}

/*Получение от пользователя года выпуска диска*/
void getYear(short* year)
{
	printf("Year of disk manufacture (%i-%i): ", MIN_YEAR_OF_DISK, THIS_YEAR);
	while (true)
	{
		if (scanf("%hu", year) == 1)
			if (*year > MIN_YEAR_OF_DISK && *year <= THIS_YEAR)
				break;
		while (getchar() != '\n') {}
		printf("Incorrect year value. Try agane.");
	}
	while (getchar() != '\n') {}
}

/*Выбор пункта меню*/
char menuChoice()
{
	while (true)
	{
		char pressKey = getch(); //нажатая клавиша
		switch (pressKey)
		{
		case PRINT_QUEUE:
		case ADD_DISK:
		case SHOW_DISK:
		case SHOW_AND_REMOVE_DISK:
		case GET_COUNT:
		case ESC:
			return pressKey;
		default:
			break;
		}
	}
}

/*Отобрзить меню*/
void showMainMenu()
{
	system("cls");
	printf("%25s\n", "M E N U");
	printf("1   Print BruRay disk collections\n");
	printf("2   Insert disk in the end of collection\n");
	printf("3   Show first disk in collection\n");
	printf("4   Show first disk in collection and remove him\n");
	printf("5   Get the count of disk in collection\n");
	printf("ESC EXIT.\n\n");
}
