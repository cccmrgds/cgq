#include <ModbusMaster.h>

// 定义 Modbus 主机对象
ModbusMaster node;

// 设置串口
#define MAX485_DE     9    // 控制 MAX485 芯片的驱动方向（连接到 Arduino 的 9 号引脚）
#define MAX485_RE     8    // 控制 MAX485 芯片的接收方向（连接到 Arduino 的 8 号引脚）

void preTransmission() {
  digitalWrite(MAX485_RE, 1);  // 设置 RE 引脚为高（接收模式）
  digitalWrite(MAX485_DE, 1);  // 设置 DE 引脚为高（发送模式）
}

void postTransmission() {
  digitalWrite(MAX485_RE, 0);  // 设置 RE 引脚为低（接收模式）
  digitalWrite(MAX485_DE, 0);  // 设置 DE 引脚为低（停止发送）
}

void setup() {
  // 启动串口通信
  Serial.begin(9600);
  
  // 设置 MAX485 控制引脚
  pinMode(MAX485_RE, OUTPUT);
  pinMode(MAX485_DE, OUTPUT);
  digitalWrite(MAX485_RE, 0);  // 设置为接收模式
  digitalWrite(MAX485_DE, 0);  // 设置为接收模式
  
  // 设置 Modbus RTU 设备地址
  node.begin(1, Serial);  // 设备地址为 1
  
  // 设置预传输和后传输函数
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);
  
  delay(500);  // 稍作延迟，确保设备初始化完成
}

void loop() {
  uint8_t result;
  uint16_t data[2];  // 用于存储读取的寄存器值
  
  // 一次性读取两个寄存器（0x15 和 0x16）
  result = node.readHoldingRegisters(0x15, 2);  // 从寄存器 0x15 开始读取 2 个寄存器
  if (result == node.ku8MBSuccess) {
    uint16_t highByte = node.getResponseBuffer(0);  // 获取高字节（寄存器 0x15）
    uint16_t lowByte = node.getResponseBuffer(1);   // 获取低字节（寄存器 0x16）
    uint16_t combinedValue = (highByte << 8) + lowByte;  // 组合高字节和低字节
    float distance = combinedValue / 10000.0;  // 转换为实际距离值
    Serial.print("距离: ");
    Serial.print(distance,4);
    Serial.println(" 米");
  } else {
    Serial.print("读取寄存器失败，错误代码：");
    Serial.println(result);
  }

  delay(25);  // 延迟 25 毫秒以控制读取频率
}