#include "header.hpp"

int main() {
	class RecordManage record_manager;
	class CategoryManage category_manager;
	string input_string;
	int menu_selected;
	bool flag = true;
	
	/* 재혁 추가 */
	FileManage file_manager;
	
	if (!file_manager.initFile(record_manager, category_manager)) {
		cerr << "Error: File initialization error" << endl; 
		return -1;
	}
	cout << "\nPress any key to continue...";
	_getch();
	//to do: 파일 읽기 및 데이터 저장 작업
	while (1) {
		//메인메뉴 출력부
		while (1) {
			if (flag) {
				system("cls"); 
				cout << "@ Main menu @" << endl;
				cout << "1. Add a transaction" << endl;
				cout << "2. View all transactions" << endl;
				cout << "3. Search/Edit/Delete a transaction" << endl;
				cout << "4. Manage category" << endl;
				cout << "5. Quit" << endl << endl;
				cout << "Select menu" << endl << "> ";
			}
			getline(cin, input_string);
			//add record
			if (input_string == "1") {
				if (record_manager.getRecordListSize() > 1024) { //신이 : 1023 >> 1024
					cout << "Your number of transactions has exceeded its maximum value (1024 transactions)." << endl;
					cout << "Please delete some of your transactions to continue." << endl;
					cout << "Press any key to continue...";
					_getch();
				}
				else {
					record_manager.addRecord(category_manager);
				}
				flag = true;
			}
			//print all records
			else if (input_string == "2") {
				record_manager.printAllRecordList(category_manager);
				flag = true;
			}
			//search menu
			else if (input_string == "3") {
				record_manager.searchMenu(category_manager);
				flag = true;
			}
			//category menu
			else if (input_string == "4") {
				category_manager.categoryMenu(record_manager);
				flag = true;
			}
			else if (input_string == "5") {
				//저장 작업
				file_manager.saveFile(record_manager, category_manager);
				return 0;
			}
			else{
				cout << "Please enter a valid value.\n> ";
				flag = false;
			}
		}
	}
}
