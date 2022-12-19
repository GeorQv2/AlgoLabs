#include "pch.h"
#include "CppUnitTest.h"
#include "..\DynamicArray\DArray.cpp";
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DArrayTests
{
	TEST_CLASS(DArrayTests)
	{
	public:
		
		//Default Constructor test
		TEST_METHOD(TestMethod1)
		{
			DArray<int> darray;
			Assert::IsTrue(darray.size() == 0);
			Assert::IsTrue(darray.capacity() == 10);
			Assert::IsTrue(darray.getPointer() != 0);
		}

		//Integer Constructor test
		TEST_METHOD(TestMethod2) {
			DArray<int> darray(4);
			Assert::IsTrue(darray.size() == 0);
			Assert::IsTrue(darray.capacity() == 4);
			Assert::IsTrue(darray.getPointer() != 0);
		}

		//Copy Constructor test
		TEST_METHOD(TestMethod3) {
			DArray<std::string> dar1;
			dar1.insert("F");
			DArray<std::string> dar2(dar1);
			Assert::IsTrue(dar1.size() == dar2.size());
			Assert::IsTrue(dar1.capacity() == dar2.capacity());
			Assert::IsTrue(dar1.getPointer() != dar2.getPointer());
			for (size_t i = 0; i < dar1.size(); i++)
			{
				dar1[i] == dar2[i];
			}
			dar2.insert("B");
			Assert::IsTrue(dar1.size() != dar2.size());
		}

		//Copy Constructor test
		TEST_METHOD(TestMethod4) {
			DArray<int> dar1;
			dar1.insert(10);
			DArray<int> dar2;
			dar2 = dar1;
			Assert::IsTrue(dar1.size() == dar2.size());
			Assert::IsTrue(dar1.capacity() == dar2.capacity());
			Assert::IsTrue(dar1.getPointer() != dar2.getPointer());
			dar2.insert(20);
			Assert::IsTrue(dar1.size() != dar2.size());
		}

		//Move Constructor test
		TEST_METHOD(TestMethod5) {
			DArray<std::string> dar1;
			dar1.insert("1");
			dar1.insert("2");
			dar1.insert("3");
			int size = 3;
			DArray<std::string> dar2(std::move(dar1));
			Assert::IsTrue(dar1.getPointer() == nullptr);
			Assert::IsTrue(dar2.size() == size);
			Assert::IsTrue(dar2[1] == "2");
		}

		//Append test
		TEST_METHOD(TestMethod6) {
			DArray<int> dar;
			int size = 10;
			for (size_t i = 0; i < size; i++)
			{
				dar.insert(i);
			}
			for (size_t i = 0; i < size; i++)
			{
				Assert::IsTrue(dar[i] == i);
			}
			Assert::IsTrue(dar.size() == size);
		}

		//Insert test
		TEST_METHOD(TestMethod7) {
			DArray<int> dar;
			dar.insert(1);
			dar.insert(2);
			dar.insert(3);
			dar.insert(4);
			dar.insert(5);
			dar.insert(2, 100);
			Assert::IsTrue(dar[0] == 1);
			Assert::IsTrue(dar[1] == 2);
			Assert::IsTrue(dar[2] == 100);
			Assert::IsTrue(dar[3] == 3);
			Assert::IsTrue(dar[4] == 4);
			Assert::IsTrue(dar[5] == 5);
			Assert::IsTrue(dar.size() == 6);
		}

		//Resize check
		TEST_METHOD(TestMethod8) {
			DArray<int> dar(4);
			Assert::IsTrue(dar.capacity() == 4);
			Assert::IsTrue(dar.size() == 0);
			dar.insert(1);
			dar.insert(2);
			dar.insert(3);
			dar.insert(4);
			dar.insert(5);
			Assert::IsTrue(dar.capacity() == 8);
			Assert::IsTrue(dar.size() == 5);
		}

		//Remove check 
		TEST_METHOD(TestMethod9) {
			DArray<int> dar;
			dar.insert(0);
			dar.insert(1);
			dar.insert(2);
			dar.insert(3);
			dar.insert(4);
			dar.remove(4);
			Assert::IsTrue(dar.size() == 4);
			Assert::IsTrue(dar[3] == 3);
		}

		//Move Assignment Operator
		TEST_METHOD(TestMethod10) {
			DArray<int> a;
			a.insert(10);
			a.insert(20);
			DArray<int> b;
			b = std::move(a);
			Assert::IsTrue(a.getPointer() == nullptr);
			Assert::IsTrue(b[0] == 10);
			Assert::IsTrue(b[1] == 20);
		}

		//Iterator test
		TEST_METHOD(TestMethod11) {
			DArray<int> a;
			for (int i = 0; i < 10; ++i) {
				a.insert(i + 1);
			}
			int i = 1;
			for (auto it = a.iterator(); it.hasCurrent(); it.next()) {
				Assert::IsTrue(it.get() == i++);
			}
		}
	};
}
