#pragma once
#include <iostream>
#include <type_traits>
#include <algorithm>
#include <concepts>



template <typename T, typename U>
concept optim_copy = (std::contiguous_iterator<T>
	&& std::contiguous_iterator<U>
	&& std::is_trivial_v<typename std::iterator_traits<T>::value_type>
	&& std::same_as<typename std::iterator_traits<T>::value_type, typename std::iterator_traits<U>::value_type>);

//first case
template<typename InputIterator, typename OutputIterator>
requires(!optim_copy<InputIterator, OutputIterator>)
OutputIterator optimized_copy(InputIterator first, InputIterator last, OutputIterator result) noexcept
{
	for (auto i = first; i != last; ++i, ++result)
	{
		*result = *i;
	}
	return result;
}

//second case
template<typename InputIterator, typename OutputIterator>
requires(optim_copy<InputIterator, OutputIterator>)
OutputIterator optimized_copy(InputIterator first, InputIterator last, OutputIterator result) noexcept
{
	auto n = std::distance(first,last);
	std::memcpy(&(*result), &(*first), sizeof(*first) * n);
	return result;
}
