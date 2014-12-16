/*
  AVL Tree
*/

#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

struct node
{
   int data;
   node *lchild, *rchild;

   node (int data_)
      : data (data_), lchild (NULL), rchild (NULL)
   { }

} *root = NULL;


void print (node*& in, int h)
{
   if (in)
   {
      print (in->rchild, h + 1);

      for (int i = 0; i < 2 * h + 1; i++)
	 printf (" ");
      printf ("%d\n", in->data);

      print (in->lchild, h + 1);
   }
}

node* successor (node*& in)
{
   node *temp = in->rchild, *suc = NULL;
   while (temp != NULL)
   {
      suc = temp;
      temp = temp->lchild;
   }
   return suc;
}

inline int height (node*& in)
{
   if (in == NULL)
      return 0;

   return max (height (in->lchild), height (in->rchild)) + 1;
}

inline void lrot (node*& in)
{
   node *orig = in;
   in = in->rchild;
   orig->rchild = in->lchild;
   in->lchild = orig;
}

inline void rrot (node*& in)
{
   node *orig = in;
   in = in->lchild;
   orig->lchild = in->rchild;
   in->rchild = orig;
}

void balance (node*& in, int data_, int sign)
{
   int bal = height (in->lchild) - height (in->rchild);

   if (bal == -2)
   {
      if (sign * data_ < sign * in->rchild->data)
	 rrot (in->rchild);
      lrot (in);
   }
   else if (bal == 2)
   {
      if (sign * data_ > sign * in->lchild->data)
	 lrot (in->lchild);
      rrot (in);
   }
}

void insert (node*& in, int data_)
{
   if (in == NULL)
      in = new node (data_);
   else if (data_ < in->data)
   {
      insert (in->lchild, data_); 
      balance (in, data_, 1);
   }
   else 
   {
      insert (in->rchild, data_);
      balance (in, data_, 1);
   }
}

void remove (node*& in, int data_)
{ 
   if (data_ < in->data)
   {
      remove (in->lchild, data_);
      balance (in, data_, -1);
   }
   else if (data_ > in->data)
   {
      remove (in->rchild, data_);
      balance (in, data_, -1);
   }
   else if (in->lchild == NULL || in->rchild == NULL)
   {
      delete in;
      in = (in->lchild == NULL && in->rchild == NULL) ? NULL : (in->lchild == NULL ? in->rchild : in->lchild);
   }
   else
   {
      node *suc = successor (in);
      in->data = suc->data;
      remove (in->rchild, suc->data);
   }
}

int main ()
{
   printf ("\nThis is a self-balancing binary search tree which stores integers!\n\n");

   do
   {
      printf ("Type a number from 1 to 4 to complete the respective operation listed below:\n1. Print tree\n2. Insert data\n3. Remove data\n4. Exit\n\n");

      int op; scanf ("%d", &op);
      printf ("\n");

      if (op == 1)
      {
	 print (root, 0);
	 printf ("\n\n");
      }
      else if (op == 2)
      {
	 printf ("Type the number of entries you will be inserting, and then that many integers (all space-separated)\n\n");
	 int n; scanf ("%d", &n);
	 for (int i = 0, t; i < n; i++)
	 {
	    scanf ("%d", &t);
	    insert (root, t);
	 }
	 printf ("\n");
      }
      else if (op == 3)
      {
	 printf ("Type the number of entries you will be removing, and then that many integers (all space-separated)\n\n");
	 int n; scanf ("%d", &n);
	 for (int i = 0, t; i < n; i++)
	 {
	    scanf ("%d", &t);
	    remove (root, t);
	 }
	 printf ("\n");
      }
      else if (op == 4)
	 break;
   }
   while (true);
}
	
