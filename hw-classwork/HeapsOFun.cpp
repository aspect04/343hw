
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main () {
    cout << "Hello World! " << endl;
    vector<string> vec = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};
    heapsort(vec);
    cout << vec << endl;
    return 0;
}

void heapSortHelper(vector<string> &vec, int i) {
    if (vec.size() <= i) return;
   // if (vec[i] < vec[vec.size() - 1]) {}
    if (vec[i] > vec[2*i+1] && vec[i] > vec[2*i+2]) {
        heapSortHelper(vec,2*i+1);
        heapSortHelper(vec, 2*i+2);
    }
    else if (vec[2*i+1] > vec[2*i+2]) {
        swap(vec[i], vec[2*i+1]);
        heapSortHelper(vec,2*i+1);
        heapSortHelper(vec, 2*i+2);
    }
    else {
        swap(vec[i], vec[2 * i + 2]);
        heapSortHelper(vec,2*i+1);
        heapSortHelper(vec, 2*i+2);
    }
}
void heapSort(vector<string> &vec) {
    int i = 0;
    heapSortHelper(vec, i);
}