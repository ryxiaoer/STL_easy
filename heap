//自己建立大堆的实现 emmm写完才发现没封装，尴尬+1
#program once

#include"common.h"

typedef struct Heap{
	int			  *base;
	int           capacity;
	int           size;
}Heap;

void HeapInit(Heap *php, int n);
void MinHeapInsert(Heap *php, int x);
int MinHeapRemove(Heap *php);
bool HeapEmpty(Heap *php);
void HeapPrint(Heap *php);
void HeapSort(Heap *php);
void AdjustUp(int *base, int start);
void AdjustDown(int *base, int start, int n);

void HeapInit(Heap *php, int n){
	assert(php != NULL);
	php->base = (int*)malloc(sizeof(int) * n);
	assert(php->base != NULL);
	php->capacity = n;
	php->size = 0;
}

bool HeapEmpty(Heap *php){
	assert(php != NULL);
	return php->size == 0;
}

void MinHeapInsert(Heap *php, int x){
	assert(php != NULL);
	if(php->size < php->capacity){
		php->base[php->size] = x;
		
		//调整为小堆结构  
		//从下往上调整
		AdjustUp(php->base, php->size);
		php->size++;
	}
}

int MinHeapRemove(Heap *php){
	assert(php != NULL);
	assert(php->size > 0);
	
	int heaptop_val = php->base[0];
	php->size--;
	php->base[0] = php->base[php->size];
	AdjustDown(php->base, 0, php->size);
	return heaptop_val;
}

void HeapPrint(Heap *php){
	for(int i=0; i<php->size; ++i)
		printf("%d ", php->base[i]);
	printf("\n");
}

void AdjustUp(int *base, int start){
	int j = start;
	int i = (j-1)/2;

	int tmp = base[j];
	while(j > 0){
		if(tmp < base[i]){
			base[j] = base[i]; 
			j = i;
			i = (j-1)/2;
		}
		else
			break;
	}
	base[j] = tmp;
}

void AdjustDown(int *base, int start, int n){
	int i = start;
	int j = 2*i + 1;
	while(j < n){
		if(j+1<n && base[j]>base[j+1]) //找出左右子树较小的值
			j++;
		if(base[i] > base[j]){
			Swap(&base[i], &base[j]);
			i = j;
			j = 2*i + 1;
		}
		else
			break;
	}
}


void HeapSort(Heap *php, int ar[], int n){
	for(int i=0; i<n; ++i)
		php->base[i] = ar[i];
	php->size = n;

	//调整成小堆
	int curpos = n/2 - 1; //找到最后一个分支
	while(curpos >= 0){
		AdjustDown(php->base, curpos, n);
		curpos--;
	}

	//排序
	int end = n-1;
	while(end > 0){
		Swap(&php->base[0], &php->base[end]);
		AdjustDown(php->base, 0, end);
		end--;
	}
	//HeapPrint(php);
	int k = php->size - 1;
	for(int i=0; i<n; ++i){
		ar[i] = php->base[k--];
	}
}

/*
void AdjustUp(int *base, int start)
{
	int j = start;
	int i = (j-1)/2;
	while(j > 0)
	{
		if(base[j] < base[i])
		{
			Swap(&(base[j]), &(base[i]));
			j = i;
			i = (j-1)/2;
		}
		else
			break;
	}
}
*/
