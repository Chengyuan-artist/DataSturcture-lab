#include "algraph.h"
#include "hashtable.h"

#include <iostream>

using namespace std;

void initMenu();

void output(int x);

extern int visited[MAX_VERTEX_NUM];
int main() {

    setbuf(stdout, nullptr);

    ALGraph G;
    G.vexnum = 0;

    KeyType key;
    int index;
    VertexType val;
    KeyType w;
    int num;

    int op = 1;
    initMenu();
    while (op) {
        printf("please input the command:");
        scanf("%d", &op);
        switch (op) {
            case 1:
                inputG(G, stdin);
                break;
            case 2:
                output(DestroyGraph(G));
                break;
            case 3:
                printf("please input the key of the element to quarry:");
                scanf("%d", &key);
                index = LocateVex(G, key);
                if (index == -1)printf("That key doesn't exist!\n");
                else {
                    printf("Found it! It is:\n");
                    visit(G.vertices[index].data);
                    printf("\n");
                }
                break;
            case 4:
                printf("please input the key of the element to assign:");
                scanf("%d", &key);
                printf("please input the new value ,the right format is (key[blank]others):\n");
                scanf("%d%s", &val.key, val.others);
                output(PutVex(G, key, val));
                break;
            case 5:
                printf("please input the key of the element to quarry:");
                scanf("%d", &key);
                index = FirstAdjVex(G, key);
                if (index == -1)printf("Such first adjacent vex doesn't exist!\n");
                else {
                    printf("%d", key);
                    printf(" 's first adjacent vex is:\n");
                    visit(G.vertices[index].data);
                    printf("\n");
                }
                break;
            case 6:
                printf("please input the key of the vex to quarry:");
                scanf("%d", &key);
                printf("please input the key of the vex adjacent to the former vex:");
                scanf("%d", &w);
                index = NextAdjVex(G, key, w);
                if (index == -1)
                    printf("The former key doesn't exist "
                           "or The former key's next adjacent vex related to the latter key doesn't exist!\n");
                else {
                    printf("%d", key);
                    printf(" 's next adjacent vex after %d is:\n", w);
                    visit(G.vertices[index].data);
                    printf("\n");
                }
                break;
            case 7:
                printf("please input the new value ,the right format is (key[blank]others):\n");
                scanf("%d%s", &val.key, val.others);
                output(InsertVex(G, val));
                break;
            case 8:
                printf("please input the key of the vex to delete:");
                scanf("%d", &key);
                output(DeleteVex(G, key));
                break;
            case 9:
                printf("please input the two keys of the arc to add:");
                scanf("%d", &key);
                scanf("%d", &w);
                output(InsertArc(G, key, w));
                break;
            case 10:
                printf("please input the two keys of the arc to delete:");
                scanf("%d", &key);
                scanf("%d", &w);
                output(DeleteArc(G, key, w));
                break;
            case 11:
                output(DFSTraverse(G, visit));
                break;
            case 12:
                output(BFSTraverse(G, visit));
                break;
            case 13:
                output(SaveGraph(G, "test.out"));
                break;
            case 14:
                output(LoadGraph(G, "test.in"));
                break;
            case 15:
                num = getMaxCC(G);
                if (num)printf("\nThe vex num of max connected component is %d\n", num);
                else printf("The Graph is empty\n");
                break;
            case 16:
                num = getMinCC(G);
                if (num)printf("\nThe vex num of min connected component is %d\n", num);
                else printf("The Graph is empty\n");
                break;
            case 17:
                printGraph(G, 1);
                break;
            case -1:

                for (int i = 0; i < G.vexnum; ++i) {
                    visited[i] = 0;
                }

                for (int i = 0; i < G.vexnum; ++i) {
                    if (!visited[i]) {
                        bfsVisit(G, i, visit);
                    }
                }
                break;
            default:
                printf("command %d not found!\n", op);
                break;
        }
    }

    return 0;
}


void initMenu() {
//    system("cls");
    printf("\n\n");
    printf("      Menu for Undirected Graph On link Structure \n");
    printf("-------------------------------------------------\n");
    printf("    	  1. CreateGraph       2. DestroyGraph\n");
    printf("    	  3. LocateVex         4. PutVex \n");
    printf("    	  5. FirstAdjVex       6. NextAdjVex  \n");
    printf("    	  7. InsertVex         8. DeleteVex \n");
    printf("    	  9. InsertArc        10. DeleteArc\n");
    printf("    	  11. DFSTraverse     12.BFSTraverse\n");
    printf("    	  13. SaveGraph       14.LoadGraph\n");
    printf("    	  15. getMaxCC        16.getMinCC\n");
    printf("    	  17.printGraph        0. Exit\n");
    printf("-------------------------------------------------\n");
    printf("    please choose your operation[0~17]:\n");
}

void output(int x) {
    if (x == OK)printf("\noperated successfully!\n");
    else printf("\nfail to operate!\n");
}

