/* 2154312 ��10 ֣��Զ */
#include <iostream>
#include <conio.h>
#include "hanoi.h"
#include "cmd_console_tools.h"
using namespace std;
/* ----------------------------------------------------------------------------------

	 ���ļ����ܣ�
	1����main����
	2����ʼ����Ļ
	3�����ò˵�������hanoi_menu.cpp�У�������ѡ��
	4������ѡ����ò˵������Ӧ��ִ�к�����hanoi_multiple_solutions.cpp�У�

	 ���ļ�Ҫ��
	1����������ȫ�ֱ��������ⲿȫ�ֺ;�̬ȫ�֣�const��#define�������Ʒ�Χ�ڣ�
	2����̬�ֲ����������������ƣ���ʹ��׼��Ҳ�ǣ����á����á��ܲ��þ�������
	3���������ϵͳͷ�ļ����Զ���ͷ�ļ��������ռ��

   ----------------------------------------------------------------------------------- */

   /***************************************************************************
	 �������ƣ�
	 ��    �ܣ�
	 ���������
	 �� �� ֵ��
	 ˵    ����
   ***************************************************************************/
int main()
{
	/* demo������ִ�д˾䣬��cmd��������Ϊ40��x120�У����������120�У�����9000�У���cmd�����Ҳ���д�ֱ�����ˣ�*/
	cct_setconsoleborder(120, 40, 120, 9000);
	/*�Ĵ�����*/
	cct_setconsoletitle("��ŵ�� - made by ֣��Զ 2154312");

	char src = 0, dst = 0, tmp = 0;
	int mode, floor = 0;

	while(1) {

		mode = zby_menu();									//���ò˵�����

		if (mode == 0)
			break;

		cct_gotoxy(0, 15);

		zby_clear();										//���ʹ�ù������顢����

		if (mode != 5)
			zby_input(&floor, &src, &dst, (mode % 4 == 0));	//����(ģʽ4��8���������ʱ����)

		tmp = 3 * 'B' - src - dst;							//������ת��
			
		if (mode == 4 || mode == 8 || mode == 9) {			//�����ӡ��ʼ������
			cct_cls();
			cct_setcursor(CURSOR_INVISIBLE);
			zby_output_vertical_initialize(src, dst, floor, mode);
		}

		if (mode < 5)
			zby_recur(floor, src, tmp, dst, mode);			//��ʼ�ݹ�
		else{
			cct_setcursor(CURSOR_INVISIBLE);
			zby_visualize(src, dst, floor, mode);
		}

		/*�����˵���ʾ*/
		cct_setcursor(CURSOR_VISIBLE_NORMAL);
		if (mode >=4)
			cct_gotoxy(0, 37);
		cout << "\n���س�������";
		while (_getch() != '\r')
			;
		cct_cls();
	}

	cout << endl;
	return 0;
}
