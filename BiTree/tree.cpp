//
// Created by 张承元 on 2020/11/19.
//

#include "tree.h"
#include "queue.h"

//标记数组,用来记录树中结点的key值使用情况,用于判重
int visited[MAXN];//keys


int isvisited(int key) {
    if (visited[key])return 1;
    visited[key] = 1;
    return 0;
}

status CreateBiTree(BiTree &T) {
//    memset(visited, 0, MAXN);
    if (T != nullptr)return INFEASIBLE;
    if (readTree(T, stdin)) {
        // 从标准输入流读入
        // 且建树成功
        return OK;
    } else {
        ClearBiTree(T);
        return ERROR;
    }
}

status ClearBiTree(BiTree &T) {
    clear(T);
    //标记数组置为零
    memset(visited, 0, MAXN);
    return OK;
}

void clear(BiTree &T) {
    if (T) {
        clear(T->lchild);
        clear(T->rchild);
        free(T);
        T = nullptr;
    }
}

status PreOrderTraverse(BiTree T, void (*visit)(BiTree)) {
    if (T) {
        visit(T);
        PreOrderTraverse(T->lchild, visit);
        PreOrderTraverse(T->rchild, visit);
        return OK;
    }
    return ERROR;
}

void visit(BiTree T) {
    printf("(%d,%s) ", T->data.key, T->data.others);
}

status InOrderTraverse(BiTree T, void (*visit)(BiTree)) {
    if (T) {
        InOrderTraverse(T->lchild, visit);
        visit(T);
        InOrderTraverse(T->rchild, visit);
        return OK;
    }
    return ERROR;
}

status PostOrderTraverse(BiTree T, void (*visit)(BiTree)) {
    if (T) {
        PostOrderTraverse(T->lchild, visit);
        PostOrderTraverse(T->rchild, visit);
        visit(T);
        return OK;
    }
    return ERROR;
}

status SaveBiTree(BiTree T, char *FileName) {
    FILE *out = fopen(FileName, "w");
    writeTree(T, out);
    fclose(out);
    return OK;
}

void writeTree(BiTree T, FILE *out) {
    if (T != nullptr) {
        fprintf(out, "%d %s\n", T->data.key, T->data.others);
        writeTree(T->lchild, out);
        writeTree(T->rchild, out);
    } else {
        fprintf(out, "%d null\n", 0);
    }
}

int readTree(BiTree &T, FILE *in) {
    TElemType elem;
    fscanf(in, "%d%s", &elem.key, elem.others);
    T = nullptr;
    if (elem.key == 0) {
        // 此时读入(0,null)
        return 1;
    }
    if (isvisited(elem.key)) {
        return 0;
    }
    //正常建树
    T = (BiTree) malloc(sizeof(BiTNode));
    T->data = elem;
    T->lchild = nullptr;
    T->rchild = nullptr;

    //分别建左子树，右子树
    return readTree(T->lchild, in) && readTree(T->rchild, in);
}


status LoadBiTree(BiTree &T, char *FileName) {
    FILE *in = fopen(FileName, "r");
    if (readTree(T, in)) {
        fclose(in);
        return OK;
    } else {
        fclose(in);
        ClearBiTree(T);
        return ERROR;
    }
}

status LevelOrderTraverse(BiTree T, void (*visit)(BiTree)) {
    // 层次遍历的经典队列方法
    struct Queue queue;

    queue.push(T);

    while (!queue.isempty()) {
        BiTree node = queue.getfront();
        queue.pop();
        if (node != nullptr) {
            visit(node);
            queue.push(node->lchild);
            queue.push(node->rchild);
        }
    }
    return OK;
}

int BiTreeDepth(BiTree T) {
    if (T == nullptr)return 0;
    // 二叉树深度 D(T) = 1 + max(D(T->lchild), D(T->rchild))
    return 1 + getmax(BiTreeDepth(T->lchild), BiTreeDepth(T->rchild));
}

int getmax(int a, int b) {
    return a > b ? a : b;
}

BiTNode *LocateNode(BiTree T, KeyType e) {
    if (T == nullptr) {
        return nullptr;
    }
    if (T->data.key == e) {
        return T;
    }

    // left保存左子树寻找结果
    // right保存右子树寻找结果
    BiTNode *left = LocateNode(T->lchild, e);
    BiTNode *right = LocateNode(T->rchild, e);

    if (left)return left;
    if (right)return right;

    // 若二者皆空，说明查找失败
    return nullptr;
}

status Assign(BiTree &T, KeyType e, TElemType value) {
    BiTNode *target = LocateNode(T, e);
    if (target == nullptr) {
        return INFEASIBLE;
    }
    visited[e] = 0;
    if (isvisited(value.key)) {
        visited[e] = 1;
        return ERROR;
    }
    target->data = value;
    return OK;
}

BiTNode *GetSibling(BiTree T, KeyType e) {
    BiTNode *parent = LocateParent(T, e);
    if (parent == nullptr) return nullptr;
    if (parent->lchild != nullptr && parent->lchild->data.key == e) {
        return parent->rchild;
    } else {
        return parent->lchild;
    }
}

status InsertNode(BiTree &T, KeyType e, int LR, TElemType c) {
    // 判断key值是否合法
    if (isvisited(c.key)) {
        return ERROR;
    }

    BiTNode *insert = (BiTNode *) malloc(sizeof(BiTNode));

    if (LR == 0 || LR == 1) {
        BiTNode *target = LocateNode(T, e);
        if (target == nullptr)return ERROR; // 待插入位置不存在
        //target 为待插入位置

        insert->data = c;
        BiTNode *child;
        if (LR == 0) {
            child = target->rchild;
            // 作为右子树插入
            target->rchild = insert;
        } else {
            child = target->lchild;
            // 作为左子树插入
            target->lchild = insert;
        }

        // target的原本的左子树或右子树作为插入元素的右孩子
        insert->rchild = child;
        insert->lchild = nullptr;

        return OK;
    }
    if (LR == -1) {

        insert->data = c;

        insert->rchild = T;
        insert->lchild = nullptr;

        // 更改T
        T = insert;

        return OK;
    }

    // Catch exception
    return ERROR;
}

BiTNode *LocateParent(BiTree T, KeyType e) {
    if (T == nullptr) {
        return nullptr;
    }
    if (T->lchild != nullptr && T->lchild->data.key == e) {
        return T;
    }
    if (T->rchild != nullptr && T->rchild->data.key == e) {
        return T;
    }
    BiTNode *leftres = LocateParent(T->lchild, e),
            *rightres = LocateParent(T->rchild, e);
    if (leftres)return leftres;
    if (rightres)return rightres;
    return nullptr;
}

status  DeleteNode(BiTree &T, KeyType e) {

    // 为二叉树加上"头结点"
    BiTNode *head = (BiTNode *) malloc(sizeof(BiTNode));
    head->data.key = -1;
    head->lchild = nullptr;
    head->rchild = T;

    BiTNode *parent = LocateParent(head, e);
    if (parent == nullptr)return ERROR; //key为e的结点不存在

    visited[e] = 0;// e对应标记数组值置0

    BiTNode *target;// 欲删除目标
    int isright = 0;// 标记target是否为其父节点的右孩子
    if (parent->lchild != nullptr && parent->lchild->data.key == e) {
        target = parent->lchild;
    } else {
        target = parent->rchild;
        isright = 1;
    }

    int degree = getDegree(target);
    // 分三种情况
    if (degree == 0) {
        //target 为叶子结点，直接删除
        free(target);
        if (isright) {
            parent->rchild = nullptr;
        } else {
            parent->lchild = nullptr;
        }
        return OK;
    }
    if (degree == 1) {
        BiTNode *child = target->lchild ? target->lchild : target->rchild;
        free(target);
        // 用child 代替原来 target 的位置
        // 修改父节点的指针值
        if (isright) {
            parent->rchild = child;
        } else {
            parent->lchild = child;
        }
        return OK;
    }
    if (degree == 2) {
        BiTNode *lchild = target->lchild;
        BiTNode *rchild = target->rchild;

        // 特判
        int isroot = 0; // 标记待删除结点是否为原树根结点
        if (T->data.key == target->data.key) {
            isroot = 1;
        }

        free(target);

        // 用删除结点的左孩子代替原节点位置
        if (isright) {
            parent->rchild = lchild;
        } else {
            parent->lchild = lchild;
        }
//        target = lchild;

        BiTNode *right = lchild;
        while (right->rchild != nullptr) {
            right = right->rchild;
        }
        // 此时right指向删除结点左孩子的最右结点
        // 删除结点的右孩子作为right的右孩子插入
        right->rchild = rchild;

        // 特判 如果被删除结点为根节点,则需重新修改T的指向
        if (isroot) {
            T = parent->rchild;
        }
        return OK;
    }

    // Exception
    return ERROR;
}

int getDegree(BiTNode *node) {
    if (node == nullptr)return -1;
    int res = 0;
    // 左子树存在
    if (node->lchild)res++;
    // 右子树存在
    if (node->rchild)res++;
    return res;
}

status searchBST(BiTree T, KeyType key, BiTree father, BiTree &p) {
    if (T == nullptr) {
        // 查找不成功
        // p指向查找路径上的最后一个元素
        p = father;
        return 0;
    }
    if (key == T->data.key){
        // 查找成功
        p = T;
        return 1;
    }
    if (key < T->data.key){
        // 向左子树寻找
        return searchBST(T->lchild, key, T, p);
    }else{
        // key > T->data.key
        // 向右子树寻找
        return searchBST(T->rchild, key, T, p);
    }
}

status InsertBST(BiTree &T, TElemType e) {
    BiTNode *mark;
    if(!searchBST(T, e.key, nullptr, mark)){
        // 查找不成功,此时mark指向待插入位置结点的父节点
        BiTNode *insert = (BiTNode*)malloc(sizeof(BiTNode));
        insert->data = e;
        insert->lchild = insert->rchild = nullptr;
        if (mark == nullptr){// 说明根节点T为空, insert作为根节点插入
            T = insert;
            return OK;
        }
        if (e.key < mark->data.key){// insert应作为mark的左孩子
            mark->lchild = insert;
        }else{// insert应作为mark的右孩子
            mark->rchild = insert;
        }
        return OK;
    }else{// 查找成功, 相应的key值在树中存在
        return ERROR;
    }
}

int readBST(BiTree &T, FILE *in) {
    TElemType elem;
    while (fscanf(in, "%d%s", &elem.key, elem.others)){
        if(elem.key == '#')break;
        if(elem.key){
            if(!InsertBST(T, elem)){
                return 0;
            }
        }
    }
    return 1;
}

status LoadBST(BiTree &T, char *FileName) {
    FILE *in = fopen(FileName, "r");
    if(readBST(T, in)){
        fclose(in);
        return OK;
    }else{
        fclose(in);
        ClearBiTree(T);
        return ERROR;
    }
}

int getKeyDepth(BiTree T, int key, int cnt) {
    if(T == nullptr) return 0;
    if(T->data.key == key){
        return cnt;
    }
    int leftRes = getKeyDepth(T->lchild, key, cnt + 1);
    int rightRes = getKeyDepth(T->rchild, key, cnt + 1);
    if (leftRes) return leftRes;
    if (rightRes) return rightRes;
    return 0;
}
