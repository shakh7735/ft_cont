#include <iostream>
# include <sstream>
// #include <vector>
#include <map>
#include "map.hpp"
#include "vector.hpp"

// #define NS ft
#define NS ft


// template <typename T>
// std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
// {
// 	o << "key: " << iterator->first << " | value: " << iterator->second;
// 	if (nl)
// 		o << std::endl;
// 	return ("");
// }


// template <typename T_MAP>
// void	printSize(T_MAP const &mp, bool print_content = 1)
// {
// 	std::cout << "size: " << mp.size() << std::endl;
// 	std::cout << "max_size: " << mp.max_size() << std::endl;
// 	if (print_content)
// 	{
// 		typename T_MAP::const_iterator it = mp.begin(), ite = mp.end();
// 		std::cout << std::endl << "Content is:" << std::endl;
// 		for (; it != ite; ++iyt)
// 			std::cout << "- " << printPair(it, false) << std::endl;
// 	}
// 	std::cout << "###############################################" << std::endl;
// }

const std::string	vec_example13(double &_time)
	{
		std::ostringstream	ss;
	
		NS::vector<int> vec(5, int(58));
		ss << " " << vec.capacity();
		ss << " " << vec.size();
		NS::vector<int>::iterator it = vec.begin() + 2;
		vec.insert(it, 1);
		it = vec.insert(vec.begin(), 1);
		vec.insert(vec.end(), 1);
		for (size_t i = 0; i < vec.size(); ++i)
			ss << ' ' << vec[i];
		ss << " " << vec.capacity();
		ss << " " << vec.size();
		ss << " " << *it;
		vec.reserve(30);
		it = vec.begin() + 2;
		for (size_t i = 0; i < vec.size(); ++i)
			ss << ' ' << vec[i];
		ss << " " << vec.capacity();
		ss << " " << vec.size();
		NS::vector<int> vec5;
		vec5.insert(vec5.begin(), 9);
		vec5.insert(vec5.end() - 1, 3, 10);
		for (size_t i = 0; i < vec5.size(); ++i)
			ss << ' ' << vec5[i];
		ss << " " << vec5.capacity();
		ss << " " << vec5.size();
		_time = 0;
		return (ss.str());
	}

const std::string	vec_example12(double &_time)
	{
		std::ostringstream	ss;

		NS::vector<int> vec(5, int(58));
		ss << " " << vec.capacity();
		ss << " " << vec.size();
		NS::vector<int>::iterator it = vec.begin() + 2;
		vec.insert(it, 3, 50);
		ss << " " << vec.capacity();
		ss << " " << vec.size();
		vec.insert(vec.begin(), 1, 1);
		vec.insert(vec.begin(), 0, 2);
		vec.insert(vec.end(), 3, 2);
		ss << " Content:" ;
		for (size_t i = 0; i < vec.size(); ++i)
			ss << ' ' << vec[i];
		ss << " :" ;
		ss << " " << vec.capacity();
		ss << " " << vec.size();
		vec.reserve(30);
		it = vec.begin() + 2;
		vec.insert(it, 3, -50);
		vec.insert(vec.begin(), 0, -2);
		vec.insert(vec.end(), 3, -2);
		vec.insert(vec.begin(), 1, -1);
		ss << " Content:" ;
		for (size_t i = 0; i < vec.size(); ++i)
			ss << ' ' << vec[i];
		ss << " :" ;
		ss << " " << vec.capacity();
		ss << " " << vec.size();
		_time = 0;
		return (ss.str());
	}

const std::string	vec_example16(double &_time)
	{
		std::ostringstream	ss;
	
		NS::vector<int> vec(5, int(42));
		ss << " Cap=" << vec.capacity() << " Siz=" << vec.size() << std::endl;
		vec.resize(7);
		ss << " Cap=" << vec.capacity() << " Siz=" << vec.size() << std::endl;
		vec.insert(vec.begin(), 5, 1);
		ss << " Cap=" << vec.capacity() << " Siz=" << vec.size() << std::endl;
		vec.insert(vec.begin(), 12, 1);
		ss << " Cap=" << vec.capacity() << " Siz=" << vec.size() << std::endl;
		// for (size_t i = 0; i < vec.size(); ++i)
		// 	ss << ' ' << vec[i];
		// vec.resize(7);
		// ss << " " << vec.capacity();
		// ss << " " << vec.size();
		// for (size_t i = 0; i < vec.size(); ++i)
		// 	ss << ' ' << vec[i];
		// vec.resize(11, 21);
		// vec.resize(11);
		// ss << " " << vec.capacity();
		// ss << " " << vec.size();
		// for (size_t i = 0; i < vec.size(); ++i)
		// 	ss << ' ' << vec[i];
		// vec.resize(6);
		// ss << " " << vec.capacity();
		// ss << " " << vec.size();
		// for (size_t i = 0; i < vec.size(); ++i)
		// 	ss << ' ' << vec[i];
		_time = 0;
		return (ss.str());
	}

const std::string	vec_example34(double &_time)
	{
		std::ostringstream	ss;
		clock_t				start;
		clock_t				end;
		NS::vector<int>		_vector;

		_vector.assign(50000000, 1);

		start = clock();
		_vector.clear();
		end = clock();
		_time = (double)(end - start);

		ss << " " << (_vector.capacity());
		ss << " " << (_vector.size());

		return (ss.str());
	}

	const std::string	vec_example40(double &_time)
	{
		std::ostringstream	ss;
		clock_t				start;
		clock_t				end;
		NS::vector<int>		_vector;

		for (int i = 0; i < 99000000; ++i)
			_vector.push_back(i);

		start = clock();
    	ss << " " << (*(_vector.erase(_vector.begin() + 80000, _vector.end() - 15000000)));
		end = clock();
		_time = (double)(end - start);

		ss << " " << (*(_vector.begin() + 820000));
		ss << " " << (_vector.size());
		ss << " " << (_vector.capacity());

		return (ss.str());
	}

	const std::string	vec_example75(double &_time)
	{
		std::ostringstream	ss;
		const int			size = 5;

		NS::vector<int> vct(size);
		NS::vector<int>::reverse_iterator it = vct.rbegin();
		NS::vector<int>::const_reverse_iterator ite = vct.rbegin();

		for (int i = 0; i < size; ++i)
			it[i] = (size - i) * 5;

		it = it + 5;
		it = 1 + it;
		it = it - 4;
		ss << " " << *(it += 2);
		ss << " " << *(it -= 1);

		*(it -= 2) = 42;
		*(it += 2) = 21;

		ss << " " << *(ite += 2) << " " << *(ite -= 2);

		ss << " " << (ite == it);
		ss << " " << (ite - it);
		ss << " " << (ite + 3 == it);

		ss << " " << vct.size();
		ss << " " << vct.capacity();
		NS::vector<int>::const_iterator it5 = vct.begin();
		NS::vector<int>::const_iterator ite5 = vct.end();
		for (; it5 != ite5; ++it5)
			ss << " " << *it5;

		_time = 0;
		return (ss.str());
	}

int main()
{
        double _time;
    std::cout << vec_example75(_time) << std::endl;
	std::cout << "time : " << _time/1000 << std::endl;
    return (0);
}
