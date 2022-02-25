/* 2154312 ��10 ֣��Զ */
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <windows.h>
#include <cmath>
#include "hanoi.h"
#include "cmd_console_tools.h"
using namespace std;

/* ----------------------------------------------------------------------------------

	 ���ļ����ܣ�
	1����ű� hanoi_main.cpp �и��ݲ˵�����ֵ���õĸ��˵����Ӧ��ִ�к���

	 ���ļ�Ҫ��
	1�����������ⲿȫ�ֱ�����const��#define�������Ʒ�Χ�ڣ�
	2�������徲̬ȫ�ֱ�����������Ҫ��������Ҫ�����ĵ���ʾ��ȫ�ֱ�����ʹ��׼���ǣ����á����á��ܲ��þ������ã�
	3����̬�ֲ����������������ƣ���ʹ��׼��Ҳ�ǣ����á����á��ܲ��þ�������
	4���������ϵͳͷ�ļ����Զ���ͷ�ļ��������ռ��

   ----------------------------------------------------------------------------------- */


   /*��cpp�ڶ����ȫ�ֱ���*/
int steps = 0;											//��¼�ܲ���
int speed;												//��¼��ʱ
int top[3] = { 0 }, tower[3][MAX_plates] = { {0} };     //��¼ÿ������ / ÿ���̺�


/***************************************************************************
	�������ƣ�zby_intput
	��    �ܣ����в˵��ж���ĺϲ�����
	���������
	�� �� ֵ��
	˵    ����
***************************************************************************/
void zby_input(int* floor, char* from, char* to, bool opt_speed)
{
	int i;

	while (1) {
		cout << "�����뺺ŵ���Ĳ���(1-" << MAX_plates << ")��" << endl;
		cin >> *floor;
		if (*floor >= 1 && *floor <= MAX_plates && cin.good())
			break;
		cin.clear();
		cin.ignore(65536, '\n');
	}
	cin.ignore(65536, '\n');

	while (1) {
		cout << "��������ʼ��(A-C)��" << endl;
		cin >> *from;
		if (cin.good() && ((*from >= 'A' && *from <= 'C') || (*from >= 'a' && *from <= 'c')))
			break;
		cin.clear();
		cin.ignore(65536, '\n');
	}
	cin.ignore(65536, '\n');

	if (*from >= 'a')
		*from = *from - 'a' + 'A';

	while (1) {
		cout << "������Ŀ����(A-C)��" << endl;
		cin >> *to;
		if (cin.good() && ((*to >= 'A' && *to <= 'C') || (*to >= 'a' && *to <= 'c'))
			&& *from != *to && *from != *to + 'a' - 'A' && *from != *to - 'a' + 'A')
			break;
		if (*from == *to || *from == *to + 'a' - 'A' || *from == *to - 'a' + 'A')
			cout << "Ŀ����(" << *from << ")��������ʼ��(" << *from << ")��ͬ" << endl;
		cin.clear();
		cin.ignore(65536, '\n');
	}
	cin.ignore(65536, '\n');

	if (*to >= 'a')
		*to = *to - 'a' + 'A';

	/*��ʼ����������*/
	for (i = 0; i <= *floor - 1; i++) {
		tower[*from - 'A'][i] = *floor - i;
	}
	top[*from - 'A'] = *floor;

	while (opt_speed) {
		cout << "�������ƶ��ٶ�(0-5: 0-���س�������ʾ 1-��ʱ� 5-��ʱ���)" << endl;
		cin >> speed;
		if (cin.good() && speed >= 0 && speed <= 5)
			break;
		cin.clear();
		cin.ignore(65536, '\n');
	}
}

/***************************************************************************
  �������ƣ�zby_clear
  ��    �ܣ�������顢����
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void zby_clear()
{
	int i, j;
	steps = 0;									//����num����

	for (i = 0; i < 3; i++)						//tower��������
		for (j = 0; j < MAX_plates; j++)
			tower[i][j] = 0;

	for (i = 0; i < 3; i++)
		top[i] = 0;								//top��������
}

/***************************************************************************
  �������ƣ�zby_recur
  ��    �ܣ��ݹ鲿��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void zby_recur(int n, char src, char tmp, char dst, int mode)
{
	if (n != 1)
		zby_recur(n - 1, src, dst, tmp, mode);
	tower[src - 'A'][--top[src - 'A']] = 0;		//�Ƴ���ʼ��������
	tower[dst - 'A'][top[dst - 'A']++] = n;		//������Ŀ��������
	if (mode < 5 || mode > 7)
		zby_output_horizontal(src, dst, n, mode);			//�����ӡ����
	if (mode == 4 || mode == 8 || mode == 9)
		zby_output_vertical_modify(src, dst, mode);			//�����ӡ����
	if (mode == 8)
		zby_moveplate(src, dst, mode);						//��ӡαͼ��
	if (n != 1)
		zby_recur(n - 1, tmp, src, dst, mode);
}


/***************************************************************************
  �������ƣ�zby_intput
  ��    �ܣ����в˵��ж���ĺϲ�����
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void zby_sleep()
{
	switch (speed)
	{
		case 0:
			while (_getch() != 13)
				;
			break;
		case 1:
			Sleep(500);
			break;
		case 2:
			Sleep(200);
			break;
		case 3:
			Sleep(50);
			break;
		case 4:
			Sleep(10);
			break;
		case 5:
			break;
	}
}

/***************************************************************************
  �������ƣ�zby_output_horizontal
  ��    �ܣ������ӡ������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void zby_output_horizontal(char src, char dst, int n, int mode)
{
	int i, j;

	cct_setcolor();		//����ȱʡ��ɫ

	switch (mode) {
		case 1:
			cout << n << "# " << src << "-->" << dst << endl;
			break;
		case 2:
			cout << setiosflags(ios::right) << setw(5) << ++steps << ":" << setw(3) << n << "# " << src << "-->" << dst << endl;
			break;
		case 4:
			cct_gotoxy(0, 17);
		case 8:
		case 9:
			cct_gotoxy(0, 32);
		case 3:
			cout << "��" << setiosflags(ios::right) << setw(4) << ++steps << "��(" << setw(2) << n << "#: " << src << "-->" << dst << ")";
			for (i = 0; i < 3; i++) {
				cout << " " << char(i + 'A') << ":";
				for (j = 0; j < 10; j++)
					if (tower[i][j] != 0)
						cout << setiosflags(ios::right) << setw(2) << tower[i][j];
					else
						cout << "  ";
			}
			cout << endl;
			break;
	}
}

/***************************************************************************
  �������ƣ�zby_output_vertical_initialize
  ��    �ܣ������ӡ����-��ʼ��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void zby_output_vertical_initialize(char src, char dst, int n, int mode)
{
	int i, j, mode_dif = 0;			//mode_dif���ڼ�¼��ͬģʽ��������λ�õĲ���

	switch (mode) {
		case 4:
			mode_dif = 0;
			break;
		case 8:
		case 9:
			mode_dif = 15;
			break;
	}

	/*��ӡ����*/
	cout << "�� " << src << " �ƶ��� " << dst << "���� " << n << " �㣬��ʱ����Ϊ " << speed;

	/*��ӡ�����ʼ����״̬*/
	cct_gotoxy(0, mode_dif + 17);
	cout << "��ʼ��  ";
	for (i = 0; i < 3; i++) {
		cout << " " << char(i + 'A') << ":";
		for (j = 0; j < 10; j++)
			if (tower[i][j] != 0)
				cout << setiosflags(ios::right) << setw(2) << tower[i][j];
			else
				cout << "  ";
	}

	/*��ӡ�����ʼ����״̬*/
	cct_gotoxy(9, mode_dif + 12);
	cout << "=========================" << endl;
	cct_gotoxy(11, mode_dif + 13);
	cout << "A         B         C  " << endl;

	i = 0;

	while (i < top[src - 'A']) {
		cct_gotoxy(10 + (src - 'A') * 10, mode_dif + 11 - i);
		cout << setw(2) << tower[src - 'A'][i];
		i++;
	}

	if (mode != 8 && mode != 9)
		zby_sleep();   //��ʱ
}


/***************************************************************************
  �������ƣ�zby_output_vertical_modify
  ��    �ܣ������ӡ����-�������޸�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void zby_output_vertical_modify(char src, char dst, int mode)
{
	cct_setcolor();		//����ȱʡ��ɫ
	int mode_dif = 0;	//mode_dif���ڼ�¼��ͬģʽ��������λ�õĲ���
	switch (mode) {
		case 4:
			mode_dif = 0;
			break;
		case 8:
		case 9:
			mode_dif = 15;
			break;
	}

	/*Ĩ����ʼ��������*/
	cct_gotoxy(10 + (src - 'A') * 10, mode_dif + 11 - top[src - 'A']);
	cout << "  ";

	/*Ŀ�������˴�ӡ��*/
	cct_gotoxy(10 + (dst - 'A') * 10, mode_dif + 12 - top[dst - 'A']);
	cout << setw(2) << tower[dst - 'A'][top[dst - 'A'] - 1];

	if (mode != 8 && mode != 9)
		zby_sleep();  //��ʱ
}

/***************************************************************************
  �������ƣ�zby_drawpillar
  ��    �ܣ�������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void zby_drawpillar()
{
	/*��ӡ����*/
	cct_showch(1, 15, ' ', COLOR_HYELLOW, COLOR_BLACK, 23);
	Sleep(100);
	cct_showch(33, 15, ' ', COLOR_HYELLOW, COLOR_BLACK, 23);
	Sleep(100);
	cct_showch(65, 15, ' ', COLOR_HYELLOW, COLOR_BLACK, 23);

	/*��ӡ����*/
	int i;
	for (i = 1; i <= 12; i++)
	{
		cct_showch(12, 15 - i, ' ', COLOR_HYELLOW, COLOR_BLACK, 1);
		Sleep(20);
		cct_showch(44, 15 - i, ' ', COLOR_HYELLOW, COLOR_BLACK, 1);
		Sleep(20);
		cct_showch(76, 15 - i, ' ', COLOR_HYELLOW, COLOR_BLACK, 1);
	}

	cct_setcolor();			//����ȱʡ��ɫ
}

/***************************************************************************
  �������ƣ�zby_moveplate
  ��    �ܣ�������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void zby_moveplate(char src, char dst, int mode)
{
	int color[11] = { 0,COLOR_HRED,COLOR_RED,COLOR_YELLOW,COLOR_HGREEN,COLOR_GREEN,COLOR_CYAN,COLOR_HBLUE,COLOR_BLUE,COLOR_HBLACK,COLOR_WHITE };
	int i;

	if (mode == 7)
		Sleep(500);
	else if (mode == 8 || mode == 9)		 //����������һ�����ƶ����Ա��ӡ�ò���
	{
		tower[src - 'A'][top[src - 'A']++] = tower[dst - 'A'][top[dst - 'A'] - 1];
		tower[dst - 'A'][--top[dst - 'A']] = 0;
	}

	/*����*/
	for (i = 0; 14 - top[src - 'A'] - i > 0; i++) {
		//��ӡ�µķ���
		cct_showch(12 - tower[src - 'A'][top[src - 'A'] - 1] + 32 * (src - 'A'), 14 - top[src - 'A'] - i, ' ', color[tower[src - 'A'][top[src - 'A'] - 1]], COLOR_WHITE, tower[src - 'A'][top[src - 'A'] - 1] * 2 + 1);
		//����ԭ�еķ���
		cct_showch(12 - tower[src - 'A'][top[src - 'A'] - 1] + 32 * (src - 'A'), 15 - top[src - 'A'] - i, ' ', COLOR_BLACK, COLOR_WHITE, tower[src - 'A'][top[src - 'A'] - 1] * 2 + 1);
		//��ԭ���ñ�Ĩ��������
		if (14 - top[src - 'A'] - i >= 2)
			cct_showch(12 + 32 * (src - 'A'), 15 - top[src - 'A'] - i, ' ', COLOR_HYELLOW, COLOR_WHITE, 1);
		speed == 0 ? Sleep(10) : zby_sleep();
	}

	/*��or����    (��ֵ����ֵ/��ֵ)������������*/
	for (i = 0; fabs(i) <= 32 * fabs(dst - src); i += int(fabs(dst - src) / (dst - src))) {
		//��ӡ�µķ���
		cct_showch(12 - tower[src - 'A'][top[src - 'A'] - 1] + 32 * (src - 'A') + i, 1, ' ', color[tower[src - 'A'][top[src - 'A'] - 1]], COLOR_WHITE, tower[src - 'A'][top[src - 'A'] - 1] * 2 + 1);
		//����ԭ�еķ���
		cct_showch(12 - tower[src - 'A'][top[src - 'A'] - 1] + 32 * (src - 'A') + i + (dst - src > 0 ? -1 : tower[src - 'A'][top[src - 'A'] - 1] * 2 + 1), 1, ' ', COLOR_BLACK, COLOR_WHITE, 1);
		speed == 0 ? Sleep(10) : zby_sleep();
	}

	/*����*/
	for (i = 2; i <= 14 - top[dst - 'A']; i++) {
		//��ӡ�µķ���
		cct_showch(12 - tower[src - 'A'][top[src - 'A'] - 1] + 32 * (dst - 'A'), i, ' ', color[tower[src - 'A'][top[src - 'A'] - 1]], COLOR_WHITE, tower[src - 'A'][top[src - 'A'] - 1] * 2 + 1);
		//����ԭ�еķ���
		cct_showch(12 - tower[src - 'A'][top[src - 'A'] - 1] + 32 * (dst - 'A'), i - 1, ' ', COLOR_BLACK, COLOR_WHITE, tower[src - 'A'][top[src - 'A'] - 1] * 2 + 1);
		//��ԭ���ñ�Ĩ��������
		if (i > 3)
			cct_showch(12 + 32 * (dst - 'A'), i - 1, ' ', COLOR_HYELLOW, COLOR_WHITE, 1);
		speed == 0 ? Sleep(10) : zby_sleep();
	}

	if (mode == 8 || mode == 9) {		//��ԭ������һ�����ƶ��������ƻ�����
		tower[dst - 'A'][top[dst - 'A']++] = tower[src - 'A'][top[src - 'A'] - 1];
		tower[src - 'A'][--top[src - 'A']] = 0;
	}

	cct_setcolor();			//����ȱʡ��ɫ

	if (mode == 8)
		zby_sleep();
}

/***************************************************************************
  �������ƣ�zby_visualize
  ��    �ܣ����ӻ����־����֧
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void zby_visualize(char src, char dst, int n, int mode)
{
	int color[11] = { 0,COLOR_HRED,COLOR_RED,COLOR_YELLOW,COLOR_HGREEN,COLOR_GREEN,COLOR_CYAN,COLOR_HBLUE,COLOR_BLUE,COLOR_HBLACK,COLOR_WHITE };
	int i, tmp = 3 * 'B' - src - dst;

	if (mode != 8 && mode != 9)
		cct_cls();

	if (mode != 5) {
		cct_gotoxy(0, 0);
		cout << "�� " << src << " �ƶ��� " << dst << "���� " << n << " ��";
	}

	zby_drawpillar();			//��ӡ����

	if (mode >= 6) {			//��ӡ����(mode6-9)
		for (i = 0; i < n; i++) {
			cct_showch(12 + i - n + 32 * (src - 'A'), 14 - i, ' ', color[n - i], COLOR_WHITE, 2 * (n - i) + 1);
			Sleep(20);
		}
	}

	cct_setcolor();				//����ȱʡ��ɫ

	if (mode == 7) {
		speed = 4;
		if (n % 2 == 1)
			zby_moveplate(src, dst, mode);
		else
			zby_moveplate(src, tmp, mode);
	}

	if (mode == 8) {
		zby_sleep();
		zby_recur(n, src, tmp, dst, mode);
	}

	if (mode == 9) {
		speed = 5;
		zby_hanoigame(dst);
	}
	cct_setcolor();				//����ȱʡ��ɫ
}


/***************************************************************************
  �������ƣ�zby_hanoigame
  ��    �ܣ���ŵ����Ϸ(mode9)
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void zby_hanoigame(char finaldst)
{
	char src, dst, ch;
	int i, good;
	cct_gotoxy(0, 34);
	cout << "�������ƶ�������(������ʽ��AC=A���˵������ƶ���C��Q=�˳�) ��";

	while (1) {
		cct_showch(60, 34, ' ', COLOR_BLACK, COLOR_WHITE, 60);			//����ԭ������
		cct_setcolor();
		cct_gotoxy(60, 34);
		cct_setcursor(CURSOR_VISIBLE_NORMAL);							//��������״̬����ʾ�������

		src = '\0';														//���src dst ����good
		dst = '\0';
		good = 1;

		while ((ch = _getch()) == '\b' || ch == ' ')					//���Կո� / �س�
			;
		src = ch;
		if (src != '\b' && src != '\r' && src != ' ')					//�˸�or�س�or�ո񲻻���
			cout << src;
		if (src == '\r')												//���ǻس���ֱ����һ��ѭ��
			continue;

		if ((dst = _getch()) != '\b' && dst != '\r' && dst != ' ')
			cout << dst;

		if (dst == '\r') {
			if (src == 'q' || src == 'Q')								//����Q+�س� ��break �˳���Ϸ
				break;
			else														//��������+�س� ��ֱ����һ��ѭ��
				continue;
		}

		for (i = 3; i <= 15; i++) {			//ÿ����15���ַ����¶�һ��
			if ((ch = _getch()) == '\r')	//���ǻس����ټ�������
				break;
			else if (ch != '\b' && ch != ' ') {
				cout << ch;
				if (good && dst == ' ' || dst == '\b')
					dst = ch;
				else
					good = 0;				//���������ַ����Ժ��з��˸�/�ո� �򱾴�������Ч
			}
			else
				i--;						//�˸�or�ո񲻼������
		}

		if (src >= 'a' && src <= 'c')
			src = src - 'a' + 'A';
		if (dst >= 'a' && dst <= 'c')
			dst = dst - 'a' + 'A';

		if ((src == 'q' || src == 'Q') && (dst == '\b' || dst == ' ') && good)				//����Q+n���ո�/�س� �˳���Ϸ
			break;
		if (src < 'A' || src>'C' || dst < 'A' || dst>'C' || src == dst || good == 0)		//��ĸ���� / ������ͬ / �����ĸ   ������Ч
			continue;
		/*ԭ��Ϊ�մ�����*/
		else if (tower[src - 'A'][top[src - 'A'] - 1] == 0) {
			cct_setcursor(CURSOR_INVISIBLE);
			cct_gotoxy(0, 36);
			cout << "Դ��Ϊ�գ�����";
			Sleep(1000);
			cct_showch(0, 36, ' ', COLOR_BLACK, COLOR_WHITE, 25);		//���Ǵ�����ʾ
			continue;
		}
		/*����ѹС�̴�����*/
		else if (tower[src - 'A'][top[src - 'A'] - 1] > tower[dst - 'A'][top[dst - 'A'] - 1]
			&& tower[dst - 'A'][top[dst - 'A'] - 1] != 0) {
			cct_setcursor(CURSOR_INVISIBLE);
			cct_gotoxy(0, 36);
			cout << "����ѹС�̣��Ƿ��ƶ���";
			Sleep(1000);
			cct_showch(0, 36, ' ', COLOR_BLACK, COLOR_WHITE, 25);		//���Ǵ�����ʾ
			continue;
		}

		cct_setcursor(CURSOR_INVISIBLE);								//��ʼչʾ���������ع��

		tower[dst - 'A'][top[dst - 'A']++] = tower[src - 'A'][top[src - 'A'] - 1];		//������Ŀ��������
		tower[src - 'A'][--top[src - 'A']] = 0;											//�Ƴ���ʼ��������

		zby_output_vertical_modify(src, dst, 9);
		zby_output_horizontal(src, dst, tower[dst - 'A'][top[dst - 'A'] - 1], 9);
		zby_moveplate(src, dst, 9);

		if (zby_hanoigame_checkwin(finaldst))
			break;
	}
	cct_gotoxy(0, 35);
	cout << "��Ϸ����������";
}

/***************************************************************************
  �������ƣ�zby_hanoigame_checkwin
  ��    �ܣ���ŵ����Ϸ-����Ƿ�ͨ��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int zby_hanoigame_checkwin(char finaldst)
{
	switch (finaldst) {					//���ʣ���������鶼���ˣ�����ѭ�����ǰ���¼���Ϸ����
		case 'A':
			if (top[1] + top[2] == 0)
				return 1;
		case 'B':
			if (top[0] + top[2] == 0)
				return 1;
		case 'C':
			if (top[0] + top[1] == 0)
				return 1;
	}
	return 0;							//��δ�գ�����Ϸδ����
}