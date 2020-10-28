#include "header.hpp"
#include <iomanip>

void RecordManage::printAllRecordList(CategoryManage&) {

}

bool RecordManage::addRecord(int category_size) {
	class CheckerParser cp;
	string input_string;
	bool flag = true;

	struct tm date;
	bool is_income;
	unsigned int amount;
	string memo;
	int category_number;


	//날짜 입력받는 부분
	while (flag) {
		cout << "날짜 입력" << endl;
		cin >> input_string;

		if (input_string == "q") {
			return true;
		}
		//정상 입력 시
		if (!cp.checkDate(input_string)) {
			date = cp.parseDate(input_string);
			flag = false;
		}
		//비정상 입력 시 오류 문구 출력 후 반복
	}


	//수입/지출 입력받는 부분
	flag = true;
	while (flag) {
		cout << "수입/지출" << endl;
		cin >> input_string;

		if (input_string == "q") {
			return true;
		}
		//정상 입력 시
		else if (input_string == "1" || input_string == "2") {
			if (input_string == "1") {
				is_income = true;
			}
			else {
				is_income = false;
			}
			flag == false;
		}
		//비정상 입력 시
		else {
			//to do : 오류 문구 영어로 바꾸기
			cout << "오류 문구 출력" << endl;
		}
	}

	//금액 입력 받는 부분
	flag = true;
	while (flag) {
		cout << "금액 입력" << endl;
		cin >> input_string;

		if (input_string == "q") {
			return true;
		}

		//정상 입력 시
		if (!cp.checkAmount(input_string)) {
			amount = cp.parseAmount(input_string);
			flag = false;
		}
		//비정상 입력 시 오류 문구 출력하고 반복
	}

	//메모 입력 받는 부분
	flag = true;
	while (flag) {
		cout << "메모 입력" << endl;
		cin >> input_string;

		if (input_string == "q") {
			return true;
		}

		//정상 입력 시
		if (!cp.checkMemo(input_string)) {
			memo = input_string;
		}
		//비정상 입력 시 오류 문구 출력하고 반복
	}

	//카테고리 번호 입력 받는 부분
	flag = true;
	while (flag) {
		cout << "카테고리 번호 입력" << endl;
		cin >> input_string;

		if (input_string == "q") {
			return true;
		}
		try {
			category_number = stoi(input_string);
		}
		catch (const exception& expn) {
			cout << "숫자만 입력해주세요" << endl;
		}

		if (category_number > 0 && category_number <= category_size) {
			flag = false;
		}
		else {
			cout << "1 부터 " << category_size << " 사이의 숫자만 입력해주세요" << endl;
		}
	}

	//저장 확인 물어보는 부분
	cout << "저장하시겠습니까? (취소: No)" << endl;
	cin >> input_string;

	if (input_string == "No") {
		return true;
	}
	else {
		//to do : index 찾아서 넣기 혹은 넣고 정렬하기
		record_list.push_back(Record(date, is_income, amount, memo, category_number));
		return false;
	}
}

bool RecordManage::deleteRecordList() {
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
			  
			if (input_string.size() >= 1) {
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


bool RecordManage::modifyRecordList() {
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
void RecordManage::makeSelectedList(vector<int>& vec) {
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

void RecordManage::printSelectedList() {
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