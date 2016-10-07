# include <iostream>
# include "List.h"
# include <string>

int main(int argc, char** argv) {

    List<int> l;
    l.append(100);
    l.prepend(23);
    l << 223;
    std::cout << l.pop() << l.shift() << endl << endl;

    for (int i = 0; i < 10; i++) {
        if (i % 2) {
            l.prepend(i * i);
        } else {
            l.append(i * i  * i);
        }
    }

    ListIterator<int> it(l);
    while (it) {
        std::cout << *it << endl;
        it++;
    }

    List<std::string> ls;
    ls << "Hello";

    ListIterator<std::string> its(ls);

    std::cout << *its << " ";
    std::cout << its->append(" world!") << endl;

    return 0;
}
