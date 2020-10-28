#include "header.hpp"

bool CheckerParser::checkDate(string s) {
	return false;
}

bool CheckerParser::checkAmount(string s) {
	return false;
}

bool CheckerParser::checkMemo(string s) {
	return false;
}

bool CheckerParser::checkCategoryNumber(string s, int n) {
	return false;
}

struct tm CheckerParser::parseDate(string s) {
	struct tm temp;
	temp.tm_year = 0;
	return temp;
}

unsigned int CheckerParser::parseAmount(string s) {
	return -1;
}