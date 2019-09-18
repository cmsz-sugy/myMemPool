#pragma once
#ifndef TEST_H
#define TEST_H
template <typename T>
class Test
{
public:
	Test(T v)
		: t(v)
	{}
	void testOutput();
	void a();
	
private:
	T t;
};
template<typename T>
void Test<T>::testOutput()
{
	std::cout << "This is a test output: " << t;
}

#endif 
