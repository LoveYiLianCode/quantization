#include<iostream>
#include<stdlib.h>
#include <algorithm>
#include<stdio.h>
using namespace std;
const int INF=99999999;//���������
int number;
int a[1000];                //��¼���������
int sum1[1000];             //��¼�������ݵ�ǰN���
int sum2[1000];             //��¼�������ݵ�ǰN���ƽ����;
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
/*   �������ܣ���������п�������                   */
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
/*  �������ܣ��ֱ������������ǰN��ͺ�ǰN��ƽ����  */
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
/*  �������ܣ������low��high���������ƽ����       */
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
/*  �������ܣ��ݹ��������Ľ��                      */
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
    cin>>test;                  //����������ݵĴ���
    while(test > 0)
    {
        cin>>number>>parts;     //����������ݵĸ����������ĸ���
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

