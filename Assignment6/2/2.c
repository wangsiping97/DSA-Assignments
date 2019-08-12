#include<stdio.h>
#include<stdlib.h>

#ifndef _Graph_H

struct ListVertex;
typedef struct ListVertex *position;
struct GraphStructure;
typedef struct GraphStructure *graph;
typedef int vertex;

graph InitializeGraph(int NumVertex);
void InsertEdge(graph g, vertex v, vertex w, int cost);
void PrintGraph(graph g);
void InDegree(graph g); // calculate the in-degrees of all vertices
void OutDegree(graph g); // calculate the out-degrees of all vertices
void Dijkstablera(graph g, vertex s); // solve the single-source shortest-path problem

#endif

struct ListVertex{
	vertex AdjVertex;
 	position NextAdj;
	int cost;
};

typedef position list;

struct GraphStructure{
	int NumVertex;
	list *TheVertices;
};

int *in_degree;
int *out_degree;

/**
 * Implement the routines: 
 * InitializeGraph()
 * InsertEdge()
 * InDegree()
 * OutDegree() 
 */

graph InitializeGraph(int NumVertex){
	graph g; int i;
	g = malloc(sizeof(struct GraphStructure));
	if(!g){
		printf("OUT OF SPACE! \n");
		return NULL;
	}
	g->NumVertex = NumVertex;
	g->TheVertices = malloc(sizeof(list) * (g->NumVertex));
	if(!g->TheVertices){
		printf("OUT OF SPACE! \n");
		return NULL;
	}
	for(i = 0; i < g->NumVertex; ++i){
		g->TheVertices[i] = malloc(sizeof(struct ListVertex));
		if(!g->TheVertices[i]){
			printf("OUT OF SPACE! \n");
			return NULL;
		}
		else
		    g->TheVertices[i]->NextAdj = NULL;
	}
	return g;
}

void InsertEdge(graph g, vertex v, vertex w, int cost){ // v: tail, w: head
	list pos;
	pos = g->TheVertices[v];
	while(pos->NextAdj && pos->NextAdj->AdjVertex != w){ 
		pos = pos->NextAdj; // locate the head
	}
	if(!pos->NextAdj){
		position new_cell = malloc(sizeof(struct ListVertex));
		if(!new_cell){
			printf("OUT OF SPACE! \n");
			return;
		}
		else{
			pos->NextAdj = new_cell;
			new_cell->AdjVertex = w;
			new_cell->NextAdj = NULL;
            new_cell->cost = cost;
		}
	}
	else return;
}

void InDgree(graph g){
	int i; list pos;
	in_degree = (int *)malloc(sizeof(int) * g->NumVertex);
	for(i = 0; i < g->NumVertex; ++i){
		in_degree[i] = 0;
	}
	for(i = 0; i < g->NumVertex; ++i){
		pos = g->TheVertices[i]->NextAdj;
		while(pos){
			in_degree[pos->AdjVertex]++;
			pos = pos->NextAdj;
		}
	}
}

void OutDegree(graph g){
	int i; list pos;
	out_degree = (int *)malloc(sizeof(int) * g->NumVertex);
	for(i = 0; i < g->NumVertex; ++i){
		out_degree[i] = 0;
	}
	for(i = 0; i < g->NumVertex; ++i){
		pos = g->TheVertices[i]->NextAdj;
		while(pos){
			out_degree[i]++;
			pos = pos->NextAdj;
		}
	}
}

void PrintGraph(graph g){
  int i,j,k; 
	list pos;
  for(i = 0; i < g->NumVertex; i++){
    pos = g->TheVertices[i]->NextAdj;
    printf("\n%d -> ", i);
    while(pos != NULL){
      j = pos->AdjVertex;
      k = pos->cost;
      printf("%d(cost: %d) ", j,k);
      pos = pos->NextAdj;
    }
  }
}

/**
* Implement a ReadGraph() routine to call InitializeGraph() and InsertEdge() to construct the graph in memory. 
*/
graph ReadGraph(){
	graph g;
	int n_vertex, n_edge, trait[1][2];
	FILE *fp = fopen("2.txt", "r");
	if(!fp) return 0;
	for(int i = 0; i <= 1; ++i){
		fscanf(fp, "%d", &trait[0][i]);
	}
	n_vertex = trait[0][0], n_edge = trait[0][1];
	if(n_vertex == 0) return 0;

	g = InitializeGraph(n_vertex); 
	int line, row, **element;
	element = (int **)malloc(sizeof(int *) * (n_edge + 1));
	for(int i = 0; i < (n_edge + 1); ++i){
		element[i] = (int *)malloc(sizeof(int) * 3);
	}
	for(line = 0; line < n_edge; ++line){
		for(row = 0; row <= 2; ++row){
			fscanf(fp, "%d", &element[line][row]);
		}
		InsertEdge(g, element[line][0], element[line][1], element[line][2]);
	}
	fclose(fp);
	return g;
}

/** 
 * Output all shortest paths from vertex 0 to screen using Dijkstra function.
 */
struct D_table{
    int known;
    int total_cost;
    vertex pre_vertex;
} *table;

void Dijkstablera(graph g, vertex s){
    int min;
    vertex v;
    list pos;
    table = (struct D_table *)malloc(sizeof(struct D_table) * g->NumVertex);
    for(int i = 0; i < g->NumVertex; ++i){
        table[i].known = 0;
        table[i].total_cost = 10000;
        table[i].pre_vertex = -1;
    }
    table[s].total_cost = 0;
    for( ; ; ){
        min = 10000; v = -1;
        for(int i = 0; i < g->NumVertex; ++i){
            if(table[i].known != 1 && table[i].total_cost < min){
                min = table[i].total_cost;
                v = i;
            }
        }
        if(v == -1) break;
        table[v].known = 1;
        pos = g->TheVertices[v]->NextAdj;
        while(pos){
            if(table[pos->AdjVertex].known != 1){ // unkonwn
                if(table[v].total_cost + pos->cost < table[pos->AdjVertex].total_cost){
                    table[pos->AdjVertex].total_cost = table[v].total_cost + pos->cost;
                    table[pos->AdjVertex].pre_vertex = v;
                }
            }
            pos = pos->NextAdj;
        }
    }
    for(int i = 0; i < g->NumVertex; ++i){
        printf("%d ", i);
        vertex temp = i;
        while(table[temp].pre_vertex != -1){
            printf("<- %d ", table[temp].pre_vertex);
            temp = table[temp].pre_vertex;
        }
        printf("(cost: %d) \n", table[i].total_cost);
    }
}

/**
 * main function
 */
int main(){
	graph g;
	g = ReadGraph();
	printf("The graph is: ");
	PrintGraph(g);
	printf("\nThe single-source shortest-path problem's solutions are: \n");
    Dijkstablera(g, 0); 
	return 0;
}