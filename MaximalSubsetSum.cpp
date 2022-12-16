/*
BASIC INFO:
stu ID:40843245
name:Huang Jay

Due date:2022/11/25
HW: Algorithm HW3-1
*/

#include <iostream>
using namespace std;

//This code solves Maximal Subsequent Subset Sum problem
class MaximalSubsetSum
{
private:
	int size;
	int *arr;
	int *f;
	int ans;
public:
	MaximalSubsetSum(int size)
	{
		this->size=size;
		this->arr=new int[this->size];
		this->f=new int[this->size];
		this->ans=0;
		this->FetchInput();
		this->Init();
		this->FindMaximalSubsetSum();
		this->DisplayResult();
	}
public:
	void FetchInput()
	{
		int val=0;
		for(int i=0;i<this->size;i++)
		{
			cin>>val;
			this->arr[i]=val;
		}
	}
	void Init()
	{
		for(int i=0;i<this->size;i++)
		{
			this->f[i]=0;
		}
	}
	void FindMaximalSubsetSum()
	{
		for(int i=0;i<this->size;i++)
		{
			if(i==0 || this->f[i-1]<=0)
			{
				this->f[i]=this->arr[i];
			}else
			{
				this->f[i]=this->f[i-1]+this->arr[i];
			}
		}
		
		this->ans=this->f[0];
		for(int i=0;i<this->size;i++)
		{
			if(this->f[i]>this->ans)
			{
				this->ans=this->f[i];
			}
		}
	}
	void DisplayResult()
	{
		cout<<this->ans<<endl;
	}
};
int main()
{
	int numOfData=0;
	int size=0;
	cin>>numOfData;
	while(numOfData--)
	{
		cin>>size;
		MaximalSubsetSum *maximalSubsetSum=new MaximalSubsetSum(size);
	}
	return 0;
}
