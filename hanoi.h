/* 2154312 信10 郑博远 */
#pragma once

/* ------------------------------------------------------------------------------------------------------

	 本文件功能：
	1、为了保证 hanoi_main.cpp/hanoi_menu.cpp/hanoi_multiple_solutions.cpp 能相互访问函数的函数声明
	2、一个以上的cpp中用到的宏定义（#define）或全局只读（const）变量，个数不限
	3、可以参考 cmd_console_tools.h 的写法（认真阅读并体会）
   ------------------------------------------------------------------------------------------------------ */

/* 全局只读-最大盘数 */
const int MAX_plates = 10;

/* 菜单函数 */
int zby_menu(void);

/* 清零函数 */
void zby_clear();

/* 延时函数 */
void zby_sleep();

/* 递归函数 */
void zby_recur(int n, char src, char tmp, char dst, int mode);

/* 输入函数 */
void zby_input(int* floor, char* from, char* to, bool opt_speed);

/* 横纵打印函数 */
void zby_output_horizontal(char src, char dst, int n, int mode);
void zby_output_vertical_modify(char src, char dst, int mode);
void zby_output_vertical_initialize(char src, char dst, int n, int mode);

/*伪图形界面函数*/
void zby_drawpillar();
void zby_visualize(char src, char dst, int n, int mode);
void zby_moveplate(char src, char dst, int mode);
void zby_hanoigame(char finaldst);
int zby_hanoigame_checkwin(char finaldst);