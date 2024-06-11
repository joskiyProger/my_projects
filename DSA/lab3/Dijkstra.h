#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <sys/time.h>

#define V1 21
#define V2 101


void dijkstra(int *gr, int src, int *d, int *prev, int V);
void search_path(int *prev, int src, int dst, int *pathlen, int *path);
void generate_connected_graph(int graph[V1][V1]);
void generate_grid_graph(int graph[V2][V2]);
void print_connected(int *prev,  int *d2, double t);
void print_grid(int *prev2, int *d2, double t2);
double wtime();
