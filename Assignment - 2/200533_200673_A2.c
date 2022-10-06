#include<stdio.h>
#include<stdlib.h>

/*
    We construct a sparse matrix structure as follows:

        root_node      ----->   col_header_node_1   -----> col_header_node_2   ------> col_header_node_3 ---> ... NULL
        (6969, (0, 0))          (69, (0, c_1))             (69, (0, c_2))              (69, (0, c_3))
            |
            |
            V                                                                                                       .
        row_header_node_1 --------------------------------> value_node -------------> ... NULL                      .
        (69, (r_1, 0))                                                                                              .
            |                                                                                                       .
            |                                                                                                       .
            V
        row_header_node_2 ------------------------------->     .
        (69, (r_2, 0))                                           .
            |                                                       .
            |
            V                                                                ......................................
           NULL                       

        The matrix is accessed through the root node.
*/
struct node{ // Node struct for each matrix entry and also used for the row, column headers and root
    int val;
    int r;
    int c;
    struct node* right;
    struct node* down;
};

typedef struct node node;

node* new_node(int val, int r, int c, node* right, node* down ){
    node* temp = (node*) malloc(sizeof(node));
    temp->val = val;
    temp->r = r;
    temp->c = c;
    temp->right = right;
    temp->down = down;
}


node* read_matrix(int n, int t){
    node* root;
    root = new_node(6969, 0, 0, NULL, NULL); //We use a node with row = 0, col = 0 and val = 6969 to indicate the root node which will be used to access the row and col_headers
    int f;
    node* col_head[n+1];        
    node* col_last_node[n+1];    //Direct Access Table is used to make the vertical linkages in O(n+m)
    node* last_node = root;
    node* last_row_head = root;
    for(int i = 1; i <= n; i++){
        col_head[i] = NULL;
        col_last_node[i] = NULL;
    }
    do{
        int r, c, val;
        scanf("%d %d %d", &r, &c, &val); 
        node* temp = new_node(val, r, c, NULL, NULL);
        if(!col_head[c]){
            col_head[c] = col_last_node[c] = new_node(69, 0, c, NULL, NULL); //If this is the first node in a given column we create a column header with row = 0, col = col_index, val = 69
        }
        col_last_node[c]->down = temp;
        col_last_node[c] = temp;
        
        if(last_node->r != r){
            last_node = new_node(69, r, 0, NULL, NULL); // Every time we enter a new row we create a new row header node with col = 0, row = row_index, val = 69
            last_row_head->down = last_node;
            last_row_head = last_node;
        }
        last_node->right = temp;
        last_node  = temp;
        scanf("%d", &f);
    } while(f == t);
    node* col_linker = root;
    for(int i = 1; i <= n; i++){
        if(col_head[i] != NULL){
            col_linker->right = col_head[i]; // We finally connect the column_heads horizontally
            col_linker = col_head[i];
        }
    }
    return root;
}

void print_matrix(node* root){
    int flag = 0;
    node* row_head = root;
    while(row_head){
        node* curr = row_head;
        while (curr != NULL){
            if(curr->r && curr->c){
                printf("%d %d %d \n", curr->r, curr->c, curr->val);
                flag = 1;
            }
            curr = curr->right;
        }
        row_head = row_head->down;
    }
    if(flag == 0){
        printf("NULL MATRIX!");
    }
}
node* multiply(node* A, node* B, int n){
    node* root  = new_node(6969, 0, 0, NULL, NULL);
    node* col_head_nodes[n+1];
    node* col_last_node[n+1];
    node* last_node = root;
    node* last_row_head = root;
    
    for(int i = 1; i <= n; i++){
        col_head_nodes[i] = NULL;
        col_last_node[i] = NULL;
    }
    node* row_head = A->down;
    while(row_head != NULL){
        node* col_head = B->right;
        while(col_head != NULL){                         // For each row in A and col in B, we scan through their lists and compute sum A[i][k]*B[k][j] whenever the k matches up
            node* row_curr = row_head->right;
            node* col_curr = col_head->down;
            int val = 0;
            while(row_curr != NULL && col_curr != NULL){
                int k1 = row_curr->c;
                int k2 = col_curr->r;
                if(k1 == k2){
                    val += (row_curr->val)*(col_curr->val);
                    col_curr = col_curr->down;
                    row_curr = row_curr->right;
                }
                else{
                    if(k1 < k2){
                        row_curr = row_curr->right;
                    }
                    else if(k1 > k2){
                        col_curr = col_curr->down;
                    }
                }
            }
            if(val){
                int r = row_head->r;
                int c = col_head->c;
                node* temp = new_node(val, r, c, NULL, NULL);
                if(!col_head_nodes[c])
                    col_head_nodes[c] = col_last_node[c] = new_node(69, 0, c, NULL, NULL);
                col_last_node[c]->down = temp;
                col_last_node[c] = temp;
        
                if(last_node->r != r){
                    last_node = new_node(69, r, 0, NULL, NULL);
                    last_row_head->down = last_node;
                    last_row_head = last_node;
                }
                last_node->right = temp;
                last_node  = temp;
            }
            col_head = col_head->right;
        }
        row_head = row_head->down;
    }     
    return root;
}
int main(){
    int n;
    scanf("%d", &n);
    int t;
    scanf("%d", &t);
    node *A = read_matrix(n, 1);
    node *B = read_matrix(n, 2);
    print_matrix(multiply(A, B, n));
    return 0;
}
