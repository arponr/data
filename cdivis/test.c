#include <stdio.h>
#include <stdlib.h>
#include "link.h"
#include "divis.h"

int main()
{
    /*
    node *root = avl_constr(0,0,0);
    int flag;
    for (int i = 1; i < 10; i++)
    {
	flag = 0;
	root = avl_insert(root, i, i + 1, 0, &flag);
    }
    root = avl_clear(root);
    */

    FILE *in = fopen("adj", "r");
    int N, j;
    fscanf(in, "%d\n", &N);
    link **adj = (link **) malloc(N * sizeof(link));
    if (adj == NULL)
    {
    	printf("adj malloc failed\n");
    	exit(1);
    }
    for (int i = 0; i < N; i++)
    {
    	adj[i] = NULL;
    	while (1)
    	{
    	    fscanf(in, "%d", &j);
    	    if (j == -1)
    		break;
    	    link *temp = adj[i];
    	    adj[i] = link_constr(j);
    	    adj[i]->next = temp;
    	}
    }
    state *go = state_constr(N, adj);
    int *clust = cluster(go);
    //for (int i = 0; i < N; i++)
    //printf("%d\n", clust[i]);
    cleanup(go);
}
