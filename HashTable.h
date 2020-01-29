//
//  HashTable.h
//  HashTableTree
//
//  Created by Justin Reian Balite Mercado on 10/15/19.
//  Copyright © 2019 Justin Reian Balite Mercado. All rights reserved.
//
#include<string>
#include<unordered_map>
#include "DictTree.h"
using namespace std;

#ifndef HashTable_h
#define HashTable_h

template<class KeyType, class ItemType>
class HashTable
{
public:
    HashTable();
    HashTable(int numBuckets);
    
    void add(KeyType key, ItemType item);
    bool remove(KeyType key);
    ItemType getItem(KeyType key);
    bool contains(KeyType key);
    int size();
    
    void traverse(void visit(ItemType&));
    
private:
    const int DEFAULT_BUCKET_NUM = 20;        // How many buckets by default
    DictTree<KeyType, ItemType>** buckets;
    int numBuckets;
    int numElems;                            // How many elements stored in entire table
    int getHashIndex(const KeyType& key);
};

template<class KeyType, class ItemType>
HashTable<KeyType, ItemType>::HashTable()
{
    buckets = new DictTree<KeyType, ItemType>*[DEFAULT_BUCKET_NUM];
    numBuckets = DEFAULT_BUCKET_NUM;
    numElems = 0;
    for (int i = 0; i <numBuckets; i++){
        buckets[i] = new DictTree<KeyType, ItemType>;
    }
    // for each bucket, set the i-th bucket equal to a new DictTree of type <KeyType, ItemType>
}

template<class KeyType, class ItemType>
HashTable<KeyType, ItemType>::HashTable(int numBucks)
{
    buckets = new DictTree<KeyType, ItemType>*[numBuckets];
    numElems = 0;
}

template<class KeyType, class ItemType>
int HashTable<KeyType, ItemType>::size()
{
    return numElems;
}

template<class KeyType, class ItemType>
void HashTable<KeyType, ItemType>::add(KeyType key, ItemType item)
{
    int i = getHashIndex(key);
    // Get the hash bucket Index
    
    if(!contains(key)){
        numElems+=1;
    }
    // If the hash table does not already contain key
    //    increase numElems by one
    
    buckets[i]->add(key, item);
    // add key,item to the DictTree at a buckets index
}

template<class KeyType, class ItemType>
bool HashTable<KeyType, ItemType>::remove(KeyType key)
{
    // int i = getHashIndex(key);
    // Get the hash Index
    
//    if(contains(key)){
//        numElems-= 1;
//        buckets[i]->remove(key);
//        return true;
//    }
//    else{
//        return false;
//    }
    
    // If the hash table contains the key
    //    decrease numElems by one
    //    remove the key from buckets[b]
    //    return true
    // else
    //    return false
    
    return false;
}

template<class KeyType, class ItemType>
ItemType HashTable<KeyType, ItemType>::getItem(KeyType key)
{
    // Get the hash bucket Index
    int i = getHashIndex(key);
    // return the item by using getItem on the correct bucket index.
    return buckets[i]->lookupItem(key);
    // (HINT:  Should only be 2 line of code at most.  1 is plenty.)
}

template<class KeyType, class ItemType>
bool HashTable<KeyType, ItemType>::contains(KeyType key)
{
    // Get the hash bucket Index
    int i = getHashIndex(key);
    // Use contains on the correct bucket index to return the correct true false.
    return buckets[i]->contains(key);
    // (HINT:  Should only be 2 lines of code at most.  1 is plenty.)
    return false;
}

template<class KeyType, class ItemType>
int HashTable<KeyType, ItemType>::getHashIndex(const KeyType & key)
{
    // This is done... No touching!
    
    // We are creating a hash function type called hashFunction that hashes "KeyType."
    // First we create an an unordered_map object for our KeyType and ItemType
    unordered_map<KeyType, ItemType> mapper;
    
    // Then we call the hash_function method to return the hash function
    // for the KeyType and assign it to 'hashFunction'
    typename unordered_map<KeyType, ItemType>::hasher hashFunction = mapper.hash_function();
    
    // static_cast needed since hashFunction returns an unsigned long
    return static_cast<int>(hashFunction(key) % numBuckets);
}


template<class KeyType, class ItemType>
void HashTable<KeyType, ItemType>::traverse(void visit(ItemType&))
{
    for(int i = 0; i<numBuckets; i++){
        buckets[i]->traverse(visit);
    }
}

#endif /* HashTable_h */
