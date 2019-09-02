//
// Created by lightol on 2019/9/2.
//

#include <list>
#include <iostream>

// 其实就是一个单链表快排
using std::cout;
using std::endl;

struct Node
{
    int key;
    Node* next;
    Node(int nKey, Node* pNext): key(nKey), next(pNext) {}
};

class List {
public:
    List() {}
    
    Node* CreateList(int* array, int k) {
        Node* pHeader = new Node(array[0], nullptr);
        Node* pCurrent = nullptr;
        Node* pRear = pHeader;
        
        int count = 0;
        while (++count < k) {
            pCurrent = new Node(array[count], nullptr);
            pRear->next = pCurrent;
            pRear = pCurrent;
        }
        
        return pHeader;
    }

    void ShowList(Node *pHead) const {
        Node* pCurrent = pHead;
        
        while (pCurrent) {
            cout << pCurrent->key << " ";
            pCurrent = pCurrent->next;
        }
        cout << endl;
    }

    Node* GetTail(Node *pHead) const {
        Node* pCurrent = pHead;

        while (pCurrent && pCurrent->next) {
            pCurrent = pCurrent->next;
        }

        return pCurrent;
    }

    int GetLength(Node* pHead) const {
        Node* pCurrent = pHead;
        int num = 0;
        while (pCurrent) {
            pCurrent = pCurrent->next;
            num++;
        }

        return num;
    }

    void BubbleSort(Node *pHead, int length) const {
        for (int i = 0; i < length - 1; ++i) {
            Node* pCur = pHead;
            for (int j = 0; j < length - 1 - i; ++j) {
                
                if (pCur->key > pCur->next->key) {
                    int temp = pCur->key;
                    pCur->key = pCur->next->key;
                    pCur->next->key = temp;
                }

                pCur = pCur->next;
            }
            {
//                Node* pCurrent = pHead;
//
//                while (pCurrent) {
//                    cout << pCurrent->key << " ";
//                    pCurrent = pCurrent->next;
//                }
//                cout << endl;
            }
        }
    }

    void QuickSort(Node *pHead, Node *pEnd) const {
//        cout << "pHead = " << pHead->key << endl;
//        cout << "pEnd = " << pEnd->key << endl;
        if (!pHead) {
            return;
        }

        if(pHead == pEnd) {
            return;
        }

        Node* spliter = GetSpliter(pHead, pEnd);
//        cout << "spliter = " << spliter->key << endl;
//        {
//            {
//                    Node* pCurrent = pHead;
//                    while (pCurrent) {
//                        cout << pCurrent->key << " ";
//                        if (pCurrent == pEnd) {
//                            break;
//                        }
//                        pCurrent = pCurrent->next;
//                    }
//                    cout << endl;
//                }
//        }

        QuickSort(pHead, spliter);
        QuickSort(spliter->next, pEnd);
    }

    Node* GetSpliter(Node* pHead, Node* pEnd) const {
        int point = pHead->key;
        Node* pSlow = pHead;
        Node* pFast = pHead->next;

        while (pFast) {
//            {
//                {
//                    Node* pCurrent = pHead;
//                    cout << "pFast = " << pFast->key << endl;
//                    cout << "pSlow = " << pSlow->key << endl;
//                    cout << "point = " << point << endl;
//                    while (pCurrent) {
//                        cout << pCurrent->key << " ";
//                        pCurrent = pCurrent->next;
//                    }
//                    cout << endl;
//                }
//            }
            if (pFast->key < point) {
                pSlow = pSlow->next;
                std::swap(pFast->key, pSlow->key);
//                {
//                    cout << "swap" << endl;
//                    {
//                        Node* pCurrent = pHead;
//                        while (pCurrent) {
//                            cout << pCurrent->key << " ";
//                            pCurrent = pCurrent->next;
//                        }
//                        cout << endl;
//                    }
//                }
            }

            pFast = pFast->next;


        }

        {
//            {
//                cout << "swap pHead" << endl;
//                {
//                    Node* pCurrent = pHead;
//                    while (pCurrent) {
//                        cout << pCurrent->key << " ";
//                        pCurrent = pCurrent->next;
//                    }
//                    cout << endl;
//                }
//            }
//            cout << "pHead = " << pHead->key << endl;
//            cout << "pSlow = " << pSlow->key << endl;
        }

        std::swap(pHead->key, pSlow->key);
//        {
//            cout << "swaped pHead" << endl;
//            {
//                Node* pCurrent = pHead;
//                while (pCurrent) {
//                    cout << pCurrent->key << " ";
//                    pCurrent = pCurrent->next;
//                }
//                cout << endl;
//                cout << "pSlow = " << pSlow->key << endl;
//            }
//        }

        return pSlow;
    }
};

int main() {
    int array[] = {12, 3, 4, 2, 20, 8, 7, 9};
    List myList;
    Node* pHead = myList.CreateList(array, 8);
    cout << "before sort:\n";
    myList.ShowList(pHead);
//    myList.BubbleSort(pHead, myList.GetLength(pHead));
//    cout << "after bubble sort:\n";
//    myList.ShowList(pHead);
    myList.QuickSort(pHead, myList.GetTail(pHead));
    cout << "after quick sort:\n";
    myList.ShowList(pHead);
}