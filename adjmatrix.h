#ifndef ADJMATRIX_H
#define ADJMATRIX_H
#include<string>
#include<climits>
#include<iostream>
#include "def.h"
#include "Node.h"

using namespace std;

class adjMatrix
{
    public:
        adjMatrix(string **dataset);
        void ifConnected();//任意两个机场的可连通性
        void dfs(int end, int nowApt, string nowTime, int step, int *ans);

    private:
        adjMatrixNode *_mat[80][80];
};

#endif // ADJMATRIX_H
