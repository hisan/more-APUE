

//2019-04-23 23:20完成
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "heapsort.h"

void Swap(int *a,int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void AdjustDown(int *A,int i,int len)
{//对完全二叉树的序列数组A的i位置进行向下排序调整
    int tempval = A[i];//保存我们有可能向下调整的值
    int k;
	for(k = 2*i+1;k<len;k = k*2+1)
    {
        if(k<len-1&&A[k] < A[k+1])
        {//我们是要将当前节点和他的两个孩子中的较大者进行比较，
         //所以我们寻找两者中的最大者的前提条件就是当前节点由两个孩子,所以K < len-1很有必要
            k++;
        }

        if(tempval >= A[k])
        {//若是当前节点大于他的孩子，则当前节点无需向下调整
            break;
        }
        else
        {
            A[i] = A[k];
            i = k;//当前节点已经调整，则继续调整当前节点的子节点，所以i = k
        }
    }
    A[i] = tempval;//经过一系列的调整，最终我们被筛选节点的值放入最终的位置
}

void BuildMaxHeap(int *A,int len)
{
	int i;
    for( i = (len/2)-1;i>=0;i--)
    {
        AdjustDown(A,i,len);
    }
}

void heapsort(int *A,int len,int k,int **retArray,int *returnSize)
{//输出长度为len的数组A中的前k大元素
	int i;
    BuildMaxHeap(A,len);//由初始序列A,构造大顶堆，堆是一个逻辑概念，其实就是用数组序列模拟完全二叉树，利用完全二叉树的特征进行排序操作
    for( i = len;i >=len - k +1;i--)//k趟交换和建堆过程
    {
        *retArray = (int*)realloc(*retArray,sizeof(int)*( (*returnSize)+1 ) );
        (*retArray)[(*returnSize)++] = A[0];
        Swap(&A[i-1],&A[0]);//经过建堆，我们得到一个大顶堆，我们可以将最小值A[len-1]与最大值A[0]交换
        AdjustDown(A,0,i-1);//然后从A[0]开始向下调整又得到一个大顶堆，这样重复k次我们就得了前k大元素
    }
}

int main()
{
    int a[10] = {0,1,2,3,4,5,6,7,8,9};
    int *result = NULL;
    int resultSize = 0;
	int i = 0;
    //BuildMaxHeap(a,10);//没毛病

    heapsort(a,sizeof(a)/sizeof(int),5,&result,&resultSize);//没毛病
    printf("the retarray size is %d\n",resultSize);
    for( i =0 ;i < 5;i++)
    {
        printf("%d\n",result[i]);
    }
    system("pause");
}

/*一个关键点就是比较：
    比较成功，满足条件，则不是互换A[i]与A[k]的值，
    而是确定了A[k]的值，由于大小顶堆的性质，
    要所有节点都满足（（A[i]<A[2i]）&&（A[i]<A[2i+1]））或者
    （（A[i]>A[2i]）&&（A[i]>A[2i+1]））,因此，A[i]的值要在已经到了跳出条件才能确定，
    从而我们记录在调整开始前记录的A[0]=A[k]是很重要的。
*/


