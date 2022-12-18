#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include <algorithm>
# include <stdexcept>

// # include "IteratorMap.hpp"
# include "iterator_traits.hpp"
# include "equal.hpp"
# include "pair.hpp"




namespace   ft {

	enum {BLACK = false, RED = true};
    template < class Key, class T, class Compare = ft::less<Key>,
				class A = std::allocator<ft::pair<const Key, T> > > 
    class map {

        public:
			typedef struct				s_node
			{
				ft::pair<const Key, T>	data;
				struct s_node *			left;
				struct s_node *			right;
				struct s_node *			parent;
				bool 					nil;
				bool					color;

				s_node (ft::pair<const Key, T> data) : data(data),left(0), 
                        right(0), parent (0), nil(true), color( BLACK )
					 { if (key() != Key()) nil = false; }
				s_node( void )    :   data(0), left(0), 
                        right(0), parent (0), nil(true), color( BLACK )  {}
				// s_node( const s_node &x)   { *this = x; }
				
				// s_node &operator=(const s_node &x){
				// 	if (*this != x) {
				// 		data = x.data; 
				// 		left = x.left; 
                //         right= x.right; 
				// 		parent = x.parent;
				// 	    nil = x.nil; 
				// 		color = x.color;
				// 	}
				// 	return *this;
				// }

				const Key &	key (void)	{ return (data.first); }
				T &			val (void)	{ return (data.second);}
			} 								node;

//============================================

		template <bool IsConst>
		class IteratorMap{ 
			public:
				typedef					ft::pair<const Key, T>										pair_type;
				typedef typename		ft::conditional<IsConst, const pair_type, pair_type>::type	value_type;
				typedef typename		ft::conditional<IsConst, const node, node>::type			node_type;
				typedef value_type*																	pointer;
				typedef const value_type*															const_pointer;
				typedef value_type&																	reference;
				typedef const value_type&															const_reference;
				typedef ft::bidirectional_iterator_tag												iterator_category;
				typedef					std::ptrdiff_t												difference_type;
				typedef					std::size_t													size_type;
			
			private:
				node_type *				ptr;

			public:
			////////////////---CONSTRUCTORS & DESTRUCTOR---////////////////////////////
				IteratorMap		()										{ ptr = NULL; }

				IteratorMap		(node_type *ptr)	: ptr(ptr)		{}
				
				template <bool B>
				IteratorMap	(const IteratorMap<B> & other, typename ft::enable_if<!B>::type* = 0)	: ptr(other.getPtr())	{}

				IteratorMap &operator=	(const IteratorMap & other)	
				{ ptr = other.ptr; return (*this); }

				virtual ~IteratorMap	(void)			{}
			///////////////////////////////////////////////////////////////////////////

				bool	operator==	(const IteratorMap & x) const	{ return (ptr == x.ptr); }
				bool	operator!=	(const IteratorMap & x) const	{ return (ptr != x.ptr); }
				
				IteratorMap &	operator++	()		{ this->nextNode(); return (*this); }
				IteratorMap &	operator--	()		{ this->prevNode(); return (*this); }
				IteratorMap		operator++	(int)	{ IteratorMap<IsConst> x(*this); this->nextNode(); return (x); }
				IteratorMap		operator--	(int)	{ IteratorMap<IsConst> x(*this); this->prevNode(); return (x); }

				value_type &	operator*	() const	{ return (ptr->data); }
				value_type *	operator->	() const	{ return (&(ptr->data)); }
				
				node_type  * 	getPtr	() const    { return ptr;     }
				
				IteratorMap<IsConst> 	base	() 	{ return (*this);}
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
						node_type *tmp = ptr;
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
					node_type *				tmp = ptr;
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

		template <bool IsRConst>
		class IteratorRevMap  { 
			public:
				typedef					ft::pair<const Key, T>										pair_type;
				typedef typename		ft::conditional<IsRConst, const pair_type, pair_type>::type	value_type;
				typedef typename		ft::conditional<IsRConst, const node, node>::type			node_type;
				typedef value_type*										pointer;
				typedef const value_type*								const_pointer;
				typedef value_type&										reference;
				typedef const value_type&								const_reference;
				typedef ft::bidirectional_iterator_tag					reverse_iterator_category;
				typedef IteratorMap<IsRConst>					iterator;
			
			private:
				iterator b_it;

			public:
			////////////////---CONSTRUCTORS & DESTRUCTOR---////////////////////////////
				IteratorRevMap		()	{}

				// IteratorRevMap		(node_type *ptr) :ptr(ptr)	{}

				template <bool C>
				IteratorRevMap		(const IteratorMap<C> & it)	: b_it(convert_base_to_rev(it))	{}
				
				template <bool C>
				IteratorRevMap	(const IteratorRevMap<C> & other, typename ft::enable_if<!C>::type* = 0) : b_it(other.getIt())	{}

				IteratorRevMap &operator=	(const IteratorRevMap & other)	
				{ b_it = other.b_it; return (*this); }

				~IteratorRevMap	(void)									{}
			///////////////////////////////////////////////////////////////////////////

				bool	operator==	(const IteratorRevMap & x) const	{ return (getPtr() == x.getPtr()); }
				bool	operator!=	(const IteratorRevMap & x) const	{ return (getPtr() != x.getPtr()); }
				
				IteratorRevMap &	operator++	()		{ nextRev(); return (*this); } // ++it
				IteratorRevMap &	operator--	()		{ prevRev(); return (*this); } // --it;
				IteratorRevMap		operator++	(int)	{ IteratorRevMap<IsRConst> x(*this); nextRev(); return (x); } // it++;
				IteratorRevMap		operator--	(int)	{ IteratorRevMap<IsRConst> x(*this); prevRev(); return (x); }
				
				IteratorMap<IsRConst>	base	() 	{ return (convert_rev_to_base(b_it)); }
				value_type &	operator*	(void) const	{ return (getPtr()->data); }
				value_type *	operator->	(void) const	{ return (&getPtr()->data); }
				node_type  * 	getPtr		(void) const    { return b_it.getPtr();     };
				iterator		getIt		(void) const	{ return (b_it); }

			private:
				IteratorMap<IsRConst> convert_base_to_rev(IteratorMap<IsRConst> it)
				{
					IteratorMap<IsRConst> tmp(it.getPtr());
					if ( it == --tmp)
					{
						IteratorMap<IsRConst> ret(tmp.getPtr()->left);
						tmp = ret;
					}	
					else
					{
						IteratorMap<IsRConst> ret(tmp.getPtr());
						tmp = ret;
					}
					return tmp;
				}

				IteratorMap<IsRConst> convert_rev_to_base(IteratorMap<IsRConst> it)
				{
					IteratorMap<IsRConst> tmp(it.getPtr());
					if (getPtr()->nil)
						while (it != --tmp) it = tmp;
					else
					{
						++tmp;
						if (tmp.getPtr()->nil)
							--tmp;
					}
					IteratorMap<IsRConst> ret(tmp.getPtr());
					return ret;
				}

				void nextRev()
				{
					IteratorMap<IsRConst> tmp(getPtr());
					--b_it;
					if (tmp == b_it)
					{
						IteratorMap<IsRConst> ret(getPtr()->left);
						b_it = ret;
					}
				}

				void prevRev()
				{
					IteratorMap<IsRConst> tmp = b_it;
					if (getPtr()->nil)
						while (tmp != --b_it) tmp = b_it;
					else
					{	++b_it;
						if (getPtr()->nil)
							--b_it;}
				}

		};
//==================end iterator====================

            typedef Key                                                     key_type;
			typedef T                                                       mapped_type;
			typedef ft::pair<key_type, mapped_type>                         value_type;
			typedef Compare                                                 key_compare;
            
            class value_compare : ft::binary_function<value_type, value_type, bool>
			{
				friend class map;
				protected:
					Compare comp;
					value_compare (Compare c) : comp(c) {}
				public:
					bool operator() (const value_type& x, const value_type& y) const
					{ return (comp(x.first, y.first)); }
			};
			
			// typedef A												allocator_type;
			typedef typename A::template rebind<node>::other				allocator_type;

			

			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;

			typedef		IteratorMap<false>									iterator;
			typedef		IteratorMap<true>									const_iterator;
			typedef 	IteratorRevMap<false>								reverse_iterator;
			typedef 	IteratorRevMap<true>								const_reverse_iterator;
			typedef typename iterator_traits<iterator>::difference_type		difference_type;
            typedef size_t	size_type;

        private:
            
            allocator_type		alloc;
			key_compare			comp;
			node *				root;
			node *				nil_node;
			
	
			node *new_node()
			{
				node * new_n = alloc.allocate(1);
				new_n->left = NULL;
				new_n->right = NULL;
				new_n->parent = NULL;
				new_n->nil = true;
				new_n->color = BLACK;
				return new_n;
			}

			node *new_node(const value_type& val)
			{

				node new_n(val);
				node *an= new_node();
				alloc.construct(an, new_n);
				an->left = nil_node;
				an->right = nil_node;
				an->color = RED;
				an->nil = false;
				return an;
			}

			node * leftXod  () const
			{
				node *				tmp;
				
				tmp = root;
				while (tmp->left && !tmp->nil && !tmp->left->nil)
					tmp = tmp->left;
				return tmp;
			}

			node * rightXod  () const
			{
				node *				tmp;
				
				tmp = root;
				while (tmp != nil_node && tmp->right != nil_node)
					tmp = tmp->right;
				nil_node->parent = tmp;
				return tmp;
			}

			void deletedTree()
			{
				if (!root)
					return;
				iterator it = begin();
				iterator end_it = end();
				node *f;

				while (it != end_it)
				{
					
					f = it.getPtr();
					it++;
					if (f == nil_node)
						break;
					alloc.destroy(f);
					alloc.deallocate(f, 1);
				}
				alloc.deallocate(nil_node, 1);
			}

		public:
// CONSTRUCTORS-------------------------------------------------------------------
            explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : alloc(alloc), comp(comp)	
            {
				nil_node = new_node();
				root = nil_node;
			}

            template <class InputIterator>  
            map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(),
					typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0): alloc(alloc), comp(comp) 
			{	nil_node = new_node(); root = nil_node; insert(first, last);	};
           
            map (const map& x)	{ nil_node = new_node(); root = nil_node; *this = x; };

			map & operator= (const map & x)
			{
				if (this == &x)
					return (*this);
				deletedTree();
				comp = x.comp;
				alloc = x.alloc;
				nil_node = new_node();
				root = nil_node;
				insert(x.begin(), x.end());
				return (*this);
			};
// DESTRUCTOR-------------------------------------------------------------------
            ~map()
			{	deletedTree();	};//
/*Iterators:----------------------------------------------------------------------
begin	Return iterator to beginning (public member function)
end	Return iterator to end (public member function)
rbegin	Return reverse iterator to reverse beginning (public member function)
rend	Return reverse iterator to reverse end (public member function)
cbegin	Return const_iterator to beginning (public member function)
cend	Return const_iterator to end (public member function)
crbegin	Return const_reverse_iterator to reverse beginning (public member function)
crend	Return const_reverse_iterator to reverse end (public member function)------*/
		iterator begin()				{	return (iterator(leftXod()));	};
		const_iterator begin() const	{	return (const_iterator(leftXod()));	};
		const_iterator cbegin() const	{	return (const_iterator(leftXod()));	};
				
		iterator end()					{	return (iterator(nil_node));	};
		const_iterator end() const 		{	return (const_iterator(nil_node));	};
		const_iterator cend() const 		{	return (const_iterator(nil_node));	};

		reverse_iterator rbegin ()		{	return (reverse_iterator(end()));	};
		const_reverse_iterator rbegin () const	{	return (const_reverse_iterator(end()));};

		reverse_iterator rend ()		{	return (reverse_iterator(begin()));	};
		const_reverse_iterator rend () const	{	return (const_reverse_iterator(begin()));	};

/*Capacity:------------------------------------------------------------------------
empty	Test whether container is empty (public member function)
size	Return container size (public member function)
max_size	Return maximum size (public member function)---------------------------*/
		
		// node *getRoot() { return root;} // cheking tree
		node *getNil() { return nil_node;} // cheking tree  

		bool empty () const { return root == nil_node; };

		size_type size () const 
		{
			size_type n = 0;
			for (const_iterator it = begin() ;  it != end() ; it++)
			{ n++; }
			return (n);
		};

		size_type max_size () const	{	return (alloc.max_size());	};

/*Element access:------------------------------------------------------------------
operator[]	Access element (public member function)
at	Access element (public member function)----------------------------------------*/
		mapped_type& operator[] (const key_type& k)
		{
			ft::pair<iterator,bool> it = insert(ft::make_pair(k, mapped_type()));
			return (it.first->second);
		}
		
		mapped_type& at (const key_type& k) {
			iterator x = find(k);	
			if(x == end())
				throw std::out_of_range("out out_of_range");
			return (x->second);	
			}

		const mapped_type& at (const key_type& k) const	{
			const_iterator x = find(k);	
			if(x == end())
				throw std::out_of_range("out out_of_range");
			return (x->second);	}

/*Modifiers:-----------------------------------------------------------------------
insert	Insert elements (public member function)							ok
erase	Erase elements (public member function)								ok
swap	Swap content (public member function)
clear	Clear content (public member function)
emplace	Construct and insert element (public member function)
emplace_hint	Construct and insert element with hint (public member function)----*/
			ft::pair<iterator,bool> insert (const value_type& val)
			{
				iterator it = find(val.first);
				if (!it.getPtr()->nil)
					return ft::make_pair(it, false);
				node *n = insertNode(val);
				return ft::make_pair(iterator(n), true);
			}
	
			iterator insert (iterator position, const value_type& val)
			{
				(void)position;
				node *n = insertNode(val);
				return iterator(n);
			}
				
			template <class InputIterator>  
			void insert (InputIterator first, InputIterator last,
						typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0 )
			{	while(first != last) insert(*first++);	}

			void erase (iterator position)	{	deleteNode(position.getPtr());	}

			size_type erase (const key_type& k)
			{
				iterator del = find(k);
				if (del.getPtr()->nil)
					return 0;
				erase(del);
				return 1;
			}

			void erase (iterator first, iterator last) { while(first != last) erase(first++); }
			
			void swap (map& x)	{ 
				node *tmp = root; 
				node *tmp_nil = nil_node;
				root = x.root;
				nil_node = x.nil_node;
				x.root = tmp;
				x.nil_node = tmp_nil;	
			};

			void clear() { deletedTree(); nil_node = new_node(); root = nil_node; };

/*Observers:-----------------------------------------------------------------------
key_comp	Return key comparison object (public member function)				ok
value_comp	Return value comparison object (public member function)-------------ok-*/
			key_compare key_comp (void) const 		{	return (key_compare());			};

			value_compare value_comp (void) const	{	return (value_compare(comp));	};

/*Operations:----------------------------------------------------------------------
find	Get iterator to element (public member function)   						OK
count	Count elements with a specific key (public member function)
lower_bound	Return iterator to lower bound (public member function)
upper_bound	Return iterator to upper bound (public member function)
equal_range	Get range of equal elements (public member function)-------------------*/
		iterator	find(const key_type& k)
        {
			value_type val = ft::make_pair( k, mapped_type() );
			node *f = root;
			while (!f->nil) 
			{
				if (comp(val.first, f->data.first))              	
					f = f->left;
				else if (comp(f->data.first, val.first))         	
					f = f->right;
				else					                        
					return iterator(f);
			}
			return end();
        }

		const_iterator find (const key_type& k) const
		{
			value_type val = ft::make_pair( k, mapped_type() );
			node *f = root;
			while (!f->nil) 
			{
				if (comp(val.first, f->data.first))              	
					f = f->left;
				else if (comp(f->data.first, val.first))         	
					f = f->right;
				else					                        
					return iterator(f);
			}
			return end();
		}

		size_type count (const key_type& k) const 
		{ return (find(k).getPtr()->nil ? 0 : 1); };

		iterator lower_bound (const key_type& k)
		{
			iterator it = begin();
			while (comp(it->first, k) && it != end())
				it++;
			return (it);
		}

		const_iterator lower_bound (const key_type& k) const
		{
			const_iterator it = begin();
			while (comp(it->first, k) && it != end())
				it++;
			return (it);
		}

		iterator upper_bound (const key_type& k)
		{
			iterator it = begin();
			while (!comp(k, it->first) && it != end())
				it++;
			return (it);
		}

		const_iterator upper_bound (const key_type& k) const
		{
			const_iterator it = begin();
			while (!comp(k, it->first) && it != end())
				it++;
			return (it);
		}

		ft::pair<iterator,iterator> equal_range (const key_type & k)
		{
			return (ft::make_pair(lower_bound(k), upper_bound(k)));
		}

		ft::pair<const_iterator,const_iterator> equal_range (const key_type & k) const
		{
			return (ft::make_pair(lower_bound(k), upper_bound(k)));
		}
		
/*Allocator:-----------------------------------------------------------------------
get_allocator	Get allocator (public member function)-----------------------------*/
			allocator_type get_allocator (void) const	{	return (allocator_type());	};

//RBtree function=============================================================================
		private:
//88888888888888888888888888888888888888888888888888888888888888888888888888888888888888888

			void rotateLeft(node *x) {

			/**************************
				*  rotate node x to left *
				**************************/

				node *y = x->right;

				/* establish x->right link */
				x->right = y->left;
				if (y->left != nil_node) y->left->parent = x;

				/* establish y->parent link */
				if (y != nil_node) y->parent = x->parent;
				if (x->parent) {
					if (x == x->parent->left)
						x->parent->left = y;
					else
						x->parent->right = y;
				} else {
					root = y;
				}

				/* link x and y */
				y->left = x;
				if (x != nil_node) x->parent = y;
			}

			void rotateRight(node *x) {

			/****************************
				*  rotate node x to right  *
				****************************/

				node *y = x->left;

				/* establish x->left link */
				x->left = y->right;
				if (y->right != nil_node) y->right->parent = x;

				/* establish y->parent link */
				if (y != nil_node) y->parent = x->parent;
				if (x->parent) {
					if (x == x->parent->right)
						x->parent->right = y;
					else
						x->parent->left = y;
				} else {
					root = y;
				}

				/* link x and y */
				y->right = x;
				if (x != nil_node) x->parent = y;
			}

			void insertFixup(node *x) {

			/*************************************
				*  maintain Red-Black tree balance  *
				*  after inserting node x           *
				*************************************/

				/* check Red-Black properties */
				while (x != root && x->parent->color == RED) {
					/* we have a violation */
					if (x->parent == x->parent->parent->left) {
						node *y = x->parent->parent->right;
						if (y->color == RED) {

							/* uncle is RED */
							x->parent->color = BLACK;
							y->color = BLACK;
							x->parent->parent->color = RED;
							x = x->parent->parent;
						} else {

							/* uncle is BLACK */
							if (x == x->parent->right) {
								/* make x a left child */
								x = x->parent;
								rotateLeft(x);
							}

							/* recolor and rotate */
							x->parent->color = BLACK;
							x->parent->parent->color = RED;
							rotateRight(x->parent->parent);
						}
					} else {

						/* mirror image of above code */
						node *y = x->parent->parent->left;
						if (y->color == RED) {

							/* uncle is RED */
							x->parent->color = BLACK;
							y->color = BLACK;
							x->parent->parent->color = RED;
							x = x->parent->parent;
						} else {

							/* uncle is BLACK */
							if (x == x->parent->left) {
								x = x->parent;
								rotateRight(x);
							}
							x->parent->color = BLACK;
							x->parent->parent->color = RED;
							rotateLeft(x->parent->parent);
						}
					}
				}
				root->color = BLACK;
			}

			node *insertNode(const value_type& data) {
				node *current, *parent, *x;

			/***********************************************
				*  allocate node for data and insert in tree  *
				***********************************************/

				/* find where node belongs */
				current = root;
				parent = 0;
				while (current != nil_node) {
					if (equal_val(data.first, current->data.first)) return (current);
					parent = current;
					current = (comp(data.first, current->data.first) ? current->left : current->right);
				}

				/* setup new node */
				x = new_node(data);
				x->parent = parent;
				x->left = nil_node;
				x->right = nil_node;
				x->color = RED;

				/* insert node in tree */
				if(parent) {
					if(comp(data.first, parent->data.first))
						parent->left = x;
					else
						parent->right = x;
				} else {
					root = x;
				}

				insertFixup(x);
				rightXod();
				return(x);
			}

			void deleteFixup(node *x) {

			/*************************************
				*  maintain Red-Black tree balance  *
				*  after deleting node x            *
				*************************************/

				while (x != root && x->color == BLACK) {
					if (x == x->parent->left) {
						node *w = x->parent->right;
						if (w->color == RED) {
							w->color = BLACK;
							x->parent->color = RED;
							rotateLeft (x->parent);
							w = x->parent->right;
						}
						if (w->left->color == BLACK && w->right->color == BLACK) {
							w->color = RED;
							x = x->parent;
						} else {
							if (w->right->color == BLACK) {
								w->left->color = BLACK;
								w->color = RED;
								rotateRight (w);
								w = x->parent->right;
							}
							w->color = x->parent->color;
							x->parent->color = BLACK;
							w->right->color = BLACK;
							rotateLeft (x->parent);
							x = root;
						}
					} else {
						node *w = x->parent->left;
						if (w->color == RED) {
							w->color = BLACK;
							x->parent->color = RED;
							rotateRight (x->parent);
							w = x->parent->left;
						}
						if (w->right->color == BLACK && w->left->color == BLACK) {
							w->color = RED;
							x = x->parent;
						} else {
							if (w->left->color == BLACK) {
								w->right->color = BLACK;
								w->color = RED;
								rotateLeft (w);
								w = x->parent->left;
							}
							w->color = x->parent->color;
							x->parent->color = BLACK;
							w->left->color = BLACK;
							rotateRight (x->parent);
							x = root;
						}
					}
				}
				x->color = BLACK;
			}

			void deleteNode(node *z) {
				node *x, *y;

			/*****************************
				*  delete node z from tree  *
				*****************************/

				if (!z || z == nil_node) return;
				if (z->left == nil_node || z->right == nil_node) {
					/* y has a nil_node node as a child */
					y = z;
				} else {
					/* find tree successor with a nil_node node as a child */
					y = z->right;
					while (y->left != nil_node) y = y->left;
				}

				/* x is y's only child */
				
				if (y->left != nil_node)
					x = y->left;
				else
					x = y->right;

				/* remove y from the parent chain */
				x->parent = y->parent;
				if (y->parent)
					if (y == y->parent->left)
						y->parent->left = x;
					else
						y->parent->right = x;
				else
					root = x;

				if (y != z) z = copy_data(z, y); // z->data = y->data;
				
				if (y->color == BLACK && x != nil_node) 	deleteFixup (x);
				rightXod();
				if (y != nil_node) {alloc.destroy(y); alloc.deallocate(y, 1);}
			}

			node *copy_data(node * a, node * b)
			{
				if (a == nil_node || a == b) return a; 
				node *c = new_node(b->data);
				c->parent = a->parent;
				c->left = a->left;
				c->right = a->right;
				c->nil = a->nil;
				c->color = a->color;
				if (a->left->parent == a) a->left->parent = c;
				if (a->right->parent == a) a->right->parent = c;
				if (a->parent)
					(a->parent->left == a ? a->parent->left = c : a->parent->right = c);
				if (root == a)
					root = c;
				alloc.destroy(a);
				alloc.deallocate(a, 1);
				return c;
			}

			bool equal_val (const key_type & lhs, const key_type & rhs) const
			{
				return (comp(lhs, rhs) == false && comp(rhs, lhs) == false);
			}

//88888888888888888888888888888888888888888888888888888888888888888888888888888888888
//END RBtree =================================================================================

//=============================================================================================
    };// end class MAP
//=============================================================================================


	template <class Key, class T, class Compare, class Alloc>
	bool operator== (const map<Key,T,Compare,Alloc> & lhs, const map<Key,T,Compare,Alloc> & rhs)
	{		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<  (const map<Key,T,Compare,Alloc> & lhs, const map<Key,T,Compare,Alloc> & rhs)
	{		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator!= (const map<Key,T,Compare,Alloc> & lhs, const map<Key,T,Compare,Alloc> & rhs)
	{		return (!(lhs == rhs));	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<= (const map<Key,T,Compare,Alloc> & lhs, const map<Key,T,Compare,Alloc> & rhs)
	{		return (!(rhs < lhs));	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>  (const map<Key,T,Compare,Alloc> & lhs, const map<Key,T,Compare,Alloc> & rhs)
	{		return (rhs < lhs);	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>= (const map<Key,T,Compare,Alloc> & lhs, const map<Key,T,Compare,Alloc> & rhs)
	{		return (!(lhs < rhs));	}

	template <class Key, class T, class Compare, class Alloc>
	void swap (map<Key,T,Compare,Alloc> & x, map<Key,T,Compare,Alloc> & y)
	{	x.swap(y);	}


} // endnamespace ft

#endif