#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    struct node *next;
    int index;
    char *name;
} node;

typedef struct graph {
    node **neighbours;
    int n;
} graph;

void initGraph (graph * g, int size) {

    g->n = 0;
    g->neighbours = malloc (size * sizeof (node));

    for (int i = 0; i < size; i++)
        g->neighbours[i] = NULL;
}

void addNode (graph *g, char *name, int *size) {
//functia adauga un actor in graf

    node *tmp = malloc (sizeof (node));
    tmp->index = g -> n;
    tmp->name = strdup (name);
    tmp->next = NULL;

    if (g->n == *size) { // daca se ajunge la size-ul initial, se realoca memorie
        g->neighbours = realloc (g->neighbours, 2 * (*size) * sizeof (node));        
        for (int i = (*size); i < 2 * (*size); i++)
            g->neighbours[i] = NULL;
        (*size) = 2 * (*size);
    }

    g->neighbours[g->n] = tmp;
    g->n ++; 
}

void add (node **list, int indexActor) {
//functie care adauga la inceputul unei liste
    
    node *tmp = (node*) malloc (sizeof (node));
    tmp->index = indexActor;
    tmp->next = (*list)->next;
    (*list)->next = tmp;    
}

int isEdge (graph g, int a, int b) {
//functia returneaza 1 daca exista muchie intre a si b, 0 in caz contrar

	node * tmp = g.neighbours[a]->next;

	while (tmp != NULL) {
		if (tmp->index == b)
			return 1;
		tmp = tmp->next;
	}

	return 0;
}

void addEdge (graph g, int a, int b) {
//functia adauga muchie intre a si b daca nu exista deja una
	if (isEdge (g,a,b) == 0) {
    	add (&g.neighbours[a], b);
    	add (&g.neighbours[b], a);
    }
}

int findIndex (graph g, int n, char * name) {
//functia returneaza indexul din graf in functie de un nume dat
    for (int i = 0; i < n; i++)
        if (strcmp (name, g.neighbours[i]->name) == 0)
            return i;
    
    return -1;
}

void dfs(graph g, int v, int vazut [], int *nodes) {
//parcurgere DFS 
    node *aux = g.neighbours[v];
    vazut [v] = 1;
    (*nodes)++;

    while (aux != NULL) {
        v = aux -> index;
        if (!vazut [v])
            dfs (g, v, vazut, nodes);
        aux = aux -> next;
    }    
}

int maxIndex = 0;
int maxim = 0; //numarul maxim de noduri dintre toate componentele conexe

void maximNodes (graph g, int vazut[], int *nodes) {
//calculeaza numarul maxim de noduri dintre componentele conexe  

    for (int i = 0; i < g.n; i++ ) 
        if (vazut[i] == 0) {
            *nodes = 0;
            dfs (g, i, vazut, nodes);
            if (*nodes > maxim) {
                maxim = *nodes;
                maxIndex = i;
            }
        }
}

int counter = 0;


void dfsMax(graph g, int v, int vazut [], char **maxActors) {
//parcurgere DFS care adauga in vectorul maxActors actorii
//din distributia cu numar maxim de actori
    node *tmp = g.neighbours[v];
    vazut [v] = 1;
    maxActors[counter] = strdup (g.neighbours[v]->name);
    counter++;

    while (tmp != NULL) {
        v = tmp->index;
        if (!vazut [v])
            dfsMax (g, v, vazut, maxActors);
        tmp = tmp->next;
    }

}

void pushQueue (node** q, int data) {
    node *tmp, *aux;
    tmp = (node*) malloc (sizeof (node));
    tmp->index = data;

    if (*q == NULL) {
        tmp->next = NULL;
        *q = tmp;
    } else {
        aux = *q;
        while (aux->next != NULL)
            aux = aux->next;
        aux->next = tmp;
        tmp->next = NULL;
    }   
}

int popQueue(node **q) {

    if (*q == NULL)
        return -1;

    node *tmp = *q;
    int value = tmp->index;
    *q = tmp->next;
    free (tmp);
    return value; 

}

// gaseste distanta minima dintre u si v
int minimDist (graph g, int u, int v, int d[], int vazut[]) {
    
    node *q = NULL;

    for (int i = 0; i < g.n; i++) {
        d[i] = 0;
        vazut[i] = 0;
    }

    pushQueue (&q, u);
    vazut[u] = 1;
    d[u] = 0;
    
    while (q != NULL) {
        u = popQueue (&q);
        for (int i = 0; i < g.n; i++)
            if (isEdge (g, u, i) == 1 && vazut[i] == 0) {
                d[i] = d[u] + 1;
                vazut[i] = 1;

                pushQueue (&q, i);
            }
    }
    return d[v];
}

int cmpQsort(const void *a, const void *b) {
//functie de sortare pentru qsort 
    const char **ia = (const char **)a;
    const char **ib = (const char **)b;
    return strcmp(*ia, *ib);
}

int main (int argc, char *argv[]) {

    int number, actors;
    char filmName[200];
    char actorName[200];
    char space;
    int size = 500;

    // initializare graf
    graph g;
    initGraph (&g, size);

    // citire date
    FILE *Fin = fopen(argv[2], "r");
    fscanf (Fin, "%d", &number); //numar de filme
    fscanf (Fin, "%c", &space);

    for (int i = 0; i < number; i++) {
        fgets (filmName, 200, Fin);
        fscanf (Fin, "%d", &actors);
        fscanf (Fin, "%c", &space);

        int *relatedActors = (int*) malloc(actors * sizeof (int));
        for (int j = 0; j < actors; j++) { 
            fgets (actorName, 200, Fin);

            int index = findIndex (g, g.n, actorName);
            if (index == -1) {
                addNode (&g, actorName, &size);
                relatedActors[j] = g.n - 1;
            }
            else
                relatedActors[j] = index;
        }

        // se creeaza muchiile, folosind vectorul creat anterior
        for (int k = 0; k < actors; k++) {
            for (int l = k + 1; l < actors; l++)
                addEdge (g, relatedActors[k], relatedActors[l]);
            }

        free (relatedActors);
    }

    FILE *Fout = fopen (argv[3], "w"); //deschidere fisier output

    if (strcmp (argv[1], "-c1") == 0) { //cerinta 1

        int * vazut = (int*) calloc (g.n, sizeof(int));
        int nodes = 0;

        maximNodes (g, vazut, &nodes);

        fprintf(Fout, "%d\n", maxim);

        // se pun actorii din componenta maxima intr-un vector de char*
        char ** maxActors = malloc (maxim * sizeof(char *));
        
        int * vazut2 = (int*) calloc(g.n, sizeof(int));

        dfsMax (g, maxIndex, vazut2, maxActors);

        // sortare lista actori
        qsort (maxActors, maxim, sizeof(char *), cmpQsort);

        for (int j = 0; j < maxim; j++)
           fprintf (Fout, "%s", maxActors[j]);

       free (maxActors); free (vazut); free (vazut2);

    }
    
    if (strcmp (argv[1], "-c2") == 0) { //cerinta 2

        char Actor1[200], Actor2[200];
        fgets (Actor1, 200, Fin);
        fgets (Actor2, 200, Fin);

        int actor1 = findIndex(g, g.n, Actor1);
        int actor2 = findIndex(g, g.n, Actor2);
        
        int * d = calloc (g.n, sizeof(int));
        int * vazut = calloc (g.n, sizeof(int));

        int result = minimDist (g, actor1, actor2, d, vazut);

        if (result == 0)
            fprintf (Fout , "%d\n", -1);
        else fprintf (Fout , "%d\n", result);

        free (d); free (vazut);
        
    }

    if (strcmp (argv[1], "-c3") == 0) { //cerinta 3

    }

    fclose (Fin); 
    fclose (Fout);

    return 0;
}
