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
	

	//��������5�������Լ� mode:ģʽ 0Ϊ�ļ���� 1Ϊ����̨��� 2Ϊ �����к��ļ�ͬʱ��� 
	weight_all = 3; weight_last = 7;
	weight_max = 20; weight_min = 10;
	MONEY=1000;PUNISH=30;DIE=60;DELIVERCOST=300;
	
	if(freopen("SETS.txt","r",stdin)==NULL)
	{
		printf("�޷��ҵ������ļ� SETS.txt ��\n����ΪĬ�����ݣ�\n\n");
	}
	else
	{
	scanf("%d %d %d %d",&PUNISH,&DIE,&MONEY,&DELIVERCOST);
	weight_min=PUNISH/3;
	weight_max=2*PUNISH/3;
	printf("�����ļ���SETS.txt����ȡ��ϣ� ��ʱ%d �ϵ�%d ��ʼ�ʽ�%d ������������%d\n\n",PUNISH,DIE,MONEY,DELIVERCOST);
	freopen("CON","r",stdin);
    }
	printf("��ѡ������ģʽ��\n0Ϊ�ļ����(ÿ��ʱ�䵥λ���)\n1Ϊ����̨���(ͣ�����)\n2Ϊ����̨���ļ�ͬʱ���(���������Ϊÿ��ʱ�����һ�ζ���ͣ�����)\n3Ϊͼ�λ��������(ÿ��ͣ�����)\n4Ϊͼ�λ��������(ÿ��ʱ�䵥λ���)\n\n");
	scanf("%d",&mode); getchar();
	strcpy(input_name, "sales.txt\0");
	strcpy(output_name, "output.txt\0");
	
	while(mode<0||mode>4)
	{
		printf("ģʽѡ�����������ѡ�����ģʽ��\n");
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

		
    printf("\n\n�����Ѿ�����,��ʱ�� %.3lf  ��. \n", (double)(end - start) / CLOCKS_PER_SEC);
		
	getch();
	return 0;
}


