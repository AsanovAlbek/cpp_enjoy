#include <iostream>

namespace algorithm_utils
{
    template <typename T>
    int partition(int, int, T*);
    
    template <typename T>
    int binarySearchRecurcive(T target, T *arr, int left, int right)
    {
        if (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (arr[mid] == target)
            {
                return mid;
            }
            else if (arr[mid] > target)
            {
                return binarySearchRecurcive(target, arr, left, mid - 1);
            }
            else
            {
                return binarySearchRecurcive(target, arr, mid + 1, right);
            }
        }
        return -1;
    }

    template <typename T>
    void quickSort(int low, int high, T *array)
    {
        if (low < high)
        {
            int pivotIndex = partition(low, high, array);
            quickSort(low, pivotIndex - 1, array);
            quickSort(pivotIndex + 1, high, array);
        }
    }

    template <typename T>
    int partition(int low, int high, T *array)
    {
        T pivot = array[high];
        int i = low - 1;
        for (int j = low; j < high; j++)
        {
            if (array[j] < pivot)
            {
                i++;
                std::swap(array[i], array[j]);
            }
        }
        std::swap(array[i + 1], array[high]);
        return i + 1;
    }
}