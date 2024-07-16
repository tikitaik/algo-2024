# pragma once

# include <iostream>
# include "pair.h"

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
// how to print nodes
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
            //std::cout << "index is beyond bounds of list + 1 (index starts at 0) \n";
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
            //std::cout << "index is beyond bounds of list (index starts at 0) \n";
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

    T* extractFront() { 
        if (this->size() == 0) {
            std::cout << "nothing to extract\n";
            return nullptr;
        }
        else {
            listNode* toReturn = new listNode;
            *toReturn = *this->head;
            this->remove(this->head);
            return toReturn->data;
        }
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
        //std::cout << "priorities: ";
        //std::cout << priorities << '\n';
        int index = 0;
        
        while (priority <= *curP->data) {

            //std::cout << "curP.data = " << *curP->data << '\n';
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

        //std::cout << "index to place at is " << index << " and size of list is " << this->size() << '\n';
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

    T* extractFront() { 
        if (this->size() == 0) {
            std::cout << "nothing to extract\n";
            return nullptr;
        }
        else {
            listNode<T>* toReturn = new listNode<T>;
            *toReturn = *this->head;
            this->remove(this->head);
            priorities.removeAtIndex(0);
            return toReturn->data;
        }
    }
};
/*
template <typename T> class priorityQueue : public queue<T> {
    queue<pair<T, int> > pq;

    int lowerPIndex (int priority) {
        if (pq.size() == 0) {
            return 0;
        }
        listNode<pair<T, int> >* curP = pq.returnHead();
        //std::cout << "priorities: ";
        //std::cout << priorities << '\n';
        int index = 0;
        
        while (priority <= *curP->data->two) {
            //std::cout << "curP.data = " << curP->data << '\n';
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

        //std::cout << "index to place at is " << index << '\n';
        pq.insertAtIndex(index, pair<T, int>(add, priority));
    }

    void enqueue (T add, int priority) {
        T* ptr = new T;
        *ptr = add;
        enqueue(ptr, priority);
    }

    // removes from head
    void dequeue() {
        pq.removeAtIndex(0);
    }
};*/

template <typename K, typename V> class dictionary : private linkedList<pair<K, V> > {

    pair<K, V>* pairSearch(K key) {
        if (this->curSize == 0) {
            return nullptr;
        }

        listNode<pair<K, V> >* walk = this->head;

        while (walk->next) {
            if (*walk->data->one == key) {
                return walk->data;
            }
            walk = walk->next;
        }

        if (*walk->data->one == key) {
            return walk->data;
        }
        else return nullptr;
    }

    pair<K, V>* pairSearch(K* key) {
        return pairSearch(*key);
    }

    bool containsKey(K key) {
        if (pairSearch(key)) {
            return true;
        }
        else {
            return false;
        } 
    }

    bool containsKey(K* key) {
        return containsKey(*key);
    }
    

    public:

    // insert kvp, i want to make key const so that they cant be changed later to not be unique
    void insert(K* key, V* value) {
        // do check for unique ID
        if (containsKey(key)) {
            std::cout << "key already exists in dictionary!\n";
            return;
        }

        this->insertTail(pair<K, V>(key, value));
        //std::cout << "inserted key " << key << "; with value " << value << '\n';
    }

    void insert(K key, V value) {
        //do check for unique ID
        if (containsKey(key)) {
            std::cout << "key already exists in dictionary!\n";
            return;
        }

        this->insertTail(pair<K, V>(key, value));
        //std::cout << "inserted key " << key << "; with value " << value << '\n';
    }
    
    // delete kvp using the key
    void remove (K key) {
        if (!containsKey(key)) {
            std::cout << "no such key exists in dictionary, cannot delete\n";
            return;
        }

        pair<K, V> toPrint = *pairSearch(key);
        this->removeKey(*pairSearch(key));
        std::cout << "removed pair " << toPrint << '\n';
    }

    void remove (K* key) {
        remove(*key);
    }

    V getValue(const K key) {
        if (!containsKey(key)) {
            std::cout << "will segfault cos key dont exist in dictionary\n";
        }
        return *pairSearch(key)->two;
    }

    V getValue(const K* key) {
        return getValue(*key);
    }
    
    template <typename L, typename W> friend std::ostream& operator << (std::ostream& os, const dictionary<L, W> dictionary);
};

// how to print dictionary
template <typename K, typename V> std::ostream& operator << (std::ostream& os, const dictionary<K, V> dictionary) {

    int size = dictionary.curSize;
    if (size == 0) {
            return os << "nothing to display";
        }

    listNode<pair<K, V> >* display = dictionary.head;

    for (int i = 0; i < size - 1; i++) {
        os << *display->data << ", "; 
        display = display->next;
    }
    os << *display->data;
    display = nullptr;

    return os;
}

# include "graph.h"

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
