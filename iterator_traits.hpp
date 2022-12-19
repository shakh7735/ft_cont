#ifndef ITERATOR_TRAITS
# define ITERATOR_TRAITS

# include "equal.hpp"
# include <cstddef>
# include <iterator>
# include <typeinfo>
# include <stdexcept>
// # include "Iterator.hpp"

namespace   ft {

	struct input_iterator_tag { };
	struct output_iterator_tag { };
	struct forward_iterator_tag : public input_iterator_tag { };
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

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
//=========================================================================================================================
	
	// struct output_iterator_tag { };

	// struct input_iterator_tag { };
	
	// struct forward_iterator_tag { };

    // struct bidirectional_iterator_tag : public ft::input_iterator_tag { };

	// struct random_access_iterator_tag { };

    

    

    // template <bool is_valid, typename T>
    //     struct valid_iterator_tag_res { typedef T type; const static bool value = is_valid; };
    
    // template <typename T>
    //     struct is_input_iterator_tagged : public valid_iterator_tag_res<false, T> { };

    // /* Check is_input_iterator_tagged from ft::random_access_iterator_tag */
    // template <>
    //     struct is_input_iterator_tagged<ft::random_access_iterator_tag>
    //         : public valid_iterator_tag_res<true, ft::random_access_iterator_tag> { };

    // /* Check is_input_iterator_tagged from ft::bidirectional_iterator_tag */
    // template <>
    //     struct is_input_iterator_tagged<ft::bidirectional_iterator_tag>
    //         : public valid_iterator_tag_res<true, ft::bidirectional_iterator_tag> { };

    // /* Check is_input_iterator_tagged from ft::forward_iterator_tag */
    // template <>
    //     struct is_input_iterator_tagged<ft::forward_iterator_tag>
    //         : public valid_iterator_tag_res<true, ft::forward_iterator_tag> { };

    // /* Check is_input_iterator_tagged from ft::input_iterator_tag */
    // template <>
    //     struct is_input_iterator_tagged<ft::input_iterator_tag>
    //         : public valid_iterator_tag_res<true, ft::input_iterator_tag> { };

    // template <typename T>
    //     struct is_ft_iterator_tagged : public valid_iterator_tag_res<false, T> { };
    
    // /* Check is_ft_iterator_tagged from ft::random_access_iterator_tag */
    // template <>
    //     struct is_ft_iterator_tagged<ft::random_access_iterator_tag>
    //         : public valid_iterator_tag_res<true, ft::random_access_iterator_tag> { };

    // /* Check is_ft_iterator_tagged from ft::bidirectional_iterator_tag */
    // template <>
    //     struct is_ft_iterator_tagged<ft::bidirectional_iterator_tag>
    //         : public valid_iterator_tag_res<true, ft::bidirectional_iterator_tag> { };

    // /* Check is_ft_iterator_tagged from ft::forward_iterator_tag */
    // template <>
    //     struct is_ft_iterator_tagged<ft::forward_iterator_tag>
    //         : public valid_iterator_tag_res<true, ft::forward_iterator_tag> { };

    // /* Check is_ft_iterator_tagged from ft::input_iterator_tag */
    // template <>
    //     struct is_ft_iterator_tagged<ft::input_iterator_tag>
    //         : public valid_iterator_tag_res<true, ft::input_iterator_tag> { };

    // /* Check is_ft_iterator_tagged from ft::output_iterator_tag */
    // template <>
    //     struct is_ft_iterator_tagged<ft::output_iterator_tag>
    //         : public valid_iterator_tag_res<true, ft::output_iterator_tag> { };

    // template <typename T>
    // class InvalidIteratorException : public std::exception
    // {
    //     private:
    //         std::string _msg;
        
    //     public :
    //         InvalidIteratorException () throw() { _msg = "Is invalid iterator tag : " + std::string(typeid(T).name()); }
    //         InvalidIteratorException (const InvalidIteratorException&) throw() {}
    //         InvalidIteratorException& operator= (const InvalidIteratorException&) throw() {}
    //         virtual ~InvalidIteratorException() throw() {}
    //         virtual const char* what() const throw() { return (_msg.c_str()); }
    // };

    // /*
    // ** @brief Iterator traits class defining properties of
    // ** iterators. In this, iterator_traits obtains information
    // ** from Iterator class in template argument.
    // */
    // template <class Iterator> struct iterator_traits
    // {
    //     /* Result of subtracting one iterator from another, from Iterator. */
    //     typedef typename Iterator::difference_type       difference_type;

    //     /* Type of the element where iterator point, from Iterator. */
    //     typedef typename Iterator::value_type            value_type;

    //     /* Type of a pointer to an element where the iterator point, from Iterator. */
    //     typedef typename Iterator::pointer               pointer;

    //     /* Type of a reference where iterator point, from Iterator. */
    //     typedef typename Iterator::reference             reference;

    //     /* The iterator category from Iterator. */
    //     typedef typename Iterator::iterator_category     iterator_category;
    // };
    
    // /*
    // ** @brief Iterator traits class defining properties of
    // ** iterators. This create a default operation with an
    // ** object (first argument in tempate argument).
    // */
    // template <class T> struct iterator_traits<T*>
    // {
    //     /* Result of subtracting one iterator from another. */
    //     typedef ptrdiff_t                       difference_type;

    //     /* Type of the element where iterator point. */
    //     typedef T                               value_type;

    //     /* Type of a pointer to an element where the iterator point. */
    //     typedef T*                              pointer;

    //     /* Type of a reference where iterator point. */
    //     typedef T&                              reference;

    //     /* The iterator category from Iterator. */
    //     typedef ft::random_access_iterator_tag  iterator_category;
    // };
    
    // /*
    // ** @brief Iterator traits class defining properties of
    // ** iterators. This create a default operation with a
    // ** const object (first argument in tempate argument).
    // */
    // template <class T> class iterator_traits<const T*>
    // {
    //     /* Result of subtracting one iterator from another. */
    //     typedef ptrdiff_t                       difference_type;

    //     /* Type of the element where iterator point. */
    //     typedef T                               value_type;

    //     /* Type of a pointer to an element where the iterator point. */
    //     typedef const T*                        pointer;

    //     /* Type of a reference where iterator point. */
    //     typedef const T&                        reference;

    //     /* The iterator category from Iterator. */
    //     typedef ft::random_access_iterator_tag  iterator_category;
    // };

    // /*
    // ** @brief Give a difference_type defined in ft::iterator_traits
    // ** that's the difference of address in memory
    // ** between last and first iterator.
    // **
    // ** @param first The first iterator.
    // ** @param last The last iterator.
    // ** @return The difference.
    // */
    // template<class InputIterator>
    //     typename ft::iterator_traits<InputIterator>::difference_type
    //         distance (InputIterator first, InputIterator last)
    //     {
    //         typename ft::iterator_traits<InputIterator>::difference_type rtn = 0;
    //         while (first != last)
    //         {
    //             first++;
    //             rtn++;
    //         }
    //         return (rtn);
    //     }

    // /*
    // ** @brief Base class for iterator, not really usefull, but type
    // ** defined can be use for iterator_traits. An iterator permeted to
    // ** take any element range in an object and using a set of operators.
    // */
    // template <class Category, class T, class Distance = ptrdiff_t,
    //     class Pointer = T*, class Reference = T&>
    //     class iterator
    //     {
    //         public:
    //             /* Type of elements pointed. */
    //             typedef T           value_type;

    //             /* Type to represent the difference between two iterators. */
    //             typedef Distance    difference_type;

    //             /* Type to represent a pointer to an element pointed */
    //             typedef Pointer     pointer;

    //             /* Type to represent a reference to an element pointed */
    //             typedef Reference   reference;

    //             /* Category of the iterator. */
    //             typedef Category    iterator_category;
    //     };

	//  template <class T>
    //     class bidirectional_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
    //     {  
    //         /* Category of the iterator. */
    //         typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category     iterator_category;
            
    //         /* Type of elements pointed. */
    //         typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::value_type            value_type;
            
    //         /* Type to represent the difference between two iterators. */
    //         typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type       difference_type;
            
    //         /* Type to represent a pointer to an element pointed */
    //         typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::pointer               pointer;
            
    //         /* Type to represent a reference to an element pointed */
    //         typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::reference             reference;
            
    //         private:
    //             /* Element pointed by the iterator. */
    //             pointer _elem;
    //     };

}

#endif