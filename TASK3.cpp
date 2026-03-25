#include <iostream>
#include <stack>
using namespace std;

class Queue {
private:
    int* arr;
    int frontPos;
    int rearPos;
    int maxCap;
    int count;

public:
    Queue(int max = 100) {
        maxCap = max;
        arr = new int[maxCap];
        frontPos = 0;
        rearPos = -1;
        count = 0;
    }

    ~Queue() {
        delete[] arr;
    }

    void enqueue(int val) {
        if (count == maxCap) {
            return;
        }
        rearPos = (rearPos + 1) % maxCap;
        arr[rearPos] = val;
        count++;
    }

    void dequeue() {
        if (count == 0) {
            return;
        }
        frontPos = (frontPos + 1) % maxCap;
        count--;
    }

    int front() {
        if (count == 0) {
            return -1;
        }
        return arr[frontPos];
    }

    bool isEmpty() {
        return count == 0;
    }

    int getSize() {
        return count;
    }

    void display() {
        if (count == 0) {
            cout << "Queue is empty" << endl;
            return;
        }
        for (int i = 0; i < count; i++) {
            cout << arr[(frontPos + i) % maxCap] << " ";
        }
        cout << endl;
    }
};

void reverseFirstK(Queue& q, int k) {
    if (k <= 1 || q.isEmpty()) {
        return;
    }

    int n = q.getSize();
    
    if (k > n) {
        k = n;
    }

    stack<int> s;
    for (int i = 0; i < k; i++) {
        s.push(q.front());
        q.dequeue();
    }

    while (!s.empty()) {
        q.enqueue(s.top());
        s.pop();
    }

    for (int i = 0; i < n - k; i++) {
        q.enqueue(q.front());
        q.dequeue();
    }
}

int main() {
    Queue q;
    int n, k, val;

    cout << "Enter number of elements: ";
    cin >> n;

    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++) {
        cin >> val;
        q.enqueue(val);
    }

    cout << "Queue: ";
    q.display();

    cout << "K = ";
    cin >> k;

    reverseFirstK(q, k);

    cout << "Output: ";
    q.display();
}
