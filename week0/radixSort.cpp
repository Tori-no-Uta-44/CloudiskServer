//
// Created by 李勃鋆 on 24-9-8.
//
#include "../week01.h"

// 基数排序
void radixSort(std::vector<int> &arr) {
	// 找到数组中的最大值，确定最大位数
	int maxNum = *std::max_element(arr.begin(), arr.end());

	// 从个位开始，对每一位进行计数排序
	for (int exp = 1; maxNum / exp > 0; exp *= 10) {
		int n = arr.size();
		std::vector<int> output(n); // 输出数组
		int count[10] = {0}; // 存储每个位的计数（基数为10）

		// 统计对应位出现的次数
		for (int i = 0; i < n; i++) {
			int index = (arr[i] / exp) % 10;
			count[index]++;
		}

		// 累加计数以确定元素在输出数组中的位置
		for (int i = 1; i < 10; i++) {
			count[i] += count[i - 1];
		}

		// 反向遍历原数组，按当前位的计数排序
		for (int i = n - 1; i >= 0; i--) {
			int index = (arr[i] / exp) % 10;
			output[count[index] - 1] = arr[i];
			count[index]--;
		}

		// 将排序好的结果复制回原数组
		for (int i = 0; i < n; i++) {
			arr[i] = output[i];
		}
	}
}

int radixSort_test() {
	std::vector<int> arr = {170, 45, 75, 90, 802, 24, 2, 66};
	radixSort(arr);

	std::cout << "排序后的数组: ";
	for (int num : arr) {
		std::cout << num << " ";
	}
	return 0;
}
