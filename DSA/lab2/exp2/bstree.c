#include "bstree.h"

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec * 1000 + (double)t.tv_usec / 1000;
}

int getrand(int min, int max)
{
    return (int)rand() / (RAND_MAX + 1.0) * (max - min) + min;
} 

struct bstree *bstree_create(char *key, int value)
{
    struct bstree *node;
    node = malloc(sizeof(*node));
    if (node != NULL) {
    node->key = key;
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    }

    return node;
}

void bstree_add(struct bstree *tree, char *key, int value)
{
    if (tree == NULL)
    {
        return;
    }
    struct bstree *parent, *node;
    while (tree != NULL) 
    {
        parent = tree;
        if (strcmp(key, tree->key) < 0)
        {
            tree = tree->left;
        }
        else if (strcmp(key, tree->key) > 0)
        {
            tree = tree->right;
        }
        else
        {
            return;
        }
    }
    node = bstree_create(key, value);
    
    if (strcmp(key, parent->key) < 0)
    {
        parent->left = node;
    }
    else
    {
        parent->right = node;
    }
}

struct bstree *bstree_lookup(struct bstree *tree, char *key)
{
    while (tree != NULL) 
    {
        if (strcmp(key, tree->key) == 0)
        {
            return tree;
        }
        else if (strcmp(key, tree->key) < 0)
        {
            tree = tree->left;
        }
        else
        {
            tree = tree->right;
        }
    }
    return tree;
}

struct bstree *bstree_delete(struct bstree *tree, char *key)
{
    if (tree == NULL)
        return tree;

    bstree *temp;
    bstree *min_right;
    if (strcmp(key, tree->key) < 0)
    {
        tree->left = bstree_delete(tree->left, key);
    }
    else if (strcmp(key, tree->key) > 0)
    {
        tree->right = bstree_delete(tree->right, key);
    }
    else
    {
        if (tree->left == NULL)
        {
            temp = tree->right;
            free(temp->key);
            free(temp);
            return temp;
        }
        else if (tree->right == NULL)
        {
            temp = tree->left;
            free(temp->key);
            free(temp);
            return tree;
        }
        else
        {
            min_right = bstree_min(tree->right);
            tree->key = strdup(min_right->key);
            tree->value = min_right->value;
            tree->right = bstree_delete(tree->right, min_right->key);
        }
    }
    return tree;
}

struct bstree *bstree_min(struct bstree *tree)
{
    if (tree == NULL)
    {
        return NULL;
    }

    while (tree->left != NULL)
    {
        tree = tree->left;
    }
    return tree;
}

struct bstree *bstree_max(struct bstree *tree)
{
    if (tree == NULL)
    {
        return NULL;
    }

    while (tree->right != NULL)
    {
        tree = tree->right;
    }
    return tree;
}


int main()
{
    static words word[200000];
    struct bstree *tree;
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
    tree = bstree_create(word[0].w, 0);
    for(int i = 1; i < 200001; i++)
    {
        // bstree_add(tree, word[i].w, i);
        if(i % 10000 == 0)
        {
            double sum = 0;
            for (int j = 0; j < 1000 ; j++) {
                double t = wtime();
                bstree_add(tree, word[i].w, i);
                t = wtime() - t;
                sum += t;
            }
            printf("%.6f, ", sum/1000);
        }
    }
    printf("\n");
}