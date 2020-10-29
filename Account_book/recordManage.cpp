#include "header.hpp"

void RecordManage::searchMenu(CategoryManage& category_manager) {
	Conditions cd;

	string input_string;
	int selected_menu;
	bool search_start = false;
	while (1) {
		cout << "\n@ Search a transaction @" << endl;
		cout << "1. Date and Time" << endl;
		cout << "2. Income/Expense" << endl;
		cout << "3. Memo" << endl;
		cout << "4. Category " << endl;
		cout << "5. Reset conditions (by field)" << endl << endl;

		cout << "Select field (q:return to main menu)\n> ";
	
		bool flag = true;
		while (flag) {
			getline(cin, input_string);
			try {
				selected_menu = stoi(input_string);
				flag = false;
			}
			catch (const exception& expn) {
				cout << "Please enter a valid value." << endl;
			}
		}

		if (input_string == "q") {
			break;
		}
		if (selected_menu > 5 || selected_menu < 1) {
			cout << "Please enter a valid value" << endl;
		}
		else {
			short n;
			switch (selected_menu) {
			case 1:
				//�Ⱓ ���� �߰�
				n = cd.addPeriodCondition();
				if (n == -1) {
					break;
				}
				else {
					search_start = !n;
				}
				break;
			case 2:
				//����, ���� ���� �߰�
				n = cd.addIeCondition();
				if (n == -1) {
					break;
				}
				else {
					search_start = !n;
				}
				break;
			case 3:
				//�޸� Ű���� ���� �߰�
				n = cd.addMemoCondition();
				if (n == -1) {
					break;
				}
				else {
					search_start = !n;
				}
				break;
			case 4:
				//ī�װ� ���� �߰�
				n = cd.addCategoryCondition(category_manager);
				if (n == -1) {
					break;
				}
				else {
					search_start = !n;
				}
				break;
			case 5:
				//���� �ʱ�ȭ
				n = cd.resetConditions();
				if (n == -1) {
					break;
				}
				else {
					search_start = !n;
				}
				break;
			}
			if (search_start) {
				cout << "���ǿ� �´� ��� ���" << endl;
			}
		}
	}
}