#ifndef NODE_H
#define NODE_H
#include<string>

using namespace std;

struct adjListNode
{
    int fltID;
    string intlDome;
    int arvlApt;
    string dptT;
    string arvlT;
    int aplID;
    int aplMd;
    int airFares;
    adjListNode *next;
};


struct adjMatrixNode
{
    string dptT;
    string arvlT;
    int aplID;
    int aplMd;
    int airFares;
    adjMatrixNode *next;

};


struct qNode
{
    int nowApt;
    string nowTime;
    int step;
};


struct Requirement
{
    string dptT1, dptT2, arvlT1, arvlT2, intlDome;
    int aplMd;
    int flyT, waitT;
};

#endif // NODE_H
