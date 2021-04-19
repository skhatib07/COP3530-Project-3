
#include <iostream>
#include "MinHeap.h"
#include "OrderedMap.h"

void selectionSort(vector<pair<float, string>> &arr, int n)
{
    int i, j, min_idx;

    // One by one move boundary of unsorted subarray 
    for (i = 0; i < n - 1; i++)
    {
        // Find the minimum element in unsorted array 
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j].first < arr[min_idx].first)
                min_idx = j;

        // Swap the found minimum element with the first element
        pair<float, string> temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

int main()
{
        //int tim = 45134135;
        //MinHeap* r = new MinHeap();
        OrderedMap* f = new OrderedMap();
        vector<pair<float, string>> myVector;
        srand((unsigned)time(NULL));
        int a = rand() % 20 + 1; //1 to 20    
        //cout << "Unsorted Heap" << endl;
        for (int i = 0; i < 100; i++) {
            float b = rand() % 20 + 1;
            myVector.push_back(make_pair(b,"Home depot"));
            //cout << myVector.at(i) << endl;
        }

        //r->insert(myVector);
        f->insert(myVector);
        selectionSort(myVector,myVector.size());
        
        /*
        for (int i = 0; i < myVector.size(); i++) {
            if (myVector.at(i).first == r->pop().first)
                ;
            else {
                cout << "Vectors do not match" << endl;
                return -1;
            }
        }
        cout << "Vectors match" << endl;
        */

        vector<Node*> map = f->inorderVector();
        for (Node* i : map) {
            cout << i->key() << endl;
        }
        //tim += 2414;
    return 0;
}