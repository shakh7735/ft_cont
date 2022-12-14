#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "Iterator.hpp"
# include "equal.hpp"

# include <memory>
# include <algorithm>
# include <stdexcept>

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
           
            
            size_type increasingCapacity(size_type size){ return (size * 3 / 2 + 1); }
           
            void deallocateArray()
            {
                // if (_capacity == 0)
                //     return ;
                for(T* it = arr; it != arr + _size; ++it)
                        _alloc.destroy(it);
                _alloc.deallocate(arr, _capacity);
                _size = 0;
                _capacity = 0;
            }
            
            // template <class InputIterator>
            // bool equalIteratorVal(InputIterator it) { return typeid(T) == typeid(*it); }

        public:
// CONSTRUCTORS-------------------------------------------------------------------
            
            explicit	vector( const allocator_type& alloc = allocator_type() )	:	
                        _alloc(alloc), _capacity(0), arr(NULL),	_size(0) {};

			explicit	vector( size_type n, const value_type& val = value_type(),
							const allocator_type& alloc = allocator_type() )    :
                    	_alloc(alloc), _capacity(0), arr(NULL), _size(0)		
            {	
                arr = _alloc.allocate(n);
                for (size_type k = 0; k < n; k++) {
                _alloc.construct(&arr[k], val);
                }
                _size = n;
                _capacity = n;
            };

			template <class InputIterator>
			vector( InputIterator first, InputIterator last, 
                const allocator_type& alloc = allocator_type())	:  
                _alloc(alloc), _capacity(0), arr(NULL), _size(0) 	
            {	insert(begin(), first, last);	};

			vector( const vector& x )	:	
                _alloc(x._alloc), _capacity(x._capacity), 
                arr(_alloc.allocate(x._capacity)), _size(x._size)								
            {		assign(x.begin(), x.end());		};

			vector&					operator = (const vector& x)
			{
				if (this != &x) assign(x.begin(), x.end());
				return *this;
			}
// DESTRUCTOR-------------------------------------------------------------------
            ~vector()   { clear(); _alloc.deallocate(arr, _capacity); } //   std::cout << "Delete vector.\n"; }

// Element access:--------------------------------------------------------------
        T &operator[](size_type index){
            if (index > _size)
                throw std::out_of_range("out out_of_range");
            return (*(arr + index));
        }

        const T &operator[] (size_type index) const {
            if (index > _size)
                throw std::out_of_range("out out_of_range");
            return (*(arr + index));
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
        
        void resize (size_type n)
        {
            reserve(n);
            while (n < _size)	
                pop_back();
            _size = n;

        }
        
        void resize (size_type n, T val)
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
                size_type last_cap = _capacity;
                _capacity = new_cap;
                T* tmp = arr;
                
                arr = _alloc.allocate(_capacity);
                for (size_type i = 0; i < _size; ++i)
                    _alloc.construct( arr + i , *(tmp + i));
                for(T* it = tmp; it != tmp + _size; ++it)
                        _alloc.destroy(it);
                if (last_cap > 0)
                    _alloc.deallocate(tmp, last_cap);
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
        
        void assign (size_type n, const T& val)
        {
            clear();
            reserve(n);
            while (n > _size)	
	    	    push_back(val);
        }
        
        void push_back(value_type elem) {
            if (_size == _capacity)
                reserve(increasingCapacity(_size));
            _alloc.construct(arr + _size++, elem);
        }
        
        void pop_back(void) {
            _alloc.destroy(&(arr [ --_size]));
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
            size_type dist = n;
            size_type new_size = _size + dist;
            
            if (new_size > _capacity)
                new_cap = new_size;
            reserve(new_cap);
            
            size_type i = 0;
            while ( i++ < _size)
            {
                if (pos++ == position)
                    break;
            }
            i--;
            size_type j = new_size - 1;
            while ( j >= dist + i)
            {
                _alloc.construct(&arr[j--], (arr [--_size]));
                _alloc.destroy(&arr[_size]);
                
            }
            for (size_type k = 0; k < dist; k++) {
                _alloc.destroy(&arr[i]);
                _alloc.construct(&arr[i++], val);
            }
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
            reserve(new_cap);
            
            size_type i = 0;
            while ( i++ < _size)
            {
                if (pos++ == position)
                    break;
            }
            i--;
            size_type j = new_size - 1;
            while ( j >= dist + i)
            {
                _alloc.construct(&arr[j--], (arr [--_size]));
                _alloc.destroy(&arr[_size]);
                
            }
            for (InputIterator it = first; it != last; it++) {
                arr[i++] = *it;
            }
            _size = new_size;
        }

        iterator erase (iterator position) { return erase(position, position + 1); }
        
        iterator erase (iterator first, iterator last)
        {
            int ind_first = -1;
            int ind_last = -1;
            size_type dist = ft::distance(first, last);
            iterator it = begin();
            
            for (size_type i = 0; i < _size; i++) {
                if (it == first)
                    ind_first = (int)i;
                if ( it == last)
                    ind_last = (int)i;
                if ( ind_first != -1 && i + dist < _size ) 
                    *it = it[dist];
                if ( ind_first != -1 && ind_last != -1)
                    _alloc.destroy(&(*it));

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
        
        void clear() {
            if (empty())
                return;
            for(value_type* it = arr; it != arr + _size; ++it)
                        _alloc.destroy(it);
                _size = 0;
        }

        
        
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
