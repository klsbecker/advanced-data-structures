#include <iostream>
#include <climits>

using namespace std;

struct Node
{
    int data;
    struct Node *next;
}*first = NULL;

void create(int A[], int n)
{
    int i;
    struct Node *t;
    struct Node *last;

    first = (struct Node *)  malloc(sizeof(struct Node));

    first->data = A[0];
    first->next = NULL;
    last = first;

    for (i = 1; i < n; i++) {
        t = (struct Node *) malloc(sizeof(struct Node));
        t->data = A[i];
        t->next = NULL;
        last->next = t; // Não entendi isso aqui não
        last = t;
    }
}

void display(struct Node *p)
{
    while (p != NULL) {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}

void recursiveDisplay(struct Node *p)
{
    if (p != NULL)
    {
        cout << p->data << " ";
        recursiveDisplay(p->next);
    } else {
        cout << endl;
    }
}

int count(struct Node *p)
{
    int length = 0;

    while (p != NULL) {
        length++;
        p = p->next;
    }

    return length;
}

int max(struct Node *p)
{
    int max = INT_MIN;

    while (p != NULL) {
        if (p->data > max) {
            max = p->data;
        }
        p = p->next;
    }

    return max;
}

struct Node *linearSearch(struct Node *p, int key)
{
    while (p != NULL) {
        if (p->data == key) {
            return p;
        }
        p = p->next;
    }

    return NULL;
}

struct Node *insertAtPos(struct Node *p, int position, int val)
{
    struct Node* t;

    if (position < 0 || position > count(p)) {
        return NULL;
    }

    t = (struct Node *)  malloc(sizeof(struct Node));
    t->data = val;

    if (position == 0) {
        t->next = first;
        first = t;
    } else {
        for (int i = 1; i < position; i++) {
            p = p->next;
        }

        t->next = p->next;
        p->next = t;
    }

    return t;
}

void insertSort(struct Node *p, int val)
{
    struct Node *t = (struct Node *) malloc(sizeof(struct Node));
    struct Node *q = NULL;

    t->data = val;
    t->next = NULL;

    if (first == NULL) {
        first = t;
    } else {
        while (p != NULL && p->data < val) {
            q = p;
            p = p->next;
        }

        if (p == first) {
            t->next = first;
            first = t;
        } else {
            t->next = q->next;
            q->next = t;
        }
    }
}

int deleteAt(struct Node *p, int pos)
{
    struct Node *q;
    int val = -1;

    if (pos < 0 || pos > count(p)) {
        return val;
    }

    if (pos == 0) {
        q = first;
        val = first->data;
        first = first->next;
        free(q);
        return val;
    } else {
        for (int i = 1; i < pos; i++) {
            q = p;
            p = p->next;
        }
        q->next = p->next;
        val = p->data;
        free(p);
        return val;
    }
}
int main()
{
    int A[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};
    
    create(A, 11);

    display(first);

    recursiveDisplay(first);

    cout << "List Size: " << count(first) << endl;

    cout << "Max Value: " << max(first) << endl;

    cout << "Key 10 " << (linearSearch(first, 10) ? "is" : "isn't") << " at list" << endl;

    insertAtPos(first, 6, 50);

    cout << "Value 50 inserted at position 6" << endl;

    display(first);

    insertSort(first, 12);

    cout << "Value 12 inserted sorted" << endl;

    display(first);

    cout << "Value " << deleteAt(first, 4) << " deleted from position 4" << endl;

    display(first);

    return 0;
}