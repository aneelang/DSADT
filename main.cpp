#include<iostream>
#include<set>
#include<vector>

using namespace std;

// Binary Search Tree

class BST{
    int data;
    BST* left, *right;

public:
    BST();
    BST(int value);
    BST* Insert(BST* root, int value);
    BST* deleteNode(BST* root, int value);
    BST* minValueNode(BST* node);
    void InOrder(BST* root);
    BST* search(BST* root, int value);
};

BST::BST(): data(0), left(nullptr), right(nullptr){}
BST::BST(int value){
    data = value;
    left = nullptr;
    right = nullptr;
}

BST* BST::Insert(BST* root, int value){
    if(!root)
        return new BST(value);
    if(root->data < value)
        root->right = Insert(root->right, value);
    else if(root->data > value)
        root->left = Insert(root->left, value);
    return root;
}

BST* BST::deleteNode(BST *root, int value) {
    if(!root)
        return nullptr;
    if(root->data < value)
        root->right = deleteNode(root->right, value);
    else if(root->data > value)
        root->left = deleteNode(root->left, value);
    else{
        if(root->left == nullptr && root->right == nullptr)
            return nullptr;
        else if(root->left == nullptr){
            BST* temp = root->right;
            free(root);
            return temp;
        }
        else if(root->right == nullptr){
            BST* temp = root->left;
            free(root);
            return temp;
        }
        BST* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

BST* BST::minValueNode(BST *node) {
    BST* current = node;
    if(current && current->left!= nullptr){
        current = current->left;
    }
    return current;
}

BST* BST::search(BST *root, int value) {
    if(root== nullptr|| root->data == value)
        return root;
    if(root->data < value)
        return search(root->right, value);
    return search(root->left, value);
}

void BST::InOrder(BST *root) {
    if(!root)
        return ;
    InOrder(root->left);
    cout<<root->data<<" ";
    InOrder(root->right);
}

// Linked List
template<class T>
class LinkedList{
    struct Node{
        T data;
        Node* next;
        Node(T val): data(val), next(nullptr){}
    };
    Node* head;
    int totalNumberOfElements = 0;

public:
    LinkedList(): head(nullptr){}
    LinkedList(const LinkedList<T> & ll) = delete;
    LinkedList & operator = (const LinkedList<T> &) = delete;
    ~LinkedList(){
        Node* temp = nullptr;
        while(head){
            temp = head;
            head = head->next;
            delete temp;
        }
        head = nullptr;
    }

    void Insert(T val){
        Node* temp = head;
        Node* newNode = new Node(val);
        if(temp == nullptr)
            head = newNode;
        else{
            while(temp->next!= nullptr){
                temp = temp->next;
            }
            temp->next = newNode;
        }
        totalNumberOfElements++;
    }

    void deleteNode(T val){
        cout<<"Deleting Node\n";
        Node* node = search(val);
        Node* temp = head;
        if(temp == node){
            head = temp->next;
        }
        else if(node!= nullptr){
            while(node!= nullptr){
                if(temp->next == node){
                    temp->next = node->next;
                    return ;
                }
                temp = temp->next;
            }
        }
    }

    void printKthNode(int pos){
        cout<<"Printing Kth to Last Node\n";
        Node* node = getKthNode(pos);
        while(node!= nullptr){
            cout<<node->data<<" ";
            node=node->next;
        }
        cout<<"\n";
    }

    template<class U>
    friend::ostream & operator<<(ostream & os, LinkedList<U> & ll);
    void deleteMiddleNode(){
        Node* node = head;
        Node* previous = nullptr;
        Node* temp = head;

        int counter = 0;

        while(node!= nullptr){
            counter++;
            node = node->next;
        }

        for(int i = 0; i < counter / 2; i++){
            previous = temp;
            temp = temp->next;
        }

        previous->next = temp->next;
        totalNumberOfElements--;
    }
    void removeDuplicates(){
        cout<<"Removing Duplicates\n";
        Node* temp = head;
        set<int> s;
        Node* previous = nullptr;
        while(temp!= nullptr){
            auto pos = s.find(temp->data);
            if(pos!=s.end())
                previous->next = temp->next;
            else{
                s.insert(temp->data);
                previous = temp;
            }
            temp = temp->next;
        }
    }
private:
    struct Node* search(T val){
        Node* temp = head;
        while(temp!= nullptr){
            if(temp->data == val)
                return temp;
            temp = temp->next;
        }
        cerr<<"Element not found\n";
        return nullptr;
    }
    struct Node* getKthNode(int pos){
        Node* p1 = head;
        Node* p2 = head;

        for(int i = 0; i < pos; i++){
            if(p1 == nullptr)
                return nullptr;
            p1 = p1->next;
        }

        while(p1!= nullptr){
            p1 = p1->next;
            p2 = p2->next;
        }
        return p2;
    }
    void display(ostream & out = cout) const{
        Node* node = head;
        while(node){
            out<<node->data<<" ";
            node = node->next;
        }
        out<<endl;
    }

};

template<class U>
ostream & operator<<(ostream & os, LinkedList<U> & ll){
    ll.display(os);
    return os;
}

int main(void){
    BST b, *root = nullptr;
    root = b.Insert(root, 50);
    b.Insert(root, 30);
    b.Insert(root, 20);
    b.Insert(root, 20);
    b.Insert(root, 40);
    b.Insert(root, 70);
    b.Insert(root, 60);
    b.Insert(root, 80);

    b.search(root, 80);
    b.InOrder(root);
    cout<<"\n";
    b.deleteNode(root, 60);
    b.InOrder(root);

    LinkedList<int> ll1;
    ll1.Insert(10);
    ll1.Insert(12);
    ll1.Insert(15);
    ll1.Insert(14);
    ll1.Insert(13);
    ll1.Insert(16);
    ll1.Insert(15);
    cout<<endl<<ll1<<endl;
    ll1.removeDuplicates();
    cout<<ll1<<endl;
    ll1.deleteNode(14);
    cout<<ll1<<endl;
    ll1.printKthNode(3);
    ll1.deleteMiddleNode();
    cout<<ll1<<endl;


}
