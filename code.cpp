#include<bits/stdc++.h>

#define int long long int
#define F first
#define S second
#define pb push_back
#define que_max priority_queue<int>
#define que_min priority_queue<int,vector<int>,greater<int>>;
#define endl "\n"
using namespace std;


struct Node {
	string name;
	int lockedBy;
	vector<Node*>children;
	set<Node*>lockedChildren;
	Node *parent;

	Node(string name,Node* parent) {
		this->name=name;
		lockedBy=-1;
		this->parent = parent;

	}


	void show()
	{
		cout<<"Name is "<<this->name<<endl;
	}

	void addChildren(vector<Node*> childrens)
	{
		for(auto it:childrens)
		{
			this->children.push_back(it);
		}
	}

} ;


void print(Node *root)
{
	if(root==NULL)
	{
		return;
	}
	cout<<"yes we have entered the node"<<endl;
	root->show();
	cout<<"this node is locked by "<<root->lockedBy<<endl;

	if (root->parent != nullptr) {
		cout << "parent of the node is " << root->parent->name << endl;
	} else {
		cout << "This node has no parent (it's the root node)." << endl;
	}

	if(root->children.size()) {
		cout<<"The children of nodes are "<<endl;
	}
	else {
		cout<<"it have no childrens"<<endl;
	}

	for(auto it:root->children)
	{
		it->show();
	}

	for(auto it:root->children)
	{
		print(it);
	}
}




struct MakeArTree {

	Node* root;
	unordered_map<string,Node*>nameToPointer;
	vector<string>names;
	int n,m;

	MakeArTree(string name,vector<string>names,int n, int m)
	{
		this->n=n;
		this->m=m;
		root = new Node(name, nullptr);
		this->names=names;
		nameToPointer[name] =root;
	}

	void treeFormation() {
		queue<Node* >q;
		q.push(root);
		int i,k=1;
		while(q.size()>0)
		{
			Node* front=q.front();
			q.pop();
			nameToPointer[front->name] = front;
			vector<Node*>b;
			for( i=k; i<min(n,k+m); i++)
			{
				b.push_back(new Node(names[i],front));

			}
			front->addChildren(b);

			for(auto it:b)
			{
				q.push(it);

			}
			k=i;
		}


	}

	void show(string name1)
	{	cout<<"yha aya"<<endl;
		Node* ptr = nameToPointer[name1];
		cout<<ptr->name<<endl;
		print(ptr);
	}

	bool lock(string name1,int id)
	{
		Node* root = nameToPointer[name1];
		if((root->lockedBy!=-1) || (root->lockedChildren.size()))
		{
			return false;
		}

		Node* ptr= root->parent;
		root->lockedBy=id;
		ptr=root->parent;
		while(ptr!=nullptr)
		{
			if(ptr->lockedBy!=-1)return false;
			ptr->lockedChildren.insert(root);
			ptr=ptr->parent;
		}

		return true;
	}

	bool unlock(string name2,int id)
	{
		Node* root = nameToPointer[name2];
		if((root->lockedBy!=id)||(root->lockedChildren.size()))return false;

		Node* ptr= root->parent;
		while(ptr!=nullptr)
		{
			//if(ptr->lockedBy!=-1)
			ptr->lockedChildren.erase(root);
			ptr=ptr->parent;
		}
		root->lockedBy=-1;

		return true;
	}

	bool upgrade(string name2,int id)
	{
		Node* root= nameToPointer[name2];

		if((root->lockedBy!=-1)||(root->lockedChildren.size()==0))return false;

		Node *ptr= root->parent;
		while(ptr!=nullptr)
		{
			if(ptr->lockedBy!=-1)return  false;
			ptr = ptr->parent;
		}

		vector<string>names_of_lockedC;
		for(auto it:root->lockedChildren)
		{
			names_of_lockedC.push_back(it->name);
		}

		for(auto it:names_of_lockedC)
		{
			if(!unlock(it,id))return false;
		}
		lock(root->name,id);


		return true;

	}

};





int32_t main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
#endif

	int n,m,k;
	vector<string>names;
	cin>>n>>m>>k;
	for(int i=0; i<n; i++)
	{
		string s;
		cin>>s;
		names.push_back(s);
	}

	MakeArTree* tree = new MakeArTree(names[0],names,n,m);
	tree->treeFormation();
	for(int i=0; i<k; i++)
	{
		int op,id;
		string name;
		cin>>op;
		cin>>name;
		cin>>id;
		cout<<op<<" "<<name<<" "<<id<<endl;
		if(op==1)
		{
			if(tree->lock(name,id))
			{
				cout<<"Successful operation"<<endl;
			} else
			{
				cout<<"Unsuccessful operation"<<endl;
			}
		} else if(op==2)
		{
			if(tree->unlock(name,id))
			{
				cout<<"Successful operation"<<endl;
			} else
			{
				cout<<"Unsuccessful operation"<<endl;
			}
		} else if(op==3)
		{	if(tree->upgrade(name,id))
			{
				cout<<"Successful operation"<<endl;
			} else
			{
				cout<<"Unsuccessful operation"<<endl;
			}

		}
	}

	tree->show("World");








	return 0;
}
