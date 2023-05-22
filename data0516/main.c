#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode { 	// 노드 타입
	element data;
	struct ListNode* link;
} ListNode;

ListNode* create_node(int value)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = NULL;
	return p;
}
// 오류 처리 함수
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
ListNode* insert_first(ListNode* head, int value)
{
	ListNode* p = create_node(value);
	int count = 0;

	p->link = head;
	head = p;

	// 삽입된 노드까지 이동한 링크 수를 센다.
	for (ListNode* node = head; node != NULL; node = node->link)
	{
		count++;
		if (node == p)
		{
			break;
		}
	}

	printf("move along the link : %d \n", count);
	return head;
}

ListNode* insert_last(ListNode* head, int value)
{
	ListNode* p = create_node(value);
	int count = 0;

	if (head == NULL)
	{
		head = p;
	}
	else
	{
		ListNode* last = head;
		while (last->link != NULL)
		{
			count++;
			last = last->link;
		}
		last->link = p;
	}

	// 삽입된 노드까지 이동한 링크 수를 센다.
	for (ListNode* node = head; node != NULL; node = node->link)
	{
		count++;
		if (node == p)
		{
			break;
		}
	}

	printf("move along the link : %d \n", count);
	return head;
}



// 노드 pre 뒤에 새로운 노드 삽입
ListNode* insert(ListNode* head, ListNode* pre, int value)
{
	ListNode* p = create_node(value);
	int count = 0;

	// pre 다음 노드를 p 다음 노드로 지정한다.
	p->link = pre->link;

	// p를 pre 다음 노드로 지정한다.
	pre->link = p;

	// 새 노드를 추가하는데까지 이동한 링크 수를 센다.
	for (ListNode* node = head; node != NULL; node = node->link)
	{
		count++;
		if (node == pre)
		{
			break;
		}
	}

	printf("move along the link : %d \n", count);
	return head;
}


ListNode* delete_first(ListNode* head)
{
	ListNode* removed;
	if (head == NULL) return NULL;

	removed = head;	// (1)
	head = removed->link;	// (2)
	free(removed);		// (3)

	// 제거된 노드의 갯수를 출력한다.
	int count = 0;
	for (ListNode* node = head; node != NULL; node = node->link)
	{
		count++;
	}

	printf("move along the link : %d \n", count - 1);
	return head;		// (4)
}

// pre가 가리키는 노드의 다음 노드를 삭제한다. 
ListNode* delete(ListNode* head, ListNode* pre, ListNode* cur)
{
	int count = 0;
	ListNode* removed;
	if (pre == NULL)
	{
		removed = head;	// (1)
		head = removed->link;	// (2)
	}
	else
	{
		removed = cur;
		pre->link = cur->link;
	}
	free(removed);		// (3)


	for (ListNode* node = head; node != NULL; node = node->link)
	{
		count++;
		if (node == cur)
		{
			break;
		}
	}

	printf("move along the link : %d \n", count - 1);
	return head;		// (4)
}

void print_list(ListNode* head)
{
	for (ListNode* p = head; p != NULL; p = p->link)
		printf("%d->", p->data);
	printf("NULL \n");
}

// 테스트 프로그램
int main(void)
{
	ListNode* head = NULL;
	int menu;
	while (1)
	{
		int count = 0;
		printf("Menu\n");
		printf("(1) Insert\n(2) Delete\n(3) Print\n(0) Exit\nEnter the Menu : ");
		scanf_s("%d", &menu);
		if (menu == 1)
		{
			int index, value;
			printf("Enter the number and position : ");
			scanf_s("%d %d", &value, &index);

			if (index == 0)
			{
				head = insert_first(head, value);
			}
			else if (head == NULL)
			{
				printf("List is empty. Insert at position 0.\n");
				head = insert_first(head, value);
			}
			else
			{
				ListNode* pre = head;
				int count = 0;

				// 현재 노드 수를 샌다.
				for (ListNode* p = head; p != NULL; p = p->link)
				{
					count++;
				}

				if (index >= count)
				{
					// 가장 마지막 노드의 뒤에 노드를 추가한다.
					printf("Insert at the end of the list\n");
					ListNode* last = head;
					while (last->link != NULL)
					{
						last = last->link;
					}

					last->link = create_node(value);
				}
				else
				{
					// 새 노드를 삽입할 위치(index)까지 원소를 이동한다.
					for (int i = 0; i < index - 1; i++)
					{
						pre = pre->link;
						if (pre == NULL)
						{
							printf("Index is out of range.\n");
							break;
						}
					}

					if (pre != NULL)
					{
						head = insert(head, pre, value);
					}
				}
			}

			printf("Successfully inserted.\n");
		}
		else if (menu == 2)
		{
			if (head == NULL)
			{
				printf("List is empty. Nothing to delete.\n");
				printf("\n========================================\n");
				continue;
			}
			int index;
			printf("Enter the position to delete : ");
			scanf_s("%d", &index);


			if (index == 0)
			{
				head = delete_first(head);
				printf("Successfully deleted.\n");
			}
			else
			{
				ListNode* pre = head;
				ListNode* cur = head;

				// 삭제할 노드(cur)와 그 이전 노드(pre)를 찾는다.
				for (int i = 0; i < index; i++)
				{
					pre = cur;
					cur = cur->link;
					if (cur == NULL)
					{
						printf("Index is out of range.\n");
						break;
					}
				}

				if (cur != NULL)
				{
					head = delete(head, pre, cur);
					printf("Successfully deleted.\n");
				}
			}
		}

		else if (menu == 3)
		{
			print_list(head);
		}
		else if (menu == 0)
		{
			printf("exit the program\n");
			break;
		}
		else {
			printf("Please select again\n");
		}
		printf("\n========================================\n");
	}


	return 0;
}