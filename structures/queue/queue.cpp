#include <iostream>
#include<optional>

template <typename T>
struct QueueNode
{
    std::optional<T> value;
    QueueNode<T> *next;
};

template <typename T>
struct Queue
{
    QueueNode<T> *head;
    QueueNode<T> *tail;
    size_t size = 0;

    Queue() : head(nullptr), tail(nullptr) {}
    template <size_t N>
    Queue(const T (&elements)[N]) : head(nullptr), tail(nullptr)
    {
        for (size_t i = 0; i < N; i++)
        {
            add(elements[i]);
        }
    }

    ~Queue()
    {
        while (head != nullptr)
        {
            QueueNode<T> *temp = head;
            head = head->next;
            delete temp;
        }
    }

    void add(T element)
    {
        QueueNode<T> *newNode = new QueueNode<T>{element, nullptr};
        if (tail == nullptr)
        {
            head = tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    template<size_t N>
    void addAll(const T (&elements)[N])
    {
        for (size_t i = 0; i < N; i++)
        {
            add(elements[i]);
        }
    }

    std::optional<T> offer()
    {
        if (head == nullptr)
            return std::nullopt;
        QueueNode<T> *temp = head;
        head = head->next;
        if (head == nullptr)
            tail = nullptr;
        std::optional<T> firstValue = temp->value;
        delete temp;
        size--;
        return firstValue;
    }

    std::optional<T> peek()
    {
        if (head == nullptr)
            return std::nullopt;
        return head->value;
    }

    bool isEmpty()
    {
        return head == nullptr;
    }

    void forEach(void (*iteration)(std::optional<T>))
    {
        if (head == nullptr)
            return;
        for (QueueNode<T> *current = head; current != nullptr; current = current->next)
        {
            iteration(current->value);
        }
    }

    void print()
    {
        if (head == nullptr)
            return;
        std::cout << "[";

        for (QueueNode<T> *current = head; current != nullptr; current = current->next)
        {

            if (current != head)
                std::cout << ", ";
            std::cout << (current->value.has_value() ? current->value.value() : "nullopt");
        }
        std::cout << "]\n";
    }

    void clear()
    {
        while (head != nullptr)
        {
            QueueNode<T> *temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        size = 0;
    }
};
