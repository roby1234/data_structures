#ifndef _GRAPH_H_
#define _GRAPH_H_
#include "linked_list.cpp"

using namespace std;

class edges{
private:
	int source;
	int destination;
	int weight;

public:
	edges();
	int get_src();
	int get_dest();
	int get_wt();
	void set_src(int);
	void set_dest(int);
	void set_wt(int);
};


class disjoint_set{
private:
	int parent;
	int rank;
public:
	disjoint_set();
	int get_rank();
	int get_parent();
	void set_rank(int);
	void set_parent(int);
	int find(disjoint_set set[],int);
	void do_union(disjoint_set set[],int,int);
};


class graph : public linked_list , public edges{ 
private:
	linked_list* adj_list ;
	int no_of_vertices;
	int no_of_edges ;
	edges* edge; 

public:
	graph(){}
	graph(int , int);
	~graph();
	void print_edge(int);
	graph* create_graph(int , int);
	int get_no_of_vertices();
	int get_no_of_edges();
	//edges* get_edge();
	void set_no_of_vertices(int);
	void set_no_of_edges(int);
	void make_graph(char[]);
	int insert_edge(int k ,int u , int v , int w);
	int add_edge(int , int , int);
	void print_graph();
	int iscycle(graph*);
	void Kruskal_MST(graph*);
	void print_graph_BFS();
	void print_graph_DFS();
	void BFS(int& , int , int);
	void DFS(int& , int , int);
	void DFS_visit(int& ,int& ,int& ,int* ,int* ,int* ,int* ,int* ,graph*);
//	void print_info_DFS(graph* , int);
};

#endif
