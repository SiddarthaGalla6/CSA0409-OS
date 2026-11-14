/* CODE: */
#include <stdio.h>
#define N 4
int main(void) {
 const char *name[N]={"P1","P2","P3","P4"};
 int arrival[N]={0,1,2,3},burst[N]={8,4,9,5},q=3;
 int left[N],finish[N],queue[128],head=0,tail=0,added[N]={0};
 for(int i=0;i<N;i++)left[i]=burst[i];
 int time=0,done=0; queue[tail++]=0; added[0]=1;
 printf("Gantt:");
 while(done<N) {
  if(head==tail) {
   for(int i=0;i<N;i++) if(!added[i]&&arrival[i]<=time){queue[tail++]=i;added[i]=1;}
   if(head==tail){time++;continue;}
  }
  int p=queue[head++],run=left[p]<q?left[p]:q,start=time;
  time+=run; left[p]-=run;
  printf(" %s(%d-%d)",name[p],start,time);
  for(int i=0;i<N;i++) if(!added[i]&&arrival[i]<=time){queue[tail++]=i;added[i]=1;}
  if(left[p]>0)queue[tail++]=p; else {finish[p]=time;done++;}
 }
 double tw=0,tt=0; printf("\nProcess TAT WT\n");
 for(int i=0;i<N;i++){int tat=finish[i]-arrival[i],wt=tat-burst[i];tt+=tat;tw+=wt;printf("%-7s %4d %3d\n",name[i],tat,wt);}
 printf("Average TAT = %.2f, average WT = %.2f\n",tt/N,tw/N);
 return 0;
}

/*
Input:
No keyboard input. The process arrival times, burst times and time quantum q=3 are defined in the program.
Output (reference/sample):
Gantt: P1(0-3) P2(3-6) P3(6-9) P4(9-12) P1(12-15) P2(15-16) P3(16-19) P4(19-21) P1(21-23) P3(23-26)
Process TAT WT
P1        23  15
P2        15  11
P3        24  15
P4        18  13
Average TAT = 20.00, average WT = 13.50
*/
