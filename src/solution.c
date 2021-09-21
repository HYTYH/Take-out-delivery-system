#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "data_struct.h"
#include "MoniTimeLine.h"
#include "PointList.h"
#include "Debug.h"
#include "image.h"
extern int active[100], not_active[100],mode, Mt, At,Rt,Et,Order_Num,in_active,not_inactive,weight_all,weight_last,weight_max,weight_min,weight_maxtime,Deadtime;
extern struct MONI_TIME * moni_time_line;
extern struct ORDER emergency0[2000], emergency1[2000];
extern struct ORDER * Order_Array;
extern struct DELIVER deliver[2000];
extern int emergency0_num, emergency1_num;
extern int adddeliver[100], addnum,DIE,PUNISH,MONEY,DELIVERCOST;



void End(void)
{
	//Show_line();
	int i,time;
	if (mode == 3||mode==4)
	{
		time = FindMaxListTime(addnum);
		if (time > Deadtime)
		{
			time = Deadtime;
		}
		ImageOutPut(time);
	}
	for (i = 0; i < addnum; i++)
	{
		DeleteList(deliver[i].headptr);
	}
	free(Order_Array);
	free(moni_time_line);
	Order_Array = NULL;
	moni_time_line = NULL;
	return;
}
int find_ordernum(void)
{
	int ch;
	int ans = 0;
	while ((scanf("%d", &ch)) != EOF)
	{
		//if(ch=='\n')
		ans++;
		
	}
	
	ans=ans/6;
	rewind(stdin);
	return ans;
}//Debuged!
void Get_Order(struct ORDER * Order_Array, int Order_Num)
{
	int i, id, time, x1, y1, x2, y2;
//	printf("%d\n",Order_Num);
	for (i = 0; i <= Order_Num; i++)
	{
		scanf("%d %d %d %d %d %d", &id, &time, &x1, &y1, &x2, &y2);
//		printf("hhh %d\n",i);
		if (x1 >= 0 && x1 <= 6)
		{
			x1++;
			Order_Array[i].res.loc=0;
		}
		else
		{
			x1--;
			Order_Array[i].res.loc=1;
		}
		if (x2 >= 0 && x2 <= 6)
		{
			x2++;
			Order_Array[i].cus.loc=0;
		}
		else
		{
			x2--;
			Order_Array[i].cus.loc=1;
		}
       
		Order_Array[i].res.id= Order_Array[i].cus.id =Order_Array[i].id = id;
		Order_Array[i].cus.exist_time = Order_Array[i].res.exist_time = Order_Array[i].exist_time = time;
		Order_Array[i].res.x = x1; Order_Array[i].res.y = y1;
		Order_Array[i].cus.x = x2; Order_Array[i].cus.y = y2;
		Order_Array[i].res.type = 0; Order_Array[i].cus.type = 1;
	}
	Et = Order_Array[Order_Num].exist_time;
	
}
void Output(int end)
{
	int time, deliver_num, i, dx, dy,left,right,state;
	deliver_num = moni_time_line[Rt].deliver_num;
	struct POINTLIST * aim[100] = { NULL };
	struct POINT now[100];
	int sign[2000],signnum;
	struct POINTLIST * ptr; 
	//遍历每个骑手，更新“目标点”aim

	for (i = 0; i < deliver_num; i++)
	{
		aim[i] = deliver[i].current;
		now[i].x = deliver[i].locx;
		now[i].y = deliver[i].locy;
	}
	
	for (time = Rt; time < end; time++)
	{
		
		
		if(mode != 3 && mode != 4 && (mode == 0||mode==2|| moni_time_line[time].stay == 1))
		{
		    printf("时间：%d\n钱：%d\n接单数：%d\n完成数：%d；结单：", time, moni_time_line[time].money, moni_time_line[time].order_num, moni_time_line[time].finished);
		    for(i=0;i<moni_time_line[time].finishnum;i++)
		    {
		    	if(i<moni_time_line[time].finishnum-1)
		    	{
		    		printf("%d ",moni_time_line[time].finishid[i]);
				}
				else
				{
					printf("%d",moni_time_line[time].finishid[i]);
				}
			}
			printf("；\n超时数：%d；罚单：",moni_time_line[time].over_time);
			for(i=0;i<moni_time_line[time].punishnum;i++)
		    {
		    	if(i<moni_time_line[time].punishnum-1)
		    	{
		    		printf("%d ",moni_time_line[time].punishid[i]);
				}
				else
				{
					printf("%d",moni_time_line[time].punishid[i]);
				}
			}
			printf("；\n");
     	}


		for (i = 0; i < deliver_num; i++)
		{
			if (mode != 3 && mode != 4 &&(mode==0 || mode==2 || moni_time_line[time].stay == 1))
			{ 
				printf("骑手%d位置：%d，%d；停靠：", i, now[i].x, now[i].y);
			}
			left=right=0;
			
			if(mode!=3&&mode!=4&&aim[i]==NULL&& (mode == 0 || mode == 2 ||  moni_time_line[time].stay == 1))
			{
				printf("；\n");
			}
			//更新目标
			else
			{
				while (aim[i]!=NULL&&time >= aim[i]->point.time)
				{
					if(aim[i]->point.time==time)
					{
						if (aim[i]->point.loc == 0)
						{
							//printf("left\n"); 
							if (aim[i]->point.type == 0)
							{
								left++;
							}
							else
							{
								left += 100000;
							}
						}
						else
						{
							//printf("right!\n");
							if (aim[i]->point.type == 0)
							{
								right++;
							}
							else
							{
								right += 100000;
							}
						}
					}
					aim[i] = aim[i]->next;
				}
				if (mode != 3 && mode != 4&&(mode == 0 || mode == 2 || moni_time_line[time].stay == 1))
				{
					if (left == 0 && right == 0)
					{
						printf("；\n");
					}
					else if (left > 0 && right == 0 || left == 0 && right > 0)//不是那种再中间停留两边
					{

						state = left + right;
						if (state < 100000 && state>0)//是餐馆
						{
							if (now[i].loc == 0)
							{
								printf("餐馆 %d %d；\n", now[i].x - 1, now[i].y);
							}
							else
							{
								printf("餐馆 %d %d；\n", now[i].x + 1, now[i].y);
							}
						}
						else if (state % 100000 == 0)
						{
							//是食客
							if (now[i].loc == 0)
							{
								printf("食客 %d %d；\n", now[i].x - 1, now[i].y);
							}
							else
							{
								printf("食客 %d %d；\n", now[i].x + 1, now[i].y);
							}
						}
						else
						{
							//是餐客 
							if (now[i].loc == 0)
							{
								printf("餐客 %d %d；\n", now[i].x - 1, now[i].y);
							}
							else
							{
								printf("餐客 %d %d；\n", now[i].x + 1, now[i].y);
							}
						}

					}
					else//在中间而且两边停靠
					{
						
						//先看左边
						if (left < 100000)//左边是餐馆
						{
							printf("餐馆 %d %d ", now[i].x - 1, now[i].y);
						}
						else if (left % 100000 == 0)//是食客
						{
							printf("食客 %d %d ", now[i].x - 1, now[i].y);
						}
						else//餐客
						{
							printf("餐客 %d %d ", now[i].x - 1, now[i].y);
						}
						//再看右边
						if (right < 100000)//左边是餐馆
						{
							printf("餐馆 %d %d ；\n", now[i].x + 1, now[i].y);
						}
						else if (right % 100000 == 0)//是食客
						{
							printf("食客 %d %d；\n", now[i].x + 1, now[i].y);
						}
						else//餐客
						{
							printf("餐客 %d %d；\n", now[i].x + 1, now[i].y);
						}
					}
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
	}
	for (i = 0; i < deliver_num; i++)
	{
		deliver[i].locx = now[i].x;
		deliver[i].locy = now[i].y;
	}
}
void Add_new(int start_time)
{
	int i, deliverid;
	deliverid = in_active + not_inactive;

	adddeliver[addnum] = start_time;
	addnum++;
	

	deliver[deliverid].locx = 7;
	deliver[deliverid].locy = 8;
	deliver[deliverid].time_max = 0;
	deliver[deliverid].current = deliver[deliverid].pre = deliver[deliverid].headptr = NULL;
	active[in_active] = deliverid;
	in_active++;
}
void StateChange(int time)
{
	struct POINTLIST * current;
	int i;
	for (i = 0; i < moni_time_line[time].deliver_num; i++)
	{
		current = deliver[i].current;
		while (current != NULL && current->point.time < time)
		{
			deliver[i].pre = current;
			current = current->next;
		}
		deliver[i].current = current;
	}
}
void AddDeliverAssign(struct ORDER order, int time)
{

	Add_new(time);


	Insert(&deliver[active[in_active - 1]].headptr, 0, order.res);
	Insert(&deliver[active[in_active - 1]].headptr, 1, order.cus);
	deliver[active[in_active - 1]].current = deliver[active[in_active - 1]].headptr;

	deliver[active[in_active - 1]].time_max = UpDatePointList(deliver[active[in_active - 1]].headptr, active[in_active - 1]);//插单

	UpdateMoniTimeLine(Rt, Et + DIE+40);

	Output(time);

	StateChange(time);

	UpdateMoniTimeLine(Rt, Et + DIE+40);



}

int Try_Add(struct ORDER order, int deliver_id, int * minres, int * mincus, int * minall, int limit)
{
	int min_all = 99999999, min_last = 99999999;
	int i, j, point_num, dall, dlast;
	struct POINTLIST * baseptr = SaveList(deliver[deliver_id].current, 1);
	struct POINTLIST * buffer;
	point_num = GetPointNum(baseptr);
	for (i = 0; i <= point_num; i++)
	{
		Insert(&baseptr, i, order.res);

		for (j = 1; i + j <= point_num + 1; j++)
		{
			Insert(&baseptr, i + j, order.cus);

			dlast = UpDatePointList(baseptr, deliver_id) - deliver[deliver_id].time_max;
			buffer = baseptr;

			dall = CaculateDall(baseptr, Rt) - CaculateDall(deliver[deliver_id].current, Rt);
			//printf("id:%d %d %d\n",deliver_id, dlast, dall);
			//统计结果
			//更新结果
			if ((((double)(dall*weight_all + dlast * weight_last) / (weight_all + weight_last)) < ((double)(min_all*weight_all + min_last * weight_last) / (weight_all + weight_last))) && IsNoOverTime(baseptr, limit) == 0)
			{
				//更新

				min_last = dlast;
				min_all = dall;
				(*minres) = i;
				(*mincus) = i + j;
			}


			DeletePoint(&baseptr, i + j);
		}
		DeletePoint(&baseptr, i);
	}
	//printf("minres:%d mincus:%d  minlast:%d\n", (*minres), (*mincus), min_last);
	free(baseptr);
	(*minall) = min_all;
	return min_last;
}
int Assign(struct ORDER order, int limit)
{
	int i, min_active_last, min_nonactive_last, min_active_all, min_nonactive_all, min_id_active = -1, min_id_nonactive = -1;
	int minlast, minall;
	int minres_active, mincus_active, minres_nonactive, mincus_nonactive;
	int minres_in_function, mincus_in_function;
	struct POINTLIST * buffer;
	
	//第一步，尝试给可用骑手派单
	for (i = 0, min_active_all = min_active_last = 99999998; i < in_active && min_active_last > 0; i++)
	{
		minlast = Try_Add(order, active[i], &minres_in_function, &mincus_in_function, &minall, limit);
		if ((double)(minlast*weight_last + minall * weight_all) / (weight_all + weight_last) < (double)(min_active_last*weight_last + min_active_all * weight_all) / (weight_all + weight_last))
		{
			minres_active = minres_in_function;
			mincus_active = mincus_in_function;
			min_id_active = active[i];
			min_active_last = minlast;
			min_active_all = minall;
		}

	}


	if (min_active_last < 99999997)
	{
		buffer = SaveList(deliver[min_id_active].current, 1);
		Insert(&buffer, minres_active, order.res);
		Insert(&buffer, mincus_active, order.cus);
		if (deliver[min_id_active].headptr == NULL || deliver[min_id_active].headptr == deliver[min_id_active].current)
		{
			deliver[min_id_active].current = deliver[min_id_active].headptr = buffer;

		}
		else
		{
			DeleteList(deliver[min_id_active].current);
			deliver[min_id_active].pre->next = deliver[min_id_active].current = buffer;
		}

		deliver[min_id_active].time_max = UpDatePointList(deliver[min_id_active].current, min_id_active);



		return 1;
	}
	//第二步
	for (i = 0, min_nonactive_all = min_nonactive_last = 99999999; i < not_inactive&&min_nonactive_last>0; i++)
	{
		minlast = Try_Add(order, not_active[i], &minres_in_function, &mincus_in_function, &minall, limit);
		if ((double)(minlast*weight_last + minall * weight_all) / (weight_all + weight_last) < (double)(min_nonactive_last*weight_last + min_nonactive_all * weight_all) / (weight_all + weight_last))
		{
			minres_nonactive = minres_in_function;
			mincus_nonactive = mincus_in_function;
			min_id_nonactive = not_active[i];
			min_nonactive_last = minlast;
			min_nonactive_all = minall;
		}
	}
	if (min_nonactive_last < 99999998)
	{

		buffer = SaveList(deliver[min_id_nonactive].current, 1);
		Insert(&buffer, minres_nonactive, order.res);
		Insert(&buffer, mincus_nonactive, order.cus);
		if (deliver[min_id_nonactive].headptr == NULL || deliver[min_id_nonactive].headptr == deliver[min_id_nonactive].current)
		{
			deliver[min_id_nonactive].current = deliver[min_id_nonactive].headptr = buffer;

		}
		else
		{
			DeleteList(deliver[min_id_nonactive].current);
			deliver[min_id_nonactive].pre->next = deliver[min_id_nonactive].current = buffer;
		}

		deliver[min_id_nonactive].time_max = UpDatePointList(deliver[min_id_nonactive].current, min_id_nonactive);




		return 0;
	}
	return -1;
}
void PushIntoNonactive(int num)
{
	int i;
	not_active[not_inactive] = active[num];
	not_inactive++;
	for (i = num; i < in_active - 1; i++)
	{
		active[i] = active[i + 1];
	}
	in_active--;
}
void PushIntoActive(int num)
{
	int i;
	active[in_active] = not_active[num];
	in_active++;
	for (i = num; i < not_inactive - 1; i++)
	{
		not_active[i] = not_active[i + 1];
	}
	not_inactive--;
}
void PushIntoEmergency0(int num)
{
	int i;
	emergency0[emergency0_num] = emergency1[num];
	emergency0_num++;
	for (i = num; i < emergency1_num - 1; i++)
	{
		emergency1[i] = emergency1[i + 1];
	}
	emergency1_num--;
}
void PushIntoEmergency1(int num)
{
	int i;
	emergency1[emergency1_num] = emergency0[num];
	emergency1_num++;
	for (i = num; i < emergency0_num - 1; i++)
	{
		emergency0[i] = emergency0[i + 1];
	}
	emergency0_num--;
}
void UpdateDeliverState(void)
{
	int i;
	for (i = 0; i < in_active; i++)
	{
		if (CaculateMaxTime(deliver[active[i]].current) > weight_max)
		{
			PushIntoNonactive(i);
			//printf("hhhh\n");
			i--;
		}
	}
	for (i = 0; i < not_inactive; i++)
	{
		if (CaculateMaxTime(deliver[not_active[i]].current) < weight_min)
		{
			//printf("qqq\n");
			PushIntoActive(i);
			i--;
		}
	}

}
void UpdataEmergency(int time)
{
	int i;
	for (i = 0; i < emergency1_num; i++)
	{
		if (time - emergency1[i].exist_time >= PUNISH+1)
		{
			PushIntoEmergency0(i);
			i--;
		}
	}
	
}
void Init(void)
{
	int i;
	for (i = 0; i < 200; i++)
	{
		deliver[i].current = deliver[i].headptr = deliver[i].pre = NULL;
	}

	
	
	
	Rt = At = 0;
	in_active = 0;
	not_inactive = 0;
	addnum = 0;
	Deadtime = 999999999;
	emergency0_num = emergency1_num = 0;
	Order_Num = find_ordernum() - 1;
	Order_Array = (struct ORDER *)malloc(sizeof(struct ORDER)*(Order_Num + 1));
	Get_Order(Order_Array, Order_Num);
	moni_time_line = (struct MONI_TIME *)malloc(sizeof(struct MONI_TIME)*(Et + DIE+42));
	moni_time_line[0].deliver_num = moni_time_line[0].finished = moni_time_line[0].order_num = moni_time_line[0].over_time = 0;
	moni_time_line[0].money = MONEY;

	InitMoniTimeLine(Order_Array, Order_Num, Et + DIE+40);
	weight_maxtime = (int)((double)Et * 100 / (double)Order_Num);
	for(i=0;i<MONEY/DELIVERCOST;i++)
	{
	    Add_new(0);
    }

}

void Solve(char * input_name, char * output_name)
{

	int i, j, k, state;
	int count = 0;
	FILE *fp_in;
	fp_in = freopen(input_name, "r", stdin);
	if (fp_in == NULL)
	{

		printf("输入错误！找不到文件 ""sales.txt"" ！\n");
		return;
	}

	
	if (mode == 0||mode==2)
	{
		freopen(output_name, "w", stdout);
	}

	

	Init();


	for (i = 0; i <= Order_Num || emergency0_num > 0 || emergency1_num > 0; i++)
	{

		if (i <= Order_Num)
		{
			UpdateMoniTimeLine(Rt, Et + DIE + 40);
			Mt = Order_Array[i].exist_time;
			
			if (Mt >= Deadtime)
			{
				
				Output(Mt + 1);
				//Show_line();
				//("Bankrupt\n");
				End();
				return;
			}
			if (moni_time_line[Mt].money < 0)
			{
				
				for (j = 0; j < Et + DIE + 40&&moni_time_line[j].money>=0; j++)
				{

				}
				
				Output(j + 1);
				//Show_line();
				//("Bankrupt\n");
				End();
				return;
			}
			
		}

		if (emergency0_num > 0)
		{
			for (j = 0; j < emergency0_num; j++)
			{
				if ((state = Assign(emergency0[j], PUNISH)) == -1)
				{

					if (At >= Rt && At <= Mt)
					{
						AddDeliverAssign(emergency0[j], Mt);
						
						for (k = j; k < emergency0_num - 1; k++)
						{
							emergency0[k] = emergency0[k + 1];
						}
						emergency0_num--;
						Rt = Mt;
						UpdateDeliverState();
						UpdateMoniTimeLine(Rt, Et + DIE+40);

					}
					else
					{
						if (Assign(emergency0[j], DIE) >= 0)
						{
							for (k = j; k < emergency0_num - 1; k++)
							{
								emergency0[k] = emergency0[k + 1];
							}
							emergency0_num--;
							UpdateDeliverState();
							UpdateMoniTimeLine(Rt, Et + DIE+40);
						}
					}

				}
				else
				{
					for (k = j; k < emergency0_num - 1; k++)
					{
						emergency0[k] = emergency0[k + 1];
					}
					emergency0_num--;
				}
			}
		}
		if (emergency1_num > 0)
		{
			for (j = 0; j < emergency1_num; j++)
			{
				if ((state = Assign(emergency1[j], PUNISH)) == -1)
				{

					if (At >= Rt && At <= Mt)
					{
						AddDeliverAssign(emergency1[j], Mt);
						//printf("Push out! %d\n", emergency1[j].id);
						for (k = j; k < emergency1_num - 1; k++)
						{
							emergency1[k] = emergency1[k + 1];
						}
						emergency1_num--;
						Rt = Mt;
						UpdateDeliverState();
						UpdateMoniTimeLine(Rt, Et + DIE+40);
					}
				}
				else
				{
					for (k = j; k < emergency1_num - 1; k++)
					{
						emergency1[k] = emergency1[k + 1];
					}
					emergency1_num--;
				}
			}
		}


		if (i <= Order_Num)
		{
			if ((state = Assign(Order_Array[i], PUNISH)) == -1)
			{

				if (At >= Rt && At <= Mt)
				{
					AddDeliverAssign(Order_Array[i], Mt);
					UpdateMoniTimeLine(Rt, Et + DIE+40);
					//printf("hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh\n");
					Rt = Mt;
				}
				else if (At >= Rt && At - Mt <= PUNISH - (Distance(7, 8, 998 + Mt, Order_Array[i].res) + Distance(Order_Array->res.x, Order_Array[i].res.y, 998 + Mt, Order_Array[i].cus)))
				{
					//printf("into e1:%d\n", Order_Array[i].id);
					emergency1[emergency1_num] = Order_Array[i];
					emergency1_num++;
					//printf("%d\n", emergency1_num);
				}
				else
				{
					if (Assign(Order_Array[i], DIE) == -1)
					{
						emergency0[emergency0_num] = Order_Array[i];
						emergency0_num++;
					}
				}
			}
		}


		if (i <= Order_Num && Mt - Rt >= weight_maxtime)
		{

            for(;moni_time_line[Mt].money>=DELIVERCOST+150&&addnum<=45;moni_time_line[Mt].money-=DELIVERCOST)
            {
            	Add_new(Mt); 
			} //若不是无脑加骑手，删去这个for循环。 


			UpdateDeliverState();

			UpdateMoniTimeLine(Rt, Et + DIE+40);

			UpdataEmergency(Mt);

			Output(Mt);

			StateChange(Mt);



			Rt = Mt;
		}



		UpdateDeliverState();

		UpdateMoniTimeLine(Rt, Et + DIE+40);

		UpdataEmergency(Mt);


		//Show_line();

		if ((mode==2||mode==0 )&& i<=Order_Num&&(Mt) > count * ((Et+DIE)/6) )
		{
			count++;
			freopen("CON", "w", stdout);
			printf("程序正常运行中 当前文件部分处理进度 %.2lf %%\n\n", ((double)Mt / (Et + 80)) * 100);
			freopen(output_name, "a+", stdout);
		}

		

	}

	//Show_line();
	//printf("jhhhh\n");

	Et=FindMaxListTime(addnum);
	if(Et>Deadtime)
	{
		Et=Deadtime;
	}

	Output(Et + 1);

	End();
	
	fclose(fp_in);

}


