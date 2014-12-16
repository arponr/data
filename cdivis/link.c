#include <stdio.h>
#include <stdlib.h>
#include "link.h"

link * link_constr(int ind_)
{
    link *out = malloc(sizeof(link));
    if (out == NULL)
    {
	printf("link malloc failed\n");
	exit(1);
    }
    out->ind = ind_;
    out->next = NULL;
    return out;
}

link * link_copy(link *in)
{
    if (in == NULL)
	return NULL;
    link *out = link_constr(in->ind);
    out->next = link_copy(in->next);
    return out;
}	

int link_length(link *in)
{
    int len = 0;
    while (in != NULL)
    {
	len++;
	in = in->next;
    }
    return len;
}

link * link_remove(link *in, int ind_)
{
    if (in->ind == ind_)
    {
	link *out = in->next;
	free(in);
	return out;
    }
    in->next = link_remove(in->next, ind_);
    return in;
}

link * link_clear(link *in)
{
    if (in == NULL)
	return NULL;
    in->next = link_clear(in->next);
    free(in);
    return NULL;
}
