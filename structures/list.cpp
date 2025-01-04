#include <iostream>
#include <sstream>
#include <stdio.h>
#include <ctime>
#include "search_result.cpp"
#include "algorithm_utils.cpp"

template <typename T>
struct List
{
private:
    T *array;
    size_t size;
    const double capacity = 0.5;

    void resize()
    {
        if (itemsCount >= size * capacity)
        {
            size *= 2;
            T *arr = new T[size];
            for (size_t i = 0; i < itemsCount; i++)
                arr[i] = array[i];
            delete[] array;
            array = arr;
        }
    }

public:
    size_t itemsCount;
    List()
    {
        srand(time(NULL));
        size = 0;
        array = new T[size];
        itemsCount = 0;
    }

    List(T *array, size_t size) : size(size), itemsCount(size)
    {
        srand(time(NULL));
        this->array = new T[size];
        for (size_t i = 0; i < size; i++)
        {
            this->array[i] = array[i];
        }
    }

    ~List() { delete[] array; }

    T &operator[](size_t index)
    {
        if (index >= itemsCount)
            throw "index range error";
        return array[index];
    }

    void add(T item)
    {
        itemsCount++;
        resize();
        array[itemsCount - 1] = item;
    }

    void add(T *items, size_t n)
    {
        size_t newItemsCount = itemsCount + n;
        T *newArray = new T[newItemsCount];
        for (int i = itemsCount; i < n; i++)
        {
            newArray[i] = items[i - itemsCount];
        }
        delete[] array;
        array = newArray;
        itemsCount = newItemsCount;
    }

    void remove(T item)
    {
        for (size_t i = 0; i < itemsCount; i++)
            if (array[i] == item)
                for (size_t j = i; j < itemsCount - 1; j++)
                    array[j] = array[j + 1];
        itemsCount--;
    }

    bool contains(T item)
    {
        for (size_t i = 0; i < itemsCount; i++)
            if (array[i] == item)
                return true;
        return false;
    }

    bool any(bool (*predicate)(T, T))
    {
        for (int i = 0; i < itemsCount - 1; i++)
            if (predicate(array[i], array[i + 1]))
                return true;
    }

    bool all(bool (*predicate)(T, T))
    {
        for (int i = 0; i < itemsCount - 1; i++)
            if (!predicate(array[i], array[i + 1]))
                return false;
    }

    const T *getArray() const { return array; }

    void forLoop(void (*iteration)(int, T))
    {
        for (size_t i = 0; i < itemsCount; i++)
            iteration(i, array[i]);
    }

    void forEach(void (*iteration)(T))
    {
        for (size_t i = 0; i < itemsCount; i++)
            iteration(array[i]);
    }

    template <typename R>
    List<R> map(R (*mapper)(T))
    {
        R *newArray = new R[itemsCount];
        for (size_t i = 0; i < itemsCount; i++)
            newArray[i] = mapper(array[i]);
        return List<R>{newArray, itemsCount};
    }

    template <typename R>
    List<R> mapIndexed(R (*mapper)(int, T))
    {
        R *newArray = new R[itemsCount];
        for (size_t i = 0; i < itemsCount; i++)
            newArray[i] = mapper(i, array[i]);
        return List<R>{newArray, itemsCount};
    }

    template <typename Acc>
    Acc reduce(Acc initial, Acc (*reducer)(Acc, T))
    {
        Acc result = reducer(initial, array[0]);
        for (size_t i = 1; i < itemsCount; i++)
            result = reducer(result, array[i]);
        return result;
    }

    List<T> filter(bool (*predicate)(T))
    {
        T *newArray = new T[itemsCount];
        size_t count = 0;
        for (int i = 0; i < itemsCount; i++)
            if (predicate(array[i]))
                newArray[count++] = array[i];
        T *newItems = new T[count];
        for (int i = 0; i < count; i++)
            newItems[i] = newArray[i];
        delete[] newArray;
        return List{newItems, count};
    }

    List<T> filterIndexed(bool (*predicate)(int, T))
    {
        T *newArray = new T[itemsCount];
        size_t count = 0;
        for (int i = 0; i < itemsCount; i++)
            if (predicate(i, array[i]))
                newArray[count++] = array[i];
        T *newItems = new T[count];
        for (int i = 0; i < count; i++)
            newItems[i] = newArray[i];
        delete[] newArray;
        return List{newItems, count};
    }

    T findFirst(bool (*searchFunc)(T), T defaultValue)
    {
        for (int i = 0; i < itemsCount; i++)
        {
            if (searchFunc(array[i]))
            {
                return array[i];
            }
        }
        return defaultValue;
    }

    T findLast(bool (*searchFunc)(T))
    {
        for (int i = itemsCount - 1; i >= 0; i--)
            if (searchFunc(array[i]))
                return array[i];
    }

    int indexOf(T item)
    {
        for (int i = 0; i < itemsCount; i++)
        {
            if (array[i] == item)
                return i;
        }
        return -1;
    }

    int lastIndexOf(T item)
    {
        for (int i = itemsCount - 1; i >= 0; i--)
        {
            if (array[i] == item)
                return i;
        }
        return -1;
    }

    SearchResult<T> binarySearch(T target)
    {
        int left = 0, right = itemsCount - 1;
        List<T> list = *this;
        list.bubbleSort();
        int index = algorithm_utils::binarySearchRecurcive(target, list.getArray(), left, right);
        return SearchResult{index, array[index]};
    }

    void bubbleSort()
    {
        for (size_t i = 0; i < itemsCount; i++)
            for (size_t j = 0; j < itemsCount; j++)
                if (array[j] > array[i])
                {
                    T temp = array[i];
                    array[i] = array[j];
                    array[j] = temp;
                }
    }

    void quickSort()
    {
        algorithm_utils::quickSort(0, itemsCount - 1, array);
    }

    void print()
    {
        std::cout << "[";
        for (size_t i = 0; i < itemsCount; i++)
        {
            std::cout << array[i];
            if (i < itemsCount - 1)
                std::cout << ", ";
        }
        std::cout << "]\n";
    }

    std::string toString()
    {
        std::stringstream stream;
        stream << "[";
        for (size_t i = 0; i < itemsCount; i++)
        {
            stream << array[i];
            if (i < itemsCount - 1)
                stream << ", ";
        }
        stream << "]";
        return stream.str();
    }

    List<T> shuffle()
    {
        List<T> result;
        size_t *indices = new size_t[itemsCount];
        for (size_t i = 0; i < itemsCount; ++i)
        {
            indices[i] = i;
        }

        size_t remaining = itemsCount;
        while (remaining > 0)
        {
            size_t randIndex = rand() % remaining;
            result.add(array[indices[randIndex]]);

            for (size_t i = randIndex; i < remaining - 1; ++i)
            {
                indices[i] = indices[i + 1];
            }
            remaining--;
        }

        delete[] indices;
        return result;
    }

    List<T> reversed()
    {
        T *reversedArray = new T[itemsCount];
        for (int i = 0; i < itemsCount; i++)
        {
            reversedArray[i] = array[itemsCount - 1 - i];
        }
        List<T> result(reversedArray, itemsCount);
        return result;
    }
};