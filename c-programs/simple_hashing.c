#define _GNU_SOURCE
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define MEM_ERR	\
        fprintf(stderr, "%s ERROR: malloc failed(line: %d)\n", \
                        __func__, __LINE__)

#define ARG_ERR \
        fprintf(stderr, "%s ERROR: Invalid input arg(s)(line: %d)\n", \
                        __func__, __LINE__)

typedef struct _entry_t {
        char *key;
        char *value;
        struct _entry_t *next;
} entry_t;

typedef struct _hashtable_t {
        int32_t size;
        struct _entry_t **table;
} hashtable_t;

static hashtable_t *ht_create(int32_t size);
static entry_t *ht_newpair(char *key, char *value);
static char *ht_get(hashtable_t *hashtable, char *key);
static void free_all(int32_t n, hashtable_t *hashtable);
static int32_t ht_hash(hashtable_t *hashtable, char *key);
static void ht_set(hashtable_t *hashtable, char *key, char *value);

static hashtable_t *ht_create(int32_t size)
{
        int32_t i;
        hashtable_t *hashtable;

        if (size < 1) {
                ARG_ERR;
                return NULL;
        }

        hashtable = (hashtable_t *)malloc(sizeof(hashtable_t));
        if (!hashtable) {
                MEM_ERR;
                return NULL;
        }

        hashtable->table = (entry_t **)malloc(sizeof(void *) * size);
        if (!hashtable->table) {
                free(hashtable);
                MEM_ERR;
                return NULL;
        }

        for (i = 0; i < size; i++)
                hashtable->table[i] = NULL;

        hashtable->size = size;

        return hashtable;
}

static int32_t ht_hash(hashtable_t *hashtable, char *key)
{
        uint32_t hashval;

        if (!hashtable || !key) {
                ARG_ERR;
                return -1;
        }

        for (hashval = 0; *key && (hashval < ULONG_MAX); key++) {
                hashval <<= 8;
                hashval += *key;
        }

        return (hashval % hashtable->size);
}

static entry_t *ht_newpair(char *key, char *value)
{
        entry_t *newpair;

        if (!value || !key) {
                ARG_ERR;
                return NULL;
        }

        newpair = (entry_t *)calloc(1, sizeof(entry_t));
        if (!newpair) {
                MEM_ERR;
                return NULL;
        }

        newpair->key = strdup(key);
        if (!newpair->key) {
                free(newpair);
                MEM_ERR;
                return NULL;
        }

        newpair->value = strdup(value);
        if (!newpair->value) {
                free(newpair->key);
                free(newpair);
                MEM_ERR;
                return NULL;
        }

        newpair->next = NULL;

        return newpair;
}

static void ht_set(hashtable_t *hashtable, char *key, char *value)
{
        int32_t bin;
        entry_t *next;
        entry_t *last;
        entry_t *newpair;

        if (!hashtable || !key || !value) {
                ARG_ERR;
                return;
        }

        next = hashtable->table[bin = ht_hash(hashtable, key)];

        while (next && next->key && (strcmp(key, next->key) > 0)) {
                last = next;
                next = next->next;
        }

        if (next && next->key && !strcmp(key, next->key)) {
                free(next->value);
                next->value = strdup(value);
                return;
        }

        newpair = ht_newpair(key, value);
        if (next == hashtable->table[bin]) {
                newpair->next = next;
                hashtable->table[bin] = newpair;
        } else if (!next) {
                last->next = newpair;
        } else {
                newpair->next = next;
                last->next = newpair;
        }
}

static char *ht_get(hashtable_t *hashtable, char *key)
{
        int32_t bin;
        entry_t *pair;

        if (!hashtable || !key) {
                ARG_ERR;
                return NULL;
        }

        bin = ht_hash(hashtable, key);
        pair = hashtable->table[bin];
        while (pair && pair->key && (strcmp(key, pair->key) > 0)) {
                pair = pair->next;
        }

        if (!pair || !pair->key || strcmp(key, pair->key))
                return NULL;

        return pair->value;
}

static void free_all(int32_t n, hashtable_t *hashtable)
{
        if ((n < 1) || !hashtable) {
                ARG_ERR;
                return;
        }

        while (n--) {
                if (!hashtable->table[n]) {
                        continue;
                }

                free(hashtable->table[n]->key);
                free(hashtable->table[n]->value);
                free(hashtable->table[n]);
        }

        free(hashtable->table);
        free(hashtable);
}

int32_t main(void)
{
        int32_t n = 65536;

        hashtable_t *hashtable = ht_create(n);
        if (!hashtable) {
                fprintf(stderr, "ht_cretae error\n");
                return EXIT_FAILURE;
        }

        ht_set(hashtable, "k1", "inky");
        ht_set(hashtable, "k2", "pinky");
        ht_set(hashtable, "k3", "blinky");
        ht_set(hashtable, "k4", "floyd");

        printf("%s\n", ht_get(hashtable, "k1"));
        printf("%s\n", ht_get(hashtable, "k2"));
        printf("%s\n", ht_get(hashtable, "k3"));
        printf("%s\n", ht_get(hashtable, "k4"));

        free_all(n, hashtable);

        return EXIT_SUCCESS;
}
