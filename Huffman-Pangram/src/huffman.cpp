//--- 2022-2023 Fall Semester Data Structure Assignment 2 ---//
//--------------------------//
//---Name & Surname: Muhammad Rıza Faıruzzabadı
//---Student Number: 150170908
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <bits/stdc++.h>

#include "huffman.h"
#include "structs.h"

using namespace std;

//-------------Complete The Functions Below-------------//

//-----------------------------------------------------//
//-----------Reads the key from text file--------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::readKey(const char* argv){
    ifstream readKeyFile;
    readKeyFile.open(argv);

    if(readKeyFile.is_open()){
        while(!readKeyFile.eof()){
            readKeyFile >> key;
        }
    }
    readKeyFile.close();
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//---------Sorts the key in an alpabetic order---------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::sortKey(){
    sortedKey = key;
    sort(sortedKey.begin(), sortedKey.end());
};
//-----------------------------------------------------//


//-----------------------------------------------------//
//-------Finds the frequency of the characters---------//
//-----------------------------------------------------//
void Huffman::findFrequency(){
    //DO NOT CHANGE THIS
    sortKey();
    //DO NOT CHANGE THIS
    char countedChar = sortedKey[0];    //Character that is being counted
    int sortedkeylength = sortedKey.length();
    // cout << "Sorted Key: " << sortedKey << endl;
    // cout << "Sorted Key length: " << sortedkeylength << endl;
    // int counter = 1;                    //Counter for the character, starts with 1
    // bool flag_udscore = false;          //Flag for underscore
    int i = 0;
    for(i = 0; i < sortedkeylength; i++){
        if(sortedKey[i] == sortedKey[i+1]){     //If the next character is the same as the current character
            // countedChar = sortedKey[i];      
            continue;
            // counter++;                  //Increment the counter
        }
        else{
            Token tokentemp;                //New token init
            tokentemp.symbol = countedChar; //Current char set as token symbol
            // tokentemp.val = counter;        //Current counter set as token value
            tokentemp.val = count(sortedKey.begin(), sortedKey.end(), sortedKey[i]);
            // counter = 1;            //Counter reset
            countedChar = sortedKey[i+1];   //Current char set as counted char
            Node* newNode = new Node;   //New node init
            newNode->token = tokentemp;     //Token set as node token
            queue.enque(newNode);       //Enqueue the new node
            delete newNode;             //Delete the new node
        }
    }
    //TODO
};
//-----------------------------------------------------//


//-----------------------------------------------------//
//----------------Creates Huffman Tree-----------------//
//-----------------------------------------------------//
void Huffman::createHuffmanTree(){
    Tree();             //Init the tree
    PriorityQueue();    //Init the priority queue
    findFrequency();    //Calls the frequency function, enqueue the keys

    // from now on, we have keys' queue sorted by frequency
    //let's start from the highest priority keys

    while(queue.head->next != NULL){   //Until there is only one left in queue, which will be the root of tree.
        Node* newtemp1 = new Node;   //New temp1 node init to merge leaf from queue later
        Node* newtemp2 = new Node;   //New temp2 node init to merge later
        newtemp1 = queue.dequeue();  //left leaf from queue
        newtemp2 = queue.dequeue(); //right leaf from queue
        Node* newNode = new Node;   //New node init
        newNode = huffmanTree.mergeNodes(newtemp1, newtemp2); //merging the two nodes
        queue.enque(newNode);   //Enqueue the new node
        //Since enqueue sorts the queue, subtrees (when required)
        //will be created automatically (when the newly enqueued node is larger)
        //and subtrees will be connected eventually.
        delete newtemp1;    //Delete the temp1 node
        delete newtemp2;    //Delete the temp2 node
        delete newNode;     //Delete the new node
    }
    huffmanTree.root = queue.dequeue();  //the last node in queue is the largest, which is root of Huffman tree.
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//---------------Prints the Huffman Tree---------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::printHuffmanTree(){
    huffmanTree.printTree(huffmanTree.root, 0);
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------------Finds and returns the binary------------//
//----------------value to given character-------------//
//-----------------------------------------------------//
string Huffman::getTokenBinary(char tokenChar, Node* traverse, string tokenBinary){
    if(traverse->left == NULL && traverse->right == NULL){ //If the node is a leaf
        if(traverse->token.symbol[0] == tokenChar){   
            return tokenBinary; //Return the binary value
        }
    }
    else{   //If the node is not a leaf
        if(traverse->left != NULL){ //If the node has a left child
            string leftBinary = tokenBinary + "0"; //Add 0 to the binary value
            string leftResult = getTokenBinary(tokenChar, traverse->left, leftBinary); //Recursive call to the left child
            if(leftResult != ""){   //If the result is not empty
                return leftResult;  //Return the result
            }
        }
        if(traverse->right != NULL){    //If the node has a right child
            string rightBinary = tokenBinary + "1";    //Add 1 to the binary value
            string rightResult = getTokenBinary(tokenChar, traverse->right, rightBinary);   //Recursive call to the right child
            if(rightResult != ""){  //If the result is not empty
                return rightResult; //Return the result
            }
        }
    }
    return "";  //If the result is empty, return empty string
    //TODO
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//--------------Encodes the given password-------------//
//-----------------------------------------------------//
void Huffman::encodePassword(string password){
    //TODO
    int passwordLength = password.length();
    for(int i = 0; i < passwordLength; i++){        //itirate through the password string
        string temp = getTokenBinary(password[i], huffmanTree.root, ""); //Store binary value on temp first
        encodedBinaryPassword += temp;  //concatenate the binary value to the encoded binary password
        int tempLength = temp.length();         //Store the length of the binary value on tempLength
        encodedValPassword += to_string(tempLength);    //then concatenate the length of the binary value to the encoded value password
    }
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------------Prints the encoded password-------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::printEncodedPassword(){
    cout << "Encoded Password Binary: " << encodedBinaryPassword << endl;
    cout << "Encoded Password Value: " << encodedValPassword << endl;
};

//-----------------------------------------------------//
//--------------Decodes the given password-------------//
//-----------------------------------------------------//
void Huffman::decodePassword(string encodedBinaryPassword, string encodedValPassword){
    //TODO
    int i = 0;
    int int_encodedVal = 0;
    int encodedVallength = encodedValPassword.length();
    while(i < encodedVallength){
        int_encodedVal = encodedValPassword[i] - '0'; //Convert the char to int
        // cout << "int_encodedVal: " << int_encodedVal << endl;
        string temp = encodedBinaryPassword.substr(0, int_encodedVal); //Store the binary value of the token
        encodedBinaryPassword = encodedBinaryPassword.substr(int_encodedVal); //Remove the binary value of the token from the encoded binary password
        decodeToken(temp); //Decode the token and concatenate it to the decoded password
        i++;
    }
};

//-----------------------------------------------------//

//-----------------------------------------------------//
//---------------Decodes the given binary--------------//
//-----------------------------------------------------//
void Huffman::decodeToken(string encodedToken){
    //TODO
    // cout << "Endoded Token: " << encodedToken << "length " << encodedToken.length() << endl;
    Node* traverse = huffmanTree.root;  //Start from the root
    int encodedTokenLength = encodedToken.length();
    for(int i = 0; i < encodedTokenLength; i++){
        if(encodedToken[i] == '0'){   //If the binary value is 0, go to the left child
            traverse = traverse->left;
        }
        else if(encodedToken[i] == '1'){    //If the binary value is 1, go to the right child
            traverse = traverse->right;
        }
    }
    decodedPassword += traverse->token.symbol; //Concatenate the decoded token to the decoded password
    
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------------Prints the decoded password-------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::printDecodedPassword(){
    cout << "Decoded Password: " << decodedPassword << endl;
};