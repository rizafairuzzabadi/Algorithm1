//--- 2022-2023 Fall Semester Data Structure Assignment 2 ---//
//--------------------------//
//---Name & Surname: Muhammad Rıza Faıruzzabadı
//---Student Number: 150170908
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>

#include "structs.h"

using namespace std;

//-------------Complete The Functions Below-------------//

//-------------Initialize Priority Queue-------------//
PriorityQueue::PriorityQueue(){
    head = NULL;            //setting the head to NULL
};

//-------------Insert New Node To Priority Queue-------------//
void PriorityQueue::enque(Node* newnode){
    if(head == NULL){       //If the queue is empty
        head = newnode;     //newnode becomes the head
        return;
    }
    Node *temp = head;      //storing the head node for now
    if(temp->token.val > newnode->token.val){     //If the value of the newnode is smaller than the head node
        head = newnode;     //newnode becomes the head
        newnode->next = temp;       //the old head becomes the next node of the newnode
        return;
    }
    while(temp->next != NULL &&(temp->next->token.val < newnode->token.val || temp->next->token.val == newnode->token.val)){  //Loop while it is not the last node and the value of the next node is smaller or equal than/to the newnode
        temp = temp->next;      //temp becomes the next node
    }
    newnode->next = temp->next;     //the next node of the newnode becomes the next node of the temp
    temp->next = newnode;           //the newnode becomes the next node of the temp
    return;
};

//-------------Remove Node From Priority Queue-------------//
Node* PriorityQueue::dequeue(){
    if(head == NULL){       //If the queue is empty
        return NULL;
    }
    Node *temp = head;      //storing the head node for now
    head = head->next;      //next node becomes the head
    return temp;            //return the previous head
};

//-------------Initialize Tree-------------//
Tree::Tree(){
    root = NULL;            //setting the root to NULL
};

//-------------Delete Tree Nodes From Memory-------------//
Tree::~Tree(){
    delete root;        //deletes the root, supposedly deletes the whole tree
    root = NULL;        //sets the root to NULL
    
    //OR, just in case the above line doesn't work, use the following lines:
    // deleteTree(root);       //calls the deleteTree function
};

//-------------Delete Tree From Memory-------------//
void Tree::deleteTree(Node* node){
    //-------------This Function Is Not Necessary-------------//
    //-----------------Use It At Your Own Will----------------//
    // if (node == NULL)       //If the tree is empty
    //     return;
    if(node->left != NULL)  //If the left node is not NULL
        deleteTree(node->left);     //recursively calls the deleteTree function for the left node
    if(node->right != NULL) //If the right node is not NULL
        deleteTree(node->right);    //recursively calls the deleteTree function for the right node
    delete node;                //deletes the node
    return;

    
}

//-------------Merges Two Node Into One-------------//
Node* Tree::mergeNodes(Node* temp1, Node* temp2){
    Node *temp = new Node;       //initializing temp node to store the values
    temp->token.symbol = temp1->token.symbol + temp2->token.symbol;     //sums the symbols of the two nodes and sets it to the new node
    temp->token.val = temp1->token.val + temp2->token.val;              //sets the values of the two nodes and sets it to the new node
    temp->left = temp1;          //sets temp1 to the left node of the new node
    temp->right = temp2;         //sets temp2 to the right node of the new node
    return temp;
};

void Tree::printTree(Node* traverse, int level){
    cout << level << "\t";
    for (int i = 0; i < level; i++)
        cout << "\t"; 

    cout << traverse->token.symbol << "(" << traverse->token.val << ")" << endl;

    if(traverse->left)
        printTree(traverse->left, level + 1);  
    if(traverse->right)
        printTree(traverse->right, level + 1);
};