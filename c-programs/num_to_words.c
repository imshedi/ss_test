#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#define ROWS	32
#define COLS	32

char *getPositionValue(int32_t pos)
{
	switch (pos) {
	case 1:
		return "hundred";

	case 2:
		return "thousand";

	case 3:
		return "lakh";

	case 4:
		return "crore";

	case 5:
		return "arab";

	case 6:
		return "kharab";

	case 7:
		return "neel";

	case 8:
		return "padam";

	default:
		return "";
	}
}

char *digitToWord(uint32_t digit)
{
	switch (digit) {
	case 1:
		return "one";

	case 2:
		return "two";

	case 3:
		return "three";

	case 4:
		return "four";

	case 5:
		return "five";

	case 6:
		return "six";

	case 7:
		return "seven";

	case 8:
		return "eight";

	case 9:
		return "nine";

	case 10:
		return "ten";

	case 11:
		return "eleven";

	case 12:
		return "twelve";

	case 13:
		return "thirteen";

	case 14:
		return "fourteen";

	case 15:
		return "fifteen";

	case 16:
		return "sixteen";

	case 17:
		return "seventeen";

	case 18:
		return "eighteen";

	case 19:
		return "nineteen";

	case 20:
		return "twenty";

	case 30:
		return "thirty";

	case 40:
		return "fourty";

	case 50:
		return "fifty";

	case 60:
		return "sixty";

	case 70:
		return "seventy";

	case 80:
		return "eighty";

	case 90:
		return "ninety";

	default:
		return "";
	}
}

void toWord(int32_t i, uint32_t num, int32_t pos, char word[][COLS])
{
	if (!num)
		goto end;

	if (!pos)
		strcat(word[i], "and ");

	if ((num < 20) || !(num % 10)) {
		strcat(word[i], digitToWord(num));
	} else {
		strcat(word[i], digitToWord((num / 10) * 10));
		strcat(word[i], " ");
		strcat(word[i], digitToWord(num % 10));
	}

end:
	strcat(word[i], " ");
	strcat(word[i], getPositionValue(pos));
	strcat(word[i], " ");
}

int32_t main(void)
{
	int8_t i;
	uint32_t number = 0;
	char word[ROWS][COLS] = {{0, 0}};

	printf("\nEnter any postive number: ");
	scanf("%u", &number);

	if (!number) {
		printf("Zero\n");
		return EXIT_SUCCESS;
	}

#if 0
	word = (char **)malloc(ROWS);
	if (!word) {
		fprintf(stderr, "malloc error(for rows)\n");
		return EXIT_FAILURE;
	}

	for (i = 0; i < ROWS; i++) {
		word[i] = (char *)malloc(COLS);
		if (!word[i]) {
			free(word);
			fprintf(stderr, "malloc error(for columns)\n");
			return EXIT_FAILURE;
		}
	}
#endif

	for (i = 0; number; i++) {
		int32_t div;

		div = (i != 1) ? 100 : 10;
		toWord(i, number % div, i, word);
		number /= div;
	}

	printf("\nNumber in words: ");
	for (i--, *word[i] -= 32; i >=0; i--) {
		printf("%s", word[i]);
	}
	printf("\n");

#if 0
	for (i = 0; i < COLS; i++)
		free(word[i]);
	free(word);
#endif

	return EXIT_SUCCESS;
}
