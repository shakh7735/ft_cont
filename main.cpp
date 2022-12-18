#include <iostream>
# include <sstream>
#include <vector>
#include <map>
#include "map.hpp"
#include "vector.hpp"

#define NS ft

    const std::string	vec_example12()
	{
        double _time;
		
                std::ostringstream      ss;

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



template <typename T>
std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
	o << "key: " << iterator->first << " | value: " << iterator->second;
	if (nl)
		o << std::endl;
	return ("");
}


template <typename T_MAP>
void	printSize(T_MAP const &mp, bool print_content = 1)
{
	std::cout << "size: " << mp.size() << std::endl;
	std::cout << "max_size: " << mp.max_size() << std::endl;
	if (print_content)
	{
		typename T_MAP::const_iterator it = mp.begin(), ite = mp.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << printPair(it, false) << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

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

int main()
{
        double _time;
    std::cout << map_example12(_time);
    return (0);
}
