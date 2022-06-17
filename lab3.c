#include <stdlib.h>

#include <stdio.h>
#include <string.h>




typedef struct person {
	char name[20];
	char surname[20];
	char sex[8];
	char position[20];
	unsigned int salary;
} person;

void string_into_data(char s[], int* k, char field[])
{

	int i = *k;
	while ((s[i] == ',') || (s[i] == '\"'))
	{
		i++;
	}
	int j = 0;
	while (s[i] != '\"')
	{
		field[j] = s[i];
		i++;
		j++;
	}
	field[j] = '\0';
	*k = i;
}




int main(int argc, char** argv) {
	FILE* fp;
	char s[255];

	int n = 0, i;
	person* data = NULL;
	person tmp;

	if (argc != 3) {
		printf("CSV scanner. Sort data by choosen position.\n Usage:\n csv.exe <filename> <position>\n");
		return 2;
	}

	if (NULL == (fp = fopen(argv[1], "r"))) {
		fprintf(stderr, "cannot open file '%s'", argv[1]);
		return 1;
	}
	if (!(fopen_s(&fp, argv[1], "r"))) {
		fgets(s, 255, fp);
		while (!feof(fp)) {
			fgets(s, 255, fp);
			data = (person*)realloc(data, (n + 1) * sizeof(person));
			i = 0;
			string_into_data(s, &i, data[n].name);
			string_into_data(s, &i, data[n].surname);
			string_into_data(s, &i, data[n].sex);
			string_into_data(s, &i, data[n].position);
			sscanf_s(&s[i + 3], "%d", &data[n].salary);
			n++;
		}
		fclose(fp);
	}
	int column = (int)argv[2];

	for (int i = 0; i < n - 1; i++) {
		switch (column) {
		case '1':
			for (int j = n - 1; j > i; j--) {
				if (strcmp(data[j].name, data[j - 1].name) < 0) {
					person tmp = data[j - 1];
					data[j - 1] = data[j];
					data[j] = tmp;
				}
			}
			break;
		case '2':
			for (int j = n - 1; j > i; j--) {
				if (strcmp(data[j].surname, data[j - 1].surname) < 0) {
					person tmp = data[j - 1];
					data[j - 1] = data[j];
					data[j] = tmp;
				}
			}
			break;
		case '3':
			for (int j = n - 1; j > i; j--) {
				if (strcmp(data[j].sex, data[j - 1].sex) < 0) {
					person tmp = data[j - 1];
					data[j - 1] = data[j];
					data[j] = tmp;
				}
			}
			break;
		case '4':
			for (int j = n - 1; j > i; j--) {
				if (strcmp(data[j].position, data[j - 1].position) < 0) {
					person tmp = data[j - 1];
					data[j - 1] = data[j];
					data[j] = tmp;
				}
			}
			break;
		case '5':
			for (int j = n - 1; j > i; j--) {
				if ((data[j].salary > data[j - 1].salary)) {
					person tmp = data[j - 1];
					data[j - 1] = data[j];
					data[j] = tmp;
				}
			}
			break;

		}
	}

	for (int f = 0; f < n - 1; f++) {
		printf("%s %s %s %s %u \n", data[f].name, data[f].surname, data[f].sex, data[f].position, data[f].salary);
	}





}