#include <iostream>
#include <list>

using namespace std;


class Graph
{
private:
	int nV;    // No. of vertices
	list<int> *adjList;    // Pointer to an array containing adjacency lists
public:
	Graph(int V);  // Constructor
	void display();
	void addEdge(int v, int w); // function to add an edge to graph
	int* BFS(int s);
};

Graph::Graph(int nV)
{
	this->nV = nV;
	adjList = new list<int>[nV];
}

void Graph::display()
{
	list<int>::iterator j;
	for (int i = 0; i<nV; i++){
		cout << i << "-> ";
		for (j = adjList[i].begin(); j != adjList[i].end(); ++j)
			cout << *j << "  ";
		cout << endl;
	}

}

void Graph::addEdge(int v, int w)
{
	adjList[v].push_back(w); // Add w to v’s list.
	if (v != w)
		adjList[w].push_back(v); // Add w to v’s list.
}
int * Graph::BFS(int s){
	
	int* arr1 = new int[6]; //array of size equal to the number of vertices
	// Mark all the vertices as not visited
	bool *visited = new bool[nV];
	int *cost = new int[nV];
	for (int i = 0; i < nV; i++){
		visited[i] = false;
		cost[i] = 1e5;
	}

	// Create a queue for BFS
	list<int> queue;

	// Mark the current node as visited and enqueue it
	visited[s] = true;
	cost[s] = 0;
	queue.push_back(s);
	arr1[s] = -1; //mark the array element as -1 because s is the root

	// 'i' will be used to get all adjacent vertices of a vertex
	list<int>::iterator i;

	while (!queue.empty())
	{
		s = queue.front();

		// Get all adjacent vertices of the dequeued vertex s
		// If a adjacent has not been visited, then mark it visited
		// and enqueue it
		for (i = adjList[s].begin(); i != adjList[s].end(); ++i)
		{
			if (!visited[*i])
			{
				arr1[*i] = s; //storing 
				visited[*i] = true;
				cost[*i] = cost[s] + 1;
				queue.push_back(*i);
			}
		}

		queue.pop_front();

	}
	return arr1;

}


int main()
{
	// Create a graph given in the above diagram
	Graph g(7); //7 edges 
	//adding edges to the graph
	g.addEdge(0, 1);
	g.addEdge(0, 4);
	g.addEdge(1, 2);
	g.addEdge(2, 5);
	g.addEdge(2, 3);
	g.addEdge(4, 5);

	int* arr2 = new int[6];
	arr2 = g.BFS(0);
	for (int i = 0; i < 6; i++){  //printing the array
		cout << arr2[i] << endl;
	}
	int d = 3;
	cout << "Path from 3 to 0" << endl;       //printing path from a certain destination  
	cout << d << " ";
	while (arr2[d] != -1)    {
		cout << arr2[d] << " ";          //print the value of predecessor until source is reached 
		d= arr2[d];                       // make destination equal to predecessor of destination                    
	}
	cout << endl;
	return 0;
}
