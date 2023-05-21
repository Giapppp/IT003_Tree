#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    int data;
    Node *parent, *left, *right;
    int color;
};

class RedBlackTree
{
protected:
    Node *root, *TNULL;
    void rbTransplant(Node *u, Node *v)
    {
        if (u->parent == nullptr)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;
        v->parent = u->parent;
    }

public:
    RedBlackTree()
    {
        TNULL = new Node;
        TNULL->color = 0;
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        root = TNULL;
    }

    Node *minimum(Node *node)
    {
        while (node->left != TNULL)
        {
            node = node->left;
        }
        return node;
    }

    Node *getRoot()
    {
        return this->root;
    }

    void leftRotate(Node *node)
    {
        Node *y = node->right;
        node->right = y->left;
        if (y->left != TNULL)
            y->left->parent = node;
        y->parent = node->parent;
        if (node->parent == nullptr)
            this->root = y;
        else if (node == node->parent->left)
            node->parent->left = y;
        else
            node->parent->right = y;
        y->left = node;
        node->parent = y;
    }

    void rightRotate(Node *node)
    {
        Node *y = node->left;
        node->left = y->right;
        if (y->right != TNULL)
            y->right->parent = node;
        y->parent = node->parent;
        if (node->parent == nullptr)
            this->root = y;
        else if (node == node->parent->right)
            node->parent->right = y;
        else
            node->parent->left = y;
        y->right = node;
        node->parent = y;
    }

    void insert(int data)
    {
        Node *node = new Node;
        node->parent = nullptr;
        node->data = data;
        node->left = TNULL;
        node->right = TNULL;
        node->color = 1;

        Node *y = nullptr;
        Node *x = this->root;

        while (x != TNULL)
        {
            y = x;
            if (node->data < x->data)
                x = x->left;
            else
                x = x->right;
        }

        node->parent = y;
        if (y == nullptr)
            root = node;
        else if (node->data < y->data)
            y->left = node;
        else
            y->right = node;

        if (node->parent == nullptr)
        {
            node->color = 0;
            return;
        }

        if (node->parent->parent == nullptr)
            return;

        Node *u;
        while (node->parent->color == 1)
        {
            if (node->parent == node->parent->parent->right)
            {
                u = node->parent->parent->left;
                if (u->color == 1)
                {
                    u->color = 0;
                    node->parent->color = 0;
                    node->parent->parent->color = 1;
                    node = node->parent->parent;
                }
                else
                {
                    if (node == node->parent->left)
                    {
                        node = node->parent;
                        rightRotate(node);
                    }
                    node->parent->color = 0;
                    node->parent->parent->color = 1;
                    leftRotate(node->parent->parent);
                }
            }
            else
            {
                u = node->parent->parent->right;

                if (u->color == 1)
                {
                    u->color = 0;
                    node->parent->color = 0;
                    node->parent->parent->color = 1;
                    node = node->parent->parent;
                }
                else
                {
                    if (node == node->parent->right)
                    {
                        node = node->parent;
                        leftRotate(node);
                    }
                    node->parent->color = 0;
                    node->parent->parent->color = 1;
                    rightRotate(node->parent->parent);
                }
            }
            if (node == root)
                break;
        }
        root->color = 0;
    }

    void deleteNode(Node *node, int data)
    {
        Node *z = TNULL, *x, *y;
        while (node != TNULL)
        {
            if (node->data == data)
                z = node;
            if (node->data <= data)
                node = node->right;
            else
                node = node->left;
        }

        if (z == TNULL)
        {
            cout << "Data not found in the tree" << endl;
            return;
        }

        y = z;
        int yOriginalColor = y->color;
        if (z->left == TNULL)
        {
            x = z->right;
            rbTransplant(z, z->right);
        }
        else if (z->right == TNULL)
        {
            x = z->left;
            rbTransplant(z, z->left);
        }
        else
        {
            y = minimum(z->right);
            yOriginalColor = y->color;
            x = y->right;
            if (y->parent == z)
                x->parent = y;
            else
            {
                rbTransplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            rbTransplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        if (yOriginalColor == 0)
        {
            Node *s;
            while (x != root && x->color == 0)
            {
                if (x == x->parent->left)
                {
                    s = x->parent->right;
                    if (s->color == 1)
                    {
                        s->color = 0;
                        x->parent->color = 1;
                        leftRotate(x->parent);
                        s = x->parent->right;
                    }

                    if (s->left->color == 0 && s->right->color == 0)
                    {
                        s->color = 1;
                        x = x->parent;
                    }
                    else
                    {
                        if (s->right->color == 0)
                        {
                            s->left->color = 0;
                            s->color = 1;
                            rightRotate(s);
                            s = x->parent->right;
                        }

                        s->color = x->parent->color;
                        x->parent->color = 0;
                        s->right->color = 0;
                        leftRotate(x->parent);
                        x = root;
                    }
                }
                else
                {
                    s = x->parent->left;
                    if (s->color == 1)
                    {
                        s->color = 0;
                        x->parent->color = 1;
                        rightRotate(x->parent);
                        s = x->parent->left;
                    }

                    if (s->right->color == 0 && s->right->color == 0)
                    {
                        s->color = 1;
                        x = x->parent;
                    }
                    else
                    {
                        if (s->left->color == 0)
                        {
                            s->right->color = 0;
                            s->color = 1;
                            leftRotate(s);
                            s = x->parent->left;
                        }

                        s->color = x->parent->color;
                        x->parent->color = 0;
                        s->left->color = 0;
                        rightRotate(x->parent);
                        x = root;
                    }
                }
            }
            x->color = 0;
        }
    }

    void preOrder(Node *node)
    {
        if (node != TNULL)
        {
            cout << node->data << " ";
            preOrder(node->left);
            preOrder(node->right);
        }
    }
};

int height(Node *root)
{
    if (root == NULL)
        return 0;
    else
        return max(height(root->left), height(root->right)) + 1;
}

int main()
{
    ifstream fi;
    ofstream fo("result_RB.txt");

    for (int t = 1; t <= 10; t++)
    {
        RedBlackTree RBTree;
        string fileInp = "test_" + to_string(t) + ".txt";
        fi.open(fileInp);
        if (fi.is_open())
            for (int i = 0; i < 1000000; i++)
            {
                int x;
                fi >> x;
                RBTree.insert(x);
            }
        fo << height(RBTree.getRoot()) << '\n';
    }
}