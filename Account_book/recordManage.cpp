#include "header.hpp"
#include <iomanip>


bool deleteRecordList() {
	bool flag = true;
	int selected_num;
	string input_string;
	string confirm_string;
	string to_main_menu;		
	CheckerParser cp;
	list <Record>::iterator iter;
	iter = record_list.begin();


	cout << "@ Delete a transaction @ "<< endl;


	while (flag) {
		cout << "Enter transaction number  (q:return to main menu)" << endl << "> ";
		cin >> input_string;

		
		if (input_string.compare("q") == 0) {
			return true;
		}
		else {
			  
			if (input_string.size() > =1) {
				cout << "please enter a valid value" << endl;			
			}
			else {
				
				cout << "Confirm deletion? (type 'No' to cancle)" << endl << "> ";
				cin >> confirm_string;
				if (confirm_string.compare("No") != 0) {
					
					advance(iter, stoi(input_string));      

					record_list.erase(iter);  
					
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
	string input_data;
	string to_main_menu;		
	CheckerParser cp;
	list <Record>::iterator iter;
	iter = record_list.begin();


	

	while (flag) {
		cout << "@ Edit a transaction @ " << endl;
		cout << "Enter transaction number(q:return to main menu)" << endl << "> ";


		
		cout << "1. Date and Time " << endl;
		cout << "2. Income/Expense " << endl;
		cout << "3. Amount " << endl;
		cout << "4. Memo " << endl;
		cout << "5. Category " << endl;

		cout << "select field to edit (q:return to main menu)" << endl << "> ";
		cin >> input_string;

	
		if (input_string.compare("q") == 0) {
			return true;
		}
		else {
			 
			if (input_string.size() > = 1) {
				cout << "please enter a valid value" << endl;
			}
			else {
				

				switch (stoi(input_string) {
				case 1:
					// 날짜변경
					advance(iter, num);      //  n번째 인덱스로 iter 변경 후

					// 날짜 입력 

					break;
				case 2:
					// 수입 지출 변경

					advance(iter, num);     

					bool temp = !((*iter).is_income);
					(*iter).is_income = temp;
				
					break;
				case 3:
					//수량 변경
				    advance(iter, num);
					cout << "Amount before modification: " << (*iter).amount << endl;

					cout << "Enter amount after modification (q: return to mian menu)" << endl << "> ";
					cin >> input_data;

					if (input_string == "q") {
						break;
					}

					else if (!cp.checkAmount(input_data)) {
						// 수량 확인

						(*iter).amount = stoi(input_data);
						break;
					}

					else  break;
				case 4:
					//메모 변경


					advance(iter, num);
					cout << "Memo before modification: " << (*iter).memo << endl;

					cout << "Enter Memo after modification (q: return to mian menu)" << endl << "> ";
					cin >> input_data;

					if (input_string == "q") {
						break;
					}

					else if (!cp.checkMemo(input_data)) {

						(*iter).memo = input_data;
						break;
					}

					else  break;

				case 5:
					//카테고리 변경
					advance(iter, num);
					cout << "Category before modification: " << (*iter).category << endl;

					cout << "Enter Category after modification (q: return to mian menu)" << endl << "> ";
					cin >> input_data;

					if (input_string == "q") {
						break;
					}

					else if (!cp.checkCategory(input_data)) {

						(*iter).category = stoi(input_data);
						break;
					}

					else  break;
			
				default:
					cout << "you give wrong " << endl;
					break;
				}

				flag = false;
			}
		}
	}
	return false;


};

/*
전달 받은 인덱스가 담겨 있는 벡터 기반으로 레코드 리스트에서
해당 인덱스 리코드 값 가져와 저장한다.
*/
void makeselectedList(vector<int>& vec) {
	 list<Record> selectedList;   // main에 넣을 예정

	for (int i = 0; i < vec.size(); i++) {
		list <Record>::iterator iter;

		iter = record_list.begin();

		advance(iter, vec[i]);

		selectedList.push_back(iter);
	}

}

/*
선택된 값들 프린트 하는 함수 
*/

void printselectedList() {
	list<Record> selectedList;  // main에 넣을 예정 

	list <Record>::iterator iter;
	cout << "Date       Time     Type      Amount	Memo      Category" << endl;
	for (iter = record_list.begin(); iter != record_list.end(); iter++) {
		cout <<setw(15)<< (*iter).get_date() << setw(8) << (*iter).get_isincome()<< setw(10) << (*iter).get_amount()
			<< setw(10) <<(*iter).get_memo()<< setw(10) <<(*iter).get_category_number();
	}

}


list <Record>::iterator RecordManage::get_first(){
	return record_list.begin();
}
list <Record>::iterator RecordManage::get_end() {
	return record_list.end();
}
