#include <iostream>
#include <climits>

using namespace std;

class Node {
public:
    int data;
    Node *next;
    Node *prev;
};

class DoubleLinkedList {
private:
    Node *head;
    Node *tail;
public:
    DoubleLinkedList() {head = NULL; tail = NULL;}
    DoubleLinkedList(int A[], int size);
    ~DoubleLinkedList();

    void display();
    void reverseDisplay();
    void insertAt(int pos, int val);
    int deleteAt(int pos);
    int length();
    int min();
    int max();
    long sum(); 
};

DoubleLinkedList::DoubleLinkedList(int A[], int size)
{
    Node *temp;

    head = new Node;
    head->data = A[0];
    head->next = NULL;
    head->prev = NULL;

    tail = head;

    for (int i = 1; i < size; i++) {
        temp = new Node;
        temp->data = A[i];
        temp->next = NULL;
        temp->prev = tail;
        tail->next = temp;
        tail = temp;
    }
}

DoubleLinkedList::~DoubleLinkedList()
{
    Node *p = head;
    while (p != NULL) {
        head = head->next;
        delete p;
        p = head;
    }
    head = tail = NULL;
}

void DoubleLinkedList::display()
{
    Node *p = head;
    while (p != NULL) {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}

void DoubleLinkedList::reverseDisplay()
{
    Node *p = tail;

    while (p != NULL) {
        cout << p->data << " ";
        p = p->prev;
    }
    cout << endl;
}

int DoubleLinkedList::length()
{
    Node *p = head;
    int length = 0;
    while (p != NULL) {
        length++;
        p = p->next;
    }
    return length;
}

void DoubleLinkedList::insertAt(int pos, int val)
{
    Node *temp = NULL;
    Node *p = head;

    if (pos < 0 || pos > length()) {
        return;
    }

    temp = new Node;
    temp->data = val;
    temp->next = NULL;
    temp->prev = NULL;

    if (pos == 0) {
        head->prev = temp;
        temp->next = head;
        head = temp;
    } else if (pos == length()) {
        tail->next = temp;
        temp->prev = tail;
        tail = temp;
    } else {
        for (int i = 0; i < pos - 1; i++) {
            p = p->next;
        }
        p->next->prev = temp;
        temp->prev = p;
        temp->next = p->next;
        p->next = temp;
    }
}

int DoubleLinkedList::deleteAt(int pos)
{
    Node *p = head;
    int val = -1;

    if (pos < 0 || pos > length() - 1)
        return val;

    if (pos == 0) {
        head = head->next;
        head->prev = NULL;
        val = p->data;
    } else if (pos == length() - 1) {
        p = tail;
        tail = tail->prev;
        tail->next = NULL;
    } else {
        for (int i = 0; i < pos; i++) {
            p = p->next;
        }
        p->prev->next = p->next;
        p->next->prev = p->prev;
    }

    val = p->data;
    delete p;

    return val;
}

int DoubleLinkedList::min()
{
    Node *p = head;
    int min = INT_MAX;

    while (p != NULL) {
        if (p->data < min) {
            min = p->data;
        }
        p = p->next;
    }

    return min;
}

int DoubleLinkedList::max()
{
    Node *p = head;
    int max = INT_MIN;

    while (p != NULL) {
        if (p->data > max) {
            max = p->data;
        }
        p = p->next;
    }

    return max;
}

long DoubleLinkedList::sum()
{
    Node *p = head;
    long sum = 0;

    while (p != NULL) {
        sum += p->data;
        p = p->next;
    }

    return sum;   
}

int main()
{
    int A[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};
    
    DoubleLinkedList list(A, 11);

    cout << "Double Linked List - Klaus Becker" << endl << endl;

    cout << "Original List: "; list.display(); cout << endl;

    cout << "List Size: " << list.length() << endl << endl;

    list.insertAt(6, 50);

    cout << "Value 50 inserted at position 6" << endl;

    cout << "New List: "; list.display(); cout << endl;

    cout << "Value " << list.deleteAt(4) << " deleted from position 4" << endl;

    cout << "New List: "; list.display(); cout << endl;

    cout << "Min Value: " << list.min() << endl << endl;

    cout << "Max Value: " << list.max() << endl << endl;

    cout << "Sum Value: " << list.sum() << endl << endl;

    cout << "Reverse display: "; list.reverseDisplay(); cout << endl;

    return 0;
}