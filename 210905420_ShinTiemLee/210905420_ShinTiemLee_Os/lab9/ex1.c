#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct mab {
int size;
int allocated;
struct mab * next;
struct mab * prev;
};

typedef struct mab Mab;
typedef Mab * MabPtr;

MabPtr memChk(MabPtr m, int size); // check if memory available
MabPtr memAlloc(MabPtr m, int size); // allocate a memory block
MabPtr memFree(MabPtr m);// free memory block
MabPtr memMerge(MabPtr m);// merge two memory blocks
MabPtr memSplit(MabPtr m, int size); // split a memory block

MabPtr memGet(int size){
	MabPtr temp=(MabPtr)malloc(sizeof(struct mab));
	temp->size=size;
	temp->allocated=0;
	temp->next=NULL;
	temp->prev=NULL;
	return temp;

}

MabPtr memCreatePartition(MabPtr head, int size){
	if(!head){
		head=memGet(size);
		return head;
	}
	else{
		MabPtr walk=head;
		MabPtr pre;
		while(walk){
			pre=walk;
			walk=walk->next;
		}
		walk=memGet(size);
		walk->prev=pre;
		pre->next=walk;
		return walk;
	}

}

MabPtr memChk(MabPtr m, int size){
	MabPtr walk=m;
	while(walk!=NULL){
	if(walk->size>=size && walk->allocated==0)
		return walk;
	walk=walk->next;
	}
	return walk;
}

MabPtr memAlloc(MabPtr m,int size){
	m->allocated=1;
	return m;
}

MabPtr memFree(MabPtr m){
	m->allocated=0;
	return m;
}

MabPtr memMerge(MabPtr m){
	MabPtr suc1=m->next;
	MabPtr suc2=suc1->next;
	m->size=m->size + suc1->size;
	m->next=suc2;
	if(suc2!=NULL){
		suc2->prev=m;
	}
	return m;
}

MabPtr memSplit(MabPtr m, int size){
	MabPtr new=memGet(m->size-size);
	(m->next)->prev=new;
	new->next=m->next;
	new->prev=m;
	m->next=new;
	return m;
}

int main(){
	int process_list[5];
	printf("Enter 5 process sizes:\n");
	for(int i=0;i<5;i++){
		printf("\nProcess %d:",i+1);
		scanf("%d",&process_list[i]);
	}
	MabPtr head=NULL;
	head=memCreatePartition(head,500);
	memCreatePartition(head,400);
	memCreatePartition(head,300);
	memCreatePartition(head,200);
	memCreatePartition(head,100);
	printf("Enter \n1 for first fit\n2 for best fit\n3 for worst fit:");
	int ch;
	scanf("%d",&ch);
	MabPtr temp,walk,use;
	use=NULL;
	switch(ch){
		case 1:
			for(int i=0;i<5;i++){
				temp=memChk(head,process_list[i]);
				if(temp==NULL){
					printf("\nNo sufficient space\n");
					exit(0);
				}
				memAlloc(temp,process_list[i]);
				printf("\nProcess %d has been allocated memory",i+1);

			}
			exit (0);
		case 2: 
			int min;
			for(int i=0;i<5;i++ ){
				walk=head;
				use=NULL;
				min=1000;
				while(walk){
					temp=memChk(walk,process_list[i]);
					if(temp==NULL){
						break;
					}
					if(min>temp->size)
						min=temp->size;
						use=temp;
					walk=walk->next;
				}

				if(use==NULL){
					printf("\nNo sufficient space\n");
					exit(0);
				}

				memAlloc( use,process_list[i]);
				printf("\nProcess %d has been allocated memory",i+1);
			}
			exit(0);
		case 3: 
			int max;
			for(int i=0;i<5;i++ ){
				walk=head;
				use=NULL;
				max=0;
				while(walk){
					temp=memChk(walk,process_list[i]);
					if(temp==NULL){
						break;
					}
					if(max<temp->size)
						max=temp->size;
						use=temp;
					walk=walk->next;
				}

				if(use==NULL){
					printf("\nNo sufficient space\n");
					exit(0);
				}

				memAlloc( use,process_list[i]);
				printf("\nProcess %d has been allocated memory",i+1);
			}
			exit(0);
}
}