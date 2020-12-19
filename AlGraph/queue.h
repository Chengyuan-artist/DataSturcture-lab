//
// Created by 张承元 on 2020/11/19.
//

#include <cstdlib>

#ifndef BINARYTREE_QUEUE_H
#define BINARYTREE_QUEUE_H
#endif //BINARYTREE_QUEUE_H


struct node {
    int data;
    struct node *next;
};

struct Queue {
    struct node *head;
    struct node *tail;

    Queue();

    void push(int);

    void pop();

    int isempty() const;

    int getfront() const;
};


void Queue::push(int data) {
    tail->next = (struct node *) malloc(sizeof(struct node));
    tail->next->data = data;
    tail = tail->next;
    tail->next = nullptr;
}

int Queue::isempty() const {
    if (head->next == nullptr) return 1;
    else return 0;
}

void Queue::pop() {
    struct node *tmp = head->next;
//    if (tmp == nullptr)return;
    head->next = tmp->next;
    if (isempty()) tail = head;
    free(tmp);
}

int Queue::getfront() const {
    if (!isempty())return head->next->data;
    else return -1;
}


Queue::Queue() {
    this->head = (struct node *) malloc(sizeof(struct node));
    this->tail = this->head;
    this->tail->next = nullptr;
}

