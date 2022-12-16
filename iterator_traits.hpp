#ifndef ITERATOR_TRAITS
# define ITERATOR_TRAITS

# include "equal.hpp"
# include "Iterator.hpp"
// # include "IteratorMap.hpp"

namespace   ft {


    // struct input_iterator_tag { };
	// struct output_iterator_tag { };
	// struct forward_iterator_tag : public input_iterator_tag { };
	// struct iterator_stract{};
	struct bidirectional_iterator_tag { } ;
	// typedef iterator_stract random_access_iterator_tag;

	// [ ITERATOR TRAITS ]
	// template <class iterator>
	// struct iterator_traits
	// {
	// 	typedef typename iterator::difference_type		difference_type;
	// 	typedef typename iterator::value_type			value_type;
	// 	typedef typename iterator::pointer				pointer;
	// 	typedef typename iterator::reference			reference;
	// 	typedef typename iterator::iterator_category	iterator_category;
	// };

	// template<typename InputIterator>
	// typename ft::iterator_traits<InputIterator>::difference_type distance(InputIterator first, InputIterator last,
	// 	typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
	// {
	// 	typename ft::iterator_traits<InputIterator>::difference_type n = 0;

	// 	while (first != last)		{	++n; ++first;	};
	// 	return n;
	// }

}

#endif