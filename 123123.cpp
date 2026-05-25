#include <iostream>
#include <vector>

struct Spisok {
    int value;
    Spisok *next;
    Spisok *prev;
};

void printSpisok(Spisok *current) {
    while (current != NULL) {
        std::cout << current->value << " ";
        current = current->next;
    }
}

int main() {
    Spisok *tail = NULL;
    Spisok *head = NULL;
    for (int i = 0; i < 5; i++) {
        Spisok *node = new Spisok;
        node->value = i;
        node->next = NULL;
        node->prev = node;

        if (head = NULL) {
            head = node;
        } else {
            tail->next = node;
        }

        tail = node;
    }
    printSpisok(head);
    
    return 0;
}
