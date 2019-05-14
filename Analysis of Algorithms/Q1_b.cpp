//#include<iostream>
//#include<vector>
//#include <list>
//#include<string>
//#include <stack>
//#include<fstream>
//#define INF INT_MAX
//using namespace std;
//
//struct neighbor{
//	int vnum;//vertex number
//	int weight; //edge weight
//};
//struct graph{
//	vector< list<neighbor> > edges;
//	vector<neighbor> vertices;
//};
//int nodeCount;
//vector<bool> visited;
//graph G;
//bool makeGraph(string fname){
//	ifstream fin;
//	fin.open(fname);
//	bool start = true;
//	string str;
//	if (fin.is_open()){
//		while (!fin.eof()){
//			if (start)
//			{
//				getline(fin, str);
//				nodeCount = str[0] - '0';
//				start = false;
//			}
//			else{
//				getline(fin, str);
//				//	cout << str<<endl;
//				int i = 2;
//				neighbor n;
//				n.weight = 1;
//				n.vnum = str[0] - '0';
//				G.vertices.push_back(n);
//				bool v = false;
//				visited.push_back(v);
//				list<neighbor> neighborsList;
//				while (i < str.length()){
//					if (str[i] != ' '){
//						neighbor n1;
//						n1.weight = 1;
//						n1.vnum = str[i] - '0';
//						//						cout << "neightbours:" << n1.vnum;
//						neighborsList.push_back(n1);
//					}
//					i++;
//				}
//				//			cout << endl;
//				G.edges.push_back(neighborsList);
//			}
//		}
//		fin.close();
//		return true;
//	}
//	return false;
//}
//vector<int> dist;
//vector<neighbor> parent;
//stack<neighbor>s;
//void explore(neighbor v){
//	visited[v.vnum] = true;
//	for (list<neighbor>::iterator iter = G.edges[v.vnum].begin(); iter != G.edges[v.vnum].end(); iter++){
//		if (!visited[iter->vnum]){
//			explore(*iter);
//		}
//	}
//	int  i = INF;
//	dist.push_back(i);
//	neighbor n;
//	parent.push_back(n);
//	s.push(v);
//
//}
//void topologicalSort(){
//	for (int i = 0; i < G.vertices.size(); i++){
//		//		cout << "DFS:"<<G.vertices[i].vnum;
//		if (!visited[i]){
//			explore(G.vertices[i]);
//		}
//	}
//}
//
//void shortestPathDAG(neighbor source, int m){
//	topologicalSort();
//	stack<neighbor>ss = s;
//	while (s.top().vnum != source.vnum){
//		//	cout << endl<<"n:"<<s.top().vnum;
//		int i = INF;
//		neighbor n;
//		n.vnum = -1;
//		dist[s.top().vnum] = i;
//		parent[s.top().vnum] = n;
//		s.pop();
//	}
//	//s.pop();	//pop source
//	dist[source.vnum] = 0;
//	neighbor p;
//	p.vnum = -1;
//	parent[source.vnum] = p;
//	int i = 0;
//	while (!s.empty()){
//		neighbor n;
//		n = s.top();
//		s.pop();
//		i++;
//
//		for (list<neighbor>::iterator iter = G.edges[n.vnum].begin(); iter != G.edges[n.vnum].end(); iter++){
//			if (i <= m){
//				if (dist[iter->vnum] > dist[n.vnum] + n.weight){
//					dist[iter->vnum] = dist[n.vnum] + n.weight;
//					parent[iter->vnum] = n;
//				}
//			}
//		}
//	}
//	while (!ss.empty()){
//		if (dist[ss.top().vnum]!=INF)
//			cout << endl << "distance of node " << ss.top().vnum << ":" << dist[ss.top().vnum] << " and parent = " << parent[ss.top().vnum].vnum;
//		else
//			cout << endl << "distance of node " << ss.top().vnum << ": Infinity";
//		ss.pop();
//	}
//	cout << endl;
//}
//int main(){
//	string filename = "graph.txt";
//	//	cout << filename << endl;
//	bool c = makeGraph(filename);
//	neighbor n;
//	n.vnum = 0;
//	if(c)
//		shortestPathDAG(n, 2);
//	system("Pause");
//	return 0;
//}