#include "Dijkstra.h"

int main()
{
    srand(wtime(NULL));
    int connected_graph[V1][V1] = {0}; 
    generate_connected_graph(connected_graph);

    FILE *fp = fopen("connected_file.txt", "w");
    if (!fp) perror("connected_file.txt");
    for (int i = 1; i < V1; i++) 
    {
        for (int j = 1; j < V1; j++)
            fprintf(fp, "%d ", connected_graph[i][j]);
        fprintf(fp,"\n");
    }
    fclose(fp);

    int *d = (int*) malloc((V1) * sizeof(int));
	int *prev = (int*) malloc((V1) * sizeof(int));

    double t = wtime();
    dijkstra((int *)connected_graph, 1, d, prev, V1);
    t = wtime() - t;

    print_connected(prev, d, t);

    int grid_graph[V2][V2] = {0};   
    generate_grid_graph(grid_graph);

    FILE *lp = fopen("grid_file.txt", "w");
    if (!lp) perror("grid_file.txt");
    for (int i = 1; i < V2; i++) 
    {
        for (int j = 1; j < V2; j++)
            fprintf(lp, "%d ", grid_graph[i][j]);
        fprintf(lp,"\n");
    }
    fclose(lp);

	int *d2 = (int*) malloc((V2) * sizeof(int));
	int *prev2 = (int*) malloc((V2) * sizeof(int));

    double t2 = wtime();
    dijkstra((int *)grid_graph, 1, d2, prev2, V2);
    t2 = wtime() - t2;;
    
    print_grid(prev2, d2, t2);

	return 0;
}