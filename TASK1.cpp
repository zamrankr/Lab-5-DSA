#include <iostream>
using namespace std;

template <typename T>
class AbstractQueue {
public:
    virtual void enQueue(T value) = 0;
    virtual T deQueue() = 0;
    virtual T front() const = 0;
    virtual bool isEmpty() const = 0;
    virtual bool isFull() const = 0;
    virtual ~AbstractQueue() {}
};

template <typename T>
class myQueue : public AbstractQueue<T> {
private:
    T* queue;
    int frontPos;
    int rearPos;
    int size;
    int count;

public:

    myQueue(int size) : size(size) {
        queue = new T[size];
        frontPos = 0;
        rearPos = -1;
        count = 0;
    }

    void enQueue(T value) override {
        if (isFull()) {
            cout << "Queue is full, value cannot be added" << endl;
        }
        else {
            rearPos = (rearPos + 1) % size;
            queue[rearPos] = value;
            count++;
            cout << value << " has been added to queue" << endl;
        }
    }

    T deQueue() override {
        if (isEmpty()) {
            cout << "Queue is empty" << endl;
            return T();
        }
        else {
            T value = queue[frontPos];
            frontPos = (frontPos + 1) % size;
            count--;
            cout << value << " has been removed from queue" << endl;
            return value;
        }
    }

    T front() const override {
        if (isEmpty()) {
            cout << "Queue is empty" << endl;
            return T();
        }
        else {
            return queue[frontPos];
        }
    }

    bool isEmpty() const override {
        return count == 0;
    }

    bool isFull() const override {
        return count == size;
    }

    void display() const {
        if (isEmpty()) {
            cout << "Queue is empty" << endl;
        }
        else {
            for (int i = 0; i < count; i++) {
                cout << queue[(frontPos + i) % size] << " ";
            }
            cout << endl;
        }
    }

    ~myQueue() override {
        delete[] queue;
    }

};

int main() {

    myQueue<int> q(10);

    int choice;
    int value;

    while (true) {
        cout << endl << "---------- QUEUE OPERATIONS MENU ----------" << endl;
        cout << "1. EnQueue (Add element)" << endl;
        cout << "2. DeQueue (Remove element)" << endl;
        cout << "3. Front (View front element)" << endl;
        cout << "4. Check if Empty" << endl;
        cout << "5. Check if Full" << endl;
        cout << "6. Display all elements" << endl;
        cout << "7. Exit" << endl;
        cout << endl;
        cout << "Enter your choice (1-7): ";

        cin >> choice;

        if (choice == 1) {
            if(q.isFull()) {
                cout << "Queue is full! Cannot add more elements" << endl;
            }
            else {
                cout << "Enter value to add: ";
                cin >> value;
                q.enQueue(value);
            }
        }

        else if (choice == 2) {
            q.deQueue();
        }

        else if (choice == 3) {
            if (!q.isEmpty()) {
                int frontVal = q.front();
                cout << "Front element: " << frontVal << endl;
            }
        }

        else if (choice == 4) {
            if (q.isEmpty()) {
                cout << "Queue is empty" << endl;
            }
            else {
                cout << "Queue is not empty" << endl;
            }
        }

        else if (choice == 5) {
            if (q.isFull()) {
                cout << "Queue is full" << endl;
            }
            else {
                cout << "Queue is not full" << endl;
            }
        }

        else if (choice == 6) {
            q.display();
        }

        else if (choice == 7) {
            cout << "Exiting..." << endl;
            break;
        }

        else {
            cout << "Invalid choice! Please try again." << endl;
        }

    }
}
