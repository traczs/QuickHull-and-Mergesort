
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/timeb.h>
#include <math.h>

struct C{
  double x;
  double y;
};
typedef struct C C;

void quickHull(C* array,C* newArr,int i);
void FindHull(C* array, C P, C Q,C* newArr);

int main(int argc, char* argv[])
{
  FILE* file;
  file = fopen(argv[1],"r");
  struct timeb timestart,timeend;
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
  ftime(&timestart);
  quickHull(array,newArr,i);
  ftime(&timeend);
  timediff = (int)(1000.0 * (timeend.time - timestart.time) + (timeend.millitm - timestart.millitm));
  printf("Time:%d milliseconds\n",timediff);
}

//finds the leftmost and rightmost point , then calls FindHull
void quickHull(C* array,C* newArr,int w)
{
  double maxX = array[0].x;
  double maxY = array[0].y;
  double minX = array[0].x;
  double minY = array[0].y;
  for(int i =1;i<=30000;i++)
  {
    if(array[i].x>=maxX)
    {
      maxX= array[i].x;
      maxY = array[i].y;
    }
    else if(array[i].x<=minX)
    {
      minX = array[i].x;
      minY = array[i].y;
    }
  }
  newArr[0].x = maxX;
  newArr[0].y = maxY;
  newArr[1].x = minX;
  newArr[1].y = minY;
  double a = newArr[0].y - newArr[1].y;
  double b = newArr[1].x - newArr[0].x;
  double c = ((newArr[1].y*newArr[0].x) - (newArr[0].y*newArr[1].x));
  C arrA[30000];
  C arrB[30000];
  int aTurn =0;
  int bTurn =0;
  printf("a %f, b %f ,c %f\n",a,b,c);
  for(int q=2;q<w;q++)
  {
    if(((a*array[q].x) + (b*array[q].y)) > c)
    {
      arrA[aTurn].x = array[q].x;
      arrA[aTurn].y = array[q].y;
      aTurn++;
    }
    else if(((a*array[q].x) + (b*array[q].y)) < c)
    {
      arrB[aTurn].x = array[q].x;
      arrB[aTurn].y = array[q].y;
      bTurn++;
    }
  }

  printf("up %d down %d\n",aTurn, bTurn);
  FindHull(arrA,newArr[0],newArr[1],newArr);
  FindHull(arrB,newArr[1],newArr[0],newArr);
}

//supposed to find the point furthest away from the line and create new subarrays for within the triangle, to the left and right of the triangle
void FindHull(C* array, C P, C Q, C*newArr)
{
  if(array == NULL)
  {
    return;
  }
  double a = P.y - Q.y;
  double b = Q.x - P.x;
  double c = ((Q.y*P.x) - (P.y*Q.x));
  double max=0;
  double pointx;
  double pointy;
  int i=0;
  while(array[i].x != 0)
  {
    double d = abs(((a*array[i].x)+(b*array[i].y)+c))/(sqrt(((int)a^2)+((int)b^2)));
    if(d>max)
    {
      max = d;
      pointx = array[i].x;
      pointy = array[i].y;
    }
    i++;
  }
  int j =0;
  while(newArr[j].x!=0)
  {
    j++;
  }
  newArr[j].x = pointx;
  newArr[j].y = pointy;
  FindHull(newArr,P,newArr[j],newArr);
  FindHull(newArr,Q,newArr[j],newArr);

}
