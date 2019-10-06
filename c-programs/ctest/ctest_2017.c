#include "ctest.h"

static volatile bool check = false;

void sig_handler(int32_t signo)
{
    if (signo == SIGINT) {
        check = true;
        printf("\nReceived Ctrl-C, quitting now\n");
    }
}

void show_bits(int32_t num)
{
    int8_t i;

    for (i = 31; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
        if (!(i & 3))
            printf(" ");
    }
    printf("\n");
}

#if 0
extern char buf[8];
void extern_goof_up(void)
{
  printf("%s\n", buf);
}
#endif

#if 0
bool validate_mac(const char *mac)
{
    uint8_t i = 0;
    uint8_t s = 0;

    for ( ; *mac; mac++) {
        if (isxdigit(*mac)) {
            i++;
        } else if (*mac == ':') {
            if (!i || ((i >> 1) - 1 != s))
                break;
            s++;
        } else {
            break;
        }
    }

    return ((i == 12) && (s == 5));
}

void rm_colon_from_mac(void)
{
    uint8_t values[6] = {'\0'};
    char *mac = "C0:3F:D5:4D:89:28";

    if (!validate_mac(mac)) {
        printf("Invalid MAC\n");
        return;
    }

    int32_t ret;
    ret = sscanf(mac, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
                  &values[0], &values[1], &values[2],
                  &values[3], &values[4], &values[5]);
    if (6 != ret) {
        perror("sscanf() error\n");
        return;
    }

    for (ret = 0; ret < 6; ret++)
        printf("%hhx", values[ret]);

    printf("\n");
}
#endif

#if 0
#define LEN     64
#define DELAY   0xFFFF

void pr_sp(int32_t num)
{
    while (num--)
        printf(" ");
}

void rotate_msg(void)
{
    uint16_t i = 0;
    uint16_t cnt = 2;
    char *str = "Hello World";

    while (cnt) {
        pr_sp(i);
        printf("%s\r", str);

        if (LEN != ++i) {
            fflush(stdout);
            usleep(DELAY);
            continue;
        }

        while (--i) {
            pr_sp(i);
            printf("%s", str);
            pr_sp(i - (i - 1));
            printf("\r");
            fflush(stdout);
            usleep(DELAY);
        }
        cnt--;
    }
    printf("\n");
}
#endif

#if 0
#define RANGE           1000000U
#define APSUM(a, n)     (uint32_t)(((n) * (((a) << 1) + ((n) - 1) * a)) >> 1)

/* Sum of multiples of 3 & 5 in RANGE */
void multiples_sum(void)
{
    uint32_t sum = 0;

    sum += APSUM(3, (RANGE - 1) / 3);
    sum += APSUM(5, (RANGE - 1) / 5);
    sum -= APSUM(15, (RANGE - 1) / 15);

    printf("Sum = %u\n", sum);
}
#endif

#if 0
//the apostrophe ' causes a warning
#endif

#if 0
void array_pointer(void)
{
    char a[4];

    printf("1.%p\n", a);
    printf("2.%p\n", a + 1);
    printf("3.%p\n", &a);
    printf("4.%p\n", &a + 1);
}
#endif

#if 0
void string_literal_test(void)
{
    char *s1 = "hello";
    char s2[] = "world";

    s1 = s2;

    printf("%s\n", s1);
}
#endif

#if 0
void sizeof_use(void)
{
    struct t {
        int32_t a;
        struct t *p;
    };

    struct t *handle = NULL;

    printf("%d %d\n", sizeof(*handle), sizeof(handle));
}
#endif

#if 0
void char_exp(void)
{
    unsigned char a = '\0';

    a = -1;
    show_bits(a);

    a++;
    show_bit(a);

    printf("%d\n", a);
}
#endif

#if 0
void ip_to_hex(void)
{
    char ip[] = "127.0.0.1";
    char *tmp = strtok(ip, ".");
    uint32_t res = 0;
    uint32_t i = 3;

    while (tmp) {
        res += atoi(tmp) * pow(256, i);
        i--;
        tmp = strtok(NULL, ".");
    }
    printf("0X%x\n", res);
}
#endif

#if 0
void swap_alternate(void)
{
    char s[] = "world";
    char *p = s;
    char *q = p + 1;

    while (*p && *q) {
        SWAP(*p, *q);
        p += 2;
        q = p + 1;
    }

    printf("result: %s\n", s);
}
#endif

#if 0
struct st1 {
    int32_t a;
};

struct st2 {
    int32_t a;
};

void struct_typedef_hack(void)
{
    typedef struct st1 t1;
    typedef struct st2 t2;

    /** both refer to same address */
    t1 v1 = {1};
    t2 *v2;
    v2 = (t2 *)&v1;
    printf("%d\n", v2->a);

    /** have different addresses */
    t1 x1 = {1};
    t2 x2;
    x2 = *(t2 *)&x1;
    printf("%d\n", x2.a);
}
#endif

#if 0
void unsigned_magic(void)
{
    uint8_t i = 10;

    for (; i >= 0; i--) {
        printf("%d\t", i);
    }
    printf("\n");
}
#endif

#if 0
typedef unsigned char uint_24[3];

void uint_24(void)
{
    uint_24 a = "he";
    printf("%s\n", a);
    printf("%d\n", sizeof(uint_24));
}
#endif

#if 0
void double_ptr(void)
{
    char **str = NULL;
    int32_t *len = NULL;

    GETMEM(len, int32_t, 4);
    CHECK(!len);

    str = (char **)malloc(2);
    GETMEM(str, char *, 4);
    CHECK(!str);

    GETMEM(*str, char, 4);
    CHECK(!str);

    *len = 1;

#if 0
    *len += sprintf(*str + *len, "");   /** remove warning here */
    printf("%d\t%#x\t%#x\n", *len, **str, *(*str + *len));
    *(*str + *len) = 0XF;   /** write array representation for this */
#endif

    str[0][*len] = 0XF;
    printf("%#x\n", *(*str + *len));

    FREE(len);
    FREE(*str);
    FREE(str);
}
#endif

#if 0
void swap_1nib_3nib(void)
{
    int32_t x = 0X1234;
    int32_t tmp = 0;

    tmp = ((x & ~(~0 << 4)) << 8) | ((x & (~(~0 << 4) << 8)) >> 8);
    x &= ((~0 << 12) | ~(~0 << 8)) & (~0 << 4);
    x |= tmp;
    printf("%x\n", x);

    /** this is hard coded, which is actually good in every sense */
    x = 0X1234;
    tmp = ((x & 0XF00) >> 8) | ((x & 0XF) << 8);
    x &= 0XF0F0;
    x |= tmp;
    printf("%x\n", x);
}
#endif

#if 0
void swap_byte(void)
{
    int32_t x = 0X1234;

    x = ((x & 0XFF) << 8) | (x >> 8);
    printf("%#x\n", x);
}
#endif

#if 0
typedef int32_t sint32_t, SINT32_T, sint_t;
void typedef_tweak(void)
{
    sint32_t a = 1;
    SINT32_T b = 2;
    sint_t c = 3;

    printf("%d %d %d\n", a, b, c);
}
#endif

#if 0
void echo_n_times(char *s, int32_t n)
{
    int32_t i = 0;
    char *d = NULL;

    GETMEM(d, char, ((n * 2) + 1));
    CHECK(!d);

    for (i = 0; i < n; i++) {
        d[i] = d[i + n] = s[i];
    }
    d[(n << 1) + 1] = '\0';

    printf("%s\n", d);

    FREE(d);
}
#endif

#if 0
void rev_num_rec(int32_t num)
{
    if (!num)
        return;

    printf("%d", (num % 10));
    rev_num_rec(num / 10);
}
#endif

#if 0
void incr_in_sizeof(void)
{
    int32_t x = 3;

    printf("%d\n", sizeof(int32_t[x++]));
    printf("%d\n", x);
}
#endif

#if 0
void print_p_10(void)
{
#if 0
    /** Solution 1 */
    GETMEM(p, int32_t *, sizeof(int32_t));
    CHECK(!p);

    GETMEM(*p, int32_t, sizeof(int32_t));
    CHECK(!*p);

    **p = 10;
    printf("%d \n", **p);

    FREE(*p);
    FREE(p);
#endif

#if 0
    /** if p is local */
    int32_t **p = NULL;

    p = &p - 1;
    **p = 10;
    printf("%d \n", **p);
#endif

#if 0
    /** if p is global */
    p = &p - 1;
    *p = &p + 2;
    **p = 10;
    printf("%d \n", **p);
#endif
}
#endif

#if 0
void compress_str(void)
{
    char *s = "aaaaabbbbbababccccdddd";

    while (*s) {
        if (*s != *(s + 1)) {
            printf("%c", *s);
        }
        s++;
    }
    printf("\n");
}
#endif

#if 0
struct st {
    char reason;
    enum { scan, auth, assoc, connect = 767, run } state:8;
    //enum { scan, auth, assoc, connect = 254, run } state : 8;
};

void enum_in_struct(void)
{
    struct st p = { 0, run + auth };

    printf("%d\n", p.state);
    printf("size :: %d\n", sizeof(struct st));

    return (0);
}
#endif

#if 0
void arr_union(void)
{
    int32_t i = 0;
    int32_t j = 0;
    int32_t ind = 0;
    int32_t c[8] = {-1};
    int32_t a[] = {1, 2, 2, 2, 3, 4, 5};
    int32_t b[] = {0, 2, 3, 3, 4, 5, 8};

    while ((i < SIZE(a)) && (j < SIZE(b))) {
        if (a[i] < b[j])
            (c[ind - 1] != a[i]) ? (c[ind++] = a[i++]) : i++;
        else
            (c[ind - 1] != b[j]) ? (c[ind++] = b[j++]) : j++;
    }

    while (i < SIZE(a))
        (c[ind - 1] != a[i]) ? (c[ind++] = a[i++]) : i++;


    while (j < SIZE(b))
        (c[ind - 1] != b[j]) ? (c[ind++] = b[j++]) : j++;

    for (i = 0; i < ind; i++)
        printf("%d\t", c[i]);

    printf("\n");
}
#endif

#if 0
void size_of_st_bitfield(void)
{
    typedef struct {
        int32_t a:1;
        int32_t b:4;
    } st;

    printf("%d\n", sizeof(st));
}
#endif

#if 0
void overflow_bitfield(void)
{
    typedef union {
        int32_t a:5;
        int32_t b:6;
        int32_t c:21;
    } un;

    un var;
    var.a = 0XAA55A55;
    printf("%#x\n", var.a);
}
#endif

#if 0
void change_var_in_stack(int32_t *c)
{
    /** Depends on how stack grows */
    *c = 3;
    *(c - 1) = 2;
    *(c - 2) = 1;
}

void pass_to_change_var_in_stack_fm_here(void)
{
    int32_t a = 0;
    int32_t b = 0;
    int32_t c = 0;

    change_var_in_stack(&c);

    printf("a = %d b = %d c = %d\n", a, b, c);
}
#endif

#if 0
void print_only_20_stars(void)
{
    int32_t i;
    int32_t n = 20;

    /** n--, -i < n, i + n */
    /** ~i < n --> prints 21 stars */

    for (i = 0; i < n; i--) {
        printf("*");
    }

    printf("\n");
}
#endif

#if 0
void do_while_continue_test(void)
{
    int8_t i = 0;

    do {
        i++;

        if (i < 5) {
            printf("%d\n", i);
            continue;
        }
        break;
    } while (true);
}
#endif

#if 0
void del_alt_ltr(void)
{
    char s[] = "string";
    char *p = s;
    uint32_t i = 1;

    while (*p) {
        p++;
        *p = *(p + i);
        i++;
    }

    printf("%s \n", s);
}
#endif

#if 0
void del_stdout(void)
{
    uint32_t c = 0;

    while (1) {
        printf("%c", '=');
        fflush(stdout);
        c++;
        if (c == 5) {
            printf("\r     ");
            printf("\b\b\b\b\b");
            fflush(stdout);
            c = 0;
        }
        sleep(1);
    }
}
#endif

#if 0
void a_to_i(void)
{
    int32_t num = 0;
    char *ptr = "1234";

    while (*ptr) {
        int32_t dig = *ptr - '0';
        num = num * 10 + dig;
        ptr++;
    }

    printf("%d \n", num);
}
#endif

#if 0
typedef int32_t ARR[8];
typedef int32_t (*APTR)[8];

APTR ap;
ARR a = {1, 2, 3, 4, 5};

void arr_ptr_ex(void)
{
    a[5] = 6;
    ap = &a;

    printf("%d\n", *(*ap + 5));
}
#endif

#if 0
void combine_str(void)
{
    uint32_t cnt = 0;
    char *ptr = NULL;
    char *s3 = NULL;
    char *s1 = "l@gledgese";
    char *s2 = "teobaloftwar";

    if (!(s3 = (char *)malloc(32))) {
        perror("malloc error\n");
        exit(-1);
    }

    ptr = s3;

    while (*s1 || *s2) {
        int32_t i = 0;
        while ((i <= cnt) && (*s1) && (*s3++ = *s1++) && (++i)) ;

        while ((cnt <= i) && (*s2) && (*s3++ = *s2++) && (++cnt)) ;
    }

    printf("%s\n", ptr);
}
#endif

#if 0
void count_bits(void)
{
    /** Count bits */
    uint32_t v = 5;

    v -= (v >> 1) & 0X55555555;
    v = (v & 0X33333333) + ((v >> 2) & 0X33333333);
    v = ((v + (v >> 4) & 0XF0F0F0F) * 0X1010101) >> 24;

    printf("%u\n", v);
}
#endif

#if 0
void next_pow_2(void)
{
    uint32_t v = 10;    // compute the next highest power of 2 of 32-bit v

    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;

    printf("%u\n", v);
}
#endif

#if 0
typedef union {
    struct s1 {
        char a;
    };
    struct s2 {
        int32_t b;
    };
} un;
#endif

#if 0
void stack_smash(void)
{
    uint32_t len = 0;
    char str[10] = { 0 };

    printf("Enter the name\n");
    gets(str);

    printf("len = [%d]\n", len);
    len = strlen(str);

    printf("len of string entered is : [%d]\n", len);
}
#endif

#if 0
void 100_doors(void)
{
    int32_t i = 1;
    int32_t a[101] = { 0 };

    while (i < 101) {
        int32_t j = 1;
        while (j < 101) {
            if (!(j % i))
                a[j] = !a[j];

            j++;
        }
        i++;
    }

    for (i = 1; i <= 100; i++) {
        if (a[i])
            printf("%d\t", i);
    }

    printf("\n");
}
#endif

#if 0
void rle(void)
{
    char *s = "AAAAAAAAAAAABAAAAAAAAAACCCKKKKKKKKKKKKRRRRRRR";
    int32_t count = 0;

    while (*s) {
        if (*s == *(s + 1)) {
            count++;
            s++;
            continue;
        }
        printf("%c%d", *s, ++count);
        count = 0;
        s++;
    }
    printf("\n");
}
#endif

#if 0
void scope_of_var(void)
{
    printf("Do while sample\n");
    do {
        int32_t a = 10;
        printf("%d\n", a);
        a++;
    } while (a);
}
#endif

#if 0
void find_single(void)
{
    int32_t i = 0;
    int32_t res = 0;
    int32_t a[8] = { 1, 2, 3, -1, 1, 2, 3 };

    while (i < 8) {
        res ^= a[i];
        i++;
    }

    printf("%d\n", res);
}
#endif

#if 0
#define var 3
void fun(void)
{
    char *cricket[var + ~0] = { "clarke", "kallis" };
    char *ptr = cricket[1 + ~0];

    printf("%c\n", *ptr);
}
#endif

#if 0
void bit_magic(void)
{
    int32_t a = 43;
    int32_t b = 21;
    int32_t c = 32;

    a = (((b > c) && (c | c ^ ~1)) | (b = ((c > a) && (a & b ^ ~c)) | c) ^
         (c = ((b > a) && (a ^ b ^ c)) | a)) ^ ((1 << 5) - 2);

    printf("%d \n", a);
    printf("%d \n", b);
    printf("%d \n", c);
}
#endif

#if 0
void my_strncasecmp(const char *s1, const char *s2, size_t n)
{
    while ((n--) && *s1 && *s2) {
        if (n && ((*s1 == *s2) || (*s1 == (*s2 ^ 32))
              || (*s2 == (*s1 ^ 32)))) {
            s1++, s2++;
        } else {
            printf("%d \n", (*s1 - *s2));
            return;
        }
    }
    printf("%d \n", (*s1 - *s2));
}
#endif

#if 0
void my_strcasecmp(const char *s1, const char *s2)
{
    while (*s1 && *s2) {
        if ((*s1 == *s2) || (*s1 == (*s2 ^ 32)) || (*s2 == (*s1 ^ 32))) {
            s1++, s2++;
        } else {
            printf("%d \n", (*s1 - *s2));
            return;
        }
    }
    printf("%d \n", (*s1 - *s2));
}
#endif

#if 0
void my_strncmp(const char *s1, const char *s2, size_t n)
{
    while (n-- && *s1 && *s2) {
        if ((*s1 == *s2) && n) {
            s1++, s2++;
        } else {
            printf("%d \n", (*s1 - *s2));
            return;
        }
    }
    printf("%d \n", (*s1 - *s2));
}
#endif

#if 0
void my_strcmp(const char *s1, const char *s2)
{
    while (*s1 && *s2) {
        if (*s1 == *s2) {
            s1++, s2++;
        } else {
            printf("%d \n", (*s1 - *s2));
            return;
        }
    }
    printf("%d \n", (*s1 - *s2));
}
#endif

#if 0
void my_strspn(const char *s, const char *reject)
{
    char *ptr = NULL;
    int32_t count = 0;

    ptr = (char *)reject;

    while (*s && (reject = ptr)) {
        int32_t flg = 0;
        while (*reject) {
            if (*reject == *s) {
                count++;
                flg = 1;
                break;
            }
            reject++;
        }
        if (!flg) {
            break;
        }
        s++;
    }
    printf("%d \n", count);
}
#endif

#if 0
void my_strcspn(const char *s, const char *reject)
{
    char *ptr = NULL;
    int32_t count = 0;

    ptr = (char *)reject;

    while (*s) {
        reject = ptr;
        while (*reject) {
            if (*reject == *s) {
                printf("%d \n", count);
                return;
            }
            reject++;
        }
        count++, s++;
    }
    printf("%d \n", count);
}
#endif

#if 0
void my_strncpy(char *dest, const char *src, size_t n)
{
    char *ptr = NULL;

    ptr = dest;
    while (n-- && (*dest++ = *src++)) ;

    printf("%s \n", ptr);
}
#endif

#if 0
void my_strcpy(char *dest, const char *src)
{
    char *ptr = NULL;

    ptr = dest;
    while ((*dest++ = *src++)) ;

    printf("%s \n", ptr);
}
#endif

#if 0
void my_strrchr(const char *s, int32_t c)
{
    char *ptr = NULL;

    while (*s) {
        if (*s == c) {
            ptr = (char *)s;
        }
        s++;
    }
    printf("%s \n", ptr);
}
#endif

#if 0
void my_strchr(const char *s, int32_t c)
{
    while (*s) {
        if (*s == c) {
            printf("%s \n", s);
            return;
        }
        s++;
    }
}
#endif

#if 0
void my_strncat(char *dest, const char *src, size_t n)
{
    char *ptr = NULL;

    ptr = dest;
    while (*dest && dest++) ;
    while ((n--) && (*dest++ = *src++)) ;
    *dest = '\0';

    printf("%s \n", ptr);
}
#endif

#if 0
void my_strcat(char *dest, const char *src)
{
    char *ptr = NULL;

    ptr = dest;

    while (*dest && dest++) ;

    while ((*dest++ = *src++)) ;

    printf("%s \n", ptr);
}
#endif

#if 0
void my_strlen(const char *str)
{
    uint32_t len = 0;

    while (*str && ++len && str++) ;
    printf("strlen : %d \n", len);
}
#endif

#if 0
void my_strstr(const char *str, const char *sbstr)
{

    int32_t i = 0;
    int32_t j = 0;

    for (i = 0; str[i]; i++) {
        char *bptr = (char *)sbstr;
        int32_t temp = i;
        for (j = 0; sbstr[j] && (str[i] == sbstr[j]); j++, i++) {
            if (!(sbstr[j + 1])) {
                printf("%s \n", (char *)(str + temp));
                return;
            }
        }
        sbstr = (char *)bptr;
        i = temp;
    }
}
#endif

#if 0
char **func(char **str)
{
    printf("%s\n", str[0]);
    return (char **)str;
}

int32_t rec_fun(int32_t argc, char **argv)
{
    static int32_t i = 0;

    /*
     * Value never gets assigned to "i" since it calls rec_fun recursively.
     * check for"i == 4" before if condition below to exit
     */

    if ((i = rec_fun(++i, func((char *[])"TEST", "Run"))) == 4)
        exit(0);
    else if (i == 24)
        exit(0);

    return i;
}
#endif

#if 0
void set_3_bit(void)
{
    uint32_t num = 15;
    int32_t pos1 = 2;
    int32_t pos2 = 6;

    num = ((num & ((~(~0 << 3)) << (pos1 - 1))) << (pos2 - pos1)) |
        (num & (~((~(~0 << 3)) << (pos2 - pos1 + 1))));

    printf("Result : %x \n", num);
}
#endif

#if 0
void negate_ex(void)
{
    printf("~(~0 << 3) = %d \n", ~(~0 << 3));
    printf("~(0 << 3) = %d \n", ~(0 << 3));
    printf("~(1 << 3) = %d \n", ~(1 << 3));
    printf("~(~1 << 3) = %d \n", ~(~1 << 3));
}
#endif

#if 0
int32_t fact(int32_t num)
{
    int32_t f = 1;
    int32_t i = 1;

    while (i <= num) {
        f = f * i;
        i++;
    }

    return f;
}

void pascal_triangle(void)
{
    int32_t line, i, j;

    printf("Enter the no. of lines: ");
    scanf("%d", &line);

    for (i = 0; i < line; i++) {
        for (j = 0; j < line - i - 1; j++)
            printf(" ");

        for (j = 0; j <= i; j++)
            printf("%ld ", fact(i) / (fact(j) * fact(i - j)));

        printf("\n");
    }
}
#endif

#if 0
void cal_num(void)
{
    int32_t i;
    int32_t j;
    int32_t flg = 0;

    for (i = 0; i < 10000; i++) {
        for (j = 2; j < 11; j++) {
            if ((i % j) == (j - 1)) {
                flg++;
                if (flg == 9) {
                    printf("Number is: %d \n", i);
                    return;
                }
            } else {
                flg = 0;
                break;
            }
        }
    }
}
#endif

#if 0
void addn_bitwise(void)
{
    int32_t x = 10, y = ~20 + 1;

    while (y) {
        int32_t carry = x & y;
        x ^= y;
        y = carry << 1;
    }

    printf("Data : %d\n", x);
}
#endif

#if 0
union tag {
    uint32_t a:6;
    uint32_t b:3;
    uint32_t c:1;
} u;

void add_using_bitfield()
{
    u.a = 16;
    u.b = 4;
    u.c = 1;
    printf("sizeof union = %d\n", sizeof(u));
    printf("u.a = %d\n", u.a);
}
#endif

#if 0
union ss {
    float x;
    int32_t s[1];
} m;

void print_float_bin()
{
    m.x = 1.5;
    int32_t i = 0;
    printf("\n\n");
    for (i = 31; i >= 0; i--) {
        printf("%d", m.s[0] & (1 << i) ? 1 : 0);
    }
}
#endif

#if 0
void chk_bit(void)
{
    unsigned char arr[5] = { 1, 2, 3, 4, 5 };
    int32_t n = 0;
    int32_t temp = 0;

    printf("Enter the bit num to check in array (0 <= num <= 32)\n");
    scanf("%d", &n);

    temp = arr[n / 8];
    n %= 8;
    n = 7 - n;
    printf("Bit value is : %d\n", (temp & (1 << n)) >> n);
}
#endif

#if 0
void mul_bitwise(void)
{
    int32_t a, b, l, m;
    int32_t mul = 0;

    printf("\n Enter two numbers : \n a = ");
    scanf("%d", &a);

    printf("\n b = ");
    scanf("%d", &b);

    l = a;
    m = b;
    while (a >= 1) {
        if (a & 0X1) {
            mul += b;
        }
        a >>= 1;
        b <<= 1;
    }

    printf("\nSo (%d  %d) = %d \n", l, m, mul);
}
#endif

#if 0
void big_of_two(void)
{
    int32_t a = 2;
    int32_t b = 3;
    int32_t max = 0;

    //max = (a > b) * a + (a <= b) * b;
    max = a ^ ((a ^ b) & -(a < b));

    printf("Max : %d\n", max);

    max = b + ((((b - a) >> 31) & 0X1) * (a - b));

    printf("Max : %d\n", max);
}
#endif

#if 0
void fun_in_fun(void)
{
    auto void foo();

    foo();

    void foo()
    {
        printf("in function \n");
    }
}
#endif

#if 0
void swap_byte()
{
    int32_t t = 0;
    int32_t i = 4;
    int32_t n = 0XABCD1234;

    while (i--) {
        t <<= 8;
        t |= n & (~(~0 << 8));
        n >>= 8;
    }

    printf("%x\n", t);
}
#endif

#if 0
void int_char_ptr(void)
{
    int32_t i = 0;
    int32_t temp = 0;
    int32_t a[5] = { 555, 444, 333, 222, 256 };
    unsigned char *ptr = (unsigned char *)a;

    while ((++i) <= 5) {
        temp = (*ptr++);
        temp += (*ptr++) << 8;
        temp += (*ptr++) << 16;
        temp += (*ptr++) << 24;
        printf("%d\t", temp);
    }
    printf("\n");
}
#endif

#if 0
/** execute before main */
void foo(void) __attribute__((constructor));

void bar(void) __attribute__((destructor));

void foo(void)
{
    printf("startup code before main()\n");
}

void bar(void)
{
    printf("cleanup code after main()\n");
}
#endif

#if 0
static int32_t var = 10;

void stat_glob(void)
{
    static int32_t var = 15;
    printf("%d\n", *(&var - 1));
}
#endif

#if 0
void array_hack(void)
{
    int32_t c[3] = { 1, 2, 3 };
    int32_t a[3];
    int32_t i;

    for (i = 1; i < 4; i++) {
        printf("%d\n", a[-i]);
    }
}
#endif

#if 0
int32_t a[0XFFFFFFF] = {1};

void huge_exec(void)
{
    printf("Huge Excecutable & Compilation time is more\n");
}
#endif

#if 0
struct student {
    int32_t rollno;
    char name;
} obj;

void sizeof_struct(void)
{
    int32_t s = 0;
    struct student arr[2];

    s = (char *)&arr[1] - (char *)&arr[0];

    printf("Size of struct: %d\n", s);
}
#endif

#if 0
void assert_fun(int32_t i)
{
    assert(i < 5);
    printf("%d\n", i);
}
#endif

#if 0
void prime(void)
{
    int32_t i = 0;
    int32_t j = 0;

    for (i = 2; i < 256; i++) {
        int32_t temp = sqrt(i);

        for (j = 2; j < temp; j++) {
            if (!(i % j) && (i != j))
                break;

            if (j + 1 == 10)
                printf("%d\n", i);
        }
    }
}
#endif

#if 0
void password(void)
{
    char *ptr = NULL;
    char str[32] = {'\0'};

    printf("Enter Password: ");
    ptr = getpass(str);

    printf("%s\n", ptr);
}
#endif

#if 0
void page_size()
{
    int32_t size = 0;

    size = getpagesize();
    printf("%d\n", strlen("abc" "def"));

    printf("page size :: %d\n", size);
}
#endif

#if 0
jmp_buf env_alarm;

void sig_alarm(int32_t signo)
{
    longjmp(env_alarm, 1);
}

void nonblk_read(void)
{
    char buf[1];
    int32_t fd;

    fd = open(argv[1], O_RDWR | O_NOCTTY);
    if (fd < 0) {
            perror("open call failed\n");
            exit(1);
    }

    if (signal(SIGINT, sig_handler) == SIG_ERR)
        exit(EXIT_FAILURE);

    if (signal(SIGALRM, sig_alarm) == SIG_ERR)
        exit(1);

    if (setjmp(env_alarm))
        check = 1;

    while (!check) {
        alarm(1);
        if (read(fd, buf, 1) < 0) {
            perror("");
            exit(1);
        }

        if (lseek(fd, 0, SEEK_SET)) {
            perror("");
            exit(1);
        }

        alarm(0);
        printf("%c\n", buf[0]);
    }
}
#endif

int main(void)
{
    clock_t time;

    time = clock();
    fun();
    time = clock() - time;

    printf("Time taken = %f\n", ((double)time) / CLOCKS_PER_SEC);
    getchar();

    return (EXIT_SUCCESS);
}
