#ifndef _CORE0A_MAIN_H_
#define _CORE0A_MAIN_H_

#include "setup.h"

#define CORE0A_CONTROL_FREQ 250  // Hz

// Wi-Fi 設定
const char* ssid = "asus24";        // << ご自身のWi-Fi SSID に変更 >>
const char* password = "19671202";  // << ご自身のWi-Fi パスワードに変更 >>

// UDP 設定
// PC Controller から指令を受信するポート (robot_controller.py の COMMAND_SEND_PORT と同じ)
const unsigned int commandListenPort = 50008;  // << robot_controller.py と同じにする >>
// PC Controller へセンサーデータを送信するポート (robot_controller.py の SENSOR_LISTEN_PORT と同じ)
const unsigned int sensorSendPort = 50009;  // << robot_controller.py と同じにする >>

// PC Controller の IP アドレス
// robot_controller.py が動作する PC のローカル IP アドレス
const char* controllerIP = "192.168.50.86";  // << <-- ここを PC Controller の実際の IP アドレスに変更 >>
// UDP オブジェクト
WiFiUDP udp;

// 指令受信バッファと JSON ドキュメント
char commandPacket[256];                 // 指令データの最大サイズに応じて調整
StaticJsonDocument<256> commandJsonDoc;  // 指令 JSON のバッファサイズに応じて調整

// センサーデータ JSON ドキュメントと送信バッファ
StaticJsonDocument<256> sensorJsonDoc;  // センサー JSON のバッファサイズに応じて調整
char sensorPacket[256];                 // センサーデータの最大サイズに応じて調整

void Core0a_setup() {  // アクセスポイントモード起動
      WiFi.begin(ssid, password);
      while (WiFi.status() != WL_CONNECTED) {
            delay(1000);
            Serial.println("Connecting...");
      }
      Serial.println("WiFi connected");
      Serial.print("ESP32 IP address: ");
      Serial.println(WiFi.localIP());  // この IP を PC Controller の ESP32_IP に設定

      // UDP 指令待ち受け開始
      udp.begin(commandListenPort);
      Serial.printf("Now listening for commands at IP %s, port %d\n", WiFi.localIP().toString().c_str(), commandListenPort);
}

void Core0a_loop() {
      // --- 指令の受信と処理 ---
      int packetSize = udp.parsePacket();
      if (packetSize) {
            // 受信バッファのクリアと読み込み
            memset(commandPacket, 0, sizeof(commandPacket));  // バッファをクリア
            int len = udp.read(commandPacket, sizeof(commandPacket) - 1);
            commandPacket[len] = 0;  // ヌル終端

            // JSON パース
            DeserializationError error = deserializeJson(commandJsonDoc, commandPacket);

            if (error) {
                  Serial.print(F("deserializeJson() failed for command: "));
                  Serial.println(error.f_str());
            } else {
                  // --- 受信した指令データの利用 ---
                  // 例: 指令値を取り出す
                  if (commandJsonDoc.containsKey("cmd")) {
                        JsonObject cmd = commandJsonDoc["cmd"].as<JsonObject>();

                        if (cmd.containsKey("move_speed")) {
                              move_speed = cmd["move_speed"];
                        }
                        if (cmd.containsKey("move_angle")) {
                              move_angle = cmd["move_angle"];
                        }
                        if (cmd.containsKey("move_acce")) {
                              move_acce = cmd["move_acce"];
                        }
                        if (cmd.containsKey("face_angle")) {
                              face_angle = cmd["face_angle"];
                        }
                        if (cmd.containsKey("face_speed")) {
                              face_speed = cmd["face_speed"];
                        }
                        if (cmd.containsKey("face_axis")) {
                              face_axis = cmd["face_axis"];
                        }
                        if (cmd.containsKey("vision_angle")) {
                              vision_angle = cmd["vision_angle"];
                        }
                        if (cmd.containsKey("stop")) {
                              stop = cmd["stop"];
                        }
                        if (cmd.containsKey("kick")) {
                              kick = cmd["kick"];
                              if (kick > 100) kick = 100;
                        }
                        if (cmd.containsKey("dribble")) {
                              dribble = cmd["dribble"];
                              if (dribble > 100) dribble = 100;
                        }

                        // Serial.print("Received command:");
                        // Serial.print(" move_speed: ");
                        // Serial.print(move_speed);
                        // Serial.print(" move_angle: ");
                        // Serial.print(move_angle);
                        // Serial.print(" face_angle: ");
                        // Serial.print(face_angle);
                        // Serial.print(" stop: ");
                        // Serial.print(stop);
                        // Serial.print(" kick: ");
                        // Serial.print(kick);
                        // Serial.print(" dribble: ");
                        // Serial.print(do_dribble);
                        // Serial.println();
                  }
            }
      }

      // --- センサーデータの取得と送信 ---
      // unsigned long currentTime = millis();

      // --- センサーデータの構造化 ---
      sensorJsonDoc.clear();  // ドキュメントをクリア
      sensorJsonDoc["type"] = "sensor_data";
      // sensorJsonDoc["ts"] = currentTime;  // ESP32側のタイムスタンプ

      // センサーデータの格納
      sensorJsonDoc["voltage"] = voltage;

      JsonObject photo = sensorJsonDoc.createNestedObject("photo");
      photo["front"] = is_hold_ball_front;
      photo["back"] = is_hold_ball_back;

      JsonObject moving = sensorJsonDoc.createNestedObject("moving");
      moving["dir"] = moving_dir;
      moving["speed"] = moving_speed;

      JsonObject line = sensorJsonDoc.createNestedObject("line");
      line["on_line"] = is_on_line;
      line["inside_dir"] = line_inside_dir;
      line["depth"] = line_depth;

      // --- センサーデータの送信 ---
      if (udp.beginPacket(controllerIP, sensorSendPort)) {
            // JSON をシリアライズしてパケットに書き込む
            int bytesSent = serializeJson(sensorJsonDoc, sensorPacket, sizeof(sensorPacket));
            if (bytesSent > 0) {
                  udp.write((uint8_t*)sensorPacket, bytesSent);
                  udp.endPacket();
                  // Serial.printf("Sent sensor data (%d bytes)\n", bytesSent); // デバッグ用
            } else {
                  Serial.println("Failed to serialize sensor JSON.");
            }
      } else {
            Serial.println("Failed to begin UDP packet for sensor data.");  // 頻繁に出る場合はコメントアウト
            // コントローラーPCが起動していない、IPアドレスが間違っているなどの可能性
      }
}
#endif
