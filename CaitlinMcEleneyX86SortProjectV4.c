/************************************************************************
 *
 *       x86 sort project : 
 *
 *		implement sort (either insertion sort or selection sort)
 *		translated from the Mips sort project
 *
 *
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cse222macV4.h"
#define HALFPOINT 1
#define NO_HALFPOINT 0
/*
 * declare the prototype of your assembler program or procedures
 */
// example: short asmreturn();  

void asmSort(int *list, int arrayLen, int halfpoint);
void processConfigs(int argc,char *argv[] );
void insertion_sort (int *a, int n, int hpts);
void selection_sort (int *a, int n, int hpts);
void restoreOrigArray(int *origAry,int *wrkAry, int n);
void printList(int *list, int arrayLen);
int letsCheckTheSort();
int compareCheck(int *myLst,int *stuLst, int cntN);
int letsTimeTheSort();


int  numCount = 20;
int  originalNumber[100] = {5, 8, 12, 10, 56, 22, 98, 120, 90, 4, 349, 8, 45, 37, 43, 67, 3, 18, 97, 71};
int  listOfNumber[100]   = {5, 8, 12, 10, 56, 22, 98, 120, 90, 4, 349, 8, 45, 37, 43, 67, 3, 18, 97, 71};
char sortType = 'I';   // 'I' for insert sort otherwise it is selection sort

main(int argc, char *argv[] )
{
	/* 
	 * variable declaration here
	 */

	int tmp1 = 0;
	processConfigs(argc,argv);
    

   /*
	* First call INITCST
	* replace Your Name Here with your name
	*/

	INITCST("Spring 2018 Sort routine on x86: ","Caitlin McEleney");
	sortType = 'I';   // 'I' capital I for insert sort otherwise it is selection sort


	/*
	 * call your asm procedure here
	 * you can use any variable name you want and make sure the return type
	 * is correct.
	 */



	if (letsCheckTheSort() == 0) {
		printf("\n You have pass the sort check.....  now let's time it ......\n\n");
		letsTimeTheSort();
	}
	else printf("\n********* sort fail on the check sort\ncan not continue for timing \n");
	
	printf("\n\n\nhit any key to continue or quit");
	getchar();
}



void restoreOrigArray(int *origAry,int *wrkAry, int n) {
	int i;
	for (i=0; i<n; i++) {
		wrkAry[i] = origAry[i];
	}
}


void printList(int *list, int arrayLen) {
	int i;
	for ( i = 0; i<arrayLen; i++) {
		printf("%5d",*list);
		if ((i+1) % 10 == 0) printf("\n");
		list++;
	}
	printf("\n");
}



void asmSort(int *list, int arrayLen, int halfpoint) {

	/*
	 * list = address of the list of integer array
	 * arraylen = the number of element in the list  just like list.length in java
	 * halfpoint  use as a flag
	 * halpfpoint = 1 when the sort routine reach half point just return, 
	 *              otherwise finished the sort and return
	 */

	/*
	 *
	 *
	 insertion_sort(list,arrayLen,halfpoint);
	 return;
	 selection_sort(list,arrayLen,halfpoint);
	 return;
	 *
	 *
	 */


	// any variable can be declare here before _asm
	
	int tmp = 0;
	int  i = 1;
	int  j = 0;
	
		_asm 
	{
		mov ecx,arrayLen
		mov esi,list
		mov ebx,halfpoint
		mov eax, i				//element to sort
		cmp halfpoint, 1		//check if half point is flagged
		jne more
		sar arrayLen,1

		
more:	
		mov eax, i
		mov ecx, arrayLen
		cmp eax,ecx			//if array count is 0 (decremented int cont1)
		jge	done			//exit

		mov eax, i
		mov eax, [esi+4*eax]		//add the element being pointed to by esi into edx -> eax = i
		
		mov ebx, i
		mov j, ebx
		dec j

cont1:  					//start checking the values
		mov ebx, j			//move i into edi
		imul ebx, 4			//multiply i * 4
		mov edx, esi		//move the pointer for esi to edx
		add edx, ebx		//add i * 4 to base address
		mov ebx, j			//set ebx back to j

sortLoop:
		cmp j, 0
		jl foundLocation

		mov edx, j
		mov edi, [esi+4*edx]		//put the previous element of the array into edi -> edi = j

		cmp eax, edi			//compare element i and element j
		jge foundLocation		//if [i] >= [j], found location to put i into
								//else move edx up in the array - overwrite where eax was
		mov edx, j
		inc edx
		mov [esi + 4 * edx], edi
		dec j
		jmp sortLoop			//return to cont1

foundLocation:			//put i into j's location
		mov edx, j
		inc edx
		mov [esi + 4 * edx], eax
		
		inc i				//increment to next element in the array
		jmp	more			//go back to beginning
done:
	}
		
	return;

}