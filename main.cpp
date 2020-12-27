//2019202290 ysy
#include <iostream>
#include <fstream>
#include <string>
#include<direct.h>
#include<stdio.h>
#include<vector>
#include "def.h"
#include "adjlist.h"
#include "adjmatrix.h"

using namespace std;

void getData(string **data)
{
    ifstream csvInput;
    //csvInput.open("C:/Users/Air Chrysalis/Desktop/code/Airline/dataset.csv");
    csvInput.open("./dataset.csv");
    string s;
    getline(csvInput, s);
    for (int i=0; i<maxR; i++)
    {
        for (int j=0; j<maxC-1; j++)
        {
            getline(csvInput, s, ',');
            data[i][j] = s;
        }
        getline(csvInput, s); data[i][maxC-1] = s;
    }
}


int main()
{
    string **dataset;
    dataset = new string*[maxR];
    for (int i=0; i<maxR; i++) dataset[i] = new string[maxC];

    getData(dataset);
    adjList AL(dataset);//邻接表
    adjMatrix AM(dataset);//邻接矩阵

    int n = 0;
    while (n != 8)
    {
        cout<<endl;
        cout<<"1. Depth-first traversal     2. Breadth-first traversal      3. Connectivity between 2 airports"<<endl<<endl;

        cout<<"4. Minimum time between 2 airports       5. Find the routes within 1 connections between 2 airports"<<endl<<endl;

        cout<<"6. Multiple routes meeting the requirements      7. Cheapest route meeting the requirements"<<endl<<endl;

        cout<<"8. Exit"<<endl;

        cout<<endl<<">>";
        cin>>n;
        cout<<endl;
        switch (n)
        {
            case 1: AL.depthFirstTrs(); break;

            case 2: AL.bfs(); break;

            case 3: AM.ifConnected(); break;

            case 4: AL.minTime(); break;

            case 5: AL.getSmpRoad(); break;

            case 6: AL.getRequiredRoad(); break;

            case 7: AL.getCheapRoad(); break;
        }
    }
    return 0;
}
