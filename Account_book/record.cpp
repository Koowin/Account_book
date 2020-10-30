#include "header.hpp"

Record::Record(struct tm d, bool is, unsigned int am, string me, int ca) {
	date = d;
	is_income = is;
	amount = am;
	memo = me;
	category_number = ca;
}

/* getter */
struct tm Record::get_date() {
	return date;
}

bool Record::get_isincome() {
	return is_income;
}

unsigned int Record::get_amount() {
	return amount;
}

string Record::get_memo() {
	return memo;
}

int Record::get_category_number() {
	return category_number;
}

/* setter */
void Record::set_date(struct tm da) {
	date = da;
}
void Record::set_isIncome(bool is) {
	is_income = is;
}
void Record::set_amount(unsigned int am) {
	amount = am;
}
void Record::set_memo(string me) {
	memo = me;
}
void Record::set_category_number(int ca) {
	category_number = ca;
}