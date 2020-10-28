#include "header.hpp"

Conditions::Conditions() {
	this->on_period = false;
	this->on_income = false;
	this->on_memo = false;
	this->on_category = false;
}

struct tm Conditions::get_from_date() {
	struct tm temp;
	temp.tm_year = 0;
	return temp;
}

struct tm Conditions::get_to_date() {
	struct tm temp;
	temp.tm_year = 0;
	return temp;
}

bool Conditions::get_is_income() {
	return false;
}

string Conditions::get_memo_keyword() {
	return " ";
}

int Conditions::get_category_number() {
	return -1;
}

void Conditions::set_period() {

}

void Conditions::set_income() {

}

void Conditions::set_memo() {

}

void Conditions::set_category() {

}

void Conditions::clear_conditions() {

}