#ifndef AVL_H
#define AVL_H

typedef struct node node;
struct node
{
    int lo, hi, bal;
    double data;
    node *child[2];
};

void avl_print(node *in, int depth);
node * avl_constr(int lo_, int hi_, double data_); 
node * successor(node *in);
node * rotate(node *in, int dir);
node * balance(node *in, int dir);
node * avl_insert(node *in, int lo_, int hi_, double data_, int *flag);
node * avl_remove(node *in, int lo_, int hi_, int *flag);
node * avl_clear(node *in);
node * avl_copy(node *des, node *src);
node * avl_max(node *in, node *out);

#endif
