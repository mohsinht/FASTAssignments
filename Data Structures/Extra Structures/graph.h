#pragma once
#include <iostream>
#include "singlyLinkedList.h"
#include "queue.h"
#include <list>
using namespace std;


/*
About Graphs:
	Graphs are made up of interlinked nodes. There are edges between nodes.
	Undirected Graph: That is a graph in which nodes are connected bidirectionally.
	Directed Graph: A graph in which nodes are connected in one specified direction. It can be bidirectional.
Examples:
	Websites, Social Networks, Search Engines, Maps etc.

Adjacent Vertex: Nodes directly connected. In directed graph, only the outgoing edges represent adjacent vertices.
Degree Of Vertex: Number of Adjacent vertices of a node.
Adjancency Matrix: Matrix where each row represents a node and each col represents adjacent vertices w.r.t rows.
Adjancency List: LinkedList Array, where each Array index represents a node, and the list in that part is adjacent vertices.

Ways to Traverse a Graph:
	1. BFS			2.DFS

BFS:
	*A start node is passed as a parameter, we start traversing from that node.
	*Each node is marked as visited as we traverse through it once.
	*When we are on a node, we visit all its adjacent vertices first.
	*Distance to each node is also calculated. Distance adjacent vertices is 1.
	*We can add a variable "previous" to keep track of the path.

DFS:
	*Same as BFS, just each node's first neighbour is visited first, then second then so on. When specified destination does not arrive, we backtrack.
*/

template <class T>
class AdjList {
	singlyLinkedList<T>* l;				//adjacency list
	int v;								//num of vertices


	void BFS(int start) {
		int* d = new int[v];			//distace from start node
		int* pre = new int[v];			//previous node
		bool* visited = new bool[v];	//array to mark nodes visited

		ListIterator<T> it;				//iterator to traverse through adjacent vertices
		
		for (int i = 0; i < v; i++) {
			visited[i] = false;
		}
		visited[s] = true;
		pre[s] = -1;
		queue<T> q(v);
		q.enqueue(s);
		int x;
		while (!q.isEmpty()) {
			q.dequeue(x);

			for (it = l[x].Begin(); it != l[x].End(); ++it) {
				int u = *it;
				if (!visited[u]) {
					visited[u] = true;
					d[u] = d[x] + 1;
					pre[u] = x;
					q.enqueue(u);
				}
			}
		}
	}

};