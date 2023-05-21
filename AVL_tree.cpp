#include <bits/stdc++.h>
using namespace std;

#define RH 1
#define EH 0
#define LH -1

class Node
{
public:
    int data;
    Node *left, *right;
    int height;
};

int height(Node *node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

int getBalanceFactor(Node *node)
{
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

Node *newNode(int data)
{
    Node *node = new Node();
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return (node);
}

Node *leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

Node *maxValueNode(Node *root)
{
    Node *current = root;

    while (current->right != NULL)
        current = current->right;

    return current;
}

Node *insertNode(Node *node, int data)
{

    if (node == NULL)
        return (newNode(data));

    if (data < node->data)
        node->left = insertNode(node->left, data);
    else if (data > node->data)
        node->right = insertNode(node->right, data);

    /*----------------------------------------------------------------------------------*/

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalanceFactor(node);

    // Cay con trai lech trai
    if (balance > RH && data < node->left->data)
        return rightRotate(node);

    // Cay con trai lech phai
    if (balance > RH && data > node->left->data)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Cay con phai lech trai
    if (balance < LH && data < node->right->data)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Cay con phai lech phai
    if (balance < LH && data > node->right->data)
        return leftRotate(node);

    return node;
}

Node *deleteNode(Node *root, int data)
{

    if (root == NULL)
        return root;

    if (data > root->data)
        root->right = deleteNode(root->right, data);
    else if (data < root->data)
        root->left = deleteNode(root->left, data);
    else // Nếu data có giá trị bằng với root->data thì đây chính là Node cần xóa
    {
        // Trường hợp 0 con hoặc 1 con
        if (root->left == NULL || root->right == NULL)
        {
            // Sử dụng Node temp để kiểm tra
            Node *temp = root->left;
            if (root->right != NULL)
                temp = root->right;

            if (temp == NULL) // TH: 0 con - No child case
            {
                temp = root;
                root = NULL;
                delete temp;
            }
            else // TH: 1 con - One child case
            {
                // Gán tất cả các giá trị (bao gồm left, right, height) của temp vào root
                *root = *temp;
                delete temp;
            }
        }
        else // Trường hợp 2 con - Two child case
        {
            // Tìm Node lớn nhất bên trái (nhỏ nhất bên phải)
            Node *temp = maxValueNode(root->left);

            // Đưa data của temp vào root
            root->data = temp->data;

            // Xóa temp như 2 TH trên - Delete the inorder successor
            root->right = deleteNode(root->right, temp->data);
        }
    }

    // Nếu không còn gì thì trả về luôn !!
    if (root == NULL)
        return root;

    // 2. CẬP NHẬT CHIỀU CAO - UPDATE HEIGHT OF THE CURRENT NODE
    root->height = 1 + max(height(root->left), height(root->right));

    // 3. CÂN BẰNG CÂY - GET THE BALANCE FACTOR
    int valBalance = getBalanceFactor(root);

    // Case 1: Left left - Trái trái
    if (valBalance > 1 && getBalanceFactor(root->left) >= 0)
        return rightRotate(root);

    // Case 2: Right right - Phải phải
    if (valBalance < -1 && getBalanceFactor(root->right) <= 0)
        return leftRotate(root);

    // Case 3: Left right - Trái phải
    if (valBalance > 1 && getBalanceFactor(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Case 4: Right left - Phải trái
    if (valBalance < -1 && getBalanceFactor(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void preOrder(Node *root)
{
    if (root != NULL)
    {
        cout << root->data << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

int main()
{
    Node *root = NULL;

    ifstream fi;
    ofstream fo("result_AVL.txt");

    for (int i = 0; i < 10; i++)
    {
        string fileInp = "test_" + to_string(i) + ".txt";
        fi.open(fileInp);
        if (fi.is_open())
            for (int i = 0; i < 1000000; i++)
            {
                int data;
                fi >> data;
                root = insertNode(root, data);
            }
        // preOrder(root);
        fo << height(root) << "\n";
    }
    fo.close();
    return 0;
}
