#include "Positions.h"

#define WIDTH 20        //����
#define HEIGHT 10        //����
#define TRUE 1
#define FALSE 0

Enemy enemy[WIDTH];
Player player;

int hp = 3;

//// �ʱⰪ ////
void init() {
	int i;
	for (i = 0; i < WIDTH; i++)
		enemy[i].con = FALSE;
	//�÷��̾� ��ġ�� �߾�
	player.x = WIDTH / 2;
}

//// ���� ���� ó�� ////
/* �� ���� */
void CreateEnemy() {
	int i;

	for (i = 0; i < WIDTH; i++) {
		//�ش� �ε���[i]�� ���� ������ (FALSE �̸� ����)
		if (!enemy[i].con) {
			//���� (x��) �������� �� ����, ����(y��)�� ���� ��ġ �׻� ��ġ
			enemy[i].x = rand() % WIDTH;
			enemy[i].y = HEIGHT - 1;
			//���� ������ �ε��� [i]�� ���� = TRUE�� ����
			enemy[i].con = TRUE;
			return;
		}
	}
}
/* ���� ������ */
void FallEnemy() {
	int i;
	for (i = 0; i < WIDTH; i++) {
		//�ش� �ε��� [i]�� ���� ������ (TRUE���) ������ ����
		if (enemy[i].con) {
			enemy[i].y--;
		}
	}
}
/* ���ϱ� ������ ��(�ٴڿ� ������ ��) ���� */
void DelEnemy() {
	int i;
	for (i = 0; i < WIDTH; i++) {
		if (enemy[i].con && enemy[i].y < 0)
			enemy[i].con = FALSE;
	}
}
/* �÷��̾ ������ ���� ��� (�й�) */
int DamagedPlayer() {
	int i;
	for (i = 0; i < WIDTH; i++) {
		//���� ���°� TRUE && ���� ��ġ�� y=0 �� �ٴ� && ���� x�� ��ġ = �÷��̾��� x�� ��ġ
		if ((enemy[i].con && enemy[i].y == 0) && (enemy[i].x == player.x)) {
			hp--;
			if (hp == 0)
				return TRUE;
			else
				return FALSE;

		}

	}
	//���� �ʾ����� FALSE ��ȯ
	return FALSE;
}

//// �÷��̾� ó�� ////
/* Ű �ٿ� ó�� */
int isKeyDown(int key) {
	//***GetAsyncKey�� Ű�� ���ȴٸ� �ֻ��� ��Ʈ�� 1�� ����, ������ Ű�� ���ȴٸ� ������ ��Ʈ�� 1�� ����
	//0x8000�� �ֻ��� ��Ʈ -> 16������ 2��Ʈ�� 4�� ���� ��Ʈ -> 0x8000 = 1000 0000 0000 0000�� �ǹ�
	// �� ������ ��Ʈ�� 0x0001 -> 0000 0000 0000 0001
	// ���� (GetAsyncKeyState(key) & 0x8000) != 0 �� ���� Ű�� �����ִٸ� ��(TRUE)
	return ((GetAsyncKeyState(key) & 0x8000) != 0);
}

/* �÷��̾� �̵� (��/��) */
void MovePlayer() {
	//���� ����Ű �Է� ��
	if (isKeyDown(VK_LEFT))
		player.x--;
	if (isKeyDown(VK_RIGHT))
		player.x++;
	//��ġ ���� ����
	if (player.x < 0)
		player.x = 0;
	if (player.x > WIDTH - 1)
		player.x = WIDTH - 1;
}

//// ���� ȭ�� ��� ////
void PrintGame() {
	//��� ȭ�� clear
	system("cls");

	gotoxy(25, 5);
	printf("hp : %d", hp);

	gotoxy((WIDTH / 2) - 7, HEIGHT + 2);
	int i;
	for (i = 0; i < WIDTH; i++) {
		if (enemy[i].con) {
			//�� ��ġ�� ���� ���
			gotoxy(enemy[i].x, HEIGHT - enemy[i].y);
			printf("��");
		}
	}
	//�÷��̾� ���
	gotoxy(player.x, HEIGHT);
	printf("��");

	//�ٴ� ���
	gotoxy(0, HEIGHT + 1);
	for (i = 0; i < WIDTH; i++)
		printf("��");
}


void title() {
	printf("\n\n\n\n\n");
	printf("  ################     #         ##         #          ###########    #\n");
	printf("      #      #         #    ###########     #                   #     #\n");
	printf("      #      #         #        ###         #                  #      #\n");
	printf("  ################     #       #   #        ###               #       #\n");
	printf("                       #        ###         #                #        #\n");
	printf("                       #                    #                         #\n");
	printf("                       #                    #                         #\n");
	gotoxy(11, 16);
	printf("����Ű ��, ��� �����մϴ�");
	gotoxy(7, 17);
	printf("�����  3���̰� @�� ������ ����� ���Դϴ�");
	gotoxy(9, 18);
	printf("������ �����Ϸ��� �ƹ��ų� ��������");
}


//// main �Լ� ////
void main() {
	init();
	time_t start, end;
	double result;
	start = time(NULL); // ���� �ð� ���� ����
	title();
	getch();
	system("cls");
	do {
		//�Ź� ������ ������ �ٸ� ���� �ֱ� ���� �õ尪 ����
		srand((int)malloc(NULL));

		CreateEnemy();
		FallEnemy();
		DelEnemy();
		MovePlayer();

		PrintGame();
		//������ �ӵ� ������ ���� Sleep ����
		Sleep(100);
	} while (!(DamagedPlayer())); //���� ������ �ݺ�

	system("cls");
	end = time(NULL); // �ð� ���� �� 
	result = (double)(end - start); // ��� ��� 
	gotoxy(9, 4);
	printf("GAME OVER");
	gotoxy(7, 5);
	printf("%.0f�� ��Ƽ�̽��ϴ�.", result);

}