#pragma once
#include <iostream>
#include <stdexcept>

using namespace std;

template<typename T>
class List
{
private:
    class Node
    {
    private:
        T data;
        Node* next, * prev;
    public:
        Node() : next(NULL), prev(NULL) {};
        Node(T data) {
            this->data = data;
            next = NULL;
            prev = NULL;
        }
        ~Node() {
            next = NULL;
            prev = NULL;
        }
        void set_data(T data) {
            this->data = data;
        }
        T get_data() {
            return data;
        }
        Node* get_next() {
            return next;
        }
        Node* get_prev() {
            return prev;
        }
        void set_next(Node* pointer) {
            next = pointer;
        }
        void set_prev(Node* pointer) {
            prev = pointer;
        }
    };
    Node* head, * tail;
    Node* get_pointer(size_t index)
    {
        if (isEmpty() || (index > get_size() - 1))
        {
            throw out_of_range("Invalid argument");
        }
        else if (index == get_size() - 1)
            return tail;
        else if (index == 0)
            return head;
        else
        {
            Node* temp = head;
            while ((temp) && (index--))
            {
                temp = temp->get_next();
            }
            return temp;
        }
    }
public:
    List() : head(NULL), tail(NULL) {}
    List(const List<T>& list) {
        clear();
        Node* temp = list.head;
        while (temp) {
            push_back(temp->get_data());
            temp = temp->get_next();
        }
    }
    ~List()
    {
        while (head)
        {
            tail = head->get_next();
            delete head;
            head = tail;
        }
        head = NULL;
    }
    void push_back(T data)
    {
        Node* temp = new Node;
        temp->set_data(data);
        if (head)
        {
            temp->set_prev(tail);
            tail->set_next(temp);
            tail = temp;
        }
        else
        {
            head = temp;
            tail = head;
        }
    }
    void push_front(T data)
    {
        Node* temp = new Node;
        temp->set_data(data);
        if (head)
        {
            temp->set_next(head);
            head->set_prev(temp);
            head = temp;
        }
        else
        {
            head = temp;
            tail = head;
        }
    }
    void push_front(List& ls2)
    {
        Node* temp = ls2.tail;
        size_t n = ls2.get_size();
        while ((temp) && (n--))
        {
            push_front(temp->get_data());
            temp = temp->get_prev();
        }
    }
    void pop_back()
    {
        if (head != tail)
        {
            Node* temp = tail;
            tail = tail->get_prev();
            tail->set_next(NULL);
            delete temp;
        }
        else if (!isEmpty())
        {
            Node* temp = tail;
            tail = head = NULL;
            delete temp;
        }
        else
            throw out_of_range("The list is empty");
    }
    void pop_front()
    {
        if (head != tail)
        {
            Node* temp = head;
            head = head->get_next();
            head->set_prev(NULL);
            delete temp;
        }
        else if (!isEmpty())
        {
            Node* temp = head;
            head = tail = NULL;
            delete temp;
        }
        else
            throw out_of_range("The list is empty");
    }
    void insert(size_t index, T data)
    {
        Node* temp;
        temp = get_pointer(index);
        if (temp == head)
            push_front(data);
        else
        {
            Node* newElem = new Node;
            newElem->set_data(data);
            temp->get_prev()->set_next(newElem);
            newElem->set_prev(temp->get_prev());
            newElem->set_next(temp);
            temp->set_prev(newElem);
        }
    }
    T at(size_t index)
    {
        Node* temp;
        temp = get_pointer(index);
        return temp->get_data();
    }
    void remove(size_t index)
    {
        Node* temp;
        temp = get_pointer(index);
        if (temp == head)
            pop_front();
        else if (temp == tail)
            pop_back();
        else
        {
            temp->get_prev()->set_next(temp->get_next());
            temp->get_next()->set_prev(temp->get_prev());
            delete temp;
        }
    }
    void remove(T data) {
        Node* temp = head;
        while (temp && temp->get_data() != data)
            temp = temp->get_next();
        if (!temp)
            throw out_of_range("Invalid argument");
        if (temp == head)
            pop_front();
        else if (temp == tail)
            pop_back();
        else
        {
            temp->get_prev()->set_next(temp->get_next());
            temp->get_next()->set_prev(temp->get_prev());
            delete temp;
        }
    }
    size_t get_size()
    {
        Node* temp = head;
        size_t length = 0;
        while (temp)
        {
            length++;
            temp = temp->get_next();
        }
        return length;
    }
    void print_to_console()
    {
        Node* temp = head;
        while (temp)
        {
            cout << temp->get_data() << ' ';
            temp = temp->get_next();
        }
        cout << endl;
    }
    void clear()
    {
        while (head)
        {
            tail = head->get_next();
            delete head;
            head = tail;
        }
    }
    void set(size_t index, T data)
    {
        Node* temp;
        temp = get_pointer(index);
        temp->set_data(data);
    }
    bool isEmpty()
    {
        if (!head)
            return true;
        else
            return false;
    }
};