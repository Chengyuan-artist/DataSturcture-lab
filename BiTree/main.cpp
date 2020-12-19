#include "tree.h"

void initMenu();

void output(int x);

int main() {

    setbuf(stdout, 0);

    BiTree T = nullptr;

    int op = 1;

    KeyType e;
    BiTNode *node;
    TElemType val;
    int LR;

    initMenu();
    while (op) {
//        initMenu();
        printf("please input the command:");
        scanf("%d", &op);

        switch (op) {
            case 1:
                output(CreateBiTree(T));
                break;
            case 8:
                output(PreOrderTraverse(T, visit));
                break;
            case 9:
                output(InOrderTraverse(T, visit));
                break;
            case 10:
                output(PostOrderTraverse(T, visit));
                break;
            case 12:
                output(SaveBiTree(T, "test.out"));
                break;
            case 13:
                output(LoadBiTree(T, "test.in"));
                break;
            case 2:
                output(ClearBiTree(T));
                break;
            case 11:
                output(LevelOrderTraverse(T, visit));
                break;
            case 14:
                printf("%d\n", BiTreeDepth(T));
                break;
            case 3:
                printf("please input the key of the element to quarry:");
                scanf("%d", &e);
                node = LocateNode(T, e);
                if (node == nullptr)printf("That key doesn't exist!\n");
                else {
                    printf("Found it! It is:\n");
                    visit(node);
                    printf("\n");
                }
                break;
            case 4:
                printf("please input the key of the element to assign:");
                scanf("%d", &e);
                printf("please input the new value ,the right format is (key[blank]others):\n");
                scanf("%d%s", &val.key, val.others);
                output(Assign(T, e, val));
                break;
            case 6:
                printf("please input the key of the element to insert from:\n");
                scanf("%d", &e);
                printf("please input the new value ,the right format is (key[blank]others):\n");
                scanf("%d%s", &val.key, val.others);
                printf("please choose the insert type:\n-1 : as root\n0 : as right child\n1 : as left child\n");
                scanf("%d", &LR);
                output(InsertNode(T, e, LR, val));
                break;
            case 5:
                printf("please input the key of the element to quarry:");
                scanf("%d", &e);
                node = GetSibling(T, e);
                if(node == nullptr){
                    printf("That element's not exist or sibling is null\n");
                }else{
                    printf("That element's sibling is:\n");
                    visit(node);
                    printf("\n");
                }
                break;
            case 7:
                printf("please input the key of the element to delete:");
                scanf("%d", &e);
                output(DeleteNode(T, e));
                break;
            case 0:
                printf("Thank you.\n");
                break;
            case 15:
                output(LoadBST(T, "test.in"));
                break;
            case 16:
                printf("please input the key of the element to quarry:");
                scanf("%d", &e);
                searchBST(T, e, nullptr, node);
                if(searchBST(T, e, nullptr, node)){
                    printf("Found it! It is:\n");
                    visit(node);
                    printf("\n");
                }
                else {
                    printf("That key doesn't exist!\n");
                }
                break;
            case -1:
                printf("please input the key of the element to quarry:");
                scanf("%d", &e);
                printf("%d\n", getKeyDepth(T, e, 1));
                break;
            default:
                printf("command %d not found!\n", op);
                break;
        }

//        system("pause");
    }
    return 0;
}

void initMenu() {
//    system("cls");
    printf("\n\n");
    printf("      Menu for Linear Table On Sequence Structure \n");
    printf("-------------------------------------------------\n");
    printf("    	  1. CreateBiTree       2. ClearBiTree\n");
    printf("    	  3. LocateNode         4. Assign \n");
    printf("    	  5. GetSibling         6. InsertNode  \n");
    printf("    	  7. DeleteNode         8. PreOrderTraverse \n");
    printf("    	  9. InOrderTraverse     10. PostOrderTraverse\n");
    printf("    	  11. LevelOrderTraverse    12.SaveBiTree\n");
    printf("    	  13. LoadBiTree        14.BiTreeDepth\n");
    printf("    	  15. LoadBST        16.searchBST\n");
    printf("    	  0. Exit\n");
    printf("-------------------------------------------------\n");
    printf("    please choose your operation[0~15]:\n");
}

void output(int x) {
    if (x == OK)printf("\noperated successfully!\n");
    else printf("\nfail to operate!\n");
}