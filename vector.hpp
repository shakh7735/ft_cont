#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "Iterator.hpp"
# include "equal.hpp"
# include "iterator_traits.hpp"

# include <memory>
# include <algorithm>
# include <stdexcept>
# include <iostream>

    namespace   ft {
    
    template<typename T, typename A = std::allocator<T> >
// class VECTOR ****************************************************************
    class vector {
        
        public :
            typedef	T														value_type;
			typedef A   													allocator_type;

			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;

			typedef ft::iterator< T >										iterator;
			typedef ft::iterator< const T >									const_iterator;
			typedef ft::reverse_iterator<iterator>							reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;
			typedef typename iterator_traits<iterator>::difference_type		difference_type;
			typedef size_t													size_type;
        
        private:
            
            allocator_type	 _alloc; 
            size_type _capacity;
            value_type *arr;
            size_type _size;
           
            
            size_type increasingCapacity(size_type size){ return ((size == 0? 1 : size * 2)); }
           
            void deallocateArray()
            {
                if (_capacity == 0)
                    return ;
                while (_size > 0)
                        pop_back();
                if (_capacity > 0)
                    _alloc.deallocate(arr, _capacity);
                _capacity = 0;
            }

        public:
// CONSTRUCTORS-------------------------------------------------------------------
            
            explicit	vector( const allocator_type& alloc = allocator_type() )	:	
                        _alloc(alloc), _capacity(0), arr(NULL),	_size(0) {};

			explicit	vector( size_type n, const value_type& val = value_type(),
							const allocator_type& alloc = allocator_type() )    : _alloc(alloc), _capacity(0), arr(NULL), _size(0)		
            {	
                
                if (n == 0)
                    return;
                reserve(n);
                while (_size < n) 
                    push_back(val);
            };

			template <class InputIterator>
			vector( InputIterator first, InputIterator last, 
                const allocator_type& alloc = allocator_type(), 
                typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)	:  
                _alloc(alloc), _capacity(0), arr(NULL), _size(0) 	
            {	insert(begin(), first, last);	};

			vector( const vector& x )								
            {  *this = x;   };

			vector&					operator = (const vector& x)
			{
                if (*this == x)
                    return *this;
                deallocateArray();
                _alloc = x.get_allocator();
                _capacity = x.capacity();
                arr = _alloc.allocate(_capacity);
                assign(x.begin(), x.end());
				return *this;
			}
// DESTRUCTOR-------------------------------------------------------------------
            ~vector()   { deallocateArray(); } //   std::cout << "Delete vector.\n"; }

// Element access:--------------------------------------------------------------
        T &operator[](size_type index){
            if (index > _size)
                throw std::out_of_range("out out_of_range");
            return (arr[index]);
        }

        const T &operator[] (size_type index) const {
            if (index > _size)
                throw std::out_of_range("out out_of_range");
            return (arr[index]);
        }

        T &at (size_type n)
        {
            if (n >= _size)
                throw std::out_of_range("_M_range_check");
            return *(arr + n);
        }
        
        const T &at (size_type n) const
        {
            if (n >= _size)
                throw std::out_of_range("_M_range_check");
            return *(arr + n);
        }
        
        T& front()  {
            if (empty())
                throw std::out_of_range("Vector:: is empty stack");
            return *arr;
        }
        
        const T& front() const  { 
            if (empty())
                throw std::out_of_range("Vector:: is empty stack");
            return *arr;
        }
        
        T& back()  {
            if (empty())
                throw std::out_of_range("Vector:: is empty stack");
            return *(arr + _size - 1);
        }
        
        const T& back() const   {
            if (empty())
                throw std::out_of_range("Vector:: is empty stack");
            return *(arr + _size - 1);
        }
        
        T* data() { return arr; }
        
        T* data() const { return arr; }
        
//==============================================================================

// Capacity:--------------------------------------------------------------------
        
        size_type size() const { return (_size); }
        
        size_type max_size() const { return _alloc.max_size(); }
        
        void resize (size_type n, const value_type& val = value_type())
        {
            reserve(n);
            while (n < _size)	
                pop_back();
			while (n > _size)	
			    push_back(val);
        }

        size_type capacity() const { return (_capacity); }
        
        bool empty() const  { return (_size == 0); }

        void reserve( size_type new_cap ) {
                if (new_cap <= _capacity)
                    return;
                if (new_cap > max_size())
                    throw std::length_error("_Maximum_size_out");
                size_type last_cap = _capacity;
                _capacity = new_cap;
                T* tmp = _alloc.allocate(_capacity);
                size_type s = 0;
                while (s < _size){
                    _alloc.construct( tmp + s, arr[s]);
                    s++;
                }
                size_type i = 0;
                while (i < _size) _alloc.destroy(arr + i++);   
                if (last_cap > 0)
                    _alloc.deallocate(arr, last_cap);
                arr = tmp;
            }
            
        void shrink_to_fit() { _capacity = _size; }
        
//==============================================================================

// Modifiers:-------------------------------------------------------------------
        template <class InputIterator>
		void		assign( InputIterator first, InputIterator last,
							typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0 )
        {
            size_type n = ft::distance(first, last);
            clear();
            reserve(n);
            while (n > _size)	
	    	    push_back(*(first++));
        }
        
        void assign (size_type n, const value_type& val)
        {
            clear();
            reserve(n);
            while (n > _size)	
	    	    push_back(val);
        }
        
        void push_back(const value_type& elem) {
            if (_size >= _capacity)
                reserve(increasingCapacity(_size));
            _alloc.construct(arr + _size, elem);
            _size++;
        }
        
        void pop_back(void) {
            if (_size > 0) {
                _alloc.destroy(&(arr [_size - 1]));
                _size--;
            }
        }
        
        iterator insert (iterator position, const T& val) { 
            iterator it = begin();
            size_t i = 0;
            for (; i < _size ; i++)
                if (it++ == position)
                    break;
            insert(position, 1, val); 
            return (iterator(&arr[i]));
        }
        
        void insert (iterator position, size_type n, const T& val)
        {
            iterator pos = begin();
            size_type new_cap = _capacity;
            size_type new_size = _size + n;
            
            if (new_size > _capacity)
                new_cap = new_size;
            if (new_cap == 0 || n == 0)
                return;
            if (new_cap > max_size())
                throw std::length_error("_Maximum_size_out");
            value_type *tmp = _alloc.allocate(new_cap);
            size_type i = 0;
            size_type a = 0;
            while(i < new_size){
                if (pos == position) {
                    while (n > 0) {
                        _alloc.construct(&tmp[i++], val);
                        n--;
                    }
                }
                else
                    _alloc.construct(&tmp[i++], arr[a++]);
                ++pos;
            }
            deallocateArray();
            arr = tmp;
            _capacity = new_cap;
            _size = new_size;
        }
        
           
        template <class InputIterator>
			void	insert( iterator position, InputIterator first, InputIterator last,
							typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
        {
            iterator pos = begin();
            size_type new_cap = _capacity;
            size_type dist = ft::distance(first, last);
            size_type new_size = _size + dist;
            
            if (new_size > _capacity)
                new_cap = new_size;
            
            if (new_cap == 0 || dist == 0 )
                return ;
            // reserve(new_cap);
            
            // value_type * tmp = _alloc.allocate(new_cap);
            
            if (new_cap > max_size())
                throw std::length_error("_Maximum_size_out");
            value_type *tmp = _alloc.allocate(new_cap);
            size_type i = 0;
            size_type a = 0;
            while(i < new_size){
                if (pos == position) {
                    while (first != last) {
                        _alloc.construct(&tmp[i++], (*first++));
                    }
                }
                else
                    _alloc.construct(&tmp[i++], arr[a++]);
                ++pos;
            }
            deallocateArray();
            arr = tmp;
            _capacity = new_cap;
            _size = new_size;
        }

        iterator erase (iterator position) { return erase(position, position + 1); }
        
        iterator erase (iterator first, iterator last)
        {
            int ind_first = -1;
            // int ind_last = -1;
            size_type dist = ft::distance(first, last);
            
            iterator it = begin();
            if (dist == 0)
                return it;

            for (size_type i = 0; i < _size; i++) {
                if (it == first) {
                    ind_first = (int)i;
                }
                if ( ind_first != -1 ) {
                    _alloc.destroy(&(*it));
                    if (i + dist < _size) {
                        _alloc.construct(&(*it), arr[i + dist]);
                    }
                }
                it++;
            }
            _size -= dist;
            return first ;
        }
        
        void swap( vector& other ) {
                ft::swap(_alloc, other._alloc);
				ft::swap(_capacity, other._capacity);
				ft::swap(arr, other.arr);
				ft::swap(_size, other._size);
        }
        
        void clear() {   while (size()) pop_back();  }
        
 // ============================================================================
 
// Iterators:-------------------------------------------------------------------
        iterator                begin()         { return iterator(arr);                 };
        iterator                end()           { return iterator(arr+_size);           };
        const_iterator          begin() const   { return const_iterator(arr);           };
        const_iterator          end() const     { return const_iterator (arr+_size);    };
        iterator                cbegin() const  { return iterator(arr);                 };
        iterator                cend() const    { return iterator(arr+_size);           };
    
        reverse_iterator		rbegin() 		{   return reverse_iterator(end());		    };
        const_reverse_iterator	rbegin() const  {	return const_reverse_iterator(end());	};
        reverse_iterator		rend() 			{	return reverse_iterator(begin());		};
        const_reverse_iterator	rend() const 	{	return const_reverse_iterator(begin());	};
//==============================================================================

// ALLOCATOR:-------------------------------------------------------------------
			A get_allocator() const    { return _alloc; }
//==============================================================================
    };
// END CLASS VECTOR ************************************************************


template <class T, class Alloc>
	bool	operator == (const vector<T,Alloc>& l, const vector<T,Alloc>& r)
	{
		if (l.size() != r.size())	return false;
		return ft::equal(l.begin(), l.end(), r.begin());
	};

	template <class T, class Alloc>
	bool	operator != ( const vector<T,Alloc>& l,
						 const vector<T,Alloc>& r )			
    {	return !(l == r);		};

	template <class T, class Alloc>
	bool	operator < ( const vector<T,Alloc>& l,
						 const vector<T,Alloc>& r )			
    {	return ft::lexicographical_compare(l.begin(), l.end(), r.begin(), r.end());		};

	template <class T, class Alloc>
	bool	operator <= ( const vector<T,Alloc>& l,
						 const vector<T,Alloc>& r )			
    {	return !(r < l);		};

	template <class T, class Alloc>
	bool	operator > ( const vector<T,Alloc>& l,
						 const vector<T,Alloc>& r )			
    {	return r < l;			};

	template <class T, class Alloc>
	bool	operator >= ( const vector<T,Alloc>& l,
						 const vector<T,Alloc>& r )			
    {	return !(l < r);		};

	template <class T, class Alloc>
	void	swap(vector<T,Alloc>& x, vector<T,Alloc>& y)	
    {	x.swap(y);				};


} // endnamespace ft

#endif
