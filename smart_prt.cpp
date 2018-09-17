#include <iostream>
#include <algorithm>
#include <memory>

using namespace std;

struct Point
{
	int x;
	int y;
	Point(): x(1), y(1){}
	Point(int _x, int _y): x(_x), y(_y){}
};

ostream& operator<<(ostream& os, const Point& p)
{
	return os << "x: " << p.x << " y: " << p.y << endl;
}

struct D
{
	D() { cout << "D constructor\n"; }
	~D(){}

	void bar() { cout << "Bar\n"; }

	void operator()(Point* p)
	{
		cout << "D destruct\n";
		delete[] p;
	}
};

struct Foo;

struct Bar {
	Bar() { cout << "Bar constructor\n"; }
	~Bar() { cout << "Bar destruct\n"; }

	weak_ptr<Foo> foo;

};

struct Foo {
	Foo() { cout << "Foo constructor\n"; }
	~Foo() { cout << "Foo destruct\n"; }

	shared_ptr<Bar> bar;
};





int main()
{
	
	auto_ptr<Point> p1 = auto_ptr<Point>(new Point);


	unique_ptr<Point> up1 = unique_ptr<Point>(new Point);
	unique_ptr<Point> up2 = move(up1);

	//Нельзя делать ошибка сегментации оператор = перемещающий 
	//cout << *up1 << endl;

	cout << *up2 << endl;

	unique_ptr<Point> up3(new Point);
	auto up4 = unique_ptr<Point>(new Point);
	unique_ptr<Point> up5 = make_unique<Point>();
	unique_ptr<Point> up6 = make_unique<Point>(3,5);
	auto up7 = make_unique<Point>(3, 5);

	cout << *up7.get() << endl;

	auto up8 = make_unique<Point[]>(6);

	cout << up8[5] << endl;
	
	

	//operator delete
	//operator delete[]

	{
		unique_ptr<Point, D> up9(new Point[10], D());
		cout << up9.get()[9] << endl;
	}

	{
		/*unique_ptr<Point, std::function<void(Point*)>> up10(new Point[3], [](auto *p) {
		delete[] p;
		});*/
	}

	unique_ptr<Point, D> up11(new Point[10], D());
	auto my_deleter = up11.get_deleter();
	my_deleter.bar();

	unique_ptr<Point> up12 = make_unique<Point>(1, 1);
	unique_ptr<Point> up13 = make_unique<Point>(2, 2);
	up12.swap(up13);

	cout << *up12 << endl;

	up12.reset(new Point);

	cout << *up12 << endl;
	up12.reset();
	up12.reset(nullptr);


	shared_ptr<Point> sp1 = make_shared<Point>(1, 4);
	auto sp2 = sp1;
	cout << *sp1 << endl;
	cout << *sp2 << endl;
	cout << sp2.use_count() << endl;
	

	auto test_use_count1 = [](const auto& value)
	{
		cout << value.use_count() << endl;
	};

	test_use_count1(sp2);

	auto test_use_count2 = [](auto value)
	{
		cout << value.use_count() << endl;
	};

	test_use_count2(sp2);

	auto sp3 = make_shared<Point>();

	{
		auto foo = make_shared<Foo>();

		foo->bar = make_shared<Bar>();
		foo->bar->foo = foo;
	}
	//A -> B
	//B -> A

	auto sp10 = make_shared<Point>();
	weak_ptr<Point>w(sp10);
	
	cout << *w.lock() << endl;



	return 0;
}