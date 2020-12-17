//*************************
//*Marzia Abdul Rahim	*
//*Username: Mar976	*
//*Id:6287645		*
//*Assignment 1 		*
//*************************
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//MACROS 
#define MIN(a,b)(((a)<(b))? (a):(b))
#define MAX(a,b)(((a)>(b))? (a):(b))
int invalid=-1;
struct Word
{
	int start=-1;
	int end=-1;
	int count=-1;
	int left=-1;
	int right=-1;
	int depth=-1;
};
//GLOBAL VARIABLES
Word text[50000];						//array for words
char pool[500000];					//array for characters 
int sorted[50000];					//keep the sorted array
int indexSort=0;								//indexSort for sorted array
int valid=0;
int nextChar=0;				
int root=-1;								//ROOT OF THE TREE
Word x[100];								//temp array for merge sort
//FUNCTIONS
int compare(Word,Word);
int avl_insert(Word,int);
int height(int indexSort);  
int getBalance(int node);  
int rotate_left(int);
int rotate_right(int);
int double_left(int);
int double_right(int);
void mergeSort(int l, int r);
void merge(int l, int m, int r);
void inOrder(int node) ;

int main()
{
	//Getting the file name
	string fileName="";
	cerr<<"File Name: ";
	cin>>fileName;
	

	//===================READ FROM THE FILE=========================
	ifstream in;
	in.open(fileName);
	char inChar='a';
	Word word;
	word.start=0;
	word.end=-1;
	word.count=-1;
	word.left=-1;
	word.right=-1;
	word.depth=-1;
	bool space=false;
	if(in.good())
	{
		while((inChar=in.get()) && in)
		{
			if(isspace(inChar) && !space)						//Read word after space
			{
				word.end=nextChar-1;
				root=avl_insert(word,root);
				//reset the word;
				word.start=nextChar;
				space=true;
			}
			else if(isalpha(inChar))
			{
				inChar=tolower(inChar);
				pool[nextChar]=inChar;
				nextChar++;
				space=false;
			}
			if(in.peek(),in.eof() && !space)		//ONLY FOR THE LAST WORD IN THE FILE OTHERWISE THE WORD WILL BE IGNORED
			{
				word.end=nextChar-1;
				root=avl_insert(word,root);
			}
		}	
	}
	else
	{
		cerr<<"File did not open!"<<endl;
		return 1;
	}
	in.close();
	//SORT
	inOrder(root);
	mergeSort(0,valid-1);
	//PRINT
	cout<<"\nFIRST TEN WORDS\n-----------------------"<<endl;
	for(int i=0;i<10;i++)
	{
		for(int j=text[sorted[i]].start;j<=text[sorted[i]].end;j++)
		{
			cout<<pool[j];
		}
		cout<<"\t\t"<<text[sorted[i]].count<<endl;
	}
	cout<<"\n\nLAST TEN WORDS\n-----------------------"<<endl;
	for(int i=indexSort-10;i<indexSort;i++)
	{
		for(int j=text[sorted[i]].start;j<=text[sorted[i]].end;j++)
		{
			cout<<pool[j];
		}
		cout<<"\t\t"<<text[sorted[i]].count<<endl;
	}
	
	return 0;
}
//====================================IN ORDER================================
void inOrder(int node) 
{ 
	if(node!=-1) 
	{ 
		inOrder(text[node].left); 
		sorted[indexSort++]=node;
		inOrder(text[node].right); 
	}
} 
//================================avl_insert================================
int avl_insert(Word value,int node)
{
	int compareResult=compare(value,text[node]);
	//REACH A NON-EXISTENT NODE
	if(node==invalid)
	{
		node=valid++;
		text[node]=value;
		text[node].left=invalid;
		text[node].right=invalid;
		text[node].count=1;
		text[node].depth=1;
		return node;
	}
	//NO DUPLICATE
	if(compareResult==0)
	{
		text[node].count+=1;
		nextChar=value.start;
		return node;
	}
	//LEFT
	else if(compareResult<0)
	{
		text[node].left=avl_insert(value,text[node].left);
	}
	//RIGHT
	else if(compareResult>0)
	{
		text[node].right=avl_insert(value,text[node].right);
	}
	text[node].depth=MAX(height(text[node].left),height(text[node].right))+1;
	//ROTATE
	//CASE LEFT LEFT
	if(getBalance(node)>1 && compare(value,text[text[node].left])<0)
	{
		return rotate_right(node);
	}
	//CASE RIGHT RIGHT
	if(getBalance(node)<-1 && compare(value,text[text[node].right])>0)
	{
		return rotate_left(node);
	}
	//CASE LEFT RIGHT
	if(getBalance(node)>1 && compare(value,text[text[node].right])>0) 
	{
		return double_right(node);
	}
	//CASE RIGHT LEFT
	if(getBalance(node)<-1 && compare(value,text[text[node].left])<0)
	{
		return double_left(node);
	}

	return node;
}
int getBalance(int node)  
{  
    if (node == -1)  
        return 0;  
	else
		return height(text[node].left) - height(text[node].right);  
}  
// A utility function to get the height of the tree 
int height(int node)  
{  
	if (node<0)  
        return 0;  
	return text[node].depth; 
}
//================================ROTATE LEFT================================
int rotate_left(int k2)
{
	int k1=text[k2].right;
	text[k2].right=text[k1].left;
	text[k1].left=k2;


	text[k2].depth=1+MAX(height(text[k2].left),height(text[k2].right));
	text[k1].depth=1+MAX(text[k2].depth,height(text[k1].right));

	k2=k1;
	return k2;
}
//================================ROTATE RIGHT================================
int rotate_right(int k2)
{
	int k1=text[k2].left;
	text[k2].left=text[k1].right;
	text[k1].right=k2;

	text[k2].depth=1+MAX(height(text[k2].left),height(text[k2].right));
	text[k1].depth=1+MAX(text[k2].depth,height(text[k1].left));

	k2=k1;
	return k2;
}
//================================DOUBLE LEFT================================
int double_left(int k3)
{
	text[k3].right=rotate_right(text[k3].right);
	return rotate_left(k3);
}
//================================DOUBLE RIGHT================================
int double_right(int k3)
{
	text[k3].left=rotate_left(text[k3].left);
	return rotate_right(k3);
}
//================================MERGE SORT================================
void mergeSort(int l, int r)
{
	if(l<r)
	{
		int centre=(l+r)/2;
		mergeSort(l,centre);			//SORT THE LEFT
		mergeSort(centre+1,r);			//SORT THE RIGHT
		merge(l,centre+1,r);				//JOIN THE HALVES IN THE indexSort LIST
	}
}
void merge(int lPos, int rightPos, int cPos)
{
	int leftEnd = rightPos - 1;
	int xPos = lPos;
	int numElements = cPos - lPos + 1;
	while (lPos <= leftEnd && rightPos <= cPos) 
	{
		if (text[sorted[lPos]].count >= text[sorted[rightPos]].count) 
		{
				x[xPos++] = text[sorted[lPos++]];
		} else {
				x[xPos++] = text[sorted[rightPos++]];
		}
	}
	// Copy the remaining elements of the left textay to the temporary textay
	while (lPos <= leftEnd) 
	{
			x[xPos++] = text[sorted[lPos++]];
	}
	// Copy the remaining elements of the right textay to the temporary textay
	while (rightPos <= cPos) 
	{
			x[xPos++] = text[sorted[rightPos++]];
	}
	// Copy the elements of the temporary textay to the given textay to achieve sorting
	for (int i = 0; i < numElements; i++, cPos--) 
	{
			text[sorted[cPos]] = x[cPos];
	}
}
//================================IN order
//================================COMPARE TWO WORDS================================
int compare(Word value,Word node)
{
	int lengthK=value.end-value.start;
	int lengthN=node.end-node.start;
	for(int i=0;i<=MIN(lengthK,lengthN);i++) 
	{
		if ( pool[value.start+i] < pool[node.start+i])
		{
			return -1;
		}
		if (pool[value.start+i] > pool[node.start+i])
		{
			return 1;
		}
	
	}
	if(lengthK < lengthN)			//GO TO THE LEFT
	{
		return -1;					
	}
	if(lengthK > lengthN)			//GO TO THE RIGHT
	{
		return 1;					
	}
	return 0;						//RETURN 0 AS IT IS REPEATED WORD
}
