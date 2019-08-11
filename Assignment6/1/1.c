#include<stdio.h>
#include<stdlib.h>

#ifndef _Graph_H

struct ListVertex;
typedef struct ListVertex *position;
struct GraphStructure;
typedef struct GraphStructure *graph;
typedef int vertex;

graph InitializeGraph(int NumVertex);
void InsertEdge(graph g, vertex v, vertex w);
void PrintGraph(graph g);
void InDegree(graph g); // calculate the in-degrees of all vertices
void OutDegree(graph g); // calculate the out-degrees of all vertices
void TopSort(graph g);

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
 * PrintGraph()
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

void InsertEdge(graph g, vertex v, vertex w){ // v: tail, w: head
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
  int i,j; 
	list pos;
  for(i = 0; i < g->NumVertex; i++){
    pos = g->TheVertices[i]->NextAdj;
    printf("\n%d -> ", i);
    while(pos != NULL){
      j = pos->AdjVertex;
      printf("%d ", j);
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
	FILE *fp = fopen("1.txt", "r");
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
		element[i] = (int *)malloc(sizeof(int) * 2);
	}
	for(line = 0; line < n_edge; ++line){
		for(row = 0; row <= 1; ++row){
			fscanf(fp, "%d", &element[line][row]);
		}
		InsertEdge(g, element[line][0], element[line][1]);
	}
	fclose(fp);
	return g;
}

/**
 * Output the topological sort result to screen. 
 */
void TopSort(graph g){
	int i, rear = -1, head = 0; vertex *top_queue;
	list pos;
	top_queue = (int *)malloc(sizeof(int) * g->NumVertex);
	for(i = 0; i < g->NumVertex; ++i){
		if(in_degree[i] == 0){
			top_queue[++rear] = i;
		}
	}
	while(head <= rear){
		pos = g->TheVertices[top_queue[rear]]->NextAdj;
		head++;
		while(pos){
			if(--in_degree[pos->AdjVertex] == 0){
				top_queue[++rear] = pos->AdjVertex;
			}
			pos = pos->NextAdj;
		}
	}
	if(rear < g->NumVertex - 1){
		printf("The graph has a circle! \n");
	}
	for(int j = 0; j <= rear; ++j){
		printf("%d ", top_queue[j]);
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
	printf("\nThe topological sort result is: \n");
	InDgree(g);
	TopSort(g);
	return 0;
}