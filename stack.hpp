#ifndef STACK_HPP
# define STACK_HPP

#include "vector.hpp"

namespace   ft {

    template <class T, class Container = ft::vector<T> >
    class stack{
        public:
            typedef T							value_type;
			typedef Container					container_type;
			typedef size_t						size_type;
            typedef value_type*					pointer;
			typedef const value_type*			const_pointer;
			typedef value_type&					reference;
			typedef const value_type&			const_reference;
        
        protected:
            container_type                      content;
        
        public:
// [ MEMBER FUNCTIONS ]
            explicit stack (const container_type& ctnr = container_type()) : content(ctnr) {};
            stack(stack const &other) { *this = other; }
	        virtual ~stack() {}

            stack &operator=(stack const &other) { 
                if (this != &other)
                    this->content = other.content; 
                return (*this); 
            }

            bool empty() const {    return content.empty();    };
            size_type size() const {    return content.size();  };
            value_type& top() { return content.back();  };
            const value_type& top() const { return content.back();  };
            void push (const value_type& val)   {   content.push_back(val);  };
            void pop() {   content.pop_back();   };
            void swap (stack& x)  { content.swap(x.content); };
    
//  Relational operators for stack            
            friend bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
            {   return lhs.content == rhs.content;  };

            friend bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
            {   return lhs.content != rhs.content;  };

            friend bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
            {   return lhs.content < rhs.content;  };

            friend bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
            {   return lhs.content <= rhs.content;  };

            friend bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
            {   return lhs.content > rhs.content;  };

            friend bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
            {   return lhs.content >= rhs.content;  };

            friend  void swap (stack<T,Container>& x, stack<T,Container>& y)
            {   x.swap(y); }; 
    };
} // endnamespace ft
#endif