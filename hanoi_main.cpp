/* 2154312 信10 郑博远 */
#include <iostream>
#include <conio.h>
#include "hanoi.h"
#include "cmd_console_tools.h"
using namespace std;
/* ----------------------------------------------------------------------------------

	 本文件功能：
	1、放main函数
	2、初始化屏幕
	3、调用菜单函数（hanoi_menu.cpp中）并返回选项
	4、根据选项调用菜单各项对应的执行函数（hanoi_multiple_solutions.cpp中）

	 本文件要求：
	1、不允许定义全局变量（含外部全局和静态全局，const及#define不在限制范围内）
	2、静态局部变量的数量不限制，但使用准则也是：少用、慎用、能不用尽量不用
	3、按需加入系统头文件、自定义头文件、命名空间等

   ----------------------------------------------------------------------------------- */

   /***************************************************************************
	 函数名称：
	 功    能：
	 输入参数：
	 返 回 值：
	 说    明：
   ***************************************************************************/
int main()
{
	/* demo中首先执行此句，将cmd窗口设置为40行x120列（缓冲区宽度120列，行数9000行，即cmd窗口右侧带有垂直滚动杆）*/
	cct_setconsoleborder(120, 40, 120, 9000);
	/*改窗口名*/
	cct_setconsoletitle("汉诺塔 - made by 郑博远 2154312");

	char src = 0, dst = 0, tmp = 0;
	int mode, floor = 0;

	while(1) {

		mode = zby_menu();									//调用菜单函数

		if (mode == 0)
			break;

		cct_gotoxy(0, 15);

		zby_clear();										//清空使用过的数组、计数

		if (mode != 5)
			zby_input(&floor, &src, &dst, (mode % 4 == 0));	//输入(模式4与8需多输入延时参数)

		tmp = 3 * 'B' - src - dst;							//计算中转柱
			
		if (mode == 4 || mode == 8 || mode == 9) {			//纵向打印初始化数组
			cct_cls();
			cct_setcursor(CURSOR_INVISIBLE);
			zby_output_vertical_initialize(src, dst, floor, mode);
		}

		if (mode < 5)
			zby_recur(floor, src, tmp, dst, mode);			//开始递归
		else{
			cct_setcursor(CURSOR_INVISIBLE);
			zby_visualize(src, dst, floor, mode);
		}

		/*回主菜单提示*/
		cct_setcursor(CURSOR_VISIBLE_NORMAL);
		if (mode >=4)
			cct_gotoxy(0, 37);
		cout << "\n按回车键继续";
		while (_getch() != '\r')
			;
		cct_cls();
	}

	cout << endl;
	return 0;
}
