# STM32工程模板

## 环境配置

### 必要工具安装
1. **Makefile**
   - 用于控制编译流程
   - 下载地址：[GNU Make](https://www.gnu.org/software/make/)

2. **GNU Arm GCC工具链**
   - ARM交叉编译工具链
   - 下载地址：[GNU Arm Embedded Toolchain](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads/11-2-2022-02)

## 使用说明

### 编译步骤
1. 克隆代码到本地
2. 打开终端并进入项目目录
3. 执行`make`命令进行编译
4. 编译输出文件位于：`/OBJ/[项目名]/main.bin`或`main.hex`

### 自定义项目
- 修改根目录下`Makefile`中的`PROJECT`变量可在`OBJ/`下生成新的项目文件夹

## 项目结构
- 链接脚本：
  - 主要脚本：`stm32R6.ld`
  - 测试脚本：`yj.ld`
- 源代码位置：
  - 库函数：`mo_ban/`目录
  - 主程序：`USER/main.c`
- 仿真项目：
  - 可用于仿真
  - 位置：`/protues`目录
  - 内容：Proteus仿真工程文件