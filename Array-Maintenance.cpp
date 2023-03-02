#define _CRT_SECURE_NO_WARNINGS
//Because of the use of scanf, an unsafe function
//This program was changed from my original c file
//I was too lazy to change the scanf function to input

#include <stdio.h>
#include <stdlib.h>

struct Node
{
	long long x;      //value
	long long LeftNumber;     //number of node in the left_son sub-tree
	long long LeftSum;   //sum of the value of all node in the left sub-tree
	Node* left;       //left pointer
	Node* right;      //right pointer
};
// Node of tree

struct Node* createNode()
{
	struct Node* node = (struct Node*) malloc(sizeof(struct Node));
	node->x = 0;
	node->LeftNumber = 0;
	node->LeftSum = 0;
	node->left = NULL;
	node->right = NULL;
	return node;
}
//Initialize and create a node

void insert(Node* cur, long long k, long long x)
{
	if (cur->LeftNumber >= k)
	{
		if (cur->left == NULL)
		{
			cur->left = createNode();
			cur->left->x = x;         //cur->left->x   （0-->x)
			cur->LeftNumber++;        //number of node in the left_son sub-tree increase
			cur->LeftSum += x;        //sum of the value of all node in the left sub-tree increase
		}
		else
		{
			insert(cur->left, k, x);
			cur->LeftNumber++;
			cur->LeftSum += x;
		}
	}
	else
	{
		if (cur->right == NULL)
		{
			cur->right = createNode();
			cur->right->x = x;        ////cur->right->x   （0-->x)
		}
		else
		{
			if (cur->x != 0)
				insert(cur->right, k - cur->LeftNumber - 1, x);  //We need to minus 1 since cur->x != 0
			else
				insert(cur->right, k - cur->LeftNumber, x);
		}
	}
}

Node* root = NULL;


//find the node with index == cur->LeftNumber and its left sum
//LeftSum = find(root, l - 1)
//RightSum = find(root, r)
//implenment the sum function as RightSum - LeftSum
//Speed up the summation command to reduce TLE cases
long long find(Node * cur, long long index)
{
	if (cur == NULL)
		return 0;
	if (cur->LeftNumber == index)
	{
		return cur->LeftSum;
	}
	else if (cur->LeftNumber > index)
	{
		return find(cur->left, index);
	}
	else
	{
		if(cur->x != 0)
			return cur->LeftSum + cur->x + find(cur->right, index - cur->LeftNumber - 1);
		else
			return cur->LeftSum + cur->x + find(cur->right, index - cur->LeftNumber);
	}
}


int del(Node* cur, long long k)
{
	if (cur->LeftNumber >= k)
	{
		if (cur->LeftNumber == k)
		{
			if (cur->x != 0)
			{
				long long ret = cur->x;
				cur->x = 0;
				return ret;            //return the value that is needed to delete, for LeftSum to update
			}
			else
			{
				long long ret = del(cur->right, k - cur->LeftNumber);
				return ret;
			}
		}
		long long ret = del(cur->left, k);
		cur->LeftSum -= ret;              //update the LeftSum
		cur->LeftNumber--;
		return ret;
	}
	else
	{
		if (cur->x != 0)
		{
			long long ret = del(cur->right, k - cur->LeftNumber - 1);  //We need to minus 1 since cur->x != 0
			return ret;
		}
		else
		{
			long long ret = del(cur->right, k - cur->LeftNumber);
			return ret;
		}
	}
}

int main()
{
	int n;
	scanf("%d", &n);
	for (int nn = 0; nn < n; nn++)
	{
		int cmd;
		scanf("%d", &cmd);
		if (cmd == 1)
		{
			long long k;
			long long x;
			scanf("%lld%lld", &k, &x);
			if (root == NULL)
			{
				root = createNode();      //Initialize when root == NULL
				root->x = x;
			}
			else
			{
				insert(root, k, x);
			}
		}
		else if (cmd == 2)
		{
			long long k;
			scanf("%lld", &k);
			del(root, k - 1);
		}
		else if (cmd == 3)
		{
			long long l;
			long long r;
			scanf("%lld%lld", &l, &r);
			long long LeftSum = find(root, l - 1);
			long long RightSum = find(root, r);
			printf("%lld\n", RightSum - LeftSum); 
		}
	}

	return 0;
}

