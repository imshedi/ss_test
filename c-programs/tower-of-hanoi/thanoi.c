#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "mempool.h"
#include "thanoi.h"

#ifdef CONFIG_RUN_TEST
static test_res_t *iRes;
static test_res_t *rRes;

int32_t init_test_data(int32_t lmt)
{
        if (lmt <= 0) {
                pr_err("Invalid parameter(s)\n");
                return -1;
        }

        lmt = 1 << lmt;

        iRes = (test_res_t *)malloc(lmt * sizeof(test_res_t));
        if (!iRes) {
                pr_err("malloc error\n");
                return -1;
        }

        rRes = (test_res_t *)malloc(lmt * sizeof(test_res_t));
        if (!iRes) {
                pr_err("malloc error\n");
                return -1;
        }

        return 0;
}

void fini_test_data(void)
{
        if (iRes) {
                free(iRes);
        }

        if (rRes) {
                free(rRes);
        }
}

void cmp_test_res(int32_t lmt)
{
        int32_t i;

        for (i = 0; i < lmt; i++) {
                if ((iRes[i].fm != rRes[i].fm) || (iRes[i].to != rRes[i].to)) {
                        printf("Failed: iRes[%d].fm = %c rRes[%d].fm = %c\n",
                                        i, iRes[i].fm, i, rRes[i].fm);

                        printf("Failed: iRes[%d].to = %c rRes[%d].to = %c\n",
                                        i, iRes[i].to, i, rRes[i].to);

                        return;
                }
        }

        printf("\n\n *** Success: Iterative & Recursive results are same ***\n\n");
}
#endif /* CONFIG_RUN_TEST */

hans_t *create_stack(int32_t lmt)
{
        hans_t *new_data;

        if (lmt <= 0) {
                pr_err("Invalid parameter(s)\n");
                return NULL;
        }

        new_data = (hans_t *)malloc(sizeof(hans_t));
        if (!new_data) {
                pr_err("malloc error: %s\n", strerror(errno));
                return NULL;
        }

        new_data->top = -1;
        new_data->max = lmt - 1;

        new_data->array = (int32_t *)malloc(lmt * sizeof(int32_t));
        if (!new_data->array) {
                pr_err("malloc error: %s\n", strerror(errno));
                free(new_data);
                return NULL;
        }

        return new_data;
}

bool isEmpty(hans_t *new_data)
{
        if (!new_data) {
                pr_err("Invalid parameter(s)\n");
                return false;
        }

        return (new_data->top == -1);
}

bool isFull(hans_t *new_data)
{
        if (!new_data) {
                pr_err("Invalid parameter(s)\n");
                return false;
        }

        return (new_data->top == new_data->max);
}

void display_shift(int32_t cnt, char fm, char to, int32_t disk)
{
        if (cnt <= 0 || disk <= 0) {
                pr_err("Invalid parameter(s)\n");
                return;
        }

#ifdef CONFIG_RUN_TEST
        iRes[cnt - 1].fm = fm;
        iRes[cnt - 1].to = to;
#endif /* CONFIG_RUN_TEST */

        printf("Step-%02d: Move disk %d from pole '%c' to pole '%c'\n",
                        cnt, disk, fm, to);
}

int32_t add_element(hans_t *new_data, int32_t item)
{
        if (!new_data) {
                pr_err("Invalid parameter(s)\n");
                return -1;
        }

        if (!isFull(new_data)) {
                new_data->array[++new_data->top] = item;
                return 0;
        }

        return -1;
}

int32_t remove_element(hans_t *new_data)
{
        if (!new_data) {
                pr_err("Invalid parameter(s)\n");
                return -1;
        }

        if (isEmpty(new_data)) {
                return-1;
        }

        return new_data->array[new_data->top--];
}

int32_t mv_disks(int32_t cnt, hans_t *s_tow, hans_t *d_tow, char src, char dst)
{
        int32_t ret;
        int32_t tow1;
        int32_t tow2;

        if (!s_tow || !d_tow) {
                pr_err("Invalid parameter(s)\n");
                return -1;
        }

        tow1 = remove_element(s_tow);
        tow2 = remove_element(d_tow);
        if (tow1 < 0) {
                ret = add_element(s_tow, tow2);
                if (ret < 0) {
                        pr_err("Failed to add_element\n");
                        return ret;
                }

                display_shift(cnt, dst, src, tow2);
        } else if (tow2 < 0) {
                ret = add_element(d_tow, tow1);
                if (ret) {
                        pr_err("Failed to add_element\n");
                        return ret;
                }

                display_shift(cnt, src, dst, tow1);
        } else if (tow1 > tow2) {
                ret = add_element(s_tow, tow1);
                if (ret) {
                        pr_err("Failed to add_element\n");
                        return ret;
                }

                ret = add_element(s_tow, tow2);
                if (ret) {
                        pr_err("Failed to add_element\n");
                        return ret;
                }

                display_shift(cnt, dst, src, tow2);
        } else {
                ret = add_element(d_tow, tow2);
                if (ret) {
                        pr_err("Failed to add_element\n");
                        return ret;
                }

                ret = add_element(d_tow, tow1);
                if (ret) {
                        pr_err("Failed to add_element\n");
                        return ret;
                }

                display_shift(cnt, src, dst, tow1);
        }

        return ret;
}

void _itowerOfHanoi(int lmt, hans_t *s_tow, hans_t *t_tow, hans_t *d_tow)
{
        int32_t cnt;
        int32_t shift;
        char tmp = TMP;
        char dst = DST;

        if (!s_tow || !t_tow) {
                pr_err("Invalid parameter(s)\n");
                return;
        }

        if (!(lmt & 1)) {
                tmp = DST;
                dst = TMP;
        }

        for (cnt = lmt; cnt; cnt--) {
                add_element(s_tow, cnt);
        }

        shift = (1 << lmt);
        for (cnt = 1; cnt < shift; cnt++) {
                int32_t ret;

                ret = mv_disks(cnt,
                                (cnt % 3) ? s_tow : t_tow,
                                ((cnt % 3) != 2) ? d_tow : t_tow,
                                (cnt % 3) ? SRC : tmp,
                                ((cnt % 3) != 2) ? dst : tmp);

                if (ret) {
                        pr_err("mv_disks failed\n");
                        return;
                }
        }
}

void free_stack(hans_t *ptr)
{
        free(ptr->array);
        free(ptr);
}

int32_t itowerOfHanoi(int32_t lmt)
{
        hans_t *src;
        hans_t *dst;
        hans_t *tmp;
        int32_t ret = -1;

        if (lmt <= 0) {
                pr_err("Invalid parameter(s)\n");
                return ret;
        }

        printf("\nSequence of Disk Moves:\n\n");

        src = create_stack(lmt);
        if (!src) {
                pr_err("failed to create_stack\n");
                return ret;
        }

        tmp = create_stack(lmt);
        if (!tmp) {
                pr_err("failed to create_stack\n");
                goto tmp_err;
        }

        dst = create_stack(lmt);
        if (!dst) {
                pr_err("failed to create_stack\n");
                goto dst_err;
        }

        _itowerOfHanoi(lmt, src, tmp, dst);

        free_stack(dst);
        ret = 0;

dst_err:
        free_stack(tmp);

tmp_err:
        free_stack(src);

        return ret;
}

void rtowerOfHanoi(int32_t n, char fm, char tmp, char to)
{
        static int32_t cnt;

        if (n <= 0) {
                pr_err("Invalid parameter(s)\n");
                return;
        }

        if (cnt == ((1 << n) - 1)) {
                cnt = 0;
        }

        if (n <= 1) {
                if (!cnt) {
                        printf("\nSequence of Disk Moves:\n\n");
                }

#ifdef CONFIG_RUN_TEST
                rRes[cnt].fm = fm;
                rRes[cnt].to = to;
#endif /* CONFIG_RUN_TEST */

                printf("Step-%02d: Move disk %d from pole '%c' to pole '%c'\n",
                                ++cnt, n, fm, to);
                return;
        }

        rtowerOfHanoi(n - 1, fm, to, tmp);

#ifdef CONFIG_RUN_TEST
        rRes[cnt].fm = fm;
        rRes[cnt].to = to;
#endif /* CONFIG_RUN_TEST */

        printf("Step-%02d: Move disk %d from pole '%c' to pole '%c'\n", ++cnt,
                        n, fm, to);

        rtowerOfHanoi(n - 1, tmp, fm, to);
}

int32_t main(int32_t argc, char **argv)
{
        int32_t ret;
        int32_t lmt;

        if (argc != 2) {
                pr_err("Input argument error\n"
                                "\nExample:\n"
                                "\n%s <num_disks>\n\n" "\n%s 3\n\n", argv[0], argv[0]);

                return EXIT_FAILURE;
        }

        lmt = atoi(argv[1]);
        if (lmt <= 0) {
                pr_err("Invalid input\n");
                return EXIT_FAILURE;
        }

#ifdef CONFIG_RUN_TEST
        ret = init_test_data(lmt);
        if (ret) {
                pr_err("init_test_data failed\n");
                return EXIT_FAILURE;
        }
#endif /* CONFIG_RUN_TEST */

        printf("\n****** towerOfHanoi - Iterative ******\n");
        ret = itowerOfHanoi(lmt);
        if (ret)
                pr_err("towerOfHanoi - Iterative failed\n");

        printf("\n****** towerOfHanoi - Recursive ******\n");
        rtowerOfHanoi(lmt, SRC, TMP, DST);

#ifdef CONFIG_RUN_TEST
        cmp_test_res(lmt);
        fini_test_data();
#endif /* CONFIG_RUN_TEST */

        free_all_mem();

        return EXIT_SUCCESS;
}
