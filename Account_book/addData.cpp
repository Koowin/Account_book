#include"header.cpp"

void addRecord() {
	string input, token, date, money, amount, memo, category_num;
	string date_date, date_year, date_month, date_day, date_time, date_hour, date_min;
	bool flag = true;
	int classify = 0;
	int classify_date_date = 0;
	int classify_date = 0;
	int classify_time = 0;
	int date_arr[5];

	getline(cin, input);

	istringstream iss_input(input);

	while (getline(iss_input, token, '\t')) {	// Tab을 기준으로 입력값 분할
		if (classify == 0) {
			date = token;
			classify++;
		}
		else if (classify == 1) {
			money = token;
			classify++;
		}
		else if (classify == 2) {
			amount = token;
			classify++;
		}
		else if (classify == 3) {
			memo = token;
			classify++;
		}
		else if (classify == 4) {
			category_num = token;
			classify++;
		}
		else
			classify++;
	}
	if (classify != 5) {	// 입력 해야하는 모든값을 입력하지 않았거나 입력값을 초과했을 때
		cout << "Invalid input format, 5 different values needed (Date, Money, Amount, Memo, CategoryNumber) " << endl;
		flag = false;
	}

	istringstream iss_divide_date(date);

	while (getline(iss_divide_date, token, ' ')) { //날짜와 시간을 공백을 기준으로 나눔
		if (classify_date == 0) {
			date_date = token;
			classify_date++;
		}
		else if (classify_date == 1) {
			date_time = token;
			classify_date++;
		}
	}
	cout << date_date << " divided " << date_time << endl;

	istringstream iss_date(date_date);

	while (getline(iss_date, token, '/')) { // 날짜를 '/'를 기준으로 각각 년, 월, 일로 나눔
		if (classify_date_date == 0) {
			date_year = token;
			classify_date_date++;
		}
		else if (classify_date_date == 1) {
			date_month = token;
			classify_date_date++;
		}
		else if (classify_date_date == 2) {
			date_day = token;
			classify_date_date++;
		}
	}

	istringstream iss_time(date_time);

	while (getline(iss_time, token, ':')) { // 시간을 ':'를 기준으로 시,분으로 나눔
		if (classify_time == 0) {
			date_hour = token;
			classify_time++;
		}
		else if (classify_time == 1) {
			date_min = token;
			classify_time++;
		}
	}
  // int형 배열에 년,월,일,시,분을 저장
	date_arr[0] = stoi(date_year);  
	date_arr[1] = stoi(date_month);
	date_arr[2] = stoi(date_day);
	date_arr[3] = stoi(date_hour);
	date_arr[4] = stoi(date_min);

	if (flag) {	// 입력 값이 5개가 입력이 되면 문법 검사 및 오류검사 진행
		if (checkDate(date_arr) && checkMoney(money) && checkAmount(stoi(amount)) && checkMemo(memo) && checkCategoryNumber(stoi(category_num) == 0)) {
			recordList.push_back(input);
		}
	}

	return;
}
