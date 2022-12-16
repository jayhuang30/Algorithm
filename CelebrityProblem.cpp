#include <iostream>
using namespace std;
#define NUM 3
class celebrity_problem
{
public:
	int *celebrity;
	int **Matrix;
	int numOfPeople;
public:
	celebrity_problem()
	{
		
	}
public:
	void setNumOfPeople(int numOfPeople)
	{
		this->numOfPeople=numOfPeople;
	}
	void allocateMatrix()
	{
		this->Matrix=new int *[this->numOfPeople];
		for(int i=0;i<this->numOfPeople;i++)
		{
			this->Matrix[i]=new int[this->numOfPeople];
		}
	}
	void allocateCelebrity()
	{
		this->celebrity=new int[this->numOfPeople];
	}
	void setMatrix(int arr[NUM][NUM])
	{
		this->allocateMatrix();
		for(int i=0;i<this->numOfPeople;i++)
		{
			for(int j=0;j<this->numOfPeople;j++)
			{
				this->Matrix[i][j]=arr[i][j];
			}
		}
	}
	void display_All()
	{
		for(int i=0;i<this->numOfPeople;i++)
		{
			cout<<"Is ith people is a celebrity?"<<(this->celebrity[i]==true?("true"):("false"))<<endl;
		}
	}
	void findCelebrity()
	{
		this->allocateCelebrity();
		for(int i=0;i<this->numOfPeople;i++)
		{
			bool isCelebrity=true;
			for(int k=0;k<this->numOfPeople;k++)
			{
				if(i==k)
				{
					continue;
				}
				if(this->Matrix[i][k]!=1)
				{
					isCelebrity=false;
					break;
				}
			}
			if(isCelebrity==true)
			{
				for(int k=0;k<this->numOfPeople;k++)
				{	
					if(i==k)
					{
						continue;
					}
					if(this->Matrix[k][i]!=0)
					{
						isCelebrity=false;
						break;
					}
				}
			}
			this->celebrity[i]=isCelebrity;
		}
	}
};
int main()
{
	celebrity_problem *C=new celebrity_problem();
	C->setNumOfPeople(NUM);
	int Matrix[NUM][NUM]={1,0,0,1,1,0,0,0,1};
	C->setMatrix(Matrix);
	C->findCelebrity();
	C->display_All();
	return 0;
}
