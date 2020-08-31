#include <vector>
#include <algorithm>
#include <iostream>
#include <unordered_set>

template <typename T>
void printContainer(T & container)
{
	for (auto& value : container) {
		std::cout << value << ' ';
	}
	std::cout<<std::endl;
}

/* First way: sort + unique
   Time complexity: O(nlogn) + O(n)-> O(nlogn)
   Space complexity: O(1) + O(1) -> O(1)
*/
template <typename T>
void removeDupFirstWay(std::vector<T> & vec)
{
	std::sort(vec.begin(), vec.end());                    // Time comlexity = O(nlogn), Space complexity = O(1)
	vec.erase(unique(vec.begin(), vec.end()), vec.end()); // Time comlexity = O(n), Space complexity = O(1)
}

/*Second way: unordered_set
Time complexity: O(n) + O(n)-> O(n)
Space complexity: O(n) + O(n) -> O(n)
*/
template <typename T>
void removeDupSecondWay(std::vector<T> & vec)
{
	std::unordered_set<T> s(vec.begin(), vec.end()); // Time comlexity = O(n), Space complexity = O(n)
	vec.assign(s.begin(), s.end());                 // Time comlexity = O(n), Space complexity = O(n)
}

int main()
{
	std::vector<int> vec_int {1, 2, 3, 3, 2, 1, 4, 5, 6};
	std::vector<char> vec_char {'a','b','c','a','d','b', '4','z','D'};

	std::cout << "Vector of int before: ";
	printContainer(vec_int);

	removeDupFirstWay(vec_int);

	std::cout << "Vector of int after: ";
	printContainer(vec_int);


	std::cout << "Vector of char before: ";
	printContainer(vec_char);

	removeDupSecondWay(vec_char);

	std::cout << "Vector of char after: ";
	printContainer(vec_char);

	return 0;
}
