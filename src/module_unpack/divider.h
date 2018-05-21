#pragma once

#include <iostream>
#include "windows.h"

#define SIZE_BUF 1024 * 128

//#define ERROR_FIRST_PARAM 1
#define ERROR_NO_FOUND_PATH 2
//#define ERROR_NOT_CREATE_FILE 3
//#define ERROR_WRONG_NUMBER_PARAM 4
#define ERROR_NOT_FOLDER 5
#define ERROR_NOT_OPEN_FILE 6
#define ERROR_NOT_FILE 7
#define ERROR_NOT_CREATE_DIR 8
//#define SHOW_HELP 9

uint8_t before_divide(const wchar_t* path, const wchar_t* filename);



