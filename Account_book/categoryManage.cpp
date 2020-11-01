#include "header.hpp"


void CategoryManage::categoryMenu(RecordManage& record_manager) {
	string input_string;
	bool flag = true;
	while (1) {
		if (flag) {
			system("cls");
			cout << "@ Manage category @" << endl;
			cout << "1. View categories" << endl;
			cout << "2. Add new category" << endl;
			cout << "3. Edit category" << endl;
			cout << "4. Delete category\n" << endl;

			cout << "Select menu (q:return to main menu)" << endl << "> ";
		}
		getline(cin, input_string);

		if (input_string == "q") {
			break;
		}
		else if (input_string == "1") {
			system("cls");
			cout << "@ View categories @" << endl;
			printCategoryList();

			cout << "\nPress any key to continue...\n";
			_getch();
			flag = true;

		}
		else if (input_string == "2") {
			addCategory(record_manager);
			//flag = true;
			break;
		}
		else if (input_string == "3") {
			modifyCategory(record_manager);
			//flag = true;
			break;
		}
		else if (input_string == "4") {
			deleteCategory(record_manager);
			//flag = true;
			break;
		}
		else {
			cout << "Please enter a valid value\n> ";
			flag = false;
		}
	}
}


/*  input : list <string> category_table
*	output : void
*	main함수에서 category_table을 받아서 모든 카테고리 목록을 출력하는 함수
*/
void CategoryManage::printCategoryList() {
	int i=1;
	list <Category>::iterator iter;
	list <Category>::iterator end_of_list = category.end();

	for (iter = category.begin(); iter != end_of_list; iter++) {
		cout << i << ". " << iter->get_cname() << endl;
		i++;
	}
}

/*  input : list <string> category_table
*	output : True(return to main menu)
*	새로운 카테고리를 추가하는 함수
*/

bool CategoryManage::addCategory(RecordManage& record_manager) {
	bool flag=true;
	string input_string;
	string confirm_string;
	CheckerParser cp;

	system("cls");
	cout << "@ Add new category @" << endl;

	while (flag) {
		cout << "Enter new category (q:return to main menu)" << endl << "> ";
		getline(cin, input_string);

		//입력이 'q'인지 검사
		if (input_string == "q") {
			return true;
		}
		else {
			if (category.size() >= 64) {
				cout << "Your number of categories has exceeded its maximum value (64 categories)." << endl;
				cout << "Please delete some of your categories to continue." << endl;
			}
			else {
				//카테고리 문자열 문법 검사
				if (!cp.checkCategoryName(input_string)) {
					//중복 검사
					list <Category>::iterator iter;
					list <Category>::iterator end_of_list = category.end();
					bool duplicate = false;
					for (iter = category.begin(); iter != end_of_list; iter++) {
						if (input_string == iter->get_cname()) {
							duplicate = true;
							break;
						}
					}
					if (duplicate) {
						cout << "Duplicate category, please enter a new one." << endl;
					}
					else {
						//카테고리 저장확인
						cout << "Confirm new category? (type 'No' to cancle)" << endl << "> ";
						getline(cin, confirm_string);
						if (confirm_string != "No") {
							//카테고리 저장
							category.push_back(Category(input_string));
							FileManage file_manager;
							file_manager.saveFile(record_manager, *this);
						}
						flag = false;
					}
				}
			}
		}
	}
	return false;
}

bool CategoryManage::modifyCategory(RecordManage& record_manager) {
	bool flag = true;
	int selected_num;
	string input_string;
	string confirm_string;
	CheckerParser cp;

	system("cls");
	cout << "@ Edit category @" << endl;
	int i = 1;
	list <Category>::iterator iter;
	list <Category>::iterator end_of_list = category.end();

	//카테고리 출력부
	for (iter = category.begin(); iter != end_of_list; iter++) {
		cout << i << ". " << iter->get_cname() << endl;
		i++;
	}

	while (flag) {
		cout << "\nSelect category to edit (q: return to main menu)" << endl << "> ";
		getline(cin, input_string);

		if (input_string == "q") {
			return true;
		}
		//숫자 이외의 입력 예외처리
		if (!cp.checkCategoryNumber(input_string, category.size())) {
			selected_num = stoi(input_string);
			flag = false;
		}
	}

	list<Category>::iterator selector = category.begin();
	advance(selector, selected_num-1);
	system("cls");
	cout << "Category selected: " << selector->get_cname() << endl;

	while (1) {
		cout << "\nEnter category modification (q: return to main menu)" << endl << "> ";
		getline(cin, input_string);

		if (input_string == "q") {
			return true;
		}
		else {
			//input_string check
			if (!cp.checkCategoryName(input_string)) {
				bool duplicate = false;
				iter = category.begin();
				for (; iter != end_of_list; iter++) {
					if (input_string == iter->get_cname()) {
						duplicate = true;
						break;
					}
				}
				if (duplicate) {
					cout << "Duplicate category, please enter a new one." << endl;
				}
				else {
					//수정 확인
					system("cls");
					cout << "Before modification : " << selector->get_cname() << endl;
					cout << "After modification : " << input_string << endl;
					cout << "Confirm modification? (type 'No' to cancel)" << endl << "> ";
					getline(cin, confirm_string);
					if (confirm_string == "No") {
						return false;
					}
					else {
						selector->set_cname(input_string);
						FileManage file_manager;
						file_manager.saveFile(record_manager, *this);
						return false;
					}
				}
			}
		}
	}
}

bool CategoryManage::deleteCategory(RecordManage & record_manager) {
	bool flag = true;
	bool duplicate_checker = false;
	CheckerParser cp;
	string input_string;
	int selected_num;

	system("cls");
	cout << "@ Delete category @" << endl;
	int i = 1;
	list <Category>::iterator iter;
	list <Category>::iterator end_of_list = category.end();

	for (iter = category.begin(); iter != end_of_list; iter++) {
		cout << i << ". " << iter->get_cname() << endl;
		i++;
	}

	while (flag) {
		cout << "\nSelect category to delete (q: return to main menu)" << endl << "> ";
		getline(cin, input_string);

		if (input_string == "q") {
			return true;
		}
		//숫자 이외의 입력 예외처리
		if (!cp.checkCategoryNumber(input_string, category.size())) {
			selected_num = stoi(input_string);
		}
		else {
			continue;
		}

		//0 ~ table size 이외의 입력 예외 처리
		list <Record>::iterator record_iter;
		list <Record>::iterator end_of_record_list = record_manager.get_end();
		
		//예외처리: 카테고리 개수가 1개면 삭제 안되게
		if (category.size() < 2) {
			cout << "There must be at least one category. Category is not deleted." << endl;
			return true;
		}
		if (selected_num > category.size() || selected_num < 1) {
			cout << "Number must be over 0 and under " << category.size() + 1 << endl;
		}
		else {
			//예외처리: 해당 카테고리 번호가 존재하는 기록이 있으면 삭제 안되게
			selected_num--;

			for (record_iter = record_manager.get_first(); record_iter != end_of_record_list; record_iter++) {
				if (record_iter->get_category_number() == selected_num) {
					duplicate_checker = true;
					break;
				}
			}
			//duplicate_checker == true면 겹치는 기록 존재
			if (duplicate_checker) {
				cout << "Some record have that category number. " << endl;
				flag = false;
			}
			else {
				//삭제 확인
				cout << "Confirm deletion? (type 'No' to cancel)" << endl << "> ";
				getline(cin, input_string);
				if (input_string == "No") {
					return true;
				}
				else {
					//모든 기록들 카테고리 번호 하나씩 줄이기 (선택한 것 보다 크다면)
					for (record_iter = record_manager.get_first(); record_iter != end_of_record_list; record_iter++) {
						int category_num = record_iter->get_category_number();
						if (category_num > selected_num + 1) {
							record_iter->set_category_number(category_num - 1);
						}
					}
					//삭제 작업
					iter = category.begin();
					advance(iter, selected_num);
					category.erase(iter);
					FileManage file_manager;
					file_manager.saveFile(record_manager, *this);
					return false;
				}
			}
		}
	}
}

string CategoryManage::getIndexedCategory(int index) {
	list <Category>::iterator iter = category.begin();
	advance(iter, index-1);
	return iter->get_cname();
}

int CategoryManage::getCategorySize() {
	return category.size();
}

list <Category>::iterator CategoryManage::get_first() {
	list <Category>::iterator iter = category.begin();
	return iter;
}
list <Category>::iterator CategoryManage::get_end() {
	list <Category>::iterator iter = category.end();
	return iter;
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
	return false;
}

void CategoryManage::init_add(Category c) {
	category.push_back(c);
}

Category CategoryManage::getCategory() {
	Category c = category.front();
	category.pop_front();
	return c;
}
