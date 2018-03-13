// MyHash.h

// Skeleton for the MyHash class template.  You must implement the first seven
// member functions; we have implemented the eighth.

const int DEFAULT_BUCKETS = 100;
template<typename KeyType, typename ValueType>
class MyHash
{
public:
    MyHash(double maxLoadFactor = 0.5);
    ~MyHash();
    void reset();
    void associate(const KeyType& key, const ValueType& value);
    int getNumItems() const;
    double getLoadFactor() const;

      // for a map that can't be modified, return a pointer to const ValueType
    const ValueType* find(const KeyType& key) const;

      // for a modifiable map, return a pointer to modifiable ValueType
    ValueType* find(const KeyType& key)
    {
        return const_cast<ValueType*>(const_cast<const MyHash*>(this)->find(key));
    }
//
      // C++11 syntax for preventing copying and assignment
    MyHash(const MyHash&) = delete;
    MyHash& operator=(const MyHash&) = delete;
    //void printHashTable(); //for testing purposes only, remove once tested fully

private:
    struct Node {
        KeyType key;
        ValueType value;
        Node* next;
    };
    
    
    int m_maxItems;
    int m_size;
    double m_maxLoad;
    int m_nbuckets;
    
    Node** hashTable;
    
    void resize();
    int getSlotNum(const KeyType& key) const;
    void copyNodeInto(Node* p, Node** arr);
};

template<typename KeyType, typename ValueType>
MyHash<KeyType, ValueType>::MyHash(double maxLoadFactor) {
    hashTable = new Node*[DEFAULT_BUCKETS];
    m_nbuckets = DEFAULT_BUCKETS;
    for(int i = 0; i < m_nbuckets; i++) {
        hashTable[i] = nullptr;
    }
    //if negative or 0, set to 0.5, if greater than 2 then set to 2.0
    if(maxLoadFactor <= 0)
        maxLoadFactor = 0.5;
    if(maxLoadFactor > 2)
        maxLoadFactor = 2.0;
    
    
    double c = maxLoadFactor * DEFAULT_BUCKETS; //max items calc
    m_maxItems = c;
    m_size = 0;
    m_maxLoad = maxLoadFactor;
}

template<typename KeyType, typename ValueType>
MyHash<KeyType, ValueType>::~MyHash() {
    for(int i = 0; i < m_nbuckets; i++) {
        Node* head = hashTable[i];
        while(head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    delete [] hashTable;
    m_size = 0;
    m_maxItems = 0;
}

template<typename KeyType, typename ValueType>
void MyHash<KeyType, ValueType>:: reset() {
    //free the current memory
    for(int i = 0; i < m_nbuckets; i++) {
        Node* head = hashTable[i];
        while(head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    m_size = 0;
    
    //allocate another 100 buckets
    hashTable = new Node*[DEFAULT_BUCKETS];
    m_nbuckets = DEFAULT_BUCKETS;
    //max load factor is unchanged
}

template<typename KeyType, typename ValueType>
void MyHash<KeyType, ValueType>:: associate(const KeyType& key, const ValueType& value) {
    
    int slotNum = getSlotNum(key);
    
    //if it is already there, then update it
    //search for the value
    if(hashTable[slotNum] == nullptr) {
        if(m_size+1 > m_maxItems) {
            //resize the array first
            resize();
        }
        Node* p = new Node;
        p->next = nullptr;
        p->key = key;
        p->value = value;
        hashTable[slotNum] = p;
        m_size++;
    }else if(hashTable[slotNum]->key == key) {
        //if the same key, update the value
        hashTable[slotNum]->value = value;
    }else{
        //insert at the end of the bucket
        if(m_size+1 > m_maxItems) {
            //resize the array first
            resize();
        }
        Node* p = hashTable[slotNum];
        while(p->next != nullptr) {
            p = p->next;
        }
        //insert the new stuff
        Node* data = new Node;
        data->next = nullptr;
        data->key = key;
        data->value = value;
        p->next = data;
        m_size++;
    }
}

template<typename KeyType, typename ValueType>
void MyHash<KeyType, ValueType>:: resize() {
    
    //change the number of buckets
    int oldNBuckets = m_nbuckets;
    m_nbuckets *= 2;
    const int newNbuckets = m_nbuckets;
    Node** tempArr = new Node*[newNbuckets];
    for(int i = 0; i < newNbuckets; i++) {
        tempArr[i] = nullptr;
    }
    //change the max items
    m_maxItems = m_maxLoad * m_nbuckets;
    for(int i = 0; i < oldNBuckets; i++) {
        Node* head = hashTable[i];
        while(head != nullptr) {
            Node* tempData = head;
            head = head->next;
            
            copyNodeInto(tempData, tempArr);
            
            delete tempData;
        }
    }
    
    delete [] hashTable;
    
    hashTable = tempArr;
}

template<typename KeyType, typename ValueType>
int MyHash<KeyType, ValueType>:: getSlotNum(const KeyType& key) const{
    unsigned int hash(const KeyType& k);
    unsigned int slotNum = hash(key);
    return slotNum % m_nbuckets;
}

template<typename KeyType, typename ValueType>
void MyHash<KeyType, ValueType>::copyNodeInto(Node* p, Node** arr) {
    int slotNum = getSlotNum(p->key);
    
    //if it is already there, then update it
    //search for the value
    if(arr[slotNum] == nullptr) {
        Node* data = new Node;
        data->next = nullptr;
        data->key = p->key;
        data->value = p->value;
        arr[slotNum] = data;
    }else if(arr[slotNum]->key == p->key) {
        //if the same key, update the value
        arr[slotNum]->value = p->value;
    }else{
        Node* pp = arr[slotNum];
        while(pp->next != nullptr) {
            pp = pp->next;
        }
        //insert the new stuff
        Node* data = new Node;
        data->next = nullptr;
        data->key = p->key;
        data->value = p->value;
        pp->next = data;
    }

}

template<typename KeyType, typename ValueType>
const ValueType* MyHash<KeyType, ValueType>::find(const KeyType& key) const {
    int slotNum = getSlotNum(key);
    if(hashTable[slotNum] == nullptr)
        return nullptr;
    Node* p = hashTable[slotNum];
    while(p!=nullptr) {
        if(p->key == key) {
            return &(p->value);
        }
        p = p->next;
    }
    return &(p->value);
}

template<typename KeyType, typename ValueType>
int MyHash<KeyType, ValueType>::getNumItems() const {
    return m_size;
}

template<typename KeyType, typename ValueType>
double MyHash<KeyType, ValueType>::getLoadFactor() const {
    double buck = m_nbuckets;
    double size = m_size;
    return (size/buck); //current load factor
}


//template<typename KeyType, typename ValueType>
//void MyHash<KeyType, ValueType>::printHashTable() {
//    for(int i = 0; i < m_nbuckets; i++) {
//        Node* p = hashTable[i];
//        std::cout << i << ") ";
//        while(p!= nullptr) {
//            std::cout<< "(Key: " << p->key << ", Value: " << p->value << ")->";
//            
//            p = p->next;
//        }
//        std::cout << "nullptr";
//        std::cout << std::endl;
//    }
//}




