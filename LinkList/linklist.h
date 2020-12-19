//
// Created by 张承元 on 2020/10/23.
//

#ifndef LINEARLIST_LINK__LINKLIST_H
#define LINEARLIST_LINK__LINKLIST_H

#endif //LINEARLIST_LINK__LINKLIST_H

#include <cstdio>
#include <cstdlib>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int status;
typedef int ElemType; //数据元素类型定义

typedef int ElemType;
typedef struct LNode {  //单链表（链式结构）结点的定义
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;


status InitList(LinkList &L);

status DestroyList(LinkList &L);

status ClearList(LinkList &L);

status ListEmpty(LinkList L);

int ListLength(LinkList L);

status GetElem(LinkList L, int i, ElemType &e);

status LocateElem(LinkList L, ElemType e);

status PriorElem(LinkList L, ElemType e, ElemType &pre);

status NextElem(LinkList L, ElemType e, ElemType &next);

status ListInsert(LinkList &L, int i, ElemType e);

status ListDelete(LinkList &L, int i, ElemType &e);

status ListTraverse(LinkList L);

status SaveList(LinkList L, char FileName[]);

status LoadList(LinkList &L, char FileName[]);

LNode *merge_sort(LNode *);

LNode *merge_list(LNode *p, LNode *q);

status MergeSortList(LinkList L);

status ReverseList(LinkList L);

status LoopList(LinkList L, int k);


status InitList(LinkList &L) {
    if (L == nullptr) {
        L = (LNode *) malloc(sizeof(LNode));
        L->next = nullptr;
        return OK;
    } else return INFEASIBLE;
}

status DestroyList(LinkList &L) {
    if (L != nullptr) {
        LNode *p = L->next;
        while (L != nullptr) {
            free(L);
            L = p;
            if (L != nullptr)p = L->next;
        }
        return OK;
    } else {
        return INFEASIBLE;
    }
}

status ClearList(LinkList &L) {
    if (L != nullptr) {
        LNode *head, *tail = nullptr;
        head = L->next;
        if (head != nullptr)tail = head->next;
        while (tail != nullptr) {
            free(head);
            head = tail;
            tail = head->next;
        }
        L->next = nullptr;
        return OK;
    } else {
        return INFEASIBLE;
    }
}

status ListEmpty(LinkList L) {
    if (L == nullptr)return INFEASIBLE;
    if (L->next == nullptr)return TRUE;
    else return FALSE;
}

int ListLength(LinkList L) {
    if (L == nullptr)return INFEASIBLE;
    LNode *p = L->next;
    int len = 0;
    while (p != nullptr) {
        p = p->next;
        len++;
    }
    return len;
}

status GetElem(LinkList L, int i, ElemType &e) {
    if (L == nullptr)return INFEASIBLE;
    if (i < 1)return ERROR;
    LNode *p = L;
    for (int k = 0; k < i; ++k) {
        p = p->next;
        if (p == nullptr)return ERROR;
    }
    e = p->data;
    return OK;
}

status LocateElem(LinkList L, ElemType e) {
    if (L == nullptr)return INFEASIBLE;
    int i = 0;
    LNode *p = L;
    while (p->next != nullptr) {
        p = p->next;
        i++;
        if (p->data == e) {
            return i;
        }
    }
    return ERROR;
}

status PriorElem(LinkList L, ElemType e, ElemType &pre) {
    if (L == nullptr)return INFEASIBLE;
    int i = 0;
    LNode *p = L;
    LNode *pre_node;
    while (p->next != nullptr) {
        pre_node = p;
        p = p->next;
        i++;
        if (p->data == e) {
            //找到了e
            if (i == 1)return ERROR;
            pre = pre_node->data;
            return OK;
        }
    }
    //e不在表中
    return ERROR;
}

status NextElem(LinkList L, ElemType e, ElemType &next) {
    if (L == nullptr)return INFEASIBLE;
    int i = 0;
    LNode *p = L;
    while (p->next != nullptr) {
        p = p->next;
        i++;
        if (p->data == e) {
            //找到了e
            if (p->next != nullptr) {
                //后继存在
                next = p->next->data;
                return OK;
            }
        }
    }
    //e不在表中或后继不存在
    return ERROR;

}

status ListInsert(LinkList &L, int i, ElemType e) {
    if (L == nullptr)return INFEASIBLE;
    if (i < 1)return ERROR;
    LNode *p, *pre_node;
    p = L;
    pre_node = L;
    for (int k = 0; k < i; ++k) {
        //循环i次
        pre_node = p;
        p = p->next;
        if (p == nullptr && k != i - 1)return ERROR;//插入位置不正确
        //k ==i-1 特判允许在最末尾处插入
    }
    //
    pre_node->next = (LNode *) malloc(sizeof(LNode));
    pre_node->next->data = e;
    pre_node->next->next = p;
    return OK;
}

status ListDelete(LinkList &L, int i, ElemType &e) {
    if (L == nullptr)return INFEASIBLE;
    if (i < 1)return ERROR;
    LNode *p, *pre_node;
    p = L;
    pre_node = L;
    for (int k = 0; k < i; ++k) {
        //循环i次
        pre_node = p;
        p = p->next;
        if (p == nullptr)return ERROR;//删除位置不正确
    }
    //
    pre_node->next = p->next;
    e = p->data;
    free(p);
    return OK;
}

status ListTraverse(LinkList L) {
    if (L == nullptr)return INFEASIBLE;
    LNode *p = L;
    while (p->next != nullptr) {
        printf("%d ", p->next->data);
        p = p->next;
    }
    printf("\n");
    return OK;
}

status SaveList(LinkList L, char *FileName) {
    if (L == nullptr)return INFEASIBLE;
    FILE *out = fopen(FileName, "w");
    LNode *p = L;
    while (p->next != nullptr) {
        fprintf(out, "%d ", p->next->data);
        p = p->next;
    }
    fclose(out);
    return OK;
}

status LoadList(LinkList &L, char *FileName) {
    if (L != nullptr)return INFEASIBLE;
    L = (LNode *) malloc(sizeof(LNode));
    FILE *in = fopen(FileName, "r");
    LNode *tail, *pre_tail;
    pre_tail = L;
    tail = nullptr;
    ElemType e;
    while (fscanf(in, "%d", &e) != EOF) {
        tail = (LNode *) malloc(sizeof(LNode));
        tail->data = e;
        pre_tail->next = tail;
        pre_tail = pre_tail->next;
        tail = nullptr;
    }
    pre_tail->next = tail;
    return OK;
}

LNode *merge_list(LNode *p, LNode *q) {
    LNode *h = (LNode *) malloc(sizeof(LNode));
    LNode *tail = h;
    while (p != nullptr && q != nullptr) {
        if (p->data <= q->data) {
            tail->next = p;
            p = p->next;
            tail = tail->next;
        } else {
            tail->next = q;
            q = q->next;
            tail = tail->next;
        }
    }
    tail->next = p != nullptr ? p : q;
    return h->next;
}

LNode *merge_sort(LNode *head) {
    //head points to linklist without head node
    if (head == nullptr || head->next == nullptr)return head;

    //slow and fast ptr method
    LNode *slow = head, *fast = head->next;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    //cut down the linklist
    LNode *mid = slow->next;
    slow->next = nullptr;

    LNode *left = merge_sort(head);
    LNode *right = merge_sort(mid);

    //merge two linklists
    return merge_list(left, right);
}

status MergeSortList(LinkList L) {
    if (L == nullptr)return INFEASIBLE;
    L->next = merge_sort(L->next);
    return OK;
}

status ReverseList(LinkList L) {
    if (L == nullptr)return INFEASIBLE;
    if (ListLength(L) <= 1)return OK;
    LNode *pre_e = nullptr,
            *e = L->next,
            *next_e = e->next;
    while (e != nullptr) {
        e->next = pre_e;
        pre_e = e;
        e = next_e;
        if (e != nullptr)next_e = e->next;
    }
    L->next = pre_e;
    return OK;
}

status LoopList(LinkList L, int k) {
    if (L == nullptr)return INFEASIBLE;
    LNode *tail = L;
    int len = 0;
    while (tail->next != nullptr) {
        tail = tail->next;
        len++;
    }
    if (len == 0)return OK;
    //op success by default
    while (k < 0)k += len;
    int cnt = len - (k % len);
    //link the list to a loop
    tail->next = L->next;
    LNode *q = L->next, *p = tail;
    //p is q's prior node
    for (int i = 0; i < cnt; ++i) {
        p = q;
        q = q->next;
    }
    L->next = q;
    p->next = nullptr;
    return OK;
}









