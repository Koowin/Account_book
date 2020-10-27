#include "header.hpp"

int main() {
	class RecordManage record_manager;
	class CategoryManage category_manager;
	string input_string;
	int menu_selected;
	bool flag;

	//to do: ���� �б� �� ������ ���� �۾�

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
			catch (const exception& expn) {
				cout << "���ڸ� �Է��� �ּ���" << endl;
			}
		}

		switch(menu_selected) {
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
			category_manager.categoryMenu(record_manager);
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






bool RecordManage::addRecord(int category_size) {
	class CheckerParser cp;
	string input_string;
	bool flag = true;

	struct tm date;
	bool is_income;
	unsigned int amount;
	string memo;
	int category_number;
	

	//��¥ �Է¹޴� �κ�
	while(flag){
		cout << "��¥ �Է�" << endl;
		cin >> input_string;

		if (input_string == "q") {
			return true;
		}
		//���� �Է� ��
		if (!cp.checkDate(input_string)) {
			date = cp.parseDate(input_string);
			flag = false;
		}
		//������ �Է� �� ���� ���� ��� �� �ݺ�
	}


	//����/���� �Է¹޴� �κ�
	flag = true;
	while (flag) {
		cout << "����/����" << endl;
		cin >> input_string;

		if (input_string == "q") {
			return true;
		}
		//���� �Է� ��
		else if (input_string == "1" || input_string == "2") {
			if (input_string == "1") {
				is_income = true;
			}
			else {
				is_income = false;
			}
			flag == false;
		}
		//������ �Է� ��
		else {
			//to do : ���� ���� ����� �ٲٱ�
			cout << "���� ���� ���" << endl;
		}
	}

	//�ݾ� �Է� �޴� �κ�
	flag = true;
	while (flag) {
		cout << "�ݾ� �Է�" << endl;
		cin >> input_string;

		if (input_string == "q") {
			return true;
		}
		
		//���� �Է� ��
		if (!cp.checkAmount(input_string)) {
			amount = cp.parseAmount(input_string);
			flag = false;
		}
		//������ �Է� �� ���� ���� ����ϰ� �ݺ�
	}

	//�޸� �Է� �޴� �κ�
	flag = true;
	while (flag) {
		cout << "�޸� �Է�" << endl;
		cin >> input_string;

		if (input_string == "q") {
			return true;
		}

		//���� �Է� ��
		if (!cp.checkMemo(input_string)) {
			memo = input_string;
		}
		//������ �Է� �� ���� ���� ����ϰ� �ݺ�
	}

	//ī�װ� ��ȣ �Է� �޴� �κ�
	flag = true;
	while (flag) {
		cout << "ī�װ� ��ȣ �Է�" << endl;
		cin >> input_string;

		if (input_string == "q") {
			return true;
		}
		try {
			category_number = stoi(input_string);
		}
		catch (const exception& expn) {
			cout << "���ڸ� �Է����ּ���" << endl;
		}

		if (category_number > 0 && category_number <= category_size) {
			flag = false;
		}
		else {
			cout << "1 ���� " << category_size << " ������ ���ڸ� �Է����ּ���" << endl;
		}
	}
	
	//���� Ȯ�� ����� �κ�
	cout << "�����Ͻðڽ��ϱ�? (���: No)" << endl;
	cin >> input_string;

	if (input_string == "No") {
		return true;
	}
	else {
		//to do : index ã�Ƽ� �ֱ� Ȥ�� �ְ� �����ϱ�
		record_list.push_back(Record(date, is_income, amount, memo, category_number));
		return false;
	}
}