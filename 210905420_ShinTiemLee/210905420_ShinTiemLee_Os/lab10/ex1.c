#include<stdio.h>
#include<stdlib.h>
int allocation[10][10];
int max[10][10];
int available[10];
int finish[10];


int checkstate(int num,int m,int n){
	int flag=0;
	int f=0;
	finish[num]=1;
	while(flag==0){
	flag=1;
	for(int i=0;i<m;i++){
	if(finish[i]==1)
		continue;
	else{
		f=0;
	for(int j=0;j<n;j++){
	if(available[j]<(max[i][j]-allocation[i][j])){		
		f=1;
	}
	if(f==0){
		finish[i]=1;
		flag=0;
		for(int j=0;j<m;j++)
			available[j]+=allocation[i][j];	
	}
	}
	}
	}
}
for(int j=0;j<m;j++){
		if(finish[j]==0)
			return 0;

		printf("Safe state:\t");
		return 1;
}
}

int main(){
int num;
int m,n;
printf("Enter number of processes:");
scanf("%d",&m);
printf("Enter number of resource types:");
scanf("%d",&n);
int request[n];
printf("Enter allocation mat:\n");
for(int i=0;i<m;i++){
	for(int j=0;j<n;j++){
		scanf("%d",&allocation[i][j]);
	}
}
printf("Enter max mat:\n");
for(int i=0;i<m;i++){
	for(int j=0;j<n;j++){
		scanf("%d",&max[i][j]);
	}
}
printf("Enter available array:\n");
for(int j=0;j<n;j++){
		scanf("%d",&available[j]);
	}
for(int j=0;j<m;j++){
		finish[j]=0;
	}
printf("Enter process that requests:");
scanf("%d",&num);
printf("Enter request:");
for(int i=0;i<n;i++){
	scanf("%d",&request[i]);
	available[i]-=request[i];
	if(available[i]<0){
		printf("Unsafe state");
	return 0;
	}
}

if(checkstate(num,m,n)==0)
	printf("Unsafe state");
	return 0;
	
}