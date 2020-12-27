#ifndef ADJLIST_H
#define ADJLIST_H
#include<cstring>
#include<string>
#include<vector>
#include<iostream>
#include<queue>
#include<climits>
#include "Node.h"
#include "def.h"

using namespace std;

class adjList
{
    public:
        adjList(string **dataset);

        void depthFirstTrs();//深度优先遍历
        void dfs(int nowApt, string nowTime, bool *flag, int *road, int step);

        void bfs();//广度优先遍历

        void minTime();//任意两个机场之间的最短飞行时间
        void dfsMinTime(int end, int nowApt, int costTime, string nowTime, int *ans, bool flag[], int step);

        void getSmpRoad();//仅限直飞或1次中转，求任意两个机场的航线
        void dfsGetSmpRoad(int end, int nowApt, string nowTime, bool *flag, int *road, int step, int *ansCount);

        void getRequire(Requirement *rqmt);
        bool dealRequire(adjListNode *p, Requirement &rqmt, string nowTime, int nowApt, int nowFlyT, int nowWaitT, int start, int end);

        void getRequiredRoad();//求任意两个机场的多个备选航线
        void dfsGetRequiredRoad(int start, int end, int nowApt, string nowTime, int nowFlyT, int nowWaitT,
                                                    bool *flag, int *road, int step, int *ansCount, Requirement &rqmt);

        void getCheapRoad();//求任意两个机场之间的航费最低的路径
        void dfsGetCheapRoad(int start, int end, int nowApt, string nowTime, int nowCost, int nowFlyT, int nowWaitT,
                                            bool *flag, int *road, int step, int *ansCost, int ansRoad[], Requirement &rqmt);

    private:
        adjListNode *_list[80];

};

#endif // ADJLIST_H
