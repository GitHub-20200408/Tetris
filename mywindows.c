#include "mywindows.h"//""用于引入自己写的头文件，两者默认检索顺序不同

HANDLE handle;

void initHandle()
{
    handle =GetStdHandle(STD_OUTPUT_HANDLE);
    hideCursor();
}

void  setColor(int color)
{
    SetConsoleTextAttribute(handle ,color);
}

void setPos(int x,int y)
{
    COORD coord ={x*2,y};//控制台上：字母一个字符，汉字两个字符
    SetConsoleCursorPosition(handle,coord);
}

void hideCursor()
{
    CONSOLE_CURSOR_INFO info;//光标类型
    info.bVisible =FALSE;//设置光标不可见
    info.dwSize = 1;//设置光标宽度（1~100）
    SetConsoleCursorInfo(handle,&info);//把属性设置到控制台上
}
