#pragma once

#include <iostream>
#include <tuple>

using namespace std;

template <size_t> struct int_{};


template<class Tuple>
ostream& print_tuple(ostream& out, const Tuple& t, int_< 1>)
{
	return cout << get<tuple_size<Tuple>::value - 1>(t);
}

template<class Tuple, size_t Pos>
ostream& print_tuple(ostream& out, const Tuple& t, int_< Pos>)
{
	cout << get<tuple_size<Tuple>::value - Pos>(t) << ", ";
	return print_tuple(out, t, int_<Pos-1>());
}

template<class... Args>
ostream& operator<<(ostream& out, const tuple<Args...>& t)
{
	out << "(";

	print_tuple(out, t, int_<sizeof...(Args)>());

	return out << ")";
}