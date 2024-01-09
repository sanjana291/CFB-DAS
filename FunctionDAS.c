#include <stdio.h>
#include <stdlib.h>

#define RAW 333696

int** DelayFileRead(char* filename, int* row, int* col); //function declaration for delay
double** CFB_DAS(int** delay, int* row, int* col); //function declaration for cfb das
void storebin(const char* filename, double** array, int numRows, int numColumns);


int main()
{
	int row = 2607, col = 128;
	char* delayfile="Delay.bin";

	int** delayData=DelayFileRead(delayfile, &row, &col);
	double** BF=CFB_DAS(delayData, &row, &col);
	storebin("DAS_Jan9_2024_ver2.bin", (double **)BF, row, 65);

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
		while(k < RAW/2)
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

double** CFB_DAS(int** delay, int* row, int* col)
{
	int i,j,k,n;
	int start=0,end=63;
	double tempD[*row];
	int z1;
	double data_in[*row][*col/2];
	double** bf = NULL;
	bf=(double**)malloc(*row * sizeof(double));
	for(i=0; i<*row; i++)
	{
		bf[i]=(double*)malloc(*col/2 * sizeof(double));
	}
	if(bf == NULL)
	{
		printf("Memory allocation failed for BeamForming.");
	}
	
	for(n=1; n<=65; n++)
	{
		FILE *file;
		char filename[10];
		double *temp=NULL;
		temp=(double*)malloc(RAW * sizeof(double));
		if (temp == NULL) 
		{
			printf("Memory allocation failed for temp.");
		}
	
		double **data=NULL;
		data=(double**)malloc(*row * sizeof(double));
		for(i=0; i<*row; i++)
		{
			data[i]=(double*)malloc(*col * sizeof(double));
		}
		if (data == NULL) 
		{
			printf("Memory allocation failed for data.");
		}
		
		sprintf(filename, "Transmit%d.bin", n);	
		file=fopen(filename,"rb");
		if(file != NULL)
		{
			fread(temp, sizeof(double), RAW, file);
			fclose(file);
			k=0;
			while(k<RAW)
			{
				for(i=0; i<*row; i++)
				{
					for(j=0; j<*col; j++)
					{
						data[i][j]=temp[k];
						k++;
						if(k==RAW)
							printf("Print the value of index %d is  for file %d \n",k,n);
					}
					
				}
				
			} 
		}
		else
		{
			printf("Error in File opening for Tx!");
		}
		for(k = 0; k<*row; k++)
		{
			for (int s=0; s<*row; s++)
				{
					for(int t=0; t<*col/2; t++)
					{
						z1 = delay[s][t]-1; 
						//printf(" z1 = %d ",z1);						
						tempD[s] = tempD[s] + data[z1][t];
						//printf(" Temp value is: %f\n ",tempD[s]);
					}
				}
				for (int s = 0; s < *row; s++)
				{
					bf[s][n-1] = tempD[s];
					tempD[s]=0;
					//printf("%f\n",bf[s][n]);
				}
			start++;
			end++;
		}
	}
	return bf;
}

void storebin(const char* filename, double** array, int numRows, int numColumns) 
{
    // Open the CSV file for writing
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    // Writing the array to the file

	for (size_t i = 0; i < numRows; ++i) {
   fwrite(array[i], sizeof(double), numColumns, file);
	}
}