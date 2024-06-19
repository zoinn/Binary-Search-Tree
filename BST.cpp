#include "BST.h"

Node::Node(int i, std::string s, int d ,Node* p, Node *r, Node *l)
{
    key = i;
    data = s;
    rightChild = r;
    leftChild = l;
    depth = d;
    parent = p;
};

Dictionary::Dictionary()
{
    root = nullptr;
};

bool Dictionary::isEmpty()
{
    return (this->root == nullptr);
};

/*
void Dictionary::insert(int i, std::string s)
{
    Node *ptr = root;
    bool added = false;
    while (ptr != nullptr)
    {

        if (ptr->key == i)
        {
            ptr->data = s;
            ptr = nullptr;
            added = true;
        }

        else
        {
            if (ptr->rightChild > ptr->leftChild)
                ptr = ptr->rightChild;
            else
                ptr = ptr->leftChild;
        }
    }
    if (!added)
    {
        if (this->isEmpty())
        {
            root = new Node(i, s, 0);
        }
        else
        {
            Node *ptr = root;
            int depth = 1;
            while (ptr->rightChild != nullptr || ptr->leftChild != nullptr)
            {
                // std::cout << ptr << " -- pointer\n ";
                if (ptr->key < i)
                {
                    if (ptr->rightChild == nullptr)
                        break;
                    else
                    {
                        ptr = ptr->rightChild;
                        depth++;
                        //std::cout << ptr->rightChild << " -- right child\n";
                        // std::cout << ptr->key << ':' << i << '\n';
                    }
                }
                else if (ptr->key > i)
                {
                    if (ptr->leftChild == nullptr)
                        break;
                    else
                    {
                        ptr = ptr->leftChild;
                        depth++;
                        //std::cout << ptr->leftChild << " -- left child\n";
                    }
                    // std::cout << ptr->key << ':' << i << '\n';
                }
            }

            if (ptr->key > i)
            {
                //std::cout << depth << " - depth  " << i << " - left " << ptr->key << ':' << i << '\n';
                ptr->leftChild = new Node(i, s, depth);
                // std::cout << ptr->leftChild << " -- pointer added\n";
            }
            else if (ptr->key < i)
            {
                //std::cout << depth << " - depth  " << i << " - right " << ptr->key << ':' << i << '\n';
                // std::cout << "pointed --" << rightChild;
                ptr->rightChild = new Node(i, s, depth);
                // std::cout << ptr->rightChild << " -- pointer added\n";
            }
        }
    }
};


std::string *Dictionary::lookup(int i)
{
    Node *ptr = root;
    std::string *address = nullptr;
    while (ptr != nullptr)
    {
        if (ptr->key == i)
        {
            address = &ptr->data;
            ptr = nullptr;
        }

        else
            if (ptr->key > i && ptr->leftChild != nullptr)
                ptr = ptr->leftChild;
            else if (ptr->key < i && ptr->rightChild != nullptr)
                ptr = ptr->rightChild;
            else
                ptr = nullptr;
    };

    return address;
};
 */

void Dictionary::insert(int i, std::string s)
{
    insertWorker(root , nullptr ,i, s, 0);
};

void Dictionary::insertWorker(Node* currentNode, Node* parent,int i, std::string s, int depth)
{

    if (isEmpty())
    {
        root = new Node(i, s, depth, parent);
        currentNode = root;
    }
    else if (currentNode == nullptr )
    {
        currentNode = new Node(i, s, depth, parent);
        if (parent->key > i) parent->leftChild = currentNode;
        else  parent->rightChild = currentNode;
    }

    if (i < currentNode->key)
    {
        insertWorker(currentNode->leftChild, currentNode,  i, s, depth + 1);
    }
    else if (i > currentNode->key)
    {
        insertWorker(currentNode->rightChild,currentNode, i, s, depth + 1);
    }
    else
    {
        currentNode->data = s;
    }
};

std::string *Dictionary::lookup(int i)
{
    return lookupWorker(root ,i);
};


std::string* Dictionary::lookupWorker(Node* currentNode, int i)
{
    if (currentNode == nullptr)
    {
        return nullptr;
    }

    if (currentNode->key == i)
    {
        return &currentNode->data;
    }
    else if (currentNode->key > i)
    {
        return lookupWorker(currentNode->leftChild, i);
    }
    else
    {
        return lookupWorker(currentNode->rightChild, i);
    }

};

Node* Dictionary::lookupNode(int i)
{
    return lookupNodeWorker(root ,i);
};


Node* Dictionary::lookupNodeWorker(Node* currentNode, int i)
{
    if (currentNode == nullptr)
    {
        return nullptr;
    }

    if (currentNode->key == i)
    {
        return currentNode;
    }
    else if (currentNode->key > i)
    {
        return lookupNodeWorker(currentNode->leftChild, i);
    }
    else
    {
        return lookupNodeWorker(currentNode->rightChild, i);
    }

};

void Dictionary::remove(int i)
{
    removeWorker(root,i);
};
void Dictionary::removeWorker(Node* currentNode, int i)
{
    if (currentNode == nullptr) return;

    if (i < currentNode->key)
    {
            removeWorker(currentNode->leftChild, i);
    }
    else if (i > currentNode->key)
    {
            removeWorker(currentNode->rightChild, i);
    }
    else
    {
            if (currentNode->leftChild == nullptr && currentNode->rightChild == nullptr)
            {
                //Node has no children
                if (currentNode->parent != nullptr)
                {
                    if (currentNode->parent->leftChild == currentNode)
                    {
                        currentNode->parent->leftChild = nullptr;
                    }
                    else
                    {
                        currentNode->parent->rightChild = nullptr;
                    }
                }
                delete currentNode;
            }
            else if (currentNode->leftChild == nullptr)
            {
                //Node has only a right child
                if (currentNode->parent != nullptr)
                {
                    if (currentNode->parent->leftChild == currentNode)
                    {
                        currentNode->rightChild->depth = currentNode->depth;
                        currentNode->parent->leftChild = currentNode->rightChild;
                    }
                    else
                    {
                        currentNode->leftChild->depth = currentNode->depth;
                        currentNode->parent->rightChild = currentNode->rightChild;
                    }
                }
                currentNode->rightChild->parent = currentNode->parent;
                Node* tempNode = currentNode;
                delete tempNode;
            }
            else if (currentNode->rightChild == nullptr)
            {
                //Node has only a left child
                if (currentNode->parent != nullptr)
                {
                    if (currentNode->parent->leftChild == currentNode)
                    {
                        currentNode->leftChild->depth = currentNode->depth;
                        currentNode->parent->leftChild = currentNode->leftChild;
                    }
                    else
                    {
                        currentNode->rightChild->depth = currentNode->depth;
                        currentNode->parent->rightChild = currentNode->leftChild;
                    }
                }
                currentNode->leftChild->parent = currentNode->parent;
                Node* tempNode = currentNode;
                delete tempNode;
            }
            else //Node has both children
            {
                Node* newParent = findInheritor(currentNode->rightChild);
                currentNode->key = newParent->key;
                removeWorker(currentNode->rightChild, newParent->key);
            }
    }
};

Node* Dictionary::findInheritor(Node* currentNode)
{
    if (currentNode == nullptr)
    {
        return nullptr;
    }

    while (currentNode->leftChild != nullptr)
    {
        currentNode = currentNode->leftChild;
    }

    return currentNode;
};

void Dictionary::displayEntries()
{
    displayEntriesWorker(root);
}

void Dictionary::displayEntriesWorker(Node* currentNode)
{
    if (currentNode == nullptr) return;

    // Pre-order
    //std::cout << "Key : " << currentNode->key << " | Data : " << currentNode->data << '\n';

    displayEntriesWorker(currentNode->leftChild);

    // In-order
    std::cout << "Key : " << currentNode->key << " | Data : " << currentNode->data << '\n';

    displayEntriesWorker(currentNode->rightChild);

    // Post-order
    //std::cout << "Key : " << currentNode->key << " | Data : " << currentNode->data << '\n';

}

void Dictionary::displayTree()
{
    displayTreeWorker(root);
}

void Dictionary::displayTreeWorker(Node* currentNode)
{
    if (currentNode == nullptr) return;

    // Pre-order
    std::cout << std::string(currentNode->depth*2, '~') << currentNode->key << " | " << currentNode->data << '\n';

    displayTreeWorker(currentNode->leftChild);

    // In-order
    //std::cout << std::string(currentNode->depth*2, ' ') << currentNode->key << " | " << currentNode->data << '\n';


    displayTreeWorker(currentNode->rightChild);

    // Post-order
    //std::cout << std::string(currentNode->depth*2, ' ') << currentNode->key << " | " << currentNode->data << '\n';

}

//DEEP DELETE DESTRUCTOR
Dictionary::~Dictionary()
{
    deepDeleteWorker(root);
};

void Dictionary::deepDeleteWorker(Node* currentNode)
{
    if (currentNode == nullptr) return;

    // Pre-order

    deepDeleteWorker(currentNode->leftChild);

    // In-order

    deepDeleteWorker(currentNode->rightChild);

    // Post-order
    //std::cout << "Deleting node with key: " << currentNode->key << std::endl;

    delete currentNode;
    //std::cout << "Key : " << currentNode->key << " | Data : " << currentNode->data << '\n';
}

//DEEP COPY
Dictionary::Dictionary(const Dictionary& dic)
{
    root = nullptr;

    deepCopyWorker(dic.root);

};

void Dictionary::deepCopyWorker(Node* currentNode)
{
    if (currentNode == nullptr) return;

    // Pre-order
    insert(currentNode->key, currentNode->data);
    //std::cout << "Key : " << currentNode->key << " | Data : " << currentNode->data << '\n';

    deepCopyWorker(currentNode->leftChild);

    // In-order

    deepCopyWorker(currentNode->rightChild);

    // Post-order
};

void Dictionary::rotateRight(Node* pivotNode)
{
    Node* tempNode = pivotNode->leftChild;
    // Case: If root
    if (pivotNode->parent == nullptr) root = tempNode;
    //Case : If not Root
    else if(pivotNode->key < pivotNode->parent->key)
    {
        pivotNode->parent->leftChild = tempNode;
    }
    else
    {
        pivotNode->parent->rightChild = tempNode;
    }

    pivotNode->leftChild = tempNode->rightChild;

    tempNode->rightChild = pivotNode;

    tempNode->parent = pivotNode->parent;

    pivotNode->parent = tempNode;

    updateDepth(root, 0);
};

void Dictionary::rotateLeft(Node* pivotNode)
{
    Node* tempNode = pivotNode->rightChild;

    if (pivotNode->parent == nullptr) root = tempNode;

    else if(pivotNode->key < pivotNode->parent->key)
    {
        pivotNode->parent->leftChild = tempNode;
    }
    else
    {
        pivotNode->parent->rightChild = tempNode;
    }

    pivotNode->rightChild = tempNode->leftChild;

    tempNode->leftChild = pivotNode;

    tempNode->parent = pivotNode->parent;

    pivotNode->parent = tempNode;

    updateDepth(root, 0);
};

void Dictionary::updateDepth(Node* currentNode,int currentDepth)
{
    if (currentNode == nullptr) return;

    currentNode->depth = currentDepth;

    updateDepth(currentNode->leftChild, currentDepth + 1);

    updateDepth(currentNode->rightChild, currentDepth + 1);
}

Dictionary::Dictionary(Dictionary && dic)
{
    if (root != dic.root)
    {
        this->~Dictionary();
        this->root = dic.root;
        dic.root->leftChild = nullptr;
        dic.root->rightChild = nullptr;
    }
}

Dictionary & Dictionary::operator=(const Dictionary && source)
{
    this->root = std::move(source.root);
    return *this;
}

Dictionary & Dictionary::operator=(const Dictionary & source)
{
    Dictionary copiedDic(source);
    return copiedDic;
}

void Dictionary::removeIf(Node* currentNode ,std::function<bool(int)> predicate) {

    if (currentNode == nullptr) return;

    removeIf(currentNode->leftChild, predicate);

    removeIf(currentNode->rightChild, predicate);

    if (predicate(currentNode->key)) remove(currentNode->key);


}

bool isEven(int key)
{
    if (key % 2 == 0) return true;

    else return false;
}

bool isOdd(int key)
{
    if (key % 2 != 0) return true;

    else return false;
}

Node *Dictionary::getRoot() {
    return root;
}

int main()
{
    return 0;
};


