#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

#define eps (pow(10.0,-6))

class BAG
{
public:
	int numOfItems;
	int *price;
	int *weight;
	int C;
	int *selected;
	int max_profit;
	double *d;
	double *d_sort;
	double d_sort_median;
	int *G;
	int *E;
	int *L;
	int G_N;
	int E_N;
	int L_N;
	int W_G;
	int W_E;
	int W_L;
	int *tempObj;
public:
	BAG(int numOfItems)
	{
		this->setNumOfItems(numOfItems);
		this->allocate();
		this->selected=new int[this->numOfItems];
		this->max_profit=0;
		for(int i=0;i<this->numOfItems;i++)
		{
			this->selected[i]=0;
		}
	}
	
public:
	void display_All()
	{
		cout<<"max_profit is "<<this->max_profit<<endl;
	}
public:
	void setNumOfItems(int numOfItems)
	{
		this->numOfItems=numOfItems;
	}
	void allocate()
	{
		this->price=new int[this->numOfItems];
		this->weight=new int[this->numOfItems];
		this->d=new double[this->numOfItems];
		this->d_sort=new double[this->numOfItems];
	}
	void setPrice(int *arr)
	{
		for(int i=0;i<this->numOfItems;i++)
		{
			this->price[i]=arr[i];
		}
	}
	void setWeight(int *arr)
	{
		for(int i=0;i<this->numOfItems;i++)
		{
			this->weight[i]=arr[i];
		}
	}
	void setMaxLoad(int C)
	{
		this->C=C;
	}
	void computeD()
	{
		for(int i=0;i<this->numOfItems;i++)
		{
			this->d[i]=double(this->price[i])/this->weight[i];
		}
	}
	void sortD()
	{
		for(int i=0;i<this->numOfItems;i++)
		{
			this->d_sort[i]=this->d[i];
		}
		for(int i=1;i<this->numOfItems;i++)
		{
			for(int j=i;j>=0;j--)
			{
				if(this->d_sort[j]<this->d_sort[j-1])
				{
					double tempD=this->d_sort[j];
					this->d_sort[j]=this->d_sort[j-1];
					this->d_sort[j-1]=tempD;
				}else
				{
					break;
				}
			}
		}
	}
	void findMedian()
	{
		if(this->numOfItems%2==1)
		{
			this->d_sort_median=this->d_sort[(this->numOfItems+1)/2-1];
		}
		else
		{
			this->d_sort_median=(this->d_sort[this->numOfItems/2-1]+this->d_sort[this->numOfItems/2])/2;
		}
	}
	void allocate_partition()
	{
		this->G=new int[this->numOfItems];
		this->E=new int[this->numOfItems];
		this->L=new int[this->numOfItems];
	}
	void init_parition()
	{
		this->W_G=0;
		this->W_E=0;
		this->W_L=0;
		this->G_N=0;
		this->E_N=0;
		this->L_N=0;
	}
	void partition()
	{
		this->init_parition();
		this->allocate_partition();
		
		for(int i=this->numOfItems-1;i>=0;i--)
		{
			if(this->d[i]>this->d_sort_median+eps)
			{
				this->G[this->G_N]=i;
				this->G_N++;
			}
			else if(abs(this->d[i]-this->d_sort_median)<eps)
			{
				this->E[this->E_N]=i;
				this->E_N++;
			}else
			{
				this->L[this->L_N]=i;
				this->L_N++;
			}
		}
	}
	void computeWG()
	{
		this->W_G=0;
		for(int i=0;i<this->G_N;i++)
		{
			this->W_G+=this->G[i];
		}
	}
	void computeWE()
	{
		this->W_E=0;
		for(int i=0;i<this->E_N;i++)
		{
			this->W_E+=this->E[i];
		}
	}
	void computeWL()
	{
		this->W_L=0;
		for(int i=0;i<this->L_N;i++)
		{
			this->W_L+=this->L[i];
		}
	}
	void computeTotalWeight()
	{
		this->computeWG();
		this->computeWE();
		this->computeWL();	
	}
	void putIntoBag(int *arr,int size)
	{
		for(int i=0;i<size;i++)
		{
			this->selected[i]=1;
			this->max_profit+=(this->price[i]);
		}
	}
	void findWeightObject(int *arr,int size)
	{
		this->tempObj=new int[size];
		for(int i=0;i<size;i++)
		{
			this->tempObj[i]=this->weight[arr[i]];
		}
	}
	void findPriceObject(int *arr,int size)
	{
		this->tempObj=new int[size];
		for(int i=0;i<size;i++)
		{
			this->tempObj[i]=this->price[arr[i]];
		}
	}
	int brute_force(int W,int wt[],int val[],int n)
	{
		//base case
		if(n==0||W==0)
		{
			return 0;
		}
		if(wt[n-1]>W)
		{
			return brute_force(W,wt,val,n-1);
		}
		return max(brute_force(W,wt,val,n-1),brute_force(W-wt[n-1],wt,val,n-1)+val[n-1]);
	}
	void knapsack01()
	{
		if(this->numOfItems<=5)
		{
			this->max_profit=this->brute_force(this->C,this->weight,this->price,this->numOfItems);
			return;
		}
		this->computeD();
		this->sortD();
		this->findMedian();
		this->partition();
		this->computeTotalWeight();
		
		if(this->W_G>this->C)
		{
			this->setMaxLoad(this->C);
			this->setNumOfItems(this->G_N);
			this->weight=new int[this->G_N];
			for(int i=0;i<G_N;i++)
			{
				this->weight[i]=this->G[i];
			}
		}
		else if(this->W_G+this->W_E>this->C)
		{
			this->putIntoBag(this->G,this->G_N);
			this->setMaxLoad(this->C-this->W_G);
			this->findWeightObject(this->E,this->E_N);
			this->setWeight(this->tempObj);
			this->findPriceObject(this->E,this->E_N);
			this->setPrice(this->tempObj);
			this->knapsack01();
		}
		else
		{
			this->putIntoBag(this->G,this->G_N);	
			this->putIntoBag(this->E,this->E_N);
			this->setMaxLoad(this->C-this->W_G-this->W_E);
			this->findWeightObject(this->L,this->L_N);
			this->setWeight(this->tempObj);
			this->findPriceObject(this->L,this->L_N);
			this->setPrice(this->tempObj);
			this->knapsack01();
		}
	}
};
int main()
{
	BAG *my_bag=new BAG(4);
	int price[]={2,3,4,15,18};
	int weight[]={3,4,4,8,9};
	int C=36;
	my_bag->setPrice(price);
	my_bag->setWeight(weight);
	my_bag->setMaxLoad(C);
	my_bag->knapsack01();
	my_bag->display_All();
	return 0;
}
