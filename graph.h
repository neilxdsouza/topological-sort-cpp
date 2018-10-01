#ifndef nxd_graph_h
#define nxd_graph_h

#include <set>
#include <map>
#include <string>
#include <deque>



struct Vertex {
	std::string name;
	int data;
	bool is_visited;

	bool operator< (const Vertex& rhs) const; 
	bool operator== (const Vertex& rhs) const; 
	Vertex (const std::string & p_name, int p_data, bool is_visited=false);
	Vertex(const Vertex & v);
	friend std::ostream& operator<< (std::ostream & os,
			const Vertex & v);
};

struct VertexPointerComparator {
	bool operator() (const Vertex * lhs, const Vertex * rhs) const ;
	// bool operator() (const Vertex * lhs, const Vertex * rhs) const {
	// 	return lhs->name < rhs->name;
	// }
};

struct Graph {
	std::set<Vertex*, VertexPointerComparator> vertex_set;
	std::map<Vertex *,
			std::set<Vertex*, VertexPointerComparator> *,
			VertexPointerComparator > neighbours;

	void do_vertex_exists_check(Vertex & v);

	void add_vertex(const Vertex & v);
	void add_neighbour(Vertex & v, Vertex & n);
	
	std::deque<Vertex*> get_topological_order();
	void dfs( Vertex * v, std::deque<Vertex*> & topological_order, 
			int level);
	void print_vertices_and_their_neighbours();
	void print_vertices(std::string label);
};

#endif /* nxd_graph_h */
