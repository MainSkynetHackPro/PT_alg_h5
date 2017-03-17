#include <iostream>
#include <ctype.h>

class CStackList {
public:
    CStackList() : head(0) {}

    ~CStackList() {
        if (this->head != 0) {
            while (this->head->prev != 0) {
                CListNode *prev = head->prev;
                delete prev;
                this->head = prev;
            }
        }
    }

    void push(char value);

    char pop();

    char get_item();

    bool is_empty();

private:
    struct CListNode {
        char value;
        CListNode *prev;

        CListNode(char value, CListNode *prev) : value(value), prev(prev) {};
    };

    CListNode *head;

};

void CStackList::push(char value) {
    this->head = new CListNode(value, head);
}

bool CStackList::is_empty() {
    return (this->head == NULL);
}

char CStackList::get_item() {
    if (this->head == NULL)
        return ' ';
    return this->head->value;
}

char CStackList::pop() {
    if (head == 0)
        return '\0';
    char value = this->head->value;
    CListNode *item = this->head;
    if (this->head->prev == 0) {
        this->head = 0;
    } else {
        this->head = this->head->prev;
    }
    delete item;
    return value;
}

class Anagram {
public:
    Anagram(char *ptrfirst, char *ptrsecond, size_t len) : first(ptrfirst), second(ptrsecond), len(len) {};

    bool solve();

private:
    char *first;
    char *second;
    size_t len;
};

bool Anagram::solve() {
    CStackList stack;

    char *ptr_first = this->first;
    char *ptr_second = this->second;

    while (*ptr_first != '\0') {
        if (*ptr_first == *ptr_second) {
            ptr_second++;
            ptr_first++;
        }
        if (!stack.is_empty() and stack.get_item() == *ptr_second) {
            while (true) {
                if (stack.get_item() == *ptr_second) {
                    stack.pop();
                    ptr_second++;
                } else {
                    break;
                }
            }
        } else {
            if (*ptr_first != *ptr_second) {
                stack.push(*ptr_first);
                ptr_first++;
            }
        }
    }

    return stack.is_empty();
}

int main() {
    size_t len = 1024;
    char *f_word = new char[len];
    char *s_word = new char[len];

    std::cin >> f_word;
    std::cin >> s_word;

    Anagram anagram(f_word, s_word, len);

    if (anagram.solve()) {
        std::cout << "YES";
    } else {
        std::cout << "NO";
    }

    delete[] f_word;
    delete[] s_word;
    return 0;
}