/*Задание 2
Написать функцию, которая получает указатель на статический двумерный массив (3x5) и
его размер. Функция распределяет положительные, отрицательные и нулевые элементы в
3 отдельных массива, указатели на которые также переданы в функцию.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROW_COUNT 3
#define COLLUMN_COUNT 5
#define MAX_NUMBER_IN_ARRAY 100

void divideArrayToPositiveNegativeAndZiroNumbers(int** array[][COLLUMN_COUNT], char rowCount,
    int* arrayWithPositiveNumbers, int* arrayWithNegativeNumbers, int* arrayWithZiro,
    char* positiveNumberCount, char* negativeNumberCount, char* ziroCount);
void fillTwoDimensionalArrayWhithRandomNumbers(int** array[][COLLUMN_COUNT], char arrayRowCount);
void printTwoDimensionalArray(int** array[][COLLUMN_COUNT], char arrayRowCount);
void printArray(int* array, char arrayLength);

int main()
{
    srand(time(0) * 1000);

    int generatedArray[ROW_COUNT][COLLUMN_COUNT] = {0};            //сгенерированный случайный массив

    fillTwoDimensionalArrayWhithRandomNumbers(&generatedArray, ROW_COUNT);

    printf("Generated array:\n");
    printTwoDimensionalArray(&generatedArray, ROW_COUNT);

    int arrayWithPositiveNumbers[ROW_COUNT*COLLUMN_COUNT] = {0};   //массив положительных чисел
    int arrayWithNegativeNumbers[ROW_COUNT*COLLUMN_COUNT] = {0};   //массив отрицательных чисел
    int arrayWithZiro[ROW_COUNT*COLLUMN_COUNT] = {-1};             //массив из чисел равных нулю                  

    char positiveNumberCount = 0;                                  //счетчик положительных чисел в исходном массиве
    char negativeNumberCount = 0;                                  //счетчик отрицательных чисел в исходном массиве 
    char ziroCount = 0;                                            //счетчик нулевых элементов исходного массива

    divideArrayToPositiveNegativeAndZiroNumbers(&generatedArray, ROW_COUNT,
        &arrayWithPositiveNumbers, &arrayWithNegativeNumbers, &arrayWithZiro,
        &positiveNumberCount, &negativeNumberCount, &ziroCount);

    printf("Positive numbers:\n");
    printArray(&arrayWithPositiveNumbers, positiveNumberCount);
    printf("Negatibe numbers:\n");
    printArray(&arrayWithNegativeNumbers, negativeNumberCount);
    printf("Count ziro in array: %i\n\n", ziroCount);
}

/*Разбивает двумерный массив на одномерные массивы из положительных,
отрицательных и нулевых элементов исходного*/
void divideArrayToPositiveNegativeAndZiroNumbers(int** array[][COLLUMN_COUNT], char rowCount,
    int* arrayWithPositiveNumbers, int* arrayWithNegativeNumbers, int* arrayWithZiro,
    char* positiveNumberCount, char* negativeNumberCount, char* ziroCount)
{
    for (char i = 0; i < rowCount; i++)
    {
        for (char j = 0; j < COLLUMN_COUNT; j++)
        {
            int numberOfArray = *(*(array + i) + j);

            if (numberOfArray > 0)
            {
                arrayWithPositiveNumbers[(*positiveNumberCount)++] = numberOfArray;
            }
            else
            {
                if (numberOfArray < 0)
                {
                    arrayWithNegativeNumbers[(*negativeNumberCount)++] = numberOfArray;
                }
                else
                {
                    arrayWithZiro[(*ziroCount)++] = numberOfArray;
                }
            }
        }
    }
}

/*Запонение двумерного массива случайными числами*/
void fillTwoDimensionalArrayWhithRandomNumbers(int** array[][COLLUMN_COUNT], char arrayRowCount)
{
    for (char i = 0; i < arrayRowCount; i++)
    {
        for (char j = 0; j < COLLUMN_COUNT; j++)
        {
            *(*(array + i) + j) = rand() % (2 * MAX_NUMBER_IN_ARRAY) - MAX_NUMBER_IN_ARRAY;
        }
    }
}

/*Вывод двумерного массива на консоль*/
void printTwoDimensionalArray(int** array[][COLLUMN_COUNT], char arrayRowCount)
{
    for (char i = 0; i < arrayRowCount; i++)
    {
        for (char j = 0; j < COLLUMN_COUNT; j++)
        {
            printf("%5i", *(*(array + i) + j));
        }
        printf("\n");
    }
    printf("\n");
}

/*Вывод одномерного массива на консоль*/
void printArray(int* array, char arrayLength)
{
    for (char i = 0; i < arrayLength; i++)
    {
        printf("%i ", array[i]);
    }
    printf("\n\n");
}