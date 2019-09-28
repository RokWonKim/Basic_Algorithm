#include<stdio.h>
#include<stdlib.h>

typedef struct Linkedlist{
    struct Linkedlist* next;
    int value;
}Linkedlist;

Linkedlist* head;

void insert_at_tail(int value) {
    if(head == NULL) {
	head = (Linkedlist*)malloc(sizeof(Linkedlist));
	head->value = value;
	return;
    }

    Linkedlist* p = head;
    Linkedlist* node = (Linkedlist*)malloc(sizeof(Linkedlist));
    node->value = value;
    while(p->next != NULL)
	p = p->next;
    p->next = node;
}

void insert_at_begin(int value) {
    Linkedlist* node = (Linkedlist*)malloc(sizeof(Linkedlist));
    node->next = head;
    head = node;
}

void insert_at(int begin_value, int tail_value) {
    insert_at_begin(begin_value);
    insert_at_tail(tail_value);
}

void delete_at_begin() {
    if (head->next != NULL) {
        Linkedlist* p = head;
        head = head->next;
	free(p);
    }
    else if (head->next == NULL) {
	head = NULL;
    }
}

void delete_at_tail() {
    if(head == NULL)
	return;
    else {
	Linkedlist* p = head;
	Linkedlist* pre = head;
	while(p->next != NULL) {
	    pre = p;
	    p = p->next;
	}
	pre->next = NULL;
	free(p);
    }
}

void delete_at() {
    delete_at_begin();
    delete_at_tail();
}

int main(void) {

    insert_at_tail(3);
    insert_at_tail(4);
    insert_at_tail(5);
    insert_at_tail(6);
    insert_at_tail(7);
    insert_at_tail(8);
    insert_at_begin(2);
    insert_at(1,9);


    delete_at_begin();
    delete_at_tail();
    delete_at();

    Linkedlist* p = head;

    while(p != NULL) {
	printf("%d ", p->value);
	p = p->next;
    }


    return 0;
}

