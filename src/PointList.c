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
extern int adddeliver[100], addnum,DIE,PUNISH,MONEY;
int Distance(int x, int y, int time, struct POINT des)
{
	int desx, desy, destime, ans;
	desx = des.x; desy = des.y; destime = des.exist_time;
	if (desx == x)
	{
		if (abs(desy - y) / 2 >= destime - time)
		{
			ans = abs(desy - y) / 2;
		}
		else
		{
			ans = destime - time;
		}
	}
	else
	{
		if (abs(desy - y) <= 1 || abs(desx - x) == 1)
		{
			if (abs(desy - y) / 2 + abs(desx - x) / 2 + 1 >= destime - time)
			{
				ans = abs(desy - y) / 2 + abs(desx - x) / 2 + 1;
			}
			else
			{
				ans = destime - time;
			}
		}
		else
		{
			if (abs(desy - y) / 2 + abs(desx - x) / 2 >= destime - time)
			{
				ans = abs(desy - y) / 2 + abs(desx - x) / 2;
			}
			else
			{
				ans = destime - time;
			}
		}
	}
	return ans;
}
int FindMaxListTime(int num)
{
	int i, timemax = 0;
	struct POINTLIST * current, *pre;
	for (i = 0; i < num; i++)
	{
		current = deliver[i].current;
		if (current != NULL)
		{
			while (current->next != NULL)
			{
				current = current->next;
			}
			if (current->point.time > timemax)
			{
				timemax = current->point.time;
			}
		}
	}
	return timemax;
}

struct POINTLIST * SaveList(struct POINTLIST * headptr, int mode)
{
	struct POINTLIST * newhead = NULL, *current = NULL, *current_former = headptr;
	while (current_former != NULL)
	{
		if (current == NULL)
		{
			if (current_former->point.exist_time <= At || mode == 1)
			{
				while ((newhead = current = (struct POINTLIST*)malloc(sizeof(struct POINTLIST))) == NULL);

				(*newhead) = (*current_former);
			}
		}
		else
		{
			if (current_former->point.exist_time <= At || mode == 1)
			{
				current->next = (struct POINTLIST*)malloc(sizeof(struct POINTLIST));
				current = current->next;
				(*current) = (*current_former);
			}
			current->next = NULL;
		}

		current_former = current_former->next;
	}
	return newhead;
}

void DeleteList(struct POINTLIST * headptr)
{
	struct POINTLIST * last = headptr;
	while (headptr != NULL)
	{
		last = headptr;
		headptr = headptr->next;
		free(last);
	}
}

void Insert(struct POINTLIST ** headptr, int point, struct POINT aim)
{
	struct POINTLIST * now;


	now = (struct POINTLIST *) malloc(1 * sizeof(struct POINTLIST));
	struct POINTLIST *current = NULL;


	now->point = aim;
	
	int i;
	if (point == 0)//插在最前面
	{
		if ((*headptr) == NULL)//本身就是空的
		{
			(*headptr) = now;
			now->next = NULL;
			

		}
		else
		{

			now->next = (*headptr);
			(*headptr) = now;

		}
	}
	else//不是最前面
	{
		current = (*headptr);
		for (i = 0; i < point - 1; i++)
		{
			current = current->next;
		}

		now->next = current->next;
		current->next = now;
	}
}

int UpDatePointList(struct POINTLIST * headptr, int deliver_id)
{
	int locx, locy, ans, time = Rt;
	struct POINTLIST * current = headptr, *pre = NULL;
	struct POINTLIST * Debug;
	locx = deliver[deliver_id].locx; locy = deliver[deliver_id].locy;
	if (headptr == NULL)
	{
		return 0;
	}
	while (current != NULL)
	{
		if (current == headptr)
		{
			current->point.time = time + Distance(locx, locy, Rt, current->point);
		}
		else
		{
			current->point.time = pre->point.time + Distance(pre->point.x, pre->point.y, pre->point.time, current->point);
		}
		if (current->next == NULL)
		{
			ans = current->point.time;
		}
		pre = current;
		current = current->next;
	}
	return ans;
}

void DeletePoint(struct POINTLIST ** headptr, int point)
{
	int i;
	struct POINTLIST * current, *pre=NULL;
	current = (*headptr);
	if ((*headptr) == NULL)
	{
		return;
	}
	if (point == 0)//删除的是头结点
	{
		(*headptr) = (*headptr)->next;
		free(current);
		current = NULL;
	}
	else
	{
		for (i = 0; i < point; i++)
		{
			pre = current;
			current = current->next;
		}
		//删除
		pre->next = current->next;
		free(current);
		current = NULL;
	}
}
int GetPointNum(struct POINTLIST * headptr)
{
	struct POINTLIST * current = headptr;
	int ans = 0;
	while (current != NULL)
	{
		ans++;
		current = current->next;
	}
	return ans;
}
int CaculateMaxTime(struct POINTLIST * headptr)
{
	struct POINTLIST * current = headptr;
	int max = 0;
	while (current != NULL)
	{
		if (current->point.time - current->point.exist_time > max)
		{
			max = current->point.time - current->point.exist_time;
		}
		current = current->next;
	}
	return max;
}
int IsNoOverTime(struct POINTLIST * headptr, int limit)
{
	if (CaculateMaxTime(headptr) > limit)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
int CaculateDall(struct POINTLIST * headptr, int time)
{
	struct POINTLIST * current = headptr;
	int ans = 0;
	while (current != NULL)
	{
		ans += (current->point.time - time);
		current = current->next;
	}
	return ans;
}
