#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct ListNode {

	int coef;
	int expo;
	struct ListNode* link;
}ListNode;

typedef struct ListType {
	int size;
	ListNode* head, * Tail;

}ListType;

ListType* create() {
	ListType* plist = (ListType*)malloc(sizeof(ListType));
	plist->size = 0;
	plist->head = NULL;
	plist->Tail = NULL;

	return plist;

}
void error(char* message) {
	fprintf(stderr, "%s\n", message);
	return;
}

void insert_last(ListType* plist, int coef, int expo) {
	ListNode* temp = (ListNode*)malloc(sizeof(ListNode));
	if (temp == NULL) {
		error("비었습니다.");

	}
	temp->coef = coef;
	temp->expo = expo;
	temp->link = NULL;
	if (plist->Tail == NULL) {
		plist->head = plist->Tail = temp;
	}
	else {
		plist->Tail->link = temp;
		plist->Tail = temp;

	}
	plist->size++;
}

void poly_add(ListType* plist, ListType* plist2, ListNode* plist3) {
	ListNode* a = plist->head;
	ListNode* b = plist2->head;
	int sum;
	while (a != NULL && b != NULL) {
		if (a->expo == b->expo) {
			sum = a->coef + b->coef;
			if (sum != 0) {
				insert_last(plist3, sum, a->expo);
				a = a->link;
				b = b->link;
			}
		}
		else if (a->expo > b->expo) {
			insert_last(plist3, a->coef, a->expo);
			a = a->link;
		}
		else {
			insert_last(plist3, b->coef, b->expo);
			b = b->link;
		}

	}
	for (; a != NULL; a = a->link) {
		insert_last(plist3, a->coef, a->expo);

	}
	for (; b != NULL; b = b->link) {
		insert_last(plist3, b->coef, b->expo);

	}
}
void inputing(ListType* plist, int deg) {

	for (int i = 0; i < deg; i++) {
		int coef, expo;
		printf("%d 번째 항의 지수와 계수를 차례로 입력하시오: ",(i+1));
		scanf_s("%d %d", &coef, &expo);
		insert_last(plist, coef, expo);

	}
	
}

void print_list(ListType* poly) {
	printf("List: ");
	ListType* p = (ListType*)malloc(sizeof(ListType));
	ListNode* n = (ListNode*)malloc(sizeof(ListNode));
	n = poly->head;
	if (n->coef >= 0) {

		printf("%dx%d", n->coef,n->expo);
	}
	else {
		printf("%dx%d", n->coef,n->expo);
	}
	n = n->link;

	for (n = poly->head->link; n != NULL; n = n->link) {//head 의 data 말고 head가 가리키는 곳의 data를 넣어야함
		if (n->coef >= 0) {
			
			printf("+%dx%d", n->coef, n->expo);
		}
		else {
			printf("%dx%d", n->coef, n->expo);
		}



	}
	printf("\n");
}
void main() {
	ListType* plist1, * plist2, * plist3;
	plist1 = create();
	plist2 = create();
	plist3 = create();
	int deg;
	printf("첫번째 다항식의 최대항 수: ");
	scanf_s("%d", &deg);

	inputing(plist1, deg);

	printf("두번째 다항식의 최대항 수: ");
	scanf_s("%d", &deg);

	inputing(plist2, deg);
	poly_add(plist1, plist2, plist3);
	print_list(plist3);

}