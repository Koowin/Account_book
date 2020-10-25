#include <ConsoleView.h>

ConsoleView::ConsoleView() {



}


void ConsoleView::gotoxy(short x, short y) {

	COORD Pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);

}

void ConsoleView::showUI() { // �޴� ����Ŭ ���
	bool exit = false; // ���α׷� ���� ����
	while (1) {
		switch (page) {
		/*case 0: // �ʱ�ȭ�� & ī�װ� ���� & īƮ ���� & ����
			page = userUI0();
			break;*/
		case 1: // �������� ���� �Է�
			page = userUI1();
			break;
		case 2: // ��ü ��� ����
			page = userUI2();
			break;
		case 3: // �˻�/ ����/ ���� �޴� 
			page = userUI3();
			break;
		case 4: // ī�װ� ���� �޴�
			page = userUI4();
			break;
		case 5: // ����
			page = userUI5();
			break;
		
		case -1: // ����
			exit = true;
			break;
		}
		if (exit == true) break;
	}
	cout << "���α׷��� ����Ǿ����ϴ�.\n\n" << endl;
}
