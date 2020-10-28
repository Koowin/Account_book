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
//				cout << "카테고리 목록에 중복됨" << endl;		// 수정 예정
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
//	if (!in_category.is_open()) {	// 파일이 열리지 않았다면
//		cerr << "Warning: Category.txt not open" << endl;	// 경고문구 출력
//
//		ofstream out_category("Category.txt");	// 출력 스트림
//
//		string default_category[] = { "Bills", "Entertainment", "Food", "House Rent", "Transpoertation"};	// 예약된 키워드 출력
//
//		for (auto s : default_category) {
//			out_category << s << endl;
//		}
//		
//		cout << "Category.txt is created." << endl << endl;
//	}
//	
//	else {
//		cout << "Category.txt is opened normally." << endl << endl;	// 정상적으로 open
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
//		/* Account.txt 문자열 입력 */
//		while (getline(in_Account, s)) {
//			vector<string> temp;
//
//			//temp[0]: 시간, temp[1]: 수입/지출 temp[2]: 금액, temp[3]: 메모, temp[4]: 카테고리 숫자
//			Tokenize(s, temp, "\t");	// Tab을 기준으로 하여 문자열 분리
//
//			Record r;		// 임시 r 설정
//
//			setTime(r, temp[0]); // date 설정
//
//			if (temp[1] == "expense") {		// 수입/지출 설정
//				r.is_income = false;
//			}
//
//			else if (temp[1] == "income") {
//				r.is_income = true;
//			}
//
//			r.amount = stoi(temp[2]);		// 금액 설정
//			r.memo = temp[3];				// 메모 설정
//			r.category_number = stoi(temp[4]);	// 카테고리 번호 설정
//
//			v.push_back(r);		//v에 삽입	( 삽입 순서 회의 이후 결정 )
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
//	r.date.tm_year = stoi(temp2[0])-1900;		// 연 설정
//	r.date.tm_mon = stoi(temp2[1]) - 1;		// 월 설정
//	r.date.tm_mday = stoi(temp2[2]);		// 일 설정
//	r.date.tm_hour = stoi(temp3[0]);		// 시 설정
//	r.date.tm_min = stoi(temp3[1]);			// 분 설정
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
//void Tokenize(const string& str, vector<string>& tokens, const string& delimiters) {		//1번 파라미터 문자열을 3번째 파라미터에 들어온 문자로 쪼개어 2번 벡터에 저장
//	string::size_type lastPos = str.find_first_not_of(delimiters, 0);
//	string::size_type pos = str.find_first_of(delimiters, lastPos);
//
//	while (string::npos != pos || string::npos != lastPos) {
//		tokens.push_back(str.substr(lastPos, pos - lastPos));
//		lastPos = str.find_first_not_of(delimiters, pos);
//		pos = str.find_first_of(delimiters, lastPos);
//	}
//}
