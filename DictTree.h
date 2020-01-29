//
//  DictTree.h
//  HashTableTree
//
//  Created by Justin Reian Balite Mercado on 10/15/19.
//  Copyright © 2019 Justin Reian Balite Mercado. All rights reserved.
//

#ifndef DictTree_h
#define DictTree_h

#include <iostream>
using namespace std;

template <class KeyType, class ItemType>
struct NodeT
{
    KeyType key;
    ItemType data;
    NodeT * left;
    NodeT * right;
};

template <class KeyType, class ItemType>
class DictTree
{
public:
    DictTree(); //constructor
    ~DictTree(); //deconstructor
    void add(KeyType newKey, ItemType newItem); //wrapper to call addpriv()
    int size(); //returns total number of nodes in BST
    bool contains(KeyType key); //wrapper to call containedInSubtree()
    void traverse(void visit(ItemType&)) const;
    bool remove(KeyType newKeys);
    ItemType lookupItem(KeyType key);
private:
    // Variables
    int numNodes;
    NodeT<KeyType, ItemType> * root;
    
    //Functions
    void addpriv(KeyType newKey, ItemType newItem, NodeT<KeyType, ItemType> * ptr); //inserts key and data value to BST
    NodeT<KeyType, ItemType>* containedInSubtree(NodeT<KeyType, ItemType>* subTree, KeyType key); //checks if a key is present in BST, if so return address of that node
    void preorder(void visit(ItemType&), NodeT<KeyType, ItemType>* treePtr) const; //traverses left tree, prints, traverses right tree, prints
    NodeT<KeyType, ItemType> * removeFromSubtree(NodeT<KeyType, ItemType>* subTree, KeyType key, bool& success);
    NodeT<KeyType, ItemType> * FindSmallest(NodeT<KeyType, ItemType>* ptr);
    void Destroy(NodeT<KeyType, ItemType>* node);
};

// DictTree() constructor
template <class KeyType, class ItemType>
DictTree<KeyType, ItemType>::DictTree()
{
//    cout << "root is now equal to nullptr";
    root = nullptr; // Set up the root and the initial number of nodes to 0
//    cout << "done";
    numNodes = 0;
}

// ~DictTree() deconstructor
template <class KeyType, class ItemType>
DictTree<KeyType, ItemType>::~DictTree(){
    Destroy(root);
}

template <class KeyType, class ItemType>
void DictTree<KeyType, ItemType>::Destroy(NodeT<KeyType, ItemType>* node)
{
    if (node == nullptr)
        return;
    
    Destroy(node->left);
    Destroy(node->right);
    delete node;
    cout << "Deleting" << endl;
}
template <class KeyType, class ItemType>
void DictTree<KeyType, ItemType>::add(KeyType newKey, ItemType newItem){
    addpriv(newKey, newItem, root);
}

template <class KeyType, class ItemType>
void DictTree<KeyType, ItemType>::addpriv(KeyType newKey, ItemType newItem, NodeT<KeyType, ItemType> * ptr){
    if (root==nullptr){ //empty tree
//        cout << "I need to make a node, the dict is empty!" << endl;
        NodeT<KeyType, ItemType> * newNode = new NodeT<KeyType, ItemType>;
        newNode->data = newItem;
        newNode->key = newKey;
        newNode->left = nullptr;
        newNode->right = nullptr;
        root = newNode;
        numNodes = 1;
//        cout << "I made a node! " << "number is at " << numNodes << endl;
//        cout << endl;
    }
    else if (newKey < ptr->key){
        if(ptr->left == nullptr){
//            cout << "I need to make a left node" << endl;
            NodeT<KeyType, ItemType> * newNode = new NodeT<KeyType, ItemType>;
            newNode->data = newItem;
            newNode->key = newKey;
            newNode->left = nullptr;
            newNode->right = nullptr;
            ptr->left = newNode;
            numNodes += 1;
//            cout << "I made a left node! " << endl;
//            cout << endl;
        }
        else{
//            cout << "ohp theres already a left node, cant create yet, gotta check this one" << endl;
            addpriv(newKey, newItem, ptr->left);
        }
    }
    else if (newKey > ptr->key){
        if(ptr->right == nullptr){
//            cout << "I need to make a right node" << endl;
            NodeT<KeyType, ItemType> * newNode = new NodeT<KeyType, ItemType>;
            newNode->data = newItem;
            newNode->key = newKey;
            newNode->left = nullptr;
            newNode->right = nullptr;
            ptr->right = newNode;
            numNodes += 1;
//            cout << "I made a right node! " << endl;
//            cout << endl;
        }
        else{
//            cout << "ohp theres already a right node, cant create yet, gotta check this one" << endl;
            addpriv(newKey, newItem, ptr->right);
        }
    }
}


template <class KeyType, class ItemType>
int DictTree<KeyType, ItemType>::size()
{
    // This method is completed.
    return numNodes;
}

template<class KeyType, class ItemType>
void DictTree<KeyType, ItemType>::traverse(void visit(ItemType&)) const
{
    // This method is completed.
    preorder(visit, root);
}

template<class KeyType, class ItemType>
void DictTree<KeyType, ItemType>::preorder(void visit(ItemType&), NodeT<KeyType, ItemType>* treePtr) const
{
    //treePtr
    if (treePtr==nullptr){
        return;
    }
    cout << treePtr->data << " ";
    preorder(visit, treePtr->left);
    preorder(visit, treePtr->right);
    
}

template <class KeyType, class ItemType>
bool DictTree<KeyType, ItemType>::contains(KeyType key)
{
    if (containedInSubtree(root, key) != nullptr){     // Use containedInSubtree to see if a node with the "key" is null.
        cout << "Found key " << key << " in tree. Cannot add!" << endl;
        return true;
    }
    else{
        cout << "Could not find key " << key << " in tree. Good to add!" << endl;
        return false;
    }
}

template <class KeyType, class ItemType>
ItemType DictTree<KeyType, ItemType>::lookupItem(KeyType key)
{
    NodeT<KeyType, ItemType> * number = containedInSubtree(root, key);
    return number->data;
}

template <class KeyType, class ItemType>
NodeT<KeyType, ItemType>* DictTree<KeyType, ItemType>::containedInSubtree(NodeT<KeyType, ItemType>* subTree, KeyType key)
{
    if (subTree == nullptr){
        return nullptr;
    }
    else if (subTree->key == key){
        return subTree;
    }
    
    else if(key < subTree->key){ //move left
        return containedInSubtree(subTree->left, key);
    }
    else if(key > subTree->key){ //move right
        return containedInSubtree(subTree->right, key);
    }
    return nullptr;
}

template <class KeyType, class ItemType>
bool DictTree<KeyType, ItemType>::remove(KeyType key)
{
    // This method is done.
    bool isSuccessful = false;
    
    root = removeFromSubtree(root, key, isSuccessful);
    
    if (isSuccessful){
        cout << "Sucessfully deleted node" << endl;
        numNodes--;
    }
    
    return isSuccessful;
}

// Case 1) Node is a leaf - it is deleted
// Case 2) Node has one child (left/right) - parent adopts child
//Case 3) Node has two children - find successor node.
template<class KeyType, class ItemType>
NodeT<KeyType, ItemType>* DictTree<KeyType, ItemType>::removeFromSubtree(NodeT<KeyType, ItemType>* subTree, KeyType key, bool & success)
{
    if(subTree==nullptr){
        cout << "Nothing to remove, tree is empty" << endl;
        return nullptr;
    }
    else{
        if(root->key == key){ //delete root node
            cout << "Got to delete root! " << endl;
            if(root->left == nullptr && root->right == nullptr){ //no children
                NodeT<KeyType, ItemType> * delPtr = root;
                root = nullptr;
                delete delPtr;
                success = true;
                return root;
            }
            else if(root->left == nullptr && root->right != nullptr){ //one right child
                NodeT<KeyType, ItemType> * delPtr = root;
//                cout << "old root " << root->data << endl;
                root=root->right;
//                cout << "new root " << root->data << endl;
                delPtr->right = nullptr;
                delete delPtr;
                success = true;
                return root;
            }
            else if(root->left != nullptr && root->right == nullptr){
                NodeT<KeyType, ItemType> * delPtr = root;
                //cout << "old root " << root->data << endl;
                root=root->left;
                //cout << "new root " << root->data << endl;
                delPtr->left = nullptr;
                delete delPtr;
                success = true;
                return root;
            }
            else if(root->left!=nullptr && root->right !=nullptr){
                NodeT<KeyType, ItemType> * smallRight = FindSmallest(root->right);
                cout << "Going to reassign root to " << smallRight->data << endl;
                cout << "old root is " << root->data << endl;
                NodeT<KeyType, ItemType> * delptr = root;
                root = root->right;
                root->left = delptr->left;
                delete delptr;
                success=true;
                return root;
            }
        }
       
        else{
            if (key < subTree->key && subTree->left != nullptr){
                if (subTree->left->key == key){
                    subTree = subTree->left;
                    cout << "Gotta delete left" << subTree->data << endl;
//                    if(subTree->left == nullptr && subTree->right == nullptr){ //no children
//                        NodeT<KeyType, ItemType> * delPtr = subTree;
//                        subTree = nullptr;
//                        delete delPtr;
//                        success = true;
//                        return subTree;
//                    }
//                    else if(subTree->left == nullptr && subTree->right != nullptr){ //one right child
//                        NodeT<KeyType, ItemType> * delPtr = subTree;
//                        //                cout << "old root " << root->data << endl;
//                        subTree=subTree->right;
//                        //                cout << "new root " << root->data << endl;
//                        delPtr->right = nullptr;
//                        delete delPtr;
//                        success = true;
//                        return subTree;
//                    }
//                    else if(subTree->left != nullptr && subTree->right == nullptr){
//                        NodeT<KeyType, ItemType> * delPtr = subTree;
//                        //cout << "old root " << root->data << endl;
//                        subTree=subTree->left;
//                        //cout << "new root " << root->data << endl;
//                        delPtr->left = nullptr;
//                        delete delPtr;
//                        success = true;
//                        return subTree;
//                    }
//                    else if(subTree->left!=nullptr && subTree->right !=nullptr){
//                        NodeT<KeyType, ItemType> * smallRight = FindSmallest(subTree->right);
//                        cout << "Going to reassign  to " << smallRight->data << endl;
//                        cout << "old root is " << subTree->data << endl;
//                        NodeT<KeyType, ItemType> * delptr = subTree;
//                        subTree = subTree->right;
//                        subTree->left = delptr->left;
//                        delete delptr;
//                        success=true;
//                        return subTree;
//                    }
                }
                else{
                    removeFromSubtree(subTree->left, key, success); //continue on
                }
            }
            else if (key > subTree->key && subTree->right != nullptr){
                if (subTree->right->key == key){
                    cout << "Gotta delete right";
//                    if(subTree->left == nullptr && subTree->right == nullptr){ //no children
//                        NodeT<KeyType, ItemType> * delPtr = subTree;
//                        subTree = nullptr;
//                        delete delPtr;
//                        success = true;
//                        return subTree;
//                    }
//                    else if(subTree->left == nullptr && subTree->right != nullptr){ //one right child
//                        NodeT<KeyType, ItemType> * delPtr = subTree;
//                        //                cout << "old root " << root->data << endl;
//                        subTree=subTree->right;
//                        //                cout << "new root " << root->data << endl;
//                        delPtr->right = nullptr;
//                        delete delPtr;
//                        success = true;
//                        return subTree;
//                    }
//                    else if(subTree->left != nullptr && subTree->right == nullptr){
//                        NodeT<KeyType, ItemType> * delPtr = subTree;
//                        //cout << "old root " << root->data << endl;
//                        subTree=subTree->left;
//                        //cout << "new root " << root->data << endl;
//                        delPtr->left = nullptr;
//                        delete delPtr;
//                        success = true;
//                        return subTree;
//                    }
//                    else if(subTree->left!=nullptr && subTree->right !=nullptr){
//                        NodeT<KeyType, ItemType> * smallRight = FindSmallest(subTree->right);
//                        cout << "Going to reassign  to " << smallRight->data << endl;
//                        cout << "old root is " << subTree->data << endl;
//                        NodeT<KeyType, ItemType> * delptr = subTree;
//                        subTree = subTree->right;
//                        subTree->left = delptr->left;
//                        delete delptr;
//                        success=true;
//                        return subTree;
//                    }
                }
                
                else{
                    removeFromSubtree(subTree->left, key, success); //continue on
                }
            }
            else{
                cout << "Key does not exsist" << endl;
            }
        }
    }
    return nullptr;
}

template<class KeyType, class ItemType>
NodeT<KeyType, ItemType>* DictTree<KeyType, ItemType>::FindSmallest(NodeT<KeyType, ItemType>* ptr){
    NodeT<KeyType, ItemType> * tracker = ptr;
    while(tracker && tracker->left != nullptr){
        tracker = tracker->left;
    }
    return tracker;
}
#endif
