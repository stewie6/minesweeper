#include "game.h"

int main()
{
	int deep[ROW][COL];//��㣬������¼���úõĵ��׺����֣���������²������
	char face[ROW][COL];//���棬������ӡ�ͼ�¼��Ҳ�������㣬����Ҳ������м�¼
	GameInitialization();//��ʼ��
	int confirm = 0;//ȷ�Ϲؿ���1Ϊ�򵥣�2Ϊ�еȣ�3Ϊ��ʦ���Դ�����
	do
	{
		confirm = 0;
		UserClickMenu(&confirm);//ͨ����ȡ��ҵ��������ȷ���ؿ����˳���Ϸ
		switch (confirm)
		{
		case 0:
			break;//��confirmΪ0ʱ���˳���Ϸ
		case 1:
			GameMain(deep, face, 0, 9, 9, 10);//���Ѷȣ��ؿ�9 * 9��10����
			break;
		case 2:
			GameMain(deep, face, 1, 16, 16, 40);//�е��Ѷȣ��ؿ�16 * 16��40����
			break;
		case 3:
			GameMain(deep, face, 2, 16, 25, 60);//���Ѷȣ��ؿ�16 * 25��60����
			break;
		case 4:
			GameMain(deep, face, 3, 20, 44, 132);//���Ѷȣ��ؿ�20 * 44��132����
			break;
		default:
			printf("ERROR!");
			break;
		}
	}while (confirm);//��confirmΪ0ʱ���˳���Ϸ
	return 0;
}