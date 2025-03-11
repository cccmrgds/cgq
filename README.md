# cgq
激光测距传感器
Modbus RTU 读取距离传感器数据 - Arduino 示例
本示例演示如何使用 Arduino 通过 Modbus RTU 协议读取距离传感器的数据，并将结果通过串口打印出来。代码使用了 ModbusMaster 库来实现 Modbus 通信，并通过 MAX485 芯片进行 RS485 通信。

硬件要求
Arduino 开发板（如 Arduino Uno）

距离传感器（支持 Modbus RTU 协议）（详情请看说明书）

MAX485 模块（用于 RS485 通信）

连接线

接线说明
以下是 Arduino 与 MAX485 模块的接线方式：

Arduino 引脚	MAX485 模块引脚	说明
3.3V	  VCC	  提供电源
GND	    GND	  接地
RX (0)	RO	  接收数据（MAX485 输出）
TX (1)	DI	  发送数据（MAX485 输入）
8	      RE	  接收使能（低电平有效）
9	      DE	  发送使能（高电平有效）

MAX485 模块与传感器的连接：
MAX485 模块引脚	传感器引脚	说明
A	黄线	RS485 A 信号线
B	绿线	RS485 B 信号线

传感器连接15~30v直流电源

代码说明
Modbus 通信设置：

使用 ModbusMaster 库初始化 Modbus 通信。

设置设备地址为 1（根据实际设备地址调整）。

通过 preTransmission 和 postTransmission 函数控制 MAX485 的发送和接收模式。

读取寄存器：

从寄存器 0x15 和 0x16 读取数据，并将其组合为一个 16 位值。

将读取的值转换为实际距离（假设单位为米）。

串口输出：

将计算后的距离值通过串口打印出来。

运行步骤
按照接线说明连接硬件。

将代码上传到 Arduino。

打开 Arduino IDE 的串口监视器（波特率设置为 9600）。

观察串口输出的距离值。

注意事项
确保距离传感器的 Modbus 地址与代码中的地址一致。

如果通信失败，请检查接线是否正确，并确认设备的 Modbus 寄存器地址和协议。

根据实际传感器的数据格式，调整寄存器读取和数据处理逻辑。

依赖库
ModbusMaster：用于 Modbus RTU 通信的 Arduino 库。
