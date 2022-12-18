#include <iostream>
# include <sstream>
#include <vector>
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


int main()
{
    std::cout << vec_example12();
    return (0);
}
