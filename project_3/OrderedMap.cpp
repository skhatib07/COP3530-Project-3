#include <chrono>
#include <thread>
#include "OrderedMap.h"

OrderedMap::OrderedMap() {
    root = nullptr;
    _size = 0;
}

OrderedMap::OrderedMap(float key, string val) {
    insert(key, val);
    _size = 1;
}

OrderedMap::OrderedMap(Node* _root) {
    root = _root;
    _size = 1;
}

void OrderedMap::insert(Node* node, Node* in, float key) {
    float nodeKey = node->key();
    if (nodeKey == key)
    {
        node->push_back(make_pair(key,in->vals.front().second));
        *in = *node;
        return;
    }
    else if (nodeKey > key)
    {
        if (!node->left)
        {
            node->left = in;
            in->AssignParent(node);
            _size++;
            return;
        }
        else
            insert(node->left, in, key);
    }
    else if (nodeKey < key)
    {
        if (!node->right)
        {
            node->right = in;
            in->AssignParent(node);
            _size++;
            return;
        }
        else
            insert(node->right, in, key);
    }
}

void OrderedMap::insert(float key, string val) {
    if (!root) {
        Node* in = new Node(key, val, false);
        root = in;
        _size = 1;
        return;
    }
    
    Node* in = new Node(key, val, true);
    float rootKey = root->key();
    if (rootKey == key)
    {
        root->push_back(make_pair(key, val));
        *in = *root;
        return;
    }
    else if (rootKey > key)
    {
        if (!root->left)
        {
            root->left = in;
            in->parent = root;
            _size++;
            return;
        }
        else
            insert(root->left, in, key);
    }
    else if (rootKey < key)
    {
        if (!root->right)
        {
            root->right = in;
            in->parent = root;
            _size++;
            return;
        }
        else
            insert(root->right, in, key);
    }

    TreeBalance(in);
}

void OrderedMap::insert(vector<pair<float, string>> inserts) {
    for (int i = 0; i < inserts.size(); i++){
        insert(inserts.at(i).first, inserts.at(i).second);
    }
}

void OrderedMap::TreeRecolor(Node* node) {
    if (node == root) {
        node->MakeBlack();
        return;
    }
    else if(!node || node->parent == root)
        return;

    node->getUncle()->MakeBlack();
    node->parent->MakeBlack();
    node->parent->parent->MakeRed();

    TreeRecolor(node->parent->parent);
}

Node* OrderedMap::RotateRight(Node* node) {
    Node* temp = node->left;
    Node* tempRight = temp->right;

    node->left = tempRight;
    tempRight->AssignParent(node);
    temp->right = node;
    node->AssignParent(temp);
    return temp;
}

Node* OrderedMap::RotateLeft(Node* node) {
    Node* temp = node->right;
    Node* tempLeft = temp->left;

    node->right = tempLeft;
    tempLeft->AssignParent(node);
    temp->left = node;
    node->AssignParent(temp);
    return temp;
}

void OrderedMap::TreeBalance(Node* node) {
    if (node == root || node->parent == root)
        return;


    if (node->red && node->parent->red) {
        Node* uncle = node->getUncle();
        // Uncle is Red Case
        if (uncle && uncle->red) {
            TreeRecolor(node);
        }
        else if (!uncle || uncle->black) {

            // Left Left Case
            if (node->parent->red && node->parent->parent->left == node->parent && node->parent->left == node) {
                Node* grandParent = node->parent->parent;
                Node* greatGrandParent = grandParent->parent;
                node->AssignParent(RotateRight(grandParent));
                Node* parent = node->parent;
                parent->MakeBlack();
                parent->right->MakeRed();
                parent->left = node;

                if (root == grandParent) {
                    root = parent;
                    parent->AssignParent(nullptr);
                }
                else {
                    float parentKey = parent->key();
                    float greatGrandParentKey = greatGrandParent->key();
                    if (parentKey > greatGrandParentKey) {
                        greatGrandParent->right = parent;
                        parent->AssignParent(greatGrandParent);
                    }
                    else if (parentKey < greatGrandParentKey) {
                        greatGrandParent->left = parent;
                        parent->AssignParent(greatGrandParent);
                    }
                }
            }
            //Left Right Case
            else if (node->parent->red && node->parent->parent->left == node->parent && node->parent->right == node) {
                Node* parent = node->parent;
                Node* grandParent = parent->parent;

                grandParent->left = node;
                node->AssignParent(grandParent);
                Node* savNode = parent->left;
                parent->left = node->left;
                node->left->AssignParent(parent);
                parent->right = node->right;
                node->right->AssignParent(parent);

                node->left = parent;
                parent->AssignParent(node);
                node->right = savNode;
                savNode->AssignParent(node);


                parent = node->parent;
                grandParent = parent->parent;
                node = RotateRight(parent);
                node->MakeBlack();
                parent->MakeRed();
                node->right = parent;

                if (root == parent) {
                    root = node;
                    node->AssignParent(nullptr);
                }
                else {
                    float nodeKey = node->key();
                    float grandParentkey = grandParent->key();
                    if (nodeKey > grandParentkey) {
                        grandParent->right = node;
                        node->AssignParent(grandParent);
                    }
                    else if (nodeKey < grandParentkey) {
                        grandParent->left = node;
                        node->AssignParent(grandParent);
                    }
                }

            }
            // Right Right Case
            else if (node->parent->red && node->parent->parent->right == node->parent && node->parent->right == node) {
                Node* grandParent = node->parent->parent;
                Node* greatGrandParent = grandParent->parent;
                node->AssignParent(RotateLeft(grandParent));
                Node* parent = node->parent;
                parent->MakeBlack();
                parent->left->MakeRed();
                parent->right = node;

                if (root == grandParent) {
                    root = parent;
                    parent->AssignParent(nullptr);
                }
                else {
                    float parentKey = parent->key();
                    float greatGrandParentKey = greatGrandParent->key();
                    if (parentKey > greatGrandParentKey) {
                        greatGrandParent->right = parent;
                        parent->AssignParent(greatGrandParent);
                    }
                    else if (parentKey < greatGrandParentKey) {
                        greatGrandParent->left = parent;
                        parent->AssignParent(greatGrandParent);
                    }
                }
            }
            // Right Left Case
            else if (node->parent->red && node->parent->parent->right == node->parent && node->parent->left == node) {
                Node* parent = node->parent;
                Node* grandParent = parent->parent;

                grandParent->right = node;
                node->AssignParent(grandParent);
                parent->left = node->right;
                node->right->AssignParent(parent);

                node->right = parent;
                parent->AssignParent(node);


                parent = node->parent;
                grandParent = parent->parent;
                node = RotateLeft(parent);
                node->MakeBlack();
                parent->MakeRed();
                node->left = parent;

                if (root == parent) {
                    root = node;
                    node->AssignParent(nullptr);
                }
                else {
                    float nodeKey = node->key();
                    float grandParentKey = grandParent->key();
                    if (nodeKey > grandParentKey) {
                        grandParent->right = node;
                        node->AssignParent(grandParent);
                    }
                    else if (nodeKey < grandParentKey) {
                        grandParent->left = node;
                        node->AssignParent(grandParent);
                    }
                }
            }
        }
    }
}

void OrderedMap::traverseInorder(Node* node, vector<Node*>* traversal)
{
    if (!node)
        return;
    traverseInorder(node->left, traversal);
    traversal->push_back(node);
    traverseInorder(node->right, traversal);
}

vector<Node*> OrderedMap::inorderVector() {
    vector<Node*> inorderTransverse;
    if (!root)
        return inorderTransverse;
    traverseInorder(root, &inorderTransverse);
    return inorderTransverse;
}

const int& OrderedMap::size() { return _size; }

void OrderedMap::deletePostorder(Node* node) {
    if (!node)
        return;
    deletePostorder(node->left);
    deletePostorder(node->right);
    delete node;
}

OrderedMap::~OrderedMap() {
    _size = 0;
    deletePostorder(root);
}

