#include <iostream>
using namespace std;

class TicketQueue {
private:
    int* tickets;
    int frontPos;
    int rearPos;
    int maxTickets;
    int count;

public:
    TicketQueue(int maxTickets = 100) {
        this->maxTickets = maxTickets;
        tickets = new int[maxTickets];
        frontPos = 0;
        rearPos = -1;
        count = 0;
    }

    ~TicketQueue() {
        delete[] tickets;
    }

    void addTicket(int ticketId) {
        if (count == maxTickets) {
            cout << "Queue full! Can't add more tickets." << endl;
            return;
        }
        rearPos = (rearPos + 1) % maxTickets;
        tickets[rearPos] = ticketId;
        count++;
        cout << "Ticket " << ticketId << " added successfully." << endl;
    }

    void resolveTicket() {
        if (count == 0) {
            cout << "No tickets in queue. Nothing to resolve." << endl;
            return;
        }
        cout << "Ticket " << tickets[frontPos] << " has been resolved." << endl;
        frontPos = (frontPos + 1) % maxTickets;
        count--;
    }

    int checkNext() {
        if (count == 0) {
            cout << "Queue is empty." << endl;
            return -1;
        }
        return tickets[frontPos];
    }

    bool checkEmpty() {
        return count == 0;
    }

    int getCount() {
        return count;
    }

    void showAll() {
        if (count == 0) {
            cout << "No pending tickets right now." << endl;
            return;
        }
        cout << "Tickets waiting: ";
        for (int i = 0; i < count; i++) {
            cout << tickets[(frontPos + i) % maxTickets] << " ";
        }
        cout << endl;
        cout << "Total: " << count << " tickets" << endl;
    }
};

int main() {
    TicketQueue tq;
    int option, tid;

    while (true) {
        cout << endl;
        cout << "----- Support Ticket System -----" << endl;
        cout << "1. Create new ticket" << endl;
        cout << "2. Resolve a ticket" << endl;
        cout << "3. View next ticket" << endl;
        cout << "4. Show all tickets" << endl;
        cout << "5. Quit" << endl;
        cout << "Choose option: ";
        cin >> option;

        if (option == 1) {
            cout << "Enter ticket ID (4 digits): ";
            cin >> tid;
            if (tid < 1000 || tid > 9999) {
                cout << "Error: ID must be 4 digits!" << endl;
            } else {
                tq.addTicket(tid);
            }
        } else if (option == 2) {
            tq.resolveTicket();
        } else if (option == 3) {
            int next = tq.checkNext();
            if (next != -1) {
                cout << "Next ticket: " << next << endl;
            }
        } else if (option == 4) {
            tq.showAll();
        } else if (option == 5) {
            cout << "System closed." << endl;
            break;
        } else {
            cout << "Wrong option. Try again." << endl;
        }
    }
}
