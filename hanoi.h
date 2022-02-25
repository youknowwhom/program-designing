/* 2154312 ��10 ֣��Զ */
#pragma once

/* ------------------------------------------------------------------------------------------------------

	 ���ļ����ܣ�
	1��Ϊ�˱�֤ hanoi_main.cpp/hanoi_menu.cpp/hanoi_multiple_solutions.cpp ���໥���ʺ����ĺ�������
	2��һ�����ϵ�cpp���õ��ĺ궨�壨#define����ȫ��ֻ����const����������������
	3�����Բο� cmd_console_tools.h ��д���������Ķ�����ᣩ
   ------------------------------------------------------------------------------------------------------ */

/* ȫ��ֻ��-������� */
const int MAX_plates = 10;

/* �˵����� */
int zby_menu(void);

/* ���㺯�� */
void zby_clear();

/* ��ʱ���� */
void zby_sleep();

/* �ݹ麯�� */
void zby_recur(int n, char src, char tmp, char dst, int mode);

/* ���뺯�� */
void zby_input(int* floor, char* from, char* to, bool opt_speed);

/* ���ݴ�ӡ���� */
void zby_output_horizontal(char src, char dst, int n, int mode);
void zby_output_vertical_modify(char src, char dst, int mode);
void zby_output_vertical_initialize(char src, char dst, int n, int mode);

/*αͼ�ν��溯��*/
void zby_drawpillar();
void zby_visualize(char src, char dst, int n, int mode);
void zby_moveplate(char src, char dst, int mode);
void zby_hanoigame(char finaldst);
int zby_hanoigame_checkwin(char finaldst);