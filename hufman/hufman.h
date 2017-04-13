#ifndef HUFMAN_H
#define HUFMAN_H
#define _CRT_SECURE_NO_WARNINGS
#define ERROR_INPUT_FILE_OPEN -1
#define ERROR_OUTPUT_FILE_OPEN -2
#define ERROR_BUFFER -3
#define ERROR_READ -4
#define ERROR_WRITE -5
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int copy_file(void);
int add_file(char* filename);
int exec_file(char* filenamearg);
int crc32(char* filename);
int num_sym(char* filename);
int num_frequency(char* filename);
#endif // !HUFMAN_H#pragma once
