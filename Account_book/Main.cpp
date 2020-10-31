#include "header.hpp"

int main() {
	class RecordManage record_manager;
	class CategoryManage category_manager;
	string input_string;
	int menu_selected;
	bool flag;
	
	/* 재혁 추가 */
	FileManage file_manager;
	
	if (!file_manager.initFile(record_manager, category_manager)) {
		cerr << "Error: File initialization error" << endl; 
		return -1;
	}

	//to do: 파일 읽기 및 데이터 저장 작업
	while (1) {
		//메인메뉴 출력부
		system("pause");
		system("cls"); //신이 추가
		cout << "@ Main menu @" << endl;
		cout << "1. Add a transaction" << endl;
		cout << "2. View all transactions" << endl;
		cout << "3. Search/Edit/Delete a transaction" << endl;
		cout << "4. Manage category" << endl;
		cout << "5. Quit" << endl << endl;
		cout << "Select menu" << endl << "> ";

		//���ڸ� �Է¹�� �� ���� �ݺ�
		while (1) {
			getline(cin, input_string);
			if (input_string == "1") {
				//��� 1�� �߰�
				if (record_manager.getRecordListSize() > 1023) {
					cout << "Your number of transactions has exceeded its maximum value (1024 transactions)." << endl;
					cout << "Please delete some of your transactions to continue." << endl;
				}
				else {
					record_manager.addRecord(category_manager);
				}
			}
			else if (input_string == "2") {
				//��ü ��� ���
				record_manager.printAllRecordList(category_manager);
			}
			else if (input_string == "3") {
				//�˻�,���,��� �޴�
				record_manager.searchMenu(category_manager);
			}
			else if (input_string == "4") {
				//ī�װ� �� �޴�
				category_manager.categoryMenu(record_manager);
			}
			else if (input_string == "5") {
				//���� �۾�
			}
			else{
				cout << "Please enter a valid value." << endl;
			}
		}
	}
}
