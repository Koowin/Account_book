#include "header.hpp"



bool deleteRecordList() {
	bool flag = true;
	int selected_num;
	string input_string;
	string confirm_string;
	string to_main_menu;		//'q'�� ������ ���ڿ�
	to_main_menu.assign(1, 'q');
	list <Record>::iterator iter;
	iter = record_list.begin();


	cout << "@ Delete a transaction @ "<< endl;


	while (flag) {
		cout << "Enter transaction number  (q:return to main menu)" << endl << "> ";
		cin >> input_string;

		//�Է��� 'q'���� �˻�
		if (input_string.compare("q") == 0) {
			return true;
		}
		else {
			  // ��ǲ ���� 1�̻����� Ȯ�� 
			if (input_string.size() > =1) {
				cout << "please enter a valid value" << endl;			
			}
			else {
				//������ ���� Ȯ�� 
				cout << "Confirm deletion? (type 'No' to cancle)" << endl << "> ";
				cin >> confirm_string;
				if (confirm_string.compare("No") != 0) {
					
					advance(iter, stoi(input_string));      //  n��° �ε����� iter ���� �� 

					record_list.erase(iter);  // �� �ε��� ��� ���� 
					
				}
				flag = false;
			}
		}
	}
	return false;


};


bool modifyRecordList() {
	bool flag = true;
	int selected_num;
	string input_string;
	string confirm_string;
	string to_main_menu;		//'q'�� ������ ���ڿ�
	to_main_menu.assign(1, 'q');
	list <Record>::iterator iter;
	iter = record_list.begin();


	cout << "@ Delete a transaction @ " << endl;


	while (flag) {
		cout << "Enter transaction number  (q:return to main menu)" << endl << "> ";
		cin >> input_string;

		//�Է��� 'q'���� �˻�
		if (input_string.compare("q") == 0) {
			return true;
		}
		else {
			// ��ǲ ���� 1�̻����� Ȯ�� 
			if (input_string.size() > = 1) {
				cout << "please enter a valid value" << endl;
			}
			else {
				//������ ���� Ȯ�� 
				cout << "Confirm deletion? (type 'No' to cancle)" << endl << "> ";
				cin >> confirm_string;
				if (confirm_string.compare("No") != 0) {

					advance(iter, stoi(input_string));      //  n��° �ε����� iter ���� �� 

					record_list.erase(iter);  // �� �ε��� ��� ���� 

				}
				flag = false;
			}
		}
	}
	return false;


};
list <Record>::iterator RecordManage::get_first(){
	return record_list.begin();
}
list <Record>::iterator RecordManage::get_end() {
	return record_list.end();
}
