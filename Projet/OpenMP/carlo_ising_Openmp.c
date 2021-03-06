#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <omp.h>
#include "includeOpen.h"


double get_time() {

  struct timeval tv;

  gettimeofday(&tv, (void *)0);

  return (double) tv.tv_sec + tv.tv_usec*1e-6;

}


int main(int argc, char**argv)
{

  double start,stop;

  double cpu_time_used; 

  int i,j,spin[N][N],runs;
  int ai,aj, T;
  double en_old,en_new,H,r;
  double beta;
  int* tab = NULL;
  
  

	runs = atoi(argv[1]);

  T = atoi(argv[2]);

  tab=malloc(sizeof(int)*runs*4);


  // initial fill
  for (i=0; i<N; i++)
  {
    for (j=0; j<N; j++)
    {
      spin[i][j] = updown();
      printf("%d", spin[i][j]);
    }
    printf("\n");
  }
  	 
  beta = 1/((1.38064852*pow(10,-23))*T);

  start = get_time();

  #pragma omp for schedule(dynamic,1000)
	  for(int run = 0; run<runs; run++)
	  {

	    monte_carlo(spin,tab,run, beta);
	  	
	  } 
  stop = get_time();  

  cpu_time_used = stop -start;
  
  

  ising_output(tab,cnt);

   printf("Time excution Mont Carlo %f\n", cpu_time_used);

   free(tab);

  return 0;
}
