#include "game.h"
#include "data.h"
#include "mywindows.h"
#include <conio.h>

#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")  ///播放音乐头文件

int grade = 0; ///分数
int level = 1; ///等级
int maxgrade = 0;///最高分
int model = 0;///模式控制

BLOCK cur_block;    ///当前方块
BLOCK next_block;   ///下一方块
void windowPrint(int x,int y)
{
    int i,j;
    for(i=0;i<25;i++)
    {
        for(j=0;j<26;j++)
        {
            if(windowShape[i][j] == 1)
            {
                setColor(0xb0);
                setPos(x+j,y+i);///遍历数组的坐标和平面坐标对应
                printf("%2s","");///<==>printf("  ");
            }
        }
    }
}

void printInfo()
{
    setColor(0x0b);
    setPos(32,9);
    printf("操作规则:");
    setPos(32,10);
    printf("按A或a左移");
    setPos(32,11);
    printf("按D或d左移");
    setPos(32,12);
    printf("按S或s下移");
    setPos(32,13);
    printf("按W或w变形");
    setPos(32,14);
    printf("按回车直接下落");
    setPos(32,15);
    printf("按空格暂停");
//    setColor(0x0D);
//    setPos(45,3);
//    printf("     ★★    ★★");
//    setPos(45,4);
//    printf("    ★  ★  ★  ★");
//    setPos(45,5);
//    printf("  ★      ★      ★");
//    setPos(45,6);
//    printf("★                  ★");
//    setPos(45,7);
//    printf("★                  ★");
//    setPos(45,8);
//    printf("  ★              ★");
//    setPos(45,9);
//    printf("    ★          ★");
//    setPos(45,10);
//    printf("      ★      ★");
//    setPos(45,11);
//    printf("        ★  ★");
//    setPos(45,12);
//    printf("          ★");

}

void  printGradeLevel(int num)
{
    switch(num)
    {
        case 0:break;
        case 1:grade += 10 ;break;
        case 2:grade += 30 ;break;
        case 3:grade += 60 ;break;
        case 4:grade += 100 ;break;
    }
//    if(grade <100)
//        level = 1;
//    else if(grade >=100&&grade <=300)
//        level =2;
   changeLevel(grade);///封装改变等级
   setColor(0x0e);
    setPos(32,19);
    printf("等级：%d",level);
    setPos(32,20);
    printf("得分：%d",grade);
    setPos(32,21);
//    maxgrade = maxgrade?grade:maxgrade>grade;
    if(grade>maxgrade)
        maxgrade = grade;
    else
        maxgrade+=0;
    printf("最高得分：%d",maxgrade);
    ///添加其他属性处
}



void printCheat()
{
    setColor(0x0b);
    setPos(1,3);
    printf("■■■■■■■■■■■■■\n");
    printf("  ■                      ■\n");
    printf("  ■                      ■\n");
    printf("  ■                      ■\n");
    printf("  ■■■■■■■■■■■■■");
    setPos(2,4);
    printf("改变方块形状：Q q");
    setPos(2,5);
    printf("改变方块颜色：E e");
    setPos(2,6);
    printf("改变分数等级速度：T t");

}
void  gameTime(clock_t start_time)
{
    setColor(0x0b);
    setPos(2,2);
    printf("游戏已运行的时间：%ld  s",(clock()-start_time)/CLOCKS_PER_SEC);
}

void printBlock(int x,int y,int shape,int status,int color)
{
    int i,j;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            if(block[shape][status][i][j] == 1)
            {
                setColor(color);
                setPos(x+j,y+i);
                printf("■");
            }
        }
    }
}

void deleteBlock(int x,int y,int shape,int status)
{
    int i,j;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            if(block[shape][status][i][j] == 1)
            {
                setPos(x+j,y+i);
                printf("  ");///两个空格
            }
        }
    }
}




//void startBlock()
//{
//    ///第一个方块：形状/形态/颜色=>随机  位置(x,y)>固定
//    ///初始化cur_block
//    srand((unsigned)time(NULL));///用时间(不会重复)设置随机数种子
//    cur_block.x = 22;
//    cur_block.y = 1;
//    cur_block.shape = rand()%7;
//    cur_block.status = rand()%4;
//    cur_block.color = rand()%0x10;
//    if(cur_block.color == 0x00)///如果随机产生的颜色是黑色，不可见，把颜色设置成白色
//    {
//        cur_block.color == 0x0f;
//    }
//    printBlock(cur_block.x,cur_block.y,cur_block.shape,cur_block.status,cur_block.color);
//}
//
//
//
//void nextBlock()
//{
//    ///下一个方块：形状/形态/颜色=>随机  位置(x,y)>固定的
//    ///初始化next_block值
//    deleteBlock(next_block.x,next_block.y,next_block.shape,next_block.status);
//    next_block.x = 34;
//    next_block.y = 2;
//    next_block.shape = rand()%7;
//    next_block.status = rand()%4;
//    next_block.color = rand()%0x10;
//    if(next_block.color == 0x00)
//    {
//        next_block.color == 0x0f;
//    }
//    printBlock(next_block.x,next_block.y,next_block.shape,next_block.status,next_block.color);
//}


void startBlock()
{
    ///第一个方块:形状/形态/颜色->随机 位置(x,y)固定的
    ///初始化cur_block
    ///设置随机数种子(时间永远不一样)
    srand((unsigned)time(NULL));
    cur_block.x = 22;
    cur_block.y = 1;
    cur_block.shape = rand()%7;
    cur_block.status = rand()%4;
    cur_block.color = rand()%0x10;  ///0x00-0x0f
    ///如果随机产生的颜色是黑色,把颜色设置成白色
    if(cur_block.color == 0x00)
    {
        cur_block.color = 0x0f;
    }
    printBlock(cur_block.x,cur_block.y,cur_block.shape,
               cur_block.status,cur_block.color);
}

void nextBlock()
{
    ///形状/形态/颜色->随机,位置->固定的
    ///初始化next_block值
    deleteBlock(next_block.x,next_block.y,
                next_block.shape,next_block.status);
    next_block.x = 34;
    next_block.y = 2;
    next_block.shape = rand()%7;
    next_block.status = rand()%4;
    next_block.color = rand()%0x10;
    if(next_block.color == 0x00)
    {
        next_block.color = 0x0f;
    }
    printBlock(next_block.x,next_block.y,next_block.shape,
               next_block.status,next_block.color);
}

void copyBlock()
{
    ///当前方块+下一方块，并产生新的"下一方块"
    cur_block = next_block;
    cur_block.x= 22;
    cur_block.y = 1;
    printBlock(cur_block.x,cur_block.y,cur_block.shape,cur_block.status,cur_block.color);
    nextBlock();
}




//int downBlock()
//{
//    if(crash(cur_block.x,cur_block.y+1,cur_block.shape,cur_block.status == -1))
//    {
//        ///方块落到游戏池底部
//        ///产生新的方块：下一个方块=>当前放快，重新产生下一方块
//        copyBlock();
//    }
//    ///原理：删除正在显示的方块，纵坐标+1，重新打印
//    deleteBlock(cur_block.x,cur_block.y,cur_block.shape,cur_block.status);
//    cur_block.y += 1;
//    printBlock(cur_block.x,cur_block.y,cur_block.shape,cur_block.status,cur_block.color);
//    return 0;
//}



int downBlock()
{
    ///原理:删除正在显示的方块,纵坐标+1,重新打印
    if(crash(cur_block.x,cur_block.y+1,cur_block.shape,cur_block.status) == -1)
    {
        ///发生碰撞:方块落底游戏池底部
        ///产生新的方块:下一个方块值->当前正在下落的方块,重新产生下一个方块
        ///保存方块->检测消行->打印游戏池->产生新方块
        save();
        lineClear();
        updataGame();
        copyBlock();
        return -1;
    }
    else if(crash(cur_block.x,cur_block.y+1,cur_block.shape,cur_block.status) == -2)
    {
        ///游戏结束
        return -2;
    }
    else
    {
        deleteBlock(cur_block.x,cur_block.y,
                cur_block.shape, cur_block.status);
    cur_block.y += 1;
    printBlock(cur_block.x,cur_block.y,cur_block.shape,
               cur_block.status,cur_block.color);
    return 0;
    }

}



void leftBlock()
{
    if(crash(cur_block.x-1,cur_block.y,cur_block.shape,cur_block.status) == -1)
    {
        return;///发生碰撞，直接返回空
    }
    ///原理：删除正在显示的方块，横坐标-1，重新打印
    deleteBlock(cur_block.x,cur_block.y,cur_block.shape,cur_block.status);
    cur_block.x -= 1;
    printBlock(cur_block.x,cur_block.y,cur_block.shape,cur_block.status,cur_block.color);
}


void rightBlock()
{
    if(crash(cur_block.x+1,cur_block.y,cur_block.shape,cur_block.status) == -1)
    {
        return;///发生碰撞，直接返回空
    }
    ///原理：删除正在显示的方块，横坐标+1，重新打印
    deleteBlock(cur_block.x,cur_block.y,cur_block.shape,cur_block.status);
    cur_block.x += 1;
    printBlock(cur_block.x,cur_block.y,cur_block.shape,cur_block.status,cur_block.color);
}



void tranBlock()
{
    if(crash(cur_block.x,cur_block.y,cur_block.shape,(cur_block.status+1)%4) == -1)
    {
        return;
    }
    ///原理：删除正在显示的方块，输出变形后的方块
    deleteBlock(cur_block.x,cur_block.y,cur_block.shape,cur_block.status);
    switch(cur_block.status)///<=> cur_block.status = (cur_block.status+1)%4;
    {
    case 0:
    case 1:
    case 2:
    cur_block.status++;break;
    case 3:
    cur_block.status -=3;break;
    }
     printBlock(cur_block.x,cur_block.y,cur_block.shape,cur_block.status,cur_block.color);
}


void tranShape()
{
    if(crash(cur_block.x,cur_block.y,(cur_block.shape+1)%7,cur_block.status)== -1)
    {
        return;
    }
    ///原理：删除正在显示的方块，输出改变后的方块
    deleteBlock(cur_block.x,cur_block.y,cur_block.shape,cur_block.status);
    switch(cur_block.shape)
    {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    cur_block.shape++;break;
    case 6:
    cur_block.shape-=6;break;
    }
     printBlock(cur_block.x,cur_block.y,cur_block.shape,cur_block.status,cur_block.color);
}

void tranColor()
{
    deleteBlock(cur_block.x,cur_block.y,cur_block.shape,cur_block.status);
    cur_block.color = rand()%0x10;  ///0x00-0x0f
    ///如果随机产生的颜色是黑色,把颜色设置成白色
    if(cur_block.color == 0x00)
    {
        cur_block.color = 0x0f;
    }
    printBlock(cur_block.x,cur_block.y,cur_block.shape,
               cur_block.status,cur_block.color);
}

void changeLevel(int grade)
{
    if(grade <100)
        level =1;
    else if(grade >=100&&grade <=300)
        level =2;
    else if(grade >=300&&grade <=500)
        level =3;
    else if(grade >=500&&grade <=700)
        level =4;
    else if(grade >=700&&grade <=900)
        level =5;
    else if(grade >=1000)
        level =6;
}


void changeGrade()
{
    grade +=100;
    changeLevel(grade);///封装改变等级
    setColor(0x0e);
    setPos(32,19);
    printf("等级：%d",level);
    setPos(32,20);
    printf("得分：%d",grade);
}
int crash(int x,int y,int shape,int status)
{
    int i,j;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            if(block[shape][status][i][j] == 1)
            {
                if(windowShape[i+y][j+x-15] == 1)
                {
                    ///发生碰撞
                    if(cur_block.x == 22 && cur_block.y == 1)
                    {
                        ///游戏结束
                        return -2;
                    }
                    return -1;///方块落到游戏池底部
                }
            }
        }
    }
    return 0;
}


void save()
{
        ///根据方块在界面上的坐标对应到游戏池的下标的对应位置
        ///将方块为1的保存到数组
        int i,j;
        for(i=0;i<4;i++)
        {
            for(j=0;j<4;j++)
            {
                if(block[cur_block.shape][cur_block.status][i][j] == 1)
                {
                    windowShape[i+cur_block.y][j+cur_block.x-15] = 1;
                }
            }
        }


}



void updataGame()
{
///刷新游戏池
    int i,j;
    for(i=23;i>0;i--)
    {
        for(j=1;j<15;j++)
        {
            if(windowShape[i][j] == 1)
            {
            setColor(0x0f);
//            if(model == 1)///隐形模式
//            setColor(0x00);
            setPos(15+j,i);
            printf("■");
            }else{
            setColor(0x00);
            setPos(15+j,i);
            printf("  ");///两个空格<=>printf("%2s","");
            }

        }
    }
}








void pause()
{
  while(1)
  {
      if(getch() == 32)
      {
          break;
      }
  }
}




void bottomBlock(time3,time4)
{
        for(;crash(cur_block.x,cur_block.y+1,cur_block.shape,cur_block.status) != -1;)
        {
            if(time4-time3>0.01*CLOCKS_PER_SEC)
        {
            downBlock();
            time3 += 1;
            time4 += 1;
        }
        }

}

void downerBlock()
{
    while(1)
    {
        if(crash(cur_block.x,cur_block.y+1,cur_block.shape,cur_block.status) == -1)
        {
            save();
            lineClear();
            updataGame();
            copyBlock();
            return;
        }else if(crash(cur_block.x,cur_block.y+1,cur_block.shape,cur_block.status) == -2)
        {
            ///游戏结束
            return;
        }else
        {
            ++cur_block.y;
        }
    }
}




void lineClear()
{
    ///遍历windowShap,判断是否有满行，这行所有值加起来是14
    int i,j,number = 0;
    for(i=23;i>0;i--)
    {
        int total = 0;
        for(j=1;j<15;j++)
        {
            total += windowShape[i][j];
        }
        if(14 == total)
        {
            lineDown(i);
            i += 1;
            number++;///统计一次消几行
        }
    }
   printGradeLevel(number);
}


void lineDown(int line)
{
    ///重第line行开始，i = i-1
    int i,j;
    for(i=line;i>1;i--) ///i>1,保证边界不下移

    {
        for(j=1;j<15;j++)
        {
            windowShape[i][j] = windowShape[i-1][j];
        }
    }
}


void printOver()
{
   int i,j;
   for(i=23;i>0;i--)
   {
       for(j=1;j<15;j++)
       {
           setColor(0xbf);
           setPos(15+j,i);
           printf("※");
           Sleep(5);
       }
   }
}


void printFinish()
{
    setColor(0x0d);
    setPos(20,8);
    printf("游戏结束！");
    setPos(17,9);
    printf("按Y重新开始");
    setPos(24,9);
    printf("按N结束游戏");

    switch(getch())///检测用户按键
    {

        case 'Y':
        case 'y':
        againGame();break;
        case 'N':
        case 'n':
        mciSendString(TEXT("stop a"), NULL, 0, NULL);
        break;
        default:
        printFinish();break;

    }
}

void againGame()
{
    ///重置分数等级游戏池数据
    level = 1;
    grade = 0;

    int i,j;
    for(i=1;i<24;i++)
    {
        for(j=1;j<15;j++)
        {
            windowShape[i][j] = 0;
        }
    }
    system("cls");///清屏
    gameInit();
}


void printStart(int x,int y)
{
    int color = rand()%0x10;
    if(color == 0x00)
    {
        color = 0x0f;
    }
    ///绘制图案
    setColor(color);
    setPos(x,y);
    printf("■■■■■  ■■■■■  ■■■■■  ■■■■    ■■■    ■■■■");
    setPos(x,y+1);
    printf("    ■      ■              ■      ■     ■     ■    ■");
    setPos(x,y+2);
    printf("    ■      ■■■■        ■      ■■■■      ■      ■■■");
    setPos(x,y+3);
    printf("    ■      ■              ■      ■     ■     ■            ■");
    setPos(x,y+4);
    printf("    ■      ■■■■■      ■      ■      ■  ■■■  ■■■■");
    setPos(25,15);
    printf("按任意J键开始游戏！");

}


void deleteStart(int x,int y)
{
    int i,j;
    for(i=y;i<=y+4;i++)
    {
        for(j=x;j<=x+33;j++)
        {

            setPos(j,i);
            printf("%2s","");
        }
    }
}


void printAnimation()
{
    clock_t time1,time2;
    time1 = clock();
    int x = 5;
    printStart(x,5);
    while(1)
    {
        time2 = clock();
        if(time2-time1>300)     ///时间间隔300ms
        {
            time1 = time2;
            deleteStart(x,5);
            printStart(++x,5);
            if(25 == x)
            {
                deleteStart(x,5);
                x=5;
            }
        }
    ///按任意键退出
       if(kbhit())
    {
        break;
    }
    }
    system("cls");
}
void closeMusic()
{
    mciSendString(TEXT("stop a"),NULL,0,NULL);
}
void openMusic()
{
    mciSendString(TEXT("play a"),NULL,0,NULL);

}
void gameInit()
{
    initHandle();
    ///打开音乐
    mciSendString("open E:\\codeblocks\\workfile\\Tetris\\bin\\Debug\\res\\俄罗斯方块游戏背景音乐.mp3 alias a",NULL,0,NULL);

    ///播放音乐
    mciSendString(TEXT("play a"),NULL,0,NULL);

    ///开始动画
    printAnimation();
    printInfo();
    printGradeLevel(0);
    clock_t startTime =clock();///游戏开始时间

    ///定时器
    clock_t time1,time2;
    time1 = clock();



    setPos(0,0);
/// printf("■■■\n");
/// printf("    ■");
    /**int block [2][3]= {{1,1,1,1},{0,0,1}};//J
    int i,j;
    for(i=0;i<2;i++)
    {
        for(j=0;j<3;j++)
        {
            if(block[i][j] == 1)
            {
                printf("■");}
                else{printf("  ");}

        }
        printf("\n");
    }**/
    windowPrint(15,0);

    ///测试-------------
    ///printBlock(22,1,2,1,0x0d);
    ///deleteBlock(22,1,2,1);
    ///测试-------------


    startBlock();
    nextBlock();
    while(1){
        ///检查是否有按键按下
        if(kbhit())
        {
            switch(getch())
            {
                ///方块变形
            case 'W':
            case 'w':
            case 72:///↑
                tranBlock();break;
            case 'A':
            case 'a':
            case 75:///←
                leftBlock();break;
            case 'D':
            case 'd':
            case 77:///→
                rightBlock();break;
            case 'S':
            case 's':
            case 80:///↓
                downBlock();break;
            case 13:///回车
                downerBlock();break;
            case 32:///空格 暂停
                pause();break;
            case 'Q':
            case 'q':///修改方块
                tranShape();break;
            case 'E':
            case 'e':///修改方块颜色
                tranColor();break;
            case 'T':
            case 't':///修改分数和等级
                changeGrade();break;
            case 'C':
            case 'c':///显示作弊信息
                printCheat();break;
            case 'O':
            case 'o':///关闭音乐
                closeMusic();break;
            case 'I':
            case 'i':///打开音乐
                openMusic();break;
//            case 1:///模式调节
//                model++;break;
//            case 2:///模式调节
//                model--;break;
            }
        }
        time2 = clock();
        ///每0.5s下落一次
        if(time2-time1>0.5*CLOCKS_PER_SEC/level)
        {
            gameTime(startTime);
            if(downBlock() == -2)
                break;
            time1 = time2;
        }
    }
        printOver();
        printFinish();

}
