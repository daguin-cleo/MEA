#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>

// maximum size of the buffer
#define SIZE_BUF_MAX 67108864 

int MAX_NB_DATA = 1000;
int NB_DATA = 0;

static int compare (void const *a, void const *b)
{
  int const *pa = a;
  int const *pb = b;
  return *pa - *pb;
}

double getTime(void) /**/
{
  struct timeval t;
  gettimeofday(&t, NULL);
  return (1.0e-6*t.tv_usec + t.tv_sec);
}

void initDataGenerator(char *s)
{
  sscanf(s,"%d",&MAX_NB_DATA);
  MAX_NB_DATA = MAX_NB_DATA * 1000000;
  NB_DATA = 0;
  srand (0);
}

int getData()
{
  int n1, n2, n;
  if (NB_DATA >= MAX_NB_DATA) return -1;
  n1 = rand();
  n2 = rand();
  n1 = n1&0x3FFFFFF;
  n2 = n2&0x3FFFFFF;
  n = (n1+n2)&0xFFFFFFF;
  NB_DATA++;
  return n;
}

int main (int argc, char *argv[])
{
  int *BUFFER = (int *) malloc(sizeof(int)*SIZE_BUF_MAX);
  int nb_data;
  int data;
  FILE *foutput;
  double t1, t2;

  // initialisation du generateur de nombres aleatoires
  initDataGenerator(argv[1]);

  // ===============================================================
  // remplacer cette section de code

  nb_data = 0;
  while ((data=getData()) != -1)
    {
      if (nb_data < SIZE_BUF_MAX)
	{
	  BUFFER[nb_data] = data;
	  nb_data++;
	}
    }

  // ===============================================================

  printf ("write data\n");
  t1 = getTime();
  foutput = fopen("64M_sort.data","w");
  fwrite(BUFFER,sizeof(int),SIZE_BUF_MAX,foutput);
  fclose(foutput);
  t2 = getTime();
  printf (" - time: %1.2lf sec\n",t2-t1);

}
