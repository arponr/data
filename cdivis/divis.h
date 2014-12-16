#ifndef DIVIS_H
#define DIVIS_H

#include "avl.h"

typedef struct state state;
struct state
{
    int N, E, C, flag;
    int *q, *dist, *comp, *vis;
    double *weight, *under;
    link **adj, **rem;
    node *local, *global, *max;
    node **p;
};

state * state_constr(int N_, link **adj_);
void bfs(state *in, int start);
void dfs(state *in, int i);
void reset(state *in);
void record(state *in);
void between(state *in);
void flood(state *in, int start, int num);
void compon(state *in);
double quality(state *in);
int * cluster(state *in);
void cleanup(state *in);
    
#endif
