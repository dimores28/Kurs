#include <iostream>
#include <tuple> //Кортеж
#include <string>
#include <cstdint>
#include <algorithm>
#include <vector>

#include "print_tuple.h"
using namespace std;

//parameter pack
template< class... Args>
void print( Args... args)
{
}


template<class Head, class... Args>
void print(Head head, Args... args)
{
	cout << head << endl;
	print(args...);
}


tuple<int, string> get_student()
{
	return make_tuple(20, "Vasya");
}

int main()
{ 
	print(1, 2, "C++");
	print("==============================\n");

	tuple<int, string> t1{ 42,"C++" };
	tuple<int, string> t2( 42,"C++" );
	tuple<int, string> t3 = { 42,"C++" };
	
	tuple<int, string> t4 = make_tuple( 42,"C++" );
	//tuple<> t6;

	auto t5 = make_tuple(42, "C++");

	print(get<0>(t5));
	print(get<1>(t5));
	
	int a;
	string b;
	tie(a, b) = make_tuple(33, "C++");

	print(a, b);

	auto t6 = tie(a, b);


	int age;
	string name;
	tie(age, name) = get_student();
	print(age, name);

	auto get_student2 = []() {
		return make_tuple(23, "Katya");
	};
	tie(age, name) = get_student2();
	print(age, name);


	if (make_tuple(42, "a") > make_tuple(41, "a"))
		print("true");
	if (make_tuple(42, "a") < make_tuple(42, "b"))
		print("true");

	struct Man {
		uint16_t age;
		uint16_t langs;
		uint16_t jobs;

	};

	Man m1{ 22,1,1 };
	Man m2{ 20,1,2 };
	Man m3{ 25,5,1 };

	vector<Man> mans{ m1,m2,m3 };
	//в студии не работает 
	// variant 1
	std::sort(mans.begin(), mans.end(), [](const Man& l, Man& r) {
		if (l.jobs < r.jobs)
			return true;
		if(l.langs < r.langs)
			return true;
		return l.age < r.age;
	});
	
	//variant 2
	// sort(mans.begin(), mans.end(), [](const Man& l, const Man& r) {
	//	return tie(l.jobs, l.langs, l.age) > tie(r.jobs, r.langs, r.age);
	//});

	//for_each(mans.begin(), mans.end(), [](const Man& man) {
	//	cout << "Jobs: " << man.jobs << " Langs: " << man.langs << " Age: " << man.age << endl;
	//});

	auto super_tuple = tuple_cat(make_tuple(1, 2, 3), make_tuple(4, 5, 6));

	cout << super_tuple << endl;


	return 0;
}