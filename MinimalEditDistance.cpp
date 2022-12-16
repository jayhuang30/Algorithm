/*
BASIC INFO:
stu ID:40843245
name:Huang Jay

Due date:2022/11/25
HW: Algorithm HW3-2
*/

#include <iostream>
#include <string>
using namespace std;

//This code solves Minimal Edit Distance problem
class MinimalEditDistance
{
private:
string srcS;
string tarS;
//Array to store weight (or we can say cost)
//In this code, w[0] is the cost of deletion, 1 for insertion, 2 for replacement.
int w[3];
int wSize;
int **c;

//Array to store action, this array can store the action we need for mininal cost.
int *action;
//The number of action
int step;
int maxAction;

//Temporary array
int tempArr[4];
public:
	MinimalEditDistance(string srcS,string tarS,int maxAction,int *w,int wSize)
	{
		this->srcS=srcS;
		this->tarS=tarS;
		this->maxAction=maxAction;
		this->SetW(w,wSize);
		this->step=0;
		this->Init();
		this->FindMinimalEditDistance();
		this->DisplayResult();
	}
public:
	void Init()
	{
		this->action=new int[this->maxAction];
		for(int i=0;i<this->maxAction;i++)
		{
			this->action[i]=-1;//set unused.
		}
		
		this->c=new int*[this->srcS.length()];
		for(int i=0;i<this->srcS.length()+1;i++)
		{
			this->c[i]=new int[this->tarS.length()+1];
		}
	}
	void SetW(int *w,int wSize)
	{
		this->wSize=wSize;
		for(int i=0;i<this->wSize;i++)
		{
			this->w[i]=w[i];
		}
	}
	void FindMinimalEditDistance()
	{
		for(int row=0;row<this->srcS.length()+1;row++)
		{
			for(int col=0;col<this->tarS.length()+1;col++)
			{
				if(row==0)
				{
					this->c[row][col]=col;
				}else if(col==0)
				{
					this->c[row][col]=row;
				}else 
				{
					this->CheckOperation(row,col);
				}
			}
		}
	}
	void CheckOperation(int row,int col)
	{
		this->tempArr[0]=this->c[row-1][col]+this->w[0];
		this->tempArr[1]=this->c[row][col-1]+this->w[1];
		this->tempArr[2]=this->c[row-1][col-1]+this->w[2];
		this->tempArr[3]=this->c[row-1][col-1];	
		
		if(this->srcS[row]==this->tarS[col])
		{
			this->c[row][col]=this->tempArr[3];
			this->action[step]=3;
			this->step++;
		}else
		{
			int minIdx=0;
			int minVal=this->tempArr[0];
			for(int i=0;i<2;i++)
			{
				if(this->tempArr[i]<minVal)
				{
					minVal=this->tempArr[i];
					minIdx=i;
				}
			}
			this->c[row][col]=minVal;
			this->action[step]=minIdx;
			this->step++;
		}
	}
	void DisplayResult()
	{
		this->DisplayC();
		//This method is used to show actions.
		//Comment the following line if you don't want to see the actions.
		//this->DisplayAction(); 
	}
	void DisplayC()
	{
		cout<<this->c[this->srcS.length()][this->tarS.length()]<<endl;
	}
	void DisplayAction()
	{
		cout<<"One of sequence of actions to get the minimal edit distance is as follows."<<endl;
		for(int i=0;i<this->step;i++)
		{
			int tempAction=this->action[i];
			if(tempAction==0)//Deletion
			{
				cout<<"Deletion."<<endl;
			}
			else if(tempAction==1) //Insertion
			{
				cout<<"Insertion."<<endl;
			}else if(tempAction==2)//Replacement
			{
				cout<<"Replacement."<<endl;
			}else if(tempAction==3)//Nothing
			{
				cout<<"Nothing since the current two char are same."<<endl;
			}else //Error occurs.
			{
				cout<<"ERROR!!!"<<endl;
			}
		}
	}
};
int main()
{
	string srcS="";
	string tarS="";
	int maxLenOfString=1000;
	int w[3]={1,1,1};
	getline(cin,srcS);
	getline(cin,tarS);
	MinimalEditDistance *minimalEditDistance=new MinimalEditDistance(srcS,tarS,maxLenOfString,w,sizeof(w)/sizeof(w[0]));
	return 0;
}
