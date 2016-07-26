#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#define N 10
#define H 20

struct task{
	int fi;
	int pi;
	int ei;
	int Di;
};

struct job{
	int ri;
	int ei;
	int di;
	int jno;
	struct job *ptr;
};

struct pr_q{
  int para;
  int task_no;
  int pr;
};

int next_riT[N];
int no_job[N],count[N],j_in_pr=0;
struct pr_q pr_queue[N*3];
struct task T[N];
struct job *J[N],*front[N],*rear[N];

int crnt_pr[N];
int u_intvl=0,tot_task;

main()
{
	FILE *fp1;
	int i,j,k;
	int is_reles=0,t_no;

	int add_new_ifreleased();
	void find_pr();
	void sort_jobs(struct pr_q a[]);
	void assign_pr(struct pr_q a[]);
	void run_job(int t_no);
	void traverse();
	clrscr();

	fp1=fopen("c:\\rmtable.txt","r");
	printf("\n\t\t\tRM SCHEDULING ALGO\n");

	fscanf(fp1,"%d",&tot_task);
	printf("Total Task=%d\n",tot_task);
	printf("\nTask fi  pi  ei  Di");

	for(i=0;i<tot_task;i++)
	{
	 fscanf(fp1,"%d %d %d %d",&T[i].fi,&T[i].pi,&T[i].ei,&T[i].Di);
	 next_riT[i]=T[i].fi;
	 no_job[i]=0;
	 count[i]=0;
	 printf("\n %d   %d  %d  %d  %d",i,T[i].fi,T[i].pi,T[i].ei,T[i].Di);
	}

	printf("\n\t\t---------------------------");
	printf("\n\t\tstart end   Job   comment");
	printf("\n\t\t---------------------------\n");
	u_intvl=0;
	while(u_intvl<=H)
	{
	  is_reles=add_new_ifreleased();
	  find_pr();
	  if(j_in_pr>0){
	      t_no=pr_queue[0].task_no;
	      run_job(t_no);
	  }
	  u_intvl++;
	}
	//printf("\nTraversed List\n");
	//traverse();
	getch();

}


int add_new_ifreleased()
{
	int i=0,p=1,index,flag=0;
	struct job *old,*newj;
	void traverse();
	for(i=0;i<tot_task;i++)
	{
//	   printf("\n");
	   if((T[i].fi+T[i].pi*no_job[i])==u_intvl)
	   {
	     flag=1;
	     newj=(struct job *)malloc(sizeof(struct job));
	     newj->ri=T[i].fi;
	     newj->ei=T[i].ei;
	     newj->di=u_intvl+T[i].Di;
	     newj->jno=no_job[i];
	     if(count[i]!=0){
		rear[i]->ptr=newj;
		rear[i]=newj;
	     }
	     else{
		J[i]=newj;
		front[i]=newj;
		rear[i]=newj;
//		printf("\nFirst job of task %d",i);
	     }
	     rear[i]->ptr=NULL;

	     no_job[i]++;
	     count[i]++;

//	     printf("\n%d %d %d %x",rear[i]->ri,rear[i]->ei,rear[i]->di,rear[i]->ptr);
	   }//end of if statement
	}
//	printf("\nin release:");
//	traverse();
	getch();
	return flag;

}

void run_job(int t_no)
{
  int i,j;
  void traverse();
  struct job *cjob;
  J[t_no]->ei--;
  printf("\n\t\t  %d    %d    J%d,%d",u_intvl,u_intvl+1,t_no,J[t_no]->jno);
  //is job completes execution
  if(J[t_no]->ei == 0)
  {
    printf("\tJ%d,%d will end at %d",t_no,J[t_no]->jno,u_intvl+1);
    cjob=J[t_no];
    front[t_no]=J[t_no]->ptr;
    J[t_no]=J[t_no]->ptr;
     /*if(J[t_no] != NULL){
     printf("\nin run after j completes\n");
     printf("\n%d %d %d %x",J[t_no]->ri,J[t_no]->ei,J[t_no]->di,J[t_no]->ptr);
     }
     else
     printf("\nlist empty");
     getch();*/
    //free(cjob);
    count[t_no]--;
  }
 // traverse();
}


void traverse()
{
	int i,j;
	struct job *ptrn;
	for(i=0;i<tot_task;i++)
	{
		printf("\nList of Jobs of task %d",i);
		ptrn=J[i];
		for(j=0;j<count[i];j++)
		{
		 printf("\n%d %d %d %x",ptrn->ri,ptrn->ei,ptrn->di,ptrn->ptr);
		 ptrn=ptrn->ptr;
		}
	}
}

void find_pr()
{
   int i,j;
   void sort_jobs(struct pr_q a[]);
   void assign_pr(struct pr_q a[]);

   j_in_pr=0;
   for(i=0;i<tot_task;i++)
   {
       if(count[i] != 0){
	pr_queue[j_in_pr].para=J[i]->ri;
	pr_queue[j_in_pr].task_no=i;
	j_in_pr++;
       }
   }
   sort_jobs(pr_queue);
   assign_pr(pr_queue);
//   printf("\nAssigned priorities list:\n");
//   printf("\ndi  no pr");
  // for(i=0;i<j_in_pr;i++)
    // printf("\n%d   %d  %d",pr_queue[i].para,pr_queue[i].task_no,pr_queue[i].pr);
     //getch();
}

void sort_jobs(struct pr_q a[])
{
    int sorted_size;
    int min_element_index;
    int min_element_value;

    int i,temp;

    for(sorted_size=0; sorted_size < j_in_pr; sorted_size++)
    {
	min_element_index = sorted_size;
	min_element_value= a[sorted_size].para;
	for(i=sorted_size+1; i<j_in_pr; i++)
	{
	    if (a[i].para < min_element_value)
	    {
		min_element_index = i;
		min_element_value = a[i].para;
	    }
	}
	a[min_element_index].para = a[sorted_size].para;
	a[sorted_size].para = min_element_value;

	temp = a[min_element_index].task_no;
	a[min_element_index].task_no = a[sorted_size].task_no;
	a[sorted_size].task_no = temp;
    }
}


void assign_pr(struct pr_q a[])
{
   int i,j,prio=1,flag,temp;
   for(i=0;i<j_in_pr-1;i++)
   {
      if(a[i].para<a[i+1].para)
	  a[i].pr=prio++;
      else{
	 if(a[i].para==a[i+1].para){
	   //arrang as per release time
	   if(J[a[i].task_no]->ri > J[a[i+1].task_no]->ri)
	   {
	     //swap them
	     temp=a[i].task_no;
	     a[i].task_no=a[i+1].task_no;
	     a[i+1].task_no=temp;
	   }
	   a[i].pr=prio;
	 }
      }
   }
   a[i].pr=prio;
}


