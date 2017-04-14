/*Задание 2:  
Написать функцию, которая удаляет из строки все вхождения в нее заданного символа.  */

#include <stdio.h>
#define STRING_SIZE 100

void squeeze(char removeString[], int deleteChar);

int main()
{
	char removeString[STRING_SIZE];
	int i;
	int number;
	printf("Type in a word in which you want to remove the symbol (max 100 characters): ");
	gets(removeString);
	printf("Enter the character to delete: ");

	number = getchar();

	squeeze(removeString, number);

	printf("Result:");
	puts(removeString);
}

void squeeze(char removeString[], int deleteChar)
{
	int j;

	for (int i = j = 0; removeString[i] != '\0'; i++)
	{
		if (removeString[i] != deleteChar)
		{
			removeString[j++] = removeString[i];
		}
	}
	removeString[j] = '\0';
}