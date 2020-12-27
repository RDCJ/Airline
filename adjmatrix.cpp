#include "adjmatrix.h"

adjMatrix::adjMatrix(string **dataset)
{
    for (int i=0; i<=aptNum; i++)
        for (int j=0; j<=aptNum; j++)
        {
            _mat[i][j] = new adjMatrixNode;
            _mat[i][j]->next = NULL;
        }
    for (int i=0; i<maxR; i++)
    {
        int dptApt = atoi(dataset[i][4].c_str()),
             arvlApt = atoi(dataset[i][5].c_str());
        adjMatrixNode *newNode = new adjMatrixNode;
        newNode->dptT = dataset[i][6];
        newNode->arvlT = dataset[i][7];
        newNode->airFares = atoi(dataset[i][10].c_str());
        newNode->aplID = atoi(dataset[i][8].c_str());
        newNode->aplMd = atoi(dataset[i][9].c_str());
        newNode->next = _mat[dptApt][arvlApt]->next;
        _mat[dptApt][arvlApt]->next = newNode;
    }
}


void adjMatrix::ifConnected()
{
    cout<<"Input the starting airport and ending airport>>";
    int apt1, apt2;
    cin>>apt1>>apt2;
    cout<<endl;
    int ans = INT_MAX;
    dfs(apt2, apt1, EarlistT, 1, &ans);
    if (ans <= 4) cout<<"Arrive after "<<ans - 2<<" connection(s).";
    else cout<<"Can't arrive within 2 connections.";
    cout<<endl;
}

void adjMatrix::dfs(int end, int nowApt, string nowTime, int step, int *ans)
{
    if (step >= *ans || step > 4) return;
    if (nowApt == end)
    {
        if (step < *ans) *ans = step;
        return;
    }
    for (int i=1; i<=aptNum; i++)
    {
        adjMatrixNode *p = _mat[nowApt][i]->next;
        while (p != NULL)
        {
            adjMatrixNode *pp = p;
            p = p->next;
            if (deltaTime(nowTime, pp->dptT) > 0) continue;
            dfs(end, i, pp->arvlT, step+1, ans);
        }
    }
}
