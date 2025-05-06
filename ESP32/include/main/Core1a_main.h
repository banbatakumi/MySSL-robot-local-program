#ifndef _CORE1A_MAIN_H_
#define _CORE1A_MAIN_H_

#include "setup.h"

#define CORE1A_CONTROL_FREQ 500  // Hz

void Core1a_setup() {
      Serial2.begin(115200, SERIAL_8N1, 16, 17);
}

void Core1a_loop() {
      // UART送信
      const uint8_t send_byte_num = 9;
      uint8_t send_byte[send_byte_num];
      send_byte[0] = 0xFF;
      send_byte[1] = yaw / 2 + 90;
      send_byte[2] = move_angle / 2 + 90;
      send_byte[3] = move_speed * 100;
      send_byte[4] = face_angle / 2 + 90;
      send_byte[5] = face_speed * 100;
      send_byte[6] = vision_angle / 2 + 90;
      send_byte[7] = (stop << 7) | (do_dribble << 6) | (face_axis << 4) | uint8_t(kick * 0.1);
      send_byte[8] = 0xAA;
      Serial2.write(send_byte, send_byte_num);

      static const uint8_t HEADER = 0xFF;   // ヘッダ
      static const uint8_t FOOTER = 0xAA;   // ヘッダ
      static const uint8_t data_size = 9;   // データのサイズ
      static uint8_t index = 0;             // 受信したデータのインデックスカウンター
      static uint8_t recv_data[data_size];  // 受信したデータ
      static uint8_t recv_byte;
      while (Serial2.available()) {
            recv_byte = Serial2.read();
            if (index == 0) {
                  if (recv_byte == HEADER) {
                        index++;
                  } else {
                        index = 0;
                  }
            } else if (index == (data_size + 1)) {
                  if (recv_byte == FOOTER) {
                        do_rotate = (recv_data[0]) & 1;
                        is_on_line = (recv_data[0] >> 1) & 1;
                        is_hold_ball_back = (recv_data[0] >> 2) & 1;
                        is_hold_ball_front = (recv_data[0] >> 3) & 1;
                        voltage = recv_data[1] / 20.00;
                        moving_dir = recv_data[2] * 2 - 180;
                        moving_speed = recv_data[3] * 0.01;
                        under_yaw = recv_data[4] * 2 - 180;
                        ball_dir = recv_data[5] * 2 - 180;
                        ball_dis = recv_data[6];
                        line_inside_dir = recv_data[7] * 2 - 180;
                        line_depth = recv_data[8];
                  }
                  index = 0;
            } else {
                  recv_data[index - 1] = recv_byte;
                  index++;
            }
      }
}

#endif