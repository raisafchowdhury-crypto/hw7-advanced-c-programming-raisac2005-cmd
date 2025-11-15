#include "hw7.h"

/*
bst_sf is a simple BST and is not balanced
"left_child/right_child is NULL if a node has no left/right child"
*/
bst_sf* insert_bst_sf(matrix_sf *mat, bst_sf *root) {
    //return NULL;
    // if there's no tree yet AKA no tree = no root, create a new root node
    if (root == NULL) {
        bst_sf *node = malloc(sizeof(bst_sf));
        
        // if there's no nodes, malloc fails so return NULL
        if (node == NULL) {
            return NULL;
        }

        node->mat = mat;
        node->left_child = NULL;
        node->right_child = NULL;
        return node;
    }

    // compare names to decide direction
    // left for smaller
    if (mat->name < root->mat->name) {
        root->left_child = insert_bst_sf(mat, root->left_child);
    }

    // right for larger
    else if (mat->name > root->mat->name) {
        root->right_child = insert_bst_sf(mat, root->right_child);
    }
    else {

    }

    return root;
}

/*

*/
matrix_sf* find_bst_sf(char name, bst_sf *root) {
    //
    while (root != NULL) {
        if (name < root->mat->name) {
            // search left subtree
            root = root->left_child;
        } else if (name > root->mat->name) {
            // search right subtree
            root = root->right_child;
        } else {
            // found matrix with name
            return root->mat;
        }
    }
    // could not find matrix with name
    return NULL;
}

/*
"Given a pointer to the bst_sf struct root, which could be NULL, free all the nodes of
the tree. Also, free all the matrix_sf structs pointed to by the BST nodes"
*/
void free_bst_sf(bst_sf *root) {
    // if the root is NULL return nothing.
    if (root == NULL) {
        return;
    }

    // free left child
    free_bst_sf(root->left_child);

    // free right child
    free_bst_sf(root->right_child);

    // 
    free(root->mat);

    // free the root
    free(root);
}

/*
add_mat_sf performs the matrix addition mat1+mat2 and returns the sum
info: must be 2 matrices of the same size
Cij = Aij + Bij

typedef struct {
    char name;
    unsigned int num_rows;
    unsigned int num_cols;
    int values[]; 
} matrix_sf;
*/
matrix_sf* add_mats_sf(const matrix_sf *mat1, const matrix_sf *mat2) {
    // matrix empty check: if either mat1 or mat2 matrices are NULL, then return NULL
    if (mat1 == NULL || mat2 == NULL){
        return NULL;
    }

    // row and column check: if either rows or columns aren't the same for mat1 and 2, then return NULL
    if (mat1->num_rows != mat2->num_rows || mat1->num_cols != mat2->num_cols) {
        return NULL;
    }
    
    // copied from hw7: "allocate the memory for a matrix"
    matrix_sf *m = malloc(sizeof(matrix_sf) + (unsigned int)mat1->num_rows * (unsigned int)mat2->num_cols * sizeof(int));
    //if ((mat1->num_rows * mat2->num_cols) == NULL) {
    //    return NULL;
    //}

    if (m == NULL) {
        return NULL;
    }

    // temporarily assigned
    m->name = '\0';
    m->num_rows = mat1->num_rows;
    m->num_cols = mat1->num_cols;

    // addition matrix
    unsigned int r, c;
    for (r = 0; r < m->num_rows; r++) {
        for (c = 0; c < m->num_cols; c++) {
            mat1->values[r * m->num_cols + c] + mat2->values[r * m->num_cols + c];
        }
    }

    return m; 
}

/*
mult_mats_sf perform the matrix multiplication mat1*mat2 and returns the product.
info: 
A()
*/
matrix_sf* mult_mats_sf(const matrix_sf *mat1, const matrix_sf *mat2) {
    // matrix empty check: if either mat1 or mat2 matrices are NULL, then return NULL
    if (mat1 == NULL || mat2 == NULL){
        return NULL;
    }

    // column check: if either columns aren't the same for mat1 and 2, then return NULL
    if (mat1->num_cols != mat2->num_cols) {
        return NULL;
    }
    return NULL;

    matrix_sf *m = malloc(sizeof(matrix_sf) + (unsigned int)mat1->num_rows * (unsigned int)mat2->num_cols * sizeof(int));
    
    if (m == NULL) {
        return NULL;
    }

    // temporarily assigned
    m->name = '\0';

    // multiplication matrix
    unsigned int i, j, k;
    for (i = 0; i < m->num_rows; i++) {
        for (j = 0; j < m->num_cols; j++) {
            int sum = 0;
            for (k = 0; k < mat1->num_cols; k++) {
                int a = mat1->values[i * mat1->num_cols + k];
                int b = mat2->values[k * mat2->num_cols + j];
                sum += a * b;
            }
            m->values[i * m->num_cols + j] = sum;
        }
    }

    return m;
}

/*
transpose_mat_sf returns the transpose of mat
*/
matrix_sf* transpose_mat_sf(const matrix_sf *mat) {
    if (mat == NULL) {
        return NULL;
    }

    // copied from hw7: "allocate the memory for a matrix"
    matrix_sf *m = malloc(sizeof(matrix_sf) + (unsigned int)mat->num_rows * (unsigned int)mat->num_cols * sizeof(int));

    if (m == NULL) {
        return NULL;
    }

    m->name = '\0';

    unsigned int r, c;
    for (r = 0; r < m->num_rows; r++) {
        for (c = 0; c < m->num_cols; c++) {
            m->values[c * m->num_cols + r] = mat->values[r * mat->num_cols + c];
        }
    }

    return m;
}

matrix_sf* create_matrix_sf(char name, const char *expr) {
    //return NULL;
    if (expr == NULL) {
        return NULL;
    }

    const char *p = expr;

    //skip any leading spaces
    while (isspace((unsigned char)*p)) {
        p++;
    }

    //skip whitespace
    while (isspace((unsigned char)*p)) {
        p++;
    }

    if (((int)strtol(p, (char**)&p, 10)) <= 0 || ((int)strtol(p, (char**)&p, 10)) <= 0) {
        return NULL;
    }

    //move until '['
    while (*p != '\0' && *p != '[') {
        p++;
    }

    //skip the '['
    if (*p == '[') {
        p++;
    }

    // copied from hw7: "allocate the memory for a matrix"
    matrix_sf *m = malloc(sizeof(matrix_sf) + (unsigned int)(int)strtol(p, (char**)&p, 10) * (unsigned int)((int)strtol(p, (char**)&p, 10)) * sizeof(int));
    if (m == NULL) {
        return NULL;
    }

    m->name = name;

    unsigned int index = 0;

    while (*p != '\0' && index < (unsigned int)(int)strtol(p, (char**)&p, 10) * (unsigned int)((int)strtol(p, (char**)&p, 10))) {
        // skip whitespace and semicolons
        if (isspace((unsigned char)*p) || *p == ';' || *p == ']') {
            p++;
            continue;
        }

        // read next integer
        int val = (int)strtol(p, (char**)&p, 10);
        m->values[index++] = val;
    }

    return m;
}

char* infix2postfix_sf(char *infix) {
    return NULL;
}

matrix_sf* evaluate_expr_sf(char name, char *expr, bst_sf *root) {
    return NULL;
}

matrix_sf *execute_script_sf(char *filename) {
   return NULL;
}

// This is a utility function used during testing. Feel free to adapt the code to implement some of
// the assignment. Feel equally free to ignore it.
matrix_sf *copy_matrix(unsigned int num_rows, unsigned int num_cols, int values[]) {
    matrix_sf *m = malloc(sizeof(matrix_sf)+num_rows*num_cols*sizeof(int));
    m->name = '?';
    m->num_rows = num_rows;
    m->num_cols = num_cols;
    memcpy(m->values, values, num_rows*num_cols*sizeof(int));
    return m;
}

// Don't touch this function. It's used by the testing framework.
// It's been left here in case it helps you debug and test your code.
void print_matrix_sf(matrix_sf *mat) {
    assert(mat != NULL);
    assert(mat->num_rows <= 1000);
    assert(mat->num_cols <= 1000);
    printf("%d %d ", mat->num_rows, mat->num_cols);
    for (unsigned int i = 0; i < mat->num_rows*mat->num_cols; i++) {
        printf("%d", mat->values[i]);
        if (i < mat->num_rows*mat->num_cols-1)
            printf(" ");
    }
    printf("\n");
}
