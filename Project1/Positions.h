#pragma once
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include <Windows.h>

typedef struct Enemy {
	int x;
	int y;
	//���� ���� (TRUE, FALSE)�� ��Ʈ���� ��
	int con;
}Enemy;
//�÷��̾�
typedef struct Player {
	int x;
}Player;

//������ ��ġ�� Ŀ���� �̵���Ű�� �Լ�
void gotoxy(int x, int y) {
	//COORD : window.h�� �ִ� ����ü, {SHORT x, SHORT y} �� �����Ǿ� �ִ�.
	COORD pos = { x * 2, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


