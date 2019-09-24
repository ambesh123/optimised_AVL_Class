                      //  @ /\/\ BESH //

#include <bits/stdc++.h>


using namespace std;

template<typename T>
class AVL{
    private :
    struct node{
        T val;
        node *left;
        node *right;
        int height;
        int size;
        int count;
        node(T x){
            left = NULL;
            right = NULL;
            size = 1;
            height = 0;
            count = 1;
            val = x;
        }
    };

    int getHeight(node *p){
        if(p == NULL)return -1;
        return p->height;
    }

    int getSize(node *p){
        if(p == NULL)return 0;
        return p->size;
    }

    node *root;

    node *insert(node *root, T val){
        if(root == NULL)return new node(val);

        if(val > root->val) root->right = insert(root->right, val);
        else if(val < root->val) root->left = insert(root->left, val);
        else root->count++;

        int bf = getHeight(root->left) - getHeight(root->right);


        if(bf > 1){
            if(val < root->left->val){  //LL Rotation
                node *newRoot= root->left;
                root->left = newRoot->right;
                newRoot->right = root;

                root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
                root->size = getSize(root->left) + getSize(root->right) + root->count;

                root = newRoot;
            }
            else{   //LR  Rotation
                node *newRoot = root->left->right;
                root->left->right = newRoot->left;
                newRoot->left = root->left;

                root->left->height = max(getHeight(root->left->left), getHeight(root->left->right)) + 1;
                root->left->size = getSize(root->left->left) + getSize(root->left->right) + root->left->count;

                root->left = newRoot->right;
                newRoot->right = root;

                root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
                root->size = getSize(root->left) + getSize(root->right) + root->count;

                root = newRoot;
            }
        }
        else if(bf < -1){
            if(val > root->right->val){ //RR Rotation
                node *newRoot = root->right;
                root->right = newRoot->left;
                newRoot->left = root;

                root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
                root->size = getSize(root->left) + getSize(root->right) + root->count;

                root = newRoot;
            }
            else{   //RL Rotation
                node *newRoot = root->right->left;
                root->right->left = newRoot->right;
                newRoot->right = root->right;

                root->right->height = max(getHeight(root->right->left), getHeight(root->right->right)) + 1;
                root->right->size = getSize(root->right->left) + getSize(root->right->right) + root->right->count;

                root->right = newRoot->left;
                newRoot->left = root;

                root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
                root->size = getSize(root->left) + getSize(root->right) + root->count;

                root = newRoot;
            }
        }

        root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
        root->size = getSize(root->left) + getSize(root->right) + root->count;

        return root;

    }

    node *deleteAll(node *root, T val){
        if(root == NULL)return root;

        if(val == root->val){
            if(root->right != NULL && root->left != NULL){
                node *crawl = root->right;
                while(crawl->left)crawl = crawl->left;
                root->val = crawl->val;
                root->count = crawl->count;

                root->right = deleteAll(root->right, crawl->val);

                root->height = max(getHeight(root->left), getHeight(root->right))+1;
                root->size = getSize(root->left) + getSize(root->right) + root->count;

                return root;
            }
            else if(root->right){
                node *tmp = root->right;
                delete(root);
                return tmp;
            }
            else {
                node *tmp = root->left;
                delete(root);
                return tmp;
            }
        }

        if(val > root->val) root->right = deleteAll(root->right, val);
        else if(val < root->val) root->left = deleteAll(root->left, val);

        int bf = getHeight(root->left) - getHeight(root->right);


        if(bf > 1){
            if(val > root->left->val){  //LL Rotation
                node *newRoot= root->left;
                root->left = newRoot->right;
                newRoot->right = root;

                root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
                root->size = getSize(root->left) + getSize(root->right) + root->count;

                root = newRoot;
            }
            else{   //LR  Rotation
                node *newRoot = root->left->right;
                root->left->right = newRoot->left;
                newRoot->left = root->left;

                root->left->height = max(getHeight(root->left->left), getHeight(root->left->right)) + 1;
                root->left->size = getSize(root->left->left) + getSize(root->left->right) + root->left->count;

                root->left = newRoot->right;
                newRoot->right = root;

                root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
                root->size = getSize(root->left) + getSize(root->right) + root->count;

                root = newRoot;
            }
        }
        else if(bf < -1){
            if(val < root->right->val){ //RR Rotation
                node *newRoot = root->right;
                root->right = newRoot->left;
                newRoot->left = root;

                root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
                root->size = getSize(root->left) + getSize(root->right) + root->count;

                root = newRoot;
            }
            else{   //RL Rotation
                node *newRoot = root->right->left;
                root->right->left = newRoot->right;
                newRoot->right = root->right;

                root->right->height = max(getHeight(root->right->left), getHeight(root->right->right)) + 1;
                root->right->size = getSize(root->right->left) + getSize(root->right->right) + root->right->count;

                root->right = newRoot->left;
                newRoot->left = root;

                root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
                root->size = getSize(root->left) + getSize(root->right) + root->count;

                root = newRoot;
            }
        }

        root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
        root->size = getSize(root->left) + getSize(root->right) + root->count;

        return root;

    }

    node *deleteOnce(node *root, T val){
        if(root == NULL)return root;

        if(val == root->val){
            if(root->count > 1){
                root->count--;
                root->size--;
                return root;
            }
            if(root->right != NULL && root->left != NULL){
                node *crawl = root->right;
                while(crawl->left)crawl = crawl->left;
                root->val = crawl->val;
                root->count = crawl->count;
                root->right = deleteAll(root->right, crawl->val);

                root->height = max(getHeight(root->left), getHeight(root->right))+1;
                root->size = getSize(root->left) + getSize(root->right) + root->count;

                return root;
            }
            else if(root->right){
                node *tmp = root->right;
                delete(root);
                return tmp;
            }
            else {
                node *tmp = root->left;
                delete(root);
                return tmp;
            }
        }

        if(val > root->val) root->right = deleteOnce(root->right, val);
        else if(val < root->val) root->left = deleteOnce(root->left, val);

        int bf = getHeight(root->left) - getHeight(root->right);


        if(bf > 1){
            if(val > root->left->val){  //LL Rotation
                node *newRoot= root->left;
                root->left = newRoot->right;
                newRoot->right = root;

                root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
                root->size = getSize(root->left) + getSize(root->right) + root->count;

                root = newRoot;
            }
            else{   //LR  Rotation
                node *newRoot = root->left->right;
                root->left->right = newRoot->left;
                newRoot->left = root->left;

                root->left->height = max(getHeight(root->left->left), getHeight(root->left->right)) + 1;
                root->left->size = getSize(root->left->left) + getSize(root->left->right) + root->left->count;

                root->left = newRoot->right;
                newRoot->right = root;

                root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
                root->size = getSize(root->left) + getSize(root->right) + root->count;

                root = newRoot;
            }
        }
        else if(bf < -1){
            if(val < root->right->val){ //RR Rotation
                node *newRoot = root->right;
                root->right = newRoot->left;
                newRoot->left = root;

                root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
                root->size = getSize(root->left) + getSize(root->right) + root->count;

                root = newRoot;
            }
            else{   //RL Rotation
                node *newRoot = root->right->left;
                root->right->left = newRoot->right;
                newRoot->right = root->right;

                root->right->height = max(getHeight(root->right->left), getHeight(root->right->right)) + 1;
                root->right->size = getSize(root->right->left) + getSize(root->right->right) + root->right->count;

                root->right = newRoot->left;
                newRoot->left = root;

                root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
                root->size = getSize(root->left) + getSize(root->right) + root->count;

                root = newRoot;
            }
        }

        root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
        root->size = getSize(root->left) + getSize(root->right) + root->count;

        return root;

    }


    void inorder(node *root){
        if(!root)return;
        inorder(root->left);
        for(int i = 0; i < root->count; i++)
            cout<< root->val <<' ';
        inorder(root->right);
    }

    int getSmallerThan(node *root, T val){
        if(root == NULL)return 0;

        if(root->val < val){
            return getSize(root->left) + root->count + getSmallerThan(root->right, val);
        }
        else{
            return getSmallerThan(root->left, val);
        }
    }

    int getLargerThan(node *root, T val){
        if(root == NULL)return 0;

        if(root->val > val){
            return getSize(root->right) + root->count + getLargerThan(root->left, val);
        }
        else{
            return getLargerThan(root->right, val);
        }
    }

    int getCountOf(node *root, T val){
        if(root == NULL)return 0;
        if(root->val == val)return root->count;

        if(val > root->val)return getCountOf(root->right, val);
        else return getCountOf(root->left, val);
    }

    public:
        AVL(){
            root = NULL;
        }

        void insert(T val){
            this->root = insert(this->root, val);
        }

        void deleteOnce(T val){
            this->root = deleteOnce(this->root, val);
        }

        void deleteAll(T val){
            this->root = deleteAll(this->root, val);
        }

        int getSmallerThan(T val){
            return getSmallerThan(this->root, val);
        }

        int getLargerThan(T val){
            return getLargerThan(this->root, val);
        }

        int getCountOf(T val){
            return getCountOf(this->root, val);
        }

        void seeInorder(){
            inorder(this->root);
        }

        int getHeight(){
            return getHeight(this->root);
        }

        int getSize(){
            return getSize(this->root);
        }

};


int main(){
    // Driver Function

    AVL<pair<int,int> > tree;   // Our AVL tree Object

    tree.insert({3,4});
    tree.insert({8,9});
    tree.insert({10,11});
    tree.insert({3,4});

    cout<< tree.getCountOf({3,4})<<endl;

    cout<<tree.getLargerThan({4,0})<<endl;

    cout<<tree.getSmallerThan({8,11})<<endl;

}
