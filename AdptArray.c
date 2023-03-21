#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AdptArray.h"

// Struct to save the data required
typedef struct AdptArray_
{
	int ArrSize;		  // save the length of the array
	PElement *pElemArr;	  // array of elements
	DEL_FUNC delFunc;	  // delete function
	COPY_FUNC copyFunc;	  // copy function
	PRINT_FUNC printFunc; // print function
} AdptArray;

// Return the data only if the request without problems
PElement GetAdptArrayAt(PAdptArray array, int i)
{
	// if getting data wrong or nothing to give, return null
	if ((array == NULL) || (i < 0) || (array->ArrSize <= i) || (array->pElemArr[i] == NULL))
		return NULL;

	// save the data of the element
	PElement elemAt = array->copyFunc(array->pElemArr[i]);
	if (!elemAt)
		return NULL; // not success to get the element

	return elemAt;
}

// Return the size of the given array only if he is valid
int GetAdptArraySize(PAdptArray array)
{
	if (!array)
		return -1; // not valid array was paased in the function
				   // parameter that saved in the struct with the data
	return array->ArrSize;
}

// Prints the array if he is valid
void PrintDB(PAdptArray array)
{
	// if not good array passed end the function
	if (array == NULL)
		return;

	// loop to print each element in the array in the struct of data
	for (int i = 0; i < array->ArrSize; i++)
	{
		if (array->pElemArr[i] != NULL)
		{ // print the element only if is not null
			array->printFunc(array->pElemArr[i]);
		}
	} // end the loop
}

// Create new data struct with the functions only if they valid
PAdptArray CreateAdptArray(COPY_FUNC copyFunc_, DEL_FUNC delFunc_, PRINT_FUNC printFunc)
{
	// check validation of the given function, if there is problem with ine of them, return null
	if ((copyFunc_ == NULL) || (delFunc_ == NULL) || (printFunc == NULL))
		return NULL;

	// allocate new memory to the data struct of the memory needed
	PAdptArray pArr = (PAdptArray)malloc(sizeof(AdptArray));
	if (pArr == NULL)
		return NULL; // check if allocation success - return null if not

	pArr->ArrSize = 0;			 // initialize the size to 0
	pArr->pElemArr = NULL;		 // initialize the array to nothing
	pArr->copyFunc = copyFunc_;	 // set copy function
	pArr->printFunc = printFunc; // set print function
	pArr->delFunc = delFunc_;	 // set delete function

	return pArr;
}

// Set new element in specific location in the array in the data structure
Result SetAdptArrayAt(PAdptArray pArr, int location, PElement pNewElem)
{
	// if get wrong parameters return that fail to do this
	if ((pArr == NULL) || (pNewElem == NULL) || (location < 0))
		return FAIL;

	if (pArr->ArrSize == 0) // no data in the array, just locate memory and put the element
	{
		pArr->pElemArr = (PElement *)malloc(sizeof(PElement) * (location + 1));
		if (pArr->pElemArr == NULL)
			return FAIL;

		for (int i = 0; i < location; i++)
		{
			pArr->pElemArr[i] = NULL;
		}
		pArr->pElemArr[location] = pArr->copyFunc(pNewElem);
		pArr->ArrSize = location + 1;
		return SUCCESS;
	}
	else if (location < pArr->ArrSize) // the location given is in range, delete old element and put the new
	{
		PElement pOldElem = pArr->pElemArr[location];
		if (pOldElem == NULL)
			return FAIL;
		pArr->delFunc(pOldElem);
		pArr->pElemArr[location] = pArr->copyFunc(pNewElem);
		return SUCCESS;
	}
	else if (location >= pArr->ArrSize) // location bigger than size, put null in all indexes after size and put element in his location
	{
		PElement *newpElemArr = (PElement *)calloc((location + 1), sizeof(PElement));
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
		pArr->pElemArr[location] = pArr->copyFunc(pNewElem);
		pArr->ArrSize = location + 1;

		return SUCCESS;
	}
	return FAIL;
}

// Delete all the data struct that asked
void DeleteAdptArray(PAdptArray pArr)
{
	if (pArr == NULL) return;
	else if (pArr->pElemArr == NULL)
	{
		free(pArr);
		return;
	}
	else
	{
		for (int i = 0; i < pArr->ArrSize; i++)
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