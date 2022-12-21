#include <iostream>
# include <sstream>
#include <vector>
#include <map>
#include "map.hpp"
#include "vector.hpp"

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
// 		for (; it != ite; ++it)
// 			std::cout << "- " << printPair(it, false) << std::endl;
// 	}
// 	std::cout << "###############################################" << std::endl;
// }

const std::string       map_example12(double &_time)
        {
                std::ostringstream      ss;

                NS::map<char, int>      A;
                A.insert(NS::make_pair('d', 0));
                A.insert(NS::make_pair('b', -2));
                A.insert(NS::make_pair('f', 2));
                A.insert(NS::make_pair('c', -1));
                A.insert(NS::make_pair('e', 1));
                A.insert(NS::make_pair('a', -3));
                A.insert(NS::make_pair('j', 3));
                ss << " " << A.find('e')->first;
                NS::map<char, int>::const_iterator      it1 = A.find('a');
                NS::map<char, int>::const_iterator      it2 = A.find('o');
                while (it1 != it2)
                        ss << " " << (it1++)->first;
                _time = 0;
                return (ss.str());
        }
const std::string	map_example11(double &_time)
	{
		std::ostringstream	ss;

		NS::map<char, int>			A;
		NS::pair<const char, int>	*p;
		(void)p;

		p = A.get_allocator().allocate(42);
		A.get_allocator().deallocate(p, 42);
		ss << "Allocator OK";
		_time = 0;
		return (ss.str());
	}

const std::string	map_example22(double &_time)
	{
		std::ostringstream	ss;

		std::vector<int> v;
		NS::map<int, int, std::greater<int> > mp2;
		mp2.insert(NS::make_pair(20, 20));
		mp2.insert(NS::make_pair(30, 30));
		mp2.insert(NS::make_pair(40, 40));
		mp2.insert(NS::make_pair(50, 50));
		mp2.insert(NS::make_pair(60, 60));
		NS::map<int, int>::iterator it;
		for (int i = 11; i < 70; i += 10) {
			it = mp2.upper_bound(i);
			if (i == 11)
				v.push_back((it == mp2.end()));
			else
				v.push_back(it->first);
		}
		it = mp2.begin();

        std::advance(it, 21);
		
		for (std::vector<int>::iterator it1 = v.begin(); it1 != v.end(); ++it1)
			ss << " " << *it1;
		_time = 0;
		return (ss.str());
	}

	const std::string	map_example50(double &_time)
	{
		std::ostringstream	ss;
		clock_t				start;
		clock_t				end;
		NS::map<int, int>	mp;

		for (int i = 0, j = 0; i < 1000000; ++i, ++j)
			mp.insert(NS::make_pair(i, j));

		start = clock();
		ss << " " << mp.size();
		end = clock();
		_time = (double)(end - start);

		for (int i = 0; i < 430000; ++i)
			mp.erase(i);
		ss << " " << mp.size();

		return (ss.str());
	}

int main()
{
        double _time;
    std::cout << map_example11(_time) << std::endl;
    return (0);
}
