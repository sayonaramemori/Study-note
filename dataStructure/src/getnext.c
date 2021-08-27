#include<stdlib.h>
#include<stdio.h>
#include<string.h>

void getnext(char *t,int next[]){
	int i=1, j=0;
	int len = strlen(t);
	next[1] = 0;
	while(i<len){
		if(j==0||t[i]==t[j]){
			++i;++j;
			next[i] = j;
		}else j=next[j];
	}
	printf("next:\n");
	for(int i=1;i<=len;++i)
		printf("%d ",next[i]);
}
void getnextval(char*t,int next[]){
	int i=1, j=0;
	int len = strlen(t);
	next[1] = 0;
	while(i<len){
		if(j==0||t[i]==t[j]){
			++i;++j;
			next[i] = j;
			if(t[i]!=t[j]) next[i] = j;
			else next[i] = next[j];
		}else j=next[j];
	}
	printf("nextval:\n");
	for(int i=1;i<=len;++i)
		printf("%d ",next[i]);
}

int main(){
	char *s = "aaaab";
	int next[16];
	getnext(s,next);
	getnextval(s,next);
	return 0;
}
