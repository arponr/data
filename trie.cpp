/*
  Prefix Tree / Trie
  ----implemented for lowercase dictionary
*/
#include <cstdlib>
using namespace std;

class trie
{
   const int N = 26;
   
   struct node
   {
      bool word;
      node *next [N];
      
      node ()
      {
	 word = false;
	 memset (next, NULL, sizeof (next));
      }
   } *root;

public:
   void add (char *str)
   {
      node *t = root; char *p; int value;
      
      for (p = str; *p; p++)
      {
	 value = *p - 'a';
	 if (t->next [value] == NULL)
	    t->next [value] = new node ();
	 t = t->next [value];
      }
      t->word = true;
   }
   
   bool lookup (char *str)
   {
      node *t = root; char *p; int value;
      
      for (p = str; *p; p++)
      {
	 value = *p - 'a';
	 if (t->next [value] == NULL)
	    return 0;
	 t = t->next [value];
      }
      return t->word;
   }
}

