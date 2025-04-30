#pragma once

enum NodeType { START, TURNING, OBJECT_DETECTED, REGULAR };

struct Node {
    int x;
    int y;
    NodeType node_type;
    Node* prev;
    Node* next;

    Node(int x, int y, NodeType type) 
        : x(x), y(y), node_type(type), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;
    int size;
    const int CAPACITY = 10;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}
    
    ~DoublyLinkedList() {
        Node* current = head;
        while(current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    void insert(int x, int y, NodeType type) {
        if(size >= CAPACITY) return;
        
        Node* newNode = new Node(x, y, type);
        if(!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }

    void removeRegularNodes(Node* start, Node* end) {
        Node* current = start->next;
        while(current && current != end) {
            if(current->node_type == REGULAR) {
                Node* temp = current;
                current->prev->next = current->next;
                if(current->next) current->next->prev = current->prev;
                current = current->next;
                delete temp;
                size--;
            } else {
                current = current->next;
            }
        }
    }

    void printNodes() {
        Node* current = head;
        while(current) {
            Brain.Screen.print("Node(%d,%d) Type:%d", current->x, current->y, current->node_type);
            current = current->next;
        }
    }
};
