#include "DoublyLinkedList.hpp"

class PathPlanner {
private:
    DoublyLinkedList path;
    int current_x = 0;
    int current_y = 0;
    bool prioritizing_x = true;
    bool obstacle_detected = false;

    bool isDestinationReached() {
        return (current_x == 18 && current_y == 18);
    }

    bool shouldPrioritizeX() {
        int x_dist = 18 - current_x;
        int y_dist = 18 - current_y;
        return (x_dist >= y_dist);
    }

    void moveEast() {
        current_x++;
        path.insert(current_x, current_y, prioritizing_x ? TURNING : REGULAR);
    }

    void moveNorth() {
        current_y++;
        path.insert(current_x, current_y, prioritizing_x ? REGULAR : TURNING);
    }

public:
    void avoidObstacle() {
        // Backtrack 3 units
        for(int i=0; i<3; i++) {
            if(prioritizing_x) current_x--;
            else current_y--;
        }
        path.removeRegularNodes(path.getHead()->prev, path.getTail());
    }

    void planPath() {
        path.insert(0, 0, START);
        
        while(!isDestinationReached()) {
            bool new_priority = shouldPrioritizeX();
            
            if(new_priority != prioritizing_x) {
                prioritizing_x = new_priority;
                path.insert(current_x, current_y, TURNING);
            }

            if(prioritizing_x) moveEast();
            else moveNorth();

            if(path.getSize() >= path.getCapacity()) {
                path.removeRegularNodes(path.getHead(), path.getTail());
            }

            if(checkObstacle()) {
                avoidObstacle();
                prioritizing_x = !prioritizing_x;
            }
            
            path.printNodes();
        }
    }
};
