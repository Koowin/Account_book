#include <ConsoleView.h>

ConsoleView::ConsoleView() {



}


void ConsoleView::gotoxy(short x, short y) {

	COORD Pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);

}

void ConsoleView::showUI() { // 메뉴 사이클 담당
	bool exit = false; // 프로그램 종료 여부
	while (1) {
		switch (page) {
		/*case 0: // 초기화면 & 카테고리 선택 & 카트 삭제 & 결제
			page = userUI0();
			break;*/
		case 1: // 수입지출 내역 입력
			page = userUI1();
			break;
		case 2: // 전체 목록 보기
			page = userUI2();
			break;
		case 3: // 검색/ 수정/ 삭제 메뉴 
			page = userUI3();
			break;
		case 4: // 카테고리 관리 메뉴
			page = userUI4();
			break;
		case 5: // 종료
			page = userUI5();
			break;
		
		case -1: // 종료
			exit = true;
			break;
		}
		if (exit == true) break;
	}
	cout << "프로그램이 종료되었습니다.\n\n" << endl;
}
