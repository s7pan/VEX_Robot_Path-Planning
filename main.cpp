#include <iostream>
#include "vex.h" // Ensure this includes the VEX Robotics API

using namespace std;
using namespace vex;

brain Brain;
motor left_motor(PORT1, false);
motor right_motor(PORT6, true);
inertial imu = inertial();
vex::distance DistanceSensor(PORT7); // Distance sensor
drivetrain Drivetrain(left_motor, right_motor, 200, 320, 40, mm, 1);

// Node structure for doubly linked list
struct Node {
    int x, y;
    bool isNecessary;
    Node* prev;
    Node* next;

    Node(int xPos, int yPos, bool necessary) {
        x = xPos;
        y = yPos;
        isNecessary = necessary;
        prev = nullptr;
        next = nullptr;
    }
};

// Doubly Linked List for Path Storage
class DoublyLinkedList {
private:
    Node* head;
    Node* tail;
    int size;
    int capacity;

public:
    DoublyLinkedList(int cap = 10) {
        head = nullptr;
        tail = nullptr;
        size = 0;
        capacity = cap;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void insert(int x, int y, bool isNecessary) {
        Node* newNode = new Node(x, y, isNecessary);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;

        if (size > capacity) {
            removeUnnecessaryNodes();
        }
    }

    void removeUnnecessaryNodes() {
        Node* current = head;
        while (current && size > capacity) {
            if (!current->isNecessary) {
                Node* toDelete = current;
                current = current->next;
                if (toDelete == head) head = head->next;
                if (toDelete == tail) tail = tail->prev;
                if (toDelete->prev) toDelete->prev->next = toDelete->next;
                if (toDelete->next) toDelete->next->prev = toDelete->prev;
                delete toDelete;
                size--;
            } else {
                current = current->next;
            }
        }
    }

    void print() {
        Node* current = head;
        while (current) {
            cout << "(" << current->x << ", " << current->y << ")";
            if (current->isNecessary) cout << " [Necessary]";
            cout << " -> ";
            current = current->next;
        }
        cout << "NULL" << endl;
    }
};

// Function to calibrate IMU
void cali_inertial() {
    left_motor.setVelocity(15, rpm);
    right_motor.setVelocity(15, rpm);

    imu.calibrate();
    while (imu.isCalibrating()) {}

    wait(1, seconds);
    Drivetrain.turn(turnType::right);
    wait(400, msec);

    while (imu.angle(degrees) < 166.0) {}

    Drivetrain.stop(brake);
    wait(1, seconds);
}

// Function to check for obstacles
bool detectObstacle() {
    double dist = DistanceSensor.objectDistance(mm);
    cout << "Distance Sensor Reading: " << dist << " mm" << endl;
    return (dist > 0 && dist <= 40); // Check for valid distance
}

// Path Planning Algorithm
void pathPlanning(DoublyLinkedList &path) {
    int x = 0, y = 0;
    int targetX = 18, targetY = 18;

    cali_inertial(); // Step 1: IMU Calibration

    path.insert(x, y, true); // Insert starting position

    while (x != targetX || y != targetY) {
        bool moved = false;

        // Movement Priority
        if (abs(x - targetX) > abs(y - targetY)) {
            // Move East first
            if (!detectObstacle()) {
                x++;
                Drivetrain.driveFor(vex::fwd, 20, mm);
                moved = true;
            }
        } else {
            // Move North
            if (!detectObstacle()) {
                y++;
                Drivetrain.driveFor(vex::fwd, 20, mm);
                moved = true;
            }
        }

        // If movement was successful, insert into path
        if (moved) {
            path.insert(x, y, false);
            cout << "Moved to: (" << x << ", " << y << ")\n";
        } else {
            // Obstacle detected, turn and move 3-4 units away
            cout << "Obstacle detected! Turning...\n";
            Drivetrain.turn(turnType::right);
            wait(500, msec);
            for (int i = 0; i < 4; i++) {
                x++; // Move away from the obstacle
                path.insert(x, y, true);
                Drivetrain.driveFor(vex::fwd, 20, mm);
                wait(200, msec);
            }
        }

        wait(500, msec);
    }

    cout << "Destination Reached!\n";
    path.print();
}

// Main Function
int main() {
    DoublyLinkedList path(10);
    pathPlanning(path);
    return 0;
}