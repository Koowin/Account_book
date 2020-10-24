#pragma once
#include <iostream>
#include <ctime>
#include <list>
#include <string>
#include <conio.h>

using namespace std;

class Record {
public:
	struct tm date;
	bool is_income;
	unsigned int amount;
	string memo;
	short category_number;		//필요에 따라 char, short, int 선택 (변경 시 헤더파일 아래 함수 선언 및 cpp에서도 변경해주세요)
};

/* file manage 함수 */
bool initFiles(void);		//return: 성공/실패
bool saveFiles(void);		//return: 성공/실패

/* string->other 파싱 및 검사 함수 */
struct tm checkDate(string);		//return: 성공 시 string -> tm값 / 실패 시 정해주세요
unsigned int checkAmount(string);	//return: 성공 시 string -> unsigned int값 / 실패 시 정해주세요 (필요에 따라 기획서 수정 가능)
string checkMemo(string);			//return: 성공 시 그대로 / 실패 시 정해주세요.
short checkCategoryNumber(string);	//return: string->short / 실패 시 정해주세요.

/* recordManage 함수 */
void addRecord(void);			//필요에 따라 입출력 자료형 변경
void printAllRecord(void);		//필요에 따라 입출력 자료형 변경
//기록 검색 부분은 신이님이 만드신대로 여기에 추가해주세요
void modifyRecord(void);		//필요에 따라 입출력 자료형 변경
void deleteRecord(void);		//필요에 따라 입출력 자료형 변경

/* categoryManage 함수 */
void printCategoryList(list <string>);
bool addCategoryList(list <string> *);			//실패 시 True 반환
bool modifyCategory(list <string> *);				//실패 시 True 반환
bool deleteCategory(list <string> *,list <class Record> *);		//실패 시 True 반환