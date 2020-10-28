//나중에 신이님 결과물 합쳐서 넣을 예정
//찬종님이 기록 수정, 삭제 구현해주세요~

#include "header.hpp"



bool deleteRecordList() {
	bool flag = true;
	int selected_num;
	string input_string;
	string confirm_string;
	string to_main_menu;		//'q'를 저장할 문자열
	to_main_menu.assign(1, 'q');
	list <Record>::iterator iter;
	iter = record_list.begin();


	cout << "@ Delete a transaction @ "<< endl;


	while (flag) {
		cout << "Enter transaction number  (q:return to main menu)" << endl << "> ";
		cin >> input_string;

		//입력이 'q'인지 검사
		if (input_string.compare("q") == 0) {
			return true;
		}
		else {
			  // 인풋 값이 1이상인지 확인 
			if (input_string.size() > =1) {
				cout << "please enter a valid value" << endl;			
			}
			else {
				//저장기록 삭제 확인 
				cout << "Confirm deletion? (type 'No' to cancle)" << endl << "> ";
				cin >> confirm_string;
				if (confirm_string.compare("No") != 0) {
					
					advance(iter, stoi(input_string));      //  n번째 인덱스로 iter 변경 후 

					record_list.erase(iter);  // 그 인덱스 노드 삭제 
					
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
	string to_main_menu;		//'q'를 저장할 문자열
	to_main_menu.assign(1, 'q');
	list <Record>::iterator iter;
	iter = record_list.begin();


	cout << "@ Delete a transaction @ " << endl;


	while (flag) {
		cout << "Enter transaction number  (q:return to main menu)" << endl << "> ";
		cin >> input_string;

		//입력이 'q'인지 검사
		if (input_string.compare("q") == 0) {
			return true;
		}
		else {
			// 인풋 값이 1이상인지 확인 
			if (input_string.size() > = 1) {
				cout << "please enter a valid value" << endl;
			}
			else {
				//저장기록 삭제 확인 
				cout << "Confirm deletion? (type 'No' to cancle)" << endl << "> ";
				cin >> confirm_string;
				if (confirm_string.compare("No") != 0) {

					advance(iter, stoi(input_string));      //  n번째 인덱스로 iter 변경 후 

					record_list.erase(iter);  // 그 인덱스 노드 삭제 

				}
				flag = false;
			}
		}
	}
	return false;


};