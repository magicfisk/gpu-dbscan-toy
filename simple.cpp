#include<stdio.h>
#include<string.h>
#include<memory>
#include<math.h>
#include<iostream>
#include<algorithm>
#define N 1000000
#define CN 10
#define Max 1000000
#define ptsize 1000
#define sqr(x) ((x)*(x))
double esp=200;
int m=20;



struct pt
{
	int x[2];
};

pt tmp[N+100];
pt point[N+100];
int tag[N+100];
int list[N+100];
int inside[N+100];
int n;

int index[N+100];
int reindex[N+100];
int pre[N+100];
int next[N+100];

double dis(int x,int y)
{
	return sqrt(sqr(point[x].x[0]-point[y].x[0])+sqr(point[x].x[1]-point[y].x[1]));
}

int get_neighbor(int x)
{
	int cnt=0; int idx=list[0];
	for (int i=pre[x];i<x;++i)
		if (dis(i,x)<esp)
		{
			if (inside[i]==0)
			list[idx++]=i;
			cnt++;
		}
	for (int i=x+1;i<=next[x];++i)
		if (dis(i,x)<esp)
		{
			if (inside[i]==0)
			list[idx++]=i;
			cnt++;
		}
	if (cnt>m) 
	{
		for (int i=list[0];i<idx;++i) inside[list[i]]=1;
		list[0]=idx;
	}
	return cnt;		
}


bool compare(int a,int b)
{
	return tmp[a].x[0]<tmp[b].x[0];
}

int main()
{
	freopen("data.txt","r",stdin);
	freopen("ans.txt","w",stdout);
	memset(tag,0,sizeof(tag));
	scanf("%d",&n);
	for (int i=0;i<n;++i)
	{
		scanf("%d %d",&tmp[i].x[0],&tmp[i].x[1]);
		index[i]=i;
	}
	std::sort(index,index+n,compare);
	for (int i=0;i<n;++i)
	{
		point[i]=tmp[index[i]];
		reindex[index[i]]=i;
	}
	int flag=0;
	for (int i=0;i<n;++i)
	{
		while (point[flag].x[0]+esp<point[i].x[0]) flag++;
		pre[i]=flag;
	}
	flag=n-1;
	int maxlen=0;
	for (int i=n-1;i>=0;--i)
	{
		while (point[flag].x[0]-esp>point[i].x[0]) flag--;
		next[i]=flag;
		if (next[i]-pre[i]>maxlen) maxlen=next[i]-pre[i];
	}
	std::cerr<<maxlen<<"\n";
	int x=0;
	int cor=0;
	for (x=0;x<n;++x)
	{
		list[0]=1;
		if (tag[x]==0)	
		{
			int size=get_neighbor(x);
			if (size<m) tag[x]=-1;
			else
			{
				cor++;
				tag[x]=cor;
				std::cerr<<cor<<" "<<x<<"\n";
				for (int i=1;i<list[0];++i)
				{
					if (tag[list[i]]==-1)
						tag[list[i]]=cor;
					if (tag[list[i]]==0) 
					{
						tag[list[i]]=cor;
						get_neighbor(list[i]);
					}
				}
			}
		}
	}
	for (int i=0;i<n;++i)
		printf("%d %d\n",i,tag[reindex[i]]);
}
