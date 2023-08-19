#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char* argv[])
{
	int c;
	int temp;
	int cnt = 0;
	FILE* fr = NULL;
	FILE* fw = NULL;

	if (argc != 3)
	{
		printf("Usage : %s FileName\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	char output[50] = { 0, };


	if ((fr = fopen(argv[1], "r")) == NULL)
	{
		printf("Can't open %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	strcpy(output, argv[1]);
	strcat(output, "+DONE.txt");

	if ((fw = fopen(output, "w")) == NULL)
	{
		printf("Can't open %s\n", output);
		exit(1);
	}

	while ((c = fgetc(fr)) != EOF)
	{
		fputc(c, stdout);
		fputc(c, fw);
		temp = fgetc(fr);

		if ((isalpha(c) != 0) && (temp == '\n'))
		{
			fprintf(stdout, " ");
			fprintf(fw, " ");
			fseek(fr, 3L, SEEK_CUR);
		}
		if (feof(fr)) break;

		fseek(fr, -1L, SEEK_CUR);
		cnt++;
	}

	fprintf(fw, "\nFile %s : Total characters = %d", argv[2], cnt);

	fclose(fr);
	fclose(fw);

	return 0;
}