#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <algorithm>
using namespace std;

class personnel_assignment
{
public:
	int **cost_Matrix;
	int **reduced_cost_Matrix;
	int *minRow;
	int *minCol;
	int numOfProcess;
	int numOfJob;
	int minCost;
public:
	personnel_assignment()
	{
		
	}
public:
	void display_All()
	{
		this->display_costMatrix();
		this->display_reducedCostMatrix();
		this->display_minCost();
	}
	void display_minCost()
	{
		cout<<"min_cost="<<this->minCost<<endl;
	}
	void display_reducedCostMatrix()
	{
		for(int i=0;i<this->numOfProcess;i++)
		{
			for(int j=0;j<this->numOfJob;j++)
			{
				cout<<"reduced_cost_Matrix["<<i<<"]["<<j<<"]="<<this->reduced_cost_Matrix[i][j]<<"\t";
			}
			cout<<endl;
		}
	}
	void display_costMatrix()
	{
		for(int i=0;i<this->numOfProcess;i++)
		{
			for(int j=0;j<this->numOfJob;j++)
			{
				cout<<"cost_Matrix["<<i<<"]["<<j<<"]="<<this->cost_Matrix[i][j]<<"\t";
			}
			cout<<endl;
		}
	}
public:
	int minValue_Col(int col)
	{
		int res=this->reduced_cost_Matrix[0][col];
		int val=0;
		for(int i=1;i<this->numOfJob;i++)
		{
			val=this->reduced_cost_Matrix[i][col];
			if(val<res)
			{
				res=val;
			}
		}
		return res;
	}
	int minValue_Row(int row)
	{
		int res=this->reduced_cost_Matrix[row][0];
		int val=0;
		for(int i=1;i<this->numOfProcess;i++)
		{
			val=this->reduced_cost_Matrix[row][i];
			if(val<res)
			{
				res=val;
			}
		}
		return res;
	}
public:
	void setNumOfProcess(int numOfProcess)
	{
		this->numOfProcess=numOfProcess;
	}
	void setNumOfJob(int numOfJob)
	{
		this->numOfJob=numOfJob;
	}
	void allocate_costMatrix()
	{
		this->cost_Matrix=new int *[this->numOfProcess];
		for(int i=0;i<this->numOfProcess;i++)
		{
			this->cost_Matrix[i]=new int [this->numOfJob];
		}
	}
	void allocate_reducedCostMatrix()
	{
		this->reduced_cost_Matrix=new int *[this->numOfProcess];
		for(int i=0;i<this->numOfProcess;i++)
		{
			this->reduced_cost_Matrix[i]=new int [this->numOfJob];
		}
	}
	void allocateRowCol()
	{
		this->minRow=new int[this->numOfProcess];
		this->minCol=new int [this->numOfJob];
	}
public:
	void backup()
	{
		for(int i=0;i<this->numOfJob;i++)
		{
			for(int j=0;j<this->numOfProcess;j++)
			{
				this->reduced_cost_Matrix[i][j]=this->cost_Matrix[i][j];
			}
		}
	}
public:
	void subtractRow(int index,int value)
	{
		for(int i=0;i<this->numOfJob;i++)
		{
			this->reduced_cost_Matrix[index][i]-=(value);
		}
	}
	void subtractCol(int index,int value)
	{
		for(int i=0;i<this->numOfProcess;i++)
		{
			this->reduced_cost_Matrix[i][index]-=(value);
		}
	}
public:
	void reduce()
	{
		this->allocate_reducedCostMatrix();
		this->backup();
		this->allocateRowCol();
		for(int i=0;i<this->numOfProcess;i++)
		{
			this->minRow[i]=this->minValue_Row(i);
		}
		for(int i=0;i<this->numOfJob;i++)
		{
			this->subtractRow(i,this->minRow[i]);
		}
		for(int j=0;j<this->numOfJob;j++)
		{
			this->minCol[j]=this->minValue_Col(j);
		}
		for(int j=0;j<this->numOfProcess;j++)
		{
			this->subtractCol(j,this->minCol[j]);
		}	
	}
	void setCostMatrix(int **arr)
	{
		this->allocate_costMatrix();
		for(int i=0;i<this->numOfProcess;i++)
		{
			for(int j=0;j<this->numOfJob;j++)
			{
				this->cost_Matrix[i][j]=arr[i][j];
			}
		}	
	}
public:
	void computeMinCost()
	{
		this->reduce();
		this->minCost=0;
		for(int j=0;j<this->numOfProcess;j++)
		{
			this->minCost+=(this->minRow[j]);
		}
		for(int i=0;i<this->numOfJob;i++)
		{
			this->minCost+=(this->minCol[i]);
		}
	}
};
int main()
{
	int **cost_Matrix;
	cost_Matrix=new int *[4];
	for(int i=0;i<4;i++)
	{
		cost_Matrix[i]=new int [4];
	}
	cost_Matrix[0][0]=29;
	cost_Matrix[0][1]=19;
	cost_Matrix[0][2]=17;
	cost_Matrix[0][3]=12;
	cost_Matrix[1][0]=32;
	cost_Matrix[1][1]=30;
	cost_Matrix[1][2]=26;
	cost_Matrix[1][3]=28;
	cost_Matrix[2][0]=3;
	cost_Matrix[2][1]=21;
	cost_Matrix[2][2]=7;
	cost_Matrix[2][3]=9;
	cost_Matrix[3][0]=18;
	cost_Matrix[3][1]=13;
	cost_Matrix[3][2]=10;
	cost_Matrix[3][3]=15;
	
	personnel_assignment *Person=new personnel_assignment();
	Person->setNumOfProcess(4);
	Person->setNumOfJob(4);
	Person->setCostMatrix(cost_Matrix);
	Person->computeMinCost();
	Person->display_All();
	
	return 0;
}
