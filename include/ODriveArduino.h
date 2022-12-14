
#ifndef ODRIVE_ARDUINO_H
#define ODRIVE_ARDUINO_H

#include "Arduino.h"
#include "ODriveEnums.h"
class ODriveArduino {
private:
    /**
     * @brief The serial port to use for communication with the ODrive.
     *
     */
    Stream& serial_;

    /**
     * @brief Read a response from the ODrive in serial.
     * @return The response as a String.
     */
    String readString();

public:
    /**
     * @brief Construct a new ODriveArduino object
     *
     * @param[in] serial The serial port to use to communicate with the ODrive
     */
    ODriveArduino(Stream& serial);

    /**
     * @brief Set the Position of a motor
     * For general moving around of the axis, this is the recommended command.
     * This command updates the watchdog timer for the motor.
     * @param motor_number is the motor number, 0 or 1.
     * @param position is the goal position, in [turns].
     */
    void setSimplePosition(int motor_number, float position);


    /**
     * @brief Set the Position of a motor with a given velocity and torque
     * Note that if you don’t know what feed-forward is or what it’s used for, simply omit it.
     * This command updates the watchdog timer for the motor.
     * @param[in] motor_number is the motor number, 0 or 1
     * @param[in] position is the desired position, in [turns].
     * @param[in] velocity_feedforward is the velocity limit, in [turns/s] (optional)
     * @param[in] torque_feedforward is the torque limit, in [Nm] (optional)
     */
    void setPosition(int motor_number, float position, float velocity_feedforward = 0.0f, float torque_feedforward = 0.0f);

    /**
     * @brief Set the Velocity of a motor
     * Note that if you don’t know what feed-forward is or what it’s used for, simply omit it.
     * This command updates the watchdog timer for the motor.
     * @param[in] motor_number is the motor number, 0 or 1.
     * @param[in] velocity is the desired velocity in [turns/s].
     * @param[in] torque_feedforward is the torque feed-forward term, in [Nm] (optional).
     */
    void setVelocity(int motor_number, float velocity, float torque_feedforward = 0.0f);

    /**
     * @brief Set the torque of a motor
     * This command updates the watchdog timer for the motor.
     * @param motor_number is the motor number, 0 or 1.
     * @param torque is the desired torque in [Nm].
     */
    void setTorque(int motor_number, float torque);

    /**
     * @brief Get the Velocity of a motor
     *
     * @param[in] motor_number The motor to get the velocity of
     * @return float The velocity of the motor
     */
    float getVelocity(int motor_number);

    /**
     * @brief Get the Position of a motor
     *
     * @param[in] motor_number The motor to get the position of
     * @return float The position of the motor
     */
    float getPosition(int motor_number);


    /**
     * @brief get the response value in float
     *
     * @return float The response value
     */
    float readFloat();

    /**
     * @brief get the response value in int
     *
     * @return int The response value
     */
    int32_t readInt();

    /**
     * @brief change the axis state of a motor
     * of more info check https://docs.odriverobotics.com/api/odrive.axis.axisstate
     * @param[in] axis is the motor number, 0 or 1.
     * @param[in] requested_state one of the states defined in ODriveEnums.h
     * @param[in] wait_for_idle if true, wait for the state to be reached.
     * @param[in] timeout is the timeout in milliseconds (optional) *default 10*.
     * @return true the state was reached within the timeout.
     * @return false the state was not reached within the timeout.
     */
    bool runState(int axis, int requested_state, bool wait_for_idle, float timeout = 10.0f);
};

#endif  // ODRIVE_ARDUINO_H
