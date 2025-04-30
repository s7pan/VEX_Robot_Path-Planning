#include "PathPlanner.cpp"

int main() {
    // IMU Calibration
    inertial imu;
    imu.calibrate();
    waitUntil(!imu.isCalibrating());

    // Motor Setup
    motor left_motor = motor(PORT1);
    motor right_motor = motor(PORT2);
    left_motor.setVelocity(10, rpm);
    right_motor.setVelocity(10, rpm);

    // Initial Turn to 180 degrees
    left_motor.spinFor(forward, 90, degrees);
    right_motor.spinFor(reverse, 90, degrees);

    // Start Path Planning
    PathPlanner planner;
    planner.planPath();

    return 0;
}
