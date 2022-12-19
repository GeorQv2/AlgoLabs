#include <iostream>
#include <chrono>
#include <format>

template<typename T, typename Compare>
T GetPivot(T& a, T& b, T& c, Compare cp) {
	if ((cp(a, b) && cp(c, a)) || (cp(a, c) && cp(b, a)))
	{
		return a;
	}
	else if ((cp(b, a) && cp(c, b)) || (cp(b, c) && cp(a, b))) 
	{
		return b;
	}
	else 
	{
		return c;
	}
}

template<typename T, typename Compare>
void InsertionSort(T* first, T* last, Compare cp) {
	if (first == last)
	{
		return;
	}
	T val;
	T* j;
	for (T* i = first + 1; i < last; i++)
	{
		val = *i;
		j = i - 1;
		while (j >= first && cp(val, *(j)))
		{
			*(j + 1) = std::move(*j);
			j--;
		}
		*(++j) = std::move(val);
	}
}

template<typename T, typename Compare>
void QuickSort(T* first, T* last, Compare cp, bool opt = false) {
	if (opt && ((last - first) <= 13))
	{
		InsertionSort(first, last, cp);
	}
	else {
		while (first < last)
		{
			T* i = first;
			T* j = last;
			T pivot = GetPivot(*first, *last, *(first + ((last - first) / 2)), cp);
			while (true) {
				while (cp(*i, pivot))
				{
					i++;
				}
				while (cp(pivot, *j))
				{
					j--;
				}
				if (i >= j)
				{
					break;
				}
				std::swap(*i, *j);
				i++;
				j--;
			}
			if (last - j > j - first)
			{
				QuickSort(first, j, cp);
				first = j + 1;
			}
			else {
				QuickSort(j + 1, last, cp);
				last = j;
			}
		}
	}
}

template<typename T, typename Compare>
std::string RunTest(int arraySize, Compare cp) 
{

	float timeForIS = 0;
	float timeForQS = 0;
	T* isArray = new T[arraySize];
	T* qsArray = new T[arraySize];
	auto start = std::chrono::high_resolution_clock::now();
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> duration;
	for (size_t i = 0; i < 15000; i++)
	{
		for (size_t j = 0; j < arraySize; j++)
		{
			isArray[j] = arraySize - j;
			qsArray[j] = j;
		}
		//Insertion sort
		start = std::chrono::high_resolution_clock::now();
		InsertionSort(isArray, isArray + arraySize - 1, cp);
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;
		timeForIS += duration.count();
		//
		
		//Quick sort
		start = std::chrono::high_resolution_clock::now();
		QuickSort(qsArray, qsArray + arraySize - 1, cp);
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;
		timeForQS += duration.count();
		//
	}
	delete[] isArray;
	delete[] qsArray;
	isArray = nullptr;
	qsArray = nullptr;
	return std::format("as: {}, is: {}, qs: {}\n", arraySize, timeForIS, timeForQS);
}


int main() 
{
	std::string result = "";
	for (size_t i = 1; i < 31; i++)
	{
		result += RunTest<int>(i, [](int a, int b) { return a < b; });
	}
	std::cout << result << std::endl;
}