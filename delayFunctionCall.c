#include <stdio.h>
#include <stdlib.h>

#define RAW 333696

int** DelayFileRead(char* filename, int* row, int* col); //function declaration

int main()
{
	int row = 2607, col = 128;
	char* delayfile="Delay.bin";
	
	int** delayData=DelayFileRead(delayfile, &row, &col);
	
	return 0;
}

int** DelayFileRead(char* filename, int* row, int* col)
{
	FILE *file;
	int i,j,k;
	int *tempDelay = NULL;
	tempDelay = (int*)malloc((RAW/2)*sizeof(int));
	int **delay = NULL; 
	//allwcating memory for delay file
	delay = (int**)malloc((RAW/2)*sizeof(int));
	for(i = 0; i < *row; i++)
	{
		delay[i] = (int*)malloc((*col/2)*sizeof(int));
	}
	if(delay == NULL)
	{
		printf("Memory allocation failed for delay.");
	}
	
	file=fopen(filename,"rb");
	if(file != NULL)
	{
		fread(tempDelay, sizeof(int), RAW/2, file);
		fclose(file);
		k = 0;
		while(k < RAW)
		{
			for(i = 0; i < *row; i++)
			{
				for(j = 0; j < *col/2; j++)
				{
					delay[i][j] = tempDelay[k];
					k++;
				}
			}
		}		
	}
	else
	{
		printf("Error In Delay File Opening");
	}
	return delay;
	
}
