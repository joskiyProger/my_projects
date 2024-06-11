#include "binaryheap.h"
#include "Dijkstra.h"

void dijkstra(int *graph, int src, int *d, int *prev, int V)
{
    int visited[V];
	int i;
	int j;
	struct heap *h;
	struct heapnode v;

	h = heap_create(V); // Вставка начальной вершины в кучу
	for (i = 1; i < V; i++) // Инициализация массивов кратчайших расстояний, предыдущих вершин и посещенных вершин
    {
		d[i] = (i != src) ? 10000 : 0;
		prev[i] = -1; // Инициализируем предыдущую вершину как неопределенную
		heap_insert(h, d[i], i);
        visited[i] = 0;
	}

	for (i = 0; i < V; i++) 
    {
		v = heap_extract_min(h); //Извлекаем узел, ближайший к начальному
        int u = v.value;
        if (visited[u])
        {
            continue;
        }
        visited[u] = 1;

        for (j = 1; j < V; j++) // Цикл по смежным непосещённым вершинам узла
        {
            if (*(graph + u * V + j) && !visited[j]) 
            {
                if (abs(d[u]) + *(graph + u * V + j) < abs(d[j])) // Путь через u короче текущего пути?
                {
                    d[j] = d[v.value] + *(graph + u * V + j);
                    heap_decrease_key(h, j, d[j]);
                    prev[j] = v.value;
                }
            }    
        }
	}
	heap_free(h);
}

// void generate_grid_graph(int graph[V2][V2])
// {
//     for (int i = 0; i < V2; i++) 
//     {
//         for (int j = 0; j < V2;) 
//         {
            
//         }
//     }
// }

void generate_grid_graph(int graph[V2][V2]) { 
    // Заполняем матрицу смежности нулями 
    for (int i = 0; i < V2; i++) { 
        for (int j = 0; j < V2; j++) { 
            graph[i][j] = 0; 
        } 
    } 
 
    // Устанавливаем ребра между вершинами сетки (вертикально и горизонтально) 
    for (int i = 0; i < V2; i++) { 
        // Вершина сверху 
        if (i - 10 >= 0) 
            graph[i][i - 10] = 1; 
        // Вершина снизу 
        if (i + 10 < V2) 
            graph[i][i + 10] = 1; 
        // Вершина слева 
        if (i % 10 != 0) 
            graph[i][i - 1] = 1; 
        // Вершина справа 
        if (i % 10 != 9) 
            graph[i][i + 1] = 1; 
    } 
}

void generate_connected_graph(int graph[V1][V1])
{
    for (int i = 0; i < V1; i++) 
    {
        graph[i][(i + 1) % V1] = 10 + rand()%80;
        graph[(i + 1) % V1][i] = graph[i][(i + 1) % V1];
    }
}

void search_path(int *prev, int src, int dst, int *pathlen, int *path)
{
	int i;
	int j;

	*pathlen = 1;
	i = dst;

	while (i != src) {
		(*pathlen)++;
		i = prev[i];
	}

	j = 0;
	i = dst;

	while (i != src) {
		path[*pathlen - j] = i;
		i = prev[i];
		j++;
	}
	path[*pathlen - j] = i;
}

void print_connected(int *prev,  int *d, double t)
{
    int path[V1], pathlen;
    FILE *connected_file = fopen("connected_graph_result.txt", "w");

	for (int j = 1; j < V1; j++) 
    {
		if (j != 1) 
        {
			search_path(prev, 1, j, &pathlen, path);

			fprintf(connected_file, "Минимальное путь от вершины <%d> до <%d> : ", 1, j);

			for (int i = 1; i <= pathlen; i++) 
            {
				fprintf(connected_file, "%d ", path[i]);
			}
            fprintf(connected_file,"Расстояие : %d\n", d[j]);
		}
	}
    fprintf(connected_file,"Время : %f\n", t);

    fclose(connected_file);
}

void print_grid(int *prev2, int *d2, double t2)
{
    int path2[V2], pathlen2;

    FILE *grid_file = fopen("grid_graph_result.txt", "w");

	for (int j = 1; j < V2; j++) 
    {
		if (j != 1) 
        {
			search_path(prev2, 1, j, &pathlen2, path2);

			fprintf(grid_file, "Минимальное путь от вершины <%d> до <%d> : ", 1, j);

			for (int i = 1; i <= pathlen2; i++) 
            {
				fprintf(grid_file, "%d ", path2[i]);
			}
            fprintf(grid_file,"Расстояние : %d\n", d2[j]);
		}
	}
    fprintf(grid_file,"Время : %f\n", t2);

    fclose(grid_file);
}

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec * 1000 + (double)t.tv_usec / 1000;
}