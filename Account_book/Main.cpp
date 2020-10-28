#include "header.hpp"

int main() {
	RecordManage record_manager;
	CategoryManage category_manager;
	string input_string;
	int menu_selected;
	bool flag;

	//to do: ���� �б� �� ������ ���� �۾�

	FileManage file_manager;

	if (!file_manager.initFile(record_manager, category_manager)) {
		return -1;
	}

	file_manager.saveFile(record_manager, category_manager);

	while (1) {
		//to do: ���θ޴� ��º�
		cout << "���θ޴�" << endl;

		//���ڸ� �Է¹��� �� ���� �ݺ�
		flag = true;
		while (flag) {
			cin >> input_string;
			try {
				menu_selected = stoi(input_string);
				flag = false;
			}
			catch (const exception & expn) {
				cout << "���ڸ� �Է��� �ּ���" << endl;
			}
		}

		switch (menu_selected) {
		case 1:
			//��� 1�� �߰�
			record_manager.addRecord(category_manager.getCategorySize());
			break;
		case 2:
			//��ü ��� ���
			record_manager.printAllRecordList(category_manager);
			break;
		case 3:
			//�˻�,����,���� �޴�
			record_manager.searchRecords(category_manager);
			break;
		case 4:
			//ī�װ� ���� �޴�
			category_manager.categoryMenu();
			break;
		case 5:
			//���� �۾�

			return 0;		//���α׷� ����
		default:
			cout << "1~5������ ���ڸ� �Է����ּ���." << endl;
			break;
		}
	}
}

