#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *file1;
	char filename[15];
    int raw=333696;
    int row=2607;
    int col=128;
	int i,j,k,n; 
	
	//reading 65 Tx Files
	for(n=1;n<=65;n++)
	{
		double *temp=NULL; //allocating memory for temporarily storing binary file data
		temp=(double*)malloc(raw*sizeof(double));
		if (temp == NULL) 
		{
			printf("Memory allocation failed for temp.");
			return 1;
		}
	
		double **data=NULL; // allocating memory for 2d array data
		data=(double**)malloc(row*sizeof(double));
		for(i=0;i<row;i++)
		{
			data[i]=(double*)malloc(col*sizeof(double));
		}
		if (data == NULL) 
		{
			printf("Memory allocation failed for data.");
			return 1;
		}
		
		sprintf(filename, "Transmit%d.bin", n);	
		file1=fopen(filename,"rb");
		if(file1 != NULL)
		{
			fread(temp, sizeof(double), raw, file1);
			fclose(file1);
			k=0;
			while(k<raw)
			{
				for(i=0;i<row;i++)
				{
					for(j=0;j<col;j++)
					{
						data[i][j]=temp[k];  //converting 1d array to 2d array
						k++;
						//if(k==raw)
						//	printf("Print the value of index %d is  for file %d \n",k,n);
					}
					
				}
				
			} 
		}
		else
		{
			printf("Error in File opening for Tx!");
		}
	free(temp);
	
	for (i=0; i<row; i++)
	free(data[i]);
	free(data);
		
		
	}
	
	
    return 0;
}
