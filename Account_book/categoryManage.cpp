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
				cout << "max category name size = 20" << endl;			//오류 문구 수정 가능
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
	string confirm_string;

	cout << "@ Edit category @" << endl;
	int i = 1;
	list <string>::iterator iter;
	list <string>::iterator end_of_list = category_table->end();

	cout << "@ View categories @" << endl;
	for (iter = category_table -> begin(); iter != end_of_list; iter++) {
		cout << i << ". " << *iter << endl;
		i++;
	}

	while (flag) {
		cout << "\nSelect category to edit (q: return to main menu)" << endl << "> ";
		cin >> input_string;

		if (input_string == "q") {
			return true;
		}
		//숫자 이외의 입력 예외처리
		try {
			selected_num = stoi(input_string);
		}
		catch (const exception& expn) {
			cout << "Input only number" << endl;
		}
		//0 ~ table size 이외의 입력 예외 처리
		if (selected_num > category_table->size() || selected_num < 1) {
			cout << "Number must be over 0 and under " << category_table->size() + 1 << endl;
		}
		else {
			flag = false;
		}
	}

	list<string>::iterator selector = category_table->begin();
	advance(selector, selected_num-1);
	cout << "\nCategory selected: " << *selector << endl;
	while (1) {
		cout << "Enter category modification (q: return to main menu)" << endl << "> ";
		cin >> input_string;

		if (input_string == "q") {
			return true;
		}
		else {
			//input_string check
			if (input_string.size() > 20) {
				cout << "max category name size = 20" << endl;				//오류 문구 수정 가능
			}
			else {
				//수정 확인
				cout << "Before modification : " << *selector << endl;
				cout << "After modification : " << input_string << endl;
				cout << "Confirm modification? (type 'No' to cacel)" << endl << "> ";
				cin >> confirm_string;
				if (confirm_string == "No") {
					return true;
				}
				else {
					selector->assign(input_string);
					return false;
				}
			}
		}
	}
}

bool deleteCategory(list <string> *category_table, list <class Record> *record_list) {
	bool flag = true;
	bool duplicate_checker = false;

	string input_string;
	int selected_num;

	cout << "@ Delete category @" << endl;
	int i = 1;
	list <string>::iterator iter;
	list <string>::iterator end_of_list = category_table->end();

	for (iter = category_table->begin(); iter != end_of_list; iter++) {
		cout << i << ". " << *iter << endl;
		i++;
	}

	while (flag) {
		cout << "\nSelect category to delete (q: return to main menu)" << endl << "> ";
		cin >> input_string;

		if (input_string == "q") {
			return true;
		}
		//숫자 이외의 입력 예외처리
		try {
			selected_num = stoi(input_string);
		}
		catch (const exception& expn) {
			cout << "Input only number" << endl;
		}

		//0 ~ table size 이외의 입력 예외 처리
		if (selected_num > category_table->size() || selected_num < 1) {
			cout << "Number must be over 0 and under " << category_table->size() + 1 << endl;
		}
		else {
			//to do 예외처리: 해당 카테고리 번호가 존재하는 기록이 있으면 삭제 안되게
			list <class Record>::iterator record_iter;
			list <class Record>::iterator end_of_record_list = record_list->end();

			selected_num--;

			for (record_iter = record_list->begin(); record_iter != end_of_record_list; record_iter++) {
				if (record_iter->category_number == selected_num) {
					duplicate_checker = true;
					break;
				}
			}
			//duplicate_checker == true면 겹치는 기록 존재
			if (duplicate_checker) {
				cout << "Some record have that category number. " << endl;
			}
			else {
				flag = false;
			}
		}
		
		//삭제 확인
		cout << "Confirm deletion? (type 'No' to cancel)" << endl << "> ";
		cin >> input_string;
		if (input_string == "No") {
			return true;
		}
		else {
			//삭제 작업
			iter = category_table->begin();
			advance(iter, selected_num);
			category_table->erase(iter);
			return false;
		}
	}
}