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
*	main�Լ����� category_table�� �޾Ƽ� ��� ī�װ� ����� ����ϴ� �Լ�
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
*	���ο� ī�װ��� �߰��ϴ� �Լ�
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

		//�Է��� 'q'���� �˻�
		if (input_string == "q") {
			return true;
		}
		else {
			if (category.size() >= 64) {
				cout << "Your number of categories has exceeded its maximum value (64 categories)." << endl;
				cout << "Please delete some of your categories to continue." << endl;
			}
			else {
				//ī�װ� ���ڿ� ���� �˻�
				if (!cp.checkCategoryName(input_string)) {
					//�ߺ� �˻�
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
						//ī�װ� ����Ȯ��
						cout << "Confirm new category? (type 'No' to cancle)" << endl << "> ";
						cin >> confirm_string;
						if (confirm_string != "No") {
							//ī�װ� ����
							category.push_back(Category(input_string));
						}
						flag = false;
					}
				}
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

	//ī�װ� ��º�
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
		//���� �̿��� �Է� ����ó��
		try {
			selected_num = stoi(input_string);
		}
		catch (const exception& expn) {
			cout << "Input only number" << endl;
		}
		//0 ~ table size �̿��� �Է� ���� ó��
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
					//���� Ȯ��
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
		//���� �̿��� �Է� ����ó��
		try {
			selected_num = stoi(input_string);
		}
		catch (const exception& expn) {
			cout << "Input only number" << endl;
		}

		//0 ~ table size �̿��� �Է� ���� ó��
		list <Record>::iterator record_iter;
		list <Record>::iterator end_of_record_list = record_manager.get_end();

		if (selected_num > category.size() || selected_num < 1) {
			cout << "Number must be over 0 and under " << category.size() + 1 << endl;
		}
		else {
			//����ó��: ī�װ� ������ 1���� ���� �ȵǰ�
			if (category.size() < 2) {
				cout << "There must be at least one category. Category is not deleted." << endl;
				flag = false;
			}

			//����ó��: �ش� ī�װ� ��ȣ�� �����ϴ� ����� ������ ���� �ȵǰ�
			selected_num--;

			for (record_iter = record_manager.get_first(); record_iter != end_of_record_list; record_iter++) {
				if (record_iter->get_category_number() == selected_num) {
					duplicate_checker = true;
					break;
				}
			}
			//duplicate_checker == true�� ��ġ�� ��� ����
			if (duplicate_checker) {
				cout << "Some record have that category number. " << endl;
				flag = false;
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
			//��� ��ϵ� ī�װ� ��ȣ �ϳ��� ���̱� (������ �� ���� ũ�ٸ�)
			for (record_iter = record_manager.get_first(); record_iter != end_of_record_list; record_iter++) {
				int category_num = record_iter->get_category_number();
				if (category_num > selected_num+1) {
					record_iter->set_category_number(category_num-1);
				}
			}
			//���� �۾�
			iter = category.begin();
			advance(iter, selected_num);
			category.erase(iter);
			return false;
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