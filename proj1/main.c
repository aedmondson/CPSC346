#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node {
    int data;
    struct node* next;
};

void print(struct node* head) {
    struct node* tmp = head;
    printf("{");
    while(tmp->next) {
        printf("%d, ", tmp->data);
        tmp = tmp->next;
    }
    printf("%d}", tmp->data);
}

struct node* merge(struct node* head1, struct node* head2) {
    struct node* newHead;
    struct node* tmp;
    if(head1 && head2) {
        if (head1->data < head2->data) {
            newHead = head1;
            head1 = head1->next;
        } 
        else {
            newHead = head2;
            head2 = head2->next;
        }
    }
    else if (head1)
        newHead = head1;
    else if (head2)
        newHead = head2;
    tmp = newHead;
    // while both heads point to items
    while (head1 && head2) {
        if (head1->data < head2->data) {
            tmp->next = head1;
            tmp = head1;
            head1 = head1->next;
        }
        else {
            tmp->next = head2;
            tmp = head2;
            head2 = head2->next;
        }
    }
    if(head1) 
        tmp->next = head1;
    else if (head2) 
        tmp->next = head2;

    return newHead;
}

struct node* mergesort(struct node* head, int size) {
    struct node* tmp = head;
    struct node* tmp2;
    int i;
    int mid = size / 2;

    if(size <= 1)
        return head;

    for (i = 1; i < mid; i++)
        tmp = tmp->next;

    tmp2 = tmp->next;
    tmp->next = NULL;
    return merge(mergesort(head, i), mergesort(tmp2, size - i));
}

int issorted(struct node* head) {
    struct node* tmp = head;
    while (tmp->next) {
        if (tmp->data > tmp->next->data)
            return 0;
        tmp = tmp->next;
    }
    return 1;
}

int main() {
    struct node* head = malloc(sizeof(struct node));
    struct node* tail;

    tail = head;
    tail->data = rand() % 100;
    for(int i = 0; i < 24; i++) {
        tail->next = malloc(sizeof(struct node));
        tail = tail->next;
    }
    srand(time(NULL));
    for (int i = 0; i < 10; i++) {
        tail = head;
        tail->data = rand() % 100;
        for(int i = 0; i < 24; i++) {
            tail = tail->next;
            tail->data = rand() % 100;
        }
        printf("Original: ");
        print(head);
        head = mergesort(head, 25);
        printf("\nSorted:   ");
        print(head);
        if (!issorted(head))
            printf("\nFAILED");
        printf("\n--\n");
    }

    return 0;
}