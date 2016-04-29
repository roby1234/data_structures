#include "graph.cpp"
#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include "cstdlib"

using namespace std;

int main(int argc, char *argv[])
{
	ifstream File;
	File.open(argv[1]);
	string s;
	int j(0);				//no of vertices
	int k(0);				//no of edges
	while(!File.eof()){
		getline(File , s);
		if(s.length() != 0){
			for (int i = 0; i < s.length(); ++i){
				if(s.at(i) != ' '){
					if(s.at(i) != '0'){
						k++;
					}
				}
			}
		}
		j++;
	}
	cout << "No. of vertices in graph = "<< j <<endl;
	cout << "No. of edges in graph = "<< k <<endl;

	int m(0);
	int y(0);

	graph* g = new graph(j , k);
	g->make_graph(argv[1]);
	cout << "\n\nAdjacency List:: \n\n";
	g->print_graph();
	cout << "Graph has been made successfully\n";
	cout << "What do u wanna do ???\n";
	cout << "\t-> Enter 1 for performing BFS\n";
	cout << "\t-> Enter 2 for performing DFS\n";
	cout << "\t-> Enter 3 for making MST using Kruskal's Algorithm\n";
	cout << "\t-> Enter 4 for making MST using Prim's Algorithm\n";


	cin >> y ;
	if (y == 1){
		cout << "Enter the source vertex from which BFS should start\n";
		cin >> m;
		if(m < j){
			g->BFS(m,j,k);
			return 0;
		}
		else {
			cout << "There are only " << j << " vertices in the graph ranked from 0 to "<< (j-1) <<endl;
			cout << "U hv pressed a wrong key\n";
			return 0;
		}
	}
	else if (y == 2){
		cout << "Enter the source vertex from which DFS should start\n";
		cin >> m;
		if(m < j){
			g->DFS(m,j,k);
			return 0 ;		
		}
		else {
			cout << "There are only " << j << " vertices in the graph ranked from 0 to "<< (j-1) <<endl;
			cout << "U hv pressed a wrong key\n";
			return 0;
		}
	}
	else if (y == 3){
		graph* z = g->create_graph(j,k);
		z->Kruskal_MST(g);
		return 0;
	}
	else if (y == 4){
		graph* z = g->create_graph(j,k);
		z->Prim_MST(g);
		return 0;
	}
	else{
		cout << "Wrong selection\n";
		exit(0);
	}
	return 0;
}

