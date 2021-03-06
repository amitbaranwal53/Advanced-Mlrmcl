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
#define DEBUG cout<<"DEBUG"<<endl;
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
#define MAX 100

char* itoa(int val, int base=10){
	
	static char buf[32] = {0};
	if(!val){buf[0]='0';return &buf[0];}
	int i = 30;
	
	for(; val && i ; --i, val /= base)
	
		buf[i] = "0123456789abcdef"[val % base];
	
	return &buf[i+1];
	
}

float M[MAX][MAX]={0},Mg[MAX][MAX]={0},conv[MAX][MAX]={0};
int v,e;

void Normalise(int v)
{
	int i,j,k;
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

void Regularize(int v)
{
	int i,j;
	float temp[MAX][MAX];
	FOR(i,1,v) FOR(j,1,v) {temp[i][j]=M[i][j];M[i][j]=0;}
	
	FOR(i,1,v)
	FOR(j,1,v)
	FOR(k,1,v)
	M[i][j] = M[i][j]+temp[i][k]*Mg[k][j];
}

void Inflate(int v,int r)
{
	int i,j;
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
	int i,j;
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

void ProjectFlow(char *fname,int gi)
{	//cout<<"PF->"<<fname<<endl;
	FILE *fp=fopen(fname,"r");
	int i,j;
	
	fscanf(fp,"%d%d",&v,&e);
	e++;v++;
	float Gi[MAX][MAX];
	FOR(i,1,v) FOR(j,1,v) fscanf(fp,"%f",&Gi[i][j]);
	int Nodemap1[MAX]={0},Nodemap2[MAX]={0};
	char x[100];
	fscanf(fp,"%s",x);
	//cout<<x<<endl;
	FOR(i,1,v) 
	{
		fscanf(fp,"%d",&Nodemap1[i]);
		//cout<<Nodemap1[i]<<" ";
	}
	fscanf(fp,"%s",x);
	//cout<<endl<<x<<endl;
	FOR(i,1,v)
	{
		fscanf(fp,"%d",&Nodemap2[i]);
		//cout<<Nodemap2[i]<<" ";
	}
	//cout<<endl;
	fclose(fp);
	
	float temp[MAX][MAX],avg,mx;
	FOR(i,1,v) FOR(j,1,v) temp[i][j]=M[i][j];
	
	float zero=((float)0.0)/4;
	FOR(i,1,v) 
	FOR(j,1,v)
	{
		if(temp[i][j] != zero)
		{
		M[Nodemap1[i]+1][Nodemap1[j]+1]=temp[i][j];
		M[Nodemap1[i]+1][Nodemap2[j]+1]=temp[i][j];
		M[Nodemap2[i]+1][Nodemap1[j]+1]=0;
		M[Nodemap2[i]+1][Nodemap2[j]+1]=0;
		}
	}
	/*FOR(i,1,v)
	{FOR(j,1,v)
	cout<<Gi[i][j]<<" ";cout<<endl;}*/
	//cout<<v<<endl;
}
void mg(char *fname,int gi)
{	//cout<<fname<<endl;
	int i,j,k;
	FILE *fp=fopen(fname,"r");
	//int e,v;
	fscanf(fp,"%d%d",&v,&e);
	e++;v++;
	float A[MAX][MAX]={0};
	FOR(i,1,v)	FOR(j,1,v) 	fscanf(fp,"%f",&A[i][j]);				//simple adjacency matrix

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
	fclose(fp);	
}

void CRmcl(char *fname,int r,int c)
{
	int snit=2;
	//cin>>snit;
	char a[100]=".hid/",temp[100];
	strcat(a,fname);
	strcpy(temp,a);
	strcat(temp,itoa(c));
	
	FILE *fp=fopen(temp,"r");
	//int e,v;
	fscanf(fp,"%d%d",&v,&e);
	e++;v++;
	float A[MAX][MAX]={0};
	FOR(i,1,v)	FOR(j,1,v) 	fscanf(fp,"%f",&A[i][j]);				//simple adjacency matrix

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
	fclose(fp);
	//cout<<temp<<endl;
	for(i=c;i>0;i--)
	{
		Normalise(v);
		REP(j,snit)
		{
			Regularize(v);
			Inflate(v,r);
			Prune(v);
		}
		//cout<<temp<<endl;
		ProjectFlow(temp,i);
		strcpy(temp,a);
		strcat(temp,itoa(i-1));
		mg(temp,i-1);
		//cout<<v<<" "<<temp<<" "<<i<<endl;;
	}
}

void Coarse(char *fname,int r,int c)
{
	char a[100]="./co ",temp[100];
	strcat(a,fname);
	
	strcpy(temp,a);
	strcat(temp," > .hid/");
	strcat(temp,fname);
	strcat(temp,"1");
	system(temp);
	
	strcpy(a,"./co .hid/");
	strcat(a,fname);
	for(i=1;i<c;i++)
	{
		
		char t1[10],t2[10],t[100];
		strcpy(t,a);
		if(i<10){t1[0]=i+'0';t1[1]=0;}
		else {t1[0]=(i/10+'0');t1[1]=(i%10+'0');t1[2]=0;}
		
		int j=i+1;
		if(j<10){t2[0]=j+'0';t2[1]=0;}
		else {t2[0]=(j/10+'0');t2[1]=(j%10+'0');t2[2]=0;}
		
		strcat(t,t1);
		strcat(t," > .hid/");
		strcat(t,fname);
		strcat(t,t2);
		//cout<<t<<endl;
		system(t);
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

main(int argc,char** argv)
{
	if(argc < 4)
	{cout<<"USAGE : mlrmcl r clevel filename"<<endl;return 0;}

	system("rm -rf .hid");
	system("mkdir .hid -p");
	char tmp[100]={"cp "};
	strcat(tmp,argv[3]);
	strcat(tmp," .hid/");
	strcat(tmp,argv[3]);
	strcat(tmp,"0");
	system(tmp);
	
	int r,c;
	INPUT(argv[3]);
	r=atoi(argv[1]);
	c=atoi(argv[2]);
	
	Coarse(argv[3],r,c);
	CRmcl(argv[3],r,c);
	
	//RMCL ON Original Graph
	
	FILE *fp=fopen(argv[3],"r");
	int v;
	scanf("%d",&v);v++;
	fclose(fp);
	
	FOR(i,1,v)
	FOR(j,1,v)
	conv[i][j] = M[i][j];
	
	while(isconverge(v))
	{
	Regularize(v);
	Inflate(v,r);
	Prune(v);
	}
	
	int nc = 0,interpret[MAX]={0};
	FOR(i,1,v)
	{FOR(j,1,v)
	{
		//cout<<M[i][j]<<" ";
		if(M[i][j]>0 && interpret[i]==0)
		{
		nc++;
		cout<<i<<" ";
		interpret[i]=interpret[j]=1;
		FOR(k,j+1,v)
		if(M[i][k]>0  && !interpret[k])
		{
			interpret[k]=1;
			cout<<k<<" ";
		}cout<<endl;
		}
	}
	//cout<<endl;
	}
	cout<<endl<<"Number Of Clusters in the given Graph using MLRMCL : "<<nc<<endl<<endl;
	return 0;
}