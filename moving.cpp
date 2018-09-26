#include <iostream>
#include <type_traits>
#include <vector>
#include <string>
#include <ctime>

using namespace std;
using BigData = vector<vector<std::string>>;

struct A
{
	A() { cout << "A default constructor\n"; }
	A(const int& i) { cout << i << endl; }

	void foo(const int& i) { cout << "this is lvalue\n"; }
	void foo(const int&& i) { cout << "this is rvalue\n"; }

	template<class T>
	void fooT(const T& i) { cout << "this is lvalue\n"; }

	template<class T>
	void fooT(const T&& i) 
	{ 
		if (std::is_rvalue_reference<T>::value) cout << "RVALUE\n";
		if (std::is_lvalue_reference<T>::value) cout << "LVALUE\n";
		if (!std::is_reference<T>::value) cout << "NO REFERENCE\n";
	}
};


struct B
{
	B(A a){}
};


struct C
{
	void inc(int&& i)
	{
		i++;
	}
};


int foo()
{
	return 42;
}



int&& move_int(int& i)
{
	return static_cast<int&&>(i);
}


int&& move_int(int&& i)
{
	return static_cast<int&&>(i);
}




template<class T>
T&& moveT(T&& t)
{
	return static_cast<T&&>(t);
}



template<class T>
struct my_remove_reference
{
	typedef T value;
};

template<class T>
struct my_remove_reference<T&>
{
	typedef T value;
};


template<class T>
struct my_remove_reference<T&&>
{
	typedef T value;
};


template<class T>
constexpr typename my_remove_reference<T>::value&& 
moveReal(T&& t)noexcept
{
	return static_cast<typename my_remove_reference<T>::value&&>(t);
}




class Data
{
public:
	Data(){}
	Data(const Data& data){}
	Data(Data&& data){}



};



template<class T>
T&& forwardT(T& t)
{
	return static_cast<T&&>(t);
}

template<class T>
constexpr T&& forwardReal(typename my_remove_reference<T>::value& t) noexcept
{
	return static_cast<T&&>(t);
}



//A& A&, A -> A&&
template<class T, class Arg>
T* make_ptr(Arg&& arg)
{
	return new T(std::forward<Arg>(arg));
}



struct Pakage
{
	BigData data;
	Pakage(const BigData& _data) : data(_data){}
	Pakage(const BigData&& data) : data(std::move(data)) {}
	Pakage() = delete;

	void send(){}
};


int main()
{
	/*A a();
	A a1;
	A a2{42};
	
	int i = 1;
	B b(A{ i });

	A(x); // это аналогично A (x2) == A x3;

	//rvalue - временный объект

	int ix = 5;
	x.foo(ix);
	x.foo(29);
	x.fooT(nullptr);
	//x.fooT("Hello World");


	C c;
	int i3 = 3;
	c.inc(3);



	int i8 = 8;
	int&& i8_ref = 8;

	a2.foo(foo());

	int i10 = 10;
	a1.foo(i10);
	a1.foo(move(i10));


	int i11 = 11;
	static_cast<int&&>(i11);
	

	int i12 = 12;
	a1.foo(moveReal(i12));
	a1.foo(moveReal(12));




	Data d;
	Data* d2 = make_ptr<Data>(d);             //Копирование
	Data* d3 = make_ptr<Data>(Data());        //Прермещение
	delete d2;
	delete d3;


	std::forward<int>(5);
	//std::forward<int&>(5);

	a1.fooT("String");

	A x2;
	x2.fooT(nullptr);
	x2.fooT(42);
	int i13 = 13;
	x2.fooT(i13);
	x2.fooT(std::move(i13));*/


	cout << sizeof(std::string) << endl; //24
	cout << sizeof(std::vector<vector<string>>) << endl; // 12


	auto start_time = clock();
	{
		BigData bigData(1000, std::vector<std::string>(1000, "DATA")); //2.4 Gb

		Pakage pck(std::move(bigData));
		pck.send();
		cout << bigData.size() << endl;
	}
	auto end_time = clock();

	cout << (end_time - start_time) << endl;

	return 0;
}