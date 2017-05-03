/***********************************************
Samuel Tracz
0927451
CIS 3490 Assignment 1
February 13, 2017
**********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/timeb.h>

int  sort(int array[], int temp[], int left, int right);
int merge(int array[], int temp[], int left, int mid, int right);
int mergeSort(int array[], int arrSize);

//divides the array to two smaller arrays recursively and checks if left is greater than right to add to counter
int sort(int array[], int temp[], int left, int right)
{
  int mid, inverNum = 0;
  if (right > left)
  {
    mid = (right + left)/2;
    inverNum  = sort(array, temp, left, mid);
    inverNum = inverNum + sort(array, temp, mid+1, right);
    inverNum = inverNum + merge(array, temp, left, mid+1, right);
  }
  return inverNum;
}

//mergest the subarrays together and adds the number of times that left is greater than right
int merge(int array[], int temp[], int left, int mid, int right)
{
  int i = left;
  int j = mid;
  int k = left;
  int inverNum = 0;

  while ((i <= mid - 1) && (j <= right))
  {
    if (array[i] <= array[j])
    {
      temp[k++] = array[i++];
    }
    else
    {
      temp[k++] = array[j++];

      inverNum = inverNum + (mid - i);
    }
  }

  while (i <= mid - 1)
  {
    temp[k++] = array[i++];
  }
  while (j <= right)
  {
    temp[k++] = array[j++];
  }

  for (i=left; i <= right; i++)
  {
    array[i] = temp[i];
  }
  return inverNum;
}

//returns the answer
int mergeSort(int array[], int arrSize)
{
    int *temp = (int *)malloc(sizeof(int)*arrSize);
    return sort(array, temp, 0, arrSize - 1);
}

int main(int argc, char* argv[])
{
  FILE* file;
  file = fopen(argv[1],"r");
  struct timeb timestart, timeend;
  int timediff;
  int array[100000];
  char string[255];
  char* number;
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
  printf("Number: %d \n", mergeSort(array, 50000));
  ftime(&timeend);
  timediff = (int)(1000.0 * (timeend.time - timestart.time) + (timeend.millitm - timestart.millitm));
  printf("Time:%d milliseconds\n",timediff);
}
