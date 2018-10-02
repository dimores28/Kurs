#include <iostream>
#include <string>
#include <memory>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

template<class T>
void print(const T& t)
{
	for (typename T::const_iterator it = t.begin(); it != t.end(); ++it)
	{
		cout << *it ;
	}

	cout <<  endl;
}



template<class T>
struct Node
{
private:

	template<class Iter>
	class NodeIterator
	{
		friend struct Node;

	    public:
			typedef Iter iterator_type;
			typedef std::forward_iterator_tag iterator_category;
			typedef iterator_type value_type;
			typedef ptrdiff_t difference_type;
			typedef iterator_type& reference;
			typedef iterator_type* pointer;

			iterator_type* value;
	private:
		NodeIterator(Iter* p): value(p){}
	public:
		NodeIterator(const NodeIterator& it) : value(it.value){}

		bool operator !=(NodeIterator const& other)const
		{
			return value != other.value;
		}
		//Не обязательно реализововать 
		bool operator ==(NodeIterator const& other)const
		{
			return value == other.value;
		}

		typename NodeIterator::reference operator*()const
		{
			return *value;
		}

		NodeIterator& operator++()
		{
			if (value->parent == nullptr)
				value = nullptr;
			else if (value->parent->right.get() == value)
				value = value->parent;
			else
			{
				value = value->parent;
				if (value->right.get() != nullptr)
				{
					value = value->right.get();
					while (value->left.get() != nullptr)
						value = value->left.get();
				}
			}
			return *this;
		}
	};

public:
	T value;
	unique_ptr <Node> left;
	unique_ptr <Node> right;
	Node* parent;

	Node(const T& value, unique_ptr <Node> left, unique_ptr <Node> right, Node* parent)
		: value(value), left(std::move(left)), right(std::move(right)), parent(parent)
	{}

	Node(const Node&) = delete;

	typedef NodeIterator<Node> iterator;
	typedef NodeIterator<const Node> const_iterator;

	iterator begin()
	{
		Node* node = this;
		while (node->left != nullptr)
			node = node->left.get();
		return iterator(node);
	}

	iterator end()
	{
		return nullptr;
	}

	const_iterator begin()const
	{
		const Node* node = this;
		while (node->left != nullptr)
			node = node->left.get();
		return const_iterator(node);
	}


	const_iterator end()const
	{
		return nullptr;
	}

	friend std::ostream& operator<<(std::ostream& os, const Node& n)
	{
		return os << n.value;
	}
};


struct Point
{
	unsigned x;
	unsigned y;

	friend bool operator<(const Point& p1, const Point& p2)
	{
		if (p1.y < p2.y)
			return true;
		if (p1.y > p2.y)
			return false;

		return (p1.x < p2.x);
	}

};


//JAVA ITERATOR реализация на C++
template <class Container>
class Iterator
{
	Container conteiner;
	bool isStart;
	typename Container::iterator it;
public:
	Iterator(const Container& c): conteiner(c), isStart(false){}
	Iterator() = delete;

	bool next()
	{
		if (!isStart)
		{
			it = conteiner.begin();
			isStart = true;
		}
		else
			it++;

		return !(it == conteiner.end());

	}

	inline typename Container::value_type current() const
	{
		return *it;
	}
};


template<class Container>
Iterator<Container> create_iterator(const Container& c)
{
	return Iterator<Container>(c);
}



int main()
{

/*	string str{ "Hello world\n" };

	for (std::string::iterator it = str.begin(); it != str.end(); ++it)
	{
		cout << *it << endl;
	}

	for (auto it = str.begin(); it != str.end(); ++it)
	{
		cout << *it << endl;
	}

	for (auto &&s : str)
	{
		cout << s << endl;
	}

	print(str);
	*/


	auto root = make_unique<Node<string>>("a1", nullptr, nullptr, nullptr);
	root->left = make_unique<Node<string>>("b1", nullptr, nullptr, root.get());
	root->right = make_unique<Node<string>>("b2", nullptr, nullptr, root.get());

	auto b1 = root->left.get();
	auto b2 = root->right.get();

	b1->left = make_unique<Node<string>>("c1", nullptr, nullptr, b1);
	b1->right = make_unique<Node<string>>("c2", nullptr, nullptr, b1);

	b2->left = make_unique<Node<string>>("c3", nullptr, nullptr, b2);
	b2->right = make_unique<Node<string>>("c3", nullptr, nullptr, b2);

	auto c1 = b1->left.get();
	auto c2 = b1->right.get();
	auto c3 = b2->left.get();
	auto c4 = b2->right.get();

	/*
	cout << root->value << endl;
	cout << b1->value << endl;
	cout << b2->value << endl;
	cout << c1->value << endl;
	cout << c2->value << endl;
	cout << c3->value << endl;
	cout << c4->value << endl;
   */

	/*
	auto it = root->begin();
	cout << *it<< endl;
	++it;
	cout << *it << endl;
	++it;
	cout << *it << endl;*/

/*
	for (auto it = root->begin(); it != root->end(); ++it)
	{
		cout << *it << endl;
	}

	for (auto&& node : *root)
	{
		cout << node << endl;
	}





	std::set<Point> points = { {5,3}, {1,2}, {0,0} };


	for (auto it = points.begin(); it != points.end(); ++it)
	{
		Point& n = const_cast<Point&> (*it);
		//it->x = 0;
		//it->y = 0;

		n.x = 0;
		n.y = 0;
	}

	for (auto &&p : points)
	{
		cout << p.x << " " << p.y << endl;
	}

	string str{ "Hello world\n" };
	auto it = str.begin();
	cout << *std::next(it) << endl;
	cout << std::distance(str.begin(), str.end()) << endl;
	std::advance(it, 3);
	std::advance(it, -2);
	cout << *it << endl;

	auto first = root->begin();
	std::advance(first, 2);
	std::next(first);
	cout << *first << endl;


	typename std::iterator_traits<std::set<int>::iterator>::iterator_category a;
	*/




	string s = "Hello world";
	std::reverse_iterator<std::string::iterator> r = s.rbegin();
	string new_s(r, s.rend());
	cout << new_s << endl;

	std::sort(s.begin(), s.end());
	cout << s << endl;
	std::sort(std::make_reverse_iterator(s.end()), std::make_reverse_iterator(s.begin()));
	cout << s << endl;

	///////Using JAVA Iteratir
	vector<int> data{ 1,2,3,4,5,6,7,8,9,0 };
	auto iter = create_iterator(data);
	while (iter.next())
	{
		cout << iter.current() << " ";
	}
	cout << endl;



	return 0;
}

