#include <map>
#include <queue>
#include <stack>
#include <ctime>
#include <cmath>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <iostream>
#include <algorithm>


using namespace std;

long int temp,i,j,k,T;

#define CASE while(T--)
#define FOR(I,A,B) for(I=A;I<B;I++)
#define REP(i,n) FOR(i,0,n)
#define FORR(I,J,K) for(I=J;I>K;I--)
#define JAM(N) Case #N:
#define INPUT(A) freopen(A,"r",stdin);
#define OUTPUT(A) freopen(A,"w",stdout);

#define EXP 1e-10
#define INF 1e 10

#define F first
#define S second

typedef long long LL;
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
typedef pair<int,PII> TRI;

#define s(n)					scanf("%d",&n)
#define sl(n) 					scanf("%ld",&n)
#define sll(n) 					scanf("%lld",&n)
#define sf(n) 					scanf("%f",&n)
#define slf(n) 					scanf("%lf",&n)
#define ss(n) 					scanf("%s",n)

int next(){
    char c;int num=0;
    c=getchar_unlocked();
    while(!(c>='0' && c<='9')) c=getchar_unlocked();
    while(c>='0' && c<='9'){
        num=(num<<3)+(num<<1)+c-'0';
        c=getchar_unlocked();
    }
    return num;
}

//main code is here

#define MAX 107

float M[MAX][MAX]={0},Mg[MAX][MAX]={0},conv[MAX][MAX]={0};

void Normalise(int v)
{
	float csum;
	FOR(j,1,v)
	{
		csum=0;
		FOR(k,1,v)
		csum = csum + M[k][j];
		FOR(i,1,v)
		M[i][j] = M[i][j]/csum;
	}
}

inline bool isconverge(int v)
{
	int flag=0;
	FOR(i,1,v)
	FOR(j,1,v)
	if(M[i][j] != conv[i][j])
	break;
	
	if(i==v-1 && j==v-1)
	return true;
	
	FOR(i,1,v)
	FOR(j,1,v)
	conv[i][j] = M[i][j];
	return false;
}

void Expand(int v)
{
	float temp[MAX][MAX];
	FOR(i,1,v) FOR(j,1,v) {temp[i][j]=M[i][j];M[i][j]=0;}
	
	FOR(i,1,v)
	FOR(j,1,v)
	FOR(k,1,v)
	M[i][j] = M[i][j]+temp[i][k]*Mg[k][j];
}

void Inflate(int v,int r)
{
	float temp[MAX][MAX],div;
	FOR(i,1,v) FOR(j,1,v) temp[i][j]=M[i][j];
	
	FOR(j,1,v)
	{
		div=0.0;
		FOR(k,1,v)
		div = div + pow(temp[k][j],r);
		FOR(i,1,v)
		M[i][j]=pow(temp[i][j],r)/div;
	}
}

void Prune(int v)
{
	int i,j,k;
	float temp[MAX][MAX],avg,mx;
	FOR(i,1,v) FOR(j,1,v) temp[i][j]=M[i][j];
	
	FOR(j,1,v)
	{
		avg=0;
		mx=-1.0;
		FOR(k,1,v)
		{
		avg = avg + temp[k][j];
		mx = max(mx,temp[k][j]);
		}
		avg = avg/(v-1);
		float threshold=avg/4;
		FOR(i,1,v)
		if(M[i][j] < threshold)
		M[i][j]=0;	
	}
	Normalise(v);
}

main(int argc,char** argv)
{
	if(argc < 3)
	{cout<<"USAGE : rmcl r filename"<<endl;return 0;}
	
	INPUT(argv[2]);
	int v=next(),e=next(),a,b;
	int r=2;
	
	r=atoi(argv[1]);
	
	e++;v++;
	float A[MAX][MAX]={0};

	//input read
	//FOR(i,1,e){s(a);s(b);A[a][b]=A[b][a]=1;}  		//in .adj format
	FOR(i,1,v)	FOR(j,1,v) 	sf(A[i][j]);				//simple adjacency matrix

	FOR(i,1,v) A[i][i]=1.0;						     		//self loops
	
	float D[MAX][MAX]={0};
	FOR(i,1,v)
	FOR(j,1,v)
	D[i][i]+=A[i][j];
	float invD[MAX][MAX]={0};
	FOR(i,1,v) invD[i][i]=1.0/D[i][i];						//Got D inverse
		
	FOR(i,1,v)
	FOR(j,1,v)
	FOR(k,1,v)
	M[i][j]=M[i][j] + A[i][k]*invD[k][j];					//Got M
	
	FOR(i,1,v)
	FOR(j,1,v)
	Mg[i][j]=M[i][j];
	
	Normalise(v);
	
	FOR(i,1,v)
	FOR(j,1,v)
	conv[i][j] = M[i][j];
	
	while(isconverge(v))
	{
	Expand(v);
	Inflate(v,r);
	Prune(v);
	}
	
	int nc = 0,interpret[MAX]={0};
	FOR(i,1,v)
	FOR(j,1,v)
	{
		if(M[i][j]>0 && interpret[i]==0)
		{
		nc++;cout<<i<<" ";
		interpret[i]=interpret[j]=1;
		FOR(k,j+1,v)
		if(M[i][k]>0  && !interpret[k])
		{interpret[k]=1;cout<<k<<" ";}cout<<endl;
		}
	}
	
	cout<<endl<<"Number Of Clusters in the given Graph using RMCL : "<<nc<<endl<<endl;
	return 0;
}
