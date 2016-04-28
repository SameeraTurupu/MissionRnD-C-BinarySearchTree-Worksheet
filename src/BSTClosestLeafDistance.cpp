/*
Given a Binary Search Tree and a Node(temp).Find the Closest Distance from the Node to 
any leaf of the Tree.
(Least number of Edges needed to be travelled to go to the Node )

Ex : Consider the below tree .
      2
     / \
,   1   3
         \
         14
For 3 ,Output is 1 . As its closest leaf is 14 and 3 is at a distance of 1 to 14 .

Ex 2: Consider the below tree .
    2
   / \
  1   3
       \
        14
        / \
       9   20
      /      \
     6       25
For 3 ,Output is now 2 . As closest leaf to 3 is 1 and 3 is at a distance of 2 to 1 .
(through root 2 )

For 14 ,O/P : 2
For 2 , O/P : 1

Return -1 ,for Invalid Inputs
*/

#include <stdlib.h>
#include <stdio.h>

struct node{
  struct node * left;
  int data;
  struct node *right;
};
void closestLeafdown(node *root, int level, int *minDist)
{
	if (root == NULL)
		return;
	if (root->left == NULL && root->right == NULL)
	{
		if (level < (*minDist))
			*minDist = level;
		return;
	}
	closestLeafdown(root->left, level + 1, minDist);
	closestLeafdown(root->right, level + 1, minDist);
}
int findThroughParent(node * root, node *x, int *minDist)
{
	if (root == NULL) return -1;
	if (root == x) return 0;
	int left1 = findThroughParent(root->left, x, minDist);
	if (left1 != -1)
	{
		closestLeafdown(root->right, left1 + 2, minDist);
		return left1 + 1;
	}
	int right1 = findThroughParent(root->right, x, minDist);
	if (right1 != -1)
	{
		closestLeafdown(root->left, right1 + 2, minDist);
		return right1 + 1;
	}

	return -1;
}

int get_closest_leaf_distance(struct node *root, struct node *temp)
{
	if (!root || !temp)
		return -1;
	int minDist = INT_MAX;
	closestLeafdown(temp, 0, &minDist);
	findThroughParent(root, temp, &minDist);
	return minDist;
}