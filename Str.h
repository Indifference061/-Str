#pragma once
#ifndef GUARD_Str_h
#define GUARD_Str_h
#include"Vec.h"
#include<iostream>
#include<string>
class Str {
	friend std::istream& operator>>(std::istream&, Str&);
public:
	Str& operator+=(const Str& s)
	{
		std::copy(s.data.begin(), s.data.end(), std::back_inserter(data));
		return *this;
	}
	typedef Vec<char>::size_type size_type;
	Str() {}
	Str(size_type n, char c) :data(n, c) {}
	Str(const char* c)
	{
		std::copy(c, c + std::strlen(c), std::back_inserter(data));
	}
	template<class In>Str(In i, In j)
	{
		std::copy(i, j, std::back_inserter(data));
	}
	char& operator[](size_type i) { return data[i]; }
	const char& operator[](size_type i) const { return data[i]; }
	size_type size()const { return data.size(); }
	bool strcompare(Str, Str);
	int cal(Vec<Str>& );
	void clear();
private:
	Vec<char> data;
};
bool isspace(const char& c)
{
	if (c == ' ') return true;
	else return false;
}
Str operator+(const Str& s, const Str& t)
{
	Str temp = s;
	temp += t;
	return temp;
}
std::istream& operator>>(std::istream& in, Str& s)
{
	s.data.clear();
	char c;
	while (in.get(c) && isspace(c));
	if (in)
	{
		do {
			s.data.push_back(c);
		} while (in.get(c) && !isspace(c) && c != '\n');
		if (in)
			in.unget();
	}
	return in;
}
std::ostream& operator<<(std::ostream& out, const Str& s)
{
	for (Str::size_type i = 0; i < s.size(); i++)
		out << s[i];
	return out;
}
void Str::clear()
{
	data.~Vec();
}
bool operator<(const Str& s, const Str& str)
{
	Str::size_type i = 0;
	while (s[i] == str[i]|| (s[i] - 32) == str[i] || (s[i] + 32) == str[i] &&i<std::min(s.size(),str.size())) i++;
	if (s[i] >= 'A' && s[i] <= 'Z'&&i<std::min(s.size(), str.size()))
	{
		char s1 = s[i]+32;
		if (s1 < str[i]) return true;
		else if (s1 > str[i]) return false;
	}
	else if (str[i] >= 'A' && str[i] <= 'Z' && i < std::min(s.size(), str.size()))
	{
		char s1 = str[i] + 32;
		if (s[i] < s1) return true;
		else if (s[i] > s1) return false;
	}
	else if ( i < std::min(s.size(), str.size()))
	{
		if (s[i] < str[i]) return true;
		else if (s[i] > str[i]) return false;
	}
	else if (i == s.size()) return true;
	else return false;
}
bool strcompare(Str str1, Str str2)
{
	if (str1.size() != str2.size()) return 0;
	else {
		for (int i = 0; i < str1.size(); i++)
		{
			if (str1[i] != str2[i] && (str1[i] - 32) != str2[i] && (str1[i] + 32) != str2[i])
			{
				return 0;
			}
		}
	}
	return 1;
}
#endif // !GUARD_Str_h
#pragma once
