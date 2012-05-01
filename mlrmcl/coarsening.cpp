#include<stdio.h>
#include<cstdlib>
#include<iostream>
#include<cstring>
#include <list>

#define MAX 1000

using namespace std;

float adjecency[MAX+1][MAX+1];
float coarse[MAX+1][MAX+1];
int cmap[MAX+1];
int matched[MAX+1];
int edj[MAX+1];
int xadj[MAX+1];
float adjwt[MAX+1];
int numedges[MAX+1];
int nodemap1[MAX+1];
int nodemap2[MAX+1];

void update1(int num,int n,int m)
{
	int i,j,k;	
	//Here's the weight handling

for(i=0;i<num;i++)
{
	int count=0,a1,a2,b1,b2;
	
	for(j=i+1;j<=num;j++)
	{   
		for(int k=0;k<n;k++)
		{
			if(cmap[k]==i){a1=k;a2=matched[k];nodemap1[i]=k;nodemap2[i]=matched[k];}
			if(cmap[k]==j){b1=k;b2=matched[k];}
		}
		//cout<<a1<<" "<<a2<<" "<<b1<<" "<<b2<<endl;
		if(adjecency[a1][b1])
			{
				coarse[i][j]+=adjecency[a1][b1];
				adjecency[a1][b1]=0;
			}
	    
		if(adjecency[a1][b2])
			{
				coarse[i][j]+=adjecency[a1][b2];
				adjecency[a1][b2]=0;
			}
		
		if(adjecency[a2][b1])
			{
				coarse[i][j]+=adjecency[a2][b1];
				adjecency[a2][b1]=0;
			}
		
		if(adjecency[a2][b2])
			{
				coarse[i][j]+=adjecency[a2][b2];
				adjecency[a2][b2]=0;
			}
	    
			coarse[j][i]=coarse[i][j];
		
		}
	
}


//Weight handling ends here
int cc=0;
for(i=0;i<num;i++)
for(j=0;j<num;j++)
	if(coarse[i][j]) cc++;

cout<<num<<" "<<(cc>>1)<<endl;
	
for(i=0;i<num;i++)
	{
	for(j=0;j<num;j++)
	cout<<coarse[i][j]<<" ";
	cout<<endl;
	}
cout<<"Nodemap1:"<<endl;
	for(i=0;i<num;i++)cout<<nodemap1[i]<<" ";
		cout<<endl;
	cout<<"Nodemap2:"<<endl;
	for(i=0;i<num;i++)cout<<nodemap2[i]<<" ";



}

void update(int num,int n,int m)
{
int i,j;
for(i=0;i<n;i++)
{
for(j=xadj[i];j<xadj[i+1];j++)
{
    if(edj[j]==matched[i])
    {
	edj[j]=-1;
    adjwt[j]=0;
	}
}
}


}

void match(int n,int m)
{
    int num=0;
for(int i=0;i<n;i++)
{
    if(matched[i] == -1)
    {

      //printf("%d\n",i);
      for(int j=xadj[i];j<xadj[i+1];j++)
      {
       if(matched[edj[j]]==-1)
       {
       matched[edj[j]]=i;
       matched[i]=edj[j];
       cmap[i]=cmap[edj[j]]=num;
       num++;
       numedges[num]=(xadj[i+1]-xadj[i])+(xadj[edj[j]+1]-xadj[edj[j]]);
       break;
       }
      }
    }

}

for(int i=0;i<n;i++)
{
    if(matched[i]==-1)
    {
        matched[i]=i;
        cmap[i]=num++;
        numedges[num]=(xadj[i+1]-xadj[i]);
}
}
update(num,n,m);
update1(num,n,m);
}

int main(int argc,char** argv)
{
	char str[100000];
	freopen(argv[1],"r",stdin);
    int m,n,i,j,a,k,l;
    char *ptr;
	scanf("%d %d",&n,&m);
	i=0,k=0,l=0;
	int count=0;

	for(i=0;i<n;i++)
	{
	xadj[k++]=count;
	for(j=0;j<n;j++)
	{
	cin>>adjecency[i][j];
	if(adjecency[i][j])
	{
		edj[count]=j;
		adjwt[count]=adjecency[i][j];
		count++;
	}
	}
	}
	xadj[k++]=count;
		
	for(i=0;i<n;i++)
    matched[i]=-1;

	match(n,m);
    cout<<endl;
	return 0;
}
