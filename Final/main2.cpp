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
    int ReturnData;
    int long *attx; //attributes
    int long *atty;
    unsigned char *attz;
    unsigned char *CharKeys;
    Node **C;
    bool leaf;

public:
    Node(int _t, bool _leaf);

    void insertNonFull(int x, int y, char z, int k);
    void insertNonFullZ(int x, int y, char k);
    void Split(int a, int b, char c, int i, Node *y);
    void SplitZ(int a, int b, int i, Node *y);
    void traverse(char key);
    void traverseZ();

    int findKey(int k, int isZ);
    void deletion(int k, char key);
    void deleteZ(char k);

    void removeFromLeaf(int id, char key);
    void removeFromNonLeaf(int id, char key);

    int getPredecessor(int id);
    char getPredecessorZ(int id);
    int getAttPredecessor(int id, char key);
    char getAttPredecessorZ(int id);

    int getSuccessor(int id);
    char getSuccessorZ(int id);
    int getAttSuccessor(int id, char key);
    char getAttSuccessorZ(int id);

    void fill(int id, int isZ);
    void borrowFromPrev(int id, int isZ);
    void borrowFromNext(int id, int isZ);
    void merge(int id, int isZ);

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

    void deletion(int k, char key);
    void deleteZ(char k);
};

Node::Node(int t1, bool leaf1)
{
    t = t1;
    leaf = leaf1;

    Keys = new int[2 * t - 1];
    CharKeys = new unsigned char[2 * t - 1];

    attx = new long int[2 * t - 1];
    atty = new long int[2 * t - 1];
    attz = new unsigned char[2 * t - 1];
    C = new Node *[2 * t];

    n = 0;
}

int Node::findKey(int k, int isZ)
{
    int id = 0;
    if (isZ == 0)
    {
        while (id < n && Keys[id] < k)
            ++id;
    }
    if (isZ == 1)
    {
        while (id < n && CharKeys[id] < k)
            ++id;
    }
    return id;
}

// Deletion operation
void Node::deletion(int k, char key)
{
    int id = findKey(k, 0);

    if (id < n && Keys[id] == k)
    {
        if (leaf)
            removeFromLeaf(id, key);
        else
            removeFromNonLeaf(id, key);
    }
    else
    {
        if (leaf)
        {
            return;
        }

        bool flag = ((id == n) ? true : false);

        if (C[id]->n < t)
            fill(id, 0);

        if (flag && id > n)
            C[id - 1]->deletion(k, key);
        else
            C[id]->deletion(k, key);
    }
    return;
}

void Node::deleteZ(char k)
{
    int id = findKey(k, 1);

    if (id < n && CharKeys[id] == k)
    {
        if (leaf)
            removeFromLeaf(id, 'z');
        else
            removeFromNonLeaf(id, 'z');
    }
    else
    {
        if (leaf)
        {
            return;
        }

        bool flag = ((id == n) ? true : false);

        if (C[id]->n < t)
            fill(id, 1);

        if (flag && id > n)
            C[id - 1]->deleteZ(k);
        else
            C[id]->deleteZ(k);
    }
    return;
}

// Remove from the leaf
void Node::removeFromLeaf(int id, char key)
{
    for (int i = id + 1; i < n; ++i)
    {
        if (key != 'z')
        {
            Keys[i - 1] = Keys[i];
            attz[i - 1] = attz[i];
            if (key == 'x')
                atty[i - 1] = atty[i];
            if (key == 'y')
                attx[i - 1] = attx[i];
        }
        if (key == 'z')
        {
            CharKeys[i - 1] = CharKeys[i];
            attx[i - 1] = attx[i];
            atty[i - 1] = atty[i];
        }
    }
    n--;

    return;
}

// Delete from non leaf node
void Node::removeFromNonLeaf(int id, char key)
{
    int k;
    if (key == 'z')
    {
        k = CharKeys[id];
    }

    else
    {
        k = Keys[id];
    }

    if (C[id]->n >= t)
    {
        int pred;
        char predzel;
        if (key != 'z')
            pred = getPredecessor(id);
        if (key == 'z')
            predzel = getPredecessorZ(id);
        int predx = getAttPredecessor(id, 'x');
        int predy = getAttPredecessor(id, 'y');
        char predz = getAttPredecessorZ(id);
        if (key != 'z')
        {
            Keys[id] = pred;
            attz[id] = predz;
        }
        else
            CharKeys[id] = predzel;
        attx[id] = predx;
        atty[id] = predy;
        if (key != 'z')
            C[id]->deletion(pred, key); //Buna bakilacak
        if (key == 'z')
            C[id]->deleteZ(predzel);
    }

    else if (C[id + 1]->n >= t)
    {
        int scsr;
        char scrzel;
        if (key != 'z')
            scsr = getSuccessor(id);
        if (key == 'z')
            scrzel = getSuccessorZ(id);
        int scsrx = getAttSuccessor(id, 'x');
        int scsry = getAttSuccessor(id, 'y');
        char scsrz = getAttSuccessorZ(id);

        attx[id] = scsrx;
        atty[id] = scsry;

        if (key != 'z')
        {
            Keys[id] = scsr;
            attz[id] = scsrz;
            C[id + 1]->deletion(scsr, key); //buna d abakilacak
        }
        if (key == 'z')
        {
            CharKeys[id] = scrzel;
            C[id + 1]->deleteZ(scrzel);
        }
    }

    else
    {

        if (key != 'z')
        {
            merge(id, 0);
            C[id]->deletion(k, key);
        }

        if (key == 'z')
        {
            merge(id, 1);
            C[id]->deleteZ(k);
        }
    }
    return;
}

int Node::getPredecessor(int id)
{
    Node *cur = C[id];
    while (!cur->leaf)
        cur = cur->C[cur->n];

    return cur->Keys[cur->n - 1];
}

char Node::getPredecessorZ(int id)
{
    Node *cur = C[id];
    while (!cur->leaf)
        cur = cur->C[cur->n];

    return cur->CharKeys[cur->n - 1];
}

int Node::getAttPredecessor(int id, char key)
{
    Node *cur = C[id];
    while (!cur->leaf)
        cur = cur->C[cur->n];

    if (key == 'x')
        ReturnData = cur->attx[cur->n - 1];
    if (key == 'y')
        ReturnData = cur->atty[cur->n - 1];

    return ReturnData;
}

char Node::getAttPredecessorZ(int id)
{
    Node *cur = C[id];
    while (!cur->leaf)
        cur = cur->C[cur->n];

    return cur->attz[cur->n - 1];
}

int Node::getSuccessor(int id)
{
    Node *cur = C[id + 1];
    while (!cur->leaf)
        cur = cur->C[0];

    return cur->Keys[0];
}

char Node::getSuccessorZ(int id)
{
    Node *cur = C[id + 1];
    while (!cur->leaf)
        cur = cur->C[0];

    return cur->CharKeys[0];
}

int Node::getAttSuccessor(int id, char key)
{
    Node *cur = C[id + 1];
    while (!cur->leaf)
        cur = cur->C[0];
    if (key == 'x')
        ReturnData = cur->attx[0];
    if (key == 'y')
        ReturnData = cur->atty[0];
    return ReturnData;
}
char Node::getAttSuccessorZ(int id)
{
    Node *cur = C[id + 1];
    while (!cur->leaf)
        cur = cur->C[0];

    return cur->attz[0];
}

void Node::fill(int id, int isZ)
{
    if (id != 0 && C[id - 1]->n >= t)
        borrowFromPrev(id, isZ);

    else if (id != n && C[id + 1]->n >= t)
        borrowFromNext(id, isZ);

    else
    {
        if (id != n)
            merge(id, isZ);
        else
            merge(id - 1, isZ);
    }
    return;
}

void Node::borrowFromPrev(int id, int isZ)
{
    Node *child = C[id];
    Node *sibling = C[id - 1];

    for (int i = child->n - 1; i >= 0; --i)
    {
        if (isZ == 0)
        {
            child->Keys[i + 1] = child->Keys[i];
            child->attz[i + 1] = child->attz[i];
        }

        if (isZ == 1)
            child->CharKeys[i + 1] = child->CharKeys[i];
        child->attx[i + 1] = child->attx[i];
        child->atty[i + 1] = child->atty[i];
    }

    if (!child->leaf)
    {
        for (int i = child->n; i >= 0; --i)
            child->C[i + 1] = child->C[i];
    }

    if (isZ == 0)
    {
        child->Keys[0] = Keys[id - 1];
        child->attz[0] = attz[id - 1];
    }
    if (isZ == 1)
        child->CharKeys[0] = CharKeys[id - 1];

    child->attx[0] = attx[id - 1];
    child->atty[0] = atty[id - 1];

    if (!child->leaf)
        child->C[0] = sibling->C[sibling->n];

    if (isZ == 0)
    {
        Keys[id - 1] = sibling->Keys[sibling->n - 1];
        attz[id - 1] = sibling->attz[sibling->n - 1];
    }
    if (isZ == 1)
        CharKeys[id - 1] = sibling->CharKeys[sibling->n - 1];

    attx[id - 1] = sibling->attx[sibling->n - 1];
    atty[id - 1] = sibling->atty[sibling->n - 1];

    child->n += 1;
    sibling->n -= 1;

    return;
}

void Node::borrowFromNext(int id, int isZ)
{
    Node *child = C[id];
    Node *sibling = C[id + 1];

    if (isZ == 0)
    {
        child->Keys[(child->n)] = Keys[id];
        child->attz[(child->n)] = attz[id];
    }
    if (isZ == 1)
        child->CharKeys[(child->n)] = CharKeys[id];

    child->attx[(child->n)] = attx[id];
    child->atty[(child->n)] = atty[id];

    if (!(child->leaf))
        child->C[(child->n) + 1] = sibling->C[0];

    if (isZ == 0)
    {
        Keys[id] = sibling->Keys[0];
        attz[id] = sibling->attz[0];
    }
    if (isZ == 1)
        CharKeys[id] = sibling->CharKeys[0];

    attx[id] = sibling->attx[0];
    atty[id] = sibling->atty[0];

    for (int i = 1; i < sibling->n; ++i)
    {
        if (isZ == 0)
        {
            sibling->Keys[i - 1] = sibling->Keys[i];
            sibling->attz[i - 1] = sibling->attz[i];
        }
        if (isZ == 1)
            sibling->CharKeys[i - 1] = sibling->CharKeys[i];

        sibling->attx[i - 1] = sibling->attx[i];
        sibling->atty[i - 1] = sibling->atty[i];
    }

    if (!sibling->leaf)
    {
        for (int i = 1; i <= sibling->n; ++i)
            sibling->C[i - 1] = sibling->C[i];
    }

    child->n += 1;
    sibling->n -= 1;

    return;
}

// Merge
void Node::merge(int id, int isZ)
{
    Node *child = C[id];
    Node *sibling = C[id + 1];

    if (isZ == 0)
    {
        child->Keys[t - 1] = Keys[id];
        child->attz[t - 1] = attz[id];
    }
    if (isZ == 1)
        child->CharKeys[t - 1] = CharKeys[id];

    child->attx[t - 1] = attx[id];
    child->atty[t - 1] = atty[id];

    for (int i = 0; i < sibling->n; ++i)
    {

        if (isZ == 0)
        {
            child->Keys[i + t] = sibling->Keys[i];
            child->attz[i + t] = sibling->attz[i];
        }
        if (isZ == 1)
            child->CharKeys[i + t] = sibling->CharKeys[i];

        child->attx[i + t] = sibling->attx[i];
        child->atty[i + t] = sibling->atty[i];
    }

    if (!child->leaf)
    {
        for (int i = 0; i <= sibling->n; ++i)
            child->C[i + t] = sibling->C[i];
    }

    for (int i = id + 1; i < n; ++i)
    {
        if (isZ == 0)
        {
            Keys[i - 1] = Keys[i];
            attz[i - 1] = attz[i];
        }
        if (isZ == 1)
            CharKeys[i - 1] = CharKeys[i];

        attx[i - 1] = attx[i];
        atty[i - 1] = atty[i];
    }

    for (int i = id + 2; i <= n; ++i)
        C[i - 1] = C[i];

    child->n += sibling->n + 1;
    n--;

    delete (sibling);
    return;
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
        cout << CharKeys[i] << ")";
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
        root->CharKeys[0] = z;
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
            if (s->CharKeys[0] < z)
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
        while (i >= 0 && CharKeys[i] > k)
        {
            CharKeys[i + 1] = CharKeys[i];
            attx[i + 1] = attx[i];
            atty[i + 1] = atty[i];
            i--;
        }

        CharKeys[i + 1] = k;
        attx[i + 1] = x;
        atty[i + 1] = y;
        n = n + 1;
    }
    else
    {
        while (i >= 0 && CharKeys[i] > k)
            i--;

        if (C[i + 1]->n == 2 * t - 1)
        {
            SplitZ(x, y, i + 1, C[i + 1]);
            if (CharKeys[i + 1] < k)
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
        z->CharKeys[j] = y->CharKeys[j + t];
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
        CharKeys[j + 1] = CharKeys[j];
        attx[j + 1] = attx[j];
        atty[j + 1] = atty[j];
    }

    CharKeys[i] = y->CharKeys[t - 1];
    attx[i] = y->attx[t - 1];
    atty[i] = y->atty[t - 1];
    n = n + 1;
}

void BTree::deletion(int k, char key)
{
    if (!root)
    {
        cout << "The tree is empty\n";
        return;
    }

    root->deletion(k, key);

    if (root->n == 0)
    {
        Node *tmp = root;
        if (root->leaf)
            root = NULL;
        else
            root = root->C[0];

        delete tmp;
    }
    return;
}

void BTree::deleteZ(char k)
{
    if (!root)
    {
        cout << "The tree is empty\n";
        return;
    }

    root->deleteZ(k);

    if (root->n == 0)
    {
        Node *tmp = root;
        if (root->leaf)
            root = NULL;
        else
            root = root->C[0];

        delete tmp;
    }
    return;
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

    switch (Key)
    {
    case 'x':
        int tbdx;
        cin >> tbdx;
        tree.deletion(tbdx, 'x');
        break;
    case 'y':
        int tbdy;
        cin >> tbdy;
        tree.deletion(tbdy, 'y');
        break;
    case 'z':
        char tbdz;
        cin >> tbdz;
        tree.deleteZ(tbdz);
        break;
    }

    if (Key == 'z')
        tree.traverseZ();
    else
        tree.traverse(Key);

    return 0;
}
