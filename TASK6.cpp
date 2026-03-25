#include <iostream>
#include <string>
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
            cout << "Package " << value << " has been added to queue" << endl;
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
            cout << "Package " << value << " has been delivered and removed" << endl;
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
            cout << "Packages in queue:" << endl;
            for (int i = 0; i < count; i++) {
                cout << queue[(frontPos + i) % size] << endl;
            }
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

    myQueue<string> deliveryQueue(20);

    int choice;
    string pkgInfo;
    int currentTime, startTime, endTime;

    while (true) {
        cout << endl << "---------- PACKAGE DELIVERY SYSTEM ----------" << endl;
        cout << "1. Add new package" << endl;
        cout << "2. Deliver package (dequeue)" << endl;
        cout << "3. View front package" << endl;
        cout << "4. Display all packages" << endl;
        cout << "5. Check delivery time window" << endl;
        cout << "6. Exit" << endl;
        cout << endl;
        cout << "Enter your choice (1-6): ";

        cin >> choice;

        if (choice == 1) {
            if(deliveryQueue.isFull()) {
                cout << "Delivery queue is full! Cannot add more packages" << endl;
            }
            else {
                int pkgId;
                string address;
                cout << "Enter package ID: ";
                cin >> pkgId;
                cout << "Enter delivery address: ";
                cin >> address;
                cout << "Enter delivery time window start (hour 0-23): ";
                cin >> startTime;
                cout << "Enter delivery time window end (hour 0-23): ";
                cin >> endTime;

                pkgInfo = "ID: " + to_string(pkgId) + ", Address: " + address + ", Time: " + to_string(startTime) + "-" + to_string(endTime);
                deliveryQueue.enQueue(pkgInfo);
            }
        }

        else if (choice == 2) {
            deliveryQueue.deQueue();
        }

        else if (choice == 3) {
            if (!deliveryQueue.isEmpty()) {
                string frontPkg = deliveryQueue.front();
                cout << "Front package: " << frontPkg << endl;
            }
        }

        else if (choice == 4) {
            deliveryQueue.display();
            cout << "Total packages: " << deliveryQueue.getCount() << endl;
        }

        else if (choice == 5) {
            cout << "Enter current time (hour 0-23): ";
            cin >> currentTime;
            
            if (deliveryQueue.isEmpty()) {
                cout << "No packages to deliver" << endl;
            }
            else {
                string frontPkg = deliveryQueue.front();
                
                if (currentTime >= startTime && currentTime <= endTime) {
                    cout << "Package can be delivered within time window" << endl;
                }
                else if (currentTime < startTime) {
                    cout << "Package delivery window has not started yet" << endl;
                }
                else {
                    cout << "Package has expired! Time window passed" << endl;
                    cout << "Skipping to next package..." << endl;
                    deliveryQueue.deQueue();
                }
            }
        }

        else if (choice == 6) {
            cout << "Exiting..." << endl;
            break;
        }

        else {
            cout << "Invalid choice! Please try again." << endl;
        }

    }
}
