#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "data_struct.h"
extern int active[100], not_active[100],mode, Mt, At,Rt,Et,Order_Num,in_active,not_inactive,weight_all,weight_last,weight_max,weight_min,weight_maxtime,Deadtime;
extern struct MONI_TIME * moni_time_line;
extern struct ORDER emergency0[2000], emergency1[2000];
extern struct ORDER * Order_Array;
extern struct DELIVER deliver[2000];
extern int emergency0_num, emergency1_num;
extern int adddeliver[100], addnum,DIE,PUNISH,MONEY,DELIVERCOST;
void UpdateMoniTimeLine(int time, int end)
{
	int i, deliver_num = moni_time_line[time].deliver_num, punish, die=999999999, die_time = 999999999;
	struct POINTLIST * current = NULL;
	//buffer = moni_time_line[i].money;
	for (i = 0; i <= end; i++)
	{
		moni_time_line[i].stay=moni_time_line[i].finishnum=moni_time_line[i].punishnum=moni_time_line[i].deliver_num = moni_time_line[i].money = moni_time_line[i].finished = moni_time_line[i].over_time = 0;
	}
	moni_time_line[0].money = MONEY;
	

	for (i = 0; i < deliver_num; i++)
	{
		for (current = deliver[i].headptr; current != NULL; current = current->next)
		{
			moni_time_line[current->point.time].stay = 1;
			if (current->point.type == 1)
			{
				moni_time_line[current->point.time].finished++;
				moni_time_line[current->point.time].finishid[moni_time_line[current->point.time].finishnum]=current->point.id;
				moni_time_line[current->point.time].finishnum++;

				if (current->point.time - current->point.exist_time <= PUNISH)
				{
					moni_time_line[current->point.time].money += 10;
				/*	moni_time_line[current->point.time].finished++;
					moni_time_line[current->point.time].finishid[moni_time_line[current->point.time].finishnum]=current->point.id;
					moni_time_line[current->point.time].finishnum++;*/
				}
				else if (current->point.time - current->point.exist_time <= DIE)
				{
					moni_time_line[current->point.exist_time + PUNISH+1].money -= 50;
					moni_time_line[current->point.exist_time + PUNISH+1].over_time++;
					moni_time_line[current->point.exist_time + PUNISH+1].punishid[moni_time_line[current->point.exist_time + PUNISH+1].punishnum]=current->point.id;
					moni_time_line[current->point.exist_time + PUNISH+1].punishnum++;
					
				}
				else
				{
					moni_time_line[current->point.exist_time + PUNISH+1].money -= 50;
					moni_time_line[current->point.exist_time + PUNISH+1].over_time++;
					moni_time_line[current->point.exist_time + PUNISH+1].punishid[moni_time_line[current->point.exist_time + PUNISH+1].punishnum]=current->point.id;
					moni_time_line[current->point.exist_time + PUNISH+1].punishnum++;
					if (current->point.exist_time + DIE+1 < die_time)
					{
						die_time = current->point.exist_time + DIE+1;
					}
				}

			}
		}
	}
	for (i = 0; i < emergency0_num; i++)
	{
		punish = emergency0[i].exist_time + PUNISH+1;
		die = emergency0[i].exist_time + DIE+1;
		

		moni_time_line[punish].money -= 50;
		moni_time_line[punish].over_time++;
		moni_time_line[punish].punishid[moni_time_line[punish].punishnum]=emergency0[i].id;
		moni_time_line[punish].punishnum++;

		if (die < die_time)
		{
			die_time = die;
		}
	}
	for (i = 0; i < emergency1_num; i++)
	{
		punish = emergency1[i].exist_time + PUNISH+1;
		punish = emergency1[i].exist_time + DIE+1;

		moni_time_line[punish].money -= 50;
		moni_time_line[punish].over_time++;
		moni_time_line[punish].punishid[moni_time_line[punish].punishnum]=emergency1[i].id;
		moni_time_line[punish].punishnum++;

		if (die < die_time)
		{
			die_time = die;
		}
	}
	for (i = 0; i < addnum; i++)
	{

		moni_time_line[adddeliver[i]].money -= DELIVERCOST;
		moni_time_line[adddeliver[i]].deliver_num++;
	}
	for (i = 1; i <= end; i++)
	{
		moni_time_line[i].deliver_num += moni_time_line[i - 1].deliver_num;
		moni_time_line[i].finished += moni_time_line[i - 1].finished;
		moni_time_line[i].money += moni_time_line[i - 1].money;
		moni_time_line[i].over_time += moni_time_line[i - 1].over_time;
		if (moni_time_line[i].money < 0)
		{
			if (die_time > i)
			{
				die_time = i;
			}
		}

	}
	for (i = time, At = -1; i <= end; i++)
	{
		if (moni_time_line[i].money >= DELIVERCOST && At == -1)
		{
			At = i;
			Deadtime = die_time;
			return;
		}
	}
	Deadtime=die_time;
}

void InitMoniTimeLine(struct ORDER * Order_Array, int order_num, int end_time)
{
	int i;
	for (i = 0; i <= end_time; i++)
	{
		moni_time_line[i].finishnum=moni_time_line[i].punishnum=moni_time_line[i].deliver_num = moni_time_line[i].finished = moni_time_line[i].order_num = moni_time_line[i].over_time = 0;
		moni_time_line[i].money = MONEY;
	}
	for (i = 0; i <= order_num; i++)
	{
		moni_time_line[Order_Array[i].exist_time].order_num++;
	}
	for (i = 1; i <= end_time; i++)
	{
		moni_time_line[i].order_num += moni_time_line[i - 1].order_num;
	}
}


