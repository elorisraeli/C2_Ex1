#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AdptArray.h"

// PAdptArray CreateAdptArray(COPY_FUNC, DEL_FUNC,PRINT_FUNC);
// void DeleteAdptArray(PAdptArray);
// Result SetAdptArrayAt(PAdptArray, int, PElement);
// PElement GetAdptArrayAt(PAdptArray, int);
// int GetAdptArraySize(PAdptArray);
// void PrintDB(PAdptArray);

typedef struct AdptArray_
{
	int ArrSize;
	PElement* pElemArr;
	DEL_FUNC delFunc;
	COPY_FUNC copyFunc;
    PRINT_FUNC printFunc;
}AdptArray;

PElement GetAdptArrayAt(PAdptArray array, int i){
	if(array->ArrSize > i) return NULL;
    return array->pElemArr[i];
}

int GetAdptArraySize(PAdptArray array){
    return array->ArrSize;
}

void PrintDB(PAdptArray array){
	for (size_t i = 0; i < array->ArrSize; i++)
	{
		if (array->pElemArr!=NULL)
		{
			array->printFunc(array->pElemArr[i]);
		}
		
	}

}


// notice that 'PRINT_FUNC printFunc' added to this function, check all other functions if missing
PAdptArray CreateAdptArray(COPY_FUNC copyFunc_, DEL_FUNC delFunc_, PRINT_FUNC printFunc)
{
	PAdptArray pArr = (PAdptArray)malloc(sizeof(AdptArray));
	if (pArr == NULL)
		return NULL;
	pArr->ArrSize = 0;
	pArr->pElemArr = NULL;
	pArr->delFunc = delFunc_;
	pArr->copyFunc = copyFunc_;
    pArr->printFunc = printFunc;
	return pArr;
}
////////B.
Result SetAdptArrayAt(PAdptArray pArr, int idx, PElement pNewElem)
{
	PElement* newpElemArr;
	if (pArr == NULL)
		return FAIL;

	if (idx >= pArr->ArrSize)
	{
		
// Extend Array
		if ((newpElemArr = (PElement*)calloc((idx + 1), sizeof(PElement))) == NULL)
			return FAIL;
		memcpy(newpElemArr, pArr->pElemArr, (pArr->ArrSize) * sizeof(PElement));
		free(pArr->pElemArr);
		pArr->pElemArr = newpElemArr;
	}

	// Delete Previous Elem
	pArr->delFunc((pArr->pElemArr)[idx]);
	(pArr->pElemArr)[idx] = pArr->copyFunc(pNewElem);

	// Update Array Size
	pArr->ArrSize = (idx >= pArr->ArrSize) ? (idx + 1) : pArr->ArrSize;
	return SUCCESS;
}
//C.

void DeleteAdptArray(PAdptArray pArr)
{
	int i;
	if (pArr == NULL)
		return;
	for(i = 0; i < pArr->ArrSize; ++i)
	{
		if ((pArr->pElemArr)[1])
		{
			pArr->delFunc((pArr->pElemArr)[i]);
		}
		
	}
	free(pArr->pElemArr);
	free(pArr);
}