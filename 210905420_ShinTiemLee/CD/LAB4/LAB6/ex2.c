#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int cur = 0;
char str[100];

void S();
void U();
void V();
void W();

void invalid()
{
printf("-----------------ERROR!----------------\n");
exit(0);
}

void valid()
{
printf("----------------SUCCESS!---------------\n");
exit(0);
}

void S()
{
	U();
	V();
	W();
}


void U()
{
if (str[cur]=='('){
		cur++;
		S();
		if(str[cur]==')')
			cur++;
		else
			invalid();
	}
	else if (str[cur]=='d'){
		cur++;
	}
	else if (str[cur]=='a'){
		cur++;
		S();
		if(str[cur]=='b'){
			cur++;
		}
		else
			invalid();
	}
	else{
		invalid();
	}
}

void V()
{
if(str[cur] == 'a')
{
cur++;
V();
}
}

void W()
{
if(str[cur] == 'c')
{
cur++;
W();
}
}



int main()
{
printf("Enter String: ");
scanf("%s", str);
S();
if(str[cur] == '$')
valid();
else{
invalid();
}
}