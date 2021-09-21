#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <time.h> 
#include "data_struct.h"
extern int active[100], not_active[100], Mt,mode, At,Rt,Et,Order_Num,in_active,not_inactive,weight_all,weight_last,weight_max,weight_min,weight_maxtime,Deadtime;
extern struct MONI_TIME * moni_time_line;
extern struct ORDER emergency0[2000], emergency1[2000];
extern struct ORDER * Order_Array;
extern struct DELIVER deliver[2000];
extern int emergency0_num, emergency1_num;
extern int adddeliver[100], addnum,DIE,PUNISH,MONEY;
void Image(int sign[],int signnum,struct POINT * deliverpoint,int pointnum)
{
	clock_t start, end;
	start = clock();
	
	int i,j,k,x,y;
	char str[100][100][100];
	char a[100];
	char b[100];
	char c[100];
	char d[100];
	char e[100];
	char f[100]; 
	char g[100]; 


	strcpy(a,"    \0");
	strcpy(b,"----\0");
	strcpy(d,"餐馆\0");
	strcpy(e,"食客\0"); 
	strcpy(f,"骑手\0"); 
	strcpy(g,"餐客\0");

	for(i=0;i<=34;i=i+2)
	{
		for(j=0;j<=16;j=j+2)
		{
			strcpy(str[i][j],b);
		}
	}
	
	for(i=0;i<=34;i=i+2)
	{
		for(j=1;j<=16;j=j+2)
		{
			strcpy(str[i][j],a);
		}
	}
	
	for(i=1;i<=34;i=i+4)
	{
		for(j=0;j<=16;j++)
		{
			strcpy(str[i][j],a);
		}
	}

	for(i=3;i<=34;i=i+4)
	{
		for(j=0;j<=16;j++)
		{
			strcpy(str[i][j],a);
		}
	}

	//操作： 
	//printf("qq0\n");
	for(i=0;i<signnum;i++)
	{
		if(Order_Array[0].id==1)
		{
	    	x=Order_Array[sign[i]-1].res.x;
    		y=Order_Array[sign[i]-1].res.y;
    		if(Order_Array[sign[i]-1].res.loc==0)
    		{
    			x--;
    		}
     		else
	    	{
	    	    x++;
	    	}
    	}
    	else
    	{
        	x=Order_Array[sign[i]].res.x;
    		y=Order_Array[sign[i]].res.y;
    		if(Order_Array[sign[i]].res.loc==0)
		    {
	    		x--;
	    	}
	    	else
	    	{
     		    x++;
    		}
		}
		
		strcpy(str[2*y+1][x],d);
	}
	//printf("qq1\n");
	for(i=0;i<signnum;i++)
	{
		if(Order_Array[0].id==1)
		{
	    	x=Order_Array[sign[i]-1].cus.x;
    		y=Order_Array[sign[i]-1].cus.y;
    		if(Order_Array[sign[i]-1].cus.loc==0)
    		{
    			x--;
    		}
     		else
	    	{
	    	    x++;
	    	}
    	}
    	else
    	{
        	x=Order_Array[sign[i]].cus.x;
    		y=Order_Array[sign[i]].cus.y;
    		if(Order_Array[sign[i]].cus.loc==0)
		    {
	    		x--;
	    	}
	    	else
	    	{
     		    x++;
    		}
		}
		
		if(strcmp(str[2*y+1][x],"餐馆\0")==0)
		{
			strcpy(str[2*y+1][x],g);
		}
		else
		{
			strcpy(str[2*y+1][x],e);
		}
	}
	//printf("qq2\n");
	for(i=0;i<pointnum;i++)
	{
		x=deliverpoint[i].x;
		y=deliverpoint[i].y;
		strcpy(str[2*y+1][x],f);
	}
	//printf("qq3\n");
	end=clock();
	while((double)(end - start) / CLOCKS_PER_SEC<=0.15)
	{
		end=clock();
	}
	
	system("cls");
	
	printf("+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+\n",str[0][0],str[0][1],str[0][2],str[0][3],str[0][4],str[0][5],str[0][6],str[0][7],str[0][8],str[0][9],str[0][10],str[0][11],str[0][12],str[0][13],str[0][14],str[0][15],str[0][16]);
	printf("|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|\n",str[1][0],str[1][1],str[1][2],str[1][3],str[1][4],str[1][5],str[1][6],str[1][7],str[1][8],str[1][9],str[1][10],str[1][11],str[1][12],str[1][13],str[1][14],str[1][15],str[1][16]);
	printf("+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+\n",str[2][0],str[2][1],str[2][2],str[2][3],str[2][4],str[2][5],str[2][6],str[2][7],str[2][8],str[2][9],str[2][10],str[2][11],str[2][12],str[2][13],str[2][14],str[2][15],str[2][16]);
	printf(" %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s \n",str[3][0],str[3][1],str[3][2],str[3][3],str[3][4],str[3][5],str[3][6],str[3][7],str[3][8],str[3][9],str[3][10],str[3][11],str[3][12],str[3][13],str[3][14],str[3][15],str[3][16]);
	printf("+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+\n",str[4][0],str[4][1],str[4][2],str[4][3],str[4][4],str[4][5],str[4][6],str[4][7],str[4][8],str[4][9],str[4][10],str[4][11],str[4][12],str[4][13],str[4][14],str[4][15],str[4][16]);
	printf("|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|\n",str[5][0],str[5][1],str[5][2],str[5][3],str[5][4],str[5][5],str[5][6],str[5][7],str[5][8],str[5][9],str[5][10],str[5][11],str[5][12],str[5][13],str[5][14],str[5][15],str[5][16]);
	printf("+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+\n",str[6][0],str[6][1],str[6][2],str[6][3],str[6][4],str[6][5],str[6][6],str[6][7],str[6][8],str[6][9],str[6][10],str[6][11],str[6][12],str[6][13],str[6][14],str[6][15],str[6][16]);
	printf(" %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s \n",str[7][0],str[7][1],str[7][2],str[7][3],str[7][4],str[7][5],str[7][6],str[7][7],str[7][8],str[7][9],str[7][10],str[7][11],str[7][12],str[7][13],str[7][14],str[7][15],str[7][16]);
	printf("+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+\n",str[8][0],str[8][1],str[8][2],str[8][3],str[8][4],str[8][5],str[8][6],str[8][7],str[8][8],str[8][9],str[8][10],str[8][11],str[8][12],str[8][13],str[8][14],str[8][15],str[8][16]);
	printf("|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|\n",str[9][0],str[9][1],str[9][2],str[9][3],str[9][4],str[9][5],str[9][6],str[9][7],str[9][8],str[9][9],str[9][10],str[9][11],str[9][12],str[9][13],str[9][14],str[9][15],str[9][16]);
	printf("+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+\n",str[10][0],str[10][1],str[10][2],str[10][3],str[10][4],str[10][5],str[10][6],str[10][7],str[10][8],str[10][9],str[10][10],str[10][11],str[10][12],str[10][13],str[10][14],str[10][15],str[10][16]);
	printf(" %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s \n",str[11][0],str[11][1],str[11][2],str[11][3],str[11][4],str[11][5],str[11][6],str[11][7],str[11][8],str[11][9],str[11][10],str[11][11],str[11][12],str[11][13],str[11][14],str[11][15],str[11][16]);
	printf("+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+\n",str[12][0],str[12][1],str[12][2],str[12][3],str[12][4],str[12][5],str[12][6],str[12][7],str[12][8],str[12][9],str[12][10],str[12][11],str[12][12],str[12][13],str[12][14],str[12][15],str[12][16]);
	printf("|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|\n",str[13][0],str[13][1],str[13][2],str[13][3],str[13][4],str[13][5],str[13][6],str[13][7],str[13][8],str[13][9],str[13][10],str[13][11],str[13][12],str[13][13],str[13][14],str[13][15],str[13][16]);
	printf("+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+\n",str[14][0],str[14][1],str[14][2],str[14][3],str[14][4],str[14][5],str[14][6],str[14][7],str[14][8],str[14][9],str[14][10],str[14][11],str[14][12],str[14][13],str[14][14],str[14][15],str[14][16]);
	printf(" %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s \n",str[15][0],str[15][1],str[15][2],str[15][3],str[15][4],str[15][5],str[15][6],str[15][7],str[15][8],str[15][9],str[15][10],str[15][11],str[15][12],str[15][13],str[15][14],str[15][15],str[15][16]);
	printf("+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+\n",str[16][0],str[16][1],str[16][2],str[16][3],str[16][4],str[16][5],str[16][6],str[16][7],str[16][8],str[16][9],str[16][10],str[16][11],str[16][12],str[16][13],str[16][14],str[16][15],str[16][16]);
	printf("|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|\n",str[17][0],str[17][1],str[17][2],str[17][3],str[17][4],str[17][5],str[17][6],str[17][7],str[17][8],str[17][9],str[17][10],str[17][11],str[17][12],str[17][13],str[17][14],str[17][15],str[17][16]);
	printf("+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+\n",str[18][0],str[18][1],str[18][2],str[18][3],str[18][4],str[18][5],str[18][6],str[18][7],str[18][8],str[18][9],str[18][10],str[18][11],str[18][12],str[18][13],str[18][14],str[18][15],str[18][16]);
	printf(" %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s \n",str[19][0],str[19][1],str[19][2],str[19][3],str[19][4],str[19][5],str[19][6],str[19][7],str[19][8],str[19][9],str[19][10],str[19][11],str[19][12],str[19][13],str[19][14],str[19][15],str[19][16]);
	printf("+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+\n",str[20][0],str[20][1],str[20][2],str[20][3],str[20][4],str[20][5],str[20][6],str[20][7],str[20][8],str[20][9],str[20][10],str[20][11],str[20][12],str[20][13],str[20][14],str[20][15],str[20][16]);
	printf("|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|\n",str[21][0],str[21][1],str[21][2],str[21][3],str[21][4],str[21][5],str[21][6],str[21][7],str[21][8],str[21][9],str[21][10],str[21][11],str[21][12],str[21][13],str[21][14],str[21][15],str[21][16]);
	printf("+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+\n",str[22][0],str[22][1],str[22][2],str[22][3],str[22][4],str[22][5],str[22][6],str[22][7],str[22][8],str[22][9],str[22][10],str[22][11],str[22][12],str[22][13],str[22][14],str[22][15],str[22][16]);
	printf(" %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s \n",str[23][0],str[23][1],str[23][2],str[23][3],str[23][4],str[23][5],str[23][6],str[23][7],str[23][8],str[23][9],str[23][10],str[23][11],str[23][12],str[23][13],str[23][14],str[23][15],str[23][16]);
	printf("+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+\n",str[24][0],str[24][1],str[24][2],str[24][3],str[24][4],str[24][5],str[24][6],str[24][7],str[24][8],str[24][9],str[24][10],str[24][11],str[24][12],str[24][13],str[24][14],str[24][15],str[24][16]);
	printf("|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|\n",str[25][0],str[25][1],str[25][2],str[25][3],str[25][4],str[25][5],str[25][6],str[25][7],str[25][8],str[25][9],str[25][10],str[25][11],str[25][12],str[25][13],str[25][14],str[25][15],str[25][16]);
	printf("+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+\n",str[26][0],str[26][1],str[26][2],str[26][3],str[26][4],str[26][5],str[26][6],str[26][7],str[26][8],str[26][9],str[26][10],str[26][11],str[26][12],str[26][13],str[26][14],str[26][15],str[26][16]);
	printf(" %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s \n",str[27][0],str[27][1],str[27][2],str[27][3],str[27][4],str[27][5],str[27][6],str[27][7],str[27][8],str[27][9],str[27][10],str[27][11],str[27][12],str[27][13],str[27][14],str[27][15],str[27][16]);
	printf("+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+\n",str[28][0],str[28][1],str[28][2],str[28][3],str[28][4],str[28][5],str[28][6],str[28][7],str[28][8],str[28][9],str[28][10],str[28][11],str[28][12],str[28][13],str[28][14],str[28][15],str[28][16]);
	printf("|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|\n",str[29][0],str[29][1],str[29][2],str[29][3],str[29][4],str[29][5],str[29][6],str[29][7],str[29][8],str[29][9],str[29][10],str[29][11],str[29][12],str[29][13],str[29][14],str[29][15],str[29][16]);
	printf("+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+\n",str[30][0],str[30][1],str[30][2],str[30][3],str[30][4],str[30][5],str[30][6],str[30][7],str[30][8],str[30][9],str[30][10],str[30][11],str[30][12],str[30][13],str[30][14],str[30][15],str[30][16]);
	printf(" %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s \n",str[31][0],str[31][1],str[31][2],str[31][3],str[31][4],str[31][5],str[31][6],str[31][7],str[31][8],str[31][9],str[31][10],str[31][11],str[31][12],str[31][13],str[31][14],str[31][15],str[31][16]);
	printf("+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+\n",str[32][0],str[32][1],str[32][2],str[32][3],str[32][4],str[32][5],str[32][6],str[32][7],str[32][8],str[32][9],str[32][10],str[32][11],str[32][12],str[32][13],str[32][14],str[32][15],str[32][16]);
	printf("|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|\n",str[33][0],str[33][1],str[33][2],str[33][3],str[33][4],str[33][5],str[33][6],str[33][7],str[33][8],str[33][9],str[33][10],str[33][11],str[33][12],str[33][13],str[33][14],str[33][15],str[33][16]);
	printf("+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+%s+\n",str[34][0],str[34][1],str[34][2],str[34][3],str[34][4],str[34][5],str[34][6],str[34][7],str[34][8],str[34][9],str[34][10],str[34][11],str[34][12],str[34][13],str[34][14],str[34][15],str[34][16]);
	
	
	
}

void ImageOutPut(int end)
{
	int time, deliver_num, i, dx, dy, left, right, state;
	clock_t start1, end1;
	struct POINTLIST * aim[100] = { NULL };
	struct POINT now[100];
	int sign[20000],signnum,pointnum;
	struct POINT deliverloc[200];
	struct POINTLIST * ptr; 
	//遍历每个骑手，更新“目标点”aim
	
	for (i = 0; i < addnum; i++)
	{
		aim[i] = deliver[i].headptr;
		now[i].x = 7;
		now[i].y = 8;
	}
	
	for (time = 0; time <= end+1; time++)
	{
		start1=clock();
		signnum=pointnum=0;
		deliver_num=moni_time_line[time].deliver_num;
		//printf("%d\n",deliver_num);
		for(i=0,signnum=0;i<deliver_num;i++)
		{
			for(ptr=deliver[i].headptr;ptr!=NULL;ptr=ptr->next)
			{
				if(ptr->point.type==1&&ptr->point.exist_time<=time&&ptr->point.time>=time)
				{
					sign[signnum]=ptr->point.id;
					signnum++;
				}
			}
		}
		
		for (i = 0; i < deliver_num; i++)
		{
		
			deliverloc[pointnum].x=now[i].x;
			deliverloc[pointnum].y=now[i].y;
			pointnum++;
			
			
			//更新目标
			if (aim[i] != NULL)
			{
				while (aim[i]!=NULL&&time >= aim[i]->point.time)
				{
					aim[i] = aim[i]->next;
				}





				if (aim[i] != NULL)
				{

					if (aim[i]->point.y == now[i].y)
					{
						if (aim[i]->point.x > now[i].x)
						{
							if (now[i].y != 0)
							{
								now[i].x++;
								now[i].y--;
							}
							else
							{
								now[i].x++;
								now[i].y++;
							}
						}
						else if (aim[i]->point.x < now[i].x)
						{
							if (now[i].y != 0)
							{
								now[i].x--;
								now[i].y--;
							}
							else
							{
								now[i].x--;
								now[i].y++;
							}
						}
					}
					else if (abs(now[i].y - aim[i]->point.y) == 1 && abs(now[i].x - aim[i]->point.x) > 2)
					{
						if (now[i].x - aim[i]->point.x > 2)
						{
							now[i].x -= 2;
						}
						else
						{
							now[i].x += 2;
						}
					}
					else
					{
						if (now[i].x - aim[i]->point.x == 0)
						{
							dy = 2; dx = 0;
						}
						else
						{
							dx = dy = 1;
						}
						if (now[i].x < aim[i]->point.x)
						{
							now[i].x += dx;
						}
						else if (now[i].x > aim[i]->point.x)
						{
							now[i].x -= dx;
						}

						if (now[i].y < aim[i]->point.y)
						{
							now[i].y += dy;
						}
						else if (now[i].y > aim[i]->point.y)
						{
							now[i].y -= dy;
						}
					}
				}
			}
		}
		
		end1=clock();
		
		if (moni_time_line[time].stay == 1 || mode == 4)
		{
			//printf("haaa\n");
			while ((double)(end1 - start1) / CLOCKS_PER_SEC <= 0.4)
			{
				end1 = clock();
			}
			//printf("asddjakldaskl!!!\n %d\n",Deadtime);
			if(time>Deadtime)
			{
				return;
			}
		//	printf("hh\n");


			Image(sign, signnum, deliverloc, pointnum);

			printf("时间：%d 钱：%d  \n接单数：%d 完成数：%d 超时数：%d \n", time, moni_time_line[time].money, moni_time_line[time].order_num, moni_time_line[time].finished, moni_time_line[time].over_time);

		}
		
	}
	for (i = 0; i < deliver_num; i++)
	{
		deliver[i].locx = now[i].x;
		deliver[i].locy = now[i].y;
	}
}


