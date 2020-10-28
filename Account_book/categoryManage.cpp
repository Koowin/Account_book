#include "header.hpp"
/*  input : list <string> category_table
*	output : void
*	main함수에서 category_table을 받아서 모든 카테고리 목록을 출력하는 함수
*/

Category::Category() {

}

Category::Category(string s) {
	this->c_name = s;
}

string Category::get_cname() {
	return this->c_name;
}

void Category::set_cname(string s) {
	this->c_name = s;
}

void CategoryManage::categoryMenu() {

}

void CategoryManage::printCategoryList() {
	
}

/*  input : list <string> category_table
*	output : True(Fail), False(Success)
*	새로운 카테고리를 추가하는 함수
*/

bool CategoryManage::addCategoryList(Category c) {
	return false;
}

bool CategoryManage::modifyCategoryList(Category c) {
	return false;
}

bool CategoryManage::deleteCategoryList(Category c) {
	return false;
}

int CategoryManage::getCategorySize() {
	return category.size();
}

void CategoryManage::init_add(Category c) {
	category.push_back(c);
}

bool modifyCategory(list <string> *category_table) {
	bool flag = true;
	int selected_num;
	string input_string;
	
	cout << "@ Edit category @" << endl;
	int i = 1;
	list <string>::iterator iter;
	list <string>::iterator end_of_list = category_table->end();

	cout << "@ View categories @" << endl;
	for (iter = category_table -> begin(); iter != end_of_list; iter++) {
		cout << i << ". " << *iter << endl;
		i++;
	}
	cout << "\nSelect category to edit (q: return to main menu)" << endl << "> ";
	cin >> selected_num;
	
	list<string>::iterator selector = category_table->begin();
	advance(selector, selected_num-1);
	cout << "\n Category selected: " << *selector << endl;
	////////temp///
	return false;
}
bool deleteCategory(list <string>, list <class Record>) {

	/////temp///
	return false;
}

int CategoryManage::listSize() {
	return this->category.size();
}

bool CategoryManage::isDuplicate(string s) {
	list<Category>::iterator iter = category.begin();
	for (; iter != category.end();) {
		string temp = (*iter).get_cname();
		if (temp == s) {
			return true;
		}
		iter++;
	}
}

Category CategoryManage::getCategory() {
	Category c = category.front();
	category.pop_front();
	return c;
}