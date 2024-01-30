#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <graphics.h>
#include <time.h>
#include <stdlib.h>
#define WIN_WIDTH 1600
#define WIN_HEIGHT 900
#define DIFFICULTY 4	//难度种类
#define ROW 50	//行数
#define COL 50	//列数
#define MINE 99 //雷

//游戏初始化，加载资源
void GameInitialization();

//刷新窗口，实现对玩家操作的响应
void UpdateWin(int deep[ROW][COL], char face[ROW][COL], int difficulty, int row, int col);

//菜单渲染
void MenuPrint();

//判断用户点击菜单
void UserClickMenu(int* confirmPtr);

//用来初始化深层数组，difficulty用来传难度，不同难度初始化大小不同
void DeepBoardIntial(int deep[ROW][COL], int row, int col);

//用来初始化表面数组，difficulty用来传难度，不同难度初始化大小不同
void FaceBoardIntial(char face[ROW][COL], int row, int col);

//随机放置地雷
void RandomMineGenerate(int deep[ROW][COL], int row, int col, int minesnum);

//检查是否胜利，0为输，1为赢，2为继续
int IsGameWin(int deep[ROW][COL], char face[ROW][COL], int row, int col, int row2, int col2);

//连续揭示，点的是周围没有雷的格子，即数字零，周围就会连续揭示,实现原版操作
//连续揭示，原版的一种操作，连续解释的赋值为 L ，方便实现当玩家探索一个没有雷的空块时，程序应该自动揭示与该空块相邻的所有空块，直到遇到数字（即与雷相邻的块）。这个特性是原版扫雷游戏的关键特点，加快游戏进程
void LinkChange(int deep[ROW][COL], char face[ROW][COL], int i, int j, int row, int col);

//装填数字，计算非雷格子中应该是数字几，来表示周围雷的个数，装填在数组中
void FillinNum(int deep[ROW][COL], int row, int col);

//检查坐标是否有效
int CheckIfValid(int row, int col, int row2, int col2);

//游戏主体
void GameMain(int deep[ROW][COL], char face[ROW][COL], int difficulty, int rowrow, int colcol, int minenum);