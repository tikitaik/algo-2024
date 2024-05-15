#pragma once

#include <iostream>

// listNode with data that constitutes the linked list
template<typename T> struct listNode {
    listNode* prev;
    listNode* next;
    int id;
    T* data;

    listNode() {
        this->prev = (listNode*)malloc(sizeof(listNode));
        this->next = (listNode*)malloc(sizeof(listNode));
    }

    listNode (T* newData) : data(newData) {
        this->prev = (listNode*)malloc(sizeof(listNode));
        this->next = (listNode*)malloc(sizeof(listNode));
    }

    listNode (T* newData, int id) : data(newData) {
        this->prev = (listNode*)malloc(sizeof(listNode));
        this->next = (listNode*)malloc(sizeof(listNode));
        this->id = id;
    }
};
// how to print linkedlists
template <typename T> std::ostream& operator << (std::ostream& os, const listNode<T> node) {

    os << "next: " << node.next << ", prev: " << node.prev << ", id: " << node.id << ", data: " << *node.data << '\n';

    return os;
}

// single type doubly linked list
template <typename T> class linkedList {
    protected:
    
    // typedef to write easier
    typedef listNode<T> listNode;

    // yuh yuh vars
    listNode* head;
    listNode* tail;
    // current size
    int curSize;

    // thing that reassigns pointers to whats before & after them, if they are not head and/ or tail
    // doesnt actually delete the listnode though
    void remove(listNode* del) {
        if (del == head && del == tail) {
            head = nullptr;
            tail = nullptr;
        }
        else if (del == head) {
            del->next->prev = nullptr;
            head = del->next;
        }
        else if (del == tail) {
            del->prev->next = nullptr;
            tail = del->prev;
        }
        else {
            del->prev->next = del->next;
            del->next->prev = del->prev;
        }
        delete del;
        curSize--;
    }

    public:

    // yah yah yah constructor lets goo
    linkedList() {
        curSize = 0;
        this->head = nullptr;
        this->tail = nullptr;
    }

    // add listNode as new head but its pointer so its dynamic
    void insertHead(T* add) {
        curSize++;
        listNode* newNode = new listNode(add);

        if (head) {
            head->prev = newNode;
        }

        if (!tail) {
            tail = newNode;
        }

        newNode->next = head;
        newNode->prev = nullptr;

        this->head = newNode;
    }

    // add static var as head
    void insertHead(T add) {
        T* ptr = new T;
        *ptr = add;
        insertHead(ptr);
    }

    // add listNode as new tail
    void insertTail(T* add) {
        curSize++;
        listNode* newNode = new listNode(add);

        if (tail) {
            tail->next = newNode;
        }
        if (head == nullptr) {
            head = newNode;
        }

        newNode->next = nullptr;
        newNode->prev = tail;

        this->tail = newNode;
    }

    // add listNode as new tail
    void insertTail(T* add, int id) {
        curSize++;
        listNode* newNode = new listNode(add, id);

        if (tail) {
            tail->next = newNode;
        }
        if (head == nullptr) {
            head = newNode;
        }

        newNode->next = nullptr;
        newNode->prev = tail;

        this->tail = newNode;
    }

    // add listNode as new tail static
    void insertTail(T add) {
        T* ptr = new T;
        *ptr = add;
        insertTail(ptr);
    }

    // add listNode as new tail static
    void insertTail(T add, int id) {
        T* ptr = new T;
        *ptr = add;
        insertTail(ptr, id);
    }

    // inserts value at index specified
    void insertAtIndex(int index, T* add) {
        // good on me for making such a robust program
        if ((curSize != 0 && index > curSize) || index < 0) {
            std::cout << "index is beyond bounds of list + 1 (index starts at 0) \n";
            return;
        }

        if (curSize == 0) {
            insertHead(add);
            return;
        }

        listNode* newNode = new listNode(add);
        listNode* indexNode = this->head;
        // traverse list to index
        for (int i = 0; i < index; i++) {
            indexNode = indexNode->next;
        }

        // cant insert element at tail as that is outside the bounds of the array
        if (index == 0) { 
            insertHead(add); 
        }
        else if (index == curSize) {
            insertTail(add);
        }
        else {
            newNode->next = indexNode;
            newNode->prev = indexNode->prev;
            indexNode->prev->next = newNode;
            indexNode->prev = newNode;
            curSize++;
        }
    }

    // inserts value at index specified when value is static
    void insertAtIndex(int index, T add) {
        T* ptr = new T;
        *ptr = add;
        insertAtIndex(index, ptr);
    }
    
    // same as remove key but dont need to put key in
    void removeNode(listNode* node) {
        if (contains(*node->data)) {
            remove(node);
        }
        else {
            std::cout << "listNode does not exits in this list, cannot remove\n";
        }
    }
    
    // deletes listNode at given index
    void removeAtIndex(int n) {
        if (n > curSize - 1 || n < 0) {
            std::cout << "index is beyond bounds of list (index starts at 0) \n";
            return;
        }

        remove(goToIndex(n));
        //std::cout << "removed listNode at index " << n << " with value of " << del->data <<"\n";
    }

    // deletes the first node found in the list with this key, probably why switching the neighbours funcs add order made it better
    void removeKey(T key) {
        if (searchKey(key)) {
            listNode* del = searchKey(key);
            remove(del);
        }
    }

    void removeKey(T* key) {
        if (searchKey(*key)) {
            listNode* del = searchKey(*key);
            remove(del);
        }
    }

    // same thing but every node
    void removeAllKeys(T key) {
        while (searchKey(key)) {
            listNode* del = searchKey(key);
            remove(del);
        }
    }
    // outputs address and value of the head listNode
    void displayHead() {
        std::cout << "head is at " << this->head << " and value of head is " << head->data << "\n";
    }
    // outputs address and value of the tail listNode
    void displayTail() {
        std::cout << "tail is at " << this->tail << " and value of tail is " << tail->data << "\n";
    }

    // returns mem address of the first listNode found from head with equal key
    listNode* searchKey(const T key) {
        listNode* searchKey = this->head;

        for (int i = 0; i < curSize; i++) {
            if (*searchKey->data == key) {
                return searchKey;
            }
            else {
                searchKey = searchKey->next;
            }
        }
        return nullptr;
    }

    listNode* searchID(int key) {
        listNode* searchKey = this->head;

        for (int i = 0; i < curSize; i++) {
            if (searchKey->id == key) {
                return searchKey;
            }
            else {
                searchKey = searchKey->next;
            }
        }
        return nullptr;
    }
    // returns index of first listnode found with equivalent key
    int getIndex(const T* key) {
        listNode* searchKey = this->head;

        for (int i = 0; i < curSize; i++) {
            if (*searchKey->data == *key) {
                return i;
            }
            else {
                searchKey = searchKey->next;
            }
        }
        return -1;
    }
    // does this list contain a node w this key
    bool contains(const T key) {
        listNode* searchKey = this->head;

        for (int i = 0; i < curSize; i++) {
            if (*searchKey->data == key) {
                //std::cout << "contains return true\n";
                return true;
            }
            else if (searchKey->next) {
                searchKey = searchKey->next;
            }
        }
        //std::cout << "contains return false\n";
        return false;
    }

    // returns pointer to listNode at passed index
    listNode* goToIndex(int index) {

        listNode* atIndex = this->head;

        for (int i = 0; i < index; i++) {
            atIndex = atIndex->next;
        }
        return atIndex;
    }

    listNode* returnHead() {
        return this->head;
    }

    listNode* returnTail() {
        return this->tail;
    }

    int size() const {
        return curSize;
    }

    bool isEmpty() {
        if (curSize == 0) {
            return true;
        }
        else if (curSize < 0) {
            std::cout << "size is < 0 \n";
            return true;
        }
        else {
            return false;
        }
    }

    template <typename U> friend std::ostream& operator << (std::ostream& os, const linkedList<U> list);
};

// how to print linkedlists
template <typename T> std::ostream& operator << (std::ostream& os, const linkedList<T> list) {

    if (list.curSize == 0) {
            return os << "nothing to display";
        }

    listNode<T>* display = list.head;

    for (int i = 0; i < list.curSize - 1; i++) {
        os << *display->data << ", "; 
        display = display->next;
    }
    os << *display->data;
    display = nullptr;

    return os;
}

template <typename T> class stack : public linkedList<T> {
    protected:
    // listNode from linked list is the saem as listNode here
    typedef listNode<T> listNode;
    public:     

    void push (T* add) {
        this->insertTail(add);
    }

    void push (T add) {
        this->insertTail(add);
    }

    // removes and returns from tail
    listNode* pop() {
        if (this->size() == 0) {
            std::cout << "nothing to pop, returning \n";
            return nullptr;
        }
        else {
            listNode* toReturn = new listNode;
            *toReturn = *this->tail;
            this->remove(this->tail);
            return toReturn;
        }
    }

    listNode* top() {
        if (this->size() == 0) {
            //std::cout << "stack size is 0, nothing to return \n";
            return nullptr;
        }
        return this->tail;
    }
};

template <typename T> class queue : public linkedList<T> {
    protected:
    // listNode from linked list is the same as listNode here
    typedef listNode<T> listNode;
    public:     

    void enqueue (T* add) {
        this->insertTail(add);
    }

    void enqueue (T add) {
        enqueue(add);
    }

    // removes from head
    void dequeue() {
        this->removeAtIndex(0);
    }

    // returns address to front listNode
    listNode* peek() {
        return this->head;
    }

    void removeFront() {
        this->remove(this->head);
    }
};

template <typename T> class priorityQueue : public queue<T> {
    linkedList<int> priorities;

    int lowerPIndex (int priority) {
        if (priorities.size() == 0) {
            return 0;
        }
        listNode<int>* curP = priorities.returnHead();
        std::cout << "priorities: ";
        std::cout << priorities << '\n';
        int index = 0;
        
        while (priority <= *curP->data) {
            std::cout << "curP.data = " << curP->data << '\n';
            index++;
            if (curP->next) {
                curP = curP->next;
            }
            else {
                return index;
            }   
        }
        return index;
    }

    public:

    void enqueue (T* add, int priority) {
        int index = lowerPIndex(priority);
        int* priorityPointer = new int;
        *priorityPointer = priority;

        std::cout << "index to place at is " << index << '\n';
        this->insertAtIndex(index, add);
        priorities.insertAtIndex(index, *priorityPointer);
    }

    void enqueue (T add, int priority) {
        T* ptr = new T;
        *ptr = add;
        enqueue(ptr, priority);
    }

    // removes from head
    void dequeue() {
        this->removeAtIndex(0);
        priorities.removeAtIndex(0);
    }
};

template <typename K, typename V> class dictionary : linkedList<K>, linkedList<V> {
    linkedList<K> keys;
    linkedList<V> values;

    public:

    // insert kvp, i want to make key const so that they cant be changed later to not be unique
    void insert(K* key, V* value) {
        // do check for unique ID
        if (keys.contains(key)) {
            std::cout << "key already exists in dictionary!\n";
            return;
        }

        keys.insertTail(key);
        values.insertTail(value);
        //std::cout << "inserted key " << key << "; with value " << value << '\n';
    }

    // delete kvp using the key
    void remove (K* key) {
        if (!keys.contains(key)) {
            std::cout << "no such key exists in dictionary, cannot delete\n";
            return;
        }

        int index = keys.getIndex(key);
        K keyPrint = keys.goToIndex(index)->data;
        V valuePrint = values.goToIndex(index)->data;
        keys.removeAtIndex(index);
        values.removeAtIndex(index);
        std::cout << "removed value " << valuePrint << " and key " << keyPrint << " from dictionary\n";
    }

    V& getValue(const K* key) {
        int index = keys.getIndex(key);
        return values.goToIndex(index)->data;
    }

    void display() {
        if (keys.size() == 0) {
            std::cout << "nothing to display \n";
            return;
        }

        std::cout << "displaying list in [key, value] format:\n";

        listNode<K>* keyDisplay = keys.returnHead();
        listNode<V>* valueDisplay = values.returnHead();

        for (int i = 0; i < keys.size() - 1; i++) {
            std::cout << "[" << keyDisplay->data << "; " << valueDisplay->data << "], "; 
            keyDisplay = keyDisplay->next;
            valueDisplay = valueDisplay->next;
        }
        std::cout << "[" << keyDisplay->data << "; " << valueDisplay->data << "]\n"; 
    }
};

#include "adts/graph.h"
template<typename T> bool operator == (const node<T> n1, const node<T> n2) {
    return n1.id == n2.id;
}

bool operator == (const edge e1, const edge e2) {
    if (e1.start == e2.start && e1.end == e2.end && e1.weight == e2.weight) {
        return true;
    }
    else {
        return false;
    }
}
