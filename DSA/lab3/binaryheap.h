#include <stdlib.h>
#include <stdio.h>

struct heapnode {
	int key; 
	int value; 
};

struct heap {
	int *index; 
	int maxsize; 
	int nnodes; 
	struct heapnode *nodes;
};

struct heap *heap_create(int maxsize);
void heap_free(struct heap *h);
void heap_swap(struct heapnode *a, struct heapnode *b, struct heap *h);
int heap_insert(struct heap *h, int key, int value);
struct heapnode *heap_min(struct heap *h);
struct heapnode heap_extract_min(struct heap *h);
void heap_heapify(struct heap *h, int index);
int heap_decrease_key(struct heap *h, int index, int key);
void heap_print(struct heap *h);
struct heap *heap_build(int *a, int a_size);
