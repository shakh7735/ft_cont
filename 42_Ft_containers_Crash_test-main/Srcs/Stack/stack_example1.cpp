/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_exmaple1.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:53:36 by vismaily          #+#    #+#             */
/*   Updated: 2022/12/18 16:48:58 by tumolabs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Example 1 */
/* Example for constructor without parametrs */
/* Example for size and push_back */

#include "test.hpp"

namespace	NS_TEST
{
	const std::string	stack_example1(double &_time)
	{
		std::ostringstream	ss;

		NS::stack<int, NS::vector<int> >	st;
		ss << " " << st.size();
		st.push(42);
		ss << " " << st.top();
		ss << " " << st.size();
		st.push(84);
		ss << " " << st.top();
		ss << " " << st.size();
		st.push(168);
		ss << " " << st.top();
		ss << " " << st.size();
		st.push(336);
		st.push(672);
		ss << " " << st.top();
		st.pop();
		ss << " " << st.top();
		ss << " " << st.empty();
		ss << " " << st.size();

		_time = 0;
		return (ss.str());
	}
}
