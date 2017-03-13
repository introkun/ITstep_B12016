/*
«адание 7.2
≈сть стопка оладий различного радиуса. ≈динственна¤ операци¤, проводима¤ с ними -
между любыми двум¤ суем лопатку и мен¤ем пор¤док оладий над лопаткой на обратный.
Ќеобходимо за минимальное количество операций таких отсортировать снизу- вверх по
убыванию радиуса.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CAKE_COUNT 10                       // олличество блинов
#define CAKE_MAX_SIZE 100                   //ћаксимальный размер блина

void getRandomArray(int array[], char arrayLength);
void printArray(int array[], char arrayLength);
int sortArrayDescending(int array[], char arrayLength);
void arrayRotate(int* array, char arrayLength);

int main()
{
    srand(time(0) * 1000);

    int cakeSizeArray[CAKE_COUNT];          //массив из размеров блинов
    getRandomArray(cakeSizeArray, CAKE_COUNT);
    printf("Cake disposition:\n");
    printArray(cakeSizeArray, CAKE_COUNT);
    printf("\n\n");
    printf("Rotations count: %i.\n\n", sortArrayDescending(cakeSizeArray, CAKE_COUNT));
}


/*—ортировка массива по убыванию*/
int sortArrayDescending(int array[], char arrayLength)
{
    int rotationCount = 0;                   // олличество переворотов
    for (int i = 0; i < arrayLength - 1; i++)
    {
        int biggestNumberPosition = i;       //номер наибольшего элемента массива
        for (int j = i + 1; j < arrayLength; j++)
        {
            if (array[j] > array[biggestNumberPosition])
            {
                biggestNumberPosition = j;
            }
        }
        if (biggestNumberPosition != i)
        {
            if (biggestNumberPosition != arrayLength)
            {
                /*переворачиваем часть массива начина¤ с наибольшего элемента,
                тем самым помеща¤ его в конец массива*/
                arrayRotate(&array[biggestNumberPosition], arrayLength - biggestNumberPosition);
                printArray(array, arrayLength);
            }
            /*переворачиваем часть массива начина¤ с текущего (первого неотсортированного) элемента,
            тем самым помеща¤ на его место наибольший неотсортированный элемент, сто¤щий в конце массива.*/
            arrayRotate(&array[i], arrayLength - i);
            printArray(array, arrayLength);
            printf("\n");
            rotationCount += 2;
        }
    }
    return rotationCount;
}

/*ѕереворачивание массива*/
void arrayRotate(int* array, char arrayLength)
{
    for (int i = 0; (i < arrayLength / 2) && (i != arrayLength - 1 - i); i++)
    {
        array[i] = array[i] + array[arrayLength - 1 - i];
        array[arrayLength - 1 - i] = array[i] - array[arrayLength - 1 - i];
        array[i] = array[i] - array[arrayLength - 1 - i];
    }
}

/*«аполнение массива случайными числами*/
void getRandomArray(int array[], char arrayLength)
{
    for (char i = 0; i < arrayLength; i++)
    {
        array[i] = rand() % CAKE_MAX_SIZE + 1;
    }
}

/*¬ывод массива на консоль*/
void printArray(int array[], char arrayLength)
{
    for (char i = 0; i < arrayLength; i++)
    {
        printf("%-3i ", array[i]);
    }
    printf("\n");
}
