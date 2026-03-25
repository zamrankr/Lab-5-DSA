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

    int getCount() const {
        return count;
    }

    ~myQueue() override {
        delete[] queue;
    }

};

int main() {

    myQueue<string> printQueue(20);

    int choice;
    string docName;

    while (true) {
        cout << endl << "---------- PRINTER QUEUE SYSTEM ----------" << endl;
        cout << "1. Add print job" << endl;
        cout << "2. Print document" << endl;
        cout << "3. Check next document" << endl;
        cout << "4. Display all print jobs" << endl;
        cout << "5. Exit" << endl;
        cout << endl;
        cout << "Enter your choice (1-5): ";

        cin >> choice;

        if (choice == 1) {
            if(printQueue.isFull()) {
                cout << "Print queue is full! Cannot add more jobs" << endl;
            }
            else {
                cout << "Enter document name: ";
                cin >> docName;
                printQueue.enQueue(docName);
            }
        }

        else if (choice == 2) {
            printQueue.deQueue();
        }

        else if (choice == 3) {
            if (!printQueue.isEmpty()) {
                string nextDoc = printQueue.front();
                cout << "Next document to print: " << nextDoc << endl;
            }
        }

        else if (choice == 4) {
            cout << "Print jobs in queue: ";
            printQueue.display();
            cout << "Total jobs: " << printQueue.getCount() << endl;
        }

        else if (choice == 5) {
            cout << "Exiting..." << endl;
            break;
        }

        else {
            cout << "Invalid choice! Please try again." << endl;
        }

    }
}
