#include <cstdlib>
using namespace std;

template <typename T>
class heap 
{
   int size;
   T *list;

   void swap (T &a, T &b)
   {
      T temp = a;
      a = b;
      b = temp;
   }

   void upheap (int i, int j)
   {
      if (list [j] < list [i])
      {
	 swap (list [i], list [j]);
	 upheap ((i - 1) / 2, i);
      }
   }

   void downheap (int i)
   {
      int a = 2 * i + 1, b = 2 * i + 2, child = i;
      if (list [a] < list [b] && a < size)
	 child = a;
      else if (b < size)
	 child = b;

      if (list [child] < list [i])
      {
	 swap (list [child], list [i]);
	 downheap (child);
      }
   }

public:
   heap (int max)
      : size (0), list (new T [max])
   { }

   bool empty ()
   {
      return (size == 0);
   }

   void push (T data)
   {
      list [size] = data;
      upheap ((size - 1) / 2, size);
      size++;
   }
   
   T pop ()
   {
      swap (list [0], list [--size]);
      downheap (0);
      return list [size];
   }
};
