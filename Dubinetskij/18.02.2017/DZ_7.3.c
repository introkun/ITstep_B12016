/*
Задание 7.3
Используя два указателя на массив целых чисел, скопировать один массив в другой.
Использовать в программе арифметику указателей для продвижения по массиву, а также
оператор разыменования.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 10                       //Колличество элементов массива
#define MAX_NUMBER 100                      //Максимально возможный элемент массива

void getRandomArray(int* array, char arrayLength);
void copyArray(int* array, int* copiedArray, char arrayLength);
void printArray(int* array, char arrayLength);

int main()
{
    srand(time(0) * 1000);

    int firstArray[ARRAY_SIZE];             //первый массив
    getRandomArray(&firstArray, ARRAY_SIZE);
    printf("Fitst array:\t\t");
    printArray(&firstArray, ARRAY_SIZE);

    int secondArray[ARRAY_SIZE];            //второй массив
    copyArray(&secondArray, &firstArray, ARRAY_SIZE);
    printf("Second array (copy):\t");
    printArray(&secondArray, ARRAY_SIZE);
}

/*Заполнение массива случайными числами*/
void getRandomArray(int* array, char arrayLength)
{
    for (char i = 0; i < arrayLength; i++)
    {
        *(array + i) = rand() % MAX_NUMBER + 1;
    }
}

/*Копирование одного массива в другой*/
void copyArray(int* array, int* copiedArray, char arrayLength)
{
    for (char i = 0; i < arrayLength; i++)
    {
        *(array + i) = *(copiedArray + i);
    }
}

/*Вывод массива на консоль*/
void printArray(int* array, char arrayLength)
{
    for (char i = 0; i < arrayLength; i++)
    {
        printf("%-3i ", *(array + i));
    }
    printf("\n");
}
