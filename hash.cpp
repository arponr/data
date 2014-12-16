/*
Hash Table
--currently hashing strings--
*/

#include <stdlib.h>
#include <string>
using namespace std;

#define MOD 104729 
#define MAXLEN 100

struct hash_ent
{
   char data [MAXLEN];
   hash_ent *next;
};

hash_ent * hash_t [MOD];

int hash_f (char in [])
{
   int out;
   char *p;
   for (p = in; *p; p++)
      out = (out * 1997 + *p) % MOD;
   return out;
}

void hash_insert(char in [])
{
   hash_ent *h = (hash_ent *) malloc (sizeof (hash_ent));
   strcpy (h->data, in);
   int val = hash_f (in);
   h->next = hash_t [val];
   hash_t [val] = h;
}

bool hash_lookup (char in [])
{
   int val = hash_f (in);
   hash_ent *h;
   for (h = hash_t [val]; h; h = h->next)
      if (strcmp (in, h->data) == 0)
	 return true;
   return false;
}
