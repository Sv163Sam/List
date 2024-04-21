#include <iostream>
#include <memory>
#include <vector>

template <typename T>
class LinkedList{
private:
    struct Node {
        T data;
        std::unique_ptr<Node> next;
        explicit Node(const T& data) : data(data), next(nullptr) {}
    };
    std::unique_ptr<Node> head;
    Node* tail;

public:
    LinkedList() : head(nullptr), tail(nullptr) {}

    void push_front(const T& data)
    {
        auto newNode = std::make_unique<Node>(data);
        newNode->next = std::move(head);
        head = std::move(newNode);
        if (!tail)
            tail = head.get();
    }

    void push_back(const T& data)
    {
        auto newNode = std::make_unique<Node>(data);
        if (tail)
        {
            tail->next = std::move(newNode);
            tail = tail->next.get();
        }
        else
        {
            head = std::move(newNode);
            tail = head.get();
        }
    }

    void insert(int index, const T& data)
    {
        if (index == 0)
        {
            push_front(data);
            return;
        }

        auto current = head.get();
        int currentIndex = 0;

        while (current && currentIndex < index - 1)
        {
            current = current->next.get();
            currentIndex++;
        }

        if (current)
        {
            auto newNode = std::make_unique<Node>(data);
            newNode->next = std::move(current->next);
            current->next = std::move(newNode);
            if (!newNode->next)
                tail = newNode.get();
        }
        else
        {
            throw std::out_of_range("Index out of range");
        }
    }

    void pop_front()
    {
        if (head)
        {
            head = std::move(head->next);
            if (!head)
                tail = nullptr;
        }
    }

    void pop_back()
    {
        if (head)
        {
            if (head.get() == tail)
            {
                head = nullptr;
                tail = nullptr;
            }
            else
            {
                auto current = head.get();
                while (current->next.get() != tail)
                    current = current->next.get();

                current->next = nullptr;
                tail = current;
            }
        }
    }

    void remove(const T& data)
    {
        if (!head)
            return;

        auto current = head.get();
        Node* previous = nullptr;

        while (current && current->data != data)
        {
            previous = current;
            current = current->next.get();
        }

        if (current)
        {
            if (previous)
            {
                previous->next = std::move(current->next);
                if (!previous->next)
                    tail = previous;
            }
            else
            {
                head = std::move(current->next);
                if (!head)
                    tail = nullptr;
            }
        }
    }

    void removeAll(const T& data)
    {
        if (!head)
            return;

        while (head && head->data == data)
            head = std::move(head->next);

        auto current = head.get();
        while (current->next)
        {
            if (current->next->data == data)
            {
                current->next = std::move(current->next->next);
            }
            else
                current = current->next.get();
        }

        if (current->data == data)
        {
            tail = current;
            tail->next = nullptr;
        }
        else
            tail = current;
    }

    std::vector<int> findAll(const T& data)
    {
        std::vector<int> indices;
        if (!head)
            return indices;

        auto current = head.get();
        int currentIndex = 0;

        while (current)
        {
            if (current->data == data)
                indices.push_back(currentIndex);

            current = current->next.get();
            currentIndex++;
        }
        return indices;
    }

    Node* find(const T& data)
    {
        if (!head)
            return nullptr;

        auto current = head.get();

        while (current)
        {
            if (current->data == data)
                return current;

            current = current->next.get();
        }
        return nullptr;
    }

    bool empty() const
    {
        return head == nullptr;
    }

    void print() const
    {
        if (!head)
            return;

        auto current = head.get();
        while (current)
        {
            std::cout << current->data << " ";
            current = current->next.get();
        }
        std::cout << std::endl;
    }
};

