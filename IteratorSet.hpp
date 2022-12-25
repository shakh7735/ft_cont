#ifndef ITERATOR_SET_HPP
# define ITERATOR_SET_HPP

# include <cstddef>
# include "equal.hpp"
# include "iterator_traits.hpp"
# include "pair.hpp"
# include "Node.hpp"

namespace ft
{
    template <bool IsConst, class Val>
		class IteratorSet { 
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
				IteratorSet		()										{ ptr = NULL; }

				IteratorSet		(node *ptr)	: ptr(ptr)		{}
				
				template <bool B>
				IteratorSet	(const IteratorSet<B, Val> & other, typename ft::enable_if<!B>::type* = 0)	: ptr(other.getPtr())	{}

				IteratorSet &operator=	(const IteratorSet& other)	
				{ ptr = other.getPtr(); return (*this); }

				virtual ~IteratorSet	(void)	{}
			///////////////////////////////////////////////////////////////////////////

				template <bool B> bool	operator==	(const IteratorSet<B, Val> & x) const	{ return (ptr == x.getPtr()); }
				template <bool B> bool	operator!=	(const IteratorSet<B, Val> & x) const	{ return (ptr != x.getPtr()); }
				
				IteratorSet &	operator++	()		{ this->nextNode(); return (*this); }
				IteratorSet &	operator--	()		{ this->prevNode(); return (*this); }
				IteratorSet		operator++	(int)	{ IteratorSet<IsConst, Val> x(*this); this->nextNode(); return (x); }
				IteratorSet		operator--	(int)	{ IteratorSet<IsConst, Val> x(*this); this->prevNode(); return (x); }

				// value_type & 	operator*	() 	{ return (ptr->data); }
				// value_type *	operator->	() 	{ return (&(ptr->data)); }
				const value_type & 	operator*	() const	{ return (ptr->data); }
				const value_type *	operator->	() const	{ return (&(ptr->data)); }
				
				node  * 	getPtr	() const    { return ptr;     }
				
				IteratorSet<IsConst, Val> 	base	() 	{ return (*this);}
				
				operator  IteratorSet<false, Val> () const		{	return IteratorSet<false, Val>(ptr);		};
				
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
		class IteratorRevSet  { 
			public:
				typedef ft::node< Val >                                                             node;
				typedef typename		ft::conditional<IsRConst, const Val, Val>::type				value_type;
				
				typedef value_type*										pointer;
				typedef const value_type*								const_pointer;
				typedef value_type&										reference;
				typedef const value_type&								const_reference;
				typedef IteratorSet<IsRConst, Val>						iterator;
				typedef typename iterator::iterator_category			reverse_iterator_category;
			
			private:
				iterator b_it;

			public:
			////////////////---CONSTRUCTORS & DESTRUCTOR---////////////////////////////
				IteratorRevSet		()	{}

				// IteratorRevSet		(node *ptr) : ptr(ptr)	{}

				template <bool C>
				IteratorRevSet		(const IteratorSet<C, Val> & it)	: b_it(convert_base_to_rev(it))	{}
				
				template <bool C>
				IteratorRevSet	(const IteratorRevSet<C, Val> & other, typename ft::enable_if<!C>::type* = 0) : b_it(other.getIt())	{}

				IteratorRevSet &operator=	(const IteratorRevSet & other)	
				{ b_it = other.b_it; return (*this); }

				~IteratorRevSet	(void)									{}
			/////////////////////////////////////////////////////////////////////////

				template <bool C> bool	operator==	(const IteratorRevSet<C, Val> & x) const	{ return (getPtr() == x.getPtr()); }
				template <bool C> bool	operator!=	(const IteratorRevSet<C, Val> & x) const	{ return (getPtr() != x.getPtr()); }
				
				IteratorRevSet &	operator++	()		{ nextRev(); return (*this); } // ++it
				IteratorRevSet &	operator--	()		{ prevRev(); return (*this); } // --it;
				IteratorRevSet		operator++	(int)	{ IteratorRevSet<IsRConst, Val> x(*this); nextRev(); return (x); } // it++;
				IteratorRevSet		operator--	(int)	{ IteratorRevSet<IsRConst, Val> x(*this); prevRev(); return (x); }
				
				IteratorSet<IsRConst, Val>	base	() 	{ return (convert_rev_to_base(b_it)); }
				// value_type &	operator*	(void) 	{ return (getPtr()->data); }
				// value_type *	operator->	(void) 	{ return (&getPtr()->data); }
				const value_type &	operator*	(void) const	{ return (getPtr()->data); }
				const value_type *	operator->	(void) const	{ return (&getPtr()->data); }
				node  * 	getPtr		(void) const    { return b_it.getPtr();     };
				iterator		getIt		(void) const	{ return (b_it); }

			private:
				IteratorSet<IsRConst, Val> convert_base_to_rev(IteratorSet<IsRConst, Val> it)
				{
					IteratorSet<IsRConst, Val> tmp(it.getPtr());
					if ( it == --tmp)
					{
						IteratorSet<IsRConst, Val> ret(tmp.getPtr()->left);
						tmp = ret;
					}	
					else
					{
						IteratorSet<IsRConst,Val> ret(tmp.getPtr());
						tmp = ret;
					}
					return tmp;
				}

				IteratorSet<IsRConst, Val> convert_rev_to_base(IteratorSet<IsRConst, Val> it)
				{
					IteratorSet<IsRConst, Val> tmp(it.getPtr());
					if (getPtr()->nil)
						while (it != --tmp) it = tmp;
					else
					{
						++tmp;
						if (tmp.getPtr()->nil)
							--tmp;
					}
					IteratorSet<IsRConst, Val> ret(tmp.getPtr());
					return ret;
				}

				void nextRev()
				{
					IteratorSet<IsRConst, Val> tmp(getPtr());
					--b_it;
					if (tmp == b_it)
					{
						IteratorSet<IsRConst, Val> ret(getPtr()->left);
						b_it = ret;
					}
				}

				void prevRev()
				{
					IteratorSet<IsRConst, Val> tmp = b_it;
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