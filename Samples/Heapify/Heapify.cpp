#include "Heapify.h"
#include <algorithm>

using namespace std;

std::vector<int> extract(Heap<int>& heap)
{
	std::vector<int> out;
	while (!heap.empty())
		out.push_back(heap.pop());

	return out;
}

template <typename Container>
void printAll(const Container &container)
{
	for (auto value : container)
		cout << value << " ";
	cout << endl;
}

int main()
{
	std::vector<int> testData{ 8, 9, 3, 4, 33, 2};
	//std::vector<int> testData{ 8, 9, 10 };
	Heap<int> heap;
	for (auto value : testData)
	{
		heap.push(value);
		cout << "Size: " << heap.size() << " First Leaf Index: " << Heapify<>::firstLeafIndex(heap.size()) << endl;
	}

	auto out = extract(heap);

	auto sortedCopy = testData;
	std::sort(sortedCopy.begin(), sortedCopy.end());
	cout << "Heap extracting is " << ((out == sortedCopy)? "Ok": "Failed") << endl;

	heap = testData;
	out = extract(heap);
	cout << "Heap extracting after heapify is " << ((out == sortedCopy) ? "Ok" : "Failed") << endl;

	out = testData;
	Heapify<>::sort(out);
	cout << "Heap array:";
	printAll(out);

	cout << "Heap take after sort is " << ((out == sortedCopy) ? "Ok" : "Failed") << endl;

	Heap<int> largest;
	for (auto value : testData)
	{
		kLargestPush<3>(largest, value);
	}

	out = extract(largest);
	cout << "3 Largest:";
	printAll(out);

	return 0;
}
