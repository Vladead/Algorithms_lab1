#include "pch.h"
#include "CppUnitTest.h"
#include "../Program1/Map.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace Testslaba1
{
	TEST_CLASS(TestLab1)
	{
		Map<int, char> map;
	public:
		TEST_METHOD_INITIALIZE(init)
		{
			map.insert(1, 'a');
			map.insert(2, 'b');
			map.insert(3, 'c');
		}
		TEST_METHOD(test_insert)
		{
			map.insert(4, 'd');
			Assert::AreEqual('d', map.find(4));
			try {
				map.insert(1, 'b');
			}
			catch (invalid_argument e) {
				Assert::AreEqual(e.what(), "This element is already in the map");
			}

		}
		TEST_METHOD(test_remove)
		{
			map.remove(1);
			try {
				map.find(1);
			}
			catch (invalid_argument e) {
				Assert::AreEqual(e.what(), "This element isn't in the map");
			}
			map.clear();
			try {
				map.remove(1);
			}
			catch (invalid_argument e) {
				Assert::AreEqual(e.what(), "Map is empty");
			}
		}
		TEST_METHOD(test_get_keys) {
			List<int> ls = map.get_keys();
			Assert::AreEqual(ls.at(0), 1);
			Assert::AreEqual(ls.at(1), 2);
			Assert::AreEqual(ls.at(2), 3);
		}
		TEST_METHOD(test_get_values) {
			List<char> ls = map.get_values();
			Assert::AreEqual(ls.at(0), 'a');
			Assert::AreEqual(ls.at(1), 'b');
			Assert::AreEqual(ls.at(2), 'c');
		}
		TEST_METHOD(test_find) {
			Assert::AreEqual(map.find(1), 'a');
			try {
				map.find(4);
			}
			catch (invalid_argument e) {
				Assert::AreEqual(e.what(), "This element isn't in the map");
			}
		}
		TEST_METHOD(test_clear) {
			Assert::AreEqual(map.find(1), 'a');
			map.clear();
			try {
				map.find(1);
			}
			catch (invalid_argument e) {
				Assert::AreEqual(e.what(), "Map is empty");
			}
		}
		TEST_METHOD(test_print) {
			map.clear();
			try {
				map.print();
			}
			catch (runtime_error e) {
				Assert::AreEqual(e.what(), "Map is empty");
			}
		}
	};
}
