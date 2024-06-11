#include "hashtab.h"

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec * 1000 + (double)t.tv_usec / 1000;
}

int getrand(int min, int max)
{
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
} 

unsigned int hashtab_hash(char *key)
{
    unsigned int h = 0, hash_mul = 31;
    while (*key)
    {
        h = h * hash_mul + (unsigned int) * key++;
    }
    return h % HASHTAB_SIZE;
}

void hashtab_init(struct listnode **hashtab)
{
    int i;

    for (i = 0; i < HASHTAB_SIZE; i++)
    {
        hashtab[i] = NULL;
    }
}

void hashtab_add(struct listnode **hashtab, char *key, int value)
{
    struct listnode *node;

    int index = hashtab_hash(key);
    node = malloc(sizeof(*node));
    if (node != NULL) 
    {
        node->key = key;
        node->value = value;
        node->next = hashtab[index];
        hashtab[index] = node;
    }
}

struct listnode *hashtab_lookup(struct listnode **hashtab, char *key)
{
    struct listnode *node;

    int index = hashtab_hash(key);
    for (node = hashtab[index]; node != NULL; node = node->next) 
    {
        if (0 == strcmp(node->key, key))
        {
            return node;
        }
    }
    return NULL;
}

void hashtab_delete(struct listnode **hashtab, char *key)
{
    struct listnode *node, *prev = NULL;
    int index = hashtab_hash(key);
    for (node = hashtab[index]; node != NULL; node = node->next) 
    {
        if (0 == strcmp(node->key, key)) 
        {
            if (prev == NULL)
            {
                hashtab[index] = node->next;            
            }
            else
            {
                prev->next = node->next;
            }
            free(node);
            return;
        }
        prev = node;
    }
}

int main()
{
    static words word[200000];
    srand(time(NULL));
    for(int i = 0; i < 200001; i++)
    {
        int j = 5 + rand()%10;
        char *C = malloc(sizeof(char) * j);
        word[i].w = malloc(sizeof(char) * j);
        for(int p = 0; p < j; p++)
        {
            C[p] = 97 + rand()%26;
        }
        memcpy(word[i].w, C, sizeof(char) * j);
        free(C);
    }
    hashtab_init(hashtab);
    for(int i = 1; i < 200001; i++)
    {
        hashtab_add(hashtab, word[i].w, i);
        // if(i % 10000 == 0)
        // {
        //     int p = rand() % i;
        //     double t = wtime();
        //     hashtab_lookup(hashtab, word[p].w);
        //     t = wtime() - t;
        //     printf("%.6f, ", t);
        // }
        if(i % 10000 == 0)
        {
            double sum = 0;
            for (int j = 0; j < 100 ; j++) {
                double t = wtime();
                hashtab_lookup(hashtab, word[i].w);
                t = wtime() - t;
                sum += t;
            }
            printf("%.6f, ", sum/100);
        }
    }
    printf("\n");
}