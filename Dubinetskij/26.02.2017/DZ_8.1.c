/*Задание 1
Написать программу, которая содержит функцию Action, принимающую в качестве
аргумента, указатели на два массива(А и В) и размеры массивов, а также указатель на
функцию.
Пользователю отображается меню, в котором он может выбрать max, min, avg.
Если выбран max - передается указатель на функцию, которая ищет максимум, если
выбран min - передается указатель на функцию, которая ищет минимум, если выбран avg -
передается указатель на функцию, которая ищет среднее.
Возвращаемое значение функции Action результат выбора пользователя max, min, avg.
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

#define FIRST_ARRAY_LENGTH 12
#define SECOND_ARRAY_LENGTH 10
#define MIN '1'
#define MAX '2'
#define AVERAGE '3'
#define ARRAYS_CHANGE '0'
#define ESC '\x1b'

void printArray(int* array, char arrayLength);
char menuChoice();
void showMenu();
int getRezultOfChoiceAction(int* firstArray, char firstArrayLength, int* secondArray, char secondArrayLength, int(*findMinMaxOrAverageNumber)(int*, char, int*, char));
int minNumberOfTwoArrays(int* firstArray, char firstArrayLength, int* secondArray, char secondArrayLength);
int maxNumberOfTwoArrays(int* firstArray, char firstArrayLength, int* secondArray, char secondArrayLength);
int averageOfTwoArays(int* firstArray, char firstArrayLength, int* secondArray, char secondArrayLength);
int arrayMinNumber(int* array, char arrayLength);
int arrayMaxNumber(int* array, char arrayLength);
int arrayAverageValue(int* array, char arrayLength);
void fillRandomArray(int* array, char arrayLength);


int main()
{
    srand(time(0) * 1000);

    int firstArray[FIRST_ARRAY_LENGTH];                     //Первый массив
    int secondArray[SECOND_ARRAY_LENGTH];                   //Второй массив

    fillRandomArray(&firstArray, FIRST_ARRAY_LENGTH);
    fillRandomArray(&secondArray, SECOND_ARRAY_LENGTH);
    int(*actions)(int*, char, int*, char);                  //Указатель на функцию, принимающую 2 массива и их длины 

    char choicingPointOfMenu = NULL;                        //Выбранный пункт меню

    while (true)
    {
        /*Если пункты меню уже выбирались, т.е. на экране уже отображено меню*/
        if (choicingPointOfMenu != NULL)
        {
            choicingPointOfMenu = menuChoice();
        }

        system("cls");
        printf("First array:\t");
        printArray(&firstArray, FIRST_ARRAY_LENGTH);
        printf("Second array:\t");
        printArray(&secondArray, SECOND_ARRAY_LENGTH);
        printf("\n");
        showMenu();

        /*если после заполнения массивов пункты меню еще не выбирались*/
        if (choicingPointOfMenu == NULL)
        {
            choicingPointOfMenu = menuChoice();
        }

        switch (choicingPointOfMenu)
        {
        case MIN:
            printf("Minimum number of both arrays: ");
            actions = minNumberOfTwoArrays;
            break;
        case MAX:
            printf("Maximum number of both arrays: ");
            actions = maxNumberOfTwoArrays;
            break;
        case AVERAGE:
            printf("Average value of both arrays: ");
            actions = averageOfTwoArays;
            break;
        case ARRAYS_CHANGE:
            fillRandomArray(&firstArray, FIRST_ARRAY_LENGTH);
            fillRandomArray(&secondArray, SECOND_ARRAY_LENGTH);
            choicingPointOfMenu = NULL;
           continue;
        case ESC:
            return 0;
        default:
            break;
        }
        getRezultOfChoiceAction(&firstArray, FIRST_ARRAY_LENGTH, &secondArray, SECOND_ARRAY_LENGTH, actions);
    }

}

/*Функция Action из задания.
Вывод результата выбранной операции, принимает указатели на 2 массива, их длины и указатель на функцию*/
int getRezultOfChoiceAction(int* firstArray, char firstArrayLength, int* secondArray, char secondArrayLength, int(*findMinMaxOrAverageNumber)(int*, char, int*, char))
{
    printf("%i\n", (*findMinMaxOrAverageNumber)(firstArray, firstArrayLength, secondArray, secondArrayLength));
}

/*Определяет минимальное число в двух массивах*/
int minNumberOfTwoArrays(int* firstArray, char firstArrayLength, int* secondArray, char secondArrayLength)
{
    int minOfFirstArray = arrayMinNumber(firstArray, firstArrayLength);      //минимальное число в первом массиве
    int minOfSecondArray = arrayMinNumber(secondArray, secondArrayLength);   //минимальное число во втором массиве

    return minOfFirstArray < minOfSecondArray ? minOfFirstArray : minOfSecondArray;
}

/*Определяет максимальное число в двух массивах*/
int maxNumberOfTwoArrays(int* firstArray, char firstArrayLength, int* secondArray, char secondArrayLength)
{
    int maxOfFirstArray = arrayMaxNumber(firstArray, firstArrayLength);      //максимальное число в первом массиве
    int maxOfSecondArray = arrayMaxNumber(secondArray, secondArrayLength);   //максимальное число во втором массиве

    return maxOfFirstArray > maxOfSecondArray ? maxOfFirstArray : maxOfSecondArray;
}

/*Определяет среднее значение двух массивов*/
int averageOfTwoArays(int* firstArray, char firstArrayLength, int* secondArray, char secondArrayLength)
{
    return (arrayAverageValue(firstArray, firstArrayLength) + arrayAverageValue(secondArray, secondArrayLength)) / 2;
}

/*Нахождение минимального числа в массиве*/
int arrayMinNumber(int* array, char arrayLength)
{
    int min = array[0];          //минимальное число в массиве            
    for (char i = 1; i < arrayLength; i++)
    {
        if (array[i] < min)
        {
            min = array[i];
        }
    }
    return min;
}

/*Нахождение максимального числа в массиве*/
int arrayMaxNumber(int* array, char arrayLength)
{
    int max = array[0];        //максимальное число в массиве
    for (char i = 1; i < arrayLength; i++)
    {
        if (array[i] > max)
        {
            max = array[i];
        }
    }
    return max;
}

/*Нахождение среднего арифметического чисел массива*/
int arrayAverageValue(int* array, char arrayLength)
{
    int summ = 0;            //сумма чисел массива
    for (char i = 0; i < arrayLength; i++)
    {
        summ += array[i];
    }
    return summ / arrayLength;
}

/*Отобрзить меню*/
void showMenu()
{
    printf("1\tFind minimum number\n");
    printf("2\tFind maximum number\n");
    printf("3\tFind average of array\n\n");
    printf("0\tChange the arrays\n");
    printf("ESC\tEXIT.\n\n");
}

/*Выбор пункта меню*/
char menuChoice()
{
    char pressKey = getch();            //нажатая клавиша
    while (true)
    {
        switch (pressKey)
        {
        case MIN:
        case MAX:
        case AVERAGE:
        case ESC:
        case ARRAYS_CHANGE:
            return pressKey;
        default:
            break;
        }
        pressKey = getch();
    }
}

/*Заполнение массива случайными числами*/
void fillRandomArray(int* array, char arrayLength)
{
    for (char i = 0; i < arrayLength; i++)
    {
        array[i] = rand() % 1000;
    }
}

/*Вывод массива на консоль*/
void printArray(int* array, char arrayLength)
{
    for (char i = 0; i < arrayLength; i++)
    {
        printf("%5i", array[i]);
    }
    printf("\n");
}
