# ifndef LIST_H
# define LIST_H

# include <cstddef>

using namespace std;
 
template<class T> class ListIterator;

// Класс списка
template<class T> class List {
protected:
    
    // Структура для узла
    struct Node {
        Node * next;
        Node * prev;
        T value;

        Node(T value) {
            this->value = value;
            next = prev = nullptr;
        }
    };
    
    // Головной узел
    Node * head;
    // Длина
    unsigned length;

private:
    // Запрет использования
    List(const List<T>& l);
    List<T>& operator=(const List&);

public:

    // Создать пустой список
    List() {
        head = tail = nullptr;
        length = 0;
    }

    // Добавить значение в конец
    void append(T value) {
        Node * node = new Node(value);
        if (length == 0) {
            head = node;
        } else {
            Node * tail = head;
            for (; tail->next != nullptr; tail = tail->next);
            tail->next = node;
        }
        length++;
    }
    
    // Добавить в начало
    void prepend(T value) {
        Node * node = new Node(value);
        node->next = head;
        head = node;
        length++;
    }
    // Размер списка
    unsigned size() {
        return length;
    }
    
    // Удалить с конца и вернуть значение
    T pop() {
        if (length == 0) throw "List is empty";

        Node * node = head;
        if (length == 1) {
            node = head;
            head = nullptr;
        } else {
            Node * tmp = head;
            for (; tmp->next->next != nullptr; tmp = tmp->next);
            node = tmp->next;
            tmp->next = nullptr;
        }
        T val = node->value;
        delete node;
        
        length--;
        
        return val;
    }
    // Удалить из начала и вернуть значение
    T shift(){
        if (length == 0) throw "List is empty";
        Node * node = head;
        head = node->next;

        length--;

        T val = node->value;
        delete node;
        return val;
    }
    // Проверка на пустоту
    bool isEmpty() {
        return length == 0;
    }
    // Деструктор, удаляет узлы списка
    ~List() {
        Node * node = head;
        while (node != nullptr) {
            Node * tmp = node;
            node = node->next;
            delete tmp;
        }
    }

    friend ListIterator<T>;
};

// Итератор по списку
template <class T> class ListIterator {
    typename List<T>::Node * node;

public:
    // Конструктор, принимает итерируемый список
    ListIterator(List<T> const &list) {
        node = list.head;
    }

    // Приведение к bool
    // Если обход окончен - то false, нет - true
    operator bool() {
        return node != nullptr;
    }

    // Сдвинуть итератор на один элемент
    ListIterator& operator++() {
        if (node == nullptr) throw "End of list";
        node = node->next;
        return *this;
    }

    // Сдвинуть итератор на один элемент (постфикснаяя форма)
    ListIterator& operator++(int) {
        if (node == nullptr) throw "End of list";
        node = node->next;
        return *this;
    }

    // Получить значение текущего узла
    T& operator*() {
        return node->value;
    }

    // Получить доступ к членам хранимогобъекта
    T* operator->() {
        return &(node->value);
    }
};

# endif // LIST_H
