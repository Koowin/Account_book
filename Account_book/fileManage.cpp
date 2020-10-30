#define _CRT_SECURE_NO_WARNINGS
#include "header.hpp"

bool FileManage::initFile(RecordManage& record_manager,CategoryManage& category_manager) {
	ifstream in_Account("Account.txt");
	ifstream in_category("Category.txt");

	/* Account.txt �ι� */
	if (!in_Account.is_open()) {
		cerr << "Warning: Account.txt not open" << endl;

		ofstream out_Account("Account.txt");
		out_Account.close();
	}
	else {	// ���������� open��
		cout << "Account.txt is opened normally." << endl << endl;	


		string s;
		/* Account.txt ���ڿ� �Է� */
		while (getline(in_Account, s)) {
			if (s == "") {		// ���ڵ尡 ������� ��
				cout << "NULL string�̳�" << endl;
				continue;
			}
			vector<string> temp;

			//temp[0]: �ð�, temp[1]: ����/���� temp[2]: �ݾ�, temp[3]: �޸�, temp[4]: ī�װ� ����
			Tokenize(s, temp, "\t");	// Tab�� �������� �Ͽ� ���ڿ� �и�
			
			/////// �ӽ� ������ ////////
			
			struct tm t;
			bool isIncome;
			unsigned int amount;
			string memo;
			short category_number;
			
			t = setTime(temp[0]); // date ����

			if (temp[1] == "expense") {		// ����/���� ����
				isIncome = false;
			}

			else if (temp[1] == "income") {
				isIncome = true;
			}

			amount = stoi(temp[2]);		// �ݾ� ����

			memo = temp[3];				// �޸� ����

			category_number = stoi(temp[4]);	// ī�װ� ��ȣ ����

			Record r = Record(t, isIncome, amount, memo, category_number);		// Record ����
			record_manager.init_add(r);		// RecordManage list�� �߰�

			if (record_manager.getRecordListSize() > 1024) {		// ���ڵ� ������ 1024�� �̻��� �� false ��ȯ
				cerr << "Error: Record size limit" << endl;
				in_Account.close();
				return false;
			}
		}
	}

	/* Category.txt �ι� */
	if (!in_category.is_open()) {	// ������ ������ �ʾҴٸ�
		cerr << "Warning: Category.txt not open" << endl;	// ����� ���
		ofstream out_category("Category.txt");	// ��� ��Ʈ��

		string default_category[] = { "Bills", "Entertainment", "Food", "House Rent", "Transpoertation"};	// ����� Ű���� ���

		for (auto s : default_category) {
			out_category << s << endl;
		}
		
		cout << "Category.txt is created." << endl << endl;
		out_category.close();
	}
	
	else {
		cout << "Category.txt is opened normally." << endl << endl;	// ���������� open
		
		string s;
		while (getline(in_category, s)) {
			Category c = Category(s);

			if (category_manager.isDuplicate(s)) {		// ī�װ� �� �ߺ� ����� �ִٸ�
				cout << "Warning: Duplicate Category" << endl;
				continue;
			}
			category_manager.init_add(c);

			if (category_manager.getCategorySize() > 64) {		// ī�װ� ������ 64�� �̻��� �� false ��ȯ
				cerr << "Error: Category size limit " << endl;
				in_category.close();
				return false;
			}
		}

		if (!category_manager.getCategorySize()) {		// ī�װ� ����� ����ִٸ�
			string default_category[] = { "Bills", "Entertainment", "Food", "House Rent", "Transpoertation" };
			for (auto s : default_category) {
				category_manager.init_add(s);
			}
		}
	}

	in_category.close();
	in_Account.close();

	return true;
}

bool FileManage::saveFile(RecordManage& record_manager, CategoryManage& category_manager) {
	/* Record ���� */
	FILE* fp = fopen("Account.txt", "w");		// ���� �ʱ�ȭ
	fclose(fp);

	ofstream out_Account("Account.txt");
	
	while (record_manager.getRecordListSize()) {		// list size�� 0�� �ɶ�����
		string s = "";
		string income = "income";
		string expense = "expense";
		Record r = record_manager.getRecord();		// 1�� record ������
		struct tm tm = r.get_date();		// �ð� �Է�
		if(tm.tm_min != 0)
			s += to_string((tm.tm_year) + 1900) + "/" +
				to_string((tm.tm_mon) + 1) + "/" +
				to_string(tm.tm_mday) + " " +
				to_string(tm.tm_hour) + ":" +
				to_string(tm.tm_min) + "\t";
		
		else
			s += to_string((tm.tm_year) + 1900) + "/" +
				to_string((tm.tm_mon) + 1) + "/" +
				to_string(tm.tm_mday) + " " +
				to_string(tm.tm_hour) + ":" +
				to_string(tm.tm_min) + '0' + "\t";

		bool isIncome = r.get_isincome();	// ����/���� �Է�
		if (isIncome == true) {		
			s += income + "\t";
		}
		else {
			s += expense + "\t";
		}

		unsigned int amount = r.get_amount();	// �ݾ� �Է�
		s += std::to_string(amount) + '\t';
		
		string memo = r.get_memo();		// �޸� �Է�
		s += memo + '\t';

		int category_num = r.get_category_number();	// ī�װ� ���� �Է�
		s += std::to_string(category_num);
		out_Account << s << endl;
	}

	fp = fopen("Category.txt", "w");
	fclose(fp);

	ofstream out_Category("Category.txt");

	while (category_manager.getCategorySize()) {
		string s = "";
		Category c = category_manager.getCategory();
		s += c.get_cname();

		out_Category << s << endl;
	}

	cout << "done" << endl << endl;

	out_Account.close();
	out_Category.close();

	return true;
}

struct tm setTime(string tm) {
	struct tm tm1, tm2;
	struct tm* lt;
	time_t t1;

	t1 = time(NULL);
	lt = localtime(&t1);

	vector<string> temp1;
	vector<string> temp2;
	vector<string> temp3;
	Tokenize(tm, temp1, " ");	// temp1[0]: YYYY/MM/DD, temp1[1]: HH:MM
	Tokenize(temp1[0], temp2, "/");	// temp2[0]: YYYY, temp2[1]: MM, temp2[2]: DD
	Tokenize(temp1[1], temp3, ":");	// temp3[0]: HH, temp3[1]: MM

	tm1.tm_year = stoi(temp2[0])-1900;		// �� ����
	tm1.tm_mon = stoi(temp2[1]) - 1;		// �� ����
	tm1.tm_mday = stoi(temp2[2]);		// �� ����
	tm1.tm_hour = stoi(temp3[0]);		// �� ����
	tm1.tm_min = stoi(temp3[1]);			// �� ����
	tm1.tm_sec = 0;

	tm2 = tm1;
	time_t t2 = mktime(&(tm1));

	if (t2 > t1) {		// �ð� ���� �����Ѵٸ�?
		cout << "Warning: Time ~~~. Current time: " << asctime(lt) << endl;	
	}

	return tm2;
}

void Tokenize(const string& str, vector<string>& tokens, const string& delimiters) {		//1�� �Ķ���� ���ڿ��� 3��° �Ķ���Ϳ� ���� ���ڷ� �ɰ��� 2�� ���Ϳ� ����
	string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	string::size_type pos = str.find_first_of(delimiters, lastPos);

	while (string::npos != pos || string::npos != lastPos) {
		tokens.push_back(str.substr(lastPos, pos - lastPos));
		lastPos = str.find_first_not_of(delimiters, pos);
		pos = str.find_first_of(delimiters, lastPos);
	}
}