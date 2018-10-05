#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;



struct ci_char_traits : public std::char_traits<char> {
	static char to_upper(char ch) {
		return std::toupper((unsigned char)ch);
	}
	static bool eq(char c1, char c2) {
		return to_upper(c1) == to_upper(c2);
	}
	static bool lt(char c1, char c2) {
		return to_upper(c1) <  to_upper(c2);
	}
	static int compare(const char* s1, const char* s2, size_t n) {
		while (n-- != 0) {
			if (to_upper(*s1) < to_upper(*s2)) return -1;
			if (to_upper(*s1) > to_upper(*s2)) return 1;
			++s1; ++s2;
		}
		return 0;
	}
	static const char* find(const char* s, int n, char a) {
		auto const ua(to_upper(a));
		while (n-- != 0)
		{
			if (to_upper(*s) == ua)
				return s;
			s++;
		}
		return nullptr;
	}
};

using ci_string = std::basic_string<char, ci_char_traits>;

std::ostream& operator<<(std::ostream& os, const ci_string& str) {
	return os.write(str.data(), str.size());
}





int main()
{
	/*
	std::string s{ "asaasasa" }; //std::basic_string<char> s1{ "asaasasa" };
	std::wstring ws{ L"saasasassa" };

	char c = ' ';
	wchar_t wc = L' ';
*/
	
	ci_string s1 = "Hello";
	ci_string s2 = "heLLo";
	if (s1 == s2)
		std::cout << s1 << " and " << s2 << " are equal\n";



	int i = 1;
	wcout << to_wstring(i) << endl;




	return 0;
}