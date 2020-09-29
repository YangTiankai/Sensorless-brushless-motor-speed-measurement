# Sensorless-brushless-motor-speed-measurement
使用电压比较器处理相电压的方法，测量四轴无人机无感无刷电机的转速，包含PCB和STM32源码，可以测量8路方波输入。输入端串联RC高通滤波器，可以处理有感无刷电机的霍尔传感器的转速反馈。


使用了另一个项目的STM32F405核心板  
https://github.com/YangTiankai/STM32F4-Core-Board


# 系统结构

![系统结构](https://github.com/YangTiankai/Sensorless-brushless-motor-speed-measurement/blob/master/readmefile/sysstrc.png)

# 原理图和PCB


![SCH1](https://github.com/YangTiankai/Sensorless-brushless-motor-speed-measurement/blob/master/readmefile/SCH1.png)

![SCH2](https://github.com/YangTiankai/Sensorless-brushless-motor-speed-measurement/blob/master/readmefile/SCH1.png)

![SCH3](https://github.com/YangTiankai/Sensorless-brushless-motor-speed-measurement/blob/master/readmefile/SCH1.png)

![PCB1](https://github.com/YangTiankai/Sensorless-brushless-motor-speed-measurement/blob/master/readmefile/PCB1.png)

![PCB2](https://github.com/YangTiankai/Sensorless-brushless-motor-speed-measurement/blob/master/readmefile/PCB2.png)


# 测速原理
对于有12个线圈的无感电机，电机每转动一圈三相线上电压产生7个周期的正弦，将其输入电压比较器即可转化为数字方波，测量其频率可知转速。

对于有感电机，电机每转动一圈霍尔线上也是产生7个周期的正弦信号，但是该信号为恒正，使用一个10uF、10kΩ的RC高通滤波器将去基频，即可得到零均正弦信号，输入电压比较器测量频率即可。





