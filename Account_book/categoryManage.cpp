#include "header.hpp"

/*  input : list <string> category_table
*	output : void
*	main함수에서 category_table을 받아서 모든 카테고리 목록을 출력하는 함수
*/
void printCategoryList(list <string> *category_table) {
	int i=1;
	list <string>::iterator iter;
	list <string>::iterator end_of_list = category_table->end();

	cout << "@ View categories @" << endl;
	for (iter = category_table->begin(); iter != end_of_list; iter++) {
		cout << i << ". " << *iter << endl;
		i++;
	}
	cout << "\nPress any key to continue..." << endl;
	_getch();
}

/*  input : list <string> category_table
*	output : True(Fail), False(Success)
*	새로운 카테고리를 추가하는 함수
*/

bool addCategoryList(list <string> *category_table) {
	bool flag=true;
	string input_string;
	string confirm_string;
	string to_main_menu;		//'q'를 저장할 문자열
	to_main_menu.assign(1,'q');

	cout << "@ Add new category @" << endl;

	while (flag) {
		cout << "Enter new category (q:return to main menu)" << endl << "> ";
		cin >> input_string;

		//입력이 'q'인지 검사
		if (input_string.compare("q") == 0) {
			return true;
		}
		else {
			//카테고리 문자열 길이 검사
			if (input_string.size() > 20) {
				cout << "max category name size = 20" << endl;
			}
			else {
				//카테고리 저장확인
				cout << "Confirm new category? (type 'No' to cancle)" << endl << "> ";
				cin >> confirm_string;
				if (confirm_string.compare("No") != 0) {
					//카테고리 저장
					category_table->push_back(input_string);
				}
				flag = false;
			}
		}
	}
	return false;
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