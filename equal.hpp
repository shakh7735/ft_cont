#ifndef EQUAL_HPP
# define EQUAL_HPP

namespace ft
{
	template <bool Cond, class T = void>
	struct enable_if 					{	};

	template <class T>
	struct enable_if<true, T>			{		typedef T type;		};

	template <class T, T v>
	struct integral_constant
	{
		static const T					value = v;
		T								value_type;
		typedef integral_constant<T, v>	type;
	};

	struct bidirectional_iterator_tag {};

    struct random_access_iterator_tag {};

	
	typedef integral_constant<bool, true>	true_type;
	typedef integral_constant<bool, false>	false_type;

	template <class T>
		struct is_integral				:	public false_type		{};

	template <class T> struct
		is_integral<const T>			:	public is_integral<T>	{};
	template <class T> struct
		is_integral<volatile const T>	:	public is_integral<T>	{};
	template <class T> struct
		is_integral<volatile T>			:	public is_integral<T>	{};
	template <> struct
		is_integral<unsigned char>		:	public true_type		{};
	template <> struct
		is_integral<unsigned short>		:	public true_type		{};
	template <> struct
		is_integral<unsigned int>		:	public true_type		{};
	template <> struct
		is_integral<unsigned long>		:	public true_type		{};
	template <> struct
		is_integral<unsigned long long> :	public true_type		{};
	template <> struct
		is_integral<signed char>		:	public true_type		{};
	template <> struct
		is_integral<short>				:	public true_type		{};
	template <> struct
		is_integral<int>				:	public true_type		{};
	template <> struct
		is_integral<long>				:	public true_type		{};
	template <> struct
		is_integral<long long>			:	public true_type		{};
	template <> struct
		is_integral<char>				:	public true_type		{};
	template <> struct
		is_integral<bool>				:	public true_type		{};

	template <bool B, class T = void, class U = void>
	struct conditional {};

	template <class T, class U>
	struct conditional<true, T, U> { typedef T type; };

	template <class T, class U>
	struct conditional<false, T, U> { typedef U type; };

	template<typename T>
	void	swap(T &first, T& second)
	{
		T	tmp = first;
		first = second;
		second = tmp;
	};


	template<class InputIt1, class InputIt2>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
	{
		for (; first1 != last1 ; ++first1, ++first2) {
			if (!(*first1 == *first2)) {
				return false;
			}
		}
		return (true);
	};

	template<class InputIt1, class InputIt2>
	bool equal(InputIt1 first1, InputIt1 last1, 
			InputIt2 first2, InputIt2 last2)
	{
		for (; first1 != last1 ; ++first1, ++first2) {
			if (first2 == last2 || *first1 != *first2  )
				return false;
		}
		return first2 == last2;
	};
	
	template<class InputIt1, class InputIt2>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
								InputIt2 first2, InputIt2 last2)
	{
		for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
			if (*first1 < *first2) return true;
			if (*first2 < *first1) return false;
		}
		return (first1 == last1) && (first2 != last2);
	};

	template<class InputIt1, class InputIt2, class Compare>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
								InputIt2 first2, InputIt2 last2,
								Compare comp)
	{
		for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
			if (comp(*first1, *first2)) return true;
			if (comp(*first2, *first1)) return false;
		}
		return (first1 == last1) && (first2 != last2);
	};
};

#endif