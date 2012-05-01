#include<iostream>
#include<stdio.h>
#include<string.h>
#include<algorithm>
#define Max 175
using namespace std;

int g[Max][Max]={0};

main(int argc,char **argv)
{
	int a,b,c,n=-1,e,i,j;
	freopen(argv[1],"r",stdin);
	freopen(strcat(argv[1],".graph"),"w",stdout);
	e=0;
	while(cin>>a>>b>>c) {g[a][b]=g[b][a]=c;e++;n=max(n,max(a,b));}
	cout<<n<<" "<<e<<endl;
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			cout<<g[i][j]<<" ";
		}
		cout<<endl;
	}
	return 0;
}