//40843245 Jay 
#include <iostream>
#include <limits>
#include <vector>
#include <cstdlib>
using namespace std;

#define NOTFOUND -1
struct WEIGHTED_EDGE
{
	int u;
	int v;
	int weight;
	//dummy constructor
	WEIGHTED_EDGE()
	{
		
	}
	WEIGHTED_EDGE(int u,int v,int weight)
	{
		this->u=u;
		this->v=v;
		this->weight=weight;
	}
};

class GRAPH 
{
protected:
	int numOfV;
	int numOfE;
	int **adjacencyMatrix;
	int **adjacencyMatrix_backup;
public:
	//dummy constructor
	GRAPH()
	{
		
	}
public:
	void display_adjacencyMatrix()
	{
		for(int i=0;i<this->numOfV;i++)
		{
			for(int j=0;j<this->numOfV;j++)
			{
				cout<<"adjacencyMatrix["<<i<<"]["<<j<<"]="<<this->adjacencyMatrix[i][j]<<"\t";
			}
			cout<<endl;
		}	
	}
public:
	void setNumOfV(int numOfV)
	{
		this->numOfV=numOfV;
	}
	void setNumOfE(int numOfE)
	{
		this->numOfE=numOfE;
	}
	//allocate
	void allocate_adjacencyMatrix()
	{
		this->adjacencyMatrix=new int *[this->numOfV];
		for(int i=0;i<this->numOfV;i++)
		{
			this->adjacencyMatrix[i]=new int [this->numOfV];
		}
		for(int i=0;i<this->numOfV;i++)
		{
			for(int j=0;j<this->numOfV;j++)
			{
				this->adjacencyMatrix[i][j]=INT_MAX;		
			}
		}
	}
	void allocate_adjacencyMatrix_backup()
	{
		this->adjacencyMatrix_backup=new int *[this->numOfV];
		for(int i=0;i<this->numOfV;i++)
		{
			this->adjacencyMatrix_backup[i]=new int [this->numOfV];
		}
		for(int i=0;i<this->numOfV;i++)
		{
			for(int j=0;j<this->numOfV;j++)
			{
				this->adjacencyMatrix_backup[i][j]=INT_MAX;		
			}
		}
	}
public:
	//copy adjacencyMatrix to adjacencyMatrix_backup
	void copy()
	{
		for(int i=0;i<this->numOfV;i++)
		{
			for(int j=0;j<this->numOfV;j++)
			{
				this->adjacencyMatrix_backup[i][j]=this->adjacencyMatrix[i][j];		
			}
		}
	}
	//backup adjacencyMatrix with adjacencyMatrix_backup
	void backup()
	{
		for(int i=0;i<this->numOfV;i++)
		{
			for(int j=0;j<this->numOfV;j++)
			{
				this->adjacencyMatrix[i][j]=this->adjacencyMatrix_backup[i][j];		
			}
		}
	}
public:
	void insertEdge(int u,int v,int weight)
	{
		this->adjacencyMatrix[u][v]=weight;
		this->adjacencyMatrix[v][u]=weight;
	}
};

class MST: public GRAPH
{
private:
	vector<int> old_V;
	vector<int> old_E;
	vector<int> new_V;
	vector<WEIGHTED_EDGE> new_E;
	int min_cost;
public:
	//dummy constructor
	MST()
	{
	
	}
public:
	void initialize()
	{
		this->min_cost=0;
		this->new_V.clear();
		this->new_E.clear();
		
		this->old_V.clear();
		for(int i=0;i<this->numOfV;i++)
		{
			this->old_V.push_back(i);
		}
	}
public:
	int findElementIdx(vector<int> vec,int tar)
	{
		int idx=0;
		vector<int>::iterator it;
		for(it=vec.begin();it!=vec.end();it++)
		{
			if((*it)==tar)
			{
				return idx;
			}
			idx++;
		}
		return NOTFOUND;
	}
	int findMinVector(vector<int> vec,int *idx_from,int *idx_go)
	{
		*idx_from=vec[0];
		*idx_go=0;
		int minVal=this->findMinElement(vec[0],idx_go);
		int val=0;

		for(int i=1;i<vec.size();i++)
		{
			val=this->findMinElement(vec[i],idx_go);
			if(val<minVal)
			{
				minVal=val;
				*idx_from=vec[i];
			}
		}
		return minVal;
	}
	//find minimum weight columnwisely with adjacency matrix
	int findMinElement(int row,int *idx)
	{
		*idx=0;
		int minVal=this->adjacencyMatrix[row][0];
		int val=0;
		for(int i=1;i<this->numOfV;i++)
		{
			val=this->adjacencyMatrix[row][i];
			if(val<minVal)
			{
				*idx=i;
				minVal=val;
			}
		}
		return minVal;
	}
	bool check_cycle(int u,int v)
	{
		int ui=this->findElementIdx(this->old_V,u);
		int vi=this->findElementIdx(this->old_V,v);
		if(ui!=NOTFOUND && vi!=NOTFOUND)
		{
			return true;
		}
		return false;
	}
public:
	void display_MST()
	{
		cout<<"min cost of MST is "<<this->min_cost<<endl;
	}
public:
	void Prim(int s)
	{
		struct WEIGHTED_EDGE *e;
		this->initialize();
		
		int idx=this->findElementIdx(this->old_V,s);
		int minWeight=0;
		int u=0,v=0;
		
		this->old_V.erase(this->old_V.begin()+idx);
		this->new_V.push_back(s);
		u=s;
		
		for(int i=0;i<this->numOfV;)
		{
			idx=-1;
			
			minWeight=this->findMinVector(this->new_V,&u,&v);
			
			//check there is a cycle if we selecte the edge.
			if(!check_cycle(u,v))//no cycle.
			{
				//select the edge
				e=new struct WEIGHTED_EDGE(u,v,minWeight);
				//push the edge into E'
				this->new_E.push_back(*e);
				
				int idx=this->findElementIdx(this->old_V,v);
				this->old_V.erase(this->old_V.begin()+idx);
				this->new_V.push_back(v);
				
				//remove the edge from E by setting it to INT_MAX
				this->adjacencyMatrix[u][v]=INT_MAX;
				this->adjacencyMatrix[v][u]=INT_MAX;
				
				this->min_cost+=(minWeight);
				
				i++;
			}else // a cycle.
			{
				//discard the edge by E setting it to INT_MAX
				this->adjacencyMatrix[u][v]=INT_MAX;
				this->adjacencyMatrix[v][u]=INT_MAX;
			}
		}
		this->display_MST();	
	}
};


int main()
{
	int numOfE=0,numOfV=0;
	int u=0,v=0,tempWeight=0;
	cin>>numOfV>>numOfE;
	
	MST *my_mst=new MST();
	my_mst->setNumOfV(numOfV);
	my_mst->setNumOfE(numOfE);
	my_mst->allocate_adjacencyMatrix();
	//input
	for(int i=0;i<numOfE;i++)
	{
		cin>>u>>v>>tempWeight;
		my_mst->insertEdge(u,v,tempWeight);
	}
	my_mst->display_adjacencyMatrix();
	my_mst->Prim(1);
	return 0;
}
