#include "header.hpp"


void CategoryManage::categoryMenu(RecordManage& record_manager) {
	string input_string;

	while (1) {
		cout << "@ Manage category @" << endl;
		cout << "1. View categories" << endl;
		cout << "2. Add new category" << endl;
		cout << "3. Edit category" << endl;
		cout << "4. Delete category\n" << endl;

		cout << "Select menu (q:return to main menu)" << endl << "> ";
		cin >> input_string;

		if (input_string == "q") {
			break;
		}
		else if (input_string == "1") {
			printCategoryList();
		}
		else if (input_string == "2") {
			addCategory();
		}
		else if (input_string == "3") {
			modifyCategory();
		}
		else if (input_string == "4") {
			deleteCategory(record_manager);
		}
		else {
			cout << "Please enter a valid value" << endl;
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

	cout << "@ View categories @" << endl;
	for (iter = category.begin(); iter != end_of_list; iter++) {
		cout << i << ". " << iter->get_cname() << endl;
		i++;
	}
	cout << "\nPress any key to continue..." << endl;
	_getch();
}

/*  input : list <string> category_table
*	output : True(Fail), False(Success)
*	새로운 카테고리를 추가하는 함수
*/

bool CategoryManage::addCategory() {
	bool flag=true;
	string input_string;
	string confirm_string;
	CheckerParser cp;

	cout << "@ Add new category @" << endl;

	while (flag) {
		cout << "Enter new category (q:return to main menu)" << endl << "> ";
		cin >> input_string;

		//입력이 'q'인지 검사
		if (input_string == "q") {
			return true;
		}
		else {
			//카테고리 문자열 길이 검사
			if (!cp.checkCategoryName(input_string)) {
				//카테고리 저장확인
				cout << "Confirm new category? (type 'No' to cancle)" << endl << "> ";
				cin >> confirm_string;
				if (confirm_string != "No") {
					//카테고리 저장
					category.push_back(Category(input_string));
				}
				flag = false;
			}
		}
	}
	return false;
}

bool CategoryManage::modifyCategory() {
	bool flag = true;
	int selected_num;
	string input_string;
	string confirm_string;
	CheckerParser cp;

	cout << "@ Edit category @" << endl;
	int i = 1;
	list <Category>::iterator iter;
	list <Category>::iterator end_of_list = category.end();

	//카테고리 출력부
	cout << "@ View categories @" << endl;
	for (iter = category.begin(); iter != end_of_list; iter++) {
		cout << i << ". " << iter->get_cname() << endl;
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
		if (selected_num > category.size() || selected_num < 1) {
			cout << "Number must be over 0 and under " << category.size() + 1 << endl;
		}
		else {
			flag = false;
		}
	}

	list<Category>::iterator selector = category.begin();
	advance(selector, selected_num-1);
	cout << "\nCategory selected: " << selector->get_cname() << endl;

	while (1) {
		cout << "Enter category modification (q: return to main menu)" << endl << "> ";
		cin >> input_string;

		if (input_string == "q") {
			return true;
		}
		else {
			//input_string check
			if (!cp.checkCategoryName(input_string)) {
				//수정 확인
				cout << "Before modification : " << selector->get_cname() << endl;
				cout << "After modification : " << input_string << endl;
				cout << "Confirm modification? (type 'No' to cacel)" << endl << "> ";
				cin >> confirm_string;
				if (confirm_string == "No") {
					return true;
				}
				else {
					selector->set_cname(input_string);
					return false;
				}
			}
		}
	}
}

bool CategoryManage::deleteCategory(RecordManage & record_manager) {
	bool flag = true;
	bool duplicate_checker = false;

	string input_string;
	int selected_num;

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
		list <Record>::iterator record_iter;
		list <Record>::iterator end_of_record_list = record_manager.get_end();

		if (selected_num > category.size() || selected_num < 1) {
			cout << "Number must be over 0 and under " << category.size() + 1 << endl;
		}
		else {
			//to do 예외처리: 해당 카테고리 번호가 존재하는 기록이 있으면 삭제 안되게

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
			//모든 기록들 카테고리 번호 하나씩 줄이기 (선택한 것 보다 크다면)
			for (record_iter = record_manager.get_first(); record_iter != end_of_record_list; record_iter++) {
				int category_num = record_iter->get_category_number();
				if (category_num > selected_num+1) {
					record_iter->set_category_number(category_num-1);
				}
			}
			//삭제 작업
			iter = category.begin();
			advance(iter, selected_num);
			category.erase(iter);
			return false;
		}
	}
}

int CategoryManage::getCategorySize() {
	return category.size();
}