// OBST Daa.cpp : Defines the entry point for the console application.
//

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node
{
	char str[20];
	int index;
	float val;
	struct node *next;
};
typedef struct node* nodeptr;
nodeptr head = NULL;
int gl_index = 1;
float gl_p[100];
float b;
FILE *fp,*output;
char name[20][20];
void createnode()
{


	int i, j;
	nodeptr temp = NULL;
	char a[20];
	while (!feof(fp))
	{
		nodeptr curr = NULL, prev = NULL;
		temp = (struct node*)malloc(sizeof(struct node));
		fscanf(fp, "%s", &temp->str);
		fgets(a, 20, fp);
		temp->index = gl_index;
		b = atof(a);
		int flag = 0;
		temp->val = b;
		gl_p[gl_index] = temp->val;
		gl_index++;
		temp->next = NULL;
		if (head == NULL)
		{
			head = temp;
			curr = head;
		}
		else
		{
			curr = head;
			while (!(strcmp(temp->str, curr->str) < 0))
			{
				if(curr->next==NULL)
				{
					curr->next = temp;
					curr = curr->next;
					temp->next = NULL;
					flag = 0;
					break;
				}
				else 
				{
					flag = 1;
					prev = curr;
					curr = curr->next;
				}
			}
			if (curr == head)
			{
				temp->next = curr;
				head = temp;
			}
			else
			{
				if (flag == 1)
				{
				prev->next = temp;
				temp->next = curr;
				}
			}
			flag = 0;
		}
	}
}
void delete()
{
	nodeptr node,temp;
	node = head;
	while (node->next != NULL)
	{
		temp = node;
		node = node->next;
	}
	if (node == node->next)
	{
		node->next = NULL;
		temp->next = NULL;
		free(node);
		return;
	}
	node->next = NULL;
	temp->next = NULL;
	free(node);
}

void print()
{
	nodeptr curr = NULL, temp = NULL;
	curr = head;
	gl_index = 1;
	while (curr != NULL)
	{
		
		curr->index = gl_index;
		gl_p[gl_index] = curr->val;
		strcpy(name[gl_index], curr->str);
		gl_index++;
		curr = curr->next;
	}
}
void obst_print(float R[21][20],int i, int j, int r1, char *dir)
{
	int t;
	if (i <= j)
	{
		t =(int)R[i][j];
		if(strcmp(name[t],"")!=0 && strcmp(name[r1],"")!=0)
		{
			fprintf(output,"%s is %s child of %s\n", name[t], dir, name[r1]);
		}
		obst_print(R,i, t - 1, t, "left");
		obst_print(R,t + 1, j, t, "right");
	}
}

void optsearchtree(int n, const float p[],float *minavg)
{
	int i, j, k, diagonal,l,pos;
	float R[21][20];
	float min = 0;
	float A[21][20],sum=0;
	for (i = 1; i <=n; i++) //initialization
	{
		A[i][i - 1] = 0;
		R[i][i - 1] = 0;
		A[i][i] = p[i];
		R[i][i] = i;
	}

	A[n+1][n] = 0;
	R[n+1][n] = 0;
	for (diagonal = 1; diagonal <= n - 1; diagonal++)
	{
		for (i = 1; i <= n - diagonal; i++)
		{
			min = 0;
			sum = 0;
			j = i + diagonal;
			for (l = i; l <=j; l++)
			{
				sum = sum + p[l];
			}
			A[i][j] = sum;
			for (k = i; k <= j; k++)
			{
				sum = A[i][k - 1] + A[k + 1][j];
				if (min == 0)
				{
					min = sum;
					pos = k;
				}
				else if (sum<min)
				{
					min = sum;
					pos = k;
				}
			}
			A[i][j] += min;
			R[i][j] = pos;
		}
	}

	*minavg = A[1][n];
	fprintf(output,"%s is the root of the tree\n",name[(int)R[1][n]]);
	int r1 = (int)R[1][n];
	obst_print(R,1, r1 - 1, r1, "left");
	obst_print(R,r1 + 1, n, r1, "right");

}

int main(int argc,char *argv[])
{
//Taking input file from command line argument

	fp = fopen(argv[1], "r");
	output=fopen(argv[2],"w");
	createnode();
	print();
	float p[sizeof(gl_p) / sizeof(gl_p[1])];
	int i;
	for (i = 1; i < gl_index;i++)
	{
		p[i] = gl_p[i];
	}
	gl_index--;
	float R[21][20];
	float *root=(float*)malloc(sizeof(float));
	optsearchtree(gl_index, p,root);
	free(root);
	delete();
	fclose(fp);
	fclose(output);
	return 0;
}
