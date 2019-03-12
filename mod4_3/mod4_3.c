#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//define the struct stackNode
struct stackNode
{
	char *data;
	//creating the pointer to link to the next node
	struct stackNode *nextPtr;
};

//synonyms created for stackNode
typedef struct stackNode StackNode;
typedef StackNode *StackNodePtr;

//function prototypes
void push(StackNodePtr *topPtr, char *info);
int pop(StackNodePtr *topPtr);
int isEmpty(StackNodePtr topPtr);
void printStack(StackNodePtr currentPtr);


int main(void)
{
	StackNodePtr stackPtr = NULL;
	char reversed[160], temp[160], words[160];
	int i, l, k, c, s, dummy = 0;

	//request for input
	printf_s("%s", "Please input some words: ");
	fgets(words, 161, stdin);
	
	//print the string
	printf_s("\nThis is your string: %s", words);
	
	//grab the length of the string
	l = (int)strlen(words);

	//push the string onto the stack
	for (i = 0; i < l; i++) 
	{
		push(&stackPtr, words[i]);
	}

	//print the stack
	printStack(stackPtr);

	//populate the next string with the reversed string
	for (i = 0; i < l; i++)
	{
		reversed[i] = pop(&stackPtr);
	}

	//terminate the string
	reversed[l] = '\0';

	//shift the whole string left one place to get rid of pesky garbage data
	for (i = 0; i < l; i++)
	{
		reversed[i] = reversed[i + 1];
	}

	//here is the string completely reversed
	printf_s("\nThis is your string on drugs: %s\n", reversed);

	//proof the stack is empty
	printStack(stackPtr);

	//some counters
	k = 0;
	s = 0;

	//the part that puts the words into readable order officially making the words reversed.
	for (i = 0; i < l; i++)
	{
		//gather letters until whitespace
		if (reversed[i] != ' ') 
		{
			temp[i] = reversed[i];
			k++;

		}

		//whitespace happened start reversing the characters
		if (reversed[i] == ' ')
		{
			//this grabs the words place in the sentence
			s = i - k;
			
			for (c = 0; c < k; c++)
			{
				push(&stackPtr, temp[s + c]);
			}

			for (c = 0; c < k; c++)
			{
				reversed[s + c] = pop(&stackPtr);
			}
			
			k = 0;
		}

		//special case for the last word
		if (reversed[i + 1] == '\0')
		{
			s = i - (k - 1);

			push(&stackPtr, '\0');

			for (c = 0; c <= k; c++)
			{
				push(&stackPtr, temp[s + c]);
			}

			dummy = pop(&stackPtr);

			for (c = 0; c <= k; c++)
			{
				reversed[s + c] = pop(&stackPtr);
			}

			k = 0;
		}
	}

	//print the reversed string
	printf_s("%s", "This is the test to show that the data was reversed correctly\n");
	printf_s("%s\n", reversed);
}

//function push
void push(StackNodePtr *topPtr, char *info)
{
	StackNodePtr newPtr;

	newPtr = malloc(sizeof(StackNode));

	if (newPtr != NULL)
	{
		//printf_s("\n***%s***\n", *info);
		newPtr->data = info;
		newPtr->nextPtr = *topPtr;
		*topPtr = newPtr;
	}

	else
	{
		printf_s("%s was not inserted into the stack as there is no allocatable memory available.\n", info);
	}
}//end push

//function pop
int pop(StackNodePtr *topPtr)
{
	StackNodePtr tempPtr;
	char popValue;

	tempPtr = *topPtr;
	popValue = (*topPtr)->data;
	*topPtr = (*topPtr)->nextPtr;
	free(tempPtr);
	return popValue;
}

//function to inform the stack is empty
int isEmpty(StackNodePtr topPtr)
{
	return topPtr == NULL;
}

//function to print out the stack
void printStack(StackNodePtr currentPtr)
{
	if (currentPtr == NULL)
	{
		puts("The stack is empty.\n");
	}

	else
	{
		puts("This is what the stack looks like:");

		while (currentPtr != NULL)
		{
			printf("%c --> ", currentPtr->data);
			currentPtr = currentPtr->nextPtr;
		}

		puts("NULL\n");
	}
}//end function printStack