#include<stdio.h>
#include<stdlib.h>

struct AdjMatrix{
    int NumVertex;
    int **Edge;
    int **path;
};

typedef struct AdjMatrix *graph;

/** 
 * Implement with Adjacency Matrix
 */
graph CreateGraph(int Numvertex){
    graph g;
    g = malloc(sizeof(struct AdjMatrix));
    if(!g){
        printf("OUT OF SPACE!\n"); return NULL;
    }
    g->NumVertex = Numvertex;
    g->Edge = malloc(sizeof(int *) * (g->NumVertex + 1));
    if(!g->Edge){
        printf("OUT OF SPACE!\n"); return NULL;
    }
    for(int i = 0; i < (g->NumVertex + 1); ++i){
        g->Edge[i] = malloc(sizeof(int) * (g->NumVertex + 1));
        if(!g->Edge[i]){
            printf("OUT OF SPACE!\n"); return NULL;
        }
        else{
            for(int j = 0; j < (g->NumVertex + 1); ++j){
                if(i == j){
                    g->Edge[i][j] = 0;
                }
                else g->Edge[i][j] = 32767;
                g->Edge[0][j] = j;
            }
            g->Edge[i][0] = i;
        }
    }
    g->path = malloc(sizeof(int *) * (g->NumVertex + 1));
    if(!g->path){
        printf("OUT OF SPACE! \n"); return NULL;
    }
    for(int i = 0; i < (g->NumVertex + 1); ++i){
        g->path[i] = malloc(sizeof(int) * (g->NumVertex + 1));
        if(!g->path[i]){
            printf("OUT OF SPACE! \n"); return NULL;
        }
        else{
            for(int j = 0; j < (g->NumVertex + 1); ++j){
                g->path[i][j] = -1;
                g->path[0][j] = j;
            }
            g->path[i][0] = i;
        }
    }
    return g;
}

void CreateEdge(graph g, int v, int w, int cost){
    g->Edge[v][w] = cost;
}

void PrintGraph(graph g){
    for(int i = 0; i < (g->NumVertex + 1); ++i){
        for(int j = 0; j < (g->NumVertex + 1); ++j){
            if(i == 0 && j == 0){
                printf("V ");
            }
            else if(g->Edge[i][j] == 32767){
                printf("∞ ");
            }
            else printf("%d ", g->Edge[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/** 
 * Implement a ReadGraph() routine to construct the graph in memory
 */
graph ReadGraph(){
    graph g;
    int n_vertex, n_edge, trait[1][2];
	FILE *fp = fopen("3.txt", "r");
	if(!fp) return 0;
	for(int i = 0; i <= 1; ++i){
		fscanf(fp, "%d", &trait[0][i]);
	}
	n_vertex = trait[0][0], n_edge = trait[0][1];
	if(n_vertex == 0) return 0;

	g = CreateGraph(n_vertex); 
	int line, row, **element;
	element = (int **)malloc(sizeof(int *) * (n_edge + 1));
	for(int i = 0; i < (n_edge + 1); ++i){
		element[i] = (int *)malloc(sizeof(int) * 3);
	}
	for(line = 0; line < n_edge; ++line){
		for(row = 0; row <= 2; ++row){
			fscanf(fp, "%d", &element[line][row]);
		}
		CreateEdge(g, element[line][0], element[line][1], element[line][2]);
	}
	fclose(fp);
	return g;
}

/**
 * Output the pairwise short paths together with shortest lengths to screen
 */
void Floyd(graph g){
    for(int k = 1; k < (g->NumVertex + 1); ++k){
        for(int i = 1; i < (g->NumVertex + 1); ++i){
            for(int j = 1; j < (g->NumVertex + 1); ++j){
                if(g->Edge[i][k] + g->Edge[k][j] < g->Edge[i][j]){
                    g->Edge[i][j] = g->Edge[i][k] + g->Edge[k][j];
                    g->path[i][j] = k;
                }
            }
        }
    }
}

void PrintPath(graph g){
    for(int i = 1; i < (g->NumVertex + 1); ++i){
        for(int j = 1; j < (g->NumVertex + 1); ++j){
            printf("%d <- ", j);
            int temp = g->path[i][j];
            while(temp != -1){
                printf("%d <- ", temp);
                temp = g->path[i][temp];
            }
            printf("%d ",i);
            printf("(cost: %d) \n", g->Edge[i][j]);
        }
    }
}

int main(){
    graph g;
    g = ReadGraph();
    printf("The Adjacency Matrix for the graph is: \n");
    PrintGraph(g);
    printf("The pairwise shortest paths for the graph are: \n");
    Floyd(g);
    PrintPath(g);
    return 0;
}