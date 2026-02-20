# Changelog

本项目的所有重要更改都将记录在此文件中。

格式基于 [Keep a Changelog](https://keepachangelog.com/zh-CN/1.0.0/)，
版本号遵循 [语义化版本](https://semver.org/lang/zh-CN/)。

## [Unreleased]

### 计划中

- 文件存储功能（保存/加载学生数据）
- 成绩排序功能
- 模糊搜索功能
- 更丰富的统计功能（成绩分布等）

## [1.1.0] - 2024-XX-XX

### Added

- 新增 `empty()` 方法检查学生列表是否为空
- 新增 `clear()` 方法清空所有学生数据
- 新增 `get_max_score()` 和 `get_min_score()` 统计方法
- 新增迭代器支持（`begin()`, `end()`）
- 新增类型别名（`value_type`, `size_type`, `const_iterator`）
- 新增 `Student::is_valid_score()` 静态方法验证成绩有效性
- 新增移动语义版本的 `add_student(Student&&)` 方法
- 新增 const 版本的 `find_student()` 方法
- 添加 CONTRIBUTING.md 贡献指南
- 添加 GitHub Issue/PR 模板

### Changed

- **Breaking**: `find_student()` 现在返回 `std::optional<std::reference_wrapper<Student>>` 而非原始指针
- **Breaking**: `Student` 构造函数现在使用值传递 + `std::move` 代替 const 引用
- **Breaking**: getter 方法现在返回 `std::string_view` 而非 `std::string`
- 改进 `get_name()` 和 `get_id()` 返回类型为 `std::string_view`，避免不必要的拷贝
- 所有简单 getter 方法标记为 `noexcept`
- 所有简单 getter 方法标记为 `[[nodiscard]]`
- 使用 `std::find_if` 和 `std::accumulate` 算法替代手写循环
- 改进主程序的输入验证和错误处理
- 添加输入缓冲区清理功能
- 主程序新增"显示最高/最低分"菜单选项

### Fixed

- 修复输入错误时程序无限循环的问题
- 修复中文显示编码问题（添加编码说明）

### Documentation

- 大幅改进代码文档注释（Doxygen 风格）
- 添加详细的学习要点说明
- 添加代码示例到头文件
- 添加时间复杂度说明

### Tests

- 新增边界条件测试
- 新增 `is_valid_score` 测试
- 新增移动语义测试
- 新增 const 版本 `find_student` 测试
- 新增迭代器测试
- 新增 `empty()` 和 `clear()` 测试

## [1.0.0] - 2024-XX-XX

### Added

- 初始版本发布
- `Student` 类：存储学生信息（姓名、学号、成绩）
- `StudentManager` 类：管理学生列表
  - `add_student()` 添加学生
  - `remove_student()` 删除学生
  - `find_student()` 查找学生
  - `calculate_average_score()` 计算平均分
  - `get_student_count()` 获取学生数量
  - `get_all_students()` 获取所有学生
- 命令行交互界面
- CMake 构建系统
- doctest 单元测试
- GitHub Actions CI/CD
- MIT 许可证

---

[Unreleased]: https://github.com/Vae-Scrooge/SimpleStudentManager/compare/v1.1.0...HEAD
[1.1.0]: https://github.com/Vae-Scrooge/SimpleStudentManager/compare/v1.0.0...v1.1.0
[1.0.0]: https://github.com/Vae-Scrooge/SimpleStudentManager/releases/tag/v1.0.0
