//Muhammad Riza Fairuzzabadi
//150170908

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

enum Color //boolean for each of the colors
{
    RED,
    BLACK
};

using namespace std;

struct Node
{
    string season; //columns/datas
    string name;
    string team;
    int rebound;
    int assist;
    int point;
    bool color;
    Node *left;
    Node *right;
    Node *parent;
};

class RBTree
{
private:
    Node *root;
    Node *TNULL;

    void initializeNULLNode(Node *node, Node *parent)
    {
        node->season = ""; //NULL node initialization
        node->name = "";
        node->team = "";
        node->rebound = 0;
        node->assist = 0;
        node->point = 0;
        node->parent = parent;
        node->left = nullptr;
        node->right = nullptr;
        node->color = BLACK;
    }
    void fixInsert(Node *k) //fixes violations that may caused by initial BST insertion
    {
        Node *u;
        while (k->parent->color == RED)
        {
            if (k->parent == k->parent->parent->right)
            {
                u = k->parent->parent->left;
                if (u->color == RED)
                {
                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                }
                else
                {
                    if (k == k->parent->left)
                    {
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    leftRotate(k->parent->parent);
                }
            }
            else
            {
                u = k->parent->parent->right;

                if (u->color == RED)
                {
                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                }
                else
                {
                    if (k == k->parent->right)
                    {
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    rightRotate(k->parent->parent);
                }
            }
            if (k == root)
            {
                break;
            }
        }
        root->color = BLACK;
    }

    void PreOrderPrint(Node *root, string indent, bool last) //Printing of the nodes after first season
    {
        if (root != TNULL)
        {
            cout << indent;
            indent += "-";
            string TheColor; //to convert the boolean colors to their string equivalent
            if (root->color == BLACK)
                TheColor = "BLACK";
            else if (root->color == RED)
                TheColor = "RED";
            cout << "(" << TheColor << ")" << root->name << endl;
            PreOrderPrint(root->left, indent, false);
            PreOrderPrint(root->right, indent, true);
        }
    }
    void CheckSame(Node *root, Node *toCompare) //to check whether if the inserted player has played in the previous season, if true, updates their datas.
    {
        if (root != TNULL)
        {
            if (root->name == toCompare->name)
            {
                root->point = root->point + toCompare->point;
                root->rebound = root->rebound + toCompare->rebound;
                root->assist = root->assist + toCompare->assist;
                root->season = toCompare->season;
                if (root->point > leading1)
                {
                    if (root->season == WhichSeason) //this is most probably unnecessary since the insertion is in  season basis. But done anymway in case somehow a data from another season
                    {                                // slipped into the middle
                        leader1 = root->name;
                        leading1 = root->point;
                    }
                }
                if (root->assist > leading2)
                {
                    if (root->season == WhichSeason)
                    {
                        leader2 = root->name;
                        leading2 = root->assist;
                    }
                }
                if (root->rebound > leading3)
                {
                    if (root->season == WhichSeason)
                    {
                        leader3 = root->name;
                        leading3 = root->rebound;
                    }
                }
                return;
            }
            CheckSame(root->left, toCompare); //also in pre-order traversal
            CheckSame(root->right, toCompare);
        }
    }

public:
    int SeasonChange = 0;             //Check how much season passed.
    string WhichSeason = "Default";   //Stores the name of current season to be compared with to check any changes. Default is given  to indicate the first season.
    string leader1, leader2, leader3; //to store leading players;
    int leading1 = 0;                 //to store leading scores/points of each
    int leading2 = 0;
    int leading3 = 0;

    RBTree()
    {
        TNULL = new Node;
        TNULL->color = BLACK;
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        root = TNULL;
    }
    void leftRotate(Node *x)
    {
        Node *y = x->right;
        x->right = y->left;
        if (y->left != TNULL)
        {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr)
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
        if (y->right != TNULL)
        {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr)
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
    void endoftheLine() //essential since at the end, season doesn't change
    {
        cout << "End of the " << WhichSeason << " Season" << endl;
        cout << "Max Points: " << leading1 << " - Player Name: " << leader1 << endl;
        cout << "Max Assists: " << leading2 << " - Player Name: " << leader2 << endl;
        cout << "Max Rebs: " << leading3 << " - Player Name: " << leader3 << endl;
    }
    void insert(string &season, string &name, string &team, int rebound, int assist, int point)
    {
        Node *node = new Node;
        node->parent = nullptr;
        node->season = season;
        node->name = name;
        node->team = team;
        node->rebound = rebound;
        node->assist = assist;
        node->point = point;
        node->left = TNULL;
        node->right = TNULL;
        node->color = RED;
        if (season != WhichSeason && WhichSeason != "Default") //to check any season change
        {
            cout << "End of the " << WhichSeason << " Season" << endl; //prints the data
            cout << "Max Points: " << leading1 << " - Player Name: " << leader1 << endl;
            cout << "Max Assists: " << leading2 << " - Player Name: " << leader2 << endl;
            cout << "Max Rebs: " << leading3 << " - Player Name: " << leader3 << endl;
            SeasonChange++;
            leader1 = ""; //leading players are reset after each season
            leader2 = ""; //to prevent player with high score that is not in the season to win
            leader3 = "";
            leading1 = 0;
            leading2 = 0;
            leading3 = 0;
            if (SeasonChange == 1)
            {
                Printer(); //print only after first season ends.
            }
        }
        WhichSeason = season; //gets current season
        Evaluate(node);       //evaluate whether there are any players who join new season

        Node *y = nullptr;
        Node *x = this->root;

        while (x != TNULL)
        {
            y = x;
            if (node->name < x->name)
            {
                x = x->left;
            }
            else
            {
                x = x->right;
            }
        }

        if (node->point > leading1) //changes leader and points if there are any who surpass
        {
            leader1 = node->name;
            leading1 = node->point;
        }
        if (node->assist > leading2)
        {
            leader2 = node->name;
            leading2 = node->assist;
        }
        if (node->rebound > leading3)
        {
            leader3 = node->name;
            leading3 = node->rebound;
        }

        node->parent = y;
        if (y == nullptr)
        {
            root = node;
        }
        else if (node->name < y->name)
        {
            y->left = node;
        }
        else
        {
            y->right = node;
        }
        if (node->parent == nullptr) //if new node is root, returns.
        {
            node->color = BLACK;
            return;
        }
        if (node->parent->parent == nullptr) //if grandparent is null, returns.
        {
            return;
        }
        fixInsert(node);
    }
    void Evaluate(Node *currentNode) //explained above
    {
        if (root)
        {
            CheckSame(this->root, currentNode);
        }
    }
    void Printer() //explained above
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
    string a;
    string b;
    string c;
    int d;
    int e;
    int f;
    string line;
    RBTree tree;

    getline(file, line); //this is the header line
    while (!file.eof())  //till the end of file, may get error if there's an empty line at the end, since stoi is used.
    {
        Node *head = NULL;

        getline(file, line, ','); //takes season
        a = line;
        getline(file, line, ','); //name
        b = line;
        getline(file, line, ','); //team
        c = line;
        getline(file, line, ','); //rebound
        d = stoi(line);
        getline(file, line, ','); //assist
        e = stoi(line);
        getline(file, line, '\n'); //point
        f = stoi(line);

        tree.insert(a, b, c, d, e, f);
    }
    tree.endoftheLine();

    return 0;
}
