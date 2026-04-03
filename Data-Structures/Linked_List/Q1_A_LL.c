//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;
// struct _listnode 안에는 정수 데이터를 저장하는 item과
// 다음 노드를 가리키는 포인터 next가 있다.
// 자기 자신과 같은 구조체를 가리키는 포인터를 멤버로 가질 수 있다.

typedef struct _linkedlist
{
	int size; // 연결 리스트에 들어 있는 노드의 개수
	ListNode *head;
} LinkedList;
// Linkedlist 구조체
// int 형 변수 size 가 있고, _listnode 구조체 포인터 변수 head 가 존재한다.

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototype of this function
int insertSortedLL(LinkedList *ll, int item);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;

	// Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	printf("1: Insert an integer to the sorted linked list:\n");
	printf("2: Print the index of the most recent input value:\n");
	printf("3: Print sorted linked list:\n");
	printf("0: Quit:");

	while (c != 0)
	{
		printf("\nPlease input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertSortedLL(&ll, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			printf("The value %d was added at index %d\n", i, j);
			break;
		case 3:
			printf("The resulting sorted linked list is: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

int insertSortedLL(LinkedList *ll, int item)
{
	// 가장 먼저 해야 할 게 뭘까?
	// ll이 정렬되어 있으므로 head부터 next로 노드들을 탐색하면서, item과 해당 ll의 item과
	// 크기를 비교한다.

	// 만약 ll-> item < item < ll -> next -> item 이면 그 자리에 넣는다.
	// 같으면 삽입 X

	// ll의 head부터 검사한다.
	// 만약 head 가 Null 이면 그 자리에 삽입
	ListNode *newNode = malloc(sizeof(ListNode));
	newNode->item = item;
	newNode->next = NULL;

	// newNode라는 node 구조체 생성(malloc)
	// 여기서 동적으로 메모리를 할당 하는 이유
	// ll 에 들어가는 노드들은  insertSortedLL() 함수가 끝나도 남아있어야한다.
	// ListNode *newNode;
	// 이런식으로 선언하면 지역변수라 함수가 끝나는 순간 사라진다.
	// 반면에 malloc() 으로 만든 메모리는 free() 가 호출되기 전까지 유지된다.

	if (ll->head == NULL)
	{
		ll->head = newNode;
		ll->size++;
		return 0;
	}

	if (ll == NULL || item == ll->head->item)
		return -1;
	// head item 보다 newnode의 item 이 작은 경우에는 맨 앞에 넣어야한다.
	if (item < ll->head->item)
	{
		newNode->next = ll->head;
		ll->head = newNode;
		ll->size++;
		return 0;
	}

	// ll이 빈 연결리스트 일때 삽입은 해결 했다.
	// 다음은 연결리스트를 탐색하면서
	// 현재 보고 있는 연결리스트의 노드의 item과 대소비교를 해줘야한다.
	// 현재 보고 있는 연결리스트의 노드? 어떻게 접근할까
	ListNode *prev = ll->head;
	ListNode *cur = ll->head->next;

	// 연결리스트의 head를 cur 노드라고 한다.
	// cur을 이동시키면서 탐색한다. next가 NULL 이 아닐때까지
	int index = 1;

	while (cur != NULL)
	{
		if (cur->item == item)
			return -1;

		if (item < cur->item)
		{
			newNode->next = prev->next;
			prev->next = newNode;
			ll->size++;
			return index;
		}
		cur = cur->next;
		prev = prev->next;
		index += 1;
	}

	prev->next = newNode;
	ll->size++;
	return index;
}

///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll)
{

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}

void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL)
	{
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}

ListNode *findNode(LinkedList *ll, int index)
{

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0)
	{
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value)
{

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0)
	{
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}

	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL)
	{
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}

int removeNode(LinkedList *ll, int index)
{

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0)
	{
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL)
	{

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}
