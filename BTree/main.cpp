//Muhammad Riza Fairuzzabadi 150170908
//HackerRank - fairuzzabadi17
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Node
{
    int *Keys;
    int t;
    int n;
    bool leaf;
    int *attx;
    int *atty;
    char *attz;
    unsigned char *ChKeys;
    Node **C;

public:
    Node(int _t, bool _leaf);
    void traverse(char key);
    void traverseZ();
    void insertNonFull(int x, int y, char z, int k);
    void insertNonFullZ(int x, int y, char k);
    void Split(int a, int b, char c, int i, Node *y);
    void SplitZ(int a, int b, int i, Node *y);

    friend class BTree;
};

class BTree
{
    Node *root;
    int t;
    int k;

public:
    BTree(int _t)
    {
        root = NULL;
        t = _t;
    }

    void traverse(char key)
    {
        if (root != NULL)
            root->traverse(key);
    }

    void traverseZ()
    {
        if (root != NULL)
            root->traverseZ();
    }

    void insert(int x, int y, char z, char key);
    void insertZ(int x, int y, char z, char k);
};

Node::Node(int t1, bool leaf1)
{
    t = t1;
    leaf = leaf1;
    Keys = new int[2 * t - 1];
    ChKeys = new unsigned char[2 * t - 1];
    attx = new int[2 * t - 1];
    atty = new int[2 * t - 1];
    attz = new char[2 * t - 1];
    C = new Node *[2 * t];

    n = 0;
}

void Node::traverse(char key)
{
    int i;
    for (i = 0; i < n; i++)
    {
        cout << "(";
        if (key != 'x')
            cout << attx[i] << ",";
        cout << Keys[i] << ",";
        if (key != 'y')
            cout << atty[i] << ",";
        cout << attz[i] << ")";
    }
    for (i = 0; i < n; i++)
    {
        if (leaf == false)
        {
            cout << endl;
            C[i]->traverse(key);
        }
    }

    if (leaf == false)
    {
        cout << endl;
        C[i]->traverse(key);
    }
}

void Node::traverseZ()
{

    int i;
    for (i = 0; i < n; i++)
    {
        cout << "(";
        cout << attx[i] << ",";
        cout << atty[i] << ",";
        cout << ChKeys[i] << ")";
    }
    for (i = 0; i < n; i++)
    {
        if (leaf == false)
        {
            cout << endl;
            C[i]->traverseZ();
        }
    }

    if (leaf == false)
    {
        cout << endl;
        C[i]->traverseZ();
    }
}

void BTree::insert(int x, int y, char z, char key)
{
    switch (key)
    {
    case 'x':
        k = x;
        break;
    case 'y':
        k = y;
        break;
    }
    if (root == NULL)
    {
        root = new Node(t, true);
        root->Keys[0] = k;
        root->attx[0] = x;
        root->atty[0] = y;
        root->attz[0] = z;
        root->n = 1;
    }
    else
    {
        if (root->n == 2 * t - 1)
        {
            Node *s = new Node(t, false);
            s->C[0] = root;
            s->Split(x, y, z, 0, root);
            int i = 0;
            if (s->Keys[0] < k)
                i++;
            s->C[i]->insertNonFull(x, y, z, k);
            root = s;
        }
        else
            root->insertNonFull(x, y, z, k);
    }
}

void BTree::insertZ(int x, int y, char z, char k)
{
    if (root == NULL)
    {
        root = new Node(t, true);
        root->ChKeys[0] = z;
        root->attx[0] = x;
        root->atty[0] = y;
        root->n = 1;
    }
    else
    {
        if (root->n == 2 * t - 1)
        {
            Node *s = new Node(t, false);
            s->C[0] = root;
            s->SplitZ(x, y, 0, root);
            int i = 0;
            if (s->ChKeys[0] < z)
                i++;
            s->C[i]->insertNonFullZ(x, y, z);
            root = s;
        }
        else
        {
            root->insertNonFullZ(x, y, z);
        }
    }
}

void Node::insertNonFull(int x, int y, char z, int k)
{
    int i = n - 1;

    if (leaf == true)
    {
        while (i >= 0 && Keys[i] > k)
        {
            Keys[i + 1] = Keys[i];
            attx[i + 1] = attx[i];
            atty[i + 1] = atty[i];
            attz[i + 1] = attz[i];

            i--;
        }

        Keys[i + 1] = k;
        attx[i + 1] = x;
        atty[i + 1] = y;
        attz[i + 1] = z;
        n = n + 1;
    }
    else
    {
        while (i >= 0 && Keys[i] > k)
            i--;

        if (C[i + 1]->n == 2 * t - 1)
        {
            Split(x, y, z, i + 1, C[i + 1]);
            if (Keys[i + 1] < k)
                i++;
        }
        C[i + 1]->insertNonFull(x, y, z, k);
    }
}

void Node::insertNonFullZ(int x, int y, char k)
{
    int i = n - 1;

    if (leaf == true)
    {
        while (i >= 0 && ChKeys[i] > k)
        {
            ChKeys[i + 1] = ChKeys[i];
            attx[i + 1] = attx[i];
            atty[i + 1] = atty[i];
            i--;
        }
        ChKeys[i + 1] = k;
        attx[i + 1] = x;
        atty[i + 1] = y;
        n = n + 1;
    }
    else
    {
        while (i >= 0 && ChKeys[i] > k)
            i--;
        if (C[i + 1]->n == 2 * t - 1)
        {
            SplitZ(x, y, i + 1, C[i + 1]);
            if (ChKeys[i + 1] < k)
                i++;
        }
        C[i + 1]->insertNonFullZ(x, y, k);
    }
}

void Node::Split(int a, int b, char c, int i, Node *y)
{
    Node *z = new Node(y->t, y->leaf);
    z->n = t - 1;

    for (int j = 0; j < t - 1; j++)
    {
        z->Keys[j] = y->Keys[j + t];
        z->attx[j] = y->attx[j + t];
        z->atty[j] = y->atty[j + t];
        z->attz[j] = y->attz[j + t];
    }

    if (y->leaf == false)
    {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j + t];
    }

    y->n = t - 1;
    for (int j = n; j >= i + 1; j--)
        C[j + 1] = C[j];
    C[i + 1] = z;
    for (int j = n - 1; j >= i; j--)
    {
        Keys[j + 1] = Keys[j];
        attx[j + 1] = attx[j];
        atty[j + 1] = atty[j];
        attz[j + 1] = attz[j];
    }
    Keys[i] = y->Keys[t - 1];
    attx[i] = y->attx[t - 1];
    atty[i] = y->atty[t - 1];
    attz[i] = y->attz[t - 1];
    n = n + 1;
}

void Node::SplitZ(int a, int b, int i, Node *y)
{
    Node *z = new Node(y->t, y->leaf);
    z->n = t - 1;
    for (int j = 0; j < t - 1; j++)
    {
        z->ChKeys[j] = y->ChKeys[j + t];
        z->attx[j] = y->attx[j + t];
        z->atty[j] = y->atty[j + t];
    }
    if (y->leaf == false)
    {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j + t];
    }
    y->n = t - 1;
    for (int j = n; j >= i + 1; j--)
        C[j + 1] = C[j];
    C[i + 1] = z;
    for (int j = n - 1; j >= i; j--)
    {
        ChKeys[j + 1] = ChKeys[j];
        attx[j + 1] = attx[j];
        atty[j + 1] = atty[j];
    }
    ChKeys[i] = y->ChKeys[t - 1];
    attx[i] = y->attx[t - 1];
    atty[i] = y->atty[t - 1];
    n = n + 1;
}

int main()
{
    int Keycount;
    int Degree;
    char Key;
    cin >> Keycount;
    cin >> Degree;
    cin >> Key;
    BTree tree(Degree);
    for (int i = 0; i < Keycount; i++)
    {
        int x;
        int y;
        char z;
        cin >> x >> y >> z;
        if (Key == 'z')
            tree.insertZ(x, y, z, z);
        else
            tree.insert(x, y, z, Key);
    }
    if (Key == 'z')
        tree.traverseZ();
    else
        tree.traverse(Key);

    return 0;
}
