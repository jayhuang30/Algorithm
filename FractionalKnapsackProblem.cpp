//40843245 Jay
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string>
using namespace std;

typedef struct pair
{
int index;
double value;	
}PAIR;
class knapsack_bag
{
private:
	int max_load;
	int *price;
	int *weight;
	int n;
	PAIR *sorted_ratio;
	double *selected_load;
	double curr_load;
	double max_profit;
public:	
	knapsack_bag(int n)
	{
		this->n=n;
		price=new int[this->n];
		weight=new int[this->n];
	}
	void setPrice(int *arr,int n)
	{
		int i=0;
		for(i=0;i<n;i++)
		{
			this->price[i]=arr[i];
		}
	}
	void setWeight(int *arr,int n)
	{
		int i=0;
		for(i=0;i<n;i++)
		{
			this->weight[i]=arr[i];
		}
	}
	void setMaxLoad(int max_load)
	{
		this->max_load=max_load;
	}
	void display_sorted_ratio()
	{
		for(int i=0;i<this->n;i++)
		{
			cout<<"("<<this->sorted_ratio[i].index<<","<<this->sorted_ratio[i].value<<")"<<endl;
		}
		cout<<endl;
	}
	void display_ratio(double *arr,int n)
	{
		for(int i=0;i<n;i++)
		{
			cout<<arr[i]<<endl;
		}
		cout<<endl;
	}
	void display_PriceWeight()
	{
		cout<<"price and weight is:(price,weight)."<<endl;
		for(int i=0;i<this->n;i++)
		{
			cout<<"("<<this->price[i]<<","<<this->weight[i]<<")"<<endl;
		}
	}
	void display_maxProfit()
	{
		cout<<"my max profit is "<<this->max_profit<<endl;	
		for(int i=0;i<this->n;i++)
		{
			cout<<"selected_load["<<i<<"]="<<this->selected_load[i]<<endl;
		}
	}
public:
	//sort the CP where CP[i]=price[i]/weight[i] with insertion sort.
	void sort_ratio(double *arr)
	{
		sorted_ratio=new PAIR[this->n];
		for(int i=0;i<this->n;i++)
		{
			sorted_ratio[i].index=i;
			sorted_ratio[i].value=arr[i];
		}
		
		sorted_ratio[0].value=arr[0];
		sorted_ratio[0].index=0;
		for(int i=1;i<this->n;i++)
		{	
			for(int j=this->n-1;j>=i;j--)
			{
				if(sorted_ratio[j].value<sorted_ratio[j-1].value)
				{
					int tempI=sorted_ratio[j].index;
					sorted_ratio[j].index=sorted_ratio[j-1].index;
					sorted_ratio[j-1].index=tempI;
					double temp=sorted_ratio[j].value;
					sorted_ratio[j].value=sorted_ratio[j-1].value;
					sorted_ratio[j-1].value=temp;
				}
			}
		}	
	}
public:
	//major function
	void fractional_knapsack()
	{
		bool *selected=new bool[this->n];	
		for(int i=0;i<this->n;i++)
		{
			selected[i]=false;
		}
		
		double *ratio=new double[this->n];
		for(int i=0;i<this->n;i++)
		{
			ratio[i]=double(this->price[i])/this->weight[i];
		}
		
		selected_load=new double[this->n];
		for(int i=0;i<this->n;i++)
		{
			selected_load[i]=0;
		}
		sort_ratio(ratio);
		this->curr_load=0;
		this->max_profit=0;
				
		int curr_idx=this->n-1;
		while(curr_idx>=0 && this->curr_load<this->max_load-0.0000001)
		{
			int tempI=sorted_ratio[curr_idx].index;
			//Cases that can all fetch
			if(this->weight[tempI]<=(this->max_load-this->curr_load))
			{
				this->curr_load+=this->weight[tempI];
				this->max_profit+=this->price[tempI];
				this->selected_load[tempI]=this->weight[tempI];
			}
			//Cases that can NOT all fetch
			else
			{
				double val=(this->max_load-this->curr_load)*ratio[tempI];
			
				this->max_profit+=val;
				this->selected_load[tempI]=(this->max_load-this->curr_load);
				this->curr_load=this->max_load;
			}
			curr_idx--;
		}
		this->display_maxProfit();
	}
};
int main()
{
	int numOfItems=0;
	int max_load=0;
	int tempPrice=0,tempWeight=0;
	int *price,*weight;
	cin>>numOfItems;
	cin.get(); //discard a new line char.
	cin>>max_load;
	cin.get();
	
	price=new int[numOfItems];
	weight=new int[numOfItems];
	for(int i=0;i<numOfItems;i++)
	{
		cin>>tempPrice>>tempWeight;
		price[i]=tempPrice;
		weight[i]=tempWeight;
	}
	
	knapsack_bag *my_bag=new knapsack_bag(numOfItems);
	my_bag->setPrice(price,numOfItems);
	my_bag->setWeight(weight,numOfItems);
	my_bag->display_PriceWeight();
	my_bag->setMaxLoad(max_load);
	my_bag->fractional_knapsack();
	return 0;
}
