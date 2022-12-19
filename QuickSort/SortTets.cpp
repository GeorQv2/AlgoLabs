#include "pch.h"
#include "CppUnitTest.h"
#include "..\\SortComparision\SortComparison.cpp";

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SortTets
{
	TEST_CLASS(SortTets)
	{
	public:
		
		//Insertion Test
		TEST_METHOD(TestMethod1)
		{
			int size = 3;
			int* ls = new int[size];
			ls[0] = 3;
			ls[1] = 2;
			ls[2] = 1;
			Assert::IsTrue(ls[0] == 3);
			Assert::IsTrue(ls[1] == 2);
			Assert::IsTrue(ls[2] == 1);
			InsertionSort(ls, ls + size, [](int a, int b) { return a < b; });
			Assert::IsTrue(ls[0] == 1);
			Assert::IsTrue(ls[1] == 2);
			Assert::IsTrue(ls[2] == 3);
			delete[] ls;
		}

		//Insertion Test 2 on bigger set
		TEST_METHOD(TestMethod2)
		{
			int size = 1000;
			int* ls = new int[size];
			for (size_t i = 0; i < size; i++)
			{
				ls[i] = size - i;
			}
			InsertionSort(ls, ls + size, [](int a, int b) { return a < b; });
			for (size_t i = 0; i < size; i++)
			{
				Assert::IsTrue(ls[i] == i + 1);
			}
			delete[] ls;
		}

		//Insertion Test 3 strings
		TEST_METHOD(TestMethod3)
		{
			int size = 3;
			std::string* ls = new std::string[size];
			ls[0] = "C";
			ls[1] = "B";
			ls[2] = "A";
			InsertionSort(ls, ls + size, [](std::string a, std::string b) { return a < b; });
			Assert::IsTrue(ls[0] == "A");
			Assert::IsTrue(ls[1] == "B");
			Assert::IsTrue(ls[2] == "C");
			delete[] ls;
		}

		//QuickSort Test
		TEST_METHOD(TestMethod4)
		{
			int size = 3;
			int* ls = new int[size];
			ls[0] = 3;
			ls[1] = 2;
			ls[2] = 1;
			Assert::IsTrue(ls[0] == 3);
			Assert::IsTrue(ls[1] == 2);
			Assert::IsTrue(ls[2] == 1);
			QuickSort(ls, ls + size - 1, [](int a, int b) { return a < b; });
			Assert::IsTrue(ls[0] == 1);
			Assert::IsTrue(ls[1] == 2);
			Assert::IsTrue(ls[2] == 3);
			delete[] ls;
		}

		//QuickSort Test 2 on bigger set
		TEST_METHOD(TestMethod5)
		{
			int size = 1000;
			int* ls = new int[size];
			for (size_t i = 0; i < size; i++)
			{
				ls[i] = size - i;
			}
			QuickSort(ls, ls + size - 1, [](int a, int b) { return a < b; });
			for (size_t i = 0; i < size; i++)
			{
				Assert::IsTrue(ls[i] == i + 1);
			}
			delete[] ls;
		}

		//QuickSort Test 3 strings
		TEST_METHOD(TestMethod6)
		{
			int size = 3;
			std::string* ls = new std::string[size];
			ls[0] = "C";
			ls[1] = "B";
			ls[2] = "A";
			QuickSort(ls, ls + size - 1, [](std::string a, std::string b) { return a < b; });
			Assert::IsTrue(ls[0] == "A");
			Assert::IsTrue(ls[1] == "B");
			Assert::IsTrue(ls[2] == "C");
			delete[] ls;
		}
	};
}
