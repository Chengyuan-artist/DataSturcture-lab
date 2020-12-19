//
// Created by chengyuan on 11/20/20.
//

#ifndef ADJLIST_ALGRAPH_H
#define ADJLIST_ALGRAPH_H

#endif //ADJLIST_ALGRAPH_H

#include <cstdlib>
#include <cstring>
#include <cstdio>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_VERTEX_NUM 20
typedef int status;
typedef int KeyType;
typedef enum {
    DG, DN, UDG, UDN
} GraphKind;
typedef struct {
    KeyType key;
    char others[20];
} VertexType; //顶点类型定义
typedef struct ArcNode {         //表结点类型定义
    int adjvex;              //顶点位置编号
    struct ArcNode *nextarc;       //下一个表结点指针
} ArcNode;
typedef struct VNode {                //头结点及其数组类型定义
    VertexType data;           //顶点信息
    ArcNode *firstarc;           //指向第一条弧
} VNode, AdjList[MAX_VERTEX_NUM];
typedef struct {  //邻接表的类型定义
    AdjList vertices;          //头结点数组
    int vexnum, arcnum;         //顶点数、弧数
    GraphKind kind;        //图的类型
} ALGraph;


// 根据V和VR构造图T并返回OK，如果V和VR不正确，返回ERROR
// 如果有相同的关键字，返回ERROR。
status CreateGraph(ALGraph &G, VertexType V[], KeyType VR[][2]);

// 销毁无向图G
status DestroyGraph(ALGraph &G);

// 销毁一个顶点所含的所有弧, 接受该顶点的firstArc指针
void destroyArcs(ArcNode *&first);

//根据u在图G中查找顶点，查找成功返回位序，否则返回-1；
int LocateVex(ALGraph G, KeyType u);

//根据u在图G中查找顶点，查找成功将该顶点值修改成value，返回OK；
//如果查找失败或关键字不唯一，返回ERROR
status PutVex(ALGraph &G, KeyType u, VertexType value);

//根据u在图G中查找顶点，查找成功返回顶点u的第一邻接顶点位序，否则返回-1；
int FirstAdjVex(ALGraph G, KeyType u);

//根据u在图G中查找顶点，查找成功返回顶点v的邻接顶点相对于w的下一邻接顶点的位序，查找失败返回-1；
int NextAdjVex(ALGraph G, KeyType v, KeyType w);

//在图G中插入顶点v，成功返回OK,否则返回ERROR
status InsertVex(ALGraph &G, VertexType v);

//在图G中删除关键字v对应的顶点以及相关的弧，成功返回OK,否则返回ERROR
status DeleteVex(ALGraph &G, KeyType v);

// 在first所指链表中，删除index的项，并更新所有受删除index影响的项的值
void maintainArcs(ArcNode *&first, int index);

// 在无向图G中增加弧<v,w>(双向)，成功返回OK,否则返回ERROR
status InsertArc(ALGraph &G, KeyType v, KeyType w);

// 在G中增加弧v->w,成功返回OK,否则返回ERROR
int insertSinArc(ALGraph &G, int v_i, int w_i);

// 在无向图G中删除弧<v,w>(双向)，成功返回OK,否则返回ERROR
status DeleteArc(ALGraph &G, KeyType v, KeyType w);

// 在G中删除弧v->w, 成功返回OK,否则返回ERROR
int deleteSingle(ALGraph &G, int v_i, int w_i);

// 对图G进行深度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
// 当某个联通分量访问完全后, 从图中尚未访问过的最小位序结点开始访问
status DFSTraverse(ALGraph &G, void (*visit)(VertexType));

void dfsVisit(ALGraph &G, int index, void (*visit)(VertexType));

// 对图G进行深度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
// 当某个联通分量访问完全后, 从图中尚未访问过的最小位序结点开始访问
status BFSTraverse(ALGraph &G, void (*visit)(VertexType));

void bfsVisit(ALGraph &G, int index, void (*visit)(VertexType));

//将图的数据写入到文件FileName中
status SaveGraph(ALGraph G, char FileName[]);

//读入文件FileName的图数据，创建图的邻接表
status LoadGraph(ALGraph &G, char FileName[]);

// 打印出图的邻接表信息;cmd == 1, human; cmd == 0, machine.
void printGraph(ALGraph G, int cmd);

// 从输入流in中读取创建无向图的数据
// 数据格式eg. (5 线性表 8 集合 7 二叉树 6 无向图 -1 nil 5 6 5 7 6 7 7 8 -1 -1) 顶点信息和边信息均以-1结尾
void inputG(ALGraph &G, FILE* in);

int getMaxCC(ALGraph G);

int getMinCC(ALGraph G);

void visit(VertexType);