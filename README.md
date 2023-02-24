# arduino(HITSZ   大一实验项目)



> 实践是检验真理的唯一标准



### 1.关于本实验

- 本实验是HITSZ自动化专业的大一课设项目
- 本实验的最终目的是造出一辆能够自动巡线, 附带可抓取物体机械臂的DIY小车



### 2. 个人程序模块介绍

#### **Auto_car**

- detect.h   ----电压检测模块
- servo.h  ----舵机模块
- setup.h  ----常数,引脚等初始化模块
- pidControl.h  ----pid调速+红外循迹算法
- sketch_feb13a.ino  ----主程序
- pid_test.ipynb  ----基于matplotlib的简单pid可视化工具



### 3. 个人在调车过程中所遇到的一些问题及解决方法



- *Q.1*  pid调速过程中pwm输出若大于128,电机不受控制全速转动;若小于128,电机不转
- *A.1*  arduino输出pwm口接线错误, 板子只有某些特殊口能输出模拟pwm, 需调整接线



- *Q.2* 接线正确,但是小车跑起来原地打转
- *A.2*  L298N的IN口接反, 可以在程序中将两口调换



- *Q.3* 小车放在黑线上停止, 拿起转动
- *A.3* 将红外循迹模块中的digitalRead() == LOW改成HIGH即可, 具体原理笔者也很迷惑, 该处于实验书中所表述完全相反



- *Q.4* 小车过不了直角弯
- *A.4* 当最外侧的红外模块被触发时先将小车的两轮反向, 再转弯



### 4. 一点补充

截至2022.2.24该程序尚未完工, 本代码并非最终版本, 尚存一些问题有待解决
