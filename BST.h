#include <iostream>
#include <functional>

struct Node
{
    Node(int, std::string, int ,Node*, Node * = nullptr, Node * = nullptr);
    int key;
    int depth;
    std::string data;
    Node *rightChild;
    Node *leftChild;
    Node* parent;
};

class Dictionary
{
public:
    Dictionary();

    Dictionary(const Dictionary &);

    Dictionary(Dictionary &&);

    Dictionary & operator=(const Dictionary &);

    Dictionary & operator=(const Dictionary &&);

    ~Dictionary();

    std::string *lookup(int);

    Node* lookupNode(int);

    void removeIf(Node*, std::function<bool(int)>);

    bool isEven(int);

    bool isOdd(int);

    void displayEntries();

    void displayTree();

    bool isEmpty();

    void insert(int, std::string);

    void remove(int);

    Node* getRoot();


private:
    void deepDeleteWorker(Node*);

    void deepCopyWorker(Node*);

    void displayEntriesWorker(Node*);

    void displayTreeWorker(Node*);

    void insertWorker(Node*,Node*,int, std::string,int);

    void removeWorker(Node*, int);

    void updateDepth(Node*, int);

    void rotateLeft(Node*);

    void rotateRight(Node*);

    Node* findInheritor(Node*);

    std::string* lookupWorker(Node*, int);

    Node* lookupNodeWorker(Node*,int);

    Node *root;
};
