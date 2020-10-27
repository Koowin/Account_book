#include "header.hpp"

/*  input : list <string> category_table
*	output : void
*	main�Լ����� category_table�� �޾Ƽ� ��� ī�װ� ����� ����ϴ� �Լ�
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
*	���ο� ī�װ��� �߰��ϴ� �Լ�
*/

bool addCategoryList(list <string> *category_table) {
	bool flag=true;
	string input_string;
	string confirm_string;
	string to_main_menu;		//'q'�� ������ ���ڿ�
	to_main_menu.assign(1,'q');

	cout << "@ Add new category @" << endl;

	while (flag) {
		cout << "Enter new category (q:return to main menu)" << endl << "> ";
		cin >> input_string;

		//�Է��� 'q'���� �˻�
		if (input_string.compare("q") == 0) {
			return true;
		}
		else {
			//ī�װ� ���ڿ� ���� �˻�
			if (input_string.size() > 20) {
				cout << "max category name size = 20" << endl;			//���� ���� ���� ����
			}
			else {
				//ī�װ� ����Ȯ��
				cout << "Confirm new category? (type 'No' to cancle)" << endl << "> ";
				cin >> confirm_string;
				if (confirm_string.compare("No") != 0) {
					//ī�װ� ����
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
		//���� �̿��� �Է� ����ó��
		try {
			selected_num = stoi(input_string);
		}
		catch (const exception& expn) {
			cout << "Input only number" << endl;
		}
		//0 ~ table size �̿��� �Է� ���� ó��
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
				cout << "max category name size = 20" << endl;				//���� ���� ���� ����
			}
			else {
				//���� Ȯ��
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
		//���� �̿��� �Է� ����ó��
		try {
			selected_num = stoi(input_string);
		}
		catch (const exception& expn) {
			cout << "Input only number" << endl;
		}

		//0 ~ table size �̿��� �Է� ���� ó��
		if (selected_num > category_table->size() || selected_num < 1) {
			cout << "Number must be over 0 and under " << category_table->size() + 1 << endl;
		}
		else {
			//to do ����ó��: �ش� ī�װ� ��ȣ�� �����ϴ� ����� ������ ���� �ȵǰ�
			list <class Record>::iterator record_iter;
			list <class Record>::iterator end_of_record_list = record_list->end();

			selected_num--;

			for (record_iter = record_list->begin(); record_iter != end_of_record_list; record_iter++) {
				if (record_iter->category_number == selected_num) {
					duplicate_checker = true;
					break;
				}
			}
			//duplicate_checker == true�� ��ġ�� ��� ����
			if (duplicate_checker) {
				cout << "Some record have that category number. " << endl;
			}
			else {
				flag = false;
			}
		}
		
		//���� Ȯ��
		cout << "Confirm deletion? (type 'No' to cancel)" << endl << "> ";
		cin >> input_string;
		if (input_string == "No") {
			return true;
		}
		else {
			//���� �۾�
			iter = category_table->begin();
			advance(iter, selected_num);
			category_table->erase(iter);
			return false;
		}
	}
}