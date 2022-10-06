#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
#include<string.h>
typedef struct node{
    int key;
    struct node* right;
    struct node* left; 
} node;
typedef struct bst{
    node* root;
    int size;
    int maxSize;
} bst;

int max(int a, int b){ //Works tested
    return (a > b)? a: b;
}

bst* create_bst(){//Works tested
    bst* temp = (bst*) malloc(sizeof(bst));    
    temp->size = 0;
    temp->maxSize = 0;
    temp->root = NULL;
    return temp;
}

node* create_node(int key){//Works tested
    node* temp = (node*) malloc(sizeof(node));
    temp->key = key;
    temp->right = NULL;
    temp->left = NULL;
    return temp;
}

int deepHeight[10000010];
void precomputeHeight(){ //Works Tested
    for(int i = 1; i < 10000010; i++){
        deepHeight[i] = (int) floor(log(i)/log(4.0/3.0));
    }
}

int size(node* nd){//Works Tested
    if(nd == NULL) 
        return 0;
    return 1 + size(nd->right)+size(nd->left);
}


node* arr[10000010];

node* build(int s, int l){//Works
    if(l < s) return NULL;
    int mid = s + (l-s)/2;
    node* nd = arr[mid];
    nd->left = build(s, mid - 1);
    nd->right = build(mid + 1, l);
    return nd;
}

int flatten(node* nd, int s){//Works
    if(nd == NULL){
        return s-1;
    }
    s = flatten(nd->left, s);
    s++;
    arr[s] = nd;
    s++;
    return flatten(nd->right, s);
}

void rebuildTree(node* nd, bst* T){//Works
    bool isRoot = (nd == T->root);
    node* parent = T->root;
    bool isRightChild;
    if(!isRoot){
        while(parent->right != nd && parent->left != nd){
            if(parent->key > nd->key){
                parent = parent->left;
            }
            else{
                parent = parent->right;
            }
        }
        isRightChild = parent->right == nd;
    }
    nd = build(0, flatten(nd, 0));
    if(isRoot) T->root = nd;
    else {
        if(isRightChild) parent->right = nd;
        else parent->left = nd;
    }
    T->maxSize = T->size;
}
void insert(int key, bst* T){
    if(T->root == NULL){
        //Handle the empty tree case
        T->root = create_node(key);
        T->size = 1;
        T->maxSize = 1;
        return;
    }
    
    int h = 1;
    node* curr = T->root;
    while(curr != NULL){
        if(curr->key >= key){
            arr[h] = curr;
            curr = curr->left;
            h++;
        }
        else {
            arr[h] = curr;
            curr = curr->right;
            h++;
        }
    }
    
    curr = arr[h-1];
    if(curr->key > key) arr[h] = curr->left = create_node(key);
    else arr[h] = curr->right = create_node(key);

    if(h > deepHeight[T->size]){
        //We look for a scapegoat amongst the ancestors of the inserted node
        int i = 0; 
        int sgSize = 0;
        while(i <= deepHeight[sgSize] && h-i >= 0){
            int j = h - i; // arr index where the ith ancestor is going to be stored
            node* brother = (arr[j-1]->right == arr[j])? arr[j-1]->left : arr[j-1]->right;
            sgSize = 1 + size(brother) + sgSize;
            i++;  
        }
                
        //when this terminates we have a scapegoat at ith position
        node* scapeGoat = arr[i];
        rebuildTree(scapeGoat, T);
        
    }

    T->size = T->size + 1;
    T->maxSize = max(T->size, T->maxSize);
    
} 

//Takes in a key to be inserted into the bst, and a bst 
//We find the appropriate place for insertion and if it is 
//a deep node then we rebalance about a scapegoat

void delete(int val, bst* T){
    node* temp = T->root;
    node* prev = NULL;
    while(temp != NULL){
        if(temp->key == val) break;
        else if(temp->key > val){
            prev = temp;
            temp = temp->left;
        }
        else{
            prev = temp;
            temp = temp->right;
        }
    }
    if(temp->key == val){
        if(temp->left == NULL){
            bool isRightChild = (prev->right == temp);
            node* right = temp->right;
            free(temp);
            if(isRightChild) prev->right = temp;
            else prev->left = temp;
        }
        else{
            node* predecessor = temp;
            node* predParent = temp;
            predecessor = predecessor->left;
            while(predecessor->right != NULL){
                predParent = predecessor;
                predecessor = predecessor->right;
            }
            bool isRightChild = (predParent->right == predecessor);
            node* left = predecessor->left;
            free(predecessor);
            if(isRightChild) predParent->right = left;
            else predParent->left = left;
        }
        T->size = T->size - 1;
        if(4*T->size <= 3*T->maxSize){
            rebuildTree(T->root, T);
        }
    }
}
// Takes a key to delete 
// If it is present in the tree
// we swap it with its predecessor and delete it
// If this makes size < 3/4*size(T)
// We balance the whole tree again

bool search(int val, bst* T){//works tested
    node* temp = T->root;
    while(temp != NULL){
        if(temp->key == val) return true;
        else if(temp->key > val){
            temp = temp->left;
        }
        else{
            temp = temp->right;
        }
    }
    return false;
}
//Just simple searching nothing fancy 


void display(bst* T){
    node* queue[50];
    memset(queue, 0, 50*sizeof(node*));
    int i = 0;
    int j = 1; 
    int skip = 1;
    int skipped = 0;
    queue[0] = T->root;
    while(queue[i] != NULL){
        printf("%d ", queue[i]->key);
        skipped++;
        if(skipped == skip){
            skip *= 2;
            skipped = 0;
            printf("\n");
        }
        if(queue[i]->left != NULL) queue[j++] = queue[i]->left;
        if(queue[i]->right != NULL) queue[j++] = queue[i]->right;
        i++;
    }

}
/*
                            4
                    2               6
                1       3       5       7
            0

0 1 2 3 5 6 7 8
                3
        1               5    
    0       2       4       6
                                7
*/
int main(){
    bst* T = create_bst();
    precomputeHeight();
    /*
    T->root = create_node(4);
    T->root->right = create_node(6);
    T->root->left = create_node(2);
    T->root->left->left = create_node(1);
    T->root->left->right = create_node(3);
    T->root->left->left->left = create_node(0);
    T->root->right->left = create_node(5);
    */
    /*
    T->root->right->right = create_node(7);
    */  
    int a[] = {3, 1, 5, 0, 2, 4, 6, 7};
    for(int i = 0; i < 16; i++) {
        insert(i, T);
        printf("\n\n");
        display(T);
    }
    
   /*
    T->root = create_node(0);
    node* nd = T->root;
    for(int i = 1; i < 7; i++){
        nd->right = create_node(i);
        nd = nd->right;
    }
    T->size = 7;
    insert(7, T);
    */
    //printf("%d", T->root->key);
    return 0;
}
