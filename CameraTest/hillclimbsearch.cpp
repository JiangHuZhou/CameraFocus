#include "hillclimbsearch.h"


HillClimbSearch::HillClimbSearch()
{
    //fCurrentValue = 0;
    //state = (struct FocusState *)malloc(sizeof(struct FocusState));

//    InitXML xml("init.xml");
//    this->defaultStep = (int)xml.getValueByName("focusStep");       //默认步长
//    this->epsylon = xml.getValueByName("epsylon");                  //误差值
//    this->minStep = (int)xml.getValueByName("minFocusStep");        //最小步长
//    this->correctValue = xml.getValueByName("focusRate");           //阀值

    //this->direction = 1;                                            //方向
//    this->lastDirection = 1;                                        //上一次方向
//    this->nextDirection = 1;                                        //下次方向

//    this->lastStep = this->defaultStep;                             //上次步长
//    this->nextStep = this->defaultStep;                             //下次步长

    def_Direction = 1;
    count = 0;
    moveChange = 0;

        frame = new int[3];
    //frame.clear();
    //def_MinStep = 500;
    //def_MaxStep = 10000;
}

HillClimbSearch::~HillClimbSearch()
{
    //free(state);
    delete []frame;
}


bool HillClimbSearch::search(int rate)
{

    //bool isSuccess = focusGetMin(rate);
    //cout << "isSuccess = "<< isSuccess << endl;
    return focusGetMin(rate);

}

bool HillClimbSearch::bigSearch(int rate)
{
    DTMoveSteps('Z',rate * def_Direction);//电机转动
    return true;
/*
    if(rate <= 100)
    {
        //next_Step = def_MaxStep * 2;
        //next_Direction = def_Direction;

        DTMoveSteps('Z',def_MaxStep * 2 * def_Direction);//电机转动

        //last_Step = next_Step;
        //last_Direction = next_Direction;
        return false;
    }
    else
    {
        if(rate > last_Value)
        {
            next_Step = def_MaxStep;
            next_Direction = def_Direction;

            last_Value = rate;
            //last_Direction = next_Direction;
            DTMoveSteps('Z',def_MaxStep * def_Direction);//电机转动

            return false;
        }
        else
        {
            next_Step = def_MaxStep / 2;
            DTMoveSteps('Z',next_Step * def_Direction);

            return true;
        }
    }
*/
}

bool HillClimbSearch::focusGetMax(int rate)
{
    return false;
    //找最大值
    //判断是否是第一次进入搜索
/*
    //第一步:采集3帧图像判断方向,及确定下一步步长

    if(count == 1 || count == 2)
    {
        //保存清晰度值
        if(count == 1)
            last_last_Value = rate;
        if(count == 2)
            last_Value = rate;
        //按默认方向移动默认最大步长
        DTMoveSteps('Z',def_MaxStep * def_Direction);//电机转动
        //移动次数加1
        count++;
        //保存移动的方向和步长
        last_Direction = def_Direction;
        last_Step = def_MaxStep;
        return  false;

    }
    else if(count == 3)
    {
        //判断方向
        if((rate > last_Value) && (last_Value > last_last_Value))
        {
            //连续变大,方向正确
            next_Direction = last_Direction;
            next_Step = last_Step;
        }
        else if((rate < last_Value) && (last_Value < last_last_Value))
        {
            //连续变小,方向错误
            next_Direction = last_Direction * -1;
            //改变步长,移动至第一帧图像位置
            next_Step = last_Step * 2;
        }
        DTMoveSteps('Z',next_Step * next_Direction);//电机转动
        //移动次数加1
        count++;
        //保存移动的方向和步长
        last_Direction = next_Direction;
        last_Step = next_Step;
        return  false;
    }
    //第二步:进入搜索主循环
    else
    {
        //表明已经判断过方向

    }


    //不是第一次进入搜索
    else
    {
        //第二次进入搜索
        if(count == 2)
        {
            //判断方向
            if(rate < last_Value - last_Value * epsylon)
            {
                //方向错误,改变方向
                next_Direction = last_Direction * -1;
            }
            else
            {
                //方向正确,方向不变
                next_Direction = last_Direction;
            }
            //改变步长
            //方向正确时:越过刚才的点
            //方向错误时:尝试增大步长
            next_Step = last_Step * 2;
        }
        //不是第二次
        else
        {
            //判断方向
            if(rate < last_Value - last_Value * epsylon)
            {
                //方向错误,说明已经走过最大值,改变方向
                next_Direction = last_Direction * -1;
                //缩小步长
                next_Step = (double)last_Step * 0.75;

                if(next_Step <= def_MinStep)
                {
                    //下次步长比最小默认步长小,说明按最小默认步长移动回去就是最大值,即对焦范围内,此时应返回true,表示对焦成功
                    next_Step = def_MinStep;
                    //电机转动

                    DTMoveSteps('Z',(int)next_Step * next_Direction);
                    cout<<"next step :" << (int)next_Step * next_Direction << endl;
                    return true;
                }

            }
            else
            {
                //方向正确,方向不变
                next_Direction = last_Direction;
                //增大步长
                next_Step = last_Step * 1.25;

                next_Step = (next_Step >= def_MaxStep) ? def_MaxStep:next_Step;

            }
        }

    }
    //电机转动
    DTMoveSteps('Z',(int)next_Step * next_Direction);
    //移动次数加1
    count++;
    //保存方向和步长
    last_Direction = next_Direction;
    last_Step = (int)next_Step;
    //保存清晰度值
    last_Value = rate;

    cout<<"count = "<<count<<" next step :" << (int)next_Step * next_Direction << endl;

    return false;
*/

/*  根据前后2帧判断方向
    if(count == 1)
    {
        //按默认方向移动默认最小步长
        DTMoveSteps('Z',def_MinStep * def_Direction);//电机转动
        //移动次数加1
        count++;
        //保存移动的方向和步长
        last_Direction = def_Direction;
        last_Step = def_MinStep;
        //保存清晰度值
        last_Value = rate;

        return  false;
    }
    //不是第一次进入搜索
    else
    {
        //第二次进入搜索
        if(count == 2)
        {
            //判断方向
            if(rate < last_Value - last_Value * epsylon)
            {
                //方向错误,改变方向
                next_Direction = last_Direction * -1;
            }
            else
            {
                //方向正确,方向不变
                next_Direction = last_Direction;
            }
            //改变步长
            //方向正确时:越过刚才的点
            //方向错误时:尝试增大步长
            next_Step = last_Step * 2;
        }
        //不是第二次
        else
        {
            //判断方向
            if(rate < last_Value - last_Value * epsylon)
            {
                //方向错误,说明已经走过最大值,改变方向
                next_Direction = last_Direction * -1;
                //缩小步长
                next_Step = (double)last_Step * 0.75;

                if(next_Step <= def_MinStep)
                {
                    //下次步长比最小默认步长小,说明按最小默认步长移动回去就是最大值,即对焦范围内,此时应返回true,表示对焦成功
                    next_Step = def_MinStep;
                    //电机转动

                    DTMoveSteps('Z',(int)next_Step * next_Direction);
                    cout<<"next step :" << (int)next_Step * next_Direction << endl;
                    return true;
                }

            }
            else
            {
                //方向正确,方向不变
                next_Direction = last_Direction;
                //增大步长
                next_Step = last_Step * 1.25;

                next_Step = (next_Step >= def_MaxStep) ? def_MaxStep:next_Step;

            }
        }

    }
    //电机转动
    DTMoveSteps('Z',(int)next_Step * next_Direction);
    //移动次数加1
    count++;
    //保存方向和步长
    last_Direction = next_Direction;
    last_Step = (int)next_Step;
    //保存清晰度值
    last_Value = rate;

    cout<<"next step :" << (int)next_Step * next_Direction << endl;

    return false;
*/
}

bool HillClimbSearch::focusGetMin(int rate)
{
    static int count = 0;
    if(count == 0)
    {

        DTMoveSteps('Z',def_MaxStep * def_Direction);//电机转动
        last_Step = def_MaxStep;
        last_Direction = def_Direction;
        last_Value = rate;
        count++;
        return false;
    }
    else
    {
        if(rate < last_Value)
        {
            //方向正确
            next_Direction = last_Direction;

            next_Step = (int)last_Step * 0.8;
        }
        else if(rate > last_Value)
        {
            //方向错误
            next_Direction = last_Direction * -1;
            next_Step = (int)last_Step * 0.75;
        }

        if((next_Step <= def_MinStep)||(rate == last_Value))
        {
            next_Step = def_MinStep;
            DTMoveSteps('Z',next_Step * next_Direction);//电机转动

            return true;
        }
        else
        {
            last_Step = next_Step;
            last_Direction = next_Direction;
            last_Value = rate;


            DTMoveSteps('Z',next_Step * next_Direction);//电机转动

            cout << "count = "<<count<<" next step = "<<next_Step * next_Direction<<endl;

            count++;
            return false;
        }
    }

/*  连续三帧判断方向
    //static vector<int>     frame(3,0);    //保存每帧图像的清晰度值
    //连续采集3帧图像求平均值,用来表示一幅图像的rate
    //cout<< "rate =  "<< rate <<endl;
    //cout <<"count = "<<count<<endl;
    //cout << "def_MinStep = "<<def_MinStep<<" def_MaxStep = "<<def_MaxStep<<endl;
    if(count < 3)
    {
        if(count == 0)
        {
            frame[0] = rate;
            next_Step = def_MaxStep;
            next_Direction = def_Direction;
        }
        else if(count == 1)
        {
            frame[1] = rate;
            next_Step = last_Step;
            next_Direction = last_Direction;
        }
        else if(count == 2)
        {
            frame[2] = rate;

            if((frame[0] > frame[1]) && (frame[1]> rate))
            {
                // 1 > 2 > 3 递减,方向正确
                next_Direction = last_Direction;
                next_Step = last_Step / 2;
            }
            else if((frame[0] < frame[1]) && (frame[1] < rate))
            {
                // 1 < 2 < 3 方向错误
                next_Direction = last_Direction * -1;

                //回到起点,相反方向按默认步长走
                next_Step = last_Step * 2;

                last_Step = def_MaxStep;
                last_Direction = next_Direction;

                last_Value = rate;

                DTMoveSteps('Z',next_Step * next_Direction);//电机转动

                cout << "count = "<<count<<" next step = "<<next_Step * next_Direction<<endl;

                count++;

                return false;
            }
            else if((frame[1] < rate)||(frame[1] < frame[0]))
            {
                //2 < 3 < 1 或者 2 < 1 < 3
                //方向错误，第2帧图像最小,说明已经越过焦点
                next_Direction = last_Direction * -1;
                //先回到第2帧图像,同时离开第2帧的位置
                next_Step = (int)last_Step * 1.5;
            }
            //next_Step = last_Step /2;
        }

        last_Direction = next_Direction;
        last_Step = next_Step;

        last_Value = rate;

        DTMoveSteps('Z',next_Step * next_Direction);//电机转动

        cout << "count = "<<count<<" next step = "<<next_Step * next_Direction<<endl;

        count++;

        return false;
    }
    else
    {
        if(rate < last_Value)
        {
            //方向正确
            next_Direction = last_Direction;
            //缩小步长
            next_Step = (int)last_Step * 0.75;
        }
        else if(rate > last_Value)
        {
            //方向错误
            next_Direction = last_Direction * -1;
            next_Step = (int)last_Step * 0.75;
        }

        if((next_Step <= def_MinStep)||(rate == last_Value))
        {
            next_Step = def_MinStep;
            DTMoveSteps('Z',next_Step * next_Direction);//电机转动

            return true;
        }
        else
        {
            last_Step = next_Step;
            last_Direction = next_Direction;
            last_Value = rate;


            DTMoveSteps('Z',next_Step * next_Direction);//电机转动

            cout << "count = "<<count<<" next step = "<<next_Step * next_Direction<<endl;

            count++;
            return false;
        }
    }
*/

    return false;
}

    /* 本搜索算法是要找到最小值
     *
    //

    //聚焦范围内
    if(rate > this->correctValue - this->epsylon && rate < this->correctValue + this->epsylon)
    {

        //将当前值更新为下一幅图的阀值
        InitXML xml("init.xml");
        xml.setValyeByName("focusRate",rate);
        return 0;
    }
    //不在默认阀值聚焦范围内
    else
    {
        //当前值小于阀值-误差,说明可能产生了局部最小值
        if(rate < this->correctValue - this->epsylon)
        {
            //以最小步长移动,方向为上次移动的方向,步长为最小步长
            this->nextDirection = this->lastDirection;
            this->nextStep = this->minStep;

            return this->nextStep * this->nextDirection;
        }
        //当前值大于上次值,说明方向错误
        if(rate > this->lastValue)
        {
            this->nextDirection = this->lastDirection * -1;
        }
        //当前值小于上次值,说明方向正确
        else
        {
            this->nextDirection = this->lastDirection;
        }
        //当前值大于阀值 + 误差,说明离焦越来越远
        if(rate > this->correctValue + this->epsylon)
        {
            this->nextStep = this->lastStep;
        }
        //靠近焦点
        else
        {
            if(this->lastStep * 0.75 <= this->minStep)
            {
                this->nextStep = this->minStep;
            }
            else
            {
                this->nextStep = this->lastStep * 0.75;
            }
        }
    }
    this->lastDirection = this->nextDirection;
    this->lastStep = this->nextStep;
    this->lastValue = rate;

    return this->nextStep * this->nextDirection;
    */


