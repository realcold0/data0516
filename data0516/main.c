#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode { 	// ��� Ÿ��
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
// ���� ó�� �Լ�
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

	// ���Ե� ������ �̵��� ��ũ ���� ����.
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

	// ���Ե� ������ �̵��� ��ũ ���� ����.
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



// ��� pre �ڿ� ���ο� ��� ����
ListNode* insert(ListNode* head, ListNode* pre, int value)
{
	ListNode* p = create_node(value);
	int count = 0;

	// pre ���� ��带 p ���� ���� �����Ѵ�.
	p->link = pre->link;

	// p�� pre ���� ���� �����Ѵ�.
	pre->link = p;

	// �� ��带 �߰��ϴµ����� �̵��� ��ũ ���� ����.
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

	// ���ŵ� ����� ������ ����Ѵ�.
	int count = 0;
	for (ListNode* node = head; node != NULL; node = node->link)
	{
		count++;
	}

	printf("move along the link : %d \n", count - 1);
	return head;		// (4)
}

// pre�� ����Ű�� ����� ���� ��带 �����Ѵ�. 
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

// �׽�Ʈ ���α׷�
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

				// ���� ��� ���� ����.
				for (ListNode* p = head; p != NULL; p = p->link)
				{
					count++;
				}

				if (index >= count)
				{
					// ���� ������ ����� �ڿ� ��带 �߰��Ѵ�.
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
					// �� ��带 ������ ��ġ(index)���� ���Ҹ� �̵��Ѵ�.
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

				// ������ ���(cur)�� �� ���� ���(pre)�� ã�´�.
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