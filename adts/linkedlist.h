# pragma once

# include <iostream>
# include "pair.h"

// listNode with data that constitutes the linked list
template<typename T> struct listNode {

    listNode* prev;
    listNode* next;
    int id;
    T* data;
    // primitive means data is hard coded and that it is not a pointer
    bool primitive;

    listNode() {
        //this->prev = (listNode*)malloc(sizeof(listNode));
        //this->next = (listNode*)malloc(sizeof(listNode));
    }

    listNode(T* newData) : data(newData) {
        //this->prev = (listNode()*)malloc(sizeof(listNode));
        //this->next = (listNode()*)malloc(sizeof(listNode));

        this->prev = nullptr;
        this->next = nullptr;
        this->primitive = false;
    }

    listNode(T* newData, int id) : data(newData) {
        //this->prev = (listnode*)malloc(sizeof(listnode));
        //this->next = (listnode*)malloc(sizeof(listnode));
        //
        this->prev = nullptr;
        this->next = nullptr;
        this->id = id;
        this->primitive = false;
    }

    listNode(T newData) {
        //this->prev = (listnode*)malloc(sizeof(listnode));
        //this->next = (listnode*)malloc(sizeof(listnode));
        //
        this->prev = nullptr;
        this->next = nullptr;
        this->primitive = true;

        T* ptr = new T;
        *ptr = newData;
        this->data = ptr;
    }

    listNode(T newData, int id) {
        //this->prev = (listnode*)malloc(sizeof(listnode));
        //this->next = (listnode*)malloc(sizeof(listnode));
        this->prev = nullptr;
        this->next = nullptr;
        this->id = id;
        this->primitive = true;

        T* ptr = new T;
        *ptr = newData;
        this->data = ptr;
    }

    ~listNode() {

        this->prev = nullptr;
        this->next = nullptr;

        // if the data is not a pointer delete memory allocated, otherwise just free the pointer
        if (this->primitive && this->data) {
            delete this->data;
        }

        this->data = nullptr;
    }

    listNode (const listNode& other) {
        this->prev = other.prev;
        this->next = other.next;
        this->id = other.id;
        this->data = other.data;
        this->primitive = false;
    }

    listNode& operator = (const listNode& other) {
        this->prev = other.prev;
        this->next = other.next;
        this->id = other.id;
        this->data = other.data;
        this->primitive = false;

        return *this;
    }
};
// how to print nodes
template <typename T> std::ostream& operator << (std::ostream& os, const listNode<T> node) {

    os << "next: " << node.next << ", prev: " << node.prev << ", id: " << node.id << ", data: " << *node.data << '\n';

    return os;
}

// single type doubly linked list
template <typename T> class linkedList {
    typedef listNode<T> listNode;

    protected:
    
    // yuh yuh vars
    listNode* head;
    listNode* tail;

    // current size
    int curSize;

    public:

    // yah yah yah constructor lets goo
    linkedList() {
        curSize = 0;
        this->head = nullptr;
        this->tail = nullptr;
    }

    ~linkedList() {

        this->head = nullptr;
        this->tail = nullptr;

        for (int i = 0; i < curSize; i++) {
            delete this->tail;
        }

    }
    
    void insertHead(T* add);
    void insertHead(T add);
    void insertTail(T* add);
    void insertTail(T* add, int id);
    void insertTail(T add);
    void insertTail(T add, int id);
    void insertAtIndex(int index, T* add);
    void insertAtIndex(int index, T add);

    void remove(listNode* del);
    void removeNode(listNode* node);
    void removeAtIndex(int n);
    void removeKey(T key);
    void removeKey(T* key);
    void removeAllKeys(T key);

    void displayHead() const;
    void displayTail() const;

    listNode* searchKey(const T key) const;
    listNode* searchID(int key) const;

    int getIndex(const T* key) const;
    bool contains(const T key) const;

    listNode* goToIndex(int index) const;
    listNode* returnHead() const;
    listNode* returnTail() const;

    int size() const;
    bool isEmpty() const;
    template <typename U> friend std::ostream& operator << (std::ostream& os, const linkedList<U> list);
};

// add listNode as new head but its pointer so its dynamic
template<typename T> void linkedList<T>::insertHead(T* add) {
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
template<typename T> void linkedList<T>::insertHead(T add) {
    T* ptr = new T;
    *ptr = add;
    insertHead(ptr);
}

// add listNode as new tail
template<typename T> void linkedList<T>::insertTail(T* add) {
    curSize++;
    listNode* newNode = new listNode(add);

    if (tail) {
        tail->next = newNode;
    }
    if (!head) {
        head = newNode;
    }

    newNode->next = nullptr;
    newNode->prev = tail;

    this->tail = newNode;
}

// add listNode as new tail
template<typename T> void linkedList<T>::insertTail(T* add, int id) {
    curSize++;
    listNode* newNode = new listNode(add, id);

    if (tail) {
        tail->next = newNode;
    }
    if (!head) {
        head = newNode;
    }

    newNode->next = nullptr;
    newNode->prev = tail;

    this->tail = newNode;
}

// add listNode as new tail static
template<typename T> void linkedList<T>::insertTail(T add) {
    T* ptr = new T;
    *ptr = add;
    insertTail(ptr);
}

// add listNode as new tail static
template<typename T> void linkedList<T>::insertTail(T add, int id) {
    T* ptr = new T;
    *ptr = add;
    insertTail(ptr, id);
}

// inserts value at index specified
template<typename T> void linkedList<T>::insertAtIndex(int index, T* add) {
    // good on me for making such a robust codebase
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
template<typename T> void linkedList<T>::insertAtIndex(int index, T add) {
    T* ptr = new T;
    *ptr = add;
    insertAtIndex(index, ptr);
}

// thing that reassigns pointers to whats before & after them, if they are not head and/ or tail
// doesnt actually delete the listnode though
template<typename T> void linkedList<T>::remove(listNode* del) {
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

// same as remove key but dont need to put key in
template<typename T> void linkedList<T>::removeNode(listNode* node) {
    if (contains(*node->data)) {
        remove(node);
    }
    else {
        std::cout << "listNode does not exits in this list, cannot remove\n";
    }
}

// deletes listNode at given index
template<typename T> void linkedList<T>::removeAtIndex(int n) {
    if (n > curSize - 1 || n < 0) {
        //std::cout << "index is beyond bounds of list (index starts at 0) \n";
        return;
    }

    remove(goToIndex(n));
    //std::cout << "removed listNode at index " << n << " with value of " << del->data <<"\n";
}

// deletes the first node found in the list with this key, probably why switching the neighbours funcs add order made it better
template<typename T> void linkedList<T>::removeKey(T key) {
    if (searchKey(key)) {
        listNode* del = searchKey(key);
        remove(del);
    }
}

template<typename T> void linkedList<T>::removeKey(T* key) {
    if (searchKey(*key)) {
        listNode* del = searchKey(*key);
        remove(del);
    }
}

// same thing but every node
template<typename T> void linkedList<T>::removeAllKeys(T key) {
    while (searchKey(key)) {
        listNode* del = searchKey(key);
        remove(del);
    }
}

// outputs address and value of the head listNode
template<typename T> void linkedList<T>::displayHead() const {
    std::cout << "head is at " << this->head << " and value of head is " << head->data << "\n";
}

// outputs address and value of the tail listNode
template<typename T> void linkedList<T>::displayTail() const {
    std::cout << "tail is at " << this->tail << " and value of tail is " << tail->data << "\n";
}

// returns mem address of the first listNode found from head with equal key
template<typename T> listNode<T>* linkedList<T>::searchKey(const T key) const {
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

template<typename T> listNode<T>* linkedList<T>::searchID(int key) const {
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
template<typename T> int linkedList<T>::getIndex(const T* key) const {
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
template<typename T> bool linkedList<T>::contains(const T key) const {

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
template<typename T> listNode<T>* linkedList<T>::goToIndex(int index) const {

    listNode* atIndex = this->head;

    for (int i = 0; i < index; i++) {
        atIndex = atIndex->next;
    }
    return atIndex;
}

template<typename T> listNode<T>* linkedList<T>::returnHead() const {
    return this->head;
}

template<typename T> listNode<T>* linkedList<T>::returnTail() const {
    return this->tail;
}

template<typename T> int linkedList<T>::size() const {
    return curSize;
}

template<typename T> bool linkedList<T>::isEmpty() const {
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

template <typename T> class priorityQueue : public queue<pair<T, int> > {

    int lowerPIndex (int priority) {
        //std::cout << "pqsize func " << this->size() << '\n';

        if (this->size() == 0) {
            return 0;
        }

        listNode<pair<T, int> >* curP = this->returnHead();
        int index = 0;
        
        //std::cout << "priority: " << priority << " and curP->data->two: " << *curP->data->two << '\n';
        while ((priority <= *curP->data->two && highPriorityFirst) || (priority >= *curP->data->two && !highPriorityFirst)) {

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

   const bool highPriorityFirst;

    priorityQueue (bool highFirst) : highPriorityFirst(highFirst) {}

    void enqueue (T* add, int priority) {
        int index = lowerPIndex(priority);

        //std::cout << "inserting " << *add << " at index " << index << '\n';
        pair<T, int>* addPair = new pair<T, int>(add, priority);
        //std::cout << *addPair << '\n';
        this->insertAtIndex(index, addPair);
    }

    void enqueue (T add, int priority) {
        T* ptr = new T;
        *ptr = add;
        enqueue(ptr, priority);
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
            listNode<pair<T, int> >* toReturn = new listNode<pair<T, int> >;
            *toReturn = *this->head;
            this->remove(this->head);
            return toReturn->data->one;
        }
    }
};

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
    void remove(K key) {
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
