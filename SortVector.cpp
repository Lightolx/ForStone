//
// Created by lightol on 2019/9/2.
//

#include <iostream>
#include <vector>

using std::cout;
using std::endl;

int Splite(int* pLeft, int* pRight) {
    int k = pRight - pLeft;
    int point = pLeft[0];

    int i = 0;
    int j = k;
    while (i < j) {
        while (i < j && pLeft[i] <= point) {
            i++;
        }
        while (i < j && pLeft[j] >= point) {
            j--;
        }
        std::swap(pLeft[i], pLeft[j]);
    }

    // i指针会走到一个比pLeft[0]大的地方停下，或者i指针会走到j指针的地址处停下，
    // 一般情况下j指针所占据的元素都会比pLeft[0]大，当然也有意外，比如从pLeft[0]右边所有的元素都比pLeft[0]小，那么i直接走到最末尾和j碰头了;
    // 最后i,j碰头时所在元素的大小十分关键，如果是i去碰到j，那么这个元素有可能比pLeft[0]大也可能比它小，如果是j去碰到i，那么此时i既然停下来了，说明这里的元素肯定比pLeft[0]大
    if (pLeft[0] <= pLeft[i]) {
        std::swap(pLeft[0], pLeft[i-1]);
        return i-1;
    } else {
        std::swap(pLeft[0], pLeft[i]);  // 唯一会出现此种情况是一开始pLeft[0]右边所有的元素都比pLeft[0]小
        return i;
    }

}

void QuickSort(int* pLeft, int* pRight) {
    if (pRight == pLeft) {
        return;
    }
    cout << "pLeft  = " << pLeft[0] << endl;
    cout << "pRight = " << pRight[0] << endl;

    int id = Splite(pLeft, pRight);
    cout << "after split, id = " << id << ", vector is" << endl;
    for (int* p = pLeft; p <= pRight; ++p) {
        cout << p[0] << " ";
    }
    cout << endl << endl;

    if (id != 0 && id != 1) { //　if (id <= 1), 说明左边的已经排好了，不需要再排了
        QuickSort(pLeft, pLeft + id-1);
    }

    if (pLeft+id != pRight && pLeft+id != pRight-1) { // if (pLeft+id >= pRight-1), 说明右边已经排好了
        QuickSort(pLeft + id + 1, pRight);
    }
}

int main() {
    /*
    std::vector<int> numbers = {5, 2, 6, 12, 4, 9, 3, 27};
    int N = numbers.size();

//    for (int i = 0; i < N; ++i) {
//        for (int j = 0; j < N - 1 - i; ++j) {
//            if (numbers[j] > numbers[j+1]) {
//                int temp = numbers[j];
//                numbers[j] = numbers[j+1];
//                numbers[j+1] = temp;
//            }
//        }
//    }
//
//    for (int num : numbers) {
//        cout << num << " ";
//    }
//    cout << endl;

    int key = numbers[0];
    int left = 0;
    int right = 0;
    for (int i = 0; i < N;) {
        if (numbers[i] > key) {
            left = numbers[i];
        }

        for (int j = N; j > i; --j) {
            if (numbers[j] < key) {
                right = numbers[j];
            }
        }
    }
    */

    int arr[] = {13, 11, 26, 5, 1, 15, 10, 14, 20, 9};
//    cout << "size of arr =    " << sizeof(arr) << endl;
//    cout << "size of arr[0] = " << sizeof(arr[0]) << endl;
    int k = sizeof(arr) / sizeof(arr[0]);
//    cout << "arr = " << arr[0] << endl;
//    cout << "arr+k = " << (arr+k-1)[0] << endl;
    QuickSort(arr, arr + k - 1);

    cout << "after all,\n" << endl;
    for (int i = 0; i < k; ++i) {
        cout << arr[i] << " ";
    }

}