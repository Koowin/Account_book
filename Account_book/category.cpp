#include "header.hpp"

Category::Category(string name) {
	c_name = name;
}

string Category::get_cname() {
	return c_name;
}

void Category::set_cname(string new_name) {
	c_name = new_name;
}