#include "hufman.h"


int copy_file(void) {
	FILE *in, *out;

	in = fopen("ms.exe", "rb");
	if (in == NULL) {
		printf("Can't open input file\n");
		//getch();
		exit(ERROR_INPUT_FILE_OPEN);
	}

	out = fopen("mscopy.exe", "wb");
	if (out == NULL) {
		printf("Can't open output file\n");
		//getch();
		exit(ERROR_OUTPUT_FILE_OPEN);
	}

	fseek(in, 0, SEEK_END);
	long long bytesize = ftell(in);
	long buffersize = 102400;
	if (buffersize > bytesize) buffersize = bytesize;
	rewind(in);
	char* buffer = (char*)malloc(sizeof(char)*buffersize);
	if (buffer == NULL) {
		printf("Buffer error\n");
		//getch();
		exit(ERROR_BUFFER);
	}

	while (bytesize > 0) {
		fread(buffer, 1, buffersize, in);
		fwrite(buffer, 1, buffersize, out);
		bytesize = bytesize - buffersize;
		if (buffersize > bytesize) buffersize = bytesize;
		printf("%lld\n", bytesize);
	}

	fclose(out);
	fclose(in);
	free(buffer);
	printf("Succes\n");
	//getch();
	return 0;
}

int add_file(char* filename) {
	FILE *in, *out;
	in = fopen(filename, "rb");
	if (in == NULL) {
		printf("Can't open input file\n");
		//getch();
		exit(ERROR_INPUT_FILE_OPEN);
	}

	out = fopen("arch.huf", "ab");
	if (out == NULL) {
		printf("Can't open output file\n");
		//getch();
		exit(ERROR_OUTPUT_FILE_OPEN);
	}

	fseek(in, 0, SEEK_END);
	long bytesize = ftell(in);
	long buffersize = 102400;
	if (buffersize > bytesize) buffersize = bytesize;
	rewind(in);
	char* buffer = (char*)malloc(sizeof(char)*buffersize);
	if (buffer == NULL) {
		printf("Buffer error\n");
		//getch();
		exit(ERROR_BUFFER);
	}

	//"namesizeinlong name offset
	long namesize = strlen(filename);

	fwrite(&namesize, sizeof(long), 1, out);
	fwrite(filename, 1, namesize, out);
	fwrite(&bytesize, sizeof(long), 1, out);

	int crc = crc32(filename);
	fwrite(&crc, sizeof(int), 1, out);

	while (bytesize > 0) {
		fread(buffer, 1, buffersize, in);
		fwrite(buffer, 1, buffersize, out);
		bytesize = bytesize - buffersize;
		if (buffersize > bytesize) buffersize = bytesize;
		printf("%lld\n", bytesize);
	}

	fclose(in);
	fclose(out);
	free(buffer);
	printf("Succes\n");
	//getch();
	return 0;

}

int exec_file(char* filenamearg) {

	FILE *in, *out;
	out = NULL;
	in = fopen("arch.huf", "rb");
	if (in == NULL) {
		printf("Can't open input file\n");
		//getch();
		exit(ERROR_INPUT_FILE_OPEN);
	}

	//fseek(in, 0, SEEK_END);
	//long bytesize = ftell(in);
	long bytesize;
	long namesize;
	char* filename = NULL;
	char* buffer = NULL;
	int crcNew, crcOld;
	//fwrite(&namesize, sizeof(long), 1, out);
	//fwrite(filename, 1, namesize, out);
	//fwrite(&bytesize, sizeof(long), 1, out);

	if (strcmp(filenamearg, "") != 0) {

		fread(&namesize, sizeof(long), 1, in);
		//printf("%ld", namesize);
		filename = (char*)malloc(sizeof(char) * (namesize));
		fread(filename, sizeof(char), namesize, in);
		filename[namesize] = '\0';
		fread(&bytesize, sizeof(long), 1, in);
		fread(&crcOld, sizeof(int), 1, in);
		//printf("%#.8X\n", crc);
		while (strcmp(filename, filenamearg) != 0) {
			fseek(in, bytesize, SEEK_CUR);
			// free(filename);
			fread(&namesize, sizeof(long), 1, in);
			//printf("%ld", namesize);
			filename = (char*)malloc(sizeof(char) * (namesize));
			fread(filename, sizeof(char), namesize, in);
			filename[namesize] = '\0';
			fread(&bytesize, sizeof(long), 1, in);
			fread(&crcOld, sizeof(int), 1, in);
		}

		long buffersize = 102400;
		if (buffersize > bytesize)buffersize = bytesize;
		buffer = (char*)malloc(sizeof(char)*buffersize);
		if (buffer == NULL) {
			printf("Buffer error\n");
			//getch();
			exit(ERROR_BUFFER);
		}

		out = fopen(filename, "wb");
		if (out == NULL) {
			printf("Can't open output file\n");
			//getch();
			exit(ERROR_OUTPUT_FILE_OPEN);
		}

		while (bytesize > 0) {
			fread(buffer, 1, buffersize, in);
			fwrite(buffer, 1, buffersize, out);
			bytesize = bytesize - buffersize;
			if (buffersize > bytesize) buffersize = bytesize;
			printf("%lld\n", bytesize);
		}
	}
	else {
		while (!feof(in)) {
			fread(&namesize, sizeof(long), 1, in);
			//printf("%ld", namesize);
			filename = (char*)malloc(sizeof(char) * (namesize));
			fread(filename, sizeof(char), namesize, in);
			filename[namesize] = '\0';
			fread(&bytesize, sizeof(long), 1, in);

			long buffersize = 102400;
			if (buffersize > bytesize)buffersize = bytesize;
			char* buffer = (char*)malloc(sizeof(char)*buffersize);
			if (buffer == NULL) {
				printf("Buffer error\n");
				exit(ERROR_BUFFER);
			}
			out = fopen(filename, "wb");
			if (out == NULL) {
				printf("Can't open output file\n");
				exit(ERROR_OUTPUT_FILE_OPEN);
			}

			while (bytesize > 0) {
				fread(buffer, 1, buffersize, in);
				fwrite(buffer, 1, buffersize, out);
				bytesize = bytesize - buffersize;
				if (buffersize > bytesize) buffersize = bytesize;
				printf("%lld\n", bytesize);
			}
			printf("success\n");

		}
	}

	fclose(in);
	fclose(out);
	free(buffer);
	
	crcNew = crc32(filename);
	if (crcNew == crcOld) {
		printf("Succes\n");
	    printf("%#.8X\n", crcOld);
	}
	//getch();
	return 0;
}