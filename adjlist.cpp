#include "adjlist.h"

adjList::adjList(string **dataset)
{
    for (int i=0; i<80; i++)
    {
        _list[i] = new adjListNode;
        _list[i]->next = NULL;
    }
    for (int i=0; i<maxR; i++)//构造邻接表
    {
        int dptApt = atoi(dataset[i][4].c_str());
        adjListNode *newNode = new adjListNode;
        newNode->fltID = i+1;
        newNode->dptT = dataset[i][6];
        newNode->arvlT = dataset[i][7];
        newNode->arvlApt = atoi(dataset[i][5].c_str());
        newNode->airFares = atoi(dataset[i][10].c_str());
        newNode->aplID = atoi(dataset[i][8].c_str());
        newNode->aplMd = atoi(dataset[i][9].c_str());
        newNode->intlDome = dataset[i][2];
        newNode->next = _list[dptApt]->next;
        _list[dptApt]->next = newNode;
    }
}


void adjList::depthFirstTrs()
{
    cout<<"Input the starting airport>>";
    int start; cin>>start;
    //初始化
    bool flag[aptNum+1];
    for (int i=1; i<=aptNum; i++) flag[i] = false;
    flag[start] = true;
    int road[10] = {0};
    road[0] = start;

    dfs(start, EarlistT, flag, road, 0);
}


void adjList::dfs(int nowApt, string nowTime, bool *flag, int *road, int step)
{
    //if (step > 3) return;
    bool ifend = true;//记录当前机场是否能到其他机场
    adjListNode *p = _list[nowApt]->next;
    while (p != NULL)
    {
        adjListNode *pp = p;
        p = p->next;
        if (flag[pp->arvlApt]) continue;
        if (deltaTime(nowTime, pp->dptT) >= 0) continue;

        ifend = false;//记录当前机场能到其他机场
        flag[pp->arvlApt] = true;
        road[step+1] = pp->arvlApt;

        dfs(pp->arvlApt, pp->arvlT, flag, road, step+1);

        flag[pp->arvlApt] = false;
    }
    if (ifend == true)//当前机场不能到其他机场，则输出已走的路径
    {
        for (int i=0; i<step; i++)
            cout<<road[i]<<"->";
        cout<<road[step]<<endl;
    }
}


void adjList::bfs()
{
    cout<<"Input the starting airport>>";
    int start; cin>>start;

    bool flag[aptNum+1];
    for (int i=1; i<=aptNum; i++) flag[i] = false;
    flag[start] = true;
    queue<qNode> que;
    que.push(qNode {start, EarlistT, 0});
    while (!que.empty())
    {
        qNode poped = que.front();
        que.pop();
        cout<<poped.nowApt<<' ';
        adjListNode *p = _list[poped.nowApt]->next;
        while (p != NULL)
        {
            adjListNode *pp = p;
            p = p->next;
            if (flag[pp->arvlApt] == true) continue;
            if (deltaTime(poped.nowTime, pp->dptT) >= 0) continue;
            que.push(qNode {pp->arvlApt, pp->arvlT, poped.step + 1});
            flag[pp->arvlApt] = true;
        }
    }
    cout<<endl;
}


void adjList::minTime()
{
    cout<<"Input the starting airport and ending airport>>";
    int apt1, apt2;
    cin>>apt1>>apt2;
    cout<<endl;
    //初始化
    int ans = INT_MAX;
    bool flag[80];
    for (int i=1; i<=aptNum; i++) flag[i] = false;
    flag[apt1] = true;

    dfsMinTime(apt2, apt1, 0, EarlistT, &ans, flag, 1);

    if (ans < INT_MAX)
    {
        int hour = ans / 60,
             min = ans % 60;
        cout<<"The minimum time is ";
        if (hour > 0)
        {
            cout<<hour<<'h';
            if (min > 0) cout<<' '<<min<<"min.";
        }
        else cout<<min<<"min.";
    }
    else cout<<"Cannot arrive.";
    cout<<endl;
}


void adjList::dfsMinTime(int end, int nowApt, int costTime, string nowTime, int *ans, bool flag[], int step)
{
    if (costTime >= *ans) return;//当前耗时比搜索到的最低耗时高则退出
    if (step > 5) return;
    if (nowApt == end)
    {
        *ans = costTime;//更新结果
        return;
    }
    adjListNode *p = _list[nowApt]->next;
    while (p != NULL)
    {
        adjListNode *pp = p;
        p = p->next;

        if (flag[pp->arvlApt]) continue;
        if (step == 1) nowTime = pp->dptT;//起始时间设定为第一趟航班起飞时间
        if (deltaTime(nowTime, pp->dptT) > 0) continue;

        flag[pp->arvlApt] = true;
        int addTime = deltaTime(pp->dptT, nowTime) + deltaTime(pp->arvlT, pp->dptT);

        dfsMinTime(end, pp->arvlApt, costTime + addTime, pp->arvlT, ans, flag, step+1);

        flag[pp->arvlApt] = false;
    }
}


void adjList::getSmpRoad()
{
    cout<<"Input the starting airport and ending airport>>";
    int apt1, apt2;
    cin>>apt1>>apt2;
    cout<<endl;

    bool flag[aptNum+1];
    for (int i=1; i<=aptNum; i++) flag[i] = false;
    flag[apt1] = true;
    int road[10] = {0};
    int ansCount = 0;

    dfsGetSmpRoad(apt2, apt1, EarlistT, flag, road, 0, &ansCount);
    if (ansCount <= 0) cout<<"Can't arrive within 1 connection."<<endl;
}


void adjList::dfsGetSmpRoad(int end, int nowApt, string nowTime, bool *flag, int *road, int step, int *ansCount)
{
    if (step > 2) return;//中转次数不超过 1
    if (nowApt == end)//到目的地就输出路径
    {
        (*ansCount)++;
        cout<<"Route "<<*ansCount<<": ";
        for (int i=0; i<step; i++) cout<<road[i]<<' ';
        cout<<endl;
        return;
    }
    adjListNode *p = _list[nowApt]->next;
    while (p != NULL)
    {
        adjListNode *pp = p;
        p = p->next;
        if (flag[pp->arvlApt] == true) continue;
        if (deltaTime(nowTime, pp->dptT) > 0) continue;

        flag[pp->arvlApt] = true;
        road[step] = pp->fltID;

        dfsGetSmpRoad(end, pp->arvlApt, pp->arvlT, flag, road, step+1, ansCount);

        flag[pp->arvlApt] = false;
    }
}


void adjList::getRequire(Requirement *rqmt)
{
    cout<<endl<<"Input \"no\" if you don't have requirement."<<endl;

    cout<<endl<<"Required departure time>>"<<endl;
    getchar();
    getline(cin, rqmt->dptT1);
    if (rqmt->dptT1 != "No" && rqmt->dptT1 != "NO" && rqmt->dptT1 != "no")
        getline(cin, rqmt->dptT2);

    cout<<endl<<"Required arrival time>>"<<endl;
    getline(cin, rqmt->arvlT1);
    if (rqmt->arvlT1 != "No" && rqmt->arvlT1 != "NO" && rqmt->arvlT1 != "no")
        getline(cin, rqmt->arvlT2);

    string time;
    cout<<endl<<"Flight time limit?(hour)"<<endl;
    cin>>time;
    if (time == "No" || time == "NO" || time == "no") rqmt->flyT = INT_MAX;
    else rqmt->flyT = atoi(time.c_str()) * 60;

    cout<<endl<<"Connection time limit?(hour)"<<endl;
    cin>>time;
    if (time == "No" || time == "NO" || time == "no") rqmt->waitT = INT_MAX;
    else rqmt->waitT = atoi(time.c_str()) * 60;

    cout<<endl<<"Intl/Dome? >>"; cin>>rqmt->intlDome;
    cout<<endl<<"Required airplane model>>";
    {
        string md;
        cin>>md;
        if (md == "No" || md == "NO" || md == "no") rqmt->aplMd = 0;
        else rqmt->aplMd = atoi(md.c_str());
    }
}


bool adjList::dealRequire(adjListNode *p, Requirement &rqmt, string nowTime, int nowApt,
                                        int nowFlyT, int nowWaitT, int start, int end)
{
    if (deltaTime(nowTime, p->dptT) > 0) return false;

    if (nowApt == start && rqmt.dptT1 != "No" && rqmt.dptT1 != "NO" && rqmt.dptT1 != "no")
    {
        if (rqmt.dptT1.find('/') == rqmt.dptT1.npos)
        {
            string rt1 = p->dptT.substr(0, 9) + rqmt.dptT1;
            if (deltaTime(p->dptT, rt1) < 0) return false;
            string rt2 = p->dptT.substr(0, 9) + rqmt.dptT2;
            if (deltaTime(p->dptT, rt2) > 0) return false;
        }
        else
        {
            if (deltaTime(p->dptT, rqmt.dptT1) < 0) return false;
            if (deltaTime(p->dptT, rqmt.dptT2) > 0) return false;
        }
    }
    if (p->arvlApt == end && rqmt.arvlT1 != "No" && rqmt.arvlT1 != "NO" && rqmt.arvlT1 != "no")
    {
        if (rqmt.arvlT1.find('/') == rqmt.arvlT1.npos)
        {
            string rt1 = p->arvlT.substr(0, 9) + rqmt.arvlT1;
            if (deltaTime(p->arvlT, rt1) < 0) return false;
            string rt2 = p->arvlT.substr(0, 9) + rqmt.arvlT2;
            if (deltaTime(p->arvlT, rt2) > 0) return false;
        }
        else
        {
            if (deltaTime(p->arvlT, rqmt.arvlT1) < 0) return false;
            if (deltaTime(p->arvlT, rqmt.arvlT2) > 0) return false;
        }
    }

    if (nowFlyT + deltaTime(p->arvlT, p->dptT) > rqmt.flyT) return false;
    if (nowWaitT + deltaTime(p->dptT, nowTime) > rqmt.waitT) return false;

    if (rqmt.intlDome != "No" && rqmt.intlDome != "NO" && rqmt.intlDome != "no" && p->intlDome != rqmt.intlDome) return false;
    if (rqmt.aplMd != 0 && p->aplMd != rqmt.aplMd) return false;
    return true;
}


void adjList::getRequiredRoad()
{
    int apt1, apt2;
    cout<<"Input starting airport and ending airport>>";
    cin>>apt1>>apt2;

    Requirement rqmt;
    getRequire(&rqmt);//询问查询条件

    bool flag[aptNum+1];
    for (int i=1; i<=aptNum; i++) flag[i] = false;
    flag[apt1] = true;
    int road[10] = {0};
    int ansCount = 0;//记录搜索到的总路径数
    cout<<endl;

    dfsGetRequiredRoad(apt1, apt2, apt1, EarlistT, 0, 0, flag, road, 0, &ansCount, rqmt);
    if (ansCount <= 0) cout<<"Can't find a right route."<<endl;
}


void adjList::dfsGetRequiredRoad(int start, int end, int nowApt, string nowTime, int nowFlyT, int nowWaitT,
                                                        bool *flag, int *road, int step, int *ansCount, Requirement &rqmt)
{
    if (*ansCount >= 10) return;//避免输出的方案太多
    if (step > 4) return;
    if (nowApt == end)
    {
        (*ansCount)++;
        cout<<"Route "<<*ansCount<<": ";
        for (int i=0; i<step; i++) cout<<road[i]<<' ';
        cout<<endl;
        return;
    }
    adjListNode *p = _list[nowApt]->next;
    while (p != NULL)
    {
        adjListNode *pp = p;
        p = p->next;
        if (flag[pp->arvlApt]) continue;
        if (step == 0) nowTime = pp->dptT;//起始时间设定为第一趟航班起飞时间
        if (!dealRequire(pp, rqmt, nowTime, nowApt, nowFlyT, nowWaitT, start, end)) continue;//判断此航班是否符合要求

        flag[pp->arvlApt] = true;
        road[step] = pp->fltID;

        dfsGetRequiredRoad(start, end, pp->arvlApt, pp->arvlT, nowFlyT + deltaTime(pp->arvlT, pp->dptT),
                                            nowWaitT+deltaTime(pp->dptT, nowTime), flag, road, step+1, ansCount, rqmt);

        flag[pp->arvlApt] = false;
    }
}


void adjList::getCheapRoad()
{
    int apt1, apt2;
    cout<<"Input starting airport and ending airport>>";
    cin>>apt1>>apt2;

    Requirement rqmt;
    getRequire(&rqmt);//询问查询条件

    bool flag[aptNum+1];
    for (int i=1; i<=aptNum; i++) flag[i] = false;
    flag[apt1] = true;
    int road[10] = {0}, ansRoad[10] = {10};
    int ansCost = INT_MAX;

    dfsGetCheapRoad(apt1, apt2, apt1, EarlistT, 0, 0, 0, flag, road, 0, &ansCost, ansRoad, rqmt);
    cout<<endl;

    if (ansCost == INT_MAX) cout<<"Can't find a right route."<<endl;
    else
    {
        cout<<"The lowest fares: "<<ansCost<<endl;
        cout<<"Route: ";
        int i=0;
        while (ansRoad[i] != 0) cout<<ansRoad[i++]<<' ';
        cout<<endl;
    }
}


void adjList::dfsGetCheapRoad(int start, int end, int nowApt, string nowTime, int nowCost, int nowFlyT, int nowWaitT,
                                                  bool *flag, int *road, int step, int *ansCost, int ansRoad[], Requirement &rqmt)
{
    if (nowCost >= *ansCost) return;//当前花费比目前搜索到的最低花费高则退出
    if (step > 4) return;
    if (nowApt == end)
    {
        for (int i=0; i<step; i++) ansRoad[i] = road[i];
        for (int i=step; i<10; i++) ansRoad[i] = 0;
        *ansCost = nowCost;
        return;
    }
    adjListNode *p = _list[nowApt]->next;
    while (p != NULL)
    {
        adjListNode *pp = p;
        p = p->next;
        if (flag[pp->arvlApt]) continue;
        if (step == 0) nowTime = pp->dptT;//起始时间设定为第一趟航班起飞时间
        if (!dealRequire(pp, rqmt, nowTime, nowApt, nowFlyT, nowWaitT, start, end)) continue;//判断此航班是否符合要求

        flag[pp->arvlApt] = true;
        road[step] = pp->fltID;

        dfsGetCheapRoad(start, end, pp->arvlApt, pp->arvlT, nowCost + pp->airFares, nowFlyT + deltaTime(pp->arvlT, pp->dptT),
                                     nowWaitT+deltaTime(pp->dptT, nowTime), flag, road, step+1, ansCost, ansRoad, rqmt);

        flag[pp->arvlApt] = false;
        road[step] = 0;
    }
}
