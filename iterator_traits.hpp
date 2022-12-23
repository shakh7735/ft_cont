#ifndef ITERATOR_TRAITS
# define ITERATOR_TRAITS

# include "equal.hpp"
# include <cstddef>
// # include <iterator>
# include <typeinfo>
# include <stdexcept>
// # include "Iterator.hpp"

namespace   ft {

	// struct input_iterator_tag { };
	// struct output_iterator_tag { };
	// struct forward_iterator_tag { };
	// struct bidirectional_iterator_tag {};
	// struct random_access_iterator_tag {};

    class random_access_iterator_tag { };
    class bidirectional_iterator_tag { };
    class forward_iterator_tag { };
    class input_iterator_tag { };
    class output_iterator_tag { };

///////////////////////////////////////////////////////////////////////////////////
    template <bool is_valid, typename T>
        struct valid_iterator_tag_res { typedef T type; const static bool value = is_valid; };
    template <typename T>
        struct is_input_iterator_tagged : public valid_iterator_tag_res<false, T> { };
    template <>
        struct is_input_iterator_tagged<ft::random_access_iterator_tag>
            : public valid_iterator_tag_res<true, ft::random_access_iterator_tag> { };
    template <>
        struct is_input_iterator_tagged<ft::bidirectional_iterator_tag>
            : public valid_iterator_tag_res<true, ft::bidirectional_iterator_tag> { };
    template <>
        struct is_input_iterator_tagged<ft::forward_iterator_tag>
            : public valid_iterator_tag_res<true, ft::forward_iterator_tag> { };
    template <>
        struct is_input_iterator_tagged<ft::input_iterator_tag>
            : public valid_iterator_tag_res<true, ft::input_iterator_tag> { };

    template <typename T>
        struct is_ft_iterator_tagged : public valid_iterator_tag_res<false, T> { };
    
    template <>
        struct is_ft_iterator_tagged<ft::random_access_iterator_tag>
            : public valid_iterator_tag_res<true, ft::random_access_iterator_tag> { };

    template <>
        struct is_ft_iterator_tagged<ft::bidirectional_iterator_tag>
            : public valid_iterator_tag_res<true, ft::bidirectional_iterator_tag> { };

    template <>
        struct is_ft_iterator_tagged<ft::forward_iterator_tag>
            : public valid_iterator_tag_res<true, ft::forward_iterator_tag> { };

    template <>
        struct is_ft_iterator_tagged<ft::input_iterator_tag>
            : public valid_iterator_tag_res<true, ft::input_iterator_tag> { };

    template <>
        struct is_ft_iterator_tagged<ft::output_iterator_tag>
            : public valid_iterator_tag_res<true, ft::output_iterator_tag> { };
// /////////////////////////////////////////////////////////////////////////////////


	// [ ITERATOR TRAITS ]
	template <class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};

	template < class T >
	struct iterator_traits< T* >
	{
		typedef ptrdiff_t								difference_type;
		typedef T										value_type;
		typedef T*										pointer;
		typedef T&										reference;
		typedef random_access_iterator_tag			iterator_category;
	};

	template <class T>
	struct iterator_traits<const T*>
	{
		typedef ptrdiff_t								difference_type;
		typedef T										value_type;
		typedef const T*								pointer;
		typedef const T&								reference;
		typedef random_access_iterator_tag			iterator_category;
	};


	template<typename InputIterator>
	typename ft::iterator_traits<InputIterator>::difference_type distance(InputIterator first, InputIterator last,
		typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
	{
		typename ft::iterator_traits<InputIterator>::difference_type n = 0;

		while (first != last)		{	++n; ++first;	};
		return n;
	}

     template <class Category, class T, class Distance = ptrdiff_t,  class Pointer = T*, class Reference = T&>
        class iteratorT
        {
            public:
                typedef T           value_type;
                typedef Distance    difference_type;
                typedef Pointer     pointer;
                typedef Reference   reference;
                typedef Category    iterator_category;
        };

    template <class T>
        class bidirectional_iterator : ft::iteratorT<ft::bidirectional_iterator_tag, T>
        {  
            typedef typename ft::iteratorT<ft::bidirectional_iterator_tag, T>::iterator_category     iterator_category;
            typedef typename ft::iteratorT<ft::bidirectional_iterator_tag, T>::value_type            value_type;
            typedef typename ft::iteratorT<ft::bidirectional_iterator_tag, T>::difference_type       difference_type;
            typedef typename ft::iteratorT<ft::bidirectional_iterator_tag, T>::pointer               pointer;
            typedef typename ft::iteratorT<ft::bidirectional_iterator_tag, T>::reference             reference;
            
            private:
                pointer _elem;
        };

    template <typename T>
    class InvalidIteratorException : public std::exception
    {
        private:
            std::string _msg;
        
        public :
            InvalidIteratorException () throw() { _msg = "Is invalid iterator tag : " + std::string(typeid(T).name()); }
            InvalidIteratorException (const InvalidIteratorException&) throw() {}
            InvalidIteratorException& operator= (const InvalidIteratorException&) throw() {}
            virtual ~InvalidIteratorException() throw() {}
            virtual const char* what() const throw() { return (_msg.c_str()); }
    };

}

#endif