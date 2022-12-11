// #ifndef RBTREE_H
// #define RBTREE_H

// #include "map.hpp"


// typedef node;
// enum {BLACK = false, RED = true};

// node *grandparent(node *n)
// {
// 	if ((n != NULL) && (n->parent != NULL))
// 		return n->parent->parent;
// 	else
// 		return NULL;
// }

// node *uncle(node *n)
// {
// 	node *g = grandparent(n);
// 	if (g == NULL)
// 		return NULL; // No grandparent means no uncle
// 	if (n->parent == g->left)
// 		return g->right;
// 	else
// 		return g->left;
// }

// void rotate_left(node *n)
// {
//     node *pivot = n->right;
	
//     pivot->parent = n->parent; /* при этом, возможно, pivot становится корнем дерева */
//     if (n->parent != NULL) {
//         if (n->parent->left==n)
//             n->parent->left = pivot;
//         else
//             n->parent->right = pivot;
//     }	

//     n->right = pivot->left;
//     if (pivot->left != NULL)
//         pivot->left->parent = n;

//     n->parent = pivot;
//     pivot->left = n;
// }

// void rotate_right(node *n)
// {
//     node *pivot = n->left;
	
//     pivot->parent = n->parent; /* при этом, возможно, pivot становится корнем дерева */
//     if (n->parent != NULL) {
//         if (n->parent->left==n)
//             n->parent->left = pivot;
//         else
//             n->parent->right = pivot;
//     }		
	
//     n->left = pivot->right;
//     if (pivot->right != NULL)
//         pivot->right->parent = n;

//     n->parent = pivot;
//     pivot->right = n;
// }

// void insert_case1(node *n)
// {
// 	if (n->parent == NULL)
// 		n->color = BLACK;
// 	else
// 		insert_case2(n);
// }

// void insert_case2(node *n)
// {
// 	if (n->parent->color == BLACK)
// 		return; /* Tree is still valid */
// 	else
// 		insert_case3(n);
// }

// void insert_case3(node *n)
// {
// 	node *u = uncle(n), *g;

// 	if ((u != NULL) && (u->color == RED)) {
// 	// && (n->parent->color == RED) Второе условие проверяется в insert_case2, то есть родитель уже является красным.
// 		n->parent->color = BLACK;
// 		u->color = BLACK;
// 		g = grandparent(n);
// 		g->color = RED;
// 		insert_case1(g);
// 	} else {
// 		insert_case4(n);
// 	}
// }

// void insert_case4(node *n)
// {
// 	node *g = grandparent(n);

// 	if ((n == n->parent->right) && (n->parent == g->left)) {
// 		rotate_left(n->parent);
// 		n = n->left;
// 	} else if ((n == n->parent->left) && (n->parent == g->right)) {
// 		rotate_right(n->parent);
// 		n = n->right;
// 	}
// 	insert_case5(n);
// }

// void insert_case5(node *n)
// {
// 	node *g = grandparent(n);

// 	n->parent->color = BLACK;
// 	g->color = RED;
// 	if ((n == n->parent->left) && (n->parent == g->left)) {
// 		rotate_right(g);
// 	} else {
// 		rotate_left(g);
// 	}
// }


// node *sibling(node *n)
// {
// 	if (n == n->parent->left)
// 		return n->parent->right;
// 	else
// 		return n->parent->left;
// }

// // void replace_node(node* n, node* child) {
// //     child->parent = n->parent;
// //     if (n == n->parent->left) {
// //         n->parent->left = child;
// //     } else {
// //         n->parent->right = child;
// //     }
// // }

// // void delete_one_child(node *n)
// // {
// // 	/*
// // 	 * Условие: n имеет не более одного ненулевого потомка.
// // 	 */
// // 	node *child = is_leaf(n->right) ? n->left : n->right;
    
// // 	replace_node(n, child);
// // 	if (n->color == BLACK) {
// // 		if (child->color == RED)
// // 			child->color = BLACK;
// // 		else
// // 			delete_case1(child);
// // 	}
// // 	free(n);
// // }

// void delete_case1(node *n)
// {
// 	if (n->parent != NULL)
// 		delete_case2(n);
// }


// void delete_case2(node *n)
// {
// 	node *s = sibling(n);

// 	if (s->color == RED) {
// 		n->parent->color = RED;
// 		s->color = BLACK;
// 		if (n == n->parent->left)
// 			rotate_left(n->parent);
// 		else
// 			rotate_right(n->parent);
// 	} 
// 	delete_case3(n);
// }

// void delete_case3(node *n)
// {
// 	node *s = sibling(n);

// 	if (
//             (n->parent->color == BLACK) &&
// 	        (s->color == BLACK) &&
// 	        (s->left->color == BLACK) &&
// 	        (s->right->color == BLACK)
//         )
//     {
// 		s->color = RED;
// 		delete_case1(n->parent);
// 	} else
// 		delete_case4(n);
// }

// void delete_case4(node *n)
// {
// 	node *s = sibling(n);

// 	if (
//             (n->parent->color == RED) &&
// 	        (s->color == BLACK) &&
// 	        (s->left->color == BLACK) &&
// 	        (s->right->color == BLACK)
//         )
//     {
// 		s->color = RED;
// 		n->parent->color = BLACK;
// 	} else
// 		delete_case5(n);
// }

// void delete_case5(node *n)
// {
// 	node *s = sibling(n);

// 	if  (s->color == BLACK) { /* this if statement is trivial, 
// due to case 2 (even though case 2 changed the sibling to a sibling's child, 
// the sibling's child can't be red, since no red parent can have a red child). */
// /* the following statements just force the red to be on the left of the left of the parent, 
//    or right of the right, so case six will rotate correctly. */
// 		if (
//                 (n == n->parent->left) &&
// 		        (s->right->color == BLACK) &&
// 		        (s->left->color == RED)
//            )
//         {
//             /* this last test is trivial too due to cases 2-4. */
// 			s->color = RED;
// 			s->left->color = BLACK;
// 			rotate_right(s);
// 		} else if (
//                 (n == n->parent->right) &&
// 		        (s->left->color == BLACK) &&
// 		        (s->right->color == RED)
//             ) 
//         {
//             /* this last test is trivial too due to cases 2-4. */
// 			s->color = RED;
// 			s->right->color = BLACK;
// 			rotate_left(s);
// 		}
// 	}
// 	delete_case6(n);
// }

// void delete_case6(node *n)
// {
// 	node *s = sibling(n);

// 	s->color = n->parent->color;
//     n->parent->color = BLACK;

// 	if (n == n->parent->left) {
//         s->right->color = BLACK;
// 		rotate_left(n->parent);
// 	} else {
// 		s->left->color = BLACK;
// 		rotate_right(n->parent);
// 	}
// }

// #endif

//======================================================================================
//======================================================================================

// remove(RBTNode<T>*&root, RBTNode<T>*node)
// {
// 	RBTNode<T> *child, *parent;
// 	RBTColor color;
// 	// Левый и правый узлы удаленного узла не пусты (не конечные узлы)
// 	if (node->left != NULL && node->right != NULL)     
// 	{
// 		RBTNode<T> *replace = node;
// 		// Найти узел-преемник (самый нижний левый узел правого поддерева текущего узла)
// 		replace = node->right;
// 		while (replace->left != NULL)
// 		{
// 			replace = replace->left;
// 		}
// 		// Случай, когда удаленный узел не является корневым узлом
// 		if (node->parent != NULL)
// 		{
// 			if (node->parent->left == node)
// 				node->parent->left = replace;
// 			else
// 				node->parent->right = replace;
// 		}
// 		// Ситуация с корневым узлом
// 		else
// 			root = replace;
// 		// child - это правильный узел, который заменяет узел и является узлом, который требует последующей корректировки
// 		// Поскольку замена является преемником, он не может иметь левого дочернего узла
// 		// Аналогично, у узла-предшественника не может быть правого дочернего узла
// 		child = replace->right;
// 		parent = replace->parent;
// 		color = replace->color;
		
// 		// Удаленный узел является родительским узлом замещающего узла (repalce)
// 		if (parent == node)
// 			parent = replace;
// 		else
// 		{
// 			// Существование дочернего узла
// 			if (child != NULL)
// 				child->parent = parent;
// 			parent->left = child;

// 			replace->right = node->right;
// 			node->right->parent = replace;
// 		}
// 		replace->parent = node->parent;
// 		replace->color = node->color;
// 		replace->left = node->left;
// 		node->left->parent = replace;
// 		if (color == Black)
// 			removeFixUp(root, child, parent);

// 		delete node;
// 		return;
// 	}
// 	// Когда в удаленном узле только левый (правый) узел пуст, найдите дочерний узел удаленного узла
// 	if (node->left != NULL)    
// 		child = node->left;
// 	else
// 		child = node->right;

// 	parent = node->parent;
// 	color = node->color;
// 	if (child) 
// 	{
// 		child->parent = parent;
// 	}
// 	// Удаленный узел не является корневым узлом
// 	if (parent)     
// 	{
// 		if (node == parent->left)
// 			parent->left = child;
// 		else
// 			parent->right = child;
// 	}
// 	// Удаленный узел является корневым узлом
// 	else
// 		RBTree::root = child;		

// 	if (color == Black)
// 	{
// 		removeFixUp(root, child, parent);
// 	}
// 	delete node;

// }
// template<class T>
// void RBTree<T>::removeFixUp(RBTNode<T>* &root, RBTNode<T>* node,RBTNode<T>*parent)
// {
// 	RBTNode<T>*othernode;
// 	while ((!node) || node->color == Black && node != RBTree::root)
// 	{
// 		if (parent->left == node)
// 		{
// 			othernode = parent->right;
// 			if (othernode->color == Red)
// 			{
// 				othernode->color = Black;
// 				parent->color = Red;
// 				leftRotate(root, parent);
// 				othernode = parent->right;
// 			}
// 			else
// 			{
// 				if (!(othernode->right) || othernode->right->color == Black)
// 				{
// 					othernode->left->color=Black;
// 					othernode->color = Red;
// 					rightRotate(root, othernode);
// 					othernode = parent->right;
// 				}
// 				othernode->color = parent->color;
// 				parent->color = Black;
// 				othernode->right->color = Black;
// 				leftRotate(root, parent);
// 				node = root;
// 				break;
// 			}
// 		}
// 		else
// 		{
// 			othernode = parent->left;
// 			if (othernode->color == Red)
// 			{
// 				othernode->color = Black;
// 				parent->color = Red;
// 				rightRotate(root, parent);
// 				othernode = parent->left;
// 			}
// 			if ((!othernode->left || othernode->left->color == Black) && (!othernode->right || othernode->right->color == Black))
// 			{
// 				othernode->color = Red;
// 				node = parent;
// 				parent = node->parent;
// 			}
// 			else
// 			{
// 				if (!(othernode->left) || othernode->left->color == Black)
// 				{
// 					othernode->right->color = Black;
// 					othernode->color = Red;
// 					leftRotate(root, othernode);
// 					othernode = parent->left;
// 				}
// 				othernode->color = parent->color;
// 				parent->color = Black;
// 				othernode->left->color = Black;
// 				rightRotate(root, parent);
// 				node = root;
// 				break;
// 			}
// 		}
// 	}
// 	if (node)
// 		node->color = Black;
// }