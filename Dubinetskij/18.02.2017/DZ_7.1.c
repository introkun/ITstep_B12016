/*
Задание 7.1
Написать программу «справочник». Создать два одномерных массива. Один массив
хранит номера ICQ, второй – телефонные номера. Реализовать меню для пользователя:
• Отсортировать по номерам ICQ
• Отсортировать по номерам телефона• Вывести список пользователей
• Выход
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define REFERENCE_BOOK_SIZE 17                       //Колличество элементов в справочнике
#define ESC '\x1b'    
#define SORT_BY_ICQ '1'
#define SORT_BY_PHONE '2'

void fillArrayRandomIsqNumbers(int isqArray[], char arrayLength);
void fillArrayRandomPhoneNumbers(int phoneArray[], char arrayLength);
void arrayFillRandom(int array[], char arrayLength, char cipherInNumber);
int getRandomNumber(char cipherInNumber);
void arraySort(int needSortArray[], int dependentArray[], char arrayLength);
void replaseNumbers(int* firstNumber, int* secondNumber);
void printList(int firstArray[], int secondArray[], char arrayLength);
char choiceSortingArray();
void showMenu();
void arrayRotate(int array[], char arrayLength);

int main()
{
    srand(time(0) * 1000);

    int icqNumbersArray[REFERENCE_BOOK_SIZE];        //Список ISQ номеров
    int phoneNumbersArray[REFERENCE_BOOK_SIZE];      //Список телефонных номеров

    fillArrayRandomIsqNumbers(icqNumbersArray, REFERENCE_BOOK_SIZE);
    fillArrayRandomPhoneNumbers(phoneNumbersArray, REFERENCE_BOOK_SIZE);

    showMenu();
    printList(icqNumbersArray, phoneNumbersArray, REFERENCE_BOOK_SIZE);
    char previousArraySorted = 0;                    //предыдущий отсортированный массив
    while (true)
    {
        switch (choiceSortingArray())
        {
        case SORT_BY_ICQ:
            if (previousArraySorted != SORT_BY_ICQ)
            {
                arraySort(icqNumbersArray, phoneNumbersArray, REFERENCE_BOOK_SIZE);
            }
            else
            {
                arrayRotate(icqNumbersArray, REFERENCE_BOOK_SIZE);
                arrayRotate(phoneNumbersArray, REFERENCE_BOOK_SIZE);
            }
            printList(icqNumbersArray, phoneNumbersArray, REFERENCE_BOOK_SIZE);
            previousArraySorted = SORT_BY_ICQ;
            break;
        case SORT_BY_PHONE:
            if (previousArraySorted != SORT_BY_PHONE)
            {
                arraySort(phoneNumbersArray, icqNumbersArray, REFERENCE_BOOK_SIZE);
            }
            else
            {
                arrayRotate(icqNumbersArray, REFERENCE_BOOK_SIZE);
                arrayRotate(phoneNumbersArray, REFERENCE_BOOK_SIZE);
            }
            printList(icqNumbersArray, phoneNumbersArray, REFERENCE_BOOK_SIZE);
            previousArraySorted = SORT_BY_PHONE;
            break;
        case ESC: return 0;
        default:
            break;
        }
    }
}

/*Заполнение массива случайными ISQ номерами*/
void fillArrayRandomIsqNumbers(int icqArray[], char arrayLength)
{
    char const cipherInIcqNumber = 9;                //длина номера ICQ
    arrayFillRandom(icqArray, arrayLength, cipherInIcqNumber);
}

/*Заполнение массива случайными телефонными номерами*/
void fillArrayRandomPhoneNumbers(int phoneArray[], char arrayLength)
{
    char const cipherInPhoneNumber = 7;              //длина телефонного номера
    arrayFillRandom(phoneArray, arrayLength, cipherInPhoneNumber);
}

/*Заполнение массива случайными числами*/
void arrayFillRandom(int array[], char arrayLength, char cipherInNumber)
{
    for (char i = 0; i < arrayLength; i++)
    {
        array[i] = getRandomNumber(cipherInNumber);
    }
}

/*Получение случайного числа*/
int getRandomNumber(char cipherInNumber)
{
    int randomNumber = 0;                            //Случайное число
    int cipherGrade = 1;                             //Разряд цифры
    for (char i = 0; i < cipherInNumber; i++)
    {
        char cipher;                                 //Цифра
        if (i == cipherInNumber - 1)                 //Исключение первого нуля в номере
        {
            cipher = rand() % 9 + 1;
        }
        else
        {
            cipher = rand() % 10;
        }
        randomNumber += cipher* cipherGrade;
        cipherGrade *= 10;
    }
    return randomNumber;
}
/*Сортировка массива (метод Шелла)*/
void arraySort(int needSortArray[], int dependentArray[], char arrayLength)
{
    for (int i = arrayLength / 2; i > 0; i /= 2)
    {
        for (int j = i; j < arrayLength; j++)
        {
            for (int k = j - i; ((k >= 0) && (needSortArray[k] > needSortArray[k + i])); k -= i)
            {
                replaseNumbers(&needSortArray[k], &needSortArray[k + i]);
                replaseNumbers(&dependentArray[k], &dependentArray[k + i]);
            }
        }
    }
}

/*Перестановка значений двух переменных*/
void replaseNumbers(int* firstNumber, int* secondNumber)
{
    *firstNumber += *secondNumber;
    *secondNumber = *firstNumber - *secondNumber;
    *firstNumber -= *secondNumber;
}

/*Вывод справочника на консоль*/
void printList(int firstArray[], int secondArray[], char arrayLength)
{
    for (char i = 0; i < arrayLength; i++)
    {
        printf("%9i", firstArray[i]);
        printf("%10i\n", secondArray[i]);
    }
}

/*Выбор сортуруемого массива*/
char choiceSortingArray()
{
    char pressKey = getch();                         //нажатая клавиша
    while (true)
    {
        switch (pressKey)
        {
        case SORT_BY_ICQ:
        case SORT_BY_PHONE:
        case ESC:
            showMenu();
            return pressKey;
        default:
            break;
        }
        pressKey = getch();
    }
}

/*Отображает меню*/
void showMenu()
{
    system("cls");
    printf("Choice the menu item.\n");
    printf("1\tSort by ICQ number.\n");
    printf("2\tSort by Phone number.\n");
    printf("ESC\tEXIT.\n\n");
    printf("%6s%12s\n", "ICQ", "Phone");
}

/*Переворачивание массива*/
void arrayRotate(int array[], char arrayLength)
{
    for (int i = 0; (i < arrayLength / 2) && (i != arrayLength - 1 - i); i++)
    {
        replaseNumbers(&array[i], &array[arrayLength - 1 - i]);
    }
}
