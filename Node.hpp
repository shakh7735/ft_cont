#ifndef NODE_HPP
#define NODE_HPP

namespace ft{

    enum {BLACK = false, RED = true};
    template < class T > 
    struct		node
    {
        typedef T value_type;
        T                   	data;
        struct node *			left;
        struct node *			right;
        struct node *			parent;
        bool 					nil;
        bool					color;

        node (T data) : data(data),left(0), 
                right(0), parent (0), nil( true ), color( BLACK ) 
                {}
       
        node ( void )    :   data(0), left(0), 
                right(0), parent (0), nil(true), color( BLACK ) {}
        
        // node&	operator=( const node& other )
        // {
        //     this->parent = other.parent;
        //     this->rightChild = other.rightChild;
        //     this->leftChild = other.leftChild;
        //     this->color = other.color;
        // }
    } ;

//     //RBtree function=============================================================================
// //88888888888888888888888888888888888888888888888888888888888888888888888888888888888888888

// 			void rotateLeft(node *x, node*root) {

// 			/**************************
// 				*  rotate node x to left *
// 				**************************/

// 				node *y = x->right;

// 				x->right = y->left;
// 				if (!y->left->nil) y->left->parent = x;

// 				if (!y->nil) y->parent = x->parent;
// 				if (x->parent) {
// 					if (x == x->parent->left)
// 						x->parent->left = y;
// 					else
// 						x->parent->right = y;
// 				} else {
// 					root = y;
// 				}

// 				y->left = x;
// 				if (!x->nil) x->parent = y;
// 			}

// 			void rotateRight(node *x, node*root) {

// 			/****************************
// 				*  rotate node x to right  *
// 				****************************/

// 				node *y = x->left;

// 				x->left = y->right;
// 				if (!y->right->nil) y->right->parent = x;

// 				if (!y->nil) y->parent = x->parent;
// 				if (x->parent) {
// 					if (x == x->parent->right)
// 						x->parent->right = y;
// 					else
// 						x->parent->left = y;
// 				} else {
// 					root = y;
// 				}

// 				y->right = x;
// 				if (!x->nil) x->parent = y;
// 			}

// 			void insertFixup(node *x, node*root) {

// 			/*************************************
// 				*  maintain Red-Black tree balance  *
// 				*  after inserting node x           *
// 				*************************************/

// 				while (x != root && x->parent->color == RED) {
// 					/* we have a violation */
// 					if (x->parent == x->parent->parent->left) {
// 						node *y = x->parent->parent->right;
// 						if (y->color == RED) {

// 							/* uncle is RED */
// 							x->parent->color = BLACK;
// 							y->color = BLACK;
// 							x->parent->parent->color = RED;
// 							x = x->parent->parent;
// 						} else {

// 							/* uncle is BLACK */
// 							if (x == x->parent->right) {
// 								/* make x a left child */
// 								x = x->parent;
// 								rotateLeft(x);
// 							}

// 							/* recolor and rotate */
// 							x->parent->color = BLACK;
// 							x->parent->parent->color = RED;
// 							rotateRight(x->parent->parent);
// 						}
// 					} else {

// 						/* mirror image of above code */
// 						node *y = x->parent->parent->left;
// 						if (y->color == RED) {

// 							/* uncle is RED */
// 							x->parent->color = BLACK;
// 							y->color = BLACK;
// 							x->parent->parent->color = RED;
// 							x = x->parent->parent;
// 						} else {

// 							/* uncle is BLACK */
// 							if (x == x->parent->left) {
// 								x = x->parent;
// 								rotateRight(x);
// 							}
// 							x->parent->color = BLACK;
// 							x->parent->parent->color = RED;
// 							rotateLeft(x->parent->parent);
// 						}
// 					}
// 				}
// 				root->color = BLACK;
// 			}

// 			node *insertNode(const value_type& data, node*root, node* in_node) {
// 				node *current, *parent, *x;

// 			/***********************************************
// 				*  allocate node for data and insert in tree  *
// 				***********************************************/

// 				/* find where node belongs */
// 				current = root;
// 				parent = 0;
// 				while (!current->nil) {
// 					if (data.first == current->data.first) return (current);
// 					parent = current;
// 					current = (comp(data.first, current->data.first) ? current->left : current->right);
// 				}

// 				/* setup new node */
//                 x = in_node;
// 				// x = new_node(data);
// 				// x->parent = parent;
// 				// x->left = nil_node;
// 				// x->right = nil_node;
// 				// x->color = RED;

// 				/* insert node in tree */
// 				if(parent) {
// 					if(comp(data.first, parent->data.first))
// 						parent->left = x;
// 					else
// 						parent->right = x;
// 				} else {
// 					root = x;
// 				}

// 				insertFixup(x);
// 				rightXod();
// 				return(x);
// 			}

// 			void deleteFixup(node *x, node*root) {

// 			/*************************************
// 				*  maintain Red-Black tree balance  *
// 				*  after deleting node x            *
// 				*************************************/

// 				while (x != root && x->color == BLACK) {
// 					if (x == x->parent->left) {
// 						node *w = x->parent->right;
// 						if (w->color == RED) {
// 							w->color = BLACK;
// 							x->parent->color = RED;
// 							rotateLeft (x->parent);
// 							w = x->parent->right;
// 						}
// 						if (w->left->color == BLACK && w->right->color == BLACK) {
// 							w->color = RED;
// 							x = x->parent;
// 						} else {
// 							if (w->right->color == BLACK) {
// 								w->left->color = BLACK;
// 								w->color = RED;
// 								rotateRight (w);
// 								w = x->parent->right;
// 							}
// 							w->color = x->parent->color;
// 							x->parent->color = BLACK;
// 							w->right->color = BLACK;
// 							rotateLeft (x->parent);
// 							x = root;
// 						}
// 					} else {
// 						node *w = x->parent->left;
// 						if (w->color == RED) {
// 							w->color = BLACK;
// 							x->parent->color = RED;
// 							rotateRight (x->parent);
// 							w = x->parent->left;
// 						}
// 						if (w->right->color == BLACK && w->left->color == BLACK) {
// 							w->color = RED;
// 							x = x->parent;
// 						} else {
// 							if (w->left->color == BLACK) {
// 								w->right->color = BLACK;
// 								w->color = RED;
// 								rotateLeft (w);
// 								w = x->parent->left;
// 							}
// 							w->color = x->parent->color;
// 							x->parent->color = BLACK;
// 							w->left->color = BLACK;
// 							rotateRight (x->parent);
// 							x = root;
// 						}
// 					}
// 				}
// 				x->color = BLACK;
// 			}

// 			void deleteNode(node *z, node*root) {
// 				node *x, *y;

// 			/*****************************
// 				*  delete node z from tree  *
// 				*****************************/

// 				if (!z || z->nil) return;
// 				if (z->left->nil || z->right->nil) {
// 					/* y has a nil_node node as a child */
// 					y = z;
// 				} else {
// 					/* find tree successor with a nil_node node as a child */
// 					y = z->right;
// 					while (!y->left->nil) y = y->left;
// 				}

// 				/* x is y's only child */
				
// 				if (!y->left->nil)
// 					x = y->left;
// 				else
// 					x = y->right;

// 				/* remove y from the parent chain */
// 				x->parent = y->parent;
// 				if (y->parent)
// 					if (y == y->parent->left)
// 						y->parent->left = x;
// 					else
// 						y->parent->right = x;
// 				else
// 					root = x;

// 				if (y != z) z = z->data = y->data;//copy_data(z, y); // 
				
// 				if (y->color == BLACK && !x->nil) 	deleteFixup (x, root);
// 				rightXod();
// 				if (!y->nil) {alloc.destroy(y); alloc.deallocate(y, 1);}
// 			}

// 			// node *copy_data(node * a, node * b)
// 			// {
// 			// 	if (a == nil_node || a == b) return a; 
// 			// 	node *c = new_node(b->data);
// 			// 	c->parent = a->parent;
// 			// 	c->left = a->left;
// 			// 	c->right = a->right;
// 			// 	c->nil = a->nil;
// 			// 	c->color = a->color;
// 			// 	if (a->left->parent == a) a->left->parent = c;
// 			// 	if (a->right->parent == a) a->right->parent = c;
// 			// 	if (a->parent)
// 			// 		(a->parent->left == a ? a->parent->left = c : a->parent->right = c);
// 			// 	if (root == a)
// 			// 		root = c;
// 			// 	alloc.destroy(a);
// 			// 	alloc.deallocate(a, 1);
// 			// 	return c;
// 			// }

// 			bool equal_val (const value_type & lhs, const value_type & rhs) const
// 			{
//                 // if (typedef(value_type) == typedef(ft::pair::type))
// 				return (comp(lhs, rhs) == false && comp(rhs, lhs) == false);
// 			}

// //88888888888888888888888888888888888888888888888888888888888888888888888888888888888
// //END RBtree =================================================================================


}

#endif