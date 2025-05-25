#ifndef _SETUP_H_
#define _SETUP_H_

#include <ArduinoJson.h>  // JSON パース・シリアライズ用
#include <WiFi.h>
#include <WiFiUdp.h>

#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "WiFi.h"
#include "Wire.h"
#include "ir.h"
#include "motor.h"
#include "pid.h"
#include "simplify_deg.h"

#define ROBOT_1

// ピン定義
const uint8_t led_pin = 23;
const uint8_t ir_led_pin[4] = {4, 5, 18, 19};

Ir ir(12, 14, 27, 26, 25, 2, 15, 13);
Motor motor(32, 33);
MPU6050 mpu;
PID motorPID;

// MPU control/status vars
uint8_t devStatus;       // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;     // expected DMP packet size (default is 42 bytes)
uint8_t fifoBuffer[64];  // FIFO storage buffer

// orientation/motion vars
Quaternion q;         // [w, x, y, z]         quaternion container
VectorFloat gravity;  // [x, y, z]            gravity vector
float ypr[3];         // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

float yaw_correction;  // yaw軸の補正値
int16_t yaw;

bool is_connect;

// メインマイコンから受け取るデータ
bool do_rotate;

float voltage;
int16_t moving_dir;
float moving_speed;
int16_t ball_dir;
uint8_t ball_dis;
bool is_hold_ball_front;
bool is_hold_ball_back;
bool is_on_line;
int16_t line_inside_dir;
uint8_t line_depth;
int16_t under_yaw;

int16_t move_angle;
float move_speed;
float move_acce;
int16_t face_angle;
float face_speed;
uint8_t face_axis;
uint8_t kick;
bool stop;
uint8_t dribble;
int16_t vision_angle;
#endif