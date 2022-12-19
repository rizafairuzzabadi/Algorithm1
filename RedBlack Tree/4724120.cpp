// Muhammad Riza Fairuzzabadi
// 150170908

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

enum Color // boolean for each of the colors
{
    RED,
    BLACK
};

using namespace std;

struct Node
{
    string Name;
    string Platform;
    int Year_of_Release;
    string Publisher;
    double NA_Sales;
    double EU_Sales;
    double Other_Sales;
    bool color;
    Node *left;
    Node *right;
    Node *parent;
    Node(); // default constructor
};

Node::Node()
{ // default constructor
    parent = NULL;
    right = NULL;
    left = NULL;
}

class RBTree
{
private:

    Node *search(Node *x, string name)
    {
        if (x == NULL || name == x->Publisher)
        {
            return x;
        }
        if (name > x->Publisher)
        {
            return search(x->right, name);
        }
        return search(x->left, name);
    }

    void fixInsert(Node *z)
    {
        Node *y;
        while (z != this->root && z->parent->color == RED)
        { // violates rule: parent of a red node must be black
            if (z->parent == z->parent->parent->left)
            {                                 // if parent of z is the left child
                y = z->parent->parent->right; // y = z's uncle
                if (y != NULL && y->color == RED)
                { // if uncle is red
                    // turn parent and uncle to black, grandparent to red
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    // assign grandparent to z, to continue the loop
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->right)
                    {                  // if z is right child
                        z = z->parent; // assign z's parent to z
                        leftRotate(z); // left rotate it
                    }
                    z->parent->color = BLACK;       // turn parent to black
                    z->parent->parent->color = RED; // turn grandparent to red
                    rightRotate(z->parent->parent); // right rotate grandparent
                }
            }
            else
            {
                y = z->parent->parent->left; // y = z's uncle
                if (y != NULL && y->color == RED)
                { // if uncle is red
                    // turn parent and uncle to black, grandparent to red
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    // assign grandparent to z, to continue the loop
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->left)
                    {                   // if z is the left child
                        z = z->parent;  // assign z's parent to z
                        rightRotate(z); // right rotate it
                    }
                    z->parent->color = BLACK;       // turn parent to black
                    z->parent->parent->color = RED; // turn grandparent to red
                    leftRotate(z->parent->parent);  // left rotate grandparent
                }
            }
            if (z == root)
            { // if z is the root, break the loop
                break;
            }
        }
        root->color = BLACK; // root is always black
    }

    void PreOrderPrint(Node *root, string indent, bool last) // Printing of the nodes after first season
    {
        if (root != NULL)
        {
            cout << indent;
            indent += "-";
            string TheColor; // to convert the boolean colors to their string equivalent
            if (root->color == BLACK)
                TheColor = "BLACK";
            else if (root->color == RED)
                TheColor = "RED";
            cout << "(" << TheColor << ") " << root->Publisher << endl;
            PreOrderPrint(root->left, indent, false);
            PreOrderPrint(root->right, indent, true);
        }
    }

public:
    Node *root;

    RBTree()
    {
        root = NULL;
    }

    void PreInsert(Node *x)
    {
        Node *y = search(root, x->Publisher); // search if player exists in tree
        if (y != NULL)
        { // if it exists, update stats
            y->NA_Sales += x->NA_Sales;
            y->EU_Sales += x->EU_Sales;
            y->Other_Sales += x->Other_Sales;
            //delete x;
            return;
        }
        insert(x); // if it not exists, insert it
    }

    void leftRotate(Node *x)
    {
        Node *y = x->right;
        x->right = y->left;
        if (y->left != NULL)
        {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == NULL)
        {
            this->root = y;
        }
        else if (x == x->parent->left)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }
    void rightRotate(Node *x)
    {
        Node *y = x->left;
        x->left = y->right;
        if (y->right != NULL)
        {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == NULL)
        {
            this->root = y;
        }
        else if (x == x->parent->right)
        {
            x->parent->right = y;
        }
        else
        {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    void endoftheLine() {
        Printer();
    }

    void PerDecadeNews(int prevYear, Node * BestSellerNA, Node * BestSellerEU,Node * BestSellerROW) {
            cout << "End of " << prevYear << " Year" << endl;
            cout << "Best seller in North America: " << BestSellerNA->Publisher << " - " << BestSellerNA->NA_Sales << "million" << endl;
            cout << "Best seller in Europe: " << BestSellerEU->Publisher << " - " << BestSellerEU->EU_Sales << "million" << endl;
            cout << "Best seller rest of the World: " << BestSellerROW->Publisher << " - " << BestSellerROW->Other_Sales << "million" << endl;
    }

    void SeekBestSeller(Node *node, Node *(&BestSellerNA), Node *(&BestSellerEU), Node *(&BestSellerROW)){
        if (node == NULL) return; // sub-tree is empty
        if (BestSellerNA == NULL) BestSellerNA = root; 
        if (BestSellerEU == NULL) BestSellerEU = root;
        if (BestSellerROW == NULL) BestSellerROW = root;
        if (node->NA_Sales> BestSellerNA->NA_Sales){
            BestSellerNA = node;
        }
        if (node->EU_Sales > BestSellerEU->EU_Sales){
           BestSellerEU = node;
        }
        if (node->Other_Sales > BestSellerROW->Other_Sales){
            BestSellerROW = node;
        }
        SeekBestSeller(node->left, BestSellerNA,BestSellerEU, BestSellerROW);
        SeekBestSeller(node->right, BestSellerNA, BestSellerEU, BestSellerROW);
    }

    void insert(Node *z)
    {
        Node *y = NULL;
        Node *x = this->root;

        while (x != NULL)
        {
            y = x;
            if (z->Publisher < x->Publisher)
            {
                x = x->left;
            }
            else
            {
                x = x->right;
            }
        }
        z->parent = y;
        if (y == NULL)
        {
            this->root = z;
        }
        else if (z->Publisher < y->Publisher)
        {
            y->left = z;
        }
        else
        {
            y->right = z;
        }

        z->color = RED; 
        fixInsert(z);
    }

    void Printer()
    {
        if (root)
        {
            PreOrderPrint(this->root, "", true);
        }
    }
};
int main(int argc, char *argv[1])
{
    string namafayl;          //namefile
    stringstream in(argv[1]); //gets filename as argument
    in >> namafayl;

    ifstream file;
    file.open(namafayl);

    if (!file)
    {
        cerr << "File cannot be opened!";
        exit(1);
    }
    string line;
    RBTree tree;

    int prevDecade; //Self-Explanatory
    int currentDecade;
    int prevYear;
    int twentytwenty = 0;   //bool year 2020
    int printedDecade = 0;

    Node *BestSellerNA = NULL;
    Node *BestSellerEU = NULL;
    Node *BestSellerROW = NULL;

    getline(file, line); // this is the header line
    while (!file.eof())  // till the end of file, may get error if there's an empty line at the end, since stoi is used.
    {
        Node *head = new Node();
        getline(file, line, ','); // takes Name
        head->Name = line;
        getline(file, line, ','); // Platform
        head->Platform = line;

        if(line == ""){ //to ignore last blank line
            continue;       
        }

        getline(file, line, ','); // Year_of_Release
        head->Year_of_Release = stoi(line);
        currentDecade = head->Year_of_Release - (head->Year_of_Release % 10);

        getline(file, line, ','); // Publisher
        head->Publisher = line;
        getline(file, line, ','); // NA_Sales
        head->NA_Sales = stod(line);
        getline(file, line, ','); // EU_Sales
        head->EU_Sales = stod(line);
        getline(file, line, '\n'); // EU_Sales
        head->Other_Sales = stod(line);

        if(currentDecade >= 1990 && (head->Year_of_Release % 10 == 1) && printedDecade!= currentDecade){
            tree.SeekBestSeller(tree.root, BestSellerNA, BestSellerEU, BestSellerROW);
            tree.PerDecadeNews(prevYear, BestSellerNA, BestSellerEU, BestSellerROW);
            if(prevYear == 2020 && 2020 != head->Year_of_Release && (head->Year_of_Release % 10 == 1)){
                twentytwenty = 1;
                tree.endoftheLine();
                twentytwenty = 3; //So the tree will not reprinted after 2020.
            }
            printedDecade = currentDecade;
        }

        prevYear = head->Year_of_Release;
        tree.PreInsert(head);
    }
    if(currentDecade < 1990 || printedDecade < prevYear){     //Checking the cases where it endedn before the last entered decade ends. 
        tree.SeekBestSeller(tree.root, BestSellerNA, BestSellerEU, BestSellerROW);
        tree.PerDecadeNews(prevYear, BestSellerNA, BestSellerEU, BestSellerROW);
    }

    if(twentytwenty == 0)
        tree.endoftheLine();
          //Ends before end of 2020. Tree is still printed
    return 0;
}
