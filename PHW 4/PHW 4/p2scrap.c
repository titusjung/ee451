void swap(int *array, long aIndex, long bIndex)
{
   int temp = array[aIndex];
   array[aIndex] = array[bIndex];
   array[bIndex] = temp;

}



//using code from wikipedia;

/*
int partition (int* array, int start, int end, int pivotIndex)
{
   if(!(pivotIndex>start && pivotIndex<end) ||(start>=end)) return -1; 
   int pivot = array[pivotIndex];
   int i,j,k;
   i= start;
   j= end;
   while(i<j)
   {
      while(array[i]<=pivot) { i++;}
      while(array[j>pivot) {j--;}
      if(i >=j) break;
      swap(array,i,j);
   } 
   swap(array,i,pivotIndex);

   return i;
}
*/


int partition (int* array, int start, int end)
{
   int pivotIndex = (end-start)/2+start; 
   int pivot = array[start];
   int i= start;
   int j;
   for(j=start+1; j<end; j++)
   {
      if(j==pivotIndex) continue; 
      if(array[j]<=pivot)
      {
         swap(array,i,j);
         i++;
      }
   }
   swap(array,i,end-1); 
  // printf("\n q \n");   
   int k;
   /*
   for(k=start; k<end;k++)
   {
      printf(" %d",array[k]);
   }   
   //printf("\n q \n");   
*/
   return i; 
}

void quickSort(int *array, int start, int end)
{
   if(start<end)
   {
      int p= partition(array,start,end);
      if(p==-1) return;
      quickSort(array,start,p);
      quickSort(array,p+1,end);
   }
}

/*
void quickSort(int *array, int start, int end)
{
   if(start>=end) return;

   int i,x,s;
   int length = end -start; 
   int pivotIndex = (int)rand()%length+start;
   int pivot = array[pivotIndex];
   int high =start; 
   for(i=start; i<end;i++)
   {
      if(i==pivotIndex) continue; 
      if(array[i]>pivot)
      {
         high++;
         swap(array,high,i);
      }
   }

   swap(array,start,s);
   quickSort(array,start,s);
   quickSort(array,s,end);

}
/*
void quickSort(int *array, int start, int end){
   int length = end -start; 
   if(length<=1) return;
   int * lowPivot = (int *) malloc (sizeof(int)*length);
   int * highPivot = (int *) malloc (sizeof(int)*length);

   int l=0; 
   int h=0; 
   int pivotIndex = (int)rand()%length+start;
   int pivot = array[pivotIndex];
   int i;
   
   //std::cout<<"pivot is "<<pivot<<std::endl;

   for(i=start; i<end; i++)
   {
   		if(i==pivotIndex) continue;
   		else if(array[i]>pivot)
   		{
   			highPivot[h]=array[i];
   			h++;
   			//std::cout<<"high number  is "<<array[i]<<std::endl; 

   		}
   		else
   		{
   			//std::cout<<"low number  is "<<array[i]<<std::endl; 

   			lowPivot[l]=array[i];
   			l++;
   		}
   }

	quickSort(lowPivot,0,l);
	quickSort(highPivot,0,h);

   for(i=0; i<l; i++)
   {
   		array[i+start] = lowPivot[i];
   }
   array[l+start] = pivot;

   for(i=0; i<h; i++)
   {
   		array[l+1+i+start] = highPivot[i];
   }
   free(lowPivot);
   free(highPivot);

}
*/