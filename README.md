# VEX Robot Path Planning Lab  
**MTE140 - Algorithms and Data Structures**  
**University of Waterloo**  
**Instructor:** Dr. Charbel Azzi  
**Due:** March 26, 2025  

## Overview
A Mars exploration robot path planner that navigates from **(0,0)** to **(18,18)** while avoiding obstacles. Implements a doubly linked list (DLL) for dynamic waypoint management with capacity constraints (max 10 nodes).

## Key Features
- **Movement Prioritization**  
  - East (X-axis) prioritized when Δx ≥ Δy or equidistant  
  - North (Y-axis) otherwise
- **Obstacle Handling**  
  - Detection at ≤ 2 units (4 cm)  
  - 3‑unit backtracking + path cleanup
- **Node Management**  
  - Automatic deletion of regular nodes during capacity/turning triggers  
  - Critical nodes preserved (START/TURNING/OBJECT)

## File Structure
```
VEX_Robot_Path-Planning/
├── src/
│   ├── DoublyLinkedList.hpp    # Node class, DLL operations
│   ├── PathPlanner.cpp         # Movement logic, obstacle avoidance
│   └── main.cpp                # Robot setup and execution
├── docs/
│   └── Demo_Video.mp4         # Recorded demonstration
└── README.md                   # Project overview and instructions
```

## Hardware Setup
1. **VEX V5 Components**  
   - Motors on ports 1 (left) and 2 (right)  
   - Inertial Measurement Unit (IMU)  
   - Distance sensor for obstacle detection

2. **Initial Configuration**  
```cpp
// In main.cpp
motor left_motor = motor(PORT1);
motor right_motor = motor(PORT2);
inertial imu_sensor = inertial(PORT3);
distance dist_sensor = distance(PORT4);
```

## How to Run

### Dependencies
- VEXcode V5 or PROS Toolkit (optional)

### Upload to Robot
```bash
git clone https://github.com/s7pan/VEX_Robot_Path-Planning.git
# Open in VEXcode or PROS IDE, compile, and upload to V5 Brain
```

### Execution
1. Robot starts at (0,0) facing North.  
2. Follows priority rules to (18,18).  
3. Prints node list to the Brain screen during navigation.

## Challenges & Solutions
| Challenge         | Solution                                   |
|-------------------|--------------------------------------------|
| Memory Leaks      | Destructor deletes all nodes in the DLL    |
| IMU Over-rotation | Angle correction: `90° - imu.angle()`       |
| False Obstacles   | 2‑unit detection threshold (4 cm)          |
| Node Overflows    | `removeRegularNodes()` prunes non-critical nodes |

## Demo Video
A demonstration of the robot navigating from (0,0) to (18,18), showing node updates and obstacle avoidance. See `docs/Demo_Video.mp4`.

## Contributors
- s7pan (@s7pan)

## License
MIT License — see [LICENSE](LICENSE) file

## Topics
lego-v5  ·  vex  ·  path-planning  ·  algorithms  ·  data-structures  ·  cplusplus  ·  robotics  

