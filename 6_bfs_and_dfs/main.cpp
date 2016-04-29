#include "graph.cpp"
#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include "cstdlib"

using namespace std;

int main(int argc, char *argv[])
{
	int x = 0;
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

	int y(0);
	int m(0);
	graph g(j , k);
	g.make_graph(argv[1]);
	cout << "Graph has been made successfully\n";
	cout << "How do u wanna search d graph ???\n";
	cout << "\t-> Enter 1 for performing BFS\n";
	cout << "\t-> Enter 2 for performing DFS\n";
	cin >> y ;
	if (y == 1){
		g.print_graph_BFS(); 
		cout<<endl;
		cout << "Enter the source vertex from which BFS should start\n";
		cin >> m;
		if(m < j){
			g.BFS(m,j,k);
			exit(0);
		}
		else {
			cout << "There are only " << j << " vertices in the graph ranked from 0 to "<< (j-1) <<endl;
			cout << "U hv pressed a wrong key\n";
			exit(0);
		}
	}
	else if (y == 2){
		g.print_graph_DFS(); 
		cout<<endl;
		cout << "Enter the source vertex from which DFS should start\n";
		cin >> m;
		if(m < j){
			g.DFS(m,j,k);
			exit(0) ;		
		}
		else {
			cout << "There are only " << j << " vertices in the graph ranked from 0 to "<< (j-1) <<endl;
			cout << "U hv pressed a wrong key\n";
			exit(0);
		}
	}
	else{
		cout << "Wrong selection\n";
		exit(0);
	}
	return 0;
}