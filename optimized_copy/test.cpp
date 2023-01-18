#include "gtest/gtest.h"
#include "../copy_concept/copy_using_concepts.h"

#include <vector>
#include <array>
#include <deque>
#include <list>
#include <forward_list>
#include <ctime>


TEST(StaticArray, Char) {
	{
		char ch[5] = { '1', '2', '3', '4', '5' };
		char new_ch[5] = { 0 };
		optimized_copy(std::begin(ch), std::end(ch), std::begin(new_ch));
		for (int i = 0; i < 5; ++i)
		{
			EXPECT_EQ(ch[i], new_ch[i]);
		}
	}

	{
		char ch[7] = { 0 };
		char new_ch[7] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g' };
		optimized_copy(std::begin(ch), std::end(ch), std::begin(new_ch));
		for (int i = 0; i < 7; ++i)
		{
			EXPECT_EQ(ch[i], new_ch[i]);
		}
	}
}

TEST(StaticArray, Int) {
	{
		int in[5] = { 1, 2, 3, 4, 5 };
		int new_in[5] = { 0 };
		optimized_copy(std::begin(in), std::end(in), std::begin(new_in));
		for (int i = 0; i < 5; ++i)
		{
			EXPECT_EQ(in[i], new_in[i]);
		}
	}

	{
		int in[7] = { 0 };
		int new_in[7] = { 1, 2, 3, 4, 5, 6, 7 };
		optimized_copy(std::begin(in), std::end(in), std::begin(new_in));
		for (int i = 0; i < 7; ++i)
		{
			EXPECT_EQ(in[i], new_in[i]);
		}
	}
}

TEST(StaticArray, String)
{
	{
		std::string str[6] = { "To", "be", "or", "not", "to", "be?" };
		std::string result[6] = { "", "", "", "", "", "" };
		optimized_copy(std::begin(str), std::end(str), std::begin(result));
		for (int i = 0; i < 5; ++i)
		{
			EXPECT_EQ(str[i], result[i]);
		}
	}

	{
		std::string str[6] = { "", "", "", "", "", "" };
		std::string result[6] = { "To", "be", "or", "not", "to", "be?" };
		optimized_copy(std::begin(str), std::end(str), std::begin(result));
		for (int i = 0; i < 5; ++i)
		{
			EXPECT_EQ(str[i], result[i]);
		}
	}
}

TEST(Vector, Int)
{
	{
		std::vector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		std::vector<int> result(10);
		optimized_copy(vec.begin(), vec.end(), result.begin());
		EXPECT_EQ(vec, result);
	}

	{
		std::vector<int> vec(10);
		std::vector<int> result = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		optimized_copy(vec.begin(), vec.end(), result.begin());
		EXPECT_EQ(vec, result);
	}

	{
		std::vector<int> vec = { 1, 1, 2, 2, -3, -3, -4, -4, 5, 5 };
		std::vector<int> result(10);
		optimized_copy(vec.begin(), vec.end(), result.begin());
		EXPECT_EQ(vec, result);
	}

	{
		std::vector<int> v1 = { 1, 2, 3, 5 };
		std::vector<int> v2 = { 1000, 1000, 1000 };
		std::vector<int> v3 = { 0 };
		std::vector<int> v4 = { 152456325 };
		std::vector<int> v5 = { -7000000, -7000000, -14654123, 543515555 };
		std::vector<std::vector<int>> src = { v1, v2, v3, v4, v5 };
		std::vector<std::vector<int>> dst(5);
		optimized_copy(src.begin(), src.end(), dst.begin());
		EXPECT_EQ(src, dst);
	}
}

TEST(Vector, IntBackinserted)
{
	{
		std::vector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		std::vector<int> result;
		optimized_copy(vec.begin(), vec.end(), std::back_inserter(result));
		EXPECT_EQ(vec, result);
	}
}

TEST(Vector, Char)
{
	{
		std::vector<char> vec = { 'a', 'a', 'b', 'b', 'c', 'c', 'd', 'd', 'e', 'e' };
		std::vector<char> result(10);
		optimized_copy(vec.begin(), vec.end(), result.begin());
		EXPECT_EQ(vec, result);
	}
}

TEST(Vector, String)
{
	{
		std::vector<std::string> vec = { "Hey,", "any", "news?", "Nothing?!", "Sad." };
		std::vector<std::string> result(5);
		optimized_copy(vec.begin(), vec.end(), result.begin());
		EXPECT_EQ(vec, result);
	}
}

TEST(String, CopyEntirely)
{
	std::string verse =
		"Two roads diverged in a yellow wood,\n\
		And sorry I could not travel both\n\
		And be one traveler, long I stood\n\
		And looked down one as far as I could\n\
		To where it bent in the undergrowth.\n\
		\n\
		Then took the other, as just as fair,\n\
		And having perhaps the better claim,\n\
		Because it was grassyand wanted wear;\n\
		Though as for that the passing there\n\
		Had worn them really about the same.\n\
		\n\
		And both that morning equally lay\n\
		In leaves no step had trodden black.\n\
		Oh, I kept the first for another day!\n\
		Yet knowing how way leads on to way,\n\
		I doubted if I should ever come back.\n\
		\n\
		I shall be telling this with a sigh\n\
		Somewhere agesand ages hence :\n\
		Two roads diverged in a wood, and I—\n\
		I took the one less traveled by,\n\
		And that has made all the difference.";

	std::string result;
	for (int i = 0; i < 800; ++i)
	{
		result.push_back('0');
	}

	optimized_copy(verse.begin(), verse.end(), result.begin());

	for (size_t i = 0; i < verse.size(); ++i)
	{
		EXPECT_EQ(verse[i], result[i]);
	}
}

TEST(String, CopyPartly)
{
	std::string verse =
		"Two roads diverged in a yellow wood,\n\
		And sorry I could not travel both\n\
		And be one traveler, long I stood\n\
		And looked down one as far as I could\n\
		To where it bent in the undergrowth.\n\
		\n\
		Then took the other, as just as fair,\n\
		And having perhaps the better claim,\n\
		Because it was grassyand wanted wear;\n\
		Though as for that the passing there\n\
		Had worn them really about the same.\n\
		\n\
		And both that morning equally lay\n\
		In leaves no step had trodden black.\n\
		Oh, I kept the first for another day!\n\
		Yet knowing how way leads on to way,\n\
		I doubted if I should ever come back.\n\
		\n\
		I shall be telling this with a sigh\n\
		Somewhere agesand ages hence :\n\
		Two roads diverged in a wood, and I—\n\
		I took the one less traveled by,\n\
		And that has made all the difference.";
	std::string result;
	for (int i = 0; i < 100; ++i)
	{
		result.push_back('0');
	}

	optimized_copy(verse.begin() + 100, verse.begin() + 200, result.begin());

	for (int i = 0; i < 100; ++i)
	{
		EXPECT_EQ(verse[i + 100], result[i]);
	}
}

TEST(DifferentContainers, VectorAndArray)
{
	{
		int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		std::vector<int> vec(10);
		optimized_copy(std::begin(arr), std::end(arr), vec.begin());
		auto a = std::begin(arr);
		auto v = vec.begin();
		for (; a != std::end(arr); ++a, ++v)
		{
			EXPECT_EQ(*a, *v);
		}
	}

	{
		int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		std::vector<int> vec(10);
		optimized_copy(vec.begin(), vec.end(), std::begin(arr));
		auto a = std::begin(arr);
		auto v = vec.begin();
		for (; v != vec.end(); ++a, ++v)
		{
			EXPECT_EQ(*a, *v);
		}
	}
}

TEST(DifferentContainers, VectorAndString)
{
	{
		std::string str = "Honesty is the best policy.";
		std::vector<char> vec(28);
		optimized_copy(str.begin(), str.end(), vec.begin());
		for (int i = 0; i < 28; ++i)
		{
			EXPECT_EQ(str[i], vec[i]);
		}
	}
}

TEST(DifferentContainers, VectorAndList)
{
	{
		std::vector<int> vec(10);
		std::list<int> lis = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		optimized_copy(vec.begin(), vec.end(), lis.begin());
		auto l = lis.begin();
		auto v = vec.begin();
		for (; v != vec.end(); ++l, ++v)
		{
			EXPECT_EQ(*l, *v);
		}
	}

	{
		std::vector<int> vec(10);
		std::list<int> lis = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		optimized_copy(lis.begin(), lis.end(), vec.begin());
		auto l = lis.begin();
		auto v = vec.begin();
		for (; l != lis.end(); ++l, ++v)
		{
			EXPECT_EQ(*l, *v);
		}
	}
}

TEST(DifferentContainers, DequeAndForwardList)
{
	{
		std::deque<int> dq = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		std::forward_list<int> fl(10);
		optimized_copy(dq.begin(), dq.end(), fl.begin());
		auto d = dq.begin();
		auto l = fl.begin();
		for (; d != dq.end(); ++d, ++l)
		{
			EXPECT_EQ(*d, *l);
		}
	}
}
