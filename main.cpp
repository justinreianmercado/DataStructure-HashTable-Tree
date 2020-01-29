//
//  main.cpp
//  HashTableTree
//
//  Created by Justin Reian Balite Mercado on 10/15/19.
//  Copyright © 2019 Justin Reian Balite Mercado. All rights reserved.
//

#include <iostream>
#include "DictTree.h"
#include "HashTable.h"
#include <string>
#include <fstream>
using namespace std;

void display1(string& anItem){
    cout << "Displaying items - " << anItem << endl;
}

int main() {
    ofstream outFile;
    ifstream inFile;
    
    cout << "Testing DictTree" << endl << endl;
    DictTree<int, string> * tree1 = new DictTree<int, string>();
    cout << "Testing HashTree" << endl << endl;
    HashTable<int, string> * dict1 = new HashTable<int, string>();
    
    outFile.open("output.txt");
    inFile.open("input.txt");
    
    if(!inFile){ //This will test if the instructions have been loaded properly
        cout << "File not found! " << endl;
        exit(0);
    }
    else{
        cout << "Unit Test Instructions Loaded" <<endl;
    }
    
    string command;
    inFile>>command;
    while(command!="quit"){
        if(command=="add"){
            int key;
            inFile>>key;
            string data;
            inFile>>data;
            dict1->add(key, data);
            outFile<<"Adding element" <<endl;
        }
        if(command=="print"){
            dict1->traverse(display1);
            outFile<<"Printing" << endl;
        }
        if(command=="remove"){
            int key;
            inFile>>key;
            cout<< "Remove function is not compiling" << endl;
            outFile<< "Remove function is not compiling" << endl;
        }
        if(command=="getitem"){
//            int key;
//            inFile >> key;
//            string result;
//            result << dict1->getItem(key);
//            outFile<<"Getting item at key " << key " is " << result<< endl;
            cout<< "getitem function is not compiling" << endl;
            outFile<< "getitem function is not compiling" << endl;
        }
        if(command=="size"){
            int i = dict1->size();
            outFile<< "size is " << i << endl;
            cout<< "size is " << i << endl;
        }
        if(command=="contains"){
            int key;
            inFile>>key;
            bool result = dict1->contains(key);
            if(result){
                cout << "True" << endl;
                outFile << "Contains is true" << endl;
            }
            else{
                cout << "False" << endl;
                outFile << "Contains is false" << endl;
            }
        }
        inFile>>command;
    }
    outFile.close();
    inFile.close();
    return 0;
}
