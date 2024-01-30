#include "game.h"

IMAGE DeepBackground;//������ײ�����
IMAGE EachDifficultyBackground[DIFFICULTY];//��DIFFICULTY�ָ����Ѷȵı���
IMAGE NumberEmptyBlock[8];//���ֺ����ֵĿշ���
IMAGE DiscoveredEmptyBlock;//̽�����Ŀշ���
IMAGE CoveredBlock;//δ̽���ķ���
IMAGE DifficultyMenu[DIFFICULTY][2];//�˵��е��ѶȰ���
IMAGE RedMineBlock;//��ɫ����
IMAGE BlackMineBlock;//��ɫ����
IMAGE FlagBlock;//����
IMAGE SmilingFaceBlock[2];//Ц��
IMAGE HandsomeFaceBlock[2];//˧��
IMAGE CryingFaceBlock[2];//����
IMAGE BackBlock[2];//���ؼ�
IMAGE ExitBlock[2];//�˳���Ϸ
int MenuClickStatus = 0;//0Ϊδ�����1Ϊ������Ѷȣ�2Ϊ����е��Ѷȣ��Դ�����
int smile = 0;//Ц��״̬������0�ǵ�һ�ţ�1�ǵڶ���
int cry = 0;//����״̬������0�ǲ��ô�ӡ��1�ǵ�һ�ţ�2�ǵڶ���
int handsome = 0;//˧��״̬������0�ǲ��ô�ӡ��1�ǵ�һ�ţ�2�ǵڶ���
int back = 0;//���ؼ�״̬������0Ϊ��һ�ţ�1Ϊ�ڶ���
int exitstatus = 0;

//��ʼ����Ϸ��������Դ
void GameInitialization()
{
	//����ײ������������ڴ�
	loadimage(&DeepBackground, "rsc/background/DeepBackground.png");
	//�����ַ����������·�����ı����д洢
	char name[64];//�ַ����飬����װ��·��
	for (int i = 0; i < DIFFICULTY; i++)//���ز˵��е��ѶȰ���
	{
		for (int j = 0; j < 2; j++)
		{
			sprintf(name, "rsc/menu/%d_Difficulty_%d.png", i + 1, j + 1);//���ν��ѶȰ�����·��д��name��
			loadimage(&DifficultyMenu[i][j], name);//���ν��ѶȰ����������ڴ�
		}
	}
	for(int i = 0;i < DIFFICULTY;i++)//��DIFFICULTY���Ѷȱ������м���
	{
		sprintf(name, "rsc/background/Difficulty_%d.png",i + 1);//���⼸�ֱ�����·��д��name��
		loadimage(&EachDifficultyBackground[i], name);//���������м���
	}
	for (int i = 0; i < 8; i++)//�԰��ִ����ֵĿշ�����м���
	{
		sprintf(name,"rsc/block/%d_block.png", i + 1);//��·��д��name��
		loadimage(&NumberEmptyBlock[i], name);//���ذ��ַ���
	}
	loadimage(&CoveredBlock, "rsc/block/covered_block.png");//����δ̽���ķ���
	loadimage(&DiscoveredEmptyBlock, "rsc/block/empty_block.png");//����̽�����Ŀշ���
	loadimage(&RedMineBlock, "rsc/block/mine_boom_block.png");//���غ챳������
	loadimage(&BlackMineBlock, "rsc/block/mine_appear_block.png");//���غڱ�������
	loadimage(&FlagBlock, "rsc/block/flag_block.png");//���ر��췽��
	loadimage(&SmilingFaceBlock[0], "rsc/block/smilingface_block.png");//���ص����Ц������
	loadimage(&SmilingFaceBlock[1], "rsc/block/smilingface_block_down.png");//���ذ��µ�Ц������
	loadimage(&HandsomeFaceBlock[0], "rsc/block/handsomeface.png");//���ص����˧������
	loadimage(&HandsomeFaceBlock[1], "rsc/block/handsomeface_down.png");//���ذ��µ�˧������
	loadimage(&CryingFaceBlock[0], "rsc/block/cryingface_block.png");//���ص���Ŀ�������
	loadimage(&CryingFaceBlock[1], "rsc/block/cryingface_block_down.png");//���ذ��µĿ�������
	loadimage(&BackBlock[0], "rsc/block/back_block.png");//���ط��ؼ�
	loadimage(&BackBlock[1], "rsc/block/back_block_down.png");//���ط��ؼ�
	loadimage(&ExitBlock[0], "rsc/menu/exit_up.png");//�����˳���Ϸ��
	loadimage(&ExitBlock[1], "rsc/menu/exit_down.png");//�����˳���Ϸ��
	initgraph(WIN_WIDTH, WIN_HEIGHT, 0);//��ʼ������
}

//�˵���Ⱦ
void MenuPrint()
{
	BeginBatchDraw();//��ʼ˫����
	putimage(0, 0, &DeepBackground);//��Ⱦ��ײ�����
	for(int i = 0;i < DIFFICULTY;i++)//������Ⱦ�ѶȰ�����δ���µ�״̬
	{
		putimage(600, 90 + i * 100, &DifficultyMenu[i][0]);
	}
	if(MenuClickStatus)//ֻҪMenuClickStatus��Ϊ��Ϳ��Խ�������Ĳ���
	{
		putimage(600, 90 + (MenuClickStatus - 1) * 100, &DifficultyMenu[MenuClickStatus - 1][1]);//ͨ��MenuClickStatus������Ⱦ��Ӧ����İ��µİ���
	}
	putimage(1100, 90, &ExitBlock[exitstatus]);//��Ⱦ�˳���
	setbkmode(TRANSPARENT);// �������ֱ���Ϊ͸��
	settextcolor(BLACK);// ����������ɫ
	settextstyle(25, 0, _T("����"));//���������С������
	outtextxy(5, 500, _T("���������Խ�ʾ���飬����Ҽ����Ա�־С�죬�ٴ��Ҽ�ȡ�����"));//��������
	outtextxy(5, 525, _T("����ģʽ��"));//��������
	outtextxy(5, 550, _T("��ģʽ���� ��9  * ��9  ����10 ����"));//��������
	outtextxy(5, 575, _T("�е�ģʽ���� ��16 * ��16 ����40 ����"));//��������
	outtextxy(5, 600, _T("��ʦģʽ���� ��16 * ��25 ����60 ����"));//��������
	outtextxy(5, 625, _T("����ģʽ���� ��20 * ��44 ����132����"));//��������
	outtextxy(5, 650, _T("���С��������ˢ����Ϸ������˵���²���"));//��������
	outtextxy(5, 675, _T("С������ʼ��Ц������ɿ����ʹ���ʧ�ܣ����˧���ʹ���ʤ��"));//��������

	EndBatchDraw();//����˫����
}

//�ж��û����
void UserClickMenu(int * confirmPtr)
{
	ExMessage menuclick;//������Ϣ����
	int x = 0;//������
	int y = 0;//������
	while(1)
	{
		MenuPrint();//ͨ��ѭ������ˢ�´��ڣ�ʹ�ñ仯����ʵʱ����
		peekmessage(&menuclick);//ͨ��ѭ�����г�����ȡ��Ϣ
		if (menuclick.message == WM_LBUTTONDOWN)//�������
		{
			x = menuclick.x;//��¼������
			y = menuclick.y;
			if (menuclick.x < 1000 && menuclick.x > 600 && menuclick.y > 90 && menuclick.y < 180)
			{
				MenuClickStatus = 1;//�㵽��һ����ť��ˢ��״̬�������Ա���Ⱦ�仯���ͼƬ
			}
			else if (menuclick.x < 1000 && menuclick.x > 600 && menuclick.y > 190 && menuclick.y < 280)
			{
				MenuClickStatus = 2;//�㵽�ڶ�����ť��ˢ��״̬�������Ա���Ⱦ�仯���ͼƬ
			}
			else if (menuclick.x < 1000 && menuclick.x > 600 && menuclick.y > 290 && menuclick.y < 380)
			{
				MenuClickStatus = 3;//�㵽��������ť��ˢ��״̬�������Ա���Ⱦ�仯���ͼƬ
			}
			else if (menuclick.x < 1000 && menuclick.x > 600 && menuclick.y > 390 && menuclick.y < 480)
			{
				MenuClickStatus = 4;//�㵽���ĸ���ť��ˢ��״̬�������Ա���Ⱦ�仯���ͼƬ
			}
			else if (menuclick.x < 1500 && menuclick.x > 1100 && menuclick.y > 90 && menuclick.y < 490)
			{
				exitstatus = 1;//�㵽���˳�����ť��ˢ��״̬�������Ա���Ⱦ�仯���ͼƬ
			}
		}
		if (menuclick.message == WM_LBUTTONUP)//���̧��
		{
			exitstatus = 0;//ˢ�±������Ա���Ⱦ̧��İ�����ͼƬ
			MenuClickStatus = 0;//ˢ�±������Ա���Ⱦ̧��İ�����ͼƬ
			if (menuclick.x < 1000 && menuclick.x > 600 && menuclick.y > 90 && menuclick.y < 180)
			{
				if (x < 1000 && x > 600 && y > 90 && y < 180)
				{
					*confirmPtr = 1;//���º�̧�����ڵ�һ����ť�ϣ���ѡ��ؿ�Ϊ��һ��
					break;
				}
			}
			else if (menuclick.x < 1000 && menuclick.x > 600 && menuclick.y > 190 && menuclick.y < 280)
			{
				if (x < 1000 && x > 600 && y > 190 && y < 280)
				{
					*confirmPtr = 2;//���º�̧�����ڵڶ�����ť�ϣ���ѡ��ؿ�Ϊ�ڶ���
					break;
				}
			}
			else if (menuclick.x < 1000 && menuclick.x > 600 && menuclick.y > 290 && menuclick.y < 380)
			{
				if (x < 1000 && x > 600 && y > 290 && y < 380)
				{
					*confirmPtr = 3;//���º�̧�����ڵ�������ť�ϣ���ѡ��ؿ�Ϊ������
					break;
				}
			}
			else if (menuclick.x < 1000 && menuclick.x > 600 && menuclick.y > 390 && menuclick.y < 480)
			{
				if (x < 1000 && x > 600 && y > 390 && y < 480)
				{
					*confirmPtr = 4;//���º�̧�����ڵ��ĸ���ť�ϣ���ѡ��ؿ�Ϊ���Ĺ�
					break;
				}
			}
			else if (menuclick.x < 1500 && menuclick.x > 1100 && menuclick.y > 90 && menuclick.y < 490)
			{
				if (x < 1500 && x > 1100 && y > 90 && y < 490)
				{
					*confirmPtr = 0;//���º�̧�������˳���ť�ϣ����˳���Ϸ
					break;
				}
			}
		}
	}
}


//������ʼ��������飬difficulty�������Ѷȣ���ͬ�Ѷȳ�ʼ����С��ͬ
void DeepBoardIntial(int deep[ROW][COL], int row, int col)
{
	int i = 0, j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			deep[i][j] = 0;//��ʼ��Ϊ0���Ա�֮���������
		}
	}
}

//������ʼ���������飬difficulty�������Ѷȣ���ͬ�Ѷȳ�ʼ����С��ͬ
void FaceBoardIntial(char face[ROW][COL], int row, int col)
{
	int i = 0, j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			face[i][j] = '_';//��ʼ��Ϊ _ ����ʾδ��ʾ�ĸ���
		}
	}
}

//������õ���
void RandomMineGenerate(int deep[ROW][COL], int row, int col, int minesnum)
{
	int x = 0;
	int y = 0;
	int i = 0;
	srand((unsigned int)time(NULL));//�����������
	for (i = 0; i < minesnum; i++)//minesnum�׵ĸ���������ѭ������
	{
		x = rand() % row;//����0~(row - 1)�����֣���ʾ�������
		y = rand() % col;//����0~(col - 1)�����֣���ʾ�������
		if (deep[x][y] != MINE)//ȷ�����λ�ò����ף�ֻҪ�����Ѿ��ǵ��׵ĸ��ӣ����һ�����ף���ֹ�ظ����õ��µĵ�����Ŀ����
		{
			deep[x][y] = MINE;//�����������ɵ�������Ϊ��
		}
		else//������ף�����������
		{
			i--;//i--����ʵ�ִ˴����ϣ���������һ�ε�Ч��
		}
	}
}

//����Ƿ�ʤ����0Ϊ�䣬1ΪӮ��2Ϊ����
int IsGameWin(int deep[ROW][COL], char face[ROW][COL], int row, int col, int row2, int col2)
{
	if (deep[row][col] == MINE && face[row][col] == 'x')//ֻҪ��������ҵ��������0������
	{
		return 0;
	}
	int i = 0, j = 0;
	for (i = 0; i < row2; i++)
	{
		for (j = 0; j < col2; j++)
		{
			if (deep[i][j] != MINE && (face[i][j] == '_' || face[i][j] == 'f'))//ֻҪ���з��׸���û̽��������2���ͼ���
			{
				return 2;
			}
		}
	}
	return 1;//û�в��ף���û�з��׸���δ̽��������1����Ӯ
}

//������ʾ���������Χû���׵ĸ��ӣ��������㣬��Χ�ͻ�������ʾ,ʵ��ԭ�����
//������ʾ��ԭ���һ�ֲ������������͵ĸ�ֵΪ L ������ʵ�ֵ����̽��һ��û���׵Ŀտ�ʱ������Ӧ���Զ���ʾ��ÿտ����ڵ����пտ飬ֱ���������֣����������ڵĿ飩�����������ԭ��ɨ����Ϸ�Ĺؼ��ص㣬�ӿ���Ϸ����
void LinkChange(int deep[ROW][COL], char face[ROW][COL], int i, int j, int row, int col)
{
	//��������ʹ���˵ݹ飬�������һЩ����ʹ�õݹ鲻��һֱ�ݹ���ȥ
	if (!CheckIfValid(i, j, row, col))//ֻҪ����������Χ��ֱ�ӷ��أ���������ֵΪvoid��ֱ��return�������κ�ֵ
	{
		return;
	}
	if (face[i][j] == 'L')//�Ѿ�����Ϊ������ʾ��־ L ����ֱ�ӷ���
	{
		return;
	}
	if (deep[i][j] > 0 && deep[i][j] < 9)//������0�Աߵķ������֣�Ҳ����Ϊ L ���ҷ���
	{
		face[i][j] = 'L';
		return;
	}
	if (deep[i][j] == 9)//�ǵ�����ֱ�ӷ���
	{
		return;
	}
	if (deep[i][j] == 0)//һ��λ��Ϊ0�������λֵ��Ϊ L ����̽������Χ�˸����ӣ����еݹ�
	{
		face[i][j] = 'L';
		LinkChange(deep, face, i - 1, j - 1, row, col);
		LinkChange(deep, face, i - 1, j, row, col);
		LinkChange(deep, face, i - 1, j + 1, row, col);
		LinkChange(deep, face, i, j - 1, row, col);
		LinkChange(deep, face, i, j + 1, row, col);
		LinkChange(deep, face, i + 1, j - 1, row, col);
		LinkChange(deep, face, i + 1, j, row, col);
		LinkChange(deep, face, i + 1, j + 1, row, col);
	}
}

//װ�����֣�������׸�����Ӧ�������ּ�������ʾ��Χ�׵ĸ�����װ����������
void FillinNum(int deep[ROW][COL], int row, int col)
{
	int i = 0, j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (deep[i][j] == MINE)//�������(i,j)���ף������Աߵİ˸����Ӷ���һ
			{
				if (CheckIfValid(i - 1, j - 1, row, col) && deep[i - 1][j - 1] != MINE)//�жϸ����Ƿ����ף������ж������Ƿ���Ч��������Ч�Ҳ��ǵ��ײ��ܼ�һ
				{
					deep[i - 1][j - 1]++;
				}
				if (CheckIfValid(i - 1, j, row, col) && deep[i - 1][j] != MINE)
				{
					deep[i - 1][j]++;
				}
				if (CheckIfValid(i - 1, j + 1, row, col) && deep[i - 1][j + 1] != MINE)
				{
					deep[i - 1][j + 1]++;
				}
				if (CheckIfValid(i, j - 1, row, col) && deep[i][j - 1] != MINE)
				{
					deep[i][j - 1]++;
				}
				if (CheckIfValid(i, j + 1, row, col) && deep[i][j + 1] != MINE)
				{
					deep[i][j + 1]++;
				}
				if (CheckIfValid(i + 1, j - 1, row, col) && deep[i + 1][j - 1] != MINE)
				{
					deep[i + 1][j - 1]++;
				}
				if (CheckIfValid(i + 1, j, row, col) && deep[i + 1][j] != MINE)
				{
					deep[i + 1][j]++;
				}
				if (CheckIfValid(i + 1, j + 1, row, col) && deep[i + 1][j + 1] != MINE)
				{
					deep[i + 1][j + 1]++;
				}
			}
		}
	}
}

//��������Ƿ���Ч
int CheckIfValid(int row, int col, int row2, int col2)
{
	if (row >= 0 && row < row2 && col >= 0 && col < col2)//��������Ƿ���������
	{
		return 1;//��������Ϊ��Ч������1Ϊ��Ч
	}
	return 0;//����������Ϊ��Ч������0Ϊ��Ч
}

//ˢ����Ϸ����
void UpdateWin(int deep[ROW][COL], char face[ROW][COL], int difficulty, int row, int col)
{
	BeginBatchDraw();//��ʼ˫����
	putimage(0, 0, &DeepBackground);//�󱳾�
	putimage(800 - (&EachDifficultyBackground[difficulty])->getwidth() / 2, 90, &EachDifficultyBackground[difficulty]);//��������
	putimage((800 - EachDifficultyBackground[difficulty].getwidth() / 2) + 8, 105, &BackBlock[back]);//���ؼ���0Ϊ����ʱ�ķ��ؼ���1Ϊ���µķ��ؼ�
	putimage((WIN_WIDTH / 2) - 18, 105, &SmilingFaceBlock[smile]);//Ц����0Ϊ�����Ц����1Ϊ���µ�Ц��
	if (cry == 1)//����0�ǲ�������Ⱦ��1����Ⱦ����ʱ�Ŀ�����2����Ⱦ����ʱ�Ŀ���
	{
		putimage((WIN_WIDTH / 2) - 18, 105, &CryingFaceBlock[0]);//����ʱ�Ŀ���
	}
	else if(cry == 2)
	{
		putimage((WIN_WIDTH / 2) - 18, 105, &CryingFaceBlock[1]);//����ʱ�Ŀ���
	}
	if (handsome == 1)//˧��0�ǲ�������Ⱦ��1����Ⱦ����ʱ��˧����2����Ⱦ����ʱ��˧��
	{
		putimage((WIN_WIDTH / 2) - 18, 105, &HandsomeFaceBlock[0]);//����ʱ��˧��
	}
	else if (handsome == 2)
	{
		putimage((WIN_WIDTH / 2) - 18, 105, &HandsomeFaceBlock[1]);//����ʱ��˧��
	}
	//��ӡ��������row * col
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (face[i][j] == 'x' || face[i][j] == 'L')//��������������̽��������̽����ֻҪ����������־�е�һ������ֱ�Ӵ�ӡ������Ϣ���ǿշ�����ߴ����ֵĿշ���
			{
				if (deep[i][j] == 0)//���������0������Ⱦ�շ���
				{
					putimage((800 - EachDifficultyBackground[difficulty].getwidth() / 2) + 8 + j * 36, 90 + 79 + i * 36, &DiscoveredEmptyBlock);//��Ⱦ�շ���
				}
				else//���������0֮������֣�����Ⱦ����Ӧ���ֵķ���
				{
					putimage((800 - EachDifficultyBackground[difficulty].getwidth() / 2) + 8 + j * 36, 90 + 79 + i * 36, &NumberEmptyBlock[deep[i][j] - 1]);//��Ⱦ����Ӧ���ֵķ���
				}
			}
			else if (face[i][j] == 'r' || face[i][j] == 'b')//������������ʧ��ʱ��ʾ�챳�����׺ͺڱ�������
			{
				if (face[i][j] == 'r')//������rʱ����Ⱦ�챳�����׵ķ���
				{
					putimage((800 - EachDifficultyBackground[difficulty].getwidth() / 2) + 8 + j * 36, 90 + 79 + i * 36, &RedMineBlock);//��Ⱦ�챳�����׵ķ���
				}
				else//������bʱ����Ⱦ�ڱ������׵ķ���
				{
					putimage((800 - EachDifficultyBackground[difficulty].getwidth() / 2) + 8 + j * 36, 90 + 79 + i * 36, &BlackMineBlock);//��Ⱦ�ڱ������׵ķ���
				}
			}
			else if (face[i][j] == 'f')//�����������ʾ����ķ��飬ֻҪface[i][j]����f������Ⱦ����ķ���
			{
				putimage((800 - EachDifficultyBackground[difficulty].getwidth() / 2) + 8 + j * 36, 90 + 79 + i * 36, &FlagBlock);//��Ⱦ����ķ���
			}
			else if(face[i][j] == '_')//ֻҪ������_������Ⱦδ̽���ķ���
			{
				putimage((800 - EachDifficultyBackground[difficulty].getwidth() / 2) + 8 + j * 36, 90 + 79 + i * 36, &CoveredBlock);//��Ⱦδ̽���ķ���
			}
		}
	}
	EndBatchDraw();//����˫����
}

//��Ϸ����
void GameMain(int deep[ROW][COL], char face[ROW][COL], int difficulty, int rowrow, int colcol, int minenum)
{
	while(1)//���������ȼ���Ϸ��ѭ�����Ա����ÿһ�ֵ����¿�ʼ
	{
		DeepBoardIntial(deep, rowrow, colcol);//���Ѷȸ���Ϊ row * col ��С
		FaceBoardIntial(face, rowrow, colcol);
		RandomMineGenerate(deep, rowrow, colcol, minenum);//������ɵ��ף�����minenum��
		FillinNum(deep, rowrow, colcol);//װ������
		ExMessage msg;//������ȡ��Ϣ
		int row = 0, col = 0;//�������������������
		int rowr = 0, colr = 0;//�������������������
		bool RightButtonPressed = false;//�Ҽ����±�־����
		int check = 0;//����Ƿ�ʤ����0Ϊʧ�ܣ�1Ϊʤ����2Ϊ����
		cry = 0;//�µ�һ����Ϸ��������״̬����ˢ��Ϊ0��������Ⱦ����ͼƬ��ʹЦ����������
		handsome = 0;//�µ�һ����Ϸ����˧��״̬����ˢ��Ϊ0��������Ⱦ˧��ͼƬ��ʹЦ����������
		do//����һ����Ϸ��ѭ����������������һ��
		{
			UpdateWin(deep, face, difficulty, rowrow, colcol);//ͨ��ѭ��������ˢ�´��ڣ���ʹ�仯ʵʱ����
			peekmessage(&msg);//ͨ��ѭ��������ȡ��Ϣ
			if (msg.message == WM_LBUTTONDOWN)//�������
			{
				//��������£�������������ͻὫ���������ת��Ϊ��ά��������У��Ը����н��м�¼
				if (msg.x < ((800 - EachDifficultyBackground[difficulty].getwidth() / 2) + 8 + colcol * 36) && msg.x > (800 - EachDifficultyBackground[difficulty].getwidth() / 2) + 8 && msg.y < 169 + rowrow * 36 && msg.y > 169)
				{
					row = ((msg.y - 169) / 36) + 1;
					col = ((msg.x - ((800 - EachDifficultyBackground[difficulty].getwidth() / 2) + 8)) / 36) + 1;
					if (!(face[row - 1][col - 1] == 'x' || face[row - 1][col - 1] == 'L'))//ֻҪ�����Ѿ���ʾ���ĵؿ�ͻ������ѱ�ǣ�����һ��ˢ�´���ʱ�Ϳ�����ʾ��̽����������
					{
						face[row - 1][col - 1] = 'x';
					}
				}
				if (msg.x > 782 && msg.x < 818 && msg.y > 105 && msg.y < 141)
				{
					smile = 1;//����ʱ�����Ц����ť�ϰ��£�״̬����back��Ϊ1����ʱ��ť����ȾΪ���µ�ͼƬ
				}
				if (msg.x > (800 - EachDifficultyBackground[difficulty].getwidth() / 2) + 8 && msg.x < (800 - EachDifficultyBackground[difficulty].getwidth() / 2) + 44 && msg.y > 105 && msg.y < 141)
				{
					back = 1;//����ʱ����ڷ��ذ�ť�ϰ��£�״̬����back��Ϊ1����ʱ��ť����ȾΪ���µ�ͼƬ
				}
			}
			if (msg.message == WM_LBUTTONUP && back == 1)
			{
				back = 0;//���̧��ʱ����ť(�����Ƿ����ڰ�ť��̧��)�ͻᵯ��ͼƬ��ȾΪ̧��ķ��ؼ�
				if (msg.x > (800 - EachDifficultyBackground[difficulty].getwidth() / 2) + 8 && msg.x < (800 - EachDifficultyBackground[difficulty].getwidth() / 2) + 44 && msg.y > 105 && msg.y < 141)
				{
					return ;//ֻ��̧��ʱ������Ҳ�ڰ�ť�ϣ��Ż᷵�ز˵�������ʱ�������أ����������ﻹ��һ��ѭ����������Ϸ����ʱ�᷵�ز˵�
				}
			}
			if (msg.message == WM_LBUTTONUP && smile == 1)
			{
				smile = 0;//���̧��ʱ����ť(�����Ƿ����ڰ�ť��̧��)�ͻᵯ��ͼƬ��ȾΪ̧���Ц����
				if (msg.x > 782 && msg.x < 818 && msg.y > 105 && msg.y < 141)
				{
					break;//ֻ��̧��ʱ������Ҳ��Ц����ť�ϣ������ڲ�ѭ��������ˢ������
				}
			}
			if (msg.message == WM_RBUTTONDOWN)
			{
				//�Ҽ����£�������������ͻὫ���������ת��Ϊ��ά��������У��Ը����н��м�¼
				if (msg.x < ((800 - EachDifficultyBackground[difficulty].getwidth() / 2) + 8 + colcol * 36) && msg.x >(800 - EachDifficultyBackground[difficulty].getwidth() / 2) + 8 && msg.y < 169 + rowrow * 36 && msg.y > 169)
				{
					rowr = ((msg.y - 169) / 36) + 1;
					colr = ((msg.x - ((800 - EachDifficultyBackground[difficulty].getwidth() / 2) + 8)) / 36) + 1;
					RightButtonPressed = true;//���Ҽ�����״̬�����趨Ϊ�棬���Ҽ��Ѿ�����
				}
			}
			if (msg.message == WM_RBUTTONUP && RightButtonPressed)//�Ҽ�̧�𣬶���Ҫ�Ҽ�����״̬����Ϊ��
			{
				//�Ҽ�̧��������������ͻὫ����ת��Ϊ��ά��������У�Ȼ������������н��жԱȣ������ͬ���������Ĳ���
				if (rowr == ((msg.y - 169) / 36) + 1 && colr == ((msg.x - ((800 - EachDifficultyBackground[difficulty].getwidth() / 2) + 8)) / 36) + 1 && !(face[rowr - 1][colr - 1] == 'x' || face[rowr - 1][colr - 1] == 'L'))
				{
					if (face[rowr - 1][colr - 1] == '_')//�����δ���죬����б���
					{
						face[rowr - 1][colr - 1] = 'f';
					}
					else if (face[rowr - 1][colr - 1] == 'f')//������ѱ��죬�����ȡ������
					{
						face[rowr - 1][colr - 1] = '_';
					}
					//����ʵ���Ҽ���һ�±��죬�ٵ�һ��ȡ������
					RightButtonPressed = false;//������״̬����ˢ��Ϊ��
				}
			}
			check = IsGameWin(deep, face, row - 1, col - 1, rowrow, colcol);//����Ƿ�ʤ����ʧ���Լ���Ϸ�Ƿ����
			if (check == 2)//ֻҪ��Ϸ���������ж��Ƿ�������ʾ
			{
				if (deep[row - 1][col - 1] == 0)//��ʾ�ĸ����ǿո�(��������0����Χ�˸�����û�е���)����������ʾ
				{
					LinkChange(deep, face, row - 1, col - 1, rowrow, colcol);//�����������ĸ��ӽ���������ʾ
				}
			}
		} while (check == 2);//ֻҪcheckΪ2���������ѭ������������Ϸ������checkΪ1��0(��Ӯ����)���˳�ѭ��
		if (check == 1)//checkΪ1ʱʤ��
		{
			//ʤ��ʱЦ������˧��
			handsome = 1;//��˧��״̬������Ϊ1����Ⱦ����ʱ��˧��
			UpdateWin(deep, face, difficulty, rowrow, colcol);//ˢ�´��ڣ���ʹ˧���ɼ�
			while (1)//��ʱ�Ѿ�ʤ�����ȴ����˧��ˢ�»��ߵ�����ؽ�����
			{
				peekmessage(&msg);//ͨ��ѭ��������ȡ������Ϣ
				if (msg.message == WM_LBUTTONDOWN)//�������
				{
					if (msg.x > 782 && msg.x < 818 && msg.y > 105 && msg.y < 141)
					{
						handsome = 2;//�������˧���ϣ���˧��״̬������Ϊ2������ȾΪ���µ�˧��
					}
					if (msg.x > (800 - EachDifficultyBackground[difficulty].getwidth() / 2) + 8 && msg.x < (800 - EachDifficultyBackground[difficulty].getwidth() / 2) + 44 && msg.y > 105 && msg.y < 141)
					{
						back = 1;//����ʱ����ڷ��ذ�ť�ϰ��£�״̬����back��Ϊ1����ʱ��ť����ȾΪ���µ�ͼƬ
					}
					UpdateWin(deep, face, difficulty, rowrow, colcol);//ˢ�´��ڣ�ʹ����Щ�仯ʵʱ����
				}
				if (msg.message == WM_LBUTTONUP && back == 1)//���̧�𣬶���back����Ϊ1
				{
					back = 0;//���̧��ʱ����ť(�����Ƿ����ڰ�ť��̧��)�ͻᵯ��ͼƬ��ȾΪ̧��ķ��ؼ�
					UpdateWin(deep, face, difficulty, rowrow, colcol);//ˢ�´��ڣ�ʹ����Щ�仯ʵʱ����
					if (msg.x > (800 - EachDifficultyBackground[difficulty].getwidth() / 2) + 8 && msg.x < (800 - EachDifficultyBackground[difficulty].getwidth() / 2) + 44 && msg.y > 105 && msg.y < 141)
					{
						return;//ֻ��̧��ʱ������Ҳ�ڰ�ť�ϣ��Ż᷵�ز˵�������ʱ�������أ����������ﻹ��һ��ѭ����������Ϸ����ʱ�᷵�ز˵�
					}
				}
				if (msg.message == WM_LBUTTONUP && handsome == 2)//���̧�𣬶���handsome����Ϊ1
				{
					handsome = 1;//���̧��ʱ����ť(�����Ƿ����ڰ�ť��̧��)�ͻᵯ��ͼƬ��ȾΪ̧���˧��
					UpdateWin(deep, face, difficulty, rowrow, colcol);//ˢ�´��ڣ�ʹ����Щ�仯ʵʱ����
					if (msg.x > 782 && msg.x < 818 && msg.y > 105 && msg.y < 141)
					{
						break;//ֻ��̧��ʱ������Ҳ��Ц����ť�ϣ������ڲ�ѭ��������ˢ������
					}
				}
			}
		}
		else if (check == 0)//checkΪ0ʱʧ��
		{
			//ʧ��ʱҪ�����е�����ʾ��������������׵ı���Ϊ��ɫ����������׵ı���Ϊ��ɫ
			for (int i = 0; i < rowrow; i++)
			{
				for (int j = 0; j < colcol; j++)
				{
					if (deep[i][j] == MINE && (face[i][j] == 'x' || face[i][j] == 'L'))
					{
						face[i][j] = 'r';//��������׵ı���Ϊ��ɫ
					}
					else if (deep[i][j] == MINE && (face[i][j] == '_' || face[i][j] == 'f'))
					{
						face[i][j] = 'b';//��������׵ı���Ϊ��ɫ
					}
				}
			}
			cry = 1;//������״̬������Ϊ1������ȾΪ����Ŀ���
			UpdateWin(deep, face, difficulty, rowrow, colcol);//ˢ�´��ڣ�ʹ����Щ�仯ʵʱ����
			while (1)//��ʱ�Ѿ�ʧ�ܣ��ȴ��������ˢ�»��ߵ�����ؼ����ز˵�
			{
				peekmessage(&msg);//ͨ��ѭ��������ȡ������Ϣ
				if (msg.message == WM_LBUTTONDOWN)//�������
				{
					if (msg.x > 782 && msg.x < 818 && msg.y > 105 && msg.y < 141)
					{
						cry = 2;//������������ϣ������״̬������Ϊ2������ȾΪ���µĿ���
					}
					if (msg.x > (800 - EachDifficultyBackground[difficulty].getwidth() / 2) + 8 && msg.x < (800 - EachDifficultyBackground[difficulty].getwidth() / 2) + 44 && msg.y > 105 && msg.y < 141)
					{
						back = 1;//����ʱ����ڷ��ذ�ť�ϰ��£�״̬����back��Ϊ1����ʱ��ť����ȾΪ���µ�ͼƬ
					}
					UpdateWin(deep, face, difficulty, rowrow, colcol);//ˢ�´��ڣ�ʹ����Щ�仯ʵʱ����
				}
				if (msg.message == WM_LBUTTONUP && back == 1)//���̧�𣬶���back����Ϊ1
				{
					back = 0;//���̧��ʱ����ť(�����Ƿ����ڰ�ť��̧��)�ͻᵯ��ͼƬ��ȾΪ̧��ķ��ؼ�
					UpdateWin(deep, face, difficulty, rowrow, colcol);//ˢ�´��ڣ�ʹ����Щ�仯ʵʱ����
					if (msg.x > (800 - EachDifficultyBackground[difficulty].getwidth() / 2) + 8 && msg.x < (800 - EachDifficultyBackground[difficulty].getwidth() / 2) + 44 && msg.y > 105 && msg.y < 141)
					{
						return;//ֻ��̧��ʱ������Ҳ�ڰ�ť�ϣ��Ż᷵�ز˵�������ʱ�������أ����������ﻹ��һ��ѭ����������Ϸ����ʱ�᷵�ز˵�
					}
				}
				if (msg.message == WM_LBUTTONUP && cry == 2)//���̧�𣬶���handsome����Ϊ1
				{
					cry = 1;//���̧��ʱ����ť(�����Ƿ����ڰ�ť��̧��)�ͻᵯ��ͼƬ��ȾΪ̧��Ŀ���
					UpdateWin(deep, face, difficulty, rowrow, colcol);//ˢ�´��ڣ�ʹ����Щ�仯ʵʱ����
					if (msg.x > 782 && msg.x < 818 && msg.y > 105 && msg.y < 141)
					{
						break;//ֻ��̧��ʱ������Ҳ��Ц����ť�ϣ������ڲ�ѭ��������ˢ������
					}
				}
			}
		}
	}
}