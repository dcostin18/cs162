#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

struct ListNode;
struct List;

typedef struct ListNode
{
	int value;
	struct ListNode *succ;
	struct ListNode *prec;
	struct List *handle;

} ListNode;

typedef struct List 
{
	int count;
	ListNode *head;

} List;

ListNode* ListNode_create(int v, ListNode* s, ListNode* p, List* h)
{
	ListNode *result = (ListNode*) malloc(sizeof(ListNode));
	printf("MALLOC SUCCESS");
	assert(result!=NULL);

	result->value = v;
	result->succ = s;
	result->prec = p;
	result->handle = h;

	printf("LISTNODE CREATED");
	return result;
}

void ListNode_destroy(ListNode* ln)
{
	free((void *) ln);
}

void List_destroy(List* l)
{
	ListNode* current = l->head;
	while(current!=NULL)
	{
		ListNode_destroy(current);
		current = current->succ;
	}
	free((void *) l);
}

List* List_create(ListNode* head)
{
	List* result = (List*) malloc(sizeof(struct List));
	assert(result!=NULL);
	int c = 0;

	result->head = head;
	ListNode* next = (result->head)->succ;
	while(next!=NULL)
	{
		if(next->succ==NULL || next->prec == NULL) return NULL;
		next = next->succ;
		c++;
	}
	result->count=c;

	return result;
}

//Assumes successor is to the right
//Inserts node before succ (to the left of succ)
List* ListPush(ListNode *x, ListNode *succ)
{
	List* list = succ->handle;
	if(succ==NULL) //empty list
	{
		return List_create(x);
	}

	//modify successor of element before succ:
	ListNode* before = succ->prec;
	before->succ = x;
	succ->prec = x;

	x->handle = list;
	x->succ=succ;
	x->prec=before;

	return list;
}

List* ListPushValue(int value, ListNode *succ)
{
	return ListPush(ListNode_create(value, NULL, NULL, NULL), succ);
}

List* ListPop(ListNode *x)
{
	List* list = x->handle;
	ListNode* before = x->prec;
	ListNode* after = x->succ;
	before->succ = after;
	after->prec = before;

	return list;
}

List* ListReinsert(ListNode* x)
{
	List* list = x->handle;
	(x->prec)->succ = x;
	(x->succ)->prec = x;
	return x;
}

List* ListPopDestroy(ListNode* node)
{
	List* tor = ListPop(node);
	ListNode_destroy(node);
	return tor;
}

bool areEqualLists(List* one, List* two)
{
	if(one->count!=two->count) return false;
	if((one->head)->value!=(two->head)->value) return false;
	ListNode* next1 = (one->head)->succ;
	ListNode* next2 = (two->head)->succ;
	while(next1!=NULL)
	{
		if(next1->value != next2->value) return false;
		next1 = next1->succ;
		next2 = next2->succ;
	}

	return true;
}

void printnode(ListNode* node)
{
	int p = (node->prec)->value;
	int s = (node->succ)->value;
	printf("Value = %d, prec = %d, succ = %d", node->value, p, s);
}

int main(int argc, char** argv)
{
	ListNode* list = ListNode_create(5, NULL, NULL, NULL);
	printnode(list);
	return 0;
}