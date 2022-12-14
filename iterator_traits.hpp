#ifndef ITERATOR_TRAITS
# define ITERATOR_TRAITS

namespace   ft {


    struct bidirectional_iterator_tag {};

    struct random_access_iterator_tag {};

	// [ ITERATOR TRAITS ]
	template <class iterator>
	struct iterator_traits
	{
		typedef typename iterator::difference_type		difference_type;
		typedef typename iterator::value_type			value_type;
		typedef typename iterator::pointer				pointer;
		typedef typename iterator::reference			reference;
		typedef typename iterator::iterator_category	iterator_category;
	};

	

}

#endif