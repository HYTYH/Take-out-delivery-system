#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include "solution.h"
#include "data_struct.h"
int active[100], not_active[100],mode, Mt, At,Rt,Et,Order_Num,in_active,not_inactive,weight_all,weight_last,weight_max,weight_min,weight_maxtime,Deadtime;
struct MONI_TIME * moni_time_line;
struct ORDER emergency0[2000], emergency1[2000];
struct ORDER * Order_Array;
struct DELIVER deliver[2000];
int emergency0_num, emergency1_num;
int adddeliver[100], addnum;
int PUNISH,DIE,MONEY,DELIVERCOST;
int main()
{
	system("color 75");
	char input_name[115],output_name[115];
	char name[100];
	
	
	clock_t start, end;
	start = clock();
	
	int i,j;
	

	//操作区：5个参数以及 mode:模式 0为文件输出 1为控制台输出 2为 命令行和文件同时输出 
	weight_all = 3; weight_last = 7;
	weight_max = 20; weight_min = 10;
	MONEY=1000;PUNISH=30;DIE=60;DELIVERCOST=300;
	
	if(freopen("SETS.txt","r",stdin)==NULL)
	{
		printf("无法找到配置文件 SETS.txt ！\n设置为默认数据！\n\n");
	}
	else
	{
	scanf("%d %d %d %d",&PUNISH,&DIE,&MONEY,&DELIVERCOST);
	weight_min=PUNISH/3;
	weight_max=2*PUNISH/3;
	printf("配置文件“SETS.txt”读取完毕！ 罚时%d 废单%d 起始资金%d 购买骑手消耗%d\n\n",PUNISH,DIE,MONEY,DELIVERCOST);
	freopen("CON","r",stdin);
    }
	printf("请选择运行模式！\n0为文件输出(每个时间单位输出)\n1为控制台输出(停靠输出)\n2为控制台和文件同时输出(命令行输出为每个时间更新一次而非停靠输出)\n3为图形化界面输出(每次停留输出)\n4为图形化界面输出(每个时间单位输出)\n\n");
	scanf("%d",&mode); getchar();
	strcpy(input_name, "sales.txt\0");
	strcpy(output_name, "output.txt\0");
	
	while(mode<0||mode>4)
	{
		printf("模式选择错误！请重新选择程序模式！\n");
		scanf("%d",&mode); getchar();
	}
	system("cls");
	
	Solve(input_name, output_name);
	freopen("CON", "w", stdout);
	freopen("CON", "r", stdin);
	
	
	if(mode==2)
	{
		strcpy(input_name,output_name);
		freopen(input_name,"r",stdin);
		i=0; 
		while(gets(name)!=NULL)
		{
			puts(name);
		}
		freopen("CON","r",stdin);
	}	
		
	

 

	end = clock();

		
    printf("\n\n程序已经结束,用时： %.3lf  秒. \n", (double)(end - start) / CLOCKS_PER_SEC);
		
	getch();
	return 0;
}


