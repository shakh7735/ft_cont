#ifndef PAIR_HPP
# define PAIR_HPP

namespace   ft {

    template <class Arg1, class Arg2, class Result>
    struct binary_function
    {
        typedef Arg1 first_argument_type;
        typedef Arg2 second_argument_type;
        typedef Result result_type;
    };

    template <class T>
    struct less : binary_function<T, T, bool>
    {
        bool operator() (const T& x, const T& y) const { return (x < y); }
    };
    
    template< class T1, class T2> 
    class pair{
        public:
            typedef T1 first_type;
            typedef T2  second_type;
            
            first_type first;
            second_type second;
    
        pair() : first(), second() {};

        template<class U, class V>
        pair (const pair<U, V>& pr) : 
            first(pr.first), second(pr.second) {};

        pair (const first_type& a, const second_type& b) : 
            first(a), second(b) {};

        pair &operator= (const pair& pr)
        {
            if ( *this != pr )	
            {	this->first = pr.first; this->second = pr.second;	}
			return *this;
        }
    };

    template< class T1, class T2 >
    pair<T1, T2> make_pair( T1 t, T2 u ) { return  ft::pair<T1, T2>(t, u); };

    template< class T1, class T2 >
    bool operator==( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
    {   return (lhs.first == rhs.first && lhs.second == rhs.second);    }
    
    
    template< class T1, class T2 >
    bool operator!=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
    {   return !(lhs == rhs);   }
    
    template< class T1, class T2 >
    bool operator<( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
    {   return (lhs.first < rhs.first || (lhs.first == rhs.first && lhs.second < rhs.second));  }
   
   
    template< class T1, class T2 >
    bool operator<=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
    {   return !(rhs < lhs); };

    template< class T1, class T2 >
    bool operator>( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
    {   return (rhs < lhs); };
   
    
    template< class T1, class T2 >
    bool operator>=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
    {   return !(lhs < rhs); };

    // template <class T>
	// void swap (T & a, T & b)
	// {   T tmp(a); a = b; b = tmp;   };
    
} // endnamespace ft
#endif