# TouchGFXf429

#### 项目介绍
移植TouchGFX到秉火f429开发板上

#### 软件架构
软件架构说明


#### 安装教程

1. 安装TouchGFX4.9.3
2. 安装Keil 5
3. 安装下载驱动及软件

#### 使用说明

1. 使用TouchGFX生成代码时，选择stm32469平台，选择PC应该也可以没有试过
2. 配置完图形界面后，将根目录下generated和gui文件替换原工程文件，keil添加这两个文件夹下的.cpp，并且添加hpp路径
3. User文件夹内为SDRAM驱动

#### 作者

交流方式 QQ:921380017

#### 平台问题

野火stm32f429内部flash有限，并且没有提供外部扩展flash接口，所以爱好者生成的代码应该小于1M，否者烧录失败。
最好不要添加照片

#### 已知bug

上电开机需要复位，解决方法猜想，液晶屏的复位比芯片的复位慢，所以上电后，芯片给液晶发的指令是错误，后续有时间再修改
