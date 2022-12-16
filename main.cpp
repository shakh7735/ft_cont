#include <iostream>
#include "map.hpp"
#include "vector.hpp"

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

// int main ()
// {
// 	ft::map<char,int> mymap;
//   ft::map<char,int>::iterator it;

//   // insert some values:
//   mymap['a']=10;
//   mymap['b']=20;
//   mymap['c']=30;
//   mymap['d']=40;
//   mymap['e']=50;
//   mymap['f']=60;
 
// it = mymap.end();

// // ++it;

// char first = mymap.getNil()->parent->data.first;
// int second = mymap.getNil()->parent->data.second;
// std::cout << "nil parent: " << first << " => " << second << '\n';
// --it;
// std::cout << "- " << printPair(it, false) << std::endl;
// // for (it=mymap.begin(); it!=mymap.end(); ++it)
// //     std::cout << it->first << " => " << it->second << ": color->" << (it.base()->color ? "RED" : "BLACK") << '\n';
//   // it=mymap.find('b');
//   // mymap.erase (it);                   // erasing by iterator
// //  std::cout << "=== root ===> " << mymap.getRoot()->key() << std::endl;
// //   mymap.erase ('b');                  // erasing by key
// // std::cout << "erase() =root=> " << mymap.getRoot()->key() << std::endl;	
//   // it=mymap.find ('e');
//   // mymap.erase ( it, mymap.end() );    // erasing by range
// //   printSize(mymap);
// }



int main()
{
    // std::vector<int> a1{1, 2, 3}, a2{4, 5};
    ft::vector<int> a1(1, 3);
    // int myarray [] = { 501,502,503 };
    
    std::cout << "a1.size = " << a1.size() << '\n';
    std::cout << "a1.capacity = " << a1.capacity() << '\n';
	a1.clear();
	std::cout << "a1.size = " << a1.size() << '\n';
	std::cout << "a1.capacity = " << a1.capacity() << '\n';
    // ft::vector<int> a2(a1);
    // std::cout << "a1 = " << a1 << std::endl;

    // a2.at(0) = 5;
    // a2.at(1) = 10;
    // a2.at(2) = 11;
    // std::cout << "a2 = " << a2 << std::endl;
    // a2.insert(a2.begin(), a1.begin(), a1.end()-2);
    // std::cout << "insert a2(a1) = " << a2 << std::endl;
    // a2.insert(a2.begin() + 1, 2, 16);
    // std::cout << "insert a2(a1) = " << a2 << std::endl;
    // a2.insert(a2.begin(), 100);
    // std::cout << "insert a2 = " << a2 << std::endl;
    // ft::vector<int>::iterator it2 = a2.erase(a2.begin() + 1, a2.begin()+4);
    // std::cout << "erase a2 = " << a2 << "   iterator return " << *it2 << std::endl;
    // std::cout << "a2.size = " << a2.size() << '\n';
    // std::cout << "a2 max size = " << a2.max_size() << std::endl;
    // // a1.reserve(8);
    // // a1.push_back(4);
    // std::cout << "a1.size = " << a1.size() << '\n';
    // // a1.push_back(5);
    // // a1.push_back(6);
    // // std::cout << "a1.size = " << a1.size() << '\n';
    // std::cout << "a1.reserve = " << a1.capacity() << '\n';
    // std::cout << "a1.empty =  " << (a1.empty() ? "is empty" : "don't empty") << '\n';
    // std::cout << "a1 elem  =  " << a1 << '\n';
    // a1.pop_back();
    // a1[2] = 5;
    // std::cout << "a1 elem  =  " << a1 << '\n';
    // std::cout << "a1.size = " << a1.size() << '\n';
    // ft::vector<int>::iterator it = a1.begin();
    // std::cout << "iter = " << *it << '\n';
    // ++it;// = a1.end();
    // std::cout << "iter = " << *(it++) << '\n';
    // std::cout << "iter = " << *(it) << '\n';
    // auto it1 = std::next(a1.begin());
    // auto it2 = std::next(a2.begin());
 
    // int& ref1 = a1.front();
    // int& ref2 = a2.front();
 
    // std::cout << a1 << a2 << *it1 << ' ' << *it2 << ' ' << ref1 << ' ' << ref2 << '\n';
    // a1.swap(a2);
    // std::cout << a1 << a2 << *it1 << ' ' << *it2 << ' ' << ref1 << ' ' << ref2 << '\n';
 
    // Note that after swap the iterators and references stay associated with their
    // original elements, e.g. it1 that pointed to an element in 'a1' with value 2
    // still points to the same element, though this element was moved into 'a2'.
    // {
    //     std::cout << "-------EMPLACE----------------\n";
    //     ft::vector<int> myvector {10,20,30};
        
    //     auto it = myvector.emplace ( myvector.begin()+1, 100 );
    //     myvector.emplace ( it, 200 );
    //     myvector.emplace ( myvector.end(), 300 );
        
    //     std::cout << "myvector contains:";
    //     for (auto& x: myvector)
    //     std::cout << ' ' << x;
    //     std::cout << '\n';
    // }
}