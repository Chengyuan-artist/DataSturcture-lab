//
// Created by chengyuan on 11/26/20.
//

#ifndef ADJLIST_HASHTABLE_H
#define ADJLIST_HASHTABLE_H

#endif //ADJLIST_HASHTABLE_H

#include <cstring>

const int SIZE = 11000000;
const int M = 19140327; //9973
struct HashTable {
    struct Node {
        int next = 0, value = 0, key = 0;
    } data[SIZE];
    int head[M] = {0}, size = 0;

    int hash(int key) { return key % M; }

    int get(int key) {
        for (int p = head[hash(key)]; p; p = data[p].next)
            if (data[p].key == key) return data[p].value;
        return -1;
    }

    int modify(int key, int value) {
        for (int p = head[hash(key)]; p; p = data[p].next)
            if (data[p].key == key) return data[p].value = value;
        return -1;
    }

    int add(int key, int value) {
        if (get(key) != -1) return -1;
        // 首插法
        data[++size] = (Node) {head[hash(key)], value, key};
        head[hash(key)] = size;
        return value;
    }

    void clear() {
        memset(data, 0, sizeof(data));
        memset(head, 0, sizeof(head));
        size = 0;
    }

    int remove(int key) {
        int p = head[hash(key)], q = data[p].next;
        if (p == 0)return -1;
        // 特判首结点
        if (data[p].key == key) {
            head[hash(key)] = q;
            return data[p].value;
        }
        while (q) {
            if (data[q].key == key) {
                data[p].next = data[q].next;
                return data[p].value;
            }
            p = q;
            q = data[q].next;
        }
        return -1;
    }
};