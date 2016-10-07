# ifndef LIST_H
# define LIST_H

# include <cstddef>
# include <iostream>

using namespace std;

template<class T> class ListIterator;

template<class T> class List {
protected:

    struct Node {
        Node * next;
        Node * prev;
        T value;

        Node(T value) {
            this->value = value;
            next = prev = nullptr;
        }
    };

    Node * head;
    Node * tail;
    unsigned length;

private:
    List(const List<T>& l);
    List<T>& operator=(const List&);

public:

    List() {
        head = tail = nullptr;
        length = 0;
    }

    void append(T value) {
        Node * node = new Node(value);
        node->prev = tail;

        if (tail != nullptr)
            tail->next = node;

        tail = node;
        if (head == nullptr) {
            head = node;
        }

        length++;
    }

    void prepend(T value) {
        Node * node = new Node(value);
        node->next = head;

        if (head != nullptr)
            head->prev = node;

        head = node;
        if (tail == nullptr) {
            tail = node;
        }

        length++;
    }

    unsigned size() {
        return length;
    }

    T pop() {
        if (length == 0) throw "List is empty";

        Node * node = tail;
        tail = node->prev;

        length--;
        if (length == 0) head = tail = nullptr;

        T val = node->value;
        delete node;
        return val;
    }

    T shift(){
        if (length == 0) throw "List is empty";
        Node * node = head;
        head = node->next;

        length--;

        if (length == 0) head = tail = nullptr;

        T val = node->value;
        delete node;
        return val;
    }

    bool isEmpty() {
        return length == 0;
    }

    ~List() {
        Node * node = head;
        while (node != nullptr) {
            Node * tmp = node;
            node = node->next;
            delete tmp;
        }
    }

    List<T>& operator<<(T val) {
        append(val);
    }

    friend ListIterator<T>;
};

template <class T> class ListIterator {
    typename List<T>::Node * node;

public:
    ListIterator(List<T> const &list) {
        node = list.head;
    }

    ListIterator(ListIterator<T> const &it) {
        node = it.node;
    }

    operator bool() {
        return node != nullptr;
    }

    ListIterator& operator++() {
        if (node == nullptr) throw "End of list";
        node = node->next;
        return *this;
    }

    ListIterator& operator++(int) {
        if (node == nullptr) throw "End of list";
        node = node->next;
        return *this;
    }

    T& operator*() {
        return node->value;
    }

    T* operator->() {
        return &(node->value);
    }
};

# endif // LIST_H
