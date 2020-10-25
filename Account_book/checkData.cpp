#include "header.hpp"

bool checkDate(int *date) {
	if ((sizeof(*date)/sizeof(int)) != 5) {
		cout << "Invalid time format, please enter the date and time using the format. (YYYY/MM/DD hh:mm) \n" << endl;
		return 1;
	}
	else if ((date[0] < 1970 ) || (date[1] < 1 && date[1]>12) || (date[2] < 1 && date[2]>31) && (date[3] < -1 && date[3]>23) || (date[4] < -1 && date[4]>59)) {
		cout << "Invalid date and time, please check the value and try again.\n" << endl;
		return 1;
	}
	else
		return 0;
}

bool checkMoney(string money) {
	if (money.compare("income")==0 || (money.compare("outcome")==0)) {
		cout << "Please enter a valid money.\n" << endl;
		return 1;
	}
	else
		return 0;
}

bool checkAmount(int amount) {
	if (amount> 4294967295 || amount<1) {
		cout << "Invalid amount, please make sure"
			<<" the amount consists of only numbers with or without comma "
			<<"(range: 1 ~ 4,294,967,295) \n" << endl;
		return 1;
	}
	else
		return 0;
}

bool checkMemo(string memo) {
	if (memo.length>20 || memo.length<0) {
		cout << "Invalid memo, please try again.\n" << endl;
		return 1;
	}
	else
		return 0;
}

bool checkCategoryNumber(short category_number) {
	if (category_number > sizeof(record.category_number) || category_number<0) {
		cout << "Please enter a valid category number. \n" << endl;
		return 1;
	}
	else
		return 0;
}
