//#define _CRT_SECURE_NO_WARNINGS
//#include "header.hpp"
//
//void Category::printAll() {
//	list<string>::iterator iter = category.begin();
//	for (; iter != category.end();) {
//		cout << *iter << endl;
//		iter++;
//	}
//}
//
//Category::Category() {
//
//}
//
//Category::Category(ifstream& in) {
//	string s;
//	
//	while (getline(in,s)) {
//		list<string>::iterator iter = category.begin();
//		for (; iter != category.end();) {
//			if (*iter == s) {
//				cout << "ī�װ� ��Ͽ� �ߺ���" << endl;		// ���� ����
//				iter = category.erase(iter);
//				continue;
//			}
//			iter++;
//		}
//
//		category.push_back(s);
//	}
//}
//
//void initFiles(void) {
//	vector<Record> v;
//
//	ifstream in_Account("Account.txt");
//	ifstream in_category("Category.txt");
//
//	if (!in_category.is_open()) {	// ������ ������ �ʾҴٸ�
//		cerr << "Warning: Category.txt not open" << endl;	// ����� ���
//
//		ofstream out_category("Category.txt");	// ��� ��Ʈ��
//
//		string default_category[] = { "Bills", "Entertainment", "Food", "House Rent", "Transpoertation"};	// ����� Ű���� ���
//
//		for (auto s : default_category) {
//			out_category << s << endl;
//		}
//		
//		cout << "Category.txt is created." << endl << endl;
//	}
//	
//	else {
//		cout << "Category.txt is opened normally." << endl << endl;	// ���������� open
//		Category c = Category(in_category);
//		//c.printAll();
//	}
//
//
//	if (!in_Account.is_open()) {
//		cerr << "Warning: Account.txt not open" << endl;
//
//		ofstream out_Account("Account.txt");
//	}
//	else {
//		string s;
//
//		/* Account.txt ���ڿ� �Է� */
//		while (getline(in_Account, s)) {
//			vector<string> temp;
//
//			//temp[0]: �ð�, temp[1]: ����/���� temp[2]: �ݾ�, temp[3]: �޸�, temp[4]: ī�װ� ����
//			Tokenize(s, temp, "\t");	// Tab�� �������� �Ͽ� ���ڿ� �и�
//
//			Record r;		// �ӽ� r ����
//
//			setTime(r, temp[0]); // date ����
//
//			if (temp[1] == "expense") {		// ����/���� ����
//				r.is_income = false;
//			}
//
//			else if (temp[1] == "income") {
//				r.is_income = true;
//			}
//
//			r.amount = stoi(temp[2]);		// �ݾ� ����
//			r.memo = temp[3];				// �޸� ����
//			r.category_number = stoi(temp[4]);	// ī�װ� ��ȣ ����
//
//			v.push_back(r);		//v�� ����	( ���� ���� ȸ�� ���� ���� )
//		}
//	}
//	in_category.close();
//	in_Account.close();
//}
//
//void setTime(Record& r, string tm) {
//	struct tm* lt;
//	time_t t1;
//
//	t1 = time(NULL);
//	lt = localtime(&t1);
//
//	vector<string> temp1;
//	vector<string> temp2;
//	vector<string> temp3;
//	Tokenize(tm, temp1, " ");	// temp1[0]: YYYY/MM/DD, temp1[1]: HH:MM
//	Tokenize(temp1[0], temp2, "/");	// temp2[0]: YYYY, temp2[1]: MM, temp2[2]: DD
//	Tokenize(temp1[1], temp3, ":");	// temp3[0]: HH, temp3[1]: MM
//
//	r.date.tm_year = stoi(temp2[0])-1900;		// �� ����
//	r.date.tm_mon = stoi(temp2[1]) - 1;		// �� ����
//	r.date.tm_mday = stoi(temp2[2]);		// �� ����
//	r.date.tm_hour = stoi(temp3[0]);		// �� ����
//	r.date.tm_min = stoi(temp3[1]);			// �� ����
//	r.date.tm_sec = 0;
//
//	time_t t2 = mktime(&(r.date));
//
//	if (t2 > t1) {
//		cout << "Warning: Time ~~~. Current time: " << asctime(lt) << endl;
//	}
//}
//
//bool saveFiles(list<Record> l, Category c) {
//	ifstream in_Account("Account.txt");
//
//	if (!in_Account.is_open()) {
//		ofstream out_Account("Account.txt");
//
//		vector<string> s;
//		list<Record>::iterator iter = l.begin();
//		for (; iter != l.end(); ) {
//			string temp =
//				std::to_string((*iter).date.tm_year + 1900) + "/" +
//				std::to_string((*iter).date.tm_mon + 1) + "/" +
//				std::to_string((*iter).date.tm_mday) + "\t" +
//				"income" + "\t" +
//				std::to_string((*iter).amount) + "\t" +
//				(*iter).memo + "\t" +
//				"1" + "\n";
//
//			iter++;
//		}
//		
//	}
//}
//
//void Tokenize(const string& str, vector<string>& tokens, const string& delimiters) {		//1�� �Ķ���� ���ڿ��� 3��° �Ķ���Ϳ� ���� ���ڷ� �ɰ��� 2�� ���Ϳ� ����
//	string::size_type lastPos = str.find_first_not_of(delimiters, 0);
//	string::size_type pos = str.find_first_of(delimiters, lastPos);
//
//	while (string::npos != pos || string::npos != lastPos) {
//		tokens.push_back(str.substr(lastPos, pos - lastPos));
//		lastPos = str.find_first_not_of(delimiters, pos);
//		pos = str.find_first_of(delimiters, lastPos);
//	}
//}
