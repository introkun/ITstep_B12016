/*Задание 1:
Написать функцию, которая удаляет из строки символ с заданным номером.*/

#include <stdio.h>

void deleteChar(char str[], int size, int index);

int main()
{
	char str[200];
	printf("Enter a string: ");
	gets(str);

	int len = strlen(str);
	int index = 0;

	printf("Enter the number of the removed character: ");
	scanf("%d", &index);
	index -= 1;

	deleteChar(str, len, index);
}

void deleteChar(char str[], int size, int index)
{
	char str2[40];
	int i = 0;
	int j = 0;
	while (str[i])
	{
		if (i != index)
		{
			str2[j] = str[i];
			j++;
		}

		i++;
	}
	str2[size - 1] = '\0';
	printf("Result: %s\n", str2);
}