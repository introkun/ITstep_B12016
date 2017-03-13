/*Задание 1:
Написать функцию, которая удаляет из строки символ с заданным номером.
*/

#include <stdio.h>
#include <string.h>

#define STRING_MAX_LENGTH 128

void delateSymbolInString(char* string, int positionOfDelatedSymbol);

int main()
{
    char enteringString[STRING_MAX_LENGTH] = "";              //Исходный текст
    printf("Please enter the some string.\n");
    gets(enteringString);                       //считывание текста включая пробелы

    int numberOfDelaitedSymbol;                 //номер удаляемого символа
    printf("Enter the number of symbol which you want to delete (from 1 to %i): ", strlen(enteringString));
    scanf("%i", &numberOfDelaitedSymbol);
    printf("\n");

    delateSymbolInString(&enteringString, numberOfDelaitedSymbol);
    printf("Rezult string:\n%s\n\n", enteringString);
}

/*Удаляет из строки символ с заданным номером*/
void delateSymbolInString(char* string, int positionOfDelatedSymbol)
{
    for (int i = positionOfDelatedSymbol - 1; (i <= strlen(string)); i++)
    {
        string[i] = string[i + 1];
    }
}