#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/timeb.h>

struct C{
  double x;
  double y;
};
typedef struct C C;

int main(int argc, char* argv[])
{
  FILE* file;
  file = fopen(argv[1],"r");
  struct timeb timestart, timeend;
  int timediff;
  char string[255];
  C array[100000];
  C newArr[5000];
  char* number;
  int i =0;
  int turn = 0;
  if(!file)
  {
    return 0;
  }
  while(fgets(string,255,file)!=NULL)
  {
    number = strtok(string," ");
    array[i].x = atof(number);
    turn++;
    number = strtok(NULL,"\n");
    array[i].y = atof(number);
    i++;
    turn++;
    while((number = strtok(NULL," \n")) != NULL)
    {
      if(turn%2==0)
      {
        array[i].x = atof(number);
        turn++;
      }
      else
      {
        array[i].y = atof(number);
        turn++;
        i++;
      }
    }
  }
  double a,b,c;
  int up = 1;
  int down = 1;
  int q =0;
  ftime(&timestart);
  for(int j = 0; j<i;j++)
  {
    for(int k =0;k<i;k++)
    {
      if((array[j].x != array[k].x)&&(array[j].y != array[k].y))
      {
        a = array[k].y - array[j].y;
        b = array[j].x - array[k].x;
        c = ((array[k].y*array[j].x) - (array[j].y*array[k].x));
      }
      else
        continue;

      for(int l = 0; l<i;l++)
      {
        if(((array[l].x != array[k].x)&&(array[l].y != array[k].y))&&((array[j].x != array[l].x)&&(array[j].y != array[l].y)))
        {
          if(((a*array[l].x) + (b*array[l].y)) > c)
          {
            down =0;
          }
          else if(((a*array[l].x) + (b*array[l].y)) < c)
          {
            up =0;
          }
          else if(((a*array[l].x) + (b*array[l].y)) == c)
          {
            up = 0;
            down = 0;
            break;
          }
          if((up==0) && (down==0))
            break;
        }
        else
          continue;
      }
      if(up == 1 || down ==1)
      {
        int add1 =1;
        int add2 =1;
        for(int w=0;w<=q;w++)
        {
          if((newArr[w].x == array[j].x) &&(newArr[w].y == array[j].y))
          {
            add1 = 0;
          }
          if((newArr[w].x == array[k].x)&&(newArr[w].y == array[k].y))
          {
            add2=0;
          }
        }
        if(add1==1)
        {
        newArr[q].x = array[j].x;
        newArr[q].y = array[j].y;
        q++;
        }
        if(add2==1)
        {
        newArr[q].x = array[k].x;
        newArr[q].y = array[k].y;
        q++;
        }
        add1=1;
        add2=1;
      }
      up =1;
      down =1;
    }
  }
  for(int s=0;s<q;s++)
  {
    printf("%f %f\n",newArr[s].x ,newArr[s].y );
  }
  ftime(&timeend);
  timediff = (int)(1000.0 * (timeend.time - timestart.time) + (timeend.millitm - timestart.millitm));
  printf("Time:%d milliseconds\n",timediff);
  return 0;
}
