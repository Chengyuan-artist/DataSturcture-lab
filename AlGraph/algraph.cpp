//
// Created by chengyuan on 11/24/20.
//
#include "algraph.h"
#include "queue.h"
#include "hashtable.h"

#define MAXN 1000

// key -> index
//int getindex[MAXN];

// key -> index

//#define HASH

#ifdef HASH
HashTable hashTable;
#endif

int visited[MAX_VERTEX_NUM];

status CreateGraph(ALGraph &G, VertexType V[], KeyType VR[][2]) {


    if (G.vexnum != 0)return ERROR;
    //judge by -1
    G.kind = UDG; // 创建无向图
    G.arcnum = 0;

    // 插入顶点
    for (int i = 0; V[i].key != -1; ++i) {
        if (!InsertVex(G, V[i])) {// 插入顶点失败(key repeats)
            G.vexnum = 0;
            return ERROR;
        }
    }

    // 插入边
    for (int i = 0; VR[i][0] != -1; ++i) {
        if (VR[i][0] - VR[i][1] == 0)continue; // 不允许单边弧
        if (!InsertArc(G, VR[i][0], VR[i][1])) {// 插入边失败
            DestroyGraph(G);
            return ERROR;
        }
    }

    return OK;


}


status DestroyGraph(ALGraph &G) {
    // 请在这里补充代码，完成本关任务

    if (G.vexnum == 0)return ERROR;
    for (int i = 0; i < G.vexnum; ++i) {
        destroyArcs(G.vertices[i].firstarc);
    }
    G.vexnum = G.arcnum = 0;
#ifdef HASH
    hashTable.clear();
#endif
    return OK;

}

void destroyArcs(ArcNode *&first) {

    while (first != nullptr) {
        ArcNode *tmp = first->nextarc;
        free(first);
        first = tmp;
    }
}

int LocateVex(ALGraph G, KeyType u) {

#ifndef HASH
    for (int i = 0; i < G.vexnum; ++i) {
        if (G.vertices[i].data.key == u) {
            return i;
        }
    }
    return -1;
#endif

#ifdef HASH
    return hashTable.get(u);
#endif

}


status PutVex(ALGraph &G, KeyType u, VertexType value) {

    int index = LocateVex(G, u); //O(1)
    if (index == -1)return ERROR;
#ifndef HASH
    // working around
    for (int i = 0; i < G.vexnum; ++i) {
        if (i == index)continue;
        if (G.vertices[i].data.key == value.key) {
            // key repeats!
            return ERROR;
        }
    }

    G.vertices[index].data = value;
    return OK;
#endif

#ifdef HASH
    // 假删除
    hashTable.modify(u, -1);
    if (hashTable.get(value.key) != -1) { // O(1)
        hashTable.modify(u, index);
        return ERROR;
    }
    hashTable.remove(u);
    hashTable.add(value.key, index);

    G.vertices[index].data = value;

    return OK;
#endif
}

int FirstAdjVex(ALGraph G, KeyType u) {

    int index = LocateVex(G, u);
    if (index == -1)return -1;
    if (G.vertices[index].firstarc != nullptr)
        return G.vertices[index].firstarc->adjvex;
    else return -1;
}

int NextAdjVex(ALGraph G, KeyType v, KeyType w) {

    int index = LocateVex(G, v);
    if (index == -1)return -1;
    ArcNode *p = G.vertices[index].firstarc;
    while (p != nullptr) {
        if (G.vertices[p->adjvex].data.key == w) {
            if (p->nextarc != nullptr) {
                return p->nextarc->adjvex;
            } else {
                return -1;
            }
        }
        p = p->nextarc;
    }
    return -1;


}

status InsertVex(ALGraph &G, VertexType v) {

    if (G.vexnum >= MAX_VERTEX_NUM) return ERROR;
    int index = LocateVex(G, v.key);
    if (index != -1)return ERROR;
#ifdef HASH
    hashTable.add(v.key, G.vexnum);
#endif
    G.vertices[G.vexnum].data = v;
    G.vertices[G.vexnum].firstarc = nullptr;
    G.vexnum++;
    return OK;


}

status DeleteVex(ALGraph &G, KeyType v) {

    int index = LocateVex(G, v);
    if (index == -1)return -1;

    destroyArcs(G.vertices[index].firstarc);

    // index+1及其后的元素前移一位
    for (int i = index + 1; i < G.vexnum; ++i) {
        G.vertices[i - 1] = G.vertices[i];
#ifdef HASH
        hashTable.modify(G.vertices[i - 1].data.key, i - 1);
#endif
    }
    G.vexnum--;

    // 更新各链表的值
    for (int i = 0; i < G.vexnum; ++i) {
        maintainArcs(G.vertices[i].firstarc, index);
    }

    if (G.vexnum == 0)return ERROR;
    return OK;

}

void maintainArcs(ArcNode *&first, int index) {
    ArcNode *head = (ArcNode *) malloc(sizeof(ArcNode));
    head->nextarc = first;
    ArcNode *p = head, *q = p->nextarc;
    // p 为 q 前驱
    while (q != nullptr) {
        if (q->adjvex == index) {
            p->nextarc = q->nextarc;
            free(q);
            q = p->nextarc;
        } else {
            if (q->adjvex > index)q->adjvex--;
            p = q;
            q = p->nextarc;
        }
    }
    first = head->nextarc;
}


int insertSinArc(ALGraph &G, int v_i, int w_i) {
    ArcNode *v_p = G.vertices[v_i].firstarc;
    while (v_p != nullptr) {
        if (v_p->adjvex == w_i)return OK; // 边已存在
        v_p = v_p->nextarc;
    }
    v_p = G.vertices[v_i].firstarc;
    G.vertices[v_i].firstarc = (ArcNode *) malloc(sizeof(ArcNode));
    G.vertices[v_i].firstarc->adjvex = w_i;
    G.vertices[v_i].firstarc->nextarc = v_p;
    return OK;
}

status InsertArc(ALGraph &G, KeyType v, KeyType w) {

    // v->w
    int v_i = LocateVex(G, v);
    if (v_i == -1)return ERROR;
    int w_i = LocateVex(G, w);
    if (w_i == -1)return ERROR;

    if (insertSinArc(G, v_i, w_i) && insertSinArc(G, w_i, v_i)) {
        // 分别插入两个双向边
        G.arcnum++;
        return OK;
    } else return ERROR;


}

int deleteSingle(ALGraph &G, int v_i, int w_i) {

    ArcNode *head = (ArcNode *) malloc(sizeof(ArcNode));
    head->nextarc = G.vertices[v_i].firstarc;
    ArcNode *v_p = head, *v_q = v_p->nextarc;
    int flag = 0;
    while (v_q != nullptr) {
        if (v_q->adjvex == w_i) {
            //delete
            v_p->nextarc = v_q->nextarc;
            free(v_q);
            v_q = v_p->nextarc;
            flag = 1;
            // 无向图默认不含多重边
            break;
        } else {
            v_p = v_q;
            v_q = v_p->nextarc;
        }
    }
    G.vertices[v_i].firstarc = head->nextarc;
    free(head);
    if (flag)return 1;
    else return 0;
}

status DeleteArc(ALGraph &G, KeyType v, KeyType w) {

    // 默认 G 正确创建
    int v_i = LocateVex(G, v);
    if (v_i == -1)return ERROR;
    int w_i = LocateVex(G, w);
    if (w_i == -1)return ERROR;
    int a = deleteSingle(G, v_i, w_i);
    int b = deleteSingle(G, w_i, v_i);
    if (a && b)return OK;
    else return ERROR;
    /********** End **********/
}

int sumVisited(int n) {
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += visited[i];
    }
    return sum;
}

status DFSTraverse(ALGraph &G, void (*visit)(VertexType)) {

    if (G.vexnum == 0)return ERROR;

    for (int i = 0; i < G.vexnum; ++i) {
        visited[i] = 0;
    }

//    while (sumVisited(G.vexnum) < G.vexnum) {// 图尚未访问完全
        for (int i = 0; i < G.vexnum; ++i) {
            if (!visited[i]) {
                dfsVisit(G, i, visit);
            }
        }
//    }

    return OK;


}

void dfsVisit(ALGraph &G, int index, void (*visit)(VertexType)) {
    if (!visited[index]) {
        visit(G.vertices[index].data);
        visited[index] = 1;
        ArcNode *p = G.vertices[index].firstarc;
        while (p != nullptr) {
            dfsVisit(G, p->adjvex, visit);
            p = p->nextarc;
        }
    }
}

status BFSTraverse(ALGraph &G, void (*visit)(VertexType)) {

    if (G.vexnum == 0)return ERROR;

    for (int i = 0; i < G.vexnum; ++i) {
        visited[i] = 0;
    }

    for (int i = 0; i < G.vexnum; ++i) {
        if (!visited[i]) {
            bfsVisit(G, i, visit);
        }
    }


    return OK;
}

void inline bfsVisit(ALGraph &G, int index, void (*visit)(VertexType)) {

    // 队列的广度优先遍历的经典方法

    struct Queue queue;

    queue.push(index);

    while (!queue.isempty()) {
        int vex = queue.getfront();
        queue.pop();
        if (!visited[vex]) {
            visit(G.vertices[vex].data);
            visited[vex] = 1;
            ArcNode *p = G.vertices[vex].firstarc;
            while (p != nullptr) {
                if (!visited[p->adjvex])queue.push(p->adjvex);
                p = p->nextarc;
            }

        }
    }
}

status SaveGraph(ALGraph G, char FileName[]) {

    FILE *out = fopen(FileName, "w");
    for (int i = 0; i < G.vexnum; ++i) {
        fprintf(out, "%d %s ", G.vertices[i].data.key, G.vertices[i].data.others);
    }
    fprintf(out, "%d null ", -1);
    for (int i = 0; i < G.vexnum; ++i) {
        ArcNode *p = G.vertices[i].firstarc;
        while (p != nullptr) {
            fprintf(out, "%d %d ", G.vertices[i].data.key, G.vertices[p->adjvex].data.key);
            p = p->nextarc;
        }
    }
    fprintf(out, "%d %d", -1, -1);
    fclose(out);

    return OK;
}

status LoadGraph(ALGraph &G, char FileName[]) {


    if (G.vexnum != 0) return ERROR;

    FILE *in = fopen(FileName, "r");

    inputG(G, in);

    fclose(in);

    return OK;

}

void printGraph(ALGraph G, int cmd) {
    if (G.vexnum == 0)printf("The Graph is empty\n");
    for (int i = 0; i < G.vexnum; i++) {
        ArcNode *p = G.vertices[i].firstarc;
        printf("%2d %3s\t", G.vertices[i].data.key, G.vertices[i].data.others);
        while (p) {
            if (cmd == 1) {
                printf(" %d", G.vertices[p->adjvex].data.key);
            } else {
                printf(" %d", p->adjvex);
            }
            p = p->nextarc;
        }
        printf("\n");
    }
}

void inputG(ALGraph &G, FILE *in) {
    if (G.vexnum) {
        printf("The Graph is not empty.\n");
        return;
    }
    VertexType V[2 * MAX_VERTEX_NUM];
    KeyType VR[2 * MAX_VERTEX_NUM * MAX_VERTEX_NUM + 1][2];
    int i = 0;
    do {
        if (i > MAX_VERTEX_NUM + 1) {
            printf("The input data has wrong format.\n");
            return;
        }
        fscanf(in, "%d%s", &V[i].key, V[i].others);
    } while (V[i++].key != -1);
    i = 0;
    do {
        if (i > MAX_VERTEX_NUM * MAX_VERTEX_NUM) {
            printf("The input data has wrong format.\n");
            return;
        }
        fscanf(in, "%d%d", &VR[i][0], &VR[i][1]);
    } while (VR[i++][0] != -1);
    if (CreateGraph(G, V, VR) == ERROR)
        printf("The input data has repeat keys.\n");
    else printf("Create successfully!\n");
}

void dfsVisit(ALGraph &G, int index) {
    if (!visited[index]) {
        visited[index] = 1;
        ArcNode *p = G.vertices[index].firstarc;
        while (p != nullptr) {
            dfsVisit(G, p->adjvex);
            p = p->nextarc;
        }
    }
}


int getMaxCC(ALGraph G) {

    for (int i = 0; i < G.vexnum; ++i) {
        visited[i] = 0;
    }

    int maxSum = 0;
    int maxIndex = -1;
    int beforeDfs = 0;
    while (sumVisited(G.vexnum) < G.vexnum) {// 图尚未访问完全
        for (int i = 0; i < G.vexnum; ++i) {
            if (!visited[i]) {
                dfsVisit(G, i);
                int sum = sumVisited(G.vexnum) - beforeDfs;
                beforeDfs = sumVisited(G.vexnum);
                if (sum > maxSum) {
                    maxSum = sum;
                    maxIndex = i;
                }
            }
        }
    }
    for (int i = 0; i < G.vexnum; ++i) {
        visited[i] = 0;
    }

    if (maxIndex != -1) {
        dfsVisit(G, maxIndex, visit);
    }

    return maxSum;
}

int getMinCC(ALGraph G) {

    for (int i = 0; i < G.vexnum; ++i) {
        visited[i] = 0;
    }

    int minSum = G.vexnum + 1;
    int minIndex = -1;
    int beforeDfs = 0;
    while (sumVisited(G.vexnum) < G.vexnum) {// 图尚未访问完全
        for (int i = 0; i < G.vexnum; ++i) {
            if (!visited[i]) {
                dfsVisit(G, i);
                int sum = sumVisited(G.vexnum) - beforeDfs;
                beforeDfs = sumVisited(G.vexnum);
                if (sum < minSum) {
                    minSum = sum;
                    minIndex = i;
                }
            }
        }
    }
    for (int i = 0; i < G.vexnum; ++i) {
        visited[i] = 0;
    }

    if (minIndex != -1) {
        dfsVisit(G, minIndex, visit);
        return minSum;
    }

    return 0;
}

void visit(VertexType v) {
    printf("(%d,%s) ", v.key, v.others);
}

