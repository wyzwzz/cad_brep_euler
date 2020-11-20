# cad_brep_euler
##brep and euler operation

**CAD三维建模期末Project**

***王银沼 22021071***

使用cmake进行环境配置

有在linux环境下编译好的放在cmake-build-debug和cmake-build-release目录下

***window环境下没有编译过，尽量使用最新版gcc编译...***

**关于程序控制：**
 * L键用于切换线框模式和shader模式
 * -> 用于切换当前绘制的实体
 * Q和E控制相机上下
 * W和S控制相机前后
 * A和D控制相机左右
 * 鼠标控制相机朝向
 * 按Esc退出程序
 
 **关于带环Polygon的绘制，使用了poly2tri这个第三方库，可以将一个简单的带环多边形转换为多个三角形**
 
 **绘制框架采用glfw+glad**
 
 **一些绘制结果放在results文件夹当中**
 
