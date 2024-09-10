//
// Created by 李勃鋆 on 24-9-4.
//
#include "../week01.h"

void countingSort(std::vector<int> &arr) {
	if (arr.empty())
		return;

	// 找到数组中的最大值和最小值
	int maxVal = *std::max_element(arr.begin(), arr.end());
	int minVal = *std::min_element(arr.begin(), arr.end());

	// 创建计数数组
	int range = maxVal - minVal + 1;
	std::vector<int> count(range, 0);

	// 统计每个元素的出现次数
	for (int num : arr) {
		count[num - minVal]++;
	}

	// 累加计数数组
	for (int i = 1; i < range; i++) {
		count[i] += count[i - 1];
	}

	// 创建输出数组
	std::vector<int> output(arr.size());
	for (int i = arr.size() - 1; i >= 0; i--) {
		output[count[arr[i] - minVal] - 1] = arr[i];
		count[arr[i] - minVal]--;
	}

	// 将排序后的结果复制回原数组
	for (int i = 0; i < arr.size(); i++) {
		arr[i] = output[i];
	}
}

int countingSort_test() {
	std::vector<int> arr = {4, 2, 2, 8, 3, 3, 1};

	std::cout << "排序前: ";
	for (int num : arr) {
		std::cout << num << " ";
	}
	std::cout << std::endl;

	countingSort(arr);

	std::cout << "排序后: ";
	for (int num : arr) {
		std::cout << num << " ";
	}
	std::cout << std::endl;

	return 0;
}
