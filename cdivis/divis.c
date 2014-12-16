#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tools.h"
#include "link.h"
#include "avl.h"
#include "divis.h"

state * state_constr(int N_, link **adj_)
{
    state * out = malloc(sizeof(state));
    if (out == NULL)
    {
	printf("state malloc failed\n");
	exit(1);
    }
    out->N = N_;
    out->adj = malloc(out->N * sizeof(link *));
    out->rem = malloc(out->N * sizeof(link *));
    out->vis = malloc(out->N * sizeof(int));
    out->comp = malloc(out->N * sizeof(int));
    out->dist = malloc(out->N * sizeof(int));
    out->q = malloc(out->N * sizeof(int));
    out->weight = malloc(out->N * sizeof(double));
    out->under = malloc(out->N * sizeof(double));
    out->local = out->global = NULL;
    if (out->adj == NULL || out->rem == NULL || out->vis == NULL || 
	out->comp == NULL || out->dist == NULL || out->q == NULL || 
	out->weight == NULL || out->under == NULL)
    {
	printf("massive malloc failed\n");
	exit(1);
    }
    out->E = 0;
    for (int i = 0; i < out->N; i++)
    {
	out->E += link_length(adj_[i]);
	out->adj[i] = link_copy(adj_[i]);
	out->rem[i] = link_copy(adj_[i]);
    }
    out->p = malloc(sizeof(out->E * sizeof(node *)));
    out->E;
    return out;
}

void bfs(state *in, int start)
{
    int front = 0, back = 0;
    in->q[back++] = start;
    in->dist[start] = 0;
    in->weight[start] = 1.0;
    while (front < back)
    {
	int i = in->q[front++];
	link *j = in->rem[i];
	while (j != NULL)
	{
	    if (in->dist[j->ind] == -1)
	    {
		in->dist[j->ind] = in->dist[i] + 1;
		in->weight[j->ind] = in->weight[i];
		in->q[back++] = j->ind;
	    }
	    else if (in->dist[j->ind] == in->dist[i] + 1)
		in->weight[j->ind] += in->weight[i];
	    j = j->next;
	}
    }
}

void dfs(state *in, int i)
{
    in->vis[i] = 1;
    link *j = in->rem[i];
    while (j != NULL)
    {
	if (in->dist[j->ind] > in->dist[i])
	{
	    if (!in->vis[j->ind])
		dfs(in, j->ind);
	    double bet = ((1.0 + in->under[j->ind]) * 
			  in->weight[i] / in->weight[j->ind]);
	    in->flag = 0;
	    in->local = avl_insert(in->local,
				   min(i, j->ind), max(i, j->ind),
				   bet, &in->flag);
	    in->under[i] += bet;
	}
	j = j->next;
    }
}

void reset(state *in)
{
    for (int i = 0; i < in->N; i++)
    {
	in->dist[i] = -1;
	in->weight[i] = in->vis[i] = in->under[i] = 0;
    }
    in->local = avl_clear(in->local);
}

void record(state *in)
{
    in->global = avl_copy(in->global, in->local);
}

void between(state *in)
{
    in->global = avl_clear(in->global);
    for (int start = 0; start < in->N; start++)
    {
	reset(in);
	bfs(in, start);
	dfs(in, start);
	record(in);
    }
}

void flood(state *in, int start, int num)
{
    int front = 0, back = 0;
    in->q[back++] = start;
    in->comp[start] = num;
    while (front < back)
    {
	int i = in->q[front++];
	link *j = in->rem[i];
	while (j != NULL)
	{
	    if (in->comp[j->ind] == -1)
	    {
		in->comp[j->ind] = num;
		in->q[back++] = j->ind;
	    }
	    j = j->next;
	}
    }
}

void compon(state *in)
{
    for (int i = 0; i < in->N; i++)
	in->comp[i] = -1;
    in->C = 0;
    for (int start = 0; start < in->N; start++)
	if (in->comp[start] == -1)
	    flood(in, start, in->C++);
}

double quality(state *in)
{
    int intra[in->C], inter[in->C];
    memset(intra, 0, sizeof(intra));
    memset(inter, 0, sizeof(inter));
    for (int i = 0; i < in->N; i++)
    {
	link *j = in->adj[i];
	while (j != NULL)
	{
	    inter[in->comp[i]]++;
	    if (in->comp[j->ind] == in->comp[i])
		intra[in->comp[i]]++;
	    j = j->next;
	}
    }
    double mod = 0.0, x, y;
    for (int c = 0; c < in->C; c++)
    {
	x = (double) intra[c] / (double) in->E;
	y = (double) inter[c] / (double) in->E;
	mod += x - y * y;
    }
    return mod;
}

int * cluster(state *in)
{
    int *clust = malloc(in->N * sizeof(int));
    if (clust == NULL)
    {
	printf("clust malloc failed\n");
	exit(1);
    }
    compon(in);
    for (int i = 0; i < in->N; i++)
	clust[i] = in->comp[i];
    double top = quality(in);
    for (int e = in->E; e > 2; e -= 2)
    {
	between(in);
	node *at = avl_max(in->global, in->global);
	in->rem[at->lo] = link_remove(in->rem[at->lo], at->hi);
	in->rem[at->hi] = link_remove(in->rem[at->hi], at->lo);
	compon(in);
	double qual = quality(in);
	// printf("%lf\n", qual);
	if (qual > top)
	{
	    top = qual;
	    for (int i = 0; i < in->N; i++)
		clust[i] = in->comp[i];
	}
    }
    return clust;
}

void cleanup(state *in)
{
    free(in->q);
    free(in->dist);
    free(in->comp);
    free(in->vis);
    free(in->weight);
    free(in->under);
    for (int i = 0; i < in->N; i++)
    {
	in->adj[i] = link_clear(in->adj[i]);
	in->rem[i] = link_clear(in->rem[i]);
    }
    in->local = avl_clear(in->local);
    in->global = avl_clear(in->global);
}
