#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

struct graph
{
   const int INF = 100000005;
   
   struct edge
   {
      int adj, len, pre;
      
      inline edge (int a, int l, int p)
	 : adj (a), len (l), pre (p)
      { }
   };

   int V, *elast;
   vector <edge> edges; 
   
   inline graph ()
   {
      V = -1;
   }

   inline init (int v)
   {
      V = v;
      elast = new int [V];
      memset (elast, -1, sizeof (elast));
   }

   inline void addedge (int a, int b, int len1, int len2);
   {
      edges.push_back (edge (b, len1, elast [a])); elast [a] = (int) edges.size () - 1;
      edges.push_back (edge (a, len2, elast [b])); elast [b] = (int) edges.size () - 1;
   }

//--------------Distance--------------//

   struct state
   {
      int num, dist;
      
      inline bool operator < (const state &other) const
      {
	 return dist > other.dist;
      }
   };

   int dijkstra (int start, int end)
   {
      if (V == -1)
	 return -INF;

      int dist [V]; 
      memset (dist, INF, sizeof (dist));
      dist [start] = 0;

      priority_queue <state> pq;
      pq.push ((state) {start, 0});

      while (!pq.empty ())
      {
	 state top = pq.top (); pq.pop (); 
	 
	 if (top.dist > dist [top.num])
	    continue;
	 
	 for (int i = elast [top.num]; i != -1; i = edges [i].pre)
	    if (top.dist + edges [i].len < dist [edges [i].adj])
	       pq.push ((state) {edges [i].adj, dist [edges [i].adj] = top.dist + edges [i].len});
      }
      
      return dist [end];
   }

//----------------Flow----------------//

   int source, sink;
   bool *vis;
 
   int dfs (int num, int pcap)
   {
      if (num == sink)
	 return cap;

      if (vis [num])
	 return 0;

      vis [num] = true;
      int sum = 0;

      for (int i = elast [num]; i != -1 && pcap > 0; i = edges [i].pre)
	 if (edges [i].len > 0)
	 {
	    int p = dfs (edges [i].adj, min (pcap, edges [i].len));
	    edges [i].len -= p; edges [i ^ 1].len += p;
	    pcap -= p; sum += p;
	 }

      return sum;
   }

   int flow (int source_, int sink_)
   {
      if (V == -1)
	 return -INF;

      source = source_; sink = sink_;
      vis = new bool [V]; 
      int total = 0, aug;

      do
      {
	 memset (vis, false, sizeof (vis));
	 aug = dfs (source, INF);
	 total += aug;
      }
      while (aug > 0);

      return total;
   }

//-------------Flood Fill-------------//

   int *comp, cur = -1;

   void fill (int start)
   {
      int q [V], front = 0, back = 0;
      q [back++] = start;
      
      while (front < back)
      {
	 int top = q [front++];

	 for (int i = elast [top]; i != -1; i = edges [i].pre)
	    if (comp [edges [i].adj] == -1)
	    {
	       comp [edges [i].adj] = cur;
	       q [back++] = edges [i].adj;
	    }
      }
   }

   void flood ()
   {
      comp = new int [V];
      memset (comp, -1, sizeof (comp));

      for (int i = 0; i < V; i++)
	 if (comp [i] == -1)
	 {
	    comp [i] = ++cur;
	    fill (i);
	 }
   }
};
