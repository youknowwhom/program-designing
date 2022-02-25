/* 2154312 信10 郑博远 */
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <windows.h>
#include <cmath>
#include "hanoi.h"
#include "cmd_console_tools.h"
using namespace std;

/* ----------------------------------------------------------------------------------

	 本文件功能：
	1、存放被 hanoi_main.cpp 中根据菜单返回值调用的各菜单项对应的执行函数

	 本文件要求：
	1、不允许定义外部全局变量（const及#define不在限制范围内）
	2、允许定义静态全局变量（具体需要的数量不要超过文档显示，全局变量的使用准则是：少用、慎用、能不用尽量不用）
	3、静态局部变量的数量不限制，但使用准则也是：少用、慎用、能不用尽量不用
	4、按需加入系统头文件、自定义头文件、命名空间等

   ----------------------------------------------------------------------------------- */


   /*该cpp内定义的全局变量*/
int steps = 0;											//记录总步数
int speed;												//记录延时
int top[3] = { 0 }, tower[3][MAX_plates] = { {0} };     //记录每柱盘数 / 每柱盘号


/***************************************************************************
	函数名称：zby_intput
	功    能：进行菜单中多项的合并输入
	输入参数：
	返 回 值：
	说    明：
***************************************************************************/
void zby_input(int* floor, char* from, char* to, bool opt_speed)
{
	int i;

	while (1) {
		cout << "请输入汉诺塔的层数(1-" << MAX_plates << ")：" << endl;
		cin >> *floor;
		if (*floor >= 1 && *floor <= MAX_plates && cin.good())
			break;
		cin.clear();
		cin.ignore(65536, '\n');
	}
	cin.ignore(65536, '\n');

	while (1) {
		cout << "请输入起始柱(A-C)：" << endl;
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
		cout << "请输入目标柱(A-C)：" << endl;
		cin >> *to;
		if (cin.good() && ((*to >= 'A' && *to <= 'C') || (*to >= 'a' && *to <= 'c'))
			&& *from != *to && *from != *to + 'a' - 'A' && *from != *to - 'a' + 'A')
			break;
		if (*from == *to || *from == *to + 'a' - 'A' || *from == *to - 'a' + 'A')
			cout << "目标柱(" << *from << ")不能与起始柱(" << *from << ")相同" << endl;
		cin.clear();
		cin.ignore(65536, '\n');
	}
	cin.ignore(65536, '\n');

	if (*to >= 'a')
		*to = *to - 'a' + 'A';

	/*初始化三根柱子*/
	for (i = 0; i <= *floor - 1; i++) {
		tower[*from - 'A'][i] = *floor - i;
	}
	top[*from - 'A'] = *floor;

	while (opt_speed) {
		cout << "请输入移动速度(0-5: 0-按回车单步演示 1-延时最长 5-延时最短)" << endl;
		cin >> speed;
		if (cin.good() && speed >= 0 && speed <= 5)
			break;
		cin.clear();
		cin.ignore(65536, '\n');
	}
}

/***************************************************************************
  函数名称：zby_clear
  功    能：清空数组、步数
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void zby_clear()
{
	int i, j;
	steps = 0;									//步数num清零

	for (i = 0; i < 3; i++)						//tower数组清零
		for (j = 0; j < MAX_plates; j++)
			tower[i][j] = 0;

	for (i = 0; i < 3; i++)
		top[i] = 0;								//top数组清零
}

/***************************************************************************
  函数名称：zby_recur
  功    能：递归部分
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void zby_recur(int n, char src, char tmp, char dst, int mode)
{
	if (n != 1)
		zby_recur(n - 1, src, dst, tmp, mode);
	tower[src - 'A'][--top[src - 'A']] = 0;		//移除起始柱顶端盘
	tower[dst - 'A'][top[dst - 'A']++] = n;		//盘移至目标柱顶端
	if (mode < 5 || mode > 7)
		zby_output_horizontal(src, dst, n, mode);			//横向打印数组
	if (mode == 4 || mode == 8 || mode == 9)
		zby_output_vertical_modify(src, dst, mode);			//纵向打印数组
	if (mode == 8)
		zby_moveplate(src, dst, mode);						//打印伪图形
	if (n != 1)
		zby_recur(n - 1, tmp, src, dst, mode);
}


/***************************************************************************
  函数名称：zby_intput
  功    能：进行菜单中多项的合并输入
  输入参数：
  返 回 值：
  说    明：
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
  函数名称：zby_output_horizontal
  功    能：横向打印输出语句
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void zby_output_horizontal(char src, char dst, int n, int mode)
{
	int i, j;

	cct_setcolor();		//调回缺省颜色

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
			cout << "第" << setiosflags(ios::right) << setw(4) << ++steps << "步(" << setw(2) << n << "#: " << src << "-->" << dst << ")";
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
  函数名称：zby_output_vertical_initialize
  功    能：纵向打印数组-初始化
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void zby_output_vertical_initialize(char src, char dst, int n, int mode)
{
	int i, j, mode_dif = 0;			//mode_dif用于记录不同模式纵向数组位置的差异

	switch (mode) {
		case 4:
			mode_dif = 0;
			break;
		case 8:
		case 9:
			mode_dif = 15;
			break;
	}

	/*打印首行*/
	cout << "从 " << src << " 移动到 " << dst << "，共 " << n << " 层，延时设置为 " << speed;

	/*打印横向初始数组状态*/
	cct_gotoxy(0, mode_dif + 17);
	cout << "初始：  ";
	for (i = 0; i < 3; i++) {
		cout << " " << char(i + 'A') << ":";
		for (j = 0; j < 10; j++)
			if (tower[i][j] != 0)
				cout << setiosflags(ios::right) << setw(2) << tower[i][j];
			else
				cout << "  ";
	}

	/*打印纵向初始数字状态*/
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
		zby_sleep();   //延时
}


/***************************************************************************
  函数名称：zby_output_vertical_modify
  功    能：纵向打印数组-单步骤修改
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void zby_output_vertical_modify(char src, char dst, int mode)
{
	cct_setcolor();		//调回缺省颜色
	int mode_dif = 0;	//mode_dif用于记录不同模式纵向数组位置的差异
	switch (mode) {
		case 4:
			mode_dif = 0;
			break;
		case 8:
		case 9:
			mode_dif = 15;
			break;
	}

	/*抹除起始柱顶端盘*/
	cct_gotoxy(10 + (src - 'A') * 10, mode_dif + 11 - top[src - 'A']);
	cout << "  ";

	/*目标柱顶端打印盘*/
	cct_gotoxy(10 + (dst - 'A') * 10, mode_dif + 12 - top[dst - 'A']);
	cout << setw(2) << tower[dst - 'A'][top[dst - 'A'] - 1];

	if (mode != 8 && mode != 9)
		zby_sleep();  //延时
}

/***************************************************************************
  函数名称：zby_drawpillar
  功    能：画柱子
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void zby_drawpillar()
{
	/*打印底盘*/
	cct_showch(1, 15, ' ', COLOR_HYELLOW, COLOR_BLACK, 23);
	Sleep(100);
	cct_showch(33, 15, ' ', COLOR_HYELLOW, COLOR_BLACK, 23);
	Sleep(100);
	cct_showch(65, 15, ' ', COLOR_HYELLOW, COLOR_BLACK, 23);

	/*打印柱子*/
	int i;
	for (i = 1; i <= 12; i++)
	{
		cct_showch(12, 15 - i, ' ', COLOR_HYELLOW, COLOR_BLACK, 1);
		Sleep(20);
		cct_showch(44, 15 - i, ' ', COLOR_HYELLOW, COLOR_BLACK, 1);
		Sleep(20);
		cct_showch(76, 15 - i, ' ', COLOR_HYELLOW, COLOR_BLACK, 1);
	}

	cct_setcolor();			//调回缺省颜色
}

/***************************************************************************
  函数名称：zby_moveplate
  功    能：移盘子
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void zby_moveplate(char src, char dst, int mode)
{
	int color[11] = { 0,COLOR_HRED,COLOR_RED,COLOR_YELLOW,COLOR_HGREEN,COLOR_GREEN,COLOR_CYAN,COLOR_HBLUE,COLOR_BLUE,COLOR_HBLACK,COLOR_WHITE };
	int i;

	if (mode == 7)
		Sleep(500);
	else if (mode == 8 || mode == 9)		 //撤销数组上一步的移动，以便打印该步骤
	{
		tower[src - 'A'][top[src - 'A']++] = tower[dst - 'A'][top[dst - 'A'] - 1];
		tower[dst - 'A'][--top[dst - 'A']] = 0;
	}

	/*上移*/
	for (i = 0; 14 - top[src - 'A'] - i > 0; i++) {
		//打印新的方块
		cct_showch(12 - tower[src - 'A'][top[src - 'A'] - 1] + 32 * (src - 'A'), 14 - top[src - 'A'] - i, ' ', color[tower[src - 'A'][top[src - 'A'] - 1]], COLOR_WHITE, tower[src - 'A'][top[src - 'A'] - 1] * 2 + 1);
		//覆盖原有的方块
		cct_showch(12 - tower[src - 'A'][top[src - 'A'] - 1] + 32 * (src - 'A'), 15 - top[src - 'A'] - i, ' ', COLOR_BLACK, COLOR_WHITE, tower[src - 'A'][top[src - 'A'] - 1] * 2 + 1);
		//复原不该被抹除的柱子
		if (14 - top[src - 'A'] - i >= 2)
			cct_showch(12 + 32 * (src - 'A'), 15 - top[src - 'A'] - i, ' ', COLOR_HYELLOW, COLOR_WHITE, 1);
		speed == 0 ? Sleep(10) : zby_sleep();
	}

	/*左or右移    (差值绝对值/差值)用于区分左右*/
	for (i = 0; fabs(i) <= 32 * fabs(dst - src); i += int(fabs(dst - src) / (dst - src))) {
		//打印新的方块
		cct_showch(12 - tower[src - 'A'][top[src - 'A'] - 1] + 32 * (src - 'A') + i, 1, ' ', color[tower[src - 'A'][top[src - 'A'] - 1]], COLOR_WHITE, tower[src - 'A'][top[src - 'A'] - 1] * 2 + 1);
		//覆盖原有的方块
		cct_showch(12 - tower[src - 'A'][top[src - 'A'] - 1] + 32 * (src - 'A') + i + (dst - src > 0 ? -1 : tower[src - 'A'][top[src - 'A'] - 1] * 2 + 1), 1, ' ', COLOR_BLACK, COLOR_WHITE, 1);
		speed == 0 ? Sleep(10) : zby_sleep();
	}

	/*下移*/
	for (i = 2; i <= 14 - top[dst - 'A']; i++) {
		//打印新的方块
		cct_showch(12 - tower[src - 'A'][top[src - 'A'] - 1] + 32 * (dst - 'A'), i, ' ', color[tower[src - 'A'][top[src - 'A'] - 1]], COLOR_WHITE, tower[src - 'A'][top[src - 'A'] - 1] * 2 + 1);
		//覆盖原有的方块
		cct_showch(12 - tower[src - 'A'][top[src - 'A'] - 1] + 32 * (dst - 'A'), i - 1, ' ', COLOR_BLACK, COLOR_WHITE, tower[src - 'A'][top[src - 'A'] - 1] * 2 + 1);
		//复原不该被抹除的柱子
		if (i > 3)
			cct_showch(12 + 32 * (dst - 'A'), i - 1, ' ', COLOR_HYELLOW, COLOR_WHITE, 1);
		speed == 0 ? Sleep(10) : zby_sleep();
	}

	if (mode == 8 || mode == 9) {		//还原数组上一步的移动，避免破坏数组
		tower[dst - 'A'][top[dst - 'A']++] = tower[src - 'A'][top[src - 'A'] - 1];
		tower[src - 'A'][--top[src - 'A']] = 0;
	}

	cct_setcolor();			//调回缺省颜色

	if (mode == 8)
		zby_sleep();
}

/***************************************************************************
  函数名称：zby_visualize
  功    能：可视化部分具体分支
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void zby_visualize(char src, char dst, int n, int mode)
{
	int color[11] = { 0,COLOR_HRED,COLOR_RED,COLOR_YELLOW,COLOR_HGREEN,COLOR_GREEN,COLOR_CYAN,COLOR_HBLUE,COLOR_BLUE,COLOR_HBLACK,COLOR_WHITE };
	int i, tmp = 3 * 'B' - src - dst;

	if (mode != 8 && mode != 9)
		cct_cls();

	if (mode != 5) {
		cct_gotoxy(0, 0);
		cout << "从 " << src << " 移动到 " << dst << "，共 " << n << " 层";
	}

	zby_drawpillar();			//打印柱子

	if (mode >= 6) {			//打印盘子(mode6-9)
		for (i = 0; i < n; i++) {
			cct_showch(12 + i - n + 32 * (src - 'A'), 14 - i, ' ', color[n - i], COLOR_WHITE, 2 * (n - i) + 1);
			Sleep(20);
		}
	}

	cct_setcolor();				//调回缺省颜色

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
	cct_setcolor();				//调回缺省颜色
}


/***************************************************************************
  函数名称：zby_hanoigame
  功    能：汉诺塔游戏(mode9)
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void zby_hanoigame(char finaldst)
{
	char src, dst, ch;
	int i, good;
	cct_gotoxy(0, 34);
	cout << "请输入移动的柱号(命令形式：AC=A顶端的盘子移动到C，Q=退出) ：";

	while (1) {
		cct_showch(60, 34, ' ', COLOR_BLACK, COLOR_WHITE, 60);			//覆盖原有输入
		cct_setcolor();
		cct_gotoxy(60, 34);
		cct_setcursor(CURSOR_VISIBLE_NORMAL);							//表明输入状态，显示闪动光标

		src = '\0';														//清空src dst 重置good
		dst = '\0';
		good = 1;

		while ((ch = _getch()) == '\b' || ch == ' ')					//忽略空格 / 回车
			;
		src = ch;
		if (src != '\b' && src != '\r' && src != ' ')					//退格or回车or空格不回显
			cout << src;
		if (src == '\r')												//若是回车则直接下一次循环
			continue;

		if ((dst = _getch()) != '\b' && dst != '\r' && dst != ' ')
			cout << dst;

		if (dst == '\r') {
			if (src == 'q' || src == 'Q')								//若是Q+回车 则break 退出游戏
				break;
			else														//若是其他+回车 则直接下一次循环
				continue;
		}

		for (i = 3; i <= 15; i++) {			//每读入15个字符重新读一次
			if ((ch = _getch()) == '\r')	//若是回车则不再继续读入
				break;
			else if (ch != '\b' && ch != ' ') {
				cout << ch;
				if (good && dst == ' ' || dst == '\b')
					dst = ch;
				else
					good = 0;				//若第三个字符及以后还有非退格/空格 则本次输入无效
			}
			else
				i--;						//退格or空格不计入读数
		}

		if (src >= 'a' && src <= 'c')
			src = src - 'a' + 'A';
		if (dst >= 'a' && dst <= 'c')
			dst = dst - 'a' + 'A';

		if ((src == 'q' || src == 'Q') && (dst == '\b' || dst == ' ') && good)				//若是Q+n个空格/回车 退出游戏
			break;
		if (src < 'A' || src>'C' || dst < 'A' || dst>'C' || src == dst || good == 0)		//字母错误 / 两柱相同 / 多个字母   输入无效
			continue;
		/*原柱为空错误处理*/
		else if (tower[src - 'A'][top[src - 'A'] - 1] == 0) {
			cct_setcursor(CURSOR_INVISIBLE);
			cct_gotoxy(0, 36);
			cout << "源柱为空！！！";
			Sleep(1000);
			cct_showch(0, 36, ' ', COLOR_BLACK, COLOR_WHITE, 25);		//覆盖错误提示
			continue;
		}
		/*大盘压小盘错误处理*/
		else if (tower[src - 'A'][top[src - 'A'] - 1] > tower[dst - 'A'][top[dst - 'A'] - 1]
			&& tower[dst - 'A'][top[dst - 'A'] - 1] != 0) {
			cct_setcursor(CURSOR_INVISIBLE);
			cct_gotoxy(0, 36);
			cout << "大盘压小盘，非法移动！";
			Sleep(1000);
			cct_showch(0, 36, ' ', COLOR_BLACK, COLOR_WHITE, 25);		//覆盖错误提示
			continue;
		}

		cct_setcursor(CURSOR_INVISIBLE);								//开始展示动画，隐藏光标

		tower[dst - 'A'][top[dst - 'A']++] = tower[src - 'A'][top[src - 'A'] - 1];		//盘移至目标柱顶端
		tower[src - 'A'][--top[src - 'A']] = 0;											//移除起始柱顶端盘

		zby_output_vertical_modify(src, dst, 9);
		zby_output_horizontal(src, dst, tower[dst - 'A'][top[dst - 'A'] - 1], 9);
		zby_moveplate(src, dst, 9);

		if (zby_hanoigame_checkwin(finaldst))
			break;
	}
	cct_gotoxy(0, 35);
	cout << "游戏结束！！！";
}

/***************************************************************************
  函数名称：zby_hanoigame_checkwin
  功    能：汉诺塔游戏-检查是否通关
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int zby_hanoigame_checkwin(char finaldst)
{
	switch (finaldst) {					//如果剩下两个数组都空了，在遵循规则的前提下即游戏结束
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
	return 0;							//若未空，则游戏未结束
}