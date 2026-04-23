# 贡献指南 | Contributing Guide

感谢你对 SimpleStudentManager 项目的兴趣！本文档将帮助你了解如何为项目做出贡献。

## 目录

- [行为准则](#行为准则)
- [如何贡献](#如何贡献)
- [开发环境设置](#开发环境设置)
- [代码规范](#代码规范)
- [提交规范](#提交规范)
- [Pull Request 流程](#pull-request-流程)

## 行为准则

本项目采用开放、包容的态度。请尊重所有贡献者，保持友好和建设性的交流。

## 如何贡献

### 报告 Bug

如果你发现了 bug，请[创建 Issue](https://github.com/Vae-Scrooge/SimpleStudentManager/issues/new)，包含以下信息：

1. **描述问题**：清晰简洁地描述 bug
2. **复现步骤**：提供复现问题的详细步骤
3. **预期行为**：描述你期望发生什么
4. **实际行为**：描述实际发生了什么
5. **环境信息**：
   - 操作系统（Windows/macOS/Linux）
   - 编译器版本
   - CMake 版本

### 建议新功能

欢迎提出新功能建议！请[创建 Issue](https://github.com/Vae-Scrooge/SimpleStudentManager/issues/new)，描述：

1. 功能描述
2. 使用场景
3. 可能的实现方式（可选）

### 提交代码

1. Fork 本仓库
2. 创建功能分支 (`git checkout -b feature/amazing-feature`)
3. 提交更改 (`git commit -m 'Add some amazing feature'`)
4. 推送到分支 (`git push origin feature/amazing-feature`)
5. 创建 Pull Request

## 开发环境设置

### 必需工具

| 工具 | 版本要求 |
|------|---------|
| CMake | 3.14+ |
| C++ 编译器 | 支持 C++17 |

### 构建项目

```bash
# 克隆你的 fork
git clone https://github.com/Vae-Scrooge/SimpleStudentManager.git
cd SimpleStudentManager

# 创建构建目录
mkdir build && cd build

# 配置并构建
cmake ..
cmake --build .
```

### 运行测试

```bash
mkdir build-test && cd build-test
cmake ../test
cmake --build .
ctest --output-on-failure
```

## 代码规范

### C++ 代码风格

本项目使用基于 Google C++ Style Guide 的代码风格，配置见 `.clang-format`。

关键规则：

- **缩进**：2 空格
- **命名约定**：
  - 类名：`PascalCase`（如 `StudentManager`）
  - 函数名：`snake_case`（如 `add_student`）
  - 成员变量：`snake_case_`（带下划线后缀，如 `students_`）
  - 常量：`kCamelCase`（如 `kMaxScore`）
- **大括号**：与语句在同一行（K&R 风格）
- **访问修饰符**：缩进 -2 空格

### 格式化代码

在提交前，请确保代码已格式化：

```bash
# 安装 clang-format（如果尚未安装）
# Ubuntu: sudo apt install clang-format
# macOS: brew install clang-format
# Windows: 使用 LLVM 安装程序

# 格式化所有源文件
find source include standalone -name "*.cpp" -o -name "*.h" | xargs clang-format -i
```

### 文档注释

使用 Doxygen 风格的文档注释：

```cpp
/**
 * @brief 简短描述
 * @param name 参数说明
 * @return 返回值说明
 */
```

### 中文注释

考虑到本项目面向中文学习者，代码注释主要使用中文。

## 提交规范

请使用清晰的提交信息：

- `feat: 添加新功能`
- `fix: 修复 bug`
- `docs: 文档更新`
- `style: 代码格式调整（不影响功能）`
- `refactor: 代码重构`
- `test: 测试相关`
- `chore: 构建/工具链更新`

## Pull Request 流程

1. **确保测试通过**：所有现有测试必须通过
2. **添加测试**：新功能应包含相应测试
3. **更新文档**：如有必要，更新 README.md
4. **代码审查**：等待维护者审查

### PR 检查清单

- [ ] 代码遵循项目的代码规范
- [ ] 已运行 `clang-format` 格式化代码
- [ ] 所有测试通过
- [ ] 新功能已添加测试
- [ ] 文档已更新（如适用）

## 获取帮助

如有任何问题，可以：

1. 在 [Issues](https://github.com/Vae-Scrooge/SimpleStudentManager/issues) 中提问
2. 发送邮件至项目维护者

---

再次感谢你的贡献！🎉
