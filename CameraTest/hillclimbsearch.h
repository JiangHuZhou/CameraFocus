#ifndef HILLCLIMBSEARCH_H
#define HILLCLIMBSEARCH_H

#include <iostream>
#include "include/DTStageDriver.h"
#include <vector>
using namespace std;


class HillClimbSearch
{
public:
    HillClimbSearch();
    ~HillClimbSearch();

    bool    search(int rate);
    bool    bigSearch(int rate);

public:

    //vector<double>  zpulse;           //移动的脉冲数
    //vector<int>     direction;          //移动的方向
    int             *frame;
    int             count;              //采集的次数
    int             moveChange;         //移动的次数
    int             def_Direction;      //默认移动方向
    int             def_MinStep;        //默认最小移动步长
    int             def_MaxStep;        //默认最大移动步长
    int             last_Direction;      //上次移动的方向
    int             next_Direction;     //下次移动的方向
    int             last_Step;          //上次移动的步长
    int             next_Step;          //下次移动的步长
    int             last_Value;         //上次清晰度值
    double          last_last_Value;    //上上次清晰度值

    double          epsylon;            //误差值


    bool    focusGetMax(int rate);

    bool    focusGetMin(int rate);     //根据面积找最小值
    //struct FocusState *state;
};

#endif // HILLCLIMBSEARCH_H
