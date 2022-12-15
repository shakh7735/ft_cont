// #ifndef ITERATOR_MAP_HPP
// # define ITERATOR_MAP_HPP

// # include <cstddef>
// # include "equal.hpp"
// # include "iterator_traits.hpp"
// # include "pair.hpp"

// namespace ft
// {
//     enum {BLACK = false, RED = true};
//     template < class Val> 
//     struct				s_node
//     {
//         typedef Val             value;
//         value                 	data;
//         struct s_node *			left;
//         struct s_node *			right;
//         struct s_node *			parent;
//         bool 					nil;
//         bool					color;

//         s_node (Val data) : data(data) {}
//         s_node( void )    :   data(0), left(0), 
//                 right(0), parent (0), nil(true), color( BLACK )  {}
//     } ;

//     template <bool IsConst, class data>
//     class IteratorMap{ 
//         public:
//             typedef					ft::s_node<data>									        node;
//             typedef typename		ft::conditional<IsConst, const data, data>::type	        value_type;
//             typedef typename		ft::conditional<IsConst, const node, node>::type			node_type;
//             typedef value_type*																	pointer;
//             typedef const value_type*															const_pointer;
//             typedef value_type&																	reference;
//             typedef const value_type&															const_reference;
//             typedef ft::bidirectional_iterator_tag												iterator_category;
//             typedef					std::ptrdiff_t												difference_type;
//             typedef					std::size_t													size_type;
        
//         private:
//             node_type *				ptr;

//         public:
//         ////////////////---CONSTRUCTORS & DESTRUCTOR---////////////////////////////
//             IteratorMap		()										{ ptr = NULL; }

//             IteratorMap		(node_type *ptr)	: ptr(ptr)		{}
            
//             template <bool B>
//             IteratorMap	(const IteratorMap<B, value_type> & other, typename ft::enable_if<!B>::type* = 0)	: ptr(other.getPtr())	{}

//             IteratorMap &operator=	(const IteratorMap & other)	
//             { ptr = other.ptr; return (*this); }

//             virtual ~IteratorMap	(void)			{}
//         ///////////////////////////////////////////////////////////////////////////

//             bool	operator==	(const IteratorMap & x) const	{ return (ptr == x.ptr); }
//             bool	operator!=	(const IteratorMap & x) const	{ return (ptr != x.ptr); }
            
//             IteratorMap &	operator++	()		{ this->nextNode(); return (*this); }
//             IteratorMap &	operator--	()		{ this->prevNode(); return (*this); }
//             IteratorMap		operator++	(int)	{ IteratorMap<IsConst, value_type> x(*this); this->nextNode(); return (x); }
//             IteratorMap		operator--	(int)	{ IteratorMap<IsConst, value_type> x(*this); this->prevNode(); return (x); }

//             value_type &	operator*	() const	{ return (ptr->data); }
//             value_type *	operator->	() const	{ return (&(ptr->data)); }
            
//             node_type  * 	getPtr	() const    { return ptr;     }
            
//             IteratorMap<IsConst, data> 	base	() 	{ return (*this);}
//         private:

//             void nextNode()
//             {
//                 if (ptr->nil)
//                     return ;
//                 if (!ptr->right->nil)
//                 {
//                     ptr = ptr->right;
//                     while (!ptr->nil && !ptr->left->nil)
//                         ptr = ptr->left;
//                 }
//                 else
//                 {
//                     node_type *tmp = ptr;
//                     while (tmp->parent && tmp == tmp->parent->right)
//                         tmp = tmp->parent;
//                     if (tmp->parent)
//                         ptr = tmp->parent;
//                     else
//                         ptr = ptr->right;
//                 }
//             };

//             void prevNode()
//             {
//                 node_type *				tmp = ptr;
//                 if (!ptr->nil && !ptr->left->nil)
//                 {	
//                     ptr = ptr->left;
//                     while (!ptr->right->nil) ptr = ptr->right;
//                 }
//                 else if(ptr->parent)
//                 {
//                     if (ptr->nil)
//                         ptr = ptr->parent;
//                     else
//                     {
//                         while (tmp->parent && tmp == tmp->parent->left)
//                             tmp = tmp->parent;
//                         if (tmp->parent)
//                             ptr = tmp->parent;
//                     }
//                 }
//             };
//     };


//     template <bool IsRConst, class data>
// 		class IteratorRevMap  { 
// 			public:
// 			typedef					ft::s_node<data>									        node;
//             typedef typename		ft::conditional<IsRConst, const data, data>::type	        value_type;
//             typedef typename		ft::conditional<IsRConst, const node, node>::type			node_type;
            
				
// 				typedef value_type*										pointer;
// 				typedef const value_type*								const_pointer;
// 				typedef value_type&										reference;
// 				typedef const value_type&								const_reference;
// 				typedef ft::bidirectional_iterator_tag					reverse_iterator_category;
// 				typedef IteratorMap<IsRConst, data>					iterator;
			
// 			private:
// 				iterator b_it;

// 			public:
// 			////////////////---CONSTRUCTORS & DESTRUCTOR---////////////////////////////
// 				IteratorRevMap		()	{}

// 				// IteratorRevMap		(node_type *ptr) :ptr(ptr)	{}

// 				template <bool C, data>
// 				IteratorRevMap		(const IteratorMap<C, data> & it)	: b_it(convert_base_to_rev(it))	{}
				
// 				template <bool C, data>
// 				IteratorRevMap	(const IteratorRevMap<C, data> & other, typename ft::enable_if<!C>::type* = 0) : b_it(other.getIt())	{}

// 				IteratorRevMap &operator=	(const IteratorRevMap & other)	
// 				{ b_it = other.b_it; return (*this); }

// 				~IteratorRevMap	(void)									{}
// 			///////////////////////////////////////////////////////////////////////////

// 				bool	operator==	(const IteratorRevMap & x) const	{ return (getPtr() == x.getPtr()); }
// 				bool	operator!=	(const IteratorRevMap & x) const	{ return (getPtr() != x.getPtr()); }
				
// 				IteratorRevMap &	operator++	()		{ nextRev(); return (*this); } // ++it
// 				IteratorRevMap &	operator--	()		{ prevRev(); return (*this); } // --it;
// 				IteratorRevMap		operator++	(int)	{ IteratorRevMap<IsRConst, data> x(*this); nextRev(); return (x); } // it++;
// 				IteratorRevMap		operator--	(int)	{ IteratorRevMap<IsRConst, data> x(*this); prevRev(); return (x); }
				
// 				IteratorMap<IsRConst, data>	base	() 	{ return (convert_rev_to_base(b_it)); }
// 				value_type &	operator*	(void) const	{ return (getPtr()->data); }
// 				value_type *	operator->	(void) const	{ return (&getPtr()->data); }
// 				node_type  * 	getPtr		(void) const    { return b_it.getPtr();     };
// 				iterator		getIt		(void) const	{ return (b_it); }

// 			private:
// 				IteratorMap<IsRConst, data> convert_base_to_rev(IteratorMap<IsRConst, data> it)
// 				{
// 					IteratorMap<IsRConst, data> tmp(it.getPtr());
// 					if ( it == --tmp)
// 					{
// 						IteratorMap<IsRConst, data> ret(tmp.getPtr()->left);
// 						tmp = ret;
// 					}	
// 					else
// 					{
// 						IteratorMap<IsRConst, data> ret(tmp.getPtr());
// 						tmp = ret;
// 					}
// 					return tmp;
// 				}

// 				IteratorMap<IsRConst, data> convert_rev_to_base(IteratorMap<IsRConst, data> it)
// 				{
// 					IteratorMap<IsRConst, data> tmp(it.getPtr());
// 					if (getPtr()->nil)
// 						while (it != --tmp) it = tmp;
// 					else
// 					{
// 						++tmp;
// 						if (tmp.getPtr()->nil)
// 							--tmp;
// 					}
// 					IteratorMap<IsRConst, data> ret(tmp.getPtr());
// 					return ret;
// 				}

// 				void nextRev()
// 				{
// 					IteratorMap<IsRConst, data> tmp(getPtr());
// 					--b_it;
// 					if (tmp == b_it)
// 					{
// 						IteratorMap<IsRConst, data> ret(getPtr()->left);
// 						b_it = ret;
// 					}
// 				}

// 				void prevRev()
// 				{
// 					IteratorMap<IsRConst, data> tmp = b_it;
// 					if (getPtr()->nil)
// 						while (tmp != --b_it) tmp = b_it;
// 					else
// 					{	++b_it;
// 						if (getPtr()->nil)
// 							--b_it;}
// 				}

// 		};

// }

// #endif