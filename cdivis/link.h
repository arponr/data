#ifndef LINK_H
#define LINK_H

typedef struct link link;
struct link
{
    int ind;
    link *next;
};

link * link_constr(int ind_);
link * link_copy(link *in);
int link_length(link *in);
link * link_remove(link *in, int ind_);
link * link_clear(link *in);

#endif
