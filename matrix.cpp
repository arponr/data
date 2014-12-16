#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

struct matrix
{
   int M, N;
   double *data;
   
   matrix (int m, int n)
      : M (m), N (n), data (new double [m * n])
   { 
      memset (data, 0.0, sizeof (data));
   }

   void read ()
   {
      for (int i = 0; i < M; i++)
	 for (int j = 0; j < N; j++)
	    scanf ("%lf", data + i * M + j);
   }

   void print ()
   {
      for (int i = 0; i < M; i++)
      {
	 printf ("[");
	 for (int j = 0; j < N; j++)
	    (j < N - 1) ? printf ("%lf, ", data [i * M + j]) : printf ("%lf]\n", data [i * M + j]);
      }
      printf ("\n");
   }	       

   inline double operator () (int r, int c) const
   {
      return data [r * M + c];
   }

   inline double & operator () (int r, int c)
   {
      return data [r * M + c];
   }

   inline matrix operator * (const matrix &other) const
   {
      matrix prod (M, other.N);
      
      for (int i = 0; i < prod.M; i++)
	 for (int j = 0; j < prod.N; j++)
	    for (int k = 0; k < N; k++)
	       prod (i, j) += data [i * M + k] * other (k, j);

      return prod;
   }

   inline matrix operator * (const double &coef) const
   {
      matrix prod (M, N);
      
      for (int i = 0; i < prod.M; i++)
	 for (int j = 0; j < prod.N; j++)
	    prod (i, j) = coef * data [i * M + j];

      return prod;
   }
};

int main ()
{
   matrix a (2, 2), b (2, 2);
   a.read (); b.read ();
   a = a * b;
   b = b * 2;
   a.print (); b.print ();
}
