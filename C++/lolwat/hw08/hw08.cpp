//Brian Chuk


// Assumption: The vertices of the graph are labeled from 0 to n - 1,
// where n is the number of vertices.

#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <map>
using namespace std;

const int DEFAULT_VAL =  -1;      // must be less than 0

typedef vector<list<int>> Graph;        // The graph is given in an adjacency list.
                                         // Vertices are indexed from 0 to V-1
                                         // The indices of the vertices adjacent to vertex i
                                         // are in the list Graph[i].
                                         // Graph can be directed or undirected.

struct vertexInf {                    // Stores information for a vertex                                   
    int dist;  // distance to vertex from the source
    int prev;  // previous node in BFS tree
};

void printpath(int j,  vector<vertexInf> & vinfo) {
    stack<int> t;

    int current = j;
    while (current != DEFAULT_VAL) {
       t.push(current);
       current = vinfo[current].prev;
    }
    while (!t.empty()) {
       cout << t.top() << " ";
       t.pop();
    }
}
     


// Breadth First Search
// The unweighted shortest path algorithm on the graph g, with vertex i as the source
// Prints the length (number of edges) of the shortest path from the source to every vertex
// in the graph

void shortestpaths( Graph & g, int s) {
    queue<int> q;             // q is the queue of vertex numbers

    if (s < 0 || s > g.size()-1) {
          cout << "Bad index" << endl;
           return;
    }

    vector<vertexInf> vertices(g.size());               // stores BFS info for the vertices
                                                        // info for vertex j is in position j

    for (int j=0; j < vertices.size(); ++j)                 // Initialize distances and prev values
        { vertices[j].dist = DEFAULT_VAL; vertices[j].prev = DEFAULT_VAL; }   


    vertices[s].dist = 0;

    q.push(s);
    while  (!q.empty() )
    {
      int v = q.front();
      q.pop();
      for (list<int>::const_iterator w = g[v].begin(); w != g[v].end(); w++)
      { 

            if (vertices[*w].dist == DEFAULT_VAL)          // distance of *w from source not determined yet
            {
                vertices[*w].dist = vertices[v].dist+1;
                vertices[*w].prev = v;
                q.push(*w);
            }
      }
    }
    for (int j = 0; j < vertices.size(); j++)        // print distances from source and paths
    {
           cout << "vertex " << j << endl;
           cout << "distance: " << vertices[j].dist << endl;
           cout << "shortest path: "; 
           printpath(j,vertices); 
           cout << "\n" << endl;
    } 
}


// A driver to test the algorithm.  Constructed graph is
//
//               1
//               *
//       0    2 / \
//       *-----*---*3
//             |   |
//             |   |
//            5*---*4
//
//
int main() {
     Graph g(6);

     g[0].push_back(2);
     g[1].push_back(3);
     g[1].push_back(2);
     g[2].push_back(3);
     g[2].push_back(5);
     g[2].push_back(1);
     g[2].push_back(0);
     g[3].push_back(1);
     g[3].push_back(2);
     g[3].push_back(4);
     g[5].push_back(4);
     g[4].push_back(5);
     g[4].push_back(3);
     g[5].push_back(2);

     shortestpaths(g,1);
}