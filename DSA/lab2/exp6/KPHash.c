#include "KPHash.h"

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

unsigned int KRHash(char *key)
{
    unsigned int h = 0, hash_mul = 31;
    while (*key)
    {
        h = h * hash_mul + (unsigned int)*key++;
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

    int index = KRHash(key);
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

    int index = KRHash(key);
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
    int index = KRHash(key);
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
        int j = 5 + rand()%14;
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
        if(i % 10000 == 0)
        {
            int p = rand() % i;
            double t = wtime();
            hashtab_lookup(hashtab, word[p].w);
            t = wtime() - t;
            // printf("%s\n", word[p].w);
            // printf("%.6f     %d\n", t, i);
        }
    }
    printf("\n");
    int coll[200000] = {0};
    int y = 0;
    for(int i = 0; i < 200000; i++)
    {
        y = KRHash(word[i].w);
        coll[y] = coll[y] + 1;
    }
    int collizions_counter = 0;
    for(int p = 0; p < 20; p++)
    {
        for(int j = 0; j < 10000 + p * 10000; j++)
        {
            if(coll[j] >= 2)
            {
                collizions_counter += coll[j] - 1;
            }
        }
        printf("%d, ", collizions_counter);
        collizions_counter = 0;
    }
    printf("\n");
}