#include <stdio.h>
#include <stdlib.h>
#include "tools.h"
#include "avl.h"

void avl_print(node *in, int depth)
{
    if (in != NULL)
    {
        avl_print(in->child[1], depth + 1);
        for (int i = 0; i < 10 * depth + 1; i++)
            printf(" ");
        printf("(%d,%d,%lf)\n", in->lo, in->hi, in->data);
        avl_print(in->child[0], depth + 1);
    }
}

node *avl_constr(int lo_, int hi_, double data_)
{
    node *out = malloc(sizeof(node));
    if (out == NULL)
    {
        printf("node constr failed\n");
        exit(1);
    }
    out->lo = lo_;
    out->hi = hi_;
    out->data = data_;
    out->bal = 0;
    out->child[0] = out->child[1] = NULL;
    return out;
}

node *successor(node *in)
{
    node *temp = in->child[1], *succ = NULL;
    while (temp != NULL)
    {
        succ = temp;
        temp = temp->child[0];
    }
    return succ;
}

node *rotate(node *in, int dir)
{
    node *out = in->child[dir];
    in->child[dir] = out->child[!dir];
    out->child[!dir] = in;
    return out;
}

node *balance(node *in, int dir)
{
    if (-2 * in->child[dir]->bal == in->bal)
    {
        int det = in->child[dir]->child[!dir]->bal;
        if (det == 0)
            in->bal = in->child[dir]->bal = 0;
        else if (det == in->child[dir]->bal)
        {
            in->bal = 0;
            in->child[dir]->bal = -det;
        }
        else
        {
            in->bal = -det;
            in->child[dir]->bal = 0;
        }
        in->child[dir]->child[!dir]->bal = 0;
        in->child[dir] = rotate(in->child[dir], !dir);
        in = rotate(in, dir);
    }
    else
    {
        in->bal = in->child[dir]->bal = 0;
        in = rotate(in, dir);
    }
    return in;
}

node *avl_insert(node *in, int lo_, int hi_, double data_, int *flag)
{
    if (in == NULL)
    	in = avl_constr(lo_, hi_, data_);
    else if (in->lo == lo_ && in->hi == hi_)
    {
        in->data += data_;
        *flag = 1;
    }
    else
    {
        int dir = less(in->lo, in->hi, lo_, hi_);
        in->child[dir] = avl_insert(in->child[dir], lo_, hi_, data_,
                                    flag);
        if (!*flag)
        {
            in->bal += hom(dir);
            if (in->bal == 0)
                *flag = 1;
            else if (in->bal == 2 * hom(dir))
            {
                in = balance(in, dir);
                *flag = 1;
            }
        }
    }
    return in;
}

node *avl_remove(node *in, int lo_, int hi_, int *flag)
{
    if (lo_ == in->lo && hi_ == in->hi)
    {
        if (in->child[0] == NULL || in->child[1] == NULL)
        {
            node *out = in->child[in->child[0] == NULL];
            free(in);
            in = NULL;
            return out;
        }
        node *succ = successor(in);
        in->lo = succ->lo;
        in->hi = succ->hi;
        in->data = succ->data;
        in->child[1] = avl_remove(in->child[1], succ->lo, succ->hi,
                                  flag);
    }
    else
    {
        int dir = less(in->lo, in->hi, lo_, hi_);
        in->child[dir] = avl_remove(in->child[dir], lo_, hi_, flag);
        if (!*flag)
        {
            in->bal -= hom(dir);
            if (in->bal == 0)
                *flag = 1;
            else if (in->bal == -2 * hom(dir))
            {
                in = balance(in, !dir);
                in->bal = 0;
                *flag = 1;
            }
        }
    }
    return in;
}

node *avl_clear(node *in)
{
    if (in != NULL)
    {
        in->child[0] = avl_clear(in->child[0]);
        in->child[1] = avl_clear(in->child[1]);
        free(in);
    }
    return NULL;
}

node *avl_copy(node *des, node *src)
{
    if (src != NULL)
    {
        int flag = 0;
        des = avl_insert(des, src->lo, src->hi, src->data, &flag);
        des = avl_copy(des, src->child[0]);
        des = avl_copy(des, src->child[1]);
    }
    return des;
}

node *avl_max(node *in, node *out)
{
    if (in == NULL)
        return out;
    if (in->data > out->data)
        out = in;
    out = avl_max(in->child[0], out);
    out = avl_max(in->child[1], out);
    return out;
}
