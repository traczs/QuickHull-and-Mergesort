
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/timeb.h>

int main(int argc, char* argv[])
{
  FILE* file;
  file = fopen(argv[1],"r");
  struct timeb timestart, timeend;
  int timediff;
  int array[100000];
  char string[255];
  char* number;
  int num = 0;
  int i =0;
  if(!file)
  {
    return 0;
  }
  while(fgets(string,255,file)!=NULL)
  {
    number = strtok(string," ");
    array[i] = atoi(number);
    i++;
    while((number = strtok(NULL," \n")) != NULL)
    {
      array[i] = atoi(number);
      i++;
    }
  }
  ftime(&timestart);
  //iterates through all the points and ups the counter if left is greater than right
  for(int k = 0; k<i;k++)
  {
    for(int j=k+1;j<i;j++)
    {
      if(array[k]>array[j])
        num++;
    }
  }
  ftime(&timeend);
  timediff = (int)(1000.0 * (timeend.time - timestart.time) + (timeend.millitm - timestart.millitm));
  printf("Number: %d \nTime:%d milliseconds\n",num,timediff);
}
