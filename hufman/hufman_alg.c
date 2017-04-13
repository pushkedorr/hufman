#include "hufman.h"


typedef struct Node {
	int data;
	int frequency;
	struct Node *left;
	struct Node *right;
	struct Node *parent;
} Node;


int num_sym(char* filename) {
	FILE *in;
	int counter=0;
	in = fopen(filename, "rb");
	if (in == NULL) {
		printf("Can't open file\n");
		exit(ERROR_BUFFER);
	}
	while (!feof(in)) {
		fgetc(in);
		counter++;
	}
	printf("%d\n", counter);
	return counter;
}

int num_frequency(char* filename) {
	FILE *in;
	int num;
	int i;
	in = fopen(filename, "rb");
	int mas[256] = { 0 };
	if (in == NULL) {
		printf("Can't open file\n");
		exit(ERROR_BUFFER);
	}
	while (!feof(in)) {
		num = fgetc(in);
		mas[num]++;
	}

	for (i = 0; i < 256; i++) {
		printf("%d:    %d\n", mas[i], i);
	}
	return 0;
}