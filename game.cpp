#include "game.h"

IMAGE DeepBackground;//创建最底部背景
IMAGE EachDifficultyBackground[DIFFICULTY];//有DIFFICULTY种各个难度的背景
IMAGE NumberEmptyBlock[8];//八种含数字的空方快
IMAGE DiscoveredEmptyBlock;//探索过的空方快
IMAGE CoveredBlock;//未探索的方块
IMAGE DifficultyMenu[DIFFICULTY][2];//菜单中的难度按键
IMAGE RedMineBlock;//红色的雷
IMAGE BlackMineBlock;//黑色的雷
IMAGE FlagBlock;//标旗
IMAGE SmilingFaceBlock[2];//笑脸
IMAGE HandsomeFaceBlock[2];//帅脸
IMAGE CryingFaceBlock[2];//哭脸
IMAGE BackBlock[2];//返回键
IMAGE ExitBlock[2];//退出游戏
int MenuClickStatus = 0;//0为未点击，1为点击简单难度，2为点击中等难度，以此类推
int smile = 0;//笑脸状态变量，0是第一张，1是第二张
int cry = 0;//哭脸状态变量，0是不用打印，1是第一张，2是第二张
int handsome = 0;//帅脸状态变量，0是不用打印，1是第一张，2是第二张
int back = 0;//返回键状态变量，0为第一张，1为第二张
int exitstatus = 0;

//初始化游戏，加载资源
void GameInitialization()
{
	//将最底部背景加载入内存
	loadimage(&DeepBackground, "rsc/background/DeepBackground.png");
	//名字字符串，方便对路径的文本进行存储
	char name[64];//字符数组，用来装载路径
	for (int i = 0; i < DIFFICULTY; i++)//加载菜单中的难度按键
	{
		for (int j = 0; j < 2; j++)
		{
			sprintf(name, "rsc/menu/%d_Difficulty_%d.png", i + 1, j + 1);//依次将难度按键的路径写入name中
			loadimage(&DifficultyMenu[i][j], name);//依次将难度按键加载入内存
		}
	}
	for(int i = 0;i < DIFFICULTY;i++)//对DIFFICULTY种难度背景进行加载
	{
		sprintf(name, "rsc/background/Difficulty_%d.png",i + 1);//将这几种背景的路径写入name中
		loadimage(&EachDifficultyBackground[i], name);//将背景进行加载
	}
	for (int i = 0; i < 8; i++)//对八种带数字的空方快进行加载
	{
		sprintf(name,"rsc/block/%d_block.png", i + 1);//将路径写入name中
		loadimage(&NumberEmptyBlock[i], name);//加载八种方块
	}
	loadimage(&CoveredBlock, "rsc/block/covered_block.png");//加载未探索的方块
	loadimage(&DiscoveredEmptyBlock, "rsc/block/empty_block.png");//加载探索过的空方块
	loadimage(&RedMineBlock, "rsc/block/mine_boom_block.png");//加载红背景的雷
	loadimage(&BlackMineBlock, "rsc/block/mine_appear_block.png");//加载黑背景的雷
	loadimage(&FlagBlock, "rsc/block/flag_block.png");//加载标旗方块
	loadimage(&SmilingFaceBlock[0], "rsc/block/smilingface_block.png");//加载弹起的笑脸方块
	loadimage(&SmilingFaceBlock[1], "rsc/block/smilingface_block_down.png");//加载按下的笑脸方块
	loadimage(&HandsomeFaceBlock[0], "rsc/block/handsomeface.png");//加载弹起的帅脸方块
	loadimage(&HandsomeFaceBlock[1], "rsc/block/handsomeface_down.png");//加载按下的帅脸方块
	loadimage(&CryingFaceBlock[0], "rsc/block/cryingface_block.png");//加载弹起的哭脸方块
	loadimage(&CryingFaceBlock[1], "rsc/block/cryingface_block_down.png");//加载按下的哭脸方块
	loadimage(&BackBlock[0], "rsc/block/back_block.png");//加载返回键
	loadimage(&BackBlock[1], "rsc/block/back_block_down.png");//加载返回键
	loadimage(&ExitBlock[0], "rsc/menu/exit_up.png");//加载退出游戏键
	loadimage(&ExitBlock[1], "rsc/menu/exit_down.png");//加载退出游戏键
	initgraph(WIN_WIDTH, WIN_HEIGHT, 0);//初始化窗口
}

//菜单渲染
void MenuPrint()
{
	BeginBatchDraw();//开始双缓冲
	putimage(0, 0, &DeepBackground);//渲染最底部背景
	for(int i = 0;i < DIFFICULTY;i++)//依次渲染难度按键，未按下的状态
	{
		putimage(600, 90 + i * 100, &DifficultyMenu[i][0]);
	}
	if(MenuClickStatus)//只要MenuClickStatus不为零就可以进行下面的操作
	{
		putimage(600, 90 + (MenuClickStatus - 1) * 100, &DifficultyMenu[MenuClickStatus - 1][1]);//通过MenuClickStatus进行渲染对应种类的按下的按键
	}
	putimage(1100, 90, &ExitBlock[exitstatus]);//渲染退出键
	setbkmode(TRANSPARENT);// 设置文字背景为透明
	settextcolor(BLACK);// 设置文字颜色
	settextstyle(25, 0, _T("黑体"));//设置字体大小和字体
	outtextxy(5, 500, _T("鼠标左键可以揭示方块，鼠标右键可以标志小旗，再次右键取消标记"));//字体内容
	outtextxy(5, 525, _T("四种模式："));//字体内容
	outtextxy(5, 550, _T("简单模式场地 行9  * 列9  ，有10 个雷"));//字体内容
	outtextxy(5, 575, _T("中等模式场地 行16 * 列16 ，有40 个雷"));//字体内容
	outtextxy(5, 600, _T("大师模式场地 行16 * 列25 ，有60 个雷"));//字体内容
	outtextxy(5, 625, _T("满屏模式场地 行20 * 列44 ，有132个雷"));//字体内容
	outtextxy(5, 650, _T("点击小黄脸可以刷新游戏，后者说重新布雷"));//字体内容
	outtextxy(5, 675, _T("小黄脸初始是笑脸，变成哭脸就代表失败，变成帅脸就代表胜利"));//字体内容

	EndBatchDraw();//结束双缓冲
}

//判断用户点击
void UserClickMenu(int * confirmPtr)
{
	ExMessage menuclick;//创建信息变量
	int x = 0;//横坐标
	int y = 0;//纵坐标
	while(1)
	{
		MenuPrint();//通过循环持续刷新窗口，使得变化可以实时显现
		peekmessage(&menuclick);//通过循环进行持续获取信息
		if (menuclick.message == WM_LBUTTONDOWN)//左键按下
		{
			x = menuclick.x;//记录下坐标
			y = menuclick.y;
			if (menuclick.x < 1000 && menuclick.x > 600 && menuclick.y > 90 && menuclick.y < 180)
			{
				MenuClickStatus = 1;//点到第一个按钮，刷新状态变量，以便渲染变化后的图片
			}
			else if (menuclick.x < 1000 && menuclick.x > 600 && menuclick.y > 190 && menuclick.y < 280)
			{
				MenuClickStatus = 2;//点到第二个按钮，刷新状态变量，以便渲染变化后的图片
			}
			else if (menuclick.x < 1000 && menuclick.x > 600 && menuclick.y > 290 && menuclick.y < 380)
			{
				MenuClickStatus = 3;//点到第三个按钮，刷新状态变量，以便渲染变化后的图片
			}
			else if (menuclick.x < 1000 && menuclick.x > 600 && menuclick.y > 390 && menuclick.y < 480)
			{
				MenuClickStatus = 4;//点到第四个按钮，刷新状态变量，以便渲染变化后的图片
			}
			else if (menuclick.x < 1500 && menuclick.x > 1100 && menuclick.y > 90 && menuclick.y < 490)
			{
				exitstatus = 1;//点到第退出个按钮，刷新状态变量，以便渲染变化后的图片
			}
		}
		if (menuclick.message == WM_LBUTTONUP)//左键抬起
		{
			exitstatus = 0;//刷新变量，以便渲染抬起的按键的图片
			MenuClickStatus = 0;//刷新变量，以便渲染抬起的按键的图片
			if (menuclick.x < 1000 && menuclick.x > 600 && menuclick.y > 90 && menuclick.y < 180)
			{
				if (x < 1000 && x > 600 && y > 90 && y < 180)
				{
					*confirmPtr = 1;//按下和抬起都是在第一个按钮上，则选则关卡为第一关
					break;
				}
			}
			else if (menuclick.x < 1000 && menuclick.x > 600 && menuclick.y > 190 && menuclick.y < 280)
			{
				if (x < 1000 && x > 600 && y > 190 && y < 280)
				{
					*confirmPtr = 2;//按下和抬起都是在第二个按钮上，则选则关卡为第二关
					break;
				}
			}
			else if (menuclick.x < 1000 && menuclick.x > 600 && menuclick.y > 290 && menuclick.y < 380)
			{
				if (x < 1000 && x > 600 && y > 290 && y < 380)
				{
					*confirmPtr = 3;//按下和抬起都是在第三个按钮上，则选则关卡为第三关
					break;
				}
			}
			else if (menuclick.x < 1000 && menuclick.x > 600 && menuclick.y > 390 && menuclick.y < 480)
			{
				if (x < 1000 && x > 600 && y > 390 && y < 480)
				{
					*confirmPtr = 4;//按下和抬起都是在第四个按钮上，则选则关卡为第四关
					break;
				}
			}
			else if (menuclick.x < 1500 && menuclick.x > 1100 && menuclick.y > 90 && menuclick.y < 490)
			{
				if (x < 1500 && x > 1100 && y > 90 && y < 490)
				{
					*confirmPtr = 0;//按下和抬起都是在退出按钮上，则退出游戏
					break;
				}
			}
		}
	}
}


//用来初始化深层数组，difficulty用来传难度，不同难度初始化大小不同
void DeepBoardIntial(int deep[ROW][COL], int row, int col)
{
	int i = 0, j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			deep[i][j] = 0;//初始化为0，以便之后填充数字
		}
	}
}

//用来初始化表面数组，difficulty用来传难度，不同难度初始化大小不同
void FaceBoardIntial(char face[ROW][COL], int row, int col)
{
	int i = 0, j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			face[i][j] = '_';//初始化为 _ ，表示未揭示的格子
		}
	}
}

//随机放置地雷
void RandomMineGenerate(int deep[ROW][COL], int row, int col, int minesnum)
{
	int x = 0;
	int y = 0;
	int i = 0;
	srand((unsigned int)time(NULL));//设置随机种子
	for (i = 0; i < minesnum; i++)//minesnum雷的个数，即是循环次数
	{
		x = rand() % row;//产生0~(row - 1)的数字，表示随机的行
		y = rand() % col;//产生0~(col - 1)的数字，表示随机的列
		if (deep[x][y] != MINE)//确保这个位置不是雷，只要不是已经是地雷的格子，则放一个地雷，防止重复放置导致的地雷数目减少
		{
			deep[x][y] = MINE;//将这个随机生成的坐标设为雷
		}
		else//如果是雷，则重新生成
		{
			i--;//i--可以实现此次作废，再来生成一次的效果
		}
	}
}

//检查是否胜利，0为输，1为赢，2为继续
int IsGameWin(int deep[ROW][COL], char face[ROW][COL], int row, int col, int row2, int col2)
{
	if (deep[row][col] == MINE && face[row][col] == 'x')//只要是雷且玩家点击，返回0，即输
	{
		return 0;
	}
	int i = 0, j = 0;
	for (i = 0; i < row2; i++)
	{
		for (j = 0; j < col2; j++)
		{
			if (deep[i][j] != MINE && (face[i][j] == '_' || face[i][j] == 'f'))//只要还有非雷格子没探索，返回2，就继续
			{
				return 2;
			}
		}
	}
	return 1;//没有踩雷，且没有非雷格子未探索，返回1，则赢
}

//连续揭示，点的是周围没有雷的格子，即数字零，周围就会连续揭示,实现原版操作
//连续揭示，原版的一种操作，连续解释的赋值为 L ，方便实现当玩家探索一个没有雷的空块时，程序应该自动揭示与该空块相邻的所有空块，直到遇到数字（即与雷相邻的块）。这个特性是原版扫雷游戏的关键特点，加快游戏进程
void LinkChange(int deep[ROW][COL], char face[ROW][COL], int i, int j, int row, int col)
{
	//由于下面使用了递归，必须加入一些条件使得递归不会一直递归下去
	if (!CheckIfValid(i, j, row, col))//只要超出雷区范围，直接返回，函数返回值为void，直接return，不带任何值
	{
		return;
	}
	if (face[i][j] == 'L')//已经设置为连续揭示标志 L 的则直接返回
	{
		return;
	}
	if (deep[i][j] > 0 && deep[i][j] < 9)//在数字0旁边的非零数字，也设置为 L 并且返回
	{
		face[i][j] = 'L';
		return;
	}
	if (deep[i][j] == 9)//是地雷则直接返回
	{
		return;
	}
	if (deep[i][j] == 0)//一个位置为0，将这个位值设为 L 并且探索它周围八个格子，进行递归
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

//装填数字，计算非雷格子中应该是数字几，来表示周围雷的个数，装填在数组中
void FillinNum(int deep[ROW][COL], int row, int col)
{
	int i = 0, j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (deep[i][j] == MINE)//如果坐标(i,j)是雷，则将雷旁边的八个格子都加一
			{
				if (CheckIfValid(i - 1, j - 1, row, col) && deep[i - 1][j - 1] != MINE)//判断格子是否是雷，并且判断坐标是否有效，格子有效且不是地雷才能加一
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

//检查坐标是否有效
int CheckIfValid(int row, int col, int row2, int col2)
{
	if (row >= 0 && row < row2 && col >= 0 && col < col2)//检查坐标是否在雷区内
	{
		return 1;//在雷区内为有效，返回1为有效
	}
	return 0;//不在雷区内为无效，返回0为无效
}

//刷新游戏窗口
void UpdateWin(int deep[ROW][COL], char face[ROW][COL], int difficulty, int row, int col)
{
	BeginBatchDraw();//开始双缓冲
	putimage(0, 0, &DeepBackground);//大背景
	putimage(800 - (&EachDifficultyBackground[difficulty])->getwidth() / 2, 90, &EachDifficultyBackground[difficulty]);//雷区背景
	putimage((800 - EachDifficultyBackground[difficulty].getwidth() / 2) + 8, 105, &BackBlock[back]);//返回键，0为弹起时的返回键，1为按下的返回键
	putimage((WIN_WIDTH / 2) - 18, 105, &SmilingFaceBlock[smile]);//笑脸，0为弹起的笑脸，1为按下的笑脸
	if (cry == 1)//哭脸0是不进行渲染，1是渲染弹起时的哭脸，2是渲染按下时的哭脸
	{
		putimage((WIN_WIDTH / 2) - 18, 105, &CryingFaceBlock[0]);//弹起时的哭脸
	}
	else if(cry == 2)
	{
		putimage((WIN_WIDTH / 2) - 18, 105, &CryingFaceBlock[1]);//按下时的哭脸
	}
	if (handsome == 1)//帅脸0是不进行渲染，1是渲染弹起时的帅脸，2是渲染按下时的帅脸
	{
		putimage((WIN_WIDTH / 2) - 18, 105, &HandsomeFaceBlock[0]);//弹起时的帅脸
	}
	else if (handsome == 2)
	{
		putimage((WIN_WIDTH / 2) - 18, 105, &HandsomeFaceBlock[1]);//按下时的帅脸
	}
	//打印雷区方块row * col
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (face[i][j] == 'x' || face[i][j] == 'L')//这两个内容是已探索和连锁探索，只要是这两个标志中的一个，就直接打印方块信息，是空方快或者带数字的空方快
			{
				if (deep[i][j] == 0)//深层数组是0，则渲染空方快
				{
					putimage((800 - EachDifficultyBackground[difficulty].getwidth() / 2) + 8 + j * 36, 90 + 79 + i * 36, &DiscoveredEmptyBlock);//渲染空方快
				}
				else//深层数组是0之外的数字，则渲染带对应数字的方块
				{
					putimage((800 - EachDifficultyBackground[difficulty].getwidth() / 2) + 8 + j * 36, 90 + 79 + i * 36, &NumberEmptyBlock[deep[i][j] - 1]);//渲染带对应数字的方块
				}
			}
			else if (face[i][j] == 'r' || face[i][j] == 'b')//这两个内容是失败时显示红背景的雷和黑背景的雷
			{
				if (face[i][j] == 'r')//内容是r时，渲染红背景的雷的方块
				{
					putimage((800 - EachDifficultyBackground[difficulty].getwidth() / 2) + 8 + j * 36, 90 + 79 + i * 36, &RedMineBlock);//渲染红背景的雷的方块
				}
				else//内容是b时，渲染黑背景的雷的方块
				{
					putimage((800 - EachDifficultyBackground[difficulty].getwidth() / 2) + 8 + j * 36, 90 + 79 + i * 36, &BlackMineBlock);//渲染黑背景的雷的方块
				}
			}
			else if (face[i][j] == 'f')//这个内容是显示标旗的方块，只要face[i][j]中是f，则渲染标旗的方块
			{
				putimage((800 - EachDifficultyBackground[difficulty].getwidth() / 2) + 8 + j * 36, 90 + 79 + i * 36, &FlagBlock);//渲染标旗的方块
			}
			else if(face[i][j] == '_')//只要内容是_，则渲染未探索的方块
			{
				putimage((800 - EachDifficultyBackground[difficulty].getwidth() / 2) + 8 + j * 36, 90 + 79 + i * 36, &CoveredBlock);//渲染未探索的方块
			}
		}
	}
	EndBatchDraw();//结束双缓冲
}

//游戏主体
void GameMain(int deep[ROW][COL], char face[ROW][COL], int difficulty, int rowrow, int colcol, int minenum)
{
	while(1)//控制整个等级游戏的循环，以便进行每一局的重新开始
	{
		DeepBoardIntial(deep, rowrow, colcol);//简单难度格子为 row * col 大小
		FaceBoardIntial(face, rowrow, colcol);
		RandomMineGenerate(deep, rowrow, colcol, minenum);//随机生成地雷，地雷minenum个
		FillinNum(deep, rowrow, colcol);//装填数字
		ExMessage msg;//用来获取信息
		int row = 0, col = 0;//用来接收玩家输入行列
		int rowr = 0, colr = 0;//用来接收玩家输入行列
		bool RightButtonPressed = false;//右键按下标志变量
		int check = 0;//检查是否胜利，0为失败，1为胜利，2为继续
		cry = 0;//新的一局游戏，将哭脸状态变量刷新为0，即不渲染哭脸图片，使笑脸得以显现
		handsome = 0;//新的一局游戏，将帅脸状态变量刷新为0，即不渲染帅脸图片，使笑脸得以显现
		do//控制一局游戏的循环，跳出后会进行下一局
		{
			UpdateWin(deep, face, difficulty, rowrow, colcol);//通过循环，持续刷新窗口，以使变化实时显现
			peekmessage(&msg);//通过循环持续获取信息
			if (msg.message == WM_LBUTTONDOWN)//左键按下
			{
				//左键键按下，如果在雷区，就会将点击的坐标转化为二维数组的行列，对该行列进行记录
				if (msg.x < ((800 - EachDifficultyBackground[difficulty].getwidth() / 2) + 8 + colcol * 36) && msg.x > (800 - EachDifficultyBackground[difficulty].getwidth() / 2) + 8 && msg.y < 169 + rowrow * 36 && msg.y > 169)
				{
					row = ((msg.y - 169) / 36) + 1;
					col = ((msg.x - ((800 - EachDifficultyBackground[difficulty].getwidth() / 2) + 8)) / 36) + 1;
					if (!(face[row - 1][col - 1] == 'x' || face[row - 1][col - 1] == 'L'))//只要不是已经揭示过的地块就会标记上已标记，在下一次刷新窗口时就可以显示出探索过的样子
					{
						face[row - 1][col - 1] = 'x';
					}
				}
				if (msg.x > 782 && msg.x < 818 && msg.y > 105 && msg.y < 141)
				{
					smile = 1;//这里时左键在笑脸按钮上按下，状态变量back变为1，这时按钮会渲染为按下的图片
				}
				if (msg.x > (800 - EachDifficultyBackground[difficulty].getwidth() / 2) + 8 && msg.x < (800 - EachDifficultyBackground[difficulty].getwidth() / 2) + 44 && msg.y > 105 && msg.y < 141)
				{
					back = 1;//这里时左键在返回按钮上按下，状态变量back变为1，这时按钮会渲染为按下的图片
				}
			}
			if (msg.message == WM_LBUTTONUP && back == 1)
			{
				back = 0;//左键抬起时，按钮(不管是否是在按钮上抬起)就会弹起，图片渲染为抬起的返回键
				if (msg.x > (800 - EachDifficultyBackground[difficulty].getwidth() / 2) + 8 && msg.x < (800 - EachDifficultyBackground[difficulty].getwidth() / 2) + 44 && msg.y > 105 && msg.y < 141)
				{
					return ;//只有抬起时的坐标也在按钮上，才会返回菜单，这里时函数返回，在主函数里还有一个循环来控制游戏返回时会返回菜单
				}
			}
			if (msg.message == WM_LBUTTONUP && smile == 1)
			{
				smile = 0;//左键抬起时，按钮(不管是否是在按钮上抬起)就会弹起，图片渲染为抬起的笑脸键
				if (msg.x > 782 && msg.x < 818 && msg.y > 105 && msg.y < 141)
				{
					break;//只有抬起时的坐标也在笑脸按钮上，跳出内部循环，重新刷新雷区
				}
			}
			if (msg.message == WM_RBUTTONDOWN)
			{
				//右键按下，如果在雷区，就会将点击的坐标转化为二维数组的行列，对该行列进行记录
				if (msg.x < ((800 - EachDifficultyBackground[difficulty].getwidth() / 2) + 8 + colcol * 36) && msg.x >(800 - EachDifficultyBackground[difficulty].getwidth() / 2) + 8 && msg.y < 169 + rowrow * 36 && msg.y > 169)
				{
					rowr = ((msg.y - 169) / 36) + 1;
					colr = ((msg.x - ((800 - EachDifficultyBackground[difficulty].getwidth() / 2) + 8)) / 36) + 1;
					RightButtonPressed = true;//将右键按下状态变量设定为真，即右键已经按下
				}
			}
			if (msg.message == WM_RBUTTONUP && RightButtonPressed)//右键抬起，而且要右键按下状态变量为真
			{
				//右键抬起，如果在雷区，就会将坐标转换为二维数组的行列，然后与上面的行列进行对比，如果相同则进行下面的操作
				if (rowr == ((msg.y - 169) / 36) + 1 && colr == ((msg.x - ((800 - EachDifficultyBackground[difficulty].getwidth() / 2) + 8)) / 36) + 1 && !(face[rowr - 1][colr - 1] == 'x' || face[rowr - 1][colr - 1] == 'L'))
				{
					if (face[rowr - 1][colr - 1] == '_')//如果是未标旗，则进行标旗
					{
						face[rowr - 1][colr - 1] = 'f';
					}
					else if (face[rowr - 1][colr - 1] == 'f')//如果是已标旗，则进行取消标旗
					{
						face[rowr - 1][colr - 1] = '_';
					}
					//这里实现右键点一下标旗，再点一下取消标旗
					RightButtonPressed = false;//将按下状态变量刷新为假
				}
			}
			check = IsGameWin(deep, face, row - 1, col - 1, rowrow, colcol);//检查是否胜利或失败以及游戏是否继续
			if (check == 2)//只要游戏继续，就判断是否连续揭示
			{
				if (deep[row - 1][col - 1] == 0)//揭示的格子是空格(即格子是0，周围八个格子没有地雷)则尝试连续揭示
				{
					LinkChange(deep, face, row - 1, col - 1, rowrow, colcol);//对于这个输入的格子进行连续揭示
				}
			}
		} while (check == 2);//只要check为2则继续，则循环继续，则游戏继续，check为1或0(即赢或输)是退出循环
		if (check == 1)//check为1时胜利
		{
			//胜利时笑脸会变成帅脸
			handsome = 1;//将帅脸状态变量变为1，渲染弹起时的帅脸
			UpdateWin(deep, face, difficulty, rowrow, colcol);//刷新窗口，以使帅脸可见
			while (1)//这时已经胜利，等待点击帅脸刷新或者点击返回健返回
			{
				peekmessage(&msg);//通过循环持续获取操作信息
				if (msg.message == WM_LBUTTONDOWN)//左键按下
				{
					if (msg.x > 782 && msg.x < 818 && msg.y > 105 && msg.y < 141)
					{
						handsome = 2;//如果按到帅脸上，则帅脸状态变量变为2，即渲染为按下的帅脸
					}
					if (msg.x > (800 - EachDifficultyBackground[difficulty].getwidth() / 2) + 8 && msg.x < (800 - EachDifficultyBackground[difficulty].getwidth() / 2) + 44 && msg.y > 105 && msg.y < 141)
					{
						back = 1;//这里时左键在返回按钮上按下，状态变量back变为1，这时按钮会渲染为按下的图片
					}
					UpdateWin(deep, face, difficulty, rowrow, colcol);//刷新窗口，使得这些变化实时显现
				}
				if (msg.message == WM_LBUTTONUP && back == 1)//左键抬起，而且back变量为1
				{
					back = 0;//左键抬起时，按钮(不管是否是在按钮上抬起)就会弹起，图片渲染为抬起的返回键
					UpdateWin(deep, face, difficulty, rowrow, colcol);//刷新窗口，使得这些变化实时显现
					if (msg.x > (800 - EachDifficultyBackground[difficulty].getwidth() / 2) + 8 && msg.x < (800 - EachDifficultyBackground[difficulty].getwidth() / 2) + 44 && msg.y > 105 && msg.y < 141)
					{
						return;//只有抬起时的坐标也在按钮上，才会返回菜单，这里时函数返回，在主函数里还有一个循环来控制游戏返回时会返回菜单
					}
				}
				if (msg.message == WM_LBUTTONUP && handsome == 2)//左键抬起，而且handsome变量为1
				{
					handsome = 1;//左键抬起时，按钮(不管是否是在按钮上抬起)就会弹起，图片渲染为抬起的帅脸
					UpdateWin(deep, face, difficulty, rowrow, colcol);//刷新窗口，使得这些变化实时显现
					if (msg.x > 782 && msg.x < 818 && msg.y > 105 && msg.y < 141)
					{
						break;//只有抬起时的坐标也在笑脸按钮上，跳出内部循环，重新刷新雷区
					}
				}
			}
		}
		else if (check == 0)//check为0时失败
		{
			//失败时要将所有的雷显示出来，点击到的雷的背景为红色，点击到的雷的背景为红色
			for (int i = 0; i < rowrow; i++)
			{
				for (int j = 0; j < colcol; j++)
				{
					if (deep[i][j] == MINE && (face[i][j] == 'x' || face[i][j] == 'L'))
					{
						face[i][j] = 'r';//点击到的雷的背景为红色
					}
					else if (deep[i][j] == MINE && (face[i][j] == '_' || face[i][j] == 'f'))
					{
						face[i][j] = 'b';//点击到的雷的背景为红色
					}
				}
			}
			cry = 1;//将哭脸状态变量改为1，即渲染为弹起的哭脸
			UpdateWin(deep, face, difficulty, rowrow, colcol);//刷新窗口，使得这些变化实时显现
			while (1)//这时已经失败，等待点击哭脸刷新或者点击返回键返回菜单
			{
				peekmessage(&msg);//通过循环持续获取操作信息
				if (msg.message == WM_LBUTTONDOWN)//左键按下
				{
					if (msg.x > 782 && msg.x < 818 && msg.y > 105 && msg.y < 141)
					{
						cry = 2;//如果按到哭脸上，则哭脸状态变量变为2，即渲染为按下的哭脸
					}
					if (msg.x > (800 - EachDifficultyBackground[difficulty].getwidth() / 2) + 8 && msg.x < (800 - EachDifficultyBackground[difficulty].getwidth() / 2) + 44 && msg.y > 105 && msg.y < 141)
					{
						back = 1;//这里时左键在返回按钮上按下，状态变量back变为1，这时按钮会渲染为按下的图片
					}
					UpdateWin(deep, face, difficulty, rowrow, colcol);//刷新窗口，使得这些变化实时显现
				}
				if (msg.message == WM_LBUTTONUP && back == 1)//左键抬起，而且back变量为1
				{
					back = 0;//左键抬起时，按钮(不管是否是在按钮上抬起)就会弹起，图片渲染为抬起的返回键
					UpdateWin(deep, face, difficulty, rowrow, colcol);//刷新窗口，使得这些变化实时显现
					if (msg.x > (800 - EachDifficultyBackground[difficulty].getwidth() / 2) + 8 && msg.x < (800 - EachDifficultyBackground[difficulty].getwidth() / 2) + 44 && msg.y > 105 && msg.y < 141)
					{
						return;//只有抬起时的坐标也在按钮上，才会返回菜单，这里时函数返回，在主函数里还有一个循环来控制游戏返回时会返回菜单
					}
				}
				if (msg.message == WM_LBUTTONUP && cry == 2)//左键抬起，而且handsome变量为1
				{
					cry = 1;//左键抬起时，按钮(不管是否是在按钮上抬起)就会弹起，图片渲染为抬起的哭脸
					UpdateWin(deep, face, difficulty, rowrow, colcol);//刷新窗口，使得这些变化实时显现
					if (msg.x > 782 && msg.x < 818 && msg.y > 105 && msg.y < 141)
					{
						break;//只有抬起时的坐标也在笑脸按钮上，跳出内部循环，重新刷新雷区
					}
				}
			}
		}
	}
}