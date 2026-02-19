[![Actions Status](https://github.com/Vae-Scrooge/SimpleStudentManager/workflows/Ubuntu/badge.svg)](https://github.com/Vae-Scrooge/SimpleStudentManager/actions)
[![Actions Status](https://github.com/Vae-Scrooge/SimpleStudentManager/workflows/Windows/badge.svg)](https://github.com/Vae-Scrooge/SimpleStudentManager/actions)
[![Actions Status](https://github.com/Vae-Scrooge/SimpleStudentManager/workflows/MacOS/badge.svg)](https://github.com/Vae-Scrooge/SimpleStudentManager/actions)
[![Actions Status](https://github.com/Vae-Scrooge/SimpleStudentManager/workflows/Style/badge.svg)](https://github.com/Vae-Scrooge/SimpleStudentManager/actions)
[![Actions Status](https://github.com/Vae-Scrooge/SimpleStudentManager/workflows/Standalone/badge.svg)](https://github.com/Vae-Scrooge/SimpleStudentManager/actions)
[![Actions Status](https://github.com/Vae-Scrooge/SimpleStudentManager/workflows/Install/badge.svg)](https://github.com/Vae-Scrooge/SimpleStudentManager/actions)
[![codecov](https://codecov.io/gh/Vae-Scrooge/SimpleStudentManager/branch/main/graph/badge.svg)](https://codecov.io/gh/Vae-Scrooge/SimpleStudentManager)

# 简单学生成绩管理系统 📚

一个适合计算机专业大一学生学习的 C++ 项目模板。

## 项目简介

这是一个基于 [ModernCppStarter](https://github.com/TheLartians/ModernCppStarter) 简化的 C++ 项目，专门为大一学生设计。通过这个项目，你可以学习到：

- ✅ **CMake 构建系统**：现代 C++ 项目的标准构建工具
- ✅ **面向对象编程**：类、对象、封装的基本概念
- ✅ **单元测试**：如何测试你的代码
- ✅ **项目结构**：规范的 C++ 项目文件组织方式
- ✅ **Git 和 GitHub**：版本控制和代码托管

## 项目功能

- 📝 添加学生（姓名、学号、成绩）
- 🗑️ 删除学生
- 🔍 查询学生信息
- ✏️ 修改学生成绩
- 📊 计算平均分
- 📋 显示所有学生列表

## 环境要求

### 必需工具

| 工具 | 版本要求 | 下载链接 |
|------|---------|---------|
| CMake | 3.14+ | https://cmake.org/download/ |
| C++ 编译器 | 支持 C++17 | 见下方说明 |

### 编译器选择

**Windows 用户（推荐）：**
- **Visual Studio 2019/2022**：安装时勾选"使用 C++ 的桌面开发"
- **MinGW-w64**：https://www.mingw-w64.org/ 或使用 MSYS2

**macOS 用户：**
```bash
xcode-select --install  # 安装 Xcode 命令行工具
```

**Linux 用户：**
```bash
# Ubuntu/Debian
sudo apt update
sudo apt install build-essential cmake

# Fedora
sudo dnf install gcc-c++ cmake
```

## 快速开始

### 1. 克隆项目

```bash
# 使用 HTTPS
git clone https://github.com/你的用户名/SimpleStudentManager.git

# 或使用 SSH（需要先配置 SSH 密钥）
git clone git@github.com:你的用户名/SimpleStudentManager.git

# 进入项目目录
cd SimpleStudentManager
```

### 2. 编译并运行主程序

```bash
# 创建构建目录（不要在源代码目录中构建！）
mkdir build
cd build

# 配置项目
cmake ../standalone

# 编译项目
cmake --build .

# 运行程序
./student_manager        # Linux/macOS
.\student_manager.exe    # Windows
```

### 3. 运行测试

```bash
# 从项目根目录执行
mkdir build-test
cd build-test

# 配置测试项目
cmake ../test

# 编译
cmake --build .

# 运行测试
ctest --output-on-failure
```

## 项目结构

```
SimpleStudentManager/
├── CMakeLists.txt           # 主项目构建配置
├── README.md                # 项目说明文档（本文件）
├── LICENSE                  # 开源许可证（MIT）
├── .gitignore               # Git 忽略文件配置
│
├── include/                 # 头文件目录
│   └── student_manager/
│       └── student_manager.h  # 学生管理类头文件
│
├── source/                  # 源文件目录
│   └── student_manager.cpp    # 学生管理类实现
│
├── standalone/              # 独立可执行程序
│   ├── CMakeLists.txt
│   └── source/
│       └── main.cpp           # 主程序入口
│
├── test/                    # 测试目录
│   ├── CMakeLists.txt
│   └── source/
│       └── student_manager_tests.cpp  # 单元测试
│
└── .github/
    └── workflows/
        └── build.yml        # CI 配置（自动编译测试）
```

## 代码讲解

### 核心类设计

#### Student 类（学生类）

```cpp
class Student {
private:
    std::string name;    // 学生姓名
    std::string id;      // 学号
    double score;        // 成绩

public:
    Student(const std::string& name, const std::string& id, double score);
    
    // 获取信息
    std::string get_name() const;
    std::string get_id() const;
    double get_score() const;
    
    // 修改成绩
    void set_score(double new_score);
};
```

**学习要点：**
- `private` 和 `public` 是访问修饰符，实现封装
- `const` 在函数后面表示这个函数不会修改对象状态
- 成员变量使用下划线前缀或后缀是常见命名风格

#### StudentManager 类（学生管理类）

```cpp
class StudentManager {
private:
    std::vector<Student> students;  // 使用 vector 存储学生

public:
    bool add_student(const Student& student);
    bool remove_student(const std::string& id);
    Student* find_student(const std::string& id);
    double calculate_average_score() const;
    int get_student_count() const;
    const std::vector<Student>& get_all_students() const;
};
```

**学习要点：**
- `std::vector` 是 C++ 标准库的动态数组
- 返回 `bool` 表示操作成功或失败
- 返回指针用于查找（未找到返回 `nullptr`）

### CMake 构建系统基础

```cmake
# 最低版本要求
cmake_minimum_required(VERSION 3.14...3.22)

# 项目定义
project(SimpleStudentManager VERSION 1.0 LANGUAGES CXX)

# 创建静态库
add_library(${PROJECT_NAME} STATIC ${headers} ${sources})

# 设置 C++ 标准
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)

# 添加头文件搜索路径
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
```

### 单元测试基础

我们使用 [doctest](https://github.com/doctest/doctest) 测试框架：

```cpp
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

TEST_CASE("测试名称") {
    // 准备测试数据
    Student student("张三", "2023001", 85.5);
    
    // 验证结果
    CHECK(student.get_name() == "张三");
    CHECK(student.get_score() == doctest::Approx(85.5));
}
```

**测试框架用法：**
- `TEST_CASE("名称")` - 定义一个测试用例
- `CHECK(条件)` - 验证条件，失败继续执行
- `REQUIRE(条件)` - 验证条件，失败立即停止
- `doctest::Approx(值)` - 用于浮点数比较（处理精度问题）

## 常见问题

### Q: 编译时提示找不到头文件？

**A:** 确保使用正确的 CMake 命令。不要直接编译单个文件，应该：
1. 创建 `build` 目录
2. 在 `build` 目录中运行 `cmake ../standalone`
3. 然后运行 `cmake --build .`

### Q: Windows 上中文显示乱码？

**A:** 在命令提示符中运行：
```cmd
chcp 65001  # 切换到 UTF-8 编码
```

### Q: 测试框架下载很慢？

**A:** doctest 是在配置时自动从 GitHub 下载的。如果下载慢，可以：
1. 使用代理
2. 或手动下载后放入 `_deps` 目录

## 扩展练习

学完基础后，可以尝试以下扩展：

1. **添加文件存储功能**
   - 将学生数据保存到文件
   - 程序启动时从文件加载数据

2. **添加更多统计功能**
   - 最高分/最低分
   - 成绩排序
   - 成绩分布统计

3. **改进用户界面**
   - 使用颜色区分不同信息
   - 添加分页显示
   - 支持模糊搜索

4. **添加异常处理**
   - 输入验证
   - 错误提示更友好

## 参考资料

- [CMake 官方文档](https://cmake.org/documentation/)
- [C++ Reference](https://en.cppreference.com/)
- [doctest 文档](https://github.com/doctest/doctest/blob/master/doc/markdown/tutorial.md)
- [ModernCppStarter](https://github.com/TheLartians/ModernCppStarter) - 本项目参考模板

## 许可证

本项目采用 MIT 许可证，详见 [LICENSE](LICENSE) 文件。

---

**祝你学习愉快！如有问题，欢迎提 Issue 讨论。** 🎉
