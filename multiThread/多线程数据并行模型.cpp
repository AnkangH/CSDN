/*
数据并行：多个线程执行相同的操作，因此将数据分组，每个线程分别处理一部分数据。
案例：连续整型求和，求1-n的和，将1-n共n个数据分为两组[1,n/2]和[n/2+1,n]，创建两个线程分别求连续和。
主线程等待子线程执行求部分和接受后，输出总的连续和。
*/

#include<iostream>
#include<pthread.h> // for thread
//#include<unistd.h>  // for sleep
#include<string.h>
#include <stdio.h>  //cout不是线程安全的 没有立即刷新输出流到屏幕上
using namespace std;
void* runner(void*);//线程函数 计算从start到end的和
int sum=0;//求和
struct argVal
{
    int start;
    int end;
};//线程创建传递参数结构体 求和的起点和终点
int main(int argc,char**argv)
{
    cout<<"multiThreadTest."<<endl;
    if(argc<2)
    {
        cout<<"Usage: main intValue."<<endl;
        return 0;
    }
    pthread_t t1,t2;//两个线程
    int n=atoi(argv[1]);//获取int型参数
    argVal arg1{1,n/2},arg2{n/2+1,n};//构建两个线程创建传递参数
    int errorCode=pthread_create(&t1,nullptr,runner,(void*)&arg1);//创建线程1
    if(errorCode!=0)
    {
        printf("Thread1 create failture,abort\n");
        exit(EXIT_FAILURE);//线程创建失败处理
    }
    errorCode=pthread_create(&t1,nullptr,runner,(void*)&arg2);//创建线程2
     if(errorCode!=0)
    {
        printf("Thread2 create failture,abort\n");
        exit(EXIT_FAILURE);//线程创建失败处理
    }
    pthread_join(t1,nullptr);//main线程等待线程1终止
    pthread_join(t2,nullptr);//main线程等待线程2终止
    cout<<"sum of 1-"<<argv[1]<<" is "<<sum<<"."<<endl;//输出总的计算结果
    return 0;
}
void* runner(void* arg)
{
    argVal* x=(argVal*)arg;//void* -> argVal*
    int sumCur=0;//当前起点和终点数字的连续和
    for(int i=x->start;i<=x->end;i++)
       {
           sumCur+=i;
       }
    sum+=sumCur;//加到总的和当中
    printf("tid=%lu,start=%d,end=%d,sum=%d\n",pthread_self(),x->start,x->end,sumCur);
    pthread_exit(0);//计算结束 终止线程
}
