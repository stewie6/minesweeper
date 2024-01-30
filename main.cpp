#include "game.h"

int main()
{
	int deep[ROW][COL];//深层，用来记录布置好的地雷和数字，及埋藏在下层的内容
	char face[ROW][COL];//表面，用来打印和记录玩家操作，表层，对玩家操作进行记录
	GameInitialization();//初始化
	int confirm = 0;//确认关卡，1为简单，2为中等，3为大师，以此类推
	do
	{
		confirm = 0;
		UserClickMenu(&confirm);//通过获取玩家点击的坐标确定关卡或退出游戏
		switch (confirm)
		{
		case 0:
			break;//当confirm为0时则退出游戏
		case 1:
			GameMain(deep, face, 0, 9, 9, 10);//简单难度，地块9 * 9，10个雷
			break;
		case 2:
			GameMain(deep, face, 1, 16, 16, 40);//中等难度，地块16 * 16，40个雷
			break;
		case 3:
			GameMain(deep, face, 2, 16, 25, 60);//简单难度，地块16 * 25，60个雷
			break;
		case 4:
			GameMain(deep, face, 3, 20, 44, 132);//简单难度，地块20 * 44，132个雷
			break;
		default:
			printf("ERROR!");
			break;
		}
	}while (confirm);//当confirm为0时则退出游戏
	return 0;
}