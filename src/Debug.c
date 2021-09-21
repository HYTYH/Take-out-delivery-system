#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "data_struct.h"
#include "MoniTimeLine.h"
#include "PointList.h"
extern int active[100], not_active[100],mode, Mt, At,Rt,Et,Order_Num,in_active,not_inactive,weight_all,weight_last,weight_max,weight_min,weight_maxtime,Deadtime;
extern struct MONI_TIME * moni_time_line;
extern struct ORDER emergency0[2000], emergency1[2000];
extern struct ORDER * Order_Array;
extern struct DELIVER deliver[2000];
extern int emergency0_num, emergency1_num;
extern int adddeliver[100], addnum,DIE,PUNISH,MONEY;
void Debug(void)
{
	struct POINTLIST *a = (struct POINTLIST *)malloc(sizeof(struct POINTLIST) * 5);

	a[2].point.exist_time = a[3].point.exist_time = 1;
	a[0].point.exist_time = a[1].point.exist_time = 17;
	a[0].point.x = 7; a[0].point.y = 2;
	a[1].point.x = 5; a[1].point.y = 14;
	a[2].point.x = 1; a[2].point.y = 0;
	a[3].point.x = 1; a[3].point.y = 10;
	int i;
	for (i = 0; i < 4; i++)
	{
		if (i == 0)
		{

			a[0].next = a + 1;
		}
		else if (i == 3)
		{
			a[3].next = NULL;

		}
		else
		{
			a[i].next = a + i + 1;

		}
	}
	deliver[0].headptr = a;
	deliver[1].headptr = NULL;
	UpDatePointList(a, 0);
	//a[3].next = NULL;

}
void printfmoney(void)
{
	int i;
	for (i = 0; i < Et + 97; i++)
	{
		printf("%d %d %d %d\n", i, moni_time_line[i].money, moni_time_line[i].finished, moni_time_line[i].over_time);
	}
}
void Show_line(void)
{
	int i;
	struct POINTLIST * current;
	printf("indebug:\n");
	for (i = 0; i < addnum; i++)
	{
		current = deliver[i].headptr;
		printf("\nDELIVER_ID:%d\n", i);
		while (current != NULL)
		{
			
			printf("(%d,%d,%d,%d,%d,%d)->",current->point.id,current->point.type,current->point.x, current->point.y, current->point.time, current->point.exist_time);
			
			current = current->next;
		}
		printf("\n\n");


	}
}
