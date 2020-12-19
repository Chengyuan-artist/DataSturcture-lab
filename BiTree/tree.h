//
// Created by 张承元 on 2020/11/19.
//
#include <cstdio>
#include <cstdlib>
#include <cstring>


#ifndef BINARYTREE_TREE_H
#define BINARYTREE_TREE_H

#endif //BINARYTREE_TREE_H

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAXN 1000

typedef int status;
typedef int KeyType;
typedef struct {
    KeyType key;
    char others[20];
} TElemType; //二叉树结点类型定义


typedef struct BiTNode {  //二叉链表结点的定义
    TElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;




// 按照先序次序输入二叉树中的结点的值(分别为key和others,以空格隔开),(0,null)表示空结点
// 任一叶子结点均有两个空结点
status CreateBiTree(BiTree &T);

// 清空二叉树，并将树根置null
status ClearBiTree(BiTree &T);

// 求二叉树深度
int BiTreeDepth(BiTree T);

BiTNode *LocateNode(BiTree T, KeyType e);

status Assign(BiTree &T, KeyType e, TElemType value);

BiTNode *GetSibling(BiTree T, KeyType e);

// e:插入位置;
// LR:为0时作为e的右孩子插入，为1时作为e的左孩子插入，为-1时作为整棵树的根节点插入;
// c为插入元素的值。
status InsertNode(BiTree &T, KeyType e, int LR, TElemType c);

// 记当key值为e的结点为T
// 当T为叶子结点时，直接删除
// 当T度为1时,直接用该结点的孩子代替
// 当T度为2时,用T的左子树left代替原来的位置,
// T的右子树right作为left的最右节点的右子树插入
status DeleteNode(BiTree &T, KeyType e);

status PreOrderTraverse(BiTree T, void (*visit)(BiTree));

status InOrderTraverse(BiTree T, void (*visit)(BiTree));

status PostOrderTraverse(BiTree T, void (*visit)(BiTree));

status LevelOrderTraverse(BiTree T, void (*visit)(BiTree));

status SaveBiTree(BiTree T, char FileName[]);

// 返回值为OK时，成功读入;返回值为ERROR时，读入失败:有重复的权值
status LoadBiTree(BiTree &T, char FileName[]);

void clear(BiTree &T);

// 返回 a,b 中的最大值
int getmax(int a, int b);

// 判断树中key值存在与否
int isvisited(int key);

// 以先序的形式将树写入文件中
void writeTree(BiTree T, FILE *out);

// 以先序的形式读入数据并创建树;
// 返回值为1,说明建树成功;
// 返回值为0，说明建树过程中存在 key值重复
int readTree(BiTree &T, FILE *in);

void visit(BiTree T);

BiTNode* LocateParent(BiTree T,KeyType e);

// 获取结点的度
int getDegree(BiTNode *node);

// 在BSF中搜索关键字为key的值
// 若查找成功, p指向该结点
// 若查找失败, p指向最后查找位置的父节点
status searchBST(BiTree T, KeyType key, BiTree father, BiTree &p);

// 在BSF中插入值为e的元素
status InsertBST(BiTree &T, TElemType e);

// 从文件读入BSF树,每行为各结点值(分别为key和others,以空格隔开)
// 文件以 # 结尾
status LoadBST(BiTree &T, char FileName[]);

int readBST(BiTree &T, FILE *in);

int getKeyDepth(BiTree T, int key, int cnt);