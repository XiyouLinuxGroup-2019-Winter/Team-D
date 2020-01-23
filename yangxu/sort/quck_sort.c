#include<stdio.h>
int wakong(int a[],int b,int c)
{
	int i,j,x;
	i=b;j=c;x=a[b];
	while(i<j){ 
		while(i<j&&a[j]>=x) j--;
		if(j>i){
			a[i]=a[j];
			i++;
		}
		while(i<j&&a[i]<x) i++;
		if(j>i){
			a[j]=a[i];
			j--;
		}
	}
	a[i]=x;
	return i;
}
void quck(int a[],int b,int c)
{
	 if(b<c){
	 	int i=wakeng(a,b,c);
	 	quck(a,b,i-1);
	 	quck(a,i+1,c);
	 }
}
int main ()
{
	int n,i,j,k,m,x;
	int num[82];
	scanf("%d",&n);
	for(i=0;i<n;i++){
		scanf("%d",&num[i]);
	}
	quck(num,0,n-1);
	for(i=0;i<n;i++){
		printf("%d ",num[i]);
	}
}
