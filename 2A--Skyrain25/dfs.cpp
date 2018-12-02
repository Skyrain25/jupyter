// For simplicity, assume 
//      1. V = {0, 1, 2, ..., n-1}
//      2. Edges input as unordered pairs (from stdin)
//      3. The graph is an undirected graph
//      4. Adjacency list representation to be used

#include <iostream>
#include <vector>
#include <list>
#include <string>

using namespace std;

string order(int x)
{
  cerr<<x;
  
  switch(x % 10)
   {
     case 1: return "-st";
             break;
     case 2: return "-nd";
             break;
     case 3: return "-rd";
             break;

     default: return "-th";
    }
}


class Node
{ 
  public:
  
   unsigned visited = 0; //not yet visited
   int component = -1;//component not assigned
};


using Edges=vector<list<int>>;
using Nodes=vector<Node>;

class Graph
{
  public:
    Nodes V;
    Edges E;      	
};

int max(int a, int b, int c)
{
    return (a > b)? (a > c)?a:c: (b > c)? b: c;
}


//read edges in "edge-list" format 
Edges getEdges( )
{ 
	unsigned u, v;
	Edges adj_list;
	
	 while (cin>>u>>v)
	 {
            if( u != v)
              {
		 adj_list.resize(max(adj_list.size(),u+1,v+1));
		 adj_list[u].push_back(v);
		 adj_list[v].push_back(u);		 
              }
	  } 
	  
	  return adj_list;

}

void dfs(unsigned v, Graph& g, unsigned& count)
{
	count++;
	g.V[v].visited = count;
	
  	for(auto w: g.E[v])//iterate over neighbours of node v
  	  if ( g.V[w].visited == 0 )
		dfs(w, g, count);
	
}

void mainDFS(const Edges& E)
{
  Graph G;	 
  
  G.V.resize(E.size());
  G.E = E; //Hopefully the compiler optimizes this 
  unsigned counter = 0;

  unsigned max_comp_name = 0; // name of maximum component
  unsigned max_comp_size = 0; // size of maximum component
 

  for(unsigned i = 0; i < G.V.size(); i++)//iterate over nodes
    {
	   if(G.V[i].visited == 0)
	     {		     
	       dfs(i, G, counter);		
	      }  
     }  	
      	
  cerr<<"DFS Ranks:"<<endl;
   
  for(unsigned i =0; i < G.V.size();i++)
  {
    cerr << i<<" visited "<< order(G.V[i].visited) << endl;
   }

//--------------DO NOT EDIT BELOW!!!----------------------//
cerr<<"Name of maximum component = ";    
cout<<max_comp_name;
cerr<<endl<<"Maximum component size =";
cout<<" "<<max_comp_size<<endl; 
}
	
	


int main()
{
  Edges edges = getEdges();
  unsigned m = 0;
  
  cerr<<"Read "<<edges.size()<<" nodes "<<endl;
  
  
  for(auto e: edges)
    m+= e.size(); 


 cerr<<"Read "<<m<<" edges "<<endl;
 
 mainDFS(edges);

}



