#define _CRT_SECURE_NO_WARNINGS
#include "header.hpp"

bool FileManage::initFile(RecordManage& record_manager, CategoryManage& category_manager) {
	ifstream in_Account("Account.txt");
	ifstream in_category("Category.txt");
	CheckerParser checker;

	/* Category.txt 부문 */
	if (!in_category.is_open()) {	// 파일이 열리지 않았다면
		cerr << "Warning: Category.txt not open" << endl;	// 경고문구 출력
		ofstream out_category("Category.txt");	// 출력 스트림

		string default_category[] = { "Bills", "Entertainment", "Food", "House Rent", "Transpoertation" };	// 예약된 키워드 출력

		for (auto s : default_category) {
			out_category << s << endl;
			category_manager.init_add(s);
		}

		cout << "Category.txt is created." << endl << endl;
		out_category.close();
	}

	else {
		cout << "Category.txt is opened normally." << endl << endl;	// 정상적으로 open

		string s;
		while (getline(in_category, s)) {
			Category c = Category(s);

			if (category_manager.isDuplicate(s)) {		// 카테고리 내 중복 목록이 있다면
				cout << "Warning: Duplicate Category" << endl;
				continue;
			}
			category_manager.init_add(c);

			if (category_manager.getCategorySize() > 64) {		// 카테고리 개수가 64개 이상일 시 false 반환
				cerr << "Error: Category size limit " << endl;
				in_category.close();
				return false;
			}
		}

		if (!category_manager.getCategorySize()) {		// 카테고리 목록이 비어있다면
			string default_category[] = { "Bills", "Entertainment", "Food", "House Rent", "Transpoertation" };
			for (auto s : default_category) {
				category_manager.init_add(s);
			}
		}
	}


	/* Account.txt 부문 */
	if (!in_Account.is_open()) {
		cerr << "Warning: Account.txt not open" << endl;

		ofstream out_Account("Account.txt");
		out_Account.close();
	}
	else {	// 정상적으로 open시
		cout << "Account.txt is opened normally." << endl << endl;


		string s;
		/* Account.txt 문자열 입력 */
		while (getline(in_Account, s)) {
			if (s == "") {		// 레코드가 개행뿐일 때
				cout << "NULL string이넹" << endl;
				continue;
			}
			vector<string> temp;

			//temp[0]: 시간, temp[1]: 수입/지출 temp[2]: 금액, temp[3]: 메모, temp[4]: 카테고리 숫자
			Tokenize(s, temp, "\t");	// Tab을 기준으로 하여 문자열 분리

			/////// 임시 데이터 ////////

			struct tm t;
			struct tm t2;
			t2.tm_year = -1;
			bool isIncome;
			unsigned int amount;
			string memo;
			short category_number;

			//t = setTime(temp[0]); // date 설정
			t = checker.checkParseDate(temp[0]);
			if (t.tm_year == t2.tm_year) {
				cerr << "Error: Date" << endl;
				return false;
			}

			if (temp[1] == "expense") {		// 수입/지출 설정
				isIncome = false;
			}

			else if (temp[1] == "income") {
				isIncome = true;
			}

			else {
				cerr << "Error: income/expense" << endl;
				return false;
			}


			if (!checker.checkAmount(temp[2]))
				amount = stoi(temp[2]);		// 금액 설정
			else {
				cerr << "Error:Amount" << endl;
			}

			if (!checker.checkMemo(temp[3]))
				memo = temp[3];				// 메모 설정

			else {
				cerr << "Error: Memo" << endl;
				return false;
			}

			if (!checker.checkCategoryNumber(temp[4], category_manager.getCategorySize))
				category_number = stoi(temp[4]);	// 카테고리 번호 설정
			else {
				cerr << "Error: Category NUmber" << endl;
			}

			Record r = Record(t, isIncome, amount, memo, category_number);		// Record 생성
			record_manager.init_add(r);		// RecordManage list에 추가

			if (record_manager.getRecordListSize() > 1024) {		// 레코드 개수가 1024개 이상일 시 false 반환
				cerr << "Error: Record size limit" << endl;
				in_Account.close();
				return false;
			}
		}
	}

	in_category.close();
	in_Account.close();

	return true;
}

bool FileManage::saveFile(RecordManage& record_manager, CategoryManage& category_manager) {
	/* Record 저장 */
	FILE* fp = fopen("Account.txt", "w");		// 파일 초기화
	fclose(fp);

	ofstream out_Account("Account.txt");

	while (record_manager.getRecordListSize()) {		// list size가 0이 될때까지
		string s = "";
		string income = "income";
		string expense = "expense";
		Record r = record_manager.getRecord();		// 1개 record 가져옴
		struct tm tm = r.get_date();		// 시간 입력
		if (tm.tm_min != 0)
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

		bool isIncome = r.get_isincome();	// 수입/지출 입력
		if (isIncome == true) {
			s += income + "\t";
		}
		else {
			s += expense + "\t";
		}

		unsigned int amount = r.get_amount();	// 금액 입력
		s += std::to_string(amount) + '\t';

		string memo = r.get_memo();		// 메모 입력
		s += memo + '\t';

		int category_num = r.get_category_number();	// 카테고리 숫자 입력
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

	tm1.tm_year = stoi(temp2[0]) - 1900;		// 연 설정
	tm1.tm_mon = stoi(temp2[1]) - 1;		// 월 설정
	tm1.tm_mday = stoi(temp2[2]);		// 일 설정
	tm1.tm_hour = stoi(temp3[0]);		// 시 설정
	tm1.tm_min = stoi(temp3[1]);			// 분 설정
	tm1.tm_sec = 0;

	tm2 = tm1;
	time_t t2 = mktime(&(tm1));

	if (t2 > t1) {		// 시간 조건 위배한다면?
		cout << "Warning: Time " << asctime(lt) << endl;
	}

	return tm2;
}

void Tokenize(const string& str, vector<string>& tokens, const string& delimiters) {		//1번 파라미터 문자열을 3번째 파라미터에 들어온 문자로 쪼개어 2번 벡터에 저장
	string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	string::size_type pos = str.find_first_of(delimiters, lastPos);

	while (string::npos != pos || string::npos != lastPos) {
		tokens.push_back(str.substr(lastPos, pos - lastPos));
		lastPos = str.find_first_not_of(delimiters, pos);
		pos = str.find_first_of(delimiters, lastPos);
	}
}
