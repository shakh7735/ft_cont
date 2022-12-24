#ifndef ITERATOR_MAP_HPP
# define ITERATOR_MAP_HPP

# include <cstddef>
# include "equal.hpp"
# include "iterator_traits.hpp"
# include "pair.hpp"
# include "Node.hpp"

namespace ft
{
    template <bool IsConst, class Val>
		class IteratorMap { 
			public:
				typedef typename		ft::conditional<IsConst, const Val, Val>::type	            value_type;
				typedef ft::node< Val >                                                             node;
				typedef value_type*																	pointer;
				typedef const value_type*															const_pointer;
				typedef value_type&																	reference;
				typedef const value_type&															const_reference;
				typedef ft::bidirectional_iterator_tag												iterator_category;
				typedef					ptrdiff_t												difference_type;
				typedef					std::size_t													size_type;
			
			private:
				node *				ptr;

			public:
			////////////////---CONSTRUCTORS & DESTRUCTOR---////////////////////////////
				IteratorMap		()										{ ptr = NULL; }

				IteratorMap		(node *ptr)	: ptr(ptr)		{}
				
				template <bool B>
				IteratorMap	(const IteratorMap<B, Val> & other, typename ft::enable_if<!B>::type* = 0)	: ptr(other.getPtr())	{}

				IteratorMap &operator=	(const IteratorMap& other)	
				{ ptr = other.getPtr(); return (*this); }

				virtual ~IteratorMap	(void)	{}
			///////////////////////////////////////////////////////////////////////////

				template <bool B> bool	operator==	(const IteratorMap<B, Val> & x) const	{ return (ptr == x.getPtr()); }
				template <bool B> bool	operator!=	(const IteratorMap<B, Val> & x) const	{ return (ptr != x.getPtr()); }
				
				IteratorMap &	operator++	()		{ this->nextNode(); return (*this); }
				IteratorMap &	operator--	()		{ this->prevNode(); return (*this); }
				IteratorMap		operator++	(int)	{ IteratorMap<IsConst, Val> x(*this); this->nextNode(); return (x); }
				IteratorMap		operator--	(int)	{ IteratorMap<IsConst, Val> x(*this); this->prevNode(); return (x); }

				value_type &	operator*	() const	{ return (ptr->data); }
				value_type *	operator->	() const	{ return (&(ptr->data)); }
				
				node  * 	getPtr	() const    { return ptr;     }
				
				IteratorMap<IsConst, Val> 	base	() 	{ return (*this);}
				
				// operator  IteratorMap<false, Val>  () const		{	return IteratorMap<false, Val>(ptr);		};
				
			private:

				void nextNode()
				{
					if (ptr->nil)
						return ;
					if (!ptr->right->nil)
					{
						ptr = ptr->right;
						while (!ptr->nil && !ptr->left->nil)
							ptr = ptr->left;
					}
					else
					{
						node *tmp = ptr;
						while (tmp->parent && tmp == tmp->parent->right)
							tmp = tmp->parent;
						if (tmp->parent)
							ptr = tmp->parent;
						else
							ptr = ptr->right;
					}
				};

				void prevNode()
				{
					node *				tmp = ptr;
					if (!ptr->nil && !ptr->left->nil)
					{	
						ptr = ptr->left;
						while (!ptr->right->nil) ptr = ptr->right;
					}
					else if(ptr->parent)
					{
						if (ptr->nil)
							ptr = ptr->parent;
						else
						{
							while (tmp->parent && tmp == tmp->parent->left)
								tmp = tmp->parent;
							if (tmp->parent)
								ptr = tmp->parent;
						}
					}
				};
		};

		template <bool IsRConst, class Val>
		class IteratorRevMap  { 
			public:
				typedef ft::node< Val >                                                             node;
				typedef typename		ft::conditional<IsRConst, const Val, Val>::type				value_type;
				
				typedef value_type*										pointer;
				typedef const value_type*								const_pointer;
				typedef value_type&										reference;
				typedef const value_type&								const_reference;
				typedef IteratorMap<IsRConst, Val>						iterator;
				typedef typename iterator::iterator_category			reverse_iterator_category;
			
			private:
				iterator b_it;

			public:
			////////////////---CONSTRUCTORS & DESTRUCTOR---////////////////////////////
				IteratorRevMap		()	{}

				// IteratorRevMap		(node *ptr) : ptr(ptr)	{}

				template <bool C>
				IteratorRevMap		(const IteratorMap<C, Val> & it)	: b_it(convert_base_to_rev(it))	{}
				
				template <bool C>
				IteratorRevMap	(const IteratorRevMap<C, Val> & other, typename ft::enable_if<!C>::type* = 0) : b_it(other.getIt())	{}

				IteratorRevMap &operator=	(const IteratorRevMap & other)	
				{ b_it = other.b_it; return (*this); }

				~IteratorRevMap	(void)									{}
			/////////////////////////////////////////////////////////////////////////

				template <bool C> bool	operator==	(const IteratorRevMap<C, Val> & x) const	{ return (getPtr() == x.getPtr()); }
				template <bool C> bool	operator!=	(const IteratorRevMap<C, Val> & x) const	{ return (getPtr() != x.getPtr()); }
				
				IteratorRevMap &	operator++	()		{ nextRev(); return (*this); } // ++it
				IteratorRevMap &	operator--	()		{ prevRev(); return (*this); } // --it;
				IteratorRevMap		operator++	(int)	{ IteratorRevMap<IsRConst, Val> x(*this); nextRev(); return (x); } // it++;
				IteratorRevMap		operator--	(int)	{ IteratorRevMap<IsRConst, Val> x(*this); prevRev(); return (x); }
				
				IteratorMap<IsRConst, Val>	base	() 	{ return (convert_rev_to_base(b_it)); }
				value_type &	operator*	(void) const	{ return (getPtr()->data); }
				value_type *	operator->	(void) const	{ return (&getPtr()->data); }
				node  * 	getPtr		(void) const    { return b_it.getPtr();     };
				iterator		getIt		(void) const	{ return (b_it); }

			private:
				IteratorMap<IsRConst, Val> convert_base_to_rev(IteratorMap<IsRConst, Val> it)
				{
					IteratorMap<IsRConst, Val> tmp(it.getPtr());
					if ( it == --tmp)
					{
						IteratorMap<IsRConst, Val> ret(tmp.getPtr()->left);
						tmp = ret;
					}	
					else
					{
						IteratorMap<IsRConst,Val> ret(tmp.getPtr());
						tmp = ret;
					}
					return tmp;
				}

				IteratorMap<IsRConst, Val> convert_rev_to_base(IteratorMap<IsRConst, Val> it)
				{
					IteratorMap<IsRConst, Val> tmp(it.getPtr());
					if (getPtr()->nil)
						while (it != --tmp) it = tmp;
					else
					{
						++tmp;
						if (tmp.getPtr()->nil)
							--tmp;
					}
					IteratorMap<IsRConst, Val> ret(tmp.getPtr());
					return ret;
				}

				void nextRev()
				{
					IteratorMap<IsRConst, Val> tmp(getPtr());
					--b_it;
					if (tmp == b_it)
					{
						IteratorMap<IsRConst, Val> ret(getPtr()->left);
						b_it = ret;
					}
				}

				void prevRev()
				{
					IteratorMap<IsRConst, Val> tmp = b_it;
					if (getPtr()->nil)
						while (tmp != --b_it) tmp = b_it;
					else
					{	++b_it;
						if (getPtr()->nil)
							--b_it;}
				}

		};
}

#endif