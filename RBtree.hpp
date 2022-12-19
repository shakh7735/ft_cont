// #ifndef NODE_HPP
// # define NODE_HPP

// #include <iostream>

// # include <stdexcept>
// # include "pair.hpp"
// # include "map.hpp"

// # define RED 0
// # define BLACK 1

// namespace ft
// {
//      template < class Key, class T, class Compare = ft::less<Key>,
// 				class A = std::allocator<ft::pair<const Key, T> > > 
//     struct				s_node
// 			{
// 				ft::pair<const Key, T>	data;
// 				struct s_node *			left;
// 				struct s_node *			right;
// 				struct s_node *			parent;
// 				bool 					nil;
// 				bool					color;

// 				s_node (ft::pair<const Key, T> data) : data(data),left(0), 
//                         right(0), parent (0), nil(true), color( BLACK )
// 					 { if (key() != Key()) nil = false; }
// 				s_node( void )    :   data(0), left(0), 
//                         right(0), parent (0), nil(true), color( BLACK )  {}

// 				const Key &	key (void)	{ return (data.first); }
// 				T &			val (void)	{ return (data.second);}
// 			} ;

// }
// #endif