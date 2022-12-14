
#include "Arduino.h"
#include "ODriveArduino.h"

// Print with stream operator
template<class T> inline Print& operator <<(Print& obj, T arg) { obj.print(arg);    return obj; }
template<>        inline Print& operator <<(Print& obj, float arg) { obj.print(arg, 4); return obj; }

ODriveArduino::ODriveArduino(Stream& serial)
    : serial_(serial) {}

void ODriveArduino::setPosition(int motor_number, float position, float velocity_feedforward, float torque_feedforward) {
    this->serial_ << "p " << motor_number << " " << position << " " << velocity_feedforward << " " << torque_feedforward << "\n";
}


void ODriveArduino::setVelocity(int motor_number, float velocity, float torque_feedforward) {
    this->serial_ << "v " << motor_number << " " << velocity << " " << torque_feedforward << "\n";
}

void ODriveArduino::setTorque(int motor_number, float torque) {
    this->serial_ << "c " << motor_number << " " << torque << "\n";
}

void ODriveArduino::setSimplePosition(int motor_number, float position) {
    this->serial_ << "t " << motor_number << " " << position << "\n";
}

float ODriveArduino::readFloat() {
    return readString().toFloat();
}

float ODriveArduino::getVelocity(int motor_number) {
    this->serial_ << "r axis" << motor_number << ".encoder.vel_estimate\n";
    return ODriveArduino::readFloat();
}

float ODriveArduino::getPosition(int motor_number) {
    this->serial_ << "r axis" << motor_number << ".encoder.pos_estimate\n";
    return ODriveArduino::readFloat();
}

int32_t ODriveArduino::readInt() {
    return readString().toInt();
}

bool ODriveArduino::runState(int axis, int requested_state, bool wait_for_idle, float timeout) {
    int timeout_ctr = (int)(timeout * 10.0F);
    this->serial_ << "w axis" << axis << ".requested_state " << requested_state << '\n';
    if (wait_for_idle) {
        do {
            delay(100);
            this->serial_ << "r axis" << axis << ".current_state\n";
        } while (readInt() != AXIS_STATE_IDLE && --timeout_ctr > 0);
    }

    return timeout_ctr > 0;
}

String ODriveArduino::readString() {
    String str = "";
    static const uint32_t timeout = 1000;
    uint32_t timeout_start = millis();
    for (;;) {
        while (!this->serial_.available()) {
            if (millis() - timeout_start >= timeout) {
                return str;
            }
        }
        char c = this->serial_.read();
        if (c == '\n') {
            break;
        }
        str += c;
    }
    return str;
}
