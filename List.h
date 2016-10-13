# ifndef LIST_H
# define LIST_H

// For nulllptr using
# include <cstddef>

using namespace std;
 
template<class T> class ListIterator;

// Main list class
// Incapsulate realisation of list operations
template<class T> class List {
protected:
    
    // Struct - node of list
    // It use only in this class
    struct Node {
        Node * next;
        Node * prev;
        T value;

        // Constructor of list node
        // For fast node initialisation
        Node(T value) {
            this->value = value;
            next = prev = nullptr;
        }
    };
    
    // Head node of list
    // If list is empty this field have nullptr value
    Node * head;
    // Length of list
    unsigned length;

private:
    // Forbid copy constructor and asigment operator
    List(const List<T>& l);
    List<T>& operator=(const List&);

public:

    // Create empty list
    List() {
        head = tail = nullptr;
        length = 0;
    }

    // Add value to list tail
    void append(T value) {
        Node * node = new Node(value);
        // If list is empty
        if (length == 0) {
            // Assign this node head field
            head = node;
        } else {
            // If list isn't empty
            // Search list tail
            Node * tail = head;
            for (; tail->next != nullptr; tail = tail->next);
            // And add node after tail
            tail->next = node;
        }
        // Don't forget about length field
        length++;
    }
    
    // Add value to top of list
    void prepend(T value) {
        Node * node = new Node(value);
        node->next = head;
        head = node;
        length++;
    }
    // Size of list
    unsigned size() {
        return length;
    }
    
    // Remove node from bottom of list
    // And return value of this node
    T pop() {
        if (length == 0) throw "List is empty";

        Node * node = head;
        // if length of list is 1
        if (length == 1) {
            // node that we should remove is list head
            node = head;
            head = nullptr;
        } else {
            // else we should find node find node that prepend tail node
            Node * tmp = head;
            for (; tmp->next->next != nullptr; tmp = tmp->next);
            // Assign tail node to node variable
            node = tmp->next;
            // And assign nullptr value to `next` field of new tail
            tmp->next = nullptr;
        }
        // Get node value
        T val = node->value;
        // And delete node
        delete node;
        
        length--;
        
        return val;
    }
    // Remove first node and return value
    T shift(){
        if (length == 0) throw "List is empty";
        Node * node = head;
        head = node->next;

        length--;

        T val = node->value;
        delete node;
        return val;
    }
    // Check for list empty
    bool isEmpty() {
        return length == 0;
    }
    // Destructor, remove all nodes
    ~List() {
        Node * node = head;
        while (node != nullptr) {
            Node * tmp = node;
            node = node->next;
            delete tmp;
        }
    }

    // iterator is friend of this class
    friend ListIterator<T>;
};

// Class of list iterator
template <class T> class ListIterator {
    typename List<T>::Node * node;

public:
    // Constructor
    // Make iterator for list
    // That shlould passed as param
    ListIterator(List<T> const &list) {
        node = list.head;
    }
    
    // Create iterator from other iterator
    ListIterator(ListIterator<T> const &it) {
        node = it.node;
    }

    // Cast operator to bool
    // Return false if iterator reached the end of list
    operator bool() {
        return node != nullptr;
    }

    // Increment opertor (postfix form)
    // Move iterator to next node
    ListIterator& operator++() {
        if (node == nullptr) throw "End of list";
        node = node->next;
        return *this;
    }

    // Increment opertor (prefix form)
    // Move iterator to next node
    ListIterator& operator++(int) {
        if (node == nullptr) throw "End of list";
        node = node->next;
        return *this;
    }

    // Get value of current node
    T& operator*() {
        return node->value;
    }

    // Give access to members of the stored object
    T* operator->() {
        return &(node->value);
    }
};

# endif // LIST_H
