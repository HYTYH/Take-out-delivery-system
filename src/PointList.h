
int Distance(int x, int y, int time, struct POINT des);
int FindMaxListTime(int time);
struct POINTLIST * SaveList(struct POINTLIST * headptr, int mode);
void DeleteList(struct POINTLIST * headptr);
void Insert(struct POINTLIST ** headptr, int point, struct POINT aim);
int UpDatePointList(struct POINTLIST * headptr, int deliver_id);
void DeletePoint(struct POINTLIST ** headptr, int point);
int GetPointNum(struct POINTLIST * headptr);
int CaculateMaxTime(struct POINTLIST * headptr);
int IsNoOverTime(struct POINTLIST * headptr, int limit);
int CaculateDall(struct POINTLIST * headptr, int time);
