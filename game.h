#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

/**游戏逻辑模块**/

#include <stdio.h>
#include <time.h>


typedef struct{
    int x,y,shape,status,color;
}BLOCK;

void windowPrint(int x,int y);///绘制游戏池边框


void gameInit();///游戏初始化


void printInfo();///打印操作说明和分数


void printCheat();///显示作弊信息


void  printGradeLevel(int num);///打印分数和等级


void gameTime(clock_t star_time);///游戏计时


void printBlock(int x,int y,int shape,int status,int color);///打印方块


void deleteBlock(int x,int y,int shape,int status);///删除方块



void startBlock();///产生游戏的第一个方块



void nextBlock();///产生下一个方块



void copyBlock();///拷贝方块




int downBlock();///方块下移,返回值：标志是否落到游戏池底部



void leftBlock();///方块左移


void rightBlock();///方块右移


void tranBlock();///方块变形


void tranShape();///方块改变


void tranColor();///方块颜色改变


void changeLevel(int grade);///改变难度


void changeGrade();///改变分数



void bottomBlock(int time3,int time4);///方块直接落到游戏池的底部




int crash(int x,int y,int shape,int status);///碰撞检测




void save();///保存方块





void updataGame();///刷新游戏池




void pause();///暂停



void downerBlock();///一直下落



///消行检测
void lineClear();



///消行下移
void lineDown(int line);



///游戏结束动画
void printOver();


///重新开始提示
void printFinish();



///重新开始游戏
void againGame();


///打印开始图案
void printStart(int x,int y);


///清除开始动画
void deleteStart(int x,int y);


///动画效果->定时(边界控制)
void printAnimation();

void closeMusic();///关闭音乐

void openMusic();///打开音乐

#endif // GAME_H_INCLUDED
