#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node {
    int data;
    struct node* next;
};

// This function prints a linked list
void print(struct node* head) {
    struct node* tmp = head;
    printf("{");
    // While this is not the last node
    while(tmp->next) {
        printf("%d, ", tmp->data);
        tmp = tmp->next;
    }
    printf("%d}", tmp->data);
}

struct node* merge(struct node* head1, struct node* head2) {
    struct node* newHead;
    struct node* tmp;
    // If both heads are not null
    if(head1 && head2) {
        // Makes the smallest first element head of return list
        if (head1->data < head2->data) {
            newHead = head1;
            head1 = head1->next;
        } 
        else {
            newHead = head2;
            head2 = head2->next;
        }
    }
    // Returns list with elements if one is null
    else if (head1)
        newHead = head1;
    else if (head2)
        newHead = head2;
    tmp = newHead;
    // While both heads point to items
    while (head1 && head2) {
        // Add smaller first item to return list
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

    // Check for null pointer and size
    if(!head || size <= 1)
        return head;

    // iterate to get pointers at middle of list
    for (i = 1; i < mid; i++)
        tmp = tmp->next;
    tmp2 = tmp->next;
    tmp->next = NULL;

    return merge(mergesort(head, i), mergesort(tmp2, size - i));
}

// iteratively checks if list is sorted, used for testing
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
    // these are used for the merge test
    struct node* head2 = malloc(sizeof(struct node));
    struct node* tail2;
    struct node* tmp;

    // null pointer test
    mergesort(tail, 0);

    tail = head;
    tail2 = head2;
    head->data = 0;
    head2->data = 1;

    // constructing two interleaved lists for merge test
    for(int i = 2; i < 10; i++) {
        tmp = malloc(sizeof(struct node));
        tmp->data = i;
        if(i % 2) {
            tail2->next = tmp;
            tail2 = tmp;
        }
        else {
            tail->next = tmp;
            tail = tmp;
        }
    }

    // test merge
    head = merge(head, head2);
    printf("Merge test: ");
    print(head);
    printf("\n--\n");

    // free merge test list
    while (head->next) {
        tmp = head->next;
        free(head);
        head = tmp;
    }

    tail = head;
    tail->next = NULL;
    tail->data = rand() % 100;

    // single element test
    mergesort(head, 1);

    for(int i = 0; i < 24; i++) {
        tail->next = malloc(sizeof(struct node));
        tail = tail->next;
    }
    // test 10 times with random 25-element lists
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