#include <iostream>
using namespace std;

template <typename T>
class AbstractStack {
public:
    virtual void push(T value) = 0;
    virtual T pop() = 0;
    virtual T top() const = 0;
    virtual bool isEmpty() const = 0;
    virtual bool isFull() const = 0;
    virtual ~AbstractStack() {}
};

template <typename T>
class myStack : public AbstractStack<T> {
private:
    T* stack;
    int size;
    int topIndex;

public:

    myStack(int size) : size(size) {
        stack = new T[size];
        topIndex = -1;
    }

    void push(T value) override {
        if (topIndex == size - 1) {
            cout << "Stack is full" << endl;
        }
        else {
            stack[++topIndex] = value;
        }
    }

    T pop() override {
        if (topIndex == -1) {
            cout << "Stack is empty" << endl;
            return T();
        }
        else {
            return stack[topIndex--];
        }
    }

    T top() const override {
        if (topIndex == -1) {
            cout << "Stack is empty" << endl;
            return T();
        }
        else {
            return stack[topIndex];
        }
    }

    bool isEmpty() const override {
        return topIndex == -1;
    }

    bool isFull() const override {
        return topIndex == size - 1;
    }

    ~myStack() override {
        delete[] stack;
    }

};

template <typename T>
class QueueUsingStacks {
private:
    myStack<T> stack1;
    myStack<T> stack2;
    int capacity;

public:

    QueueUsingStacks(int size) : stack1(size), stack2(size) {
        capacity = size;
    }

    void enQueue(T value) {
        if (stack1.isFull()) {
            cout << "Queue is full, value cannot be added" << endl;
        }
        else {
            stack1.push(value);
            cout << value << " has been added to queue" << endl;
        }
    }

    T deQueue() {
        if (stack1.isEmpty() && stack2.isEmpty()) {
            cout << "Queue is empty" << endl;
            return T();
        }
        else {
            if (stack2.isEmpty()) {
                while (!stack1.isEmpty()) {
                    stack2.push(stack1.pop());
                }
            }
            T value = stack2.pop();
            cout << value << " has been removed from queue" << endl;
            return value;
        }
    }

    T front() {
        if (stack1.isEmpty() && stack2.isEmpty()) {
            cout << "Queue is empty" << endl;
            return T();
        }
        else {
            if (stack2.isEmpty()) {
                while (!stack1.isEmpty()) {
                    stack2.push(stack1.pop());
                }
            }
            return stack2.top();
        }
    }

    bool isEmpty() {
        return stack1.isEmpty() && stack2.isEmpty();
    }

    void display() {
        if (isEmpty()) {
            cout << "Queue is empty" << endl;
        }
        else {
            if (stack2.isEmpty()) {
                while (!stack1.isEmpty()) {
                    stack2.push(stack1.pop());
                }
            }
            
            myStack<T> tempStack(capacity);
            while (!stack2.isEmpty()) {
                T value = stack2.pop();
                cout << value << " ";
                tempStack.push(value);
            }
            cout << endl;
            
            while (!tempStack.isEmpty()) {
                stack2.push(tempStack.pop());
            }
        }
    }

};

int main() {

    QueueUsingStacks<int> q(10);

    int choice;
    int value;

    while (true) {
        cout << endl << "---------- QUEUE USING STACKS MENU ----------" << endl;
        cout << "1. EnQueue (Add element)" << endl;
        cout << "2. DeQueue (Remove element)" << endl;
        cout << "3. Front (View front element)" << endl;
        cout << "4. Check if Empty" << endl;
        cout << "5. Display all elements" << endl;
        cout << "6. Exit" << endl;
        cout << endl;
        cout << "Enter your choice (1-6): ";

        cin >> choice;

        if (choice == 1) {
            cout << "Enter value to add: ";
            cin >> value;
            q.enQueue(value);
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
            q.display();
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
