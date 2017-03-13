/*Задание 2:
Написать функцию, которая удаляет из строки все вхождения в нее заданного символа.
*/

#include <stdio.h>
#include <string.h>

#define STRING_MAX_LENGTH 128

void delateSymbolInString(char* string, char delatedSymbol);

int main()
{
    char enteringString[STRING_MAX_LENGTH] = "";  //Исходный текст
    printf("Please enter the some string.\n");
    gets(enteringString);                         //считывание текста включая пробелы

    char delaitedSymbol;                          //удаляемый из строки символ
    printf("Enter the symbol which you want to delete from string: ");
    scanf("%c", &delaitedSymbol);
    printf("\n");

    delateSymbolInString(&enteringString, delaitedSymbol);
    printf("Rezult string:\n%s\n\n", enteringString);
}

/*Удаляет из строки все вхождения заданного символа.
Возвращает колличество удаленных сиволов.*/
void delateSymbolInString(char* string, char delatedSymbol)
{
    int countOfDeletedSymbol = 0;                //счетчик удаляемых символов в строке
    for (int i = 0; (i <= strlen(string)); i++)
    {
        if (string[i] == delatedSymbol)
        {
            countOfDeletedSymbol++;
        }
        else
        {
            string[i - countOfDeletedSymbol] = string[i];
        }
    }
}