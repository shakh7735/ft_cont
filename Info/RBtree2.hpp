
// typedef int T;                  /* type of item to be stored */
// #define compLT(a,b) (a < b)
// #define compEQ(a,b) (a == b)

// /* Red-Black tree description */
// typedef enum { BLACK, RED } nodeColor;

// typedef struct Node_ {
//     struct Node_ *left;         /* left child */
//     struct Node_ *right;        /* right child */
//     struct Node_ *parent;       /* parent */
//     nodeColor color;            /* node color (BLACK, RED) */
//     T data;                     /* data stored in node */
// } Node;

// #define NIL &sentinel           /* all leafs are sentinels */
// Node sentinel = { NIL, NIL, 0, BLACK, 0};

// Node *root = NIL;               /* root of Red-Black tree */


// void rotateLeft(node *x) {

//    /**************************
//     *  rotate node x to left *
//     **************************/

//     node *y = x->right;

//     /* establish x->right link */
//     x->right = y->left;
//     if (y->left != nil_node) y->left->parent = x;

//     /* establish y->parent link */
//     if (y != nil_node) y->parent = x->parent;
//     if (x->parent) {
//         if (x == x->parent->left)
//             x->parent->left = y;
//         else
//             x->parent->right = y;
//     } else {
//         root = y;
//     }

//     /* link x and y */
//     y->left = x;
//     if (x != nil_node) x->parent = y;
// }

// void rotateRight(node *x) {

//    /****************************
//     *  rotate node x to right  *
//     ****************************/

//     node *y = x->left;

//     /* establish x->left link */
//     x->left = y->right;
//     if (y->right != nil_node) y->right->parent = x;

//     /* establish y->parent link */
//     if (y != nil_node) y->parent = x->parent;
//     if (x->parent) {
//         if (x == x->parent->right)
//             x->parent->right = y;
//         else
//             x->parent->left = y;
//     } else {
//         root = y;
//     }

//     /* link x and y */
//     y->right = x;
//     if (x != nil_node) x->parent = y;
// }

// void insertFixup(node *x) {

//    /*************************************
//     *  maintain Red-Black tree balance  *
//     *  after inserting node x           *
//     *************************************/

//     /* check Red-Black properties */
//     while (x != root && x->parent->color == RED) {
//         /* we have a violation */
//         if (x->parent == x->parent->parent->left) {
//             node *y = x->parent->parent->right;
//             if (y->color == RED) {

//                 /* uncle is RED */
//                 x->parent->color = BLACK;
//                 y->color = BLACK;
//                 x->parent->parent->color = RED;
//                 x = x->parent->parent;
//             } else {

//                 /* uncle is BLACK */
//                 if (x == x->parent->right) {
//                     /* make x a left child */
//                     x = x->parent;
//                     rotateLeft(x);
//                 }

//                 /* recolor and rotate */
//                 x->parent->color = BLACK;
//                 x->parent->parent->color = RED;
//                 rotateRight(x->parent->parent);
//             }
//         } else {

//             /* mirror image of above code */
//             node *y = x->parent->parent->left;
//             if (y->color == RED) {

//                 /* uncle is RED */
//                 x->parent->color = BLACK;
//                 y->color = BLACK;
//                 x->parent->parent->color = RED;
//                 x = x->parent->parent;
//             } else {

//                 /* uncle is BLACK */
//                 if (x == x->parent->left) {
//                     x = x->parent;
//                     rotateRight(x);
//                 }
//                 x->parent->color = BLACK;
//                 x->parent->parent->color = RED;
//                 rotateLeft(x->parent->parent);
//             }
//         }
//     }
//     root->color = BLACK;
// }

// node *insertnode(T data) {
//     node *current, *parent, *x;

//    /***********************************************
//     *  allocate node for data and insert in tree  *
//     ***********************************************/

//     /* find where node belongs */
//     current = root;
//     parent = 0;
//     while (current != nil_node) {
//         if (compEQ(data, current->data)) return (current);
//         parent = current;
//         current = compLT(data, current->data) ?
//             current->left : current->right;
//     }

//     /* setup new node */
//     if ((x = malloc (sizeof(*x))) == 0) {
//         printf ("insufficient memory (insertnode)\n");
//         exit(1);
//     }
//     x->data = data;
//     x->parent = parent;
//     x->left = nil_node;
//     x->right = nil_node;
//     x->color = RED;

//     /* insert node in tree */
//     if(parent) {
//         if(compLT(data, parent->data))
//             parent->left = x;
//         else
//             parent->right = x;
//     } else {
//         root = x;
//     }

//     insertFixup(x);
//     return(x);
// }

// void deleteFixup(node *x) {

//    /*************************************
//     *  maintain Red-Black tree balance  *
//     *  after deleting node x            *
//     *************************************/

//     while (x != root && x->color == BLACK) {
//         if (x == x->parent->left) {
//             node *w = x->parent->right;
//             if (w->color == RED) {
//                 w->color = BLACK;
//                 x->parent->color = RED;
//                 rotateLeft (x->parent);
//                 w = x->parent->right;
//             }
//             if (w->left->color == BLACK && w->right->color == BLACK) {
//                 w->color = RED;
//                 x = x->parent;
//             } else {
//                 if (w->right->color == BLACK) {
//                     w->left->color = BLACK;
//                     w->color = RED;
//                     rotateRight (w);
//                     w = x->parent->right;
//                 }
//                 w->color = x->parent->color;
//                 x->parent->color = BLACK;
//                 w->right->color = BLACK;
//                 rotateLeft (x->parent);
//                 x = root;
//             }
//         } else {
//             node *w = x->parent->left;
//             if (w->color == RED) {
//                 w->color = BLACK;
//                 x->parent->color = RED;
//                 rotateRight (x->parent);
//                 w = x->parent->left;
//             }
//             if (w->right->color == BLACK && w->left->color == BLACK) {
//                 w->color = RED;
//                 x = x->parent;
//             } else {
//                 if (w->left->color == BLACK) {
//                     w->right->color = BLACK;
//                     w->color = RED;
//                     rotateLeft (w);
//                     w = x->parent->left;
//                 }
//                 w->color = x->parent->color;
//                 x->parent->color = BLACK;
//                 w->left->color = BLACK;
//                 rotateRight (x->parent);
//                 x = root;
//             }
//         }
//     }
//     x->color = BLACK;
// }

// void deletenode(node *z) {
//     node *x, *y;

//    /*****************************
//     *  delete node z from tree  *
//     *****************************/

//     if (!z || z == nil_node) return;


//     if (z->left == nil_node || z->right == nil_node) {
//         /* y has a nil_node node as a child */
//         y = z;
//     } else {
//         /* find tree successor with a nil_node node as a child */
//         y = z->right;
//         while (y->left != nil_node) y = y->left;
//     }

//     /* x is y's only child */
//     if (y->left != nil_node)
//         x = y->left;
//     else
//         x = y->right;

//     /* remove y from the parent chain */
//     x->parent = y->parent;
//     if (y->parent)
//         if (y == y->parent->left)
//             y->parent->left = x;
//         else
//             y->parent->right = x;
//     else
//         root = x;

//     if (y != z) z->data = y->data;


//     if (y->color == BLACK)
//         deleteFixup (x);

//     free (y);
// }

// node *findnode(T data) {

//    /*******************************
//     *  find node containing data  *
//     *******************************/

//     node *current = root;
//     while(current != nil_node)
//         if(compEQ(data, current->data))
//             return (current);
//         else
//             current = compLT (data, current->data) ?
//                 current->left : current->right;
//     return(0);
// }
