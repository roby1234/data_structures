#include "graph.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include <string>
#include "stack_queue.cpp"
#include "stdlib.h"

using namespace std;

int max_wt(const void* a , const void* b){
	edges* a1 = (edges*)a ;
	edges* b1 = (edges*)b ;
	return a1->get_wt() > b1->get_wt();
}


edges::edges(){

	source = -1;
	destination = -1;
	weight = -1;
}

int edges::get_src(){
	return source;
}

int edges::get_dest(){
	return destination;
}

int edges::get_wt(){
	return weight;
}

void edges::set_src(int a){
	source = a;
}

void edges::set_dest(int a){
	destination = a;
}

void edges::set_wt(int a){
	weight = a;
}

/***********************************************************************************************/

disjoint_set::disjoint_set(){
	rank = -1;
	parent = -1;
}

int disjoint_set::get_rank(){
	return rank;
}

int disjoint_set::get_parent(){
	return parent;
}

void disjoint_set::set_rank(int r){
	rank = r;
}

void disjoint_set::set_parent(int p){
	parent = p;
}

int disjoint_set::find(disjoint_set set[] , int i){
	if(set[i].get_parent() != i){
		set[i].set_parent(find(set , set[i].get_parent()));
	} 
	//cout<< "Parent of " << i << " is "<<set[i].get_parent()<<endl<<endl;

	return set[i].get_parent();
}

void disjoint_set::do_union(disjoint_set set[] , int x ,int y){
	int x_root = find(set , x);
	int y_root = find(set , y);
	if(set[x_root].get_rank() < set[y_root].get_rank()){
		set[x_root].set_parent(y_root);
		cout << "parent of "<< x <<" has been set to parent of "<<y<<endl;  
	}
	else if(set[x_root].get_rank() > set[y_root].get_rank()){
		set[y_root].set_parent(x_root);
		cout << "parent of "<< y <<" has been set to parent of "<<x<<endl; 
	}
	else{
		set[y_root].set_parent(x_root);
		cout << "parent of "<< x <<" has been set to parent of "<<y<<endl; 
		set[x_root].set_rank((set[x_root].get_rank()) + 1);
		cout << "rank of parent of "<< x <<" has been increased by one "<<endl; 
	}
	cout << x << " and " <<y << " are united to the same disjoint set\n\n";
}



/********************************************************************************************/



graph::graph(int v , int e){
	no_of_vertices = v;
	no_of_edges = e ;
	adj_list = new linked_list(v);
	edge = new edges[e] ;
	
}

graph::~graph(){
	delete[] adj_list;
}

int graph::get_no_of_vertices(){
	return no_of_vertices;
}

int graph::get_no_of_edges(){
	return no_of_edges;
}

void graph::set_no_of_vertices(int a){
	no_of_vertices = a;
}

void graph::set_no_of_edges(int a){
	no_of_edges = a;
}

/*edges* graph::get_edge(){
	return edge; 
}*/

graph* graph::create_graph(int v , int e){
	graph* g = new graph(v ,e);
	g->set_no_of_vertices(v);
	g->set_no_of_edges(e);
	g->adj_list = new linked_list(v);
	g->edge = new edges[e];
	//cout << g->get_no_of_vertices()<<endl;
	//cout << g->get_no_of_edges()<<endl;
	return g;
}


void graph::make_graph(char a[]){			
	ifstream File;
	File.open(a);
	if(File.is_open()){
		string s;
		int j(0);				//no of vertices
		int k(0);				//no of edges
		while(!File.eof()){
			getline(File , s);
			if(s.length() != 0){
				for (int i = 0; i < s.length(); ++i){
					if(s.at(i) != ' '){
						if(s.at(i) != '0'){
							int m = s.at(i);
							add_edge(j , (i/2) , m - 48);
							insert_edge(k , j , i/2 , m-48);
							k++;
						}
					}
				}
			}
			j++;
		}
		File.close();
		return;
	} 
	else 
		cout << "U hv messed it up. File has not been opened\n";
	return;
}

int graph::insert_edge(int k ,int u , int v , int w){
	edge[k].set_src(u);
	edge[k].set_dest(v);
	edge[k].set_wt(w);
}

int graph::add_edge(int u , int v , int w){		//edge from u to v with weight w is added to graph
	adj_list->insertlist(v,u,w);
	cout << "A new edge from "<< u << " to " << v <<" with weight "<< w << " has been inserted \n\n";
}

void graph::print_edge(int i){
	cout << "\tSource = "<< edge[i].get_src()<<"\t";
	cout << "\tDestination = "<< edge[i].get_dest()<<"\t";
	cout << "\tWeight = "<< edge[i].get_wt()<<endl<<endl;
} 


void graph::print_graph(){
	for (int i = 0; i < no_of_vertices; ++i){
		cout << i << " have edges with\n";
		cout << "\t->\t";
		adj_list->printlist(i);
		cout << endl<<endl;
	}
}

int graph::iscycle(graph* g){
	int V = g->get_no_of_vertices();
	int E = g->get_no_of_edges();

	disjoint_set *d;
	d = new disjoint_set[V];

	for (int v = 0; v < V; ++v){
		d[v].set_parent(v);
		d[v].set_rank(0);
	}

	for (int e = 0; e < E; ++e){
		int x = d->find(d , g->edge[e].get_src());
		int y = d->find(d , g->edge[e].get_dest());
		if(x == y){
			return 1;
			cout << "By including this edge , it forms a cycle ,\n";
			cout << "So the edge is ignored\n\n"; 
		} 
		d->do_union(d,x,y);
	}
	return 0;
}

void graph::Kruskal_MST(graph* g){
	int V = g->get_no_of_vertices();
	int E = g->get_no_of_edges();
	//cout<<"no of vertices = "<<V<<endl;
	graph* final = new graph(V , E);
	int e(0);
	int i(0);

	qsort(g->edge , g->get_no_of_edges() , sizeof(g->edge[0]) , max_wt);
	cout << "Edges are sorted according to their weights\n\n";

	for (int i = 0; i < E; ++i){
		g->print_edge(i);
	}
	
	//cout << "edge 1 bw "<<(g->edge[0].get_src())<<" and " <<(g->edge[4].get_dest())<<endl;
	disjoint_set *set;
	set = new disjoint_set[V];

	for (int v = 0; v < V; ++v){
		set[v].set_parent(v);
		cout << "parent of "<<v<< " is set to "<<set[v].get_parent()<<endl;
		set[v].set_rank(0);
		cout << "rank of "<<v<< " is set to "<<set[v].get_rank()<<endl<<endl;;
	}
	//cout<<"no of vertices = "<<V<<endl;
	while(e < V-1){
		edges next_edge = g->edge[i++];
		cout<<"Source of current edge "<<next_edge.get_src()<<endl;
		cout<<"Destination of current edge = "<<next_edge.get_dest()<<endl<<endl;
		int x = set->find(set , next_edge.get_src());
		int y = set->find(set , next_edge.get_dest());
		if (x == y){
			cout << "Cycle formation , Edge rejected\n\n\n";
		}
		else if (x != y){
			final->add_edge(next_edge.get_src() , next_edge.get_dest() , next_edge.get_wt());
			set->do_union(set,x,y);	
			e++;
		}
	}
	cout << "The MST has been formed using Kruskal's Algorithm\n\nFinal Graph::\n";
	final->print_graph();
}


void graph::print_graph_BFS(){
	cout << "Graph :: till now \n";
	for (int i = 0; i < no_of_vertices; ++i){
		cout << i << " have edges with\n";
		cout << "\t->\t";
		adj_list->printlist(i);
		cout << endl;
	}
}

void graph::BFS(int &source , int n , int e){
	graph* y = new graph(n ,e);

	int* color = new int[n];
	int* distance = new int[n];
	int* pred = new int[n];
	int u;
	for (int i = 0; i < n ; ++i){
		color[i] = 0;			//undiscoverd vertices are colored White
		pred[i] = -1;
		distance[i] = -1;
	}

	int p(n); 					//keeps track of no. of unvisited vertices
	
	queue<int> q(n);
	cout << "queue of size " << n << " has been formed\n";
	q.enqueue(source);
	distance[source] = 0;		//first vertex discovered , distance from source = 0
	color[source] = 1 ;			//discoverd vertex is colored
	pred[source] = -1;			//predecessor is nil for the first vertex

	p--;
	cout <<"Still " << p << " vertices are left unvisited\n\n";
	//q.print_queue();

	while(! q.is_empty()){
		u = q.return_front();
		cout << "Element retrieved from queue is = "<< u <<endl<<endl;
		q.dequeue();
		color[u] = 2; 

		node* pointer = (adj_list->get_head(u));
		while(pointer != NULL){
			int v = pointer->get_element();
			int w = pointer->get_weight();
			if(v != -1){
				cout << "Current Element = " << v << endl;
				if(color[v] == 0){
					color[v] = 1;
					distance[v] = distance[u] + 1;
					pred[v] = u;
					y->add_edge(u , v , w);
					y->add_edge(v , u , w);
					q.enqueue(v);
					p--;
					cout <<"Still " << p << "vertices are left unvisited\n\n";
					y->print_graph_BFS();
				}
				else
					cout << "Path bw "<< u << " and " <<v << " already exists\n";
				cout << endl;
				pointer = pointer->get_next();
			}
			else{
				cout << "There does not exist edge from " << u <<" to any vertex\n";
				q.dequeue();
				color[v] = 2;
				break;
			}
		}
	}
	cout << "Here ends one connected component and the other one starts\n\n";

	int a[n];
	while(p != 0){
		for (int i = 0; i < n; ++i){
			a[i] = 0;
		}

		for (int i = 0; i < n; ++i){
			if(color[i] == 0){
				cout << "vertex "<< i <<" was left unvisited\n\n\n" ;
				a[i] = 1 ;
			}
			else{
				continue;
			}
		}
	
		cout << "\nNo. of vertices left unvisited = "<< p <<"\n\n";

		for (int i = 0; i < n; ++i){
			if(a[i] == 1){
				queue<int> q(p);
				distance[i] = 0;
				color[i] = 1 ;
				pred[i] = -1;
				cout << "Vertex "<< i <<" has been choosen as source now\n\n";
				cout << "queue of size " << p << " has been formed\n\n";
				q.enqueue(i);
				a[i]= 0;
				p--;
				cout <<"Still " << p << "vertices are left unvisited\n\n";
				//q.print_queue();

				while(! q.is_empty()){
					u = q.return_front();
					cout << "Element retrieved from queue is = "<< u <<endl<<endl;
					q.dequeue();
					color[u] = 2; 

					node* pointer = (adj_list->get_head(u));
					while(pointer != NULL){
						int v = pointer->get_element();
						int w = pointer->get_weight();
						if(v != -1){
							cout << "Current Element = " << v << endl;
							if(color[v] == 0){
								color[v] = 1;
								distance[v] = distance[u] + 1;
								pred[v] = u;
								y->add_edge(u , v , w);
								y->add_edge(v , u , w);
								q.enqueue(v);
								a[u] = 0;
								p--;
								cout <<"Still " << p << "vertices are left unvisited\n\n";
								y->print_graph_BFS();
							}
							else
								cout << "Edge bw "<< u << " and " <<v << " already exists\n\n";
							cout << endl;
							pointer = pointer->get_next();
						}
						else{
							cout << "There does not exist edge from " << u <<" to any vertex\n\n";
							q.dequeue();
							color[v] = 2;
							break;
						}
					}
				}
			}
			else
				continue;
			cout << "Here ends one connected component and the other one starts\n\n";
			break;
		}
	}	

	cout <<"The whole graph has been searched \n\nThe final graph is \n\n";
	y->print_graph_BFS();
	cout << endl<<endl;
	cout <<"Distance of each edge from the source is \n";
	for (int i = 0; i < n; ++i){
		cout << "Distance of " << i << " from source is " << distance[i] << "\n"; 
		cout << "Predecessor of " << i <<" is equal to " <<  pred[i] << "\n\n"; 
	}
}

void graph::print_graph_DFS(){
	cout << "Graph :: till now \n";
	for (int i = 0; i < no_of_vertices; ++i){
		cout << "There exists edges from vertex "<< i << " to vertices \n";
		cout << "\t->\t";
		adj_list->printlist(i);
		cout << endl;
	}
}

void graph::DFS(int &source , int n , int e){
	graph* y = new graph(n , e);

	int* color = new int[n];
	int* pred = new int[n];
	int* d_time = new int[n];
	int* f_time = new int[n];
	int* distance = new int[n];
	int u , t;
	t = 0;
	for (int i = 0; i < n ; ++i){
		color[i] = 0;			//undiscoverd vertices are colored White
		pred[i] = -1;
		d_time[i] = 0;
		f_time[i] = 0;
		distance[i] = -1;
	}

	int p(n) ;
	stack<int> s(n) ;
	cout << "stack of size " << n << " has been formed\n";
	int x = source;
	s.push_back(x);
	t++;
	color[source] = 1;
	pred[source] = -1;
	distance[source] = 0;
	d_time[source] = t;
	p--;
	cout <<"Still " << p << " vertices are left unvisited\n\n";

	while(!s.is_empty()){
		node* pointer = adj_list->get_head(x);
		while(pointer != NULL){
			int v = pointer->get_element();
			int w = pointer->get_weight();
			if(v != -1){
				if(color[v] == 0){
					DFS_visit(v,x,w,color,distance,d_time,f_time,pred,y);
					s.push_back(x);
					t++;
					p--;
					cout <<"\nStill " << p << " vertices are left unvisited\n\n";
					d_time[v] = t ;
					// j++;
					break;
				}
				else{
					cout <<"Vertex " << v << " had been discovered earlier\n";
					cout << "There exists path bw "<< x << " and " << v << "\n";
					pointer = pointer->get_next();
					if(pointer == NULL){
						//k = s.return_top();
						//f_time[x] =  d_time[x] + (2*k) + 1 ;
						if(!s.is_empty()){
							s.pop_back();
							t++;
							f_time[x] = t ;
							x = s.return_top();
							// k++;
						}
						break;
					}	
				}
			}
			else{
				cout << "There does not exist edge from " << x <<" to any vertex\n";
				s.pop_back();
				t++;
				f_time[x] = t ;
				x = pred[x];
				break;
			}
		}
		continue;
	}	

	cout << "Here ends one connected component and the other one starts\n\n";

	int a[n];
	while(p != 0){
		for (int i = 0; i < n; ++i){
			a[i] = 0;
		}
		for (int i = 0; i < n; ++i){
			if(color[i] == 0){
				cout << "vertex "<< i <<" was left unvisited\n\n\n" ;
				a[i] = 1 ;
			}
			else{
				continue;
			}
		}

		cout << "\nNo. of vertices left unvisited = "<< p <<"\n\n";

		for (int i = 0; i < n; ++i){
			if(a[i] == 1){
				stack<int> s(p) ;
				cout << "stack of size " << p << " has been formed\n";
				int x = i;
				cout << i << " is chosen as the new source\n\n"; 
				s.push_back(x);
				a[x] = 0;
				t++;
				p--;
				cout <<"\nStill " << p << "vertices are left unvisited\n\n";
				color[x] = 1;
				pred[x] = -1;
				distance[x] = 0;
				d_time[x] = t;
				while(!s.is_empty()){
					node* pointer = adj_list->get_head(x);
					while(pointer != NULL){
						int v = pointer->get_element();
						int w = pointer->get_weight();
						if(v != -1){
							if(color[v] == 0){
								DFS_visit(v,x,w,color,distance,d_time,f_time,pred,y);
								s.push_back(x);
								a[i] = 0;
								t++;
								p--;
								cout << "\nNo. of vertices left unvisited = "<< p <<"\n\n";
								d_time[v] = t ;
								// j++;
								break;
							}
							else{
								cout <<"Vertex " << v << " had been discovered earlier\n";
								cout << "So cant insert edge bw "<< x << " and " << v << "\n";
								pointer = pointer->get_next();
								if(pointer == NULL){
									if(!s.is_empty()){
										s.pop_back();
										color[i] = 2;
										t++;
										f_time[x] = t ;
										x = s.return_top();
										// k++;
									}
									break;
								}	
							}
						}
						else{
							cout << "There does not exist edge from " << x <<" to any vertex\n";
							s.pop_back();
							color[i] = 2;
							t++;
							f_time[x] = t ;
							x = pred[x];
							break;
						}
					}
					continue;
				}
			}
			else
				continue;
			cout << "Here ends one connected component and the other one starts\n\n";
			break;
		}	
	}
	cout <<"The whole graph has been searched \n\nThe final graph is \n\n";
	y->print_graph_DFS();
	cout << endl<<endl;
	cout <<"Info of each vertex is \n";
	for (int i = 0; i < n; ++i){
		cout << "Distance of " << i << " from source is " << distance[i] << "\n"; 
		cout << "Predecessor of " << i <<" is equal to " <<  pred[i] << "\n";
		cout << "Discovry time of " << i << " is " << d_time[i] << "\n"; 
		cout << "Back tracking time of " << i <<" is " <<  f_time[i] << "\n\n\n"; 
	}

}



void graph::DFS_visit(int &v , int &x ,int &w, int* color , int* distance , int* d_time , int* f_time , int* pred , graph* y){
	color[v] = 1;
	distance[v] = distance[x] + 1;
	//d_time[v] = d_time[x] + 1 ;
	pred[v] = x ; 
	y->add_edge(x,v,w);
	y->print_graph_DFS();
	x = v;
}

















