#ifndef __T_HANOI_H__
#define __T_HANOI_H__

//#define CONFIG_RUN_TEST

#define SRC 'S'
#define TMP 'T'
#define DST 'D'

#define pr_err(...) \
	do { \
		fprintf(stderr, "%s->%s->%d\n", __FILE__, __func__, __LINE__); \
		fprintf(stderr, __VA_ARGS__); \
	} while (0)

#ifdef CONFIG_RUN_TEST
typedef struct _test_res_t {
	int32_t fm;
	int32_t to;
} test_res_t;
#endif /* CONFIG_RUN_TEST */

typedef struct _hans_t {
	int32_t max;
	int32_t top;
	int32_t *array;
} hans_t;

void free_stack(hans_t *ptr);
bool isFull(hans_t *new_data);
bool isEmpty(hans_t *new_data);
hans_t *create_stack(int32_t lmt);
int32_t itowerOfHanoi(int32_t lmt);
int32_t remove_element(hans_t *new_data);
int32_t add_element(hans_t *new_data, int32_t item);
void rtowerOfHanoi(int32_t n, char fm, char tmp, char to);
void display_shift(int32_t cnt, char fm, char to, int32_t disk);
void _itowerOfHanoi(int lmt, hans_t *src_tow, hans_t *tmp_tow, hans_t *dst_tow);

int32_t mv_disks(int32_t cnt, hans_t *s_tow, hans_t *d_tow, char src, char dst);

#ifdef CONFIG_RUN_TEST
void fini_test_data(void);
void cmp_test_res(int32_t lmt);
int32_t init_test_data(int32_t lmt);
#endif /* CONFIG_RUN_TEST */

#endif /* __T_HANOI_H__ */
