#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <graphics.h>
#include <time.h>
#include <stdlib.h>
#define WIN_WIDTH 1600
#define WIN_HEIGHT 900
#define DIFFICULTY 4	//�Ѷ�����
#define ROW 50	//����
#define COL 50	//����
#define MINE 99 //��

//��Ϸ��ʼ����������Դ
void GameInitialization();

//ˢ�´��ڣ�ʵ�ֶ���Ҳ�������Ӧ
void UpdateWin(int deep[ROW][COL], char face[ROW][COL], int difficulty, int row, int col);

//�˵���Ⱦ
void MenuPrint();

//�ж��û�����˵�
void UserClickMenu(int* confirmPtr);

//������ʼ��������飬difficulty�������Ѷȣ���ͬ�Ѷȳ�ʼ����С��ͬ
void DeepBoardIntial(int deep[ROW][COL], int row, int col);

//������ʼ���������飬difficulty�������Ѷȣ���ͬ�Ѷȳ�ʼ����С��ͬ
void FaceBoardIntial(char face[ROW][COL], int row, int col);

//������õ���
void RandomMineGenerate(int deep[ROW][COL], int row, int col, int minesnum);

//����Ƿ�ʤ����0Ϊ�䣬1ΪӮ��2Ϊ����
int IsGameWin(int deep[ROW][COL], char face[ROW][COL], int row, int col, int row2, int col2);

//������ʾ���������Χû���׵ĸ��ӣ��������㣬��Χ�ͻ�������ʾ,ʵ��ԭ�����
//������ʾ��ԭ���һ�ֲ������������͵ĸ�ֵΪ L ������ʵ�ֵ����̽��һ��û���׵Ŀտ�ʱ������Ӧ���Զ���ʾ��ÿտ����ڵ����пտ飬ֱ���������֣����������ڵĿ飩�����������ԭ��ɨ����Ϸ�Ĺؼ��ص㣬�ӿ���Ϸ����
void LinkChange(int deep[ROW][COL], char face[ROW][COL], int i, int j, int row, int col);

//װ�����֣�������׸�����Ӧ�������ּ�������ʾ��Χ�׵ĸ�����װ����������
void FillinNum(int deep[ROW][COL], int row, int col);

//��������Ƿ���Ч
int CheckIfValid(int row, int col, int row2, int col2);

//��Ϸ����
void GameMain(int deep[ROW][COL], char face[ROW][COL], int difficulty, int rowrow, int colcol, int minenum);