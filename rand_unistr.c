#include <stdio.h>
#include <stdlib.h>

#define RAND_RANGE(x, y) (rand() % (y - x + 1) + x)

typedef struct {
	unsigned short min, max;
} range_t;

static range_t ranges[] = {
	{ 33,    126   }, // Standard ASCII
	{ 913,   974   }, // Greek
	{ 1040,  1103  }, // Cryllic
	{ 8544,  8571  }, // Roman Numerals
	{ 9312,  9331  }, // Circled Numbers
	{ 12032, 12245 }, // Kanji
	{ 12288, 12333 }, // Random characters
	{ 12353, 12538 }, // Hiragana & Katakana
	{ 13312, 19893 }, // Kanji
	{ 19968, 40898 }, // Kanji
	{ 44032, 55203 }, // Hangul? I think it's called that
	{ 65296, 65376 }  // Full-width ASCII
};
#define TOTAL_RANGES 12

char* to_utf8 (unsigned long c) {
	unsigned long uc = 0x00000000 | (c & 0xFFFF);
	char* ret        = NULL;

	if (uc <= 0x7F) {
		ret    = malloc(2);
		ret[0] = uc                % 0x80;
		ret[1] = '\0';
	} else if (uc <= 0x7FF) {
		ret    = malloc(3);
		ret[0] = 0xC0 + (uc >>  6) % 0x20;
		ret[1] = 0x80 +  uc        % 0x40;
		ret[2] = '\0';
	} else if (uc <= 0xFFFF) {
		ret    = malloc(4);
		ret[0] = 0xE0 + (uc >> 12) % 0x10;
		ret[1] = 0x80 + (uc >>  6) % 0x40;
		ret[2] = 0x80 +  uc        % 0x40;
		ret[3] = '\0';
	} else if (uc <= 0x1FFFFF) {
		ret    = malloc(5);
		ret[0] = 0xF0 + (uc >> 18) % 0x8;
		ret[1] = 0x80 + (uc >> 12) % 0x40;
		ret[2] = 0x80 + (uc >>  6) % 0x40;
		ret[3] = 0x80 +  uc        % 0x40;
		ret[4] = '\0';
	} else if (uc <= 0x3FFFFFF) {
		ret    = malloc(6);
		ret[0] = 0xF8 + (uc >> 24) % 0x4;
		ret[1] = 0x80 + (uc >> 18) % 0x40;
		ret[2] = 0x80 + (uc >> 12) % 0x40;
		ret[3] = 0x80 + (uc >>  6) % 0x40;
		ret[4] = 0x80 +  uc        % 0x40;
		ret[5] = '\0';
	} else if (uc <= 0x7FFFFFFF) {
		ret    = malloc(7);
		ret[0] = 0xFC + (uc >> 30) % 0x2;
		ret[1] = 0x80 + (uc >> 24) % 0x40;
		ret[2] = 0x80 + (uc >> 18) % 0x40;
		ret[3] = 0x80 + (uc >> 12) % 0x40;
		ret[4] = 0x80 + (uc >>  6) % 0x40;
		ret[5] = 0x80 +  uc        % 0x40;
		ret[6] = '\0';
	}
	return ret;
}

char* rndstr_uni (unsigned short len) {
	unsigned short n_len = (len + 2) * 4, c_len = 0;
	char* ret = malloc(n_len);
	ret[0] = '\0';

	char* tmp;
	for (unsigned short i = 0; i < len; ++i) {
		size_t str_len;

		if (RAND_RANGE(0, 10) <= 7) {
			tmp = malloc(2);
			tmp[0] = RAND_RANGE(33, 126);
			tmp[1] = '\0';
			str_len = 1;
		} else {
			unsigned short c_range = RAND_RANGE(0, TOTAL_RANGES - 1);
			tmp = to_utf8(RAND_RANGE(ranges[c_range].min, ranges[c_range].max));
			str_len = strlen(tmp);
		}

		strcat(ret, tmp);
		c_len += str_len;
	}

	ret[c_len] = '\0';
	free(tmp);
	return ret;
}

int main (void) {
	srand((unsigned int)time(NULL));
	printf ("%s\n", rndstr_uni(RAND_RANGE(5, 15)));
	return 0;
}
