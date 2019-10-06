/**
 * Copyright - Shreenidhi Shedi <yesshedi@gmail.com>
 *
 * Share and feel free to use, it's free like in freedom.
 * Please do not use this code for any kind of monetory benifits.
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_COLS	5
#define NUM_CHARS	11
#define WIDTH		10

char sp[] = "\
\n\
\n\
\n\
\n\
\n";

char pound[] = "\
\n\
  #  #\n\
########\n\
#######\n\
 #  #";

char uk[] = "\
#\n\
 #\n\
\n\
\n\
\n";

char ex[] = "\
    #\n\
    #\n\
    #\n\
     \n\
    #";

char dol[] = "\
 ####\n\
# #\n\
 ###\n\
  # #\n\
####";

char per[] = "\
 ##    #\n\
#  #  #\n\
 ## # ##\n\
   # #  #\n\
 #    ##";

char amp[] = "\
  ###\n\
 #\n\
 ###\n\
#   ##\n\
######";

char sq[] = "\
#\n\
#\n\
\n\
\n\
\n";

char dq[] = "\
##\n\
##\n\
\n\
\n\
\n";

char opar[] = "\
 #\n\
#\n\
#\n\
#\n\
 #";

char cpar[] = "\
#\n\
 #\n\
 #\n\
 #\n\
#";

char ast[] = "\
  #\n\
 ###\n\
#####\n\
 ###\n\
  #";

char plus[] = "\
  #\n\
  #\n\
#####\n\
  #\n\
  #";

char comma[] = "\
      \n\
      \n\
      \n\
      \n\
      ##";

char minus[] = "\
      \n\
      \n\
######\n\
      \n\
      \n";

char fstop[] = "\
     \n\
     \n\
     \n\
     \n\
     #";

char fslash[] = "\
     #\n\
    #\n\
   #\n\
  #\n\
 #";

char bslash[] = "\
 #\n\
  #\n\
   #\n\
    #\n\
     #";

char colon[] = "\
    #\n\
     \n\
     \n\
     \n\
    #";

char semicolon[] = "\
    #\n\
     \n\
     \n\
    #\n\
    #";

char oang[] = "\
   #\n\
  #\n\
 #\n\
  #\n\
   #";

char cang[] = "\
 #\n\
  #\n\
   #\n\
  #\n\
 #";

char eq[] = "\
\n\
 #####\n\
\n\
 #####\n\
\n";

char ques[] = "\
  ###\n\
 #   #\n\
    # \n\
   #\n\
   #";

char at[] = "\
  ###\n\
 # ###\n\
 ##   #\n\
 # ###\n\
  ####";

char osqb[] = "\
 ###\n\
 #\n\
 #\n\
 #\n\
 #\n\
 ###";

char csqb[] = "\
 ###\n\
   #\n\
   #\n\
   #\n\
   #\n\
 ###";

char cap[] = "\
     #\n\
   #  #\n\
  #    #\n\
\n\
\n";

char und[] = "\
\n\
\n\
\n\
\n\
#####";

char oflw[] = "\
   ###\n\
  #\n\
 ##\n\
  #\n\
   ###";

char cflw[] = "\
 ###\n\
    #\n\
     ##\n\
    #\n\
 ###";

char or[] = "\
 #\n\
 #\n\
 #\n\
 #\n\
 #";

char tilde[] = "\
\n\
\n\
  ###   #\n\
 #   ###\n\
\n";

char zero[] = "\
 ####\n\
#    #\n\
# ## #\n\
#    #\n\
 ####";

char one[] = "\
 ##\n\
# #\n\
  #\n\
  #\n\
#####";

char two[] = "\
 ###\n\
#   #\n\
    #\n\
  ##\n\
######";

char three[] = "\
 ###\n\
#   #\n\
  ###\n\
#   #\n\
 ###";

char four[] = "\
   ##\n\
  # #\n\
 #  #\n\
######\n\
    #";

char five[] = "\
#####\n\
#\n\
#####\n\
     #\n\
#####";

char six[] = "\
  ###\n\
##\n\
######\n\
#    #\n\
 ####";

char seven[] = "\
######\n\
     #\n\
    #\n\
   #\n\
  #";

char eight[] = "\
 ####\n\
#    #\n\
######\n\
#    #\n\
 ####";

char nine[] = "\
#####\n\
#   #\n\
#####\n\
    #\n\
#####";

char a[] = "\
 #####\n\
 #   #\n\
 #####\n\
 #   #\n\
 #   #";

char b[] = "\
 #####\n\
  #  #\n\
  ####\n\
  #  #\n\
 #####";

char c[] = "\
  ####\n\
 #\n\
 #\n\
 #\n\
  ####";

char d[] = "\
 #####\n\
  #   #\n\
  #   #\n\
  #   #\n\
 #####";

char e[] = "\
 #####\n\
 #\n\
 #####\n\
 #\n\
 #####";

char f[] = "\
 #####\n\
 #\n\
 #####\n\
 #\n\
 #";

char g[] = "\
 #####\n\
 #\n\
 #  ##\n\
 #   #\n\
 #####";

char h[] = "\
 #   #\n\
 #   #\n\
 #####\n\
 #   #\n\
 #   #";

char i[] = "\
 #####\n\
   #\n\
   #\n\
   #\n\
 #####";

char j[] = "\
 #####\n\
     #\n\
     #\n\
     #\n\
 ####";

char k[] = "\
 #    #\n\
 #   #\n\
 # ##\n\
 #   #\n\
 #    #";

char l[] = "\
 #\n\
 #\n\
 #\n\
 #\n\
 ######";

char m[] = "\
##   ##\n\
# # # #\n\
#  #  #\n\
#     #\n\
#     #";

char n[] = "\
##    #\n\
# #   #\n\
#  #  #\n\
#   # # \n\
#    ##";

char o[] = "\
  ####\n\
 #    #\n\
 #    #\n\
 #    #\n\
  ####";

char p[] = "\
 #####\n\
  #   #\n\
  ####\n\
  #\n\
  #";

char q[] = "\
  ####\n\
 #    #\n\
 #    #\n\
  ####\n\
      #";

char r[] = "\
 #####\n\
  #   #\n\
  ####\n\
  #  #\n\
  #   #";

char s[] = "\
  ####\n\
 #\n\
  ###\n\
     #\n\
 ####";

char t[] = "\
 #####\n\
   #\n\
   #\n\
   #\n\
   #";

char u[] = "\
 #    #\n\
 #    #\n\
 #    #\n\
 #    #\n\
  ####";

char v[] = "\
#     #\n\
#     #\n\
 #   #\n\
  # #\n\
   #";

char w[] = "\
#     #\n\
#     #\n\
#  #  #\n\
# # # #\n\
##   ##";

char x[] = "\
 #    #\n\
  #  #\n\
   ##\n\
  #  #\n\
 #    #";

char y[] = "\
 #   #\n\
  # #\n\
   #\n\
   #\n\
   #";

char z[] = "\
 #####\n\
    #\n\
   #\n\
  #\n\
 #####";

char *alpha[] = {a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r,
		 s, t, u, v, w, x, y, z};

char *digit[] = {zero, one, two, three, four, five, six, seven, eight, nine};

char *punct1[] = {ex, dq, pound, dol, per, amp, sq, opar, cpar, ast, plus, comma,
		 minus, fstop, fslash};

char *punct2[] = {colon, semicolon, oang, eq, cang,ques, at};

char *punct3[] = {osqb, bslash, csqb, cap, und, uk};

char *punct4[] = {oflw, or, cflw, tilde};

int32_t _print_str(char *str, int32_t len)
{
	char *pbuf;
	int32_t row;
	int size = len << 4;
	int32_t ret = EXIT_FAILURE;

	pbuf = malloc(size);
	if (!pbuf)
		return EXIT_FAILURE;

	for (row = 0; row < NUM_COLS; row++) {
		int32_t j;
		char *pbufptr = pbuf;

		memset(pbuf, '\0', size);

		for (j = 0; j < len; j++) {
			char *ptr;
			int32_t k = row;

			if (isalpha(str[j])) {
				ptr = alpha[toupper(str[j]) - 'A'];
			} else if (isspace(str[j])) {
				ptr = sp;
			} else if (isdigit(str[j])) {
				ptr = digit[str[j] - '0'];
			} else if (ispunct(str[j])) {
				if (str[j] >= '!' && str[j] <= '/')
					ptr = punct1[str[j] - '!'];
				else if (str[j] >= ':' && str[j] <= '@')
					ptr = punct2[str[j] - ':'];
				else if (str[j] >= '[' && str[j] <= '`')
					ptr = punct3[str[j] - '['];
				else if (str[j] >= '{' && str[j] <= '~')
					ptr = punct4[str[j] - '{'];
			} else {
				printf("%c : %d\n", str[j], str[j]);
				goto end;
			}

			while (k) {
				if (*ptr++ == '\n')
					k--;
			}

			for (k = 0; *ptr && (*ptr != '\n'); k++)
				*pbufptr++ = *ptr++;

			if (k < WIDTH) {
				k = WIDTH - k;
				memset(pbufptr, ' ', k);
				pbufptr += k;
			}
		}

		printf("%s\n", pbuf);
	}

	printf("\n\n");

	ret = EXIT_SUCCESS;

end:
	free(pbuf);

	return ret;
}

int32_t handle_lengthy_str(char *str, int32_t len)
{
	int32_t tlen;
	char s[NUM_CHARS];

	do {
		tlen = (len >= sizeof(s)) ? (sizeof(s) - 1) : len;

		strncpy(s, str, tlen);
		str += tlen;
		s[tlen] = '\0';
		len -= tlen;

		if (_print_str(s, tlen))
			return EXIT_FAILURE;

	} while (len);

	return EXIT_SUCCESS;
}

int32_t print_str(char *str)
{
	char *_str;
	char *token;
	int32_t len = strlen(str);

	_str = malloc(sizeof(char) * len);
	if (!_str) {
		fprintf(stderr, "Err: %s : %d\n", __func__, __LINE__);
		return EXIT_FAILURE;
	}

	strcpy(_str, str);

	token = strtok(_str, " ");
	while (token) {
		int32_t ret;

		len = strlen(token);
		ret = (len >= NUM_CHARS) ? handle_lengthy_str(token, len) :
					   _print_str(token, len);

		if (ret) {
			fprintf(stderr, "Error: %s : %d\n", __func__, __LINE__);
			goto end;
		}

		token = strtok(NULL, " ");
	}

end:
	free(_str);

	return EXIT_SUCCESS;
}

int32_t main(int32_t argc, char **argv)
{
	char *ptr;
	char str[32] = "Hello ";

	strcat(str, getenv("USER"));

	ptr = (argv[1]) ? argv[1] : str;

	return print_str(ptr);
}
