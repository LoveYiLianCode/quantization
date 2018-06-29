#include<iostream>
#include<stdlib.h>
#include <algorithm>
#include<stdio.h>
using namespace std;
const int INF=99999999;//定义无穷大
int number;
int a[1000];                //记录输入的数据
int sum1[1000];             //记录输入数据的前N项和
int sum2[1000];             //记录输入数据的前N项的平方和;
void swap(int a[], int i, int j)
{
	int t = a[i];
	a[i] = a[j];
	a[j] = t;
}
int partition(int a[], int left, int right)
{
    int i = left;
    int j = right + 1;
    int x = a[left];
    while(1){
        while(i < right && a[++i] < x);
        {
                while(a[--j]>x);
            {
                if(i >= j) break;
                swap(a,i,j);
            }
        }

    }
    swap(a,left,j);
    return j;
}
/****************************************************/
/*   函数功能：对数组进行快速排序                   */
/****************************************************/
void quicksort(int a[], int left, int right)
{
    if(left<right){
        int q = partition(a,left,right);
        quicksort(a,left,q-1);
        quicksort(a,q+1,right);
    }
}
/****************************************************/
/*  函数功能：分别求输入数组的前N项和和前N项平方和  */
/****************************************************/
void sortSum()
{
    quicksort(a,0,number-1);
    sum1[0] = a[0];
    sum2[0] = a[0]*a[0];
    for(int i = 1;i < number;i++)
    {
        sum1[i] = sum1[i-1] + a[i];
        sum2[i] = sum2[i-1] + a[i]*a[i];
    }
}
/****************************************************/
/*  函数功能：计算从low到high的量化误差平方和       */
/****************************************************/
int squareSum(int low, int high)
{
    int sum, squaresum, average, sumQ;
    sum = sum1[high] - (low == 0?0:sum1[low-1]);
    squaresum = sum2[high] - (low == 0?0:sum2[low-1]);
    average = (int)(0.5 + (double)sum / (high - low + 1));
    sumQ = squaresum - 2*average*sum + average*average*(high - low + 1);
    return sumQ;
}
/****************************************************/
/*  函数功能：递归求量化的结果                      */
/****************************************************/
int quantize(int from,int parts)
{
    int ret = INF;
    if(from == number)
        return 0;
    if(parts == 0)
        return INF;
    for(int partSize = 1;from+partSize <= number;++partSize)
    {
        ret = min(ret , squareSum(from,from + partSize - 1) + quantize(from + partSize,parts - 1));
    }
    return ret;
}
int main()
{
    int test, parts, ret;
    cin>>test;                  //输入测试数据的次数
    while(test > 0)
    {
        cin>>number>>parts;     //输入测试数据的个数和量化的个数
        for(int i = 0;i < number;i++)
        {
            cin>>a[i];
        }
        sortSum();
        ret = quantize(0,parts);
        cout<<ret<<endl;
        test--;
    }
    return 0;
}

