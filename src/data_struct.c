struct POINT
{
	int x;
	int y;
	int time;
	int exist_time;
	int type;//0 is res,1 is cus;
	int id; 
	int loc;//0isleft,1isright
};
struct ORDER
{
	int id, exist_time;
	struct POINT res, cus;
};
struct POINTLIST{

	struct POINT point;
	struct POINTLIST * next;
	
};
struct DELIVER
{
	int locx, locy, time_max;
	struct POINTLIST * headptr,*pre,*current;
	
	
};
struct MONI_TIME
{
	int money, deliver_num, order_num, finished,over_time,punishnum,finishnum,stay;
	int finishid[300],punishid[300];
};




