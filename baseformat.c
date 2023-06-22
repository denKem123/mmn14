#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEEP_ONLY_12_LSB(value) ((value)&0xFFF)
#define KEEP_ONLY_6_LSB(value) ((value)&0x3F)

struct base64
{
	char c;
	long num;
};

/**
 * A lookup table for opcode by command name
 */
static struct base64 base64_table[] = {
	{'A', 0},
	{'B', 1},
	{'C', 2},
	{'D', 3},
	{'E', 4},
	{'F', 5},
	{'G', 6},
	{'H', 7},
	{'I', 8},
	{'J', 9},
	{'K', 10},
	{'L', 11},
	{'M', 12},
	{'N', 13},
	{'O', 14},
	{'P', 15},
	{'Q', 16},
	{'R', 17},
	{'S', 18},
	{'T', 19},
	{'U', 20},
	{'V', 21},
	{'W', 22},
	{'X', 23},
	{'Y', 24},
	{'Z', 25},
	{'a', 26},
	{'b', 27},
	{'c', 28},
	{'d', 29},
	{'e', 30},
	{'f', 31},
	{'g', 32},
	{'h', 33},
	{'i', 34},
	{'j', 35},
	{'k', 36},
	{'l', 37},
	{'m', 38},
	{'n', 39},
	{'o', 40},
	{'p', 41},
	{'q', 42},
	{'r', 43},
	{'s', 44},
	{'t', 45},
	{'u', 46},
	{'v', 47},
	{'w', 48},
	{'x', 49},
	{'y', 50},
	{'z', 51},
	{'0', 52},
	{'1', 53},
	{'2', 54},
	{'3', 55},
	{'4', 56},
	{'5', 57},
	{'6', 58},
	{'7', 59},
	{'8', 60},
	{'9', 61},
	{'+', 62},
	{'/', 63},
	{'\0', 64},
};

char *decimal_to_64(long number)
{
	char* base_64 = (char*)malloc(3);
	struct base64 *e;

	for (e = base64_table; e->num < 64; e++)
	{
		if (e->num == KEEP_ONLY_6_LSB(number >> 6))
		{
			base_64[0] = e->c;
			break;
		}
	}
	for (e = base64_table; e->num < 64; e++)
	{
		if (e->num == KEEP_ONLY_6_LSB(number))
		{
			base_64[1] = e->c;
			break;
		}
	}

	base_64[2] = '\0';

	return base_64;
}