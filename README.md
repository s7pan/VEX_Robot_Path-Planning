# VEX Robot Path Planning Lab  
**MTE140 - Algorithms and Data Structures**  
**University of Waterloo**  
**Instructor:** Dr. Charbel Azzi  
**Due:** March 26, 2025  

## Purpose  
This lab implements a fully autonomous path-planning algorithm for a VEX V5 robot, simulating a Mars rover mission. By combining data structures (doubly linked lists) with real-time sensor feedback (IMU and distance sensor), students gain hands-on experience in dynamic memory management, obstacle avoidance strategies, and control logic design.

## Detailed Overview  
The robot must travel from a start coordinate of **(0,0)** to a goal of **(18,18)** on a grid. Along the way, it detects obstacles within a 4 cm threshold and dynamically recalculates its path. Key components include:

1. **Waypoint Management**  
   - Uses a doubly linked list (DLL) to store up to 10 waypoint nodes.  
   - Critical nodes (START, TURN, OBSTACLE) are preserved when pruning.
2. **Movement Strategy**  
   - Prioritizes eastward (X-axis) moves when horizontal distance ≥ vertical distance; otherwise prioritizes northward (Y-axis).  
   - Executes precise 90° turns using IMU angle correction.
3. **Obstacle Handling**  
   - Upon detecting an obstacle within 2 grid units, the robot backs up 3 units, removes non-critical waypoints, and reinserts new waypoints around the obstacle.
4. **Memory & Resource Management**  
   - Implements DLL operations (insert, delete, prune) in `DoublyLinkedList.hpp`.  
   - Ensures no memory leaks via proper destructor behavior.

## File Structure  
```
VEX_Robot_Path-Planning/
├── src/
│   ├── DoublyLinkedList.hpp    # DLL class and operations
│   ├── PathPlanner.cpp         # Core navigation and obstacle logic
│   └── main.cpp                # Robot initialization and execution loop
├── docs/
│   ├── Project_Requirements.pdf # Lab specification and grading rubric
│   └── Demo_Output.txt         # Sample console output of node list
└── README.md                   # This documentation
```

## Hardware & Software Setup
1. **VEX V5 Components**  
   - Left motor: Port 1  
   - Right motor: Port 2  
   - Inertial sensor (IMU): Port 3  
   - Distance sensor: Port 4  
2. **Software**  
   - VEXcode V5 (or PROS) installed  
   - C++17 compatible compiler  

## Installation & Execution
```bash
# Clone the repo
git clone https://github.com/s7pan/VEX_Robot_Path-Planning.git
cd VEX_Robot_Path-Planning/src

# Open in VEXcode V5 or PROS IDE, compile, and upload to the V5 Brain
```  
1. Place the robot on a clear grid surface.  
2. Run the program; the robot will autonomously navigate to (18,18).  
3. Observe console output for waypoint list updates.

## Project Requirements  
Refer to the lab specification for full requirements and grading rubric:  
- [Project Requirements (PDF)](docs/MTE140%20Robot%20Path%20Planning%20Lab.pdf)

## Challenges & Solutions
| Challenge            | Solution                                        |
|----------------------|-------------------------------------------------|
| IMU drift            | Applied angle correction: `turnAngle = 90 - imu.angle()` |
| Memory leaks         | DLL destructor cleans up all nodes              |
| False obstacle alarm | Set detection threshold to 4 cm                 |
| List overflow        | `removeRegularNodes()` prunes non-critical waypoints |

## Future Improvements
- Implement A* or D* path-planning for optimal routes  
- Add grid mapping and SLAM capabilities  
- Visualize path in real time via V5 Brain screen  

## License
MIT License  

Copyright (c) 2025 s7pan  

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

