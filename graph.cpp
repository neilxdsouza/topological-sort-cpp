#include "graph.h"

#include <iostream>

using std::map;
using std::set;
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::cerr;
using std::deque;


bool Vertex::operator< (const Vertex& rhs) const {
	return name < rhs.name;
}

bool Vertex::operator== (const Vertex& rhs) const {
	return name == rhs.name;
}

Vertex::Vertex (const string & p_name, int p_data, bool is_visited)
	: name(p_name), data(p_data), is_visited(false)
{ }

Vertex::Vertex(const Vertex & v)
	: name(v.name), data(v.data), is_visited(v.is_visited)
{ }

std::ostream & operator<< (std::ostream & os, const Vertex & v)
{
	os << " Vertex:[ name:" << v.name
		<< ", data: " << v.data << "]";
	return os;
}


bool VertexPointerComparator::operator() (const Vertex * lhs, const Vertex * rhs)
	const
{
	// cout << "Pointer comparison used" << endl;
	return lhs->name < rhs->name;
}

void Graph::do_vertex_exists_check(Vertex & v)
{
	auto it = vertex_set.find(&v);
	//if (vertex_set.find(&v) == vertex_set.end()) 
	if (it == vertex_set.end()) {
		cerr << "Vertex not found in graph" << endl;
		cerr << "returning early" << endl;
		exit(1);
	}
}


void Graph::add_vertex(const Vertex & v)
{
	vertex_set.insert(new Vertex(v));
}

void Graph::add_neighbour(Vertex & v, Vertex & n)
{
	do_vertex_exists_check(v);
	do_vertex_exists_check(n);
	map<Vertex *, std::set<Vertex*, VertexPointerComparator> *, VertexPointerComparator >::iterator it = neighbours.find(&v);
	if (it == neighbours.end()) {
		set<Vertex*, VertexPointerComparator> * s = 
			new set<Vertex*,VertexPointerComparator>;
		s->insert(&n);
		std::map<Vertex *, set<Vertex *, VertexPointerComparator> *>::iterator neighbour_map_it = neighbours.begin();
		std::pair<Vertex *, set<Vertex *, VertexPointerComparator> *> p = std::pair<Vertex * , set<Vertex*, VertexPointerComparator> *>(&v, s);
		neighbours.insert(neighbour_map_it, p);
	} else {
		auto &neighbours = it->second;
		set<Vertex*, VertexPointerComparator> & s = *neighbours;
		s.insert(&n);
	}
}

void Graph::dfs( Vertex * v_ptr, deque<Vertex*> & topological_order, int level)
{
	Vertex & v = *v_ptr;
	do_vertex_exists_check(v);
	string func_name = __PRETTY_FUNCTION__;
	cout << string (level, ' ') <<  "ENTER " << func_name << " visiting v:" << v << endl;

	v.is_visited = true;

	auto it = neighbours.find(v_ptr);

	if (it == neighbours.end()) {
		topological_order.push_back(&v);
		cout << string(level, ' ') << "EXIT " << func_name 
			<< " visitor v:" << v << endl;
		return;
	}

	set<Vertex*, VertexPointerComparator> *  neighbour_vertices_ptr = it->second;
	set<Vertex*, VertexPointerComparator> & neighbour_vertices = * neighbour_vertices_ptr;

	for (auto & v: neighbour_vertices) {
		if (!v->is_visited) {
			//Vertex & v2 = *(vertex_set.find(v));
			set<Vertex*, VertexPointerComparator>::iterator it = vertex_set.find(v);
			Vertex * v2 = *it;
			dfs(v2, topological_order, ++level);
		}
	}
	cout << "pushing: " << v << " into topological_order: " << endl;
	topological_order.push_back(&v);
	cout << "vertices in topological_order are : " << endl;
	for (auto v: topological_order) {
		cout  << ' ' << *v ;
	}
	cout << string(level, ' ') << "EXIT " << func_name 
		<< " visitor v:" << v << endl;

}


void Graph::print_vertices(string label)
{
	cout << "ENTER " << __PRETTY_FUNCTION__ <<  " " << label << endl;
	for (auto it: vertex_set) {
		auto a_vertex = *it;
		cout <<  a_vertex << endl;
	}
	cout << "EXIT " << __PRETTY_FUNCTION__ <<  " " << label << endl;
}

void Graph::print_vertices_and_their_neighbours()
{
	for (auto it: neighbours) {
		auto a_vertex = it.first;
		cout << * a_vertex << " : " ;
		//auto its_neighbours = it.second;
		set<Vertex*, VertexPointerComparator> & its_neighbours = *(it.second);
		for (auto a_neighbour: its_neighbours) {
			cout << *a_neighbour;
		}
		cout << endl;
	}
	cout << endl;
}
std::deque<Vertex*> Graph::get_topological_order()
{
	string func_name(__PRETTY_FUNCTION__);
	cout << "ENTER " << func_name 
		<< "size vertex_set: " << vertex_set.size() 
		<< endl;

	deque<Vertex*> topological_order;
	//for (auto kv_it: neighbours) {

	//	if (!kv_it->first.is_visited) {
	//		Vertex & a_neighbout = *first;
	//		dfs(a_neighbout, topological_order);
	//	}
	//}
	for (auto  v : vertex_set) {
		if (!v->is_visited) {
			cout << "INFO " << func_name 
				<< " visiting " << *v << endl;
			dfs(v, topological_order, 0);
		}
	}
	cout << "EXIT " << func_name << endl;
	return topological_order;
}

int main()
{
	cout << "Hello" << endl;
	Graph g;
	{
		string v_name("a");
		Vertex  v_a(v_name, 101);
		g.add_vertex(v_a);
		g.print_vertices("After a");
		cout << "Hello 2" << endl;

		string v_name_b("b");
		Vertex  v_b(v_name_b, 102);
		g.add_vertex(v_b);
		g.print_vertices("After b");

		cout << "Hello 3" << endl;

		string v_name_c("c");
		Vertex  v_c(v_name_c, 103);
		g.add_vertex(v_c);

		string v_name_d("d");
		Vertex  v_d(v_name_d, 104);
		g.add_vertex(v_d);

		string v_name_e("e");
		Vertex  v_e(v_name_e, 105);
		g.add_vertex(v_e);

		string v_name_f("f");
		Vertex  v_f(v_name_f, 106);
		g.add_vertex(v_f);

		cout << "Hello 6" << endl;
		g.print_vertices_and_their_neighbours();

		g.add_neighbour(v_a, v_b);
		g.add_neighbour(v_b, v_c);
		g.add_neighbour(v_b, v_d);
		g.add_neighbour(v_d, v_e);
		g.add_neighbour(v_d, v_f);
		g.add_neighbour(v_c, v_f);
		g.print_vertices_and_their_neighbours();
		cout << "Hello 7" << endl;
		cout << "Topological order is: " << endl;
		deque<Vertex*> topological_order
			= g.get_topological_order();
		for (auto v: topological_order) {
			cout << " " << *v ;
		}
		/*
		*/
		cout << endl;
	}
}
