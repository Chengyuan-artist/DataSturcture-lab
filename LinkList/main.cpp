#include "linklist.h"


int main() {
    LinkList L = nullptr;
    int op = 1;//����ָ��

    int i;//Ԫ��λ��
    int e;//Ԫ��
    int e_ad;//Ԫ��ǰ������
    int k;//�����ƶ�λ��

    setbuf(stdout, 0);

    while (op) {
        system("cls");
        printf("\n\n");
        printf("      Menu for Linear Table On Sequence Structure \n");
        printf("-------------------------------------------------\n");
        printf("    	  1. InitList       2. DestroyList\n");
        printf("    	  3. ClearList      4. ListEmpty \n");
        printf("    	  5. ListLength     6. GetElem  \n");
        printf("    	  7. LocateElem     8. PriorElem \n");
        printf("    	  9. NextElem       10. ListInsert\n");
        printf("    	  11. ListDelete    12. ListTraverse\n");
        printf("    	  13. SaveList      14. LoadList\n");
        printf("    	  15. MergeSortList 16. ReverseList\n");
        printf("    	  17. LoopList\n");
        printf("    	  0. Exit\n");
        printf("-------------------------------------------------\n");
        printf("    ��ѡ����Ĳ���[0~15]:");
        scanf("%d", &op);
        switch (op) {
            case 1:
//                printf("\n----IntiList���ܴ�ʵ�֣�\n");
                if (InitList(L) == OK) printf("���Ա����ɹ���\n");
                else printf("���Ա���ʧ�ܣ�\n");
                break;
            case 2:
//                printf("\n----DestroyList���ܴ�ʵ�֣�\n");
                if (DestroyList(L) == OK)printf("���Ա����ٳɹ���\n");
                else printf("���Ա�����ʧ�ܣ�\n");
                break;
            case 3:
//                printf("\n----ClearList���ܴ�ʵ�֣�\n");
                if (ClearList(L) == OK)printf("���Ա���ճɹ���\n");
                else printf("���Ա����ʧ�ܣ�\n");
                break;
            case 4:
//                printf("\n----ListEmpty���ܴ�ʵ�֣�\n");
                switch (ListEmpty(L)) {
                    case TRUE:
                        printf("���Ա�Ϊ�գ�\n");
                        break;
                    case INFEASIBLE:
                        printf("���Ա�δ��ʼ����\n");
                        break;
                    case FALSE:
                        printf("���Ա�ǿգ�\n");
                        break;
                }
                break;
            case 5:
//                printf("\n----ListLength���ܴ�ʵ�֣�\n");
                if (ListLength(L) == -1)printf("���Ա�δ��ʼ����\n");
                else printf("���Ա���Ϊ%d\n", ListLength(L));
                break;
            case 6:
//                printf("\n----GetElem���ܴ�ʵ�֣�\n");
                printf("����������ȡԪ�ص�λ��i:");
                scanf("%d", &i);
                switch (GetElem(L, i, e)) {
                    case OK:
                        printf("���Ա���λ��Ϊ%d��Ԫ��ֵΪ%d\n", i, e);
                        break;
                    case ERROR:
                        printf("λ��%d���벻�Ϸ���\n", i);
                        break;
                    case INFEASIBLE:
                        printf("���Ա�δ��ʼ����\n");
                        break;
                }
                break;
            case 7:
//                printf("\n----LocateElem���ܴ�ʵ�֣�\n");
                printf("������Ԫ��ֵe:");
                scanf("%d", &e);
                i = LocateElem(L, e);
                switch (i) {
                    case INFEASIBLE:
                        printf("���Ա�δ��ʼ����\n");
                        break;
                    case 0:
                        printf("���Ա��в�����������Ԫ�أ�\n");
                        break;
                    default:
                        printf("���Ա���%d��λ��Ϊ%d\n", e, i);

                }
                break;
            case 8:
//                printf("\n----PriorElem���ܴ�ʵ�֣�\n");
                printf("���������Ա��е�ĳԪ��e:");
                scanf("%d", &e);
                i = PriorElem(L, e, e_ad);
                switch (i) {
                    case INFEASIBLE:
                        printf("���Ա�δ��ʼ����\n");
                        break;
                    case ERROR:
                        printf("Ԫ��%d�������Ա��л�Ԫ��%d������ǰ����\n", e, e);
                        break;
                    default:
                        printf("Ԫ��%d��ֱ��ǰ��Ϊ%d\n", e, e_ad);
                }
                break;
            case 9:
//                printf("\n----NextElem���ܴ�ʵ�֣�\n");
                printf("���������Ա��е�ĳԪ��e:");
                scanf("%d", &e);
                i = NextElem(L, e, e_ad);
                switch (i) {
                    case INFEASIBLE:
                        printf("���Ա�δ��ʼ����\n");
                        break;
                    case ERROR:
                        printf("Ԫ��%d�������Ա��л�Ԫ��%d�����ں�̣�\n", e, e);
                        break;
                    default:
                        printf("Ԫ��%d��ֱ�Ӻ��Ϊ%d\n", e, e_ad);
                }
                break;
            case 10:
//                printf("\n----ListInsert���ܴ�ʵ�֣�\n");
                printf("���������Ԫ��e:");
                scanf("%d", &e);
                printf("���������λ��i:");
                scanf("%d", &i);
                switch (ListInsert(L, i, e)) {
                    case OK:
                        printf("����ɹ���\n");
                        break;
                    case ERROR:
                        printf("����λ�ò��Ϸ���\n");
                        break;
                    case INFEASIBLE:
                        printf("���Ա���δ��ʼ����\n");
                        break;
                    default:
                        printf("�������ʧ�ܣ�\n");
                }
                break;
            case 11:
//                printf("\n----ListDelete���ܴ�ʵ�֣�\n");
                printf("�������ɾ��Ԫ�ص�λ��i:");
                scanf("%d", &i);
                switch (ListDelete(L, i, e)) {
                    case OK:
                        printf("ɾ���ɹ���\n��ɾ��Ԫ��Ϊ%d\n", e);
                        break;
                    case ERROR:
                        printf("ɾ��λ�ò��Ϸ���\n");
                        break;
                    case INFEASIBLE:
                        printf("���Ա���δ��ʼ����\n");
                        break;
                    default:
                        printf("ɾ������ʧ�ܣ�\n");
                }
                break;
            case 12:
//                printf("\n----ListTraverse���ܴ�ʵ�֣�\n");
                switch (ListEmpty(L)) {
                    case INFEASIBLE:
                        printf("���Ա���δ��ʼ����\n");
                        break;
                    case TRUE:
                        printf("���Ա�Ϊ�գ�\n");
                        break;
                    case FALSE:
                        ListTraverse(L);
                        break;
                    default:
                        break;
                }
                break;
            case 14:
                if (LoadList(L, "test.in") == OK)printf("��ȡ�ļ��ɹ���\n");
                else printf("��ȡ�ļ�ʧ�ܣ�\n");
                break;
            case 13:
                if (SaveList(L, "test.out") == OK)printf("����ɹ�!\n");
                else printf("����ʧ�ܣ�\n");
                break;

            case 15:
                if (MergeSortList(L) == OK)printf("�����ɹ���\n");
                else printf("����ʧ�ܣ�\n");
                break;
            case 16:
                if (ReverseList(L) == OK)printf("�����ɹ���\n");
                else printf("����ʧ�ܣ�\n");
                break;
            case 17:
                printf("�����������ƶ���λ����");
                scanf("%d", &k);
                if (LoopList(L, k) == OK)printf("�����ɹ���\n");
                else printf("����ʧ�ܣ�\n");
                break;
            case 0:
                printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
                break;
            default:
                printf("��������ȷ��ָ�\n");
        }//end of switch
        system("pause");
    }//end of while
    return 0;
}//end of main()

