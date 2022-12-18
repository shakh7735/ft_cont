#ifndef ITERATOR_TRAITS
# define ITERATOR_TRAITS

# include "equal.hpp"
# include <cstddef>
# include <iterator>
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

	// struct input_iterator_tag {};
	// struct output_iterator_tag {};
	// struct forward_iterator_tag : public input_iterator_tag {};
	// struct bidirectional_iterator_tag : public forward_iterator_tag {};
	// struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	// template<typename _Category, typename _Tp, typename _Distance = ptrdiff_t,
	// 				 typename _Pointer = _Tp*, typename _Reference = _Tp&>
	// 	struct iterator
	// 	{
	// 		typedef _Category	iterator_category;
	// 		typedef _Tp			value_type;
	// 		typedef _Distance	difference_type;
	// 		typedef _Pointer	pointer;
	// 		typedef _Reference	reference;
	// 	};

	// template<typename _Iterator>
	// 	struct iterator_traits
	// 	{
	// 		typedef typename _Iterator::iterator_category	iterator_category;
	// 		typedef typename _Iterator::value_type			value_type;
	// 		typedef typename _Iterator::difference_type		difference_type;
	// 		typedef typename _Iterator::pointer				pointer;
	// 		typedef typename _Iterator::reference			reference;
	// 	};

	// template<typename _Tp>
	// 	struct iterator_traits<_Tp*>
	// 	{
	// 		typedef random_access_iterator_tag	iterator_category;
	// 		typedef _Tp							value_type;
	// 		typedef ptrdiff_t					difference_type;
	// 		typedef _Tp*						pointer;
	// 		typedef _Tp&						reference;
	// 	};

	// template<typename _Tp>
	// 	struct iterator_traits<const _Tp*>
	// 	{
	// 		typedef random_access_iterator_tag	iterator_category;
	// 		typedef _Tp							value_type;
	// 		typedef ptrdiff_t					difference_type;
	// 		typedef const _Tp*					pointer;
	// 		typedef const _Tp&					reference;
	// 	};

	// template<typename _Iter>
	// 	typename ft::iterator_traits<_Iter>::iterator_category
	// 	iterator_category(const _Iter&)
	// 	{
	// 		return (typename ft::iterator_traits<_Iter>::iterator_category());
	// 	}

	// template<typename _Iterator, bool _HasBase>
	// 	struct _Iter_base
	// 	{
	// 		typedef _Iterator iterator_type;
	// 		static iterator_type _S_base(_Iterator it)
	// 		{
	// 			return (it);
	// 		}
	// 	};

	// template<typename _Iterator>
	// 	struct _Iter_base<_Iterator, true>
	// 	{
	// 		typedef typename _Iterator::iterator_type iterator_type;
	// 		static iterator_type _S_base(_Iterator it)
	// 		{
	// 			return (it.base());
	// 		}
	// 	};



	// template<typename _InputIterator>
	// 	typename ft::iterator_traits<_InputIterator>::difference_type
	// 	distance(_InputIterator first, _InputIterator last,
	// 						 input_iterator_tag)
	// 	{
	// 		typename ft::iterator_traits<_InputIterator>::difference_type n = 0;
	// 		while (first != last)
	// 		{
	// 			++first;
	// 			++n;
	// 		}
	// 		return (n);
	// 	}

	// template<typename _RandomAccessIterator>
	// 	typename ft::iterator_traits<_RandomAccessIterator>::difference_type
	// 	distance(_RandomAccessIterator first, _RandomAccessIterator last,
	// 						 random_access_iterator_tag)
	// 	{
	// 		return (last - first);
	// 	}

	// template<typename _InputIterator>
	// 	inline
	// 	typename ft::iterator_traits<_InputIterator>::difference_type
	// 	distance(_InputIterator first, _InputIterator last)
	// 	{
	// 		return (ft::distance(first, last,
	// 				 ft::iterator_category(first)));
	// 	}

	// template<typename _InputIterator, typename _Distance>
	// 	inline void
	// 	advance(_InputIterator& i, _Distance n, input_iterator_tag)
	// 	{
	// 		while (n--)
	// 			++i;
	// 	}

	// template<typename _BidirectionalIterator, typename _Distance>
	// 	inline void
	// 	advance(_BidirectionalIterator& i, _Distance n,
	// 			bidirectional_iterator_tag)
	// 	{
	// 		if (n > 0)
	// 			while (n--)
	// 				++i;
	// 		else
	// 			while (n++)
	// 				--i;
	// 	}

	// template<typename _RandomAccessIterator, typename _Distance>
	// 	inline void
	// 	advance(_RandomAccessIterator& i, _Distance n,
	// 						random_access_iterator_tag)
	// 	{
	// 		i += n;
	// 	}

	// template<typename _InputIterator, typename _Distance>
	// 	inline void
	// 	advance(_InputIterator& i, _Distance n)
	// 	{
	// 		typename ft::iterator_traits<_InputIterator>::difference_type d = n;
	// 		ft::advance(i, d, ft::iterator_category(i));
	// 	}


}

#endif