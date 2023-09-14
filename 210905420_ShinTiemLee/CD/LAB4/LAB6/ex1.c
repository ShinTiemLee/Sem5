#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int cur = 0;
char str[100];

void S();
void T();
void Tprime();

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
	if (str[cur]=='a'){
		cur++;
	}
	else if (str[cur]=='>'){
		cur++;
	}
	else if (str[cur]=='('){
		cur++;
		T();
		if(str[cur]==')'){
			cur++;
		}
	}
	else{
		invalid();
	}
}


void T()
{
S();
Tprime();
}

void Tprime()
{
if(str[cur] == ',')
{
cur++;
S();
Tprime();
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