#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode { 	// ��� Ÿ��
	element data;
	struct ListNode* link;
} ListNode;

// ���� ó�� �Լ�
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
ListNode* insert_first(ListNode* head, int value)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));	//(1)
	p->data = value;					// (2)
	p->link = head;	// ��� �������� ���� ����	//(3)
	head = p;	// ��� ������ ����		//(4)
	return head;	// ����� ��� ������ ��ȯ
}

// ��� pre �ڿ� ���ο� ��� ����
ListNode* insert(ListNode* head, ListNode* pre, element value)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));	//(1)
	p->data = value;		//(2)
	p->link = pre->link;	//(3)	
	pre->link = p;		//(4)	
	return head;		//(5)	
}

ListNode* delete_first(ListNode* head)
{
	ListNode* removed;
	if (head == NULL) return NULL;
	removed = head;	// (1)
	head = removed->link;	// (2)
	free(removed);		// (3)
	return head;		// (4)
}
// pre�� ����Ű�� ����� ���� ��带 �����Ѵ�. 
ListNode* delete(ListNode* head, ListNode* pre)
{
	ListNode* removed;
	removed = pre->link;
	pre->link = removed->link;		// (2)
	free(removed);			// (3)
	return head;			// (4)
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
			int index;
			int num;

			printf("Enter the number and position : ");
			scanf_s("%d %d", &num, &index);
			
			if (index == 0)
			{
				insert_first(head, num);
			}
			else {
				index -= 1;

				ListNode* p = head;

				while (count != index && p  != NULL)
				{
					p = p->link;
					count++;
				}
				if (p  == NULL)
				{
					insert(head, p->link, num);
					continue;
				}
				insert(head, p->link, num);
			}
		}
		else if (menu == 2)
		{
			int index;
			printf("Enter the position : ");
			scanf_s(" %d", &index);
			
			if (index == 0)
			{
				delete_first(head);
			}
			else {

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