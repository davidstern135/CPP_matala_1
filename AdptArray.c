//
// Created by david on 3/20/2023.
//
#include "AdptArray.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct AdptArray_
{
    int ArrSize;
    PElement* pElemArr;
    DEL_FUNC delFunc;
    COPY_FUNC copyFunc;
    PRINT_FUNC printFunc;
}AdptArray,*PAdptArray;

PAdptArray CreateAdptArray(COPY_FUNC copy_f, DEL_FUNC del_f ,PRINT_FUNC print_f)
{
    PAdptArray pArr = (PAdptArray)malloc(sizeof(AdptArray));
    if (pArr == NULL)
        return NULL;
    pArr->ArrSize = 0;
    pArr->pElemArr = NULL;
    pArr->delFunc = del_f;
    pArr->printFunc= print_f;
    pArr->copyFunc = copy_f;
    return pArr;
}

void DeleteAdptArray(PAdptArray pArr){
    if(pArr==NULL)
        return;
    else {
        for (int i = 0; i < pArr->ArrSize; i++) {
            if (((pArr->pElemArr)[i]) != NULL)
                pArr->delFunc((pArr->pElemArr)[i]);
        }
    }
    free(pArr->pElemArr);
    free(pArr);
    return;
}
Result SetAdptArrayAt(PAdptArray pArr, int index, PElement pNewElem)
{
    PElement* newpElemArr;
    if (pArr == NULL)
        return FAIL;

    if (index >= pArr->ArrSize)
    {
        if ((newpElemArr = (PElement*)calloc((index + 1), sizeof(PElement))) == NULL)
            return FAIL;
        memcpy(newpElemArr, pArr->pElemArr, (pArr->ArrSize) * sizeof(PElement));
        free(pArr->pElemArr);
        pArr->pElemArr = newpElemArr;
        pArr->ArrSize = (index+1);
    }

    if (((pArr->pElemArr)[index]) != NULL)
        pArr->delFunc((pArr->pElemArr)[index]);
    (pArr->pElemArr)[index] = pArr->copyFunc(pNewElem);
    return SUCCESS;
}
PElement GetAdptArrayAt(PAdptArray pArr , int index)
{
    if (pArr==NULL){
        return NULL;
    }
    if(index >= pArr->ArrSize)
        return NULL;
    else if(((pArr->pElemArr)[index])==NULL){
        return NULL;
    }
    else
        return pArr->copyFunc((pArr->pElemArr)[index]);
}
int GetAdptArraySize(PAdptArray pArr){
    if(pArr==NULL){
        return -1;
    }
    return pArr->ArrSize;
}
void PrintDB(PAdptArray pArr){
    for (int i = 0; i < pArr->ArrSize; i++) {
        if (((pArr->pElemArr)[i]) != NULL)
            pArr->printFunc((pArr->pElemArr)[i]);
    }
}



