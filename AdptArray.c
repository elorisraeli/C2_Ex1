#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AdptArray.h"

typedef struct AdptArray_
{
	int ArrSize;
	PElement* pElemArr;
	DEL_FUNC delFunc;
	COPY_FUNC copyFunc;
    PRINT_FUNC printFunc;
}AdptArray;

PElement GetAdptArrayAt(PAdptArray array, int i){
	if(!array) return NULL;
	if(i < 0 || array->ArrSize <= i|| array->pElemArr[i] == NULL) 
	{
	return NULL;
	}
	
	PElement elemAt = array->copyFunc(array->pElemArr[i]);
	if (!elemAt) return NULL;
	
    return elemAt;
}

int GetAdptArraySize(PAdptArray array){
	if (!array) return -1;
	
    return array->ArrSize;
}

void PrintDB(PAdptArray array){
	if (!array) return;
	
	for (int i = 0; i < array->ArrSize; i++)
	{
		if (array->pElemArr[i]!=NULL)
		{
			array->printFunc(array->pElemArr[i]);
		}
	}
}

PAdptArray CreateAdptArray(COPY_FUNC copyFunc_, DEL_FUNC delFunc_, PRINT_FUNC printFunc)
{
	if(copyFunc_ == NULL || delFunc_ == NULL || printFunc == NULL) return NULL;

	PAdptArray pArr = (PAdptArray)malloc(sizeof(AdptArray));
	if (pArr == NULL) return NULL;
		
	pArr->ArrSize = 0;
	pArr->pElemArr = NULL;
	pArr->copyFunc = copyFunc_;
    pArr->printFunc = printFunc;
	pArr->delFunc = delFunc_;
	
	return pArr;
}

Result SetAdptArrayAt(PAdptArray pArr, int idx, PElement pNewElem)
{
	if (pArr == NULL)
		return FAIL;
	else if (pNewElem == NULL)
		return FAIL;
	else if (idx < 0)
		return FAIL;
	else if (pArr->ArrSize == 0)
	{
		pArr->pElemArr = (PElement*)malloc(sizeof(PElement) * (idx + 1));
		if (pArr->pElemArr == NULL)
			return FAIL;

		for (int i = 0; i < idx; i++)
		{
			pArr->pElemArr[i] = NULL;
		}
		pArr->pElemArr[idx] = pArr->copyFunc(pNewElem);
		pArr->ArrSize = idx + 1;
		return SUCCESS;
	}
	else if (idx < pArr->ArrSize)
	{
		PElement pOldElem = pArr->pElemArr[idx];
		if (pOldElem == NULL)
			return FAIL;
		pArr->delFunc(pOldElem);
		pArr->pElemArr[idx] = pArr->copyFunc(pNewElem);
		return SUCCESS;	
	}
	else if (idx >= pArr->ArrSize)
	{
		PElement* newpElemArr=(PElement*)calloc((idx + 1), sizeof(PElement));
			for (int i = 0; i < pArr->ArrSize; i++)
			{
				if (pArr->pElemArr[i] != NULL)
				{
				newpElemArr[i] = pArr->copyFunc(pArr->pElemArr[i]);
				pArr->delFunc(pArr->pElemArr[i]);
				}
			}

			free(pArr->pElemArr);
			pArr->pElemArr = newpElemArr;
			pArr->pElemArr[idx] = pArr->copyFunc(pNewElem);
			pArr->ArrSize = idx + 1;

		return SUCCESS;
		}
	
	
	return FAIL;
}


void DeleteAdptArray(PAdptArray pArr)
{
	if (pArr == NULL)
		return;
	else if (pArr->pElemArr == NULL)
	{
		free(pArr);
		return;
	}
	else{
	for(int i = 0; i < pArr->ArrSize; i++)
	{
		if ((pArr->pElemArr)[i])
		{
			pArr->delFunc((pArr->pElemArr)[i]);
		}
		
	}
	pArr->ArrSize = 0;
	pArr->delFunc = NULL;
	free(pArr->pElemArr);
	free(pArr);
	}
}