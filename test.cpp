#include "graph.h"
#include <vector>
#include <iostream>
#include <iostream>


using std::map;
using std::set;
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::cerr;
using std::deque;
using std::vector;

bool Vertex::operator< (const Vertex& rhs) const {
	return name < rhs.name;
}

bool Vertex::operator== (const Vertex& rhs) const {
	return name == rhs.name;
}

Vertex::Vertex (const string & p_name, int p_data, bool is_visited)
	: name(p_name), data(p_data), is_visited(is_visited)
{ }

Vertex::Vertex(const Vertex & v) :
	name(v.name), data(v.data), is_visited(v.is_visited)
{ }

std::ostream& operator<< (std::ostream & os, const Vertex & v)
{
	os << "[Vertex name: " << v.name << " data: " << v.data << "]" ;
	return os;
}

// struct VertexPointerComparator {
// 	bool operator() (const Vertex * lhs, const Vertex * rhs) const {
// 		return lhs->name < rhs->name;
// 	}
// };

bool VertexPointerComparator::operator() (const Vertex * lhs, const Vertex * rhs) const {
	cout << "Pointer comparison used" << endl;
	return lhs->name < rhs->name;
}

int main()
{
	string v_name("a");
	Vertex  v_a(v_name, 101);

	string v_name_z("z");
	Vertex  v_z(v_name_z, 126);

	string v_name_w("w");
	Vertex  v_w(v_name_w, 122);

	string v_name_o("o");
	Vertex  v_o(v_name_o, 115);

	string v_name_b("b");
	Vertex  v_b(v_name_b, 102);

	string v_name_f("f");
	Vertex  v_f(v_name_f, 106);


	string v_name_x("x");
	Vertex  v_x(v_name_x, 102);


	set<Vertex*, VertexPointerComparator> set_vertex;
	set_vertex.insert(&v_a);
	set_vertex.insert(&v_z);
	set_vertex.insert(&v_w);
	set_vertex.insert(&v_o);
	set_vertex.insert(&v_b);
	set_vertex.insert(&v_f);
	set_vertex.insert(&v_x);

	//vector<Vertex> vec_vertex;
	//vec_vertex.push_back(v_a);
	//vec_vertex.push_back(v_b);

	string v_name2("a");
	Vertex  v_a2(v_name, 101);


	cout << "About to call find" << endl;
	auto it = set_vertex.find(&v_a2);
	if ( it != set_vertex.end()) {
		cout << " FOUND " << endl;
		Vertex *v_ptr = *it;
		Vertex & v = *v_ptr;
		v.name = "a_mod";
		cout << v_a << endl;
		cout << v << endl;
	} else {
		cout << " NOT FOUND " << endl;
	}

	//Vertex & v2 = vec_vertex[1];

	//v2.name = "b_mod";

	//cout << v_b << endl;
	//cout << v2 << endl;

	for (auto it: set_vertex) {
		Vertex & v= *it;
		cout << " : " << v ;
	}
	cout << endl;

}
