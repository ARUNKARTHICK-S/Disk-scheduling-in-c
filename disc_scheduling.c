#include<stdio.h>
int top1=-1,top2=-1,top3=-1;
int left[200], right[200];
void fcfs(int a[],int head,int n)
{
	int i,distance,count=0,curr;
	for(i=0;i<n;i++)
	{
		curr=a[i];
		distance=abs(curr-head);
		count+=distance;
		head=curr;
	}
	printf("Total disk movement(FCFS):%d",count);
}
void difference(int a[], int head,int diff[][2], int n)
{
	int i;
    for(i = 0; i < n; i++)
    {
        diff[i][0] = abs(head - a[i]);
    }
}
int findMIN(int diff[][2], int n)
{
    int index = -1;
    int minimum = 1e9;
    int i;
    for(i = 0; i < n; i++)
    {
        if (!diff[i][1] && minimum > diff[i][0])
        {
            minimum = diff[i][0];
            index = i;
        }
    }
    return index;
}
 
void sstf(int a[],int head, int n)
{
	int i,j,count=0; 
    int diff[n][2]; 
    int seekseq[n + 1];
    for(i=0;i<n+1;i++)
    {
    	seekseq[i]=0;
    	for(j=0;j<2;j++)
    	{
    		diff[i][j]=0;
		}
	}
    for(i = 0; i < n; i++)
    {
        seekseq[i] = head;
        difference(a, head, diff, n);
        int index = findMIN(diff, n);
        diff[index][1] = 1;
    	count += diff[index][0];
        head = a[index];
    }
    seekseq[n] = head;
    printf("\nTotal disk movement(sstf):%d",count);
}
void push1(int a[],int v)
{
	a[top1++]=v;
}
void push2(int b[],int v)
{
	b[top2++]=v;
}
void push3(int a[],int v)
{
	a[++top3]=v;
}
void swap(int *x,int *y)
{
	int t;
	t=*x;
	*x=*y;
	*y=t;
}
void bubble(int pr[],int n)
{
	int i,j;
	for(i=0;i<n-1;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(pr[j]>pr[j+1])
			{
				swap(&pr[j],&pr[j+1]);
			}
		}
	}
}
void look(int a[],int head,int n,int range,int end)
{
	int i,j=0,k=0,l,x=0,count=0,temp,lower[n],upper[n],b[n];
	for(i=0;i<n;i++)
	{
		if(a[i]<head)
		{
			lower[j]=a[i];
			j++;
		}
		if(a[i]>head)
		{
			upper[k]=a[i];
			k++;	
		}
	}
	for(i=0;i<j;i++)
	{
		for(l=0;l<j-1;l++)
		{
			if(lower[l]<lower[l+1])
			{
				temp=lower[l];
				lower[l]=lower[l+1];
				lower[l+1]=temp;	
			}		
		}
	}
	for(i=0;i<=k;i++)
	{
		for(l=0;l<k-1;l++)
		{
			if(upper[l]>upper[l+1])
			{
				temp=upper[l];
				upper[l]=upper[l+1];
				upper[l+1]=temp;	
			}		
		}
	}
	
	switch(end)
    {
        case 0:
            for(i=0;i<j;i++)
            {       
                b[x]=lower[i];   
                x++;           
            }
           
            for(i=0;i<k;i++)
            {       
                b[x]=upper[i];
                x++;               
            }
        break;
        case 1:
            for(i=0;i<k;i++)
            {       
                b[x]=upper[i];   
                x++;           
            }
           
            for(i=0;i<j;i++)
            {       
                b[x]=lower[i];
                x++;               
            }
        break;
    }
    count=count+abs(head-b[0]);
    for(i=1;i<x;i++)
    {
        count=count+abs(b[i]-b[i-1]);
    }
    printf("\nTotal disk movement(look):%d",count);
}
void clook(int a[],int head,int n,int k[])
{
	int i,j,count=0;
	for(i=0;i<n-1;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(k[j]>k[i])
            {
                int temp=k[j];
                k[j]=k[i];
                k[i]=temp;
                temp=a[i];
                a[i]=a[j];
                a[j]=temp;
            }
        }
    }
    for(i=0;i<n;i++)
    {
        if(a[i]>=head)
        {
            j=i;
            break;
        }
    }
    for(i=j;i<n;i++)
    {
        count+= abs(head-a[i]);
        head=a[i];

    }
    for(i=0;i<j;i++)
    {
        count+= abs(head-a[i]);
        head=a[i];
    }
	printf("\nTotal disk movement(clook):%d",count);
}
void main()
{
	int n,i,head,range,b,end;
	printf("Enter the number of request:");
	scanf("%d",&n);
	int a[n],k[n];
	printf("Enter the range of the disk:");
	scanf("%d",&range);
	printf("\nEnter the head position:");
	scanf("%d",&head);
	for(i=0;i<n;i++)
	{
		printf("\nEnter the disk value:");
		scanf("%d",&b);
		if(b<=range-1)
		{
			a[i]=b;
			k[i]=head-a[i];
		}
		else
		{
			printf("Enter within the range 0 to %d",range-1);
			i--;
		}
	}
	printf("\nEnter the end to which the head is moving(0 to left side, 1 to right side):");
	scanf("%d",&end);
	fcfs(a,head,n);
	sstf(a,head,n);
	look(a,head,n,range,end);
	clook(a,head,n,k);
	
}
