#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

struct MatrixNode;
struct MatrixColumn;
struct Matrix;

typedef struct MatrixNode
{
	int value;
	struct MatrixNode *left;
	struct MatrixNode *right;
	struct MatrixNode *up;
	struct MatrixNode *down;
	struct MatrixColumn *handle;
} MatrixNode;

typedef struct MatrixColumn
{
	char name;
	int size;
	struct MatrixColumn *left;
	struct MatrixColumn *right;
	struct MatrixNode *head;
	struct Matrix *root;

} MatrixColumn; 

typedef struct Matrix
{
	int height;
	int width;
	MatrixColumn* head_column;
} Matrix;

MatrixNode* MatrixNode_create(int v, MatrixNode* l, MatrixNode* r, MatrixNode* u, MatrixNode* d, MatrixColumn* handle)
{
	MatrixNode* result = (MatrixNode*) malloc(sizeof(MatrixNode));
	assert(result!=NULL);

	result->left = l;
	result->right = r;
	result->up = u;
	result->down = d;
	result->handle = handle;

	return result;
}

void MatrixNode_destroy(MatrixNode* n)
{
	free((void *) n);
}

MatrixColumn* MatrixColumn_create(MatrixColumn* l, MatrixColumn* r, MatrixNode* h, char name, Matrix* root)
{
	MatrixColumn* result = (MatrixColumn*) malloc(sizeof(struct MatrixColumn));
	assert(result!=NULL);
	int c = 0;

	result->left = l;
	result->right = r;
	result->head = h;
	result->name = name;
	result->root = root;

	MatrixNode* next = (result->head)->down;
	while(next!=NULL)
	{
		if(next->down==NULL || next->up == NULL || next->left==NULL || next->right ==NULL)
			return NULL;
		next = next->down;
		c++;
	}
	result->size = c;
	return result;
}

void MatrixColumn_destroy(MatrixColumn* m)
{
	MatrixNode* current = m->head;
	while(current!=NULL)
	{
		MatrixNode_destroy(current);
		current = current->down;
	}
	free((void *) m);
}

Matrix* Matrix_create(int height, int width, MatrixColumn* head)
{
	Matrix* result = (Matrix*) malloc(sizeof(struct Matrix));
	assert(result!=NULL);

	result->head_column = head;
	MatrixColumn* next = (result->head_column)->right;

	while(next!=NULL)
	{
		if(next->right == NULL || next->left == NULL) return NULL;
		next = next->right;

	}

	result->height = height;
	result->width = width;
	return result;

}

void Matrix_destroy(Matrix* m)
{
	MatrixColumn* current = m->head_column;
	while(current!=NULL)
	{
		MatrixColumn_destroy(current);
		current = current->right;
	}
	free((void *) m);
}

Matrix* Matrix_simple_example()
{
	MatrixNode* a1, a4, b1, b2, b3, d1, d2, d4;
	MatrixColumn* a, b, c, d;
	Matrix* m;

	a1 = MatrixNode_create(1, &d1, &b1, &a4, &a4, &a);
	a4 = *MatrixNode_create(1, &d4, &d4, &a1, &a1, &a);
	b1 = *MatrixNode_create(1, &a1, &d1, &b3, &b1, &b);
	b2 = *MatrixNode_create(1, &d2, &d2, &b1, &b3, &b);
	b3 = *MatrixNode_create(1, &b3, &b3, &b2, &b1, &b);
	d1 = *MatrixNode_create(1, &b1, &a1, &d4, &d2, &d);
	d2 = *MatrixNode_create(1, &b2, &b2, &d1, &d4, &d);
	d4 = *MatrixNode_create(1, &a4, &a4, &d2, &d1, &d);

	a = MatrixColumn_create(&d, &b, a1, 'A', m);
	b = *MatrixColumn_create(&a, &d, &b1, 'B', m);
	c = *MatrixColumn_create(&b, &d, NULL, 'C', m);
	d = *MatrixColumn_create(&b, &a, &d1, 'D', m);

	m = Matrix_create(4, 4, a);

	return m;

}

Matrix* Matrix_identity(int n)
{
	//nodes: (1, self, self, self, self)
	MatrixNode **nodes[n];
	MatrixColumn **cols[n];
	Matrix *m;

	for(int i=0; i<n; i++)
	{
		nodes[i] = MatrixNode_create(1, nodes[i], nodes[i], nodes[i], nodes[i], cols[i]);
	}
	for(int i=0; i<n; i++)
	{
		cols[i] = MatrixColumn_create(cols[(i-1)%n], cols[(i+1)%n], nodes[i], (char)(i+67), m);
	}

	m = Matrix_create(n, n, cols[0]);

	return m;

}

void Matrix_print(Matrix* m)
{
	//translate toroid into 2D matrix
	int** mat[m->width][m->height];
	MatrixColumn* nextcol = m->head_column;
	//for each column
	for(int i=0; i<m->width; i++)
	{	
		MatrixNode* nextnode = nextcol->head;
		for(int x=0; x<nextcol->size; x++)
		{
			mat[x][i] = nextnode->value;
			nextnode = nextnode->down;
		}
		nextcol = nextcol->right;
	}

	//print matrix
	for(int i=0; i<m->height; i++)
	{
		printf("| ");
		for(int x=0; x<m->width; x++)
		{
			printf("%d ", mat[i][x]);
		}

		printf("|");
	}

}

bool Matrix_equal(Matrix* a, Matrix* b)
{
	if(a->width!=b->width || a->height!=b->height) return false;

	MatrixColumn* ca = a->head_column;
	MatrixColumn* cb = b->head_column;

	for(int i=0; i<a->width; i++)
	{
		MatrixNode* na = ca->head;
		MatrixNode* nb = cb->head;

		for(int i=0; i<a->height; i++)
		{
			if(na->value != nb->value) return false;
			na = na->down;
			nb = nb->down;
		}

		ca = ca->right;
		cb = cb->right;
	}

	return true;
}

int genrand(long max_val) {
    
    int number;
    
    srand ( time(NULL));
    
    long max_bound = RAND_MAX/max_val * max_val;
    do {
        number = rand();
    } while ( number > max_bound);
    
    number %= max_val;
    return number;
}

Matrix* Matrix_random(int n)
{
	int r = genrand(n-1);
	char cols[r];
	for(int i=0; i<r; i++) cols[r] = ('A'+i);

	Matrix* tor;
	MatrixColumn **columns[r];
	for(int c=0; c<r-1; c+=3)
	{
		MatrixNode **nodes[r/3];
		//generate list of random nodes
		for(int n=0; n<r; n++)
		{
			MatrixNode* left = MatrixNode_create(genrand(1), NULL, NULL, NULL, NULL, columns[n] );
			MatrixNode* right = MatrixNode_create(genrand(1), NULL, NULL, NULL, NULL, columns[n] );
			MatrixNode* up = MatrixNode_create(genrand(1), NULL, NULL, NULL, NULL, columns[n] );
			MatrixNode* down = MatrixNode_create(genrand(1), NULL, NULL, NULL, NULL, columns[n] );
			nodes[n] = MatrixNode_create(genrand(1), left, right, up ,down, columns[n]);
		}
		columns[c] = MatrixColumn_create(cols[(c-1)%n], cols[(c+1)%n], nodes[0], cols[c], tor);
	}
	tor = Matrix_create(r, r, columns[0]);
	return tor;
}

int main(int argc, char** argv)
{
	return 0;
}