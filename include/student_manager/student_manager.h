/**
 * @file student_manager.h
 * @brief 学生成绩管理系统 - 核心头文件
 * @author Vae-Scrooge
 * @version 1.1.0
 * @date 2024
 *
 * @details
 * 这个头文件定义了学生类(Student)和学生管理类(StudentManager)。
 * 适合大一学生学习 C++ 面向对象编程的基础概念。
 *
 * 学习要点：
 * - 类的封装（public/private）
 * - const 成员函数
 * - noexcept 异常说明
 * - std::optional 可选值（C++17）
 * - std::string_view 字符串视图（C++17）
 *
 * @example
 * @code
 * #include "student_manager/student_manager.h"
 * using namespace student_manager;
 *
 * int main() {
 *     StudentManager manager;
 *     manager.add_student(Student("张三", "2023001", 85.5));
 *
 *     if (auto student = manager.find_student("2023001")) {
 *         student->get().set_score(90.0);
 *     }
 *     return 0;
 * }
 * @endcode
 */

#pragma once

#include <functional>    // std::reference_wrapper
#include <optional>      // std::optional - 可选值类型
#include <string>        // std::string - 字符串
#include <string_view>   // std::string_view - 字符串视图（只读）
#include <vector>        // std::vector - 动态数组

namespace student_manager {

/**
 * @brief 学生类
 *
 * 表示一个学生，包含姓名、学号和成绩。
 * 这是一个简单的数据类（Data Class），主要用于存储学生信息。
 *
 * 设计说明：
 * - 使用 private 封装数据成员，实现信息隐藏
 * - getter 方法标记为 const，表示不修改对象状态
 * - getter 方法标记为 noexcept，承诺不抛出异常
 * - 返回 std::string_view 避免不必要的字符串拷贝
 */
class Student {
 private:
  std::string name_;   ///< 学生姓名（使用下划线后缀命名风格）
  std::string id_;     ///< 学号（字符串类型，支持带前导零的学号如 "001234"）
  double score_;       ///< 成绩（0-100分）

 public:
  /**
   * @brief 构造函数
   * @param name 学生姓名
   * @param id 学号
   * @param score 成绩（默认为 0.0）
   *
   * @note 使用成员初始化列表（member initializer list）比函数体内赋值更高效
   */
  Student(std::string name, std::string id, double score = 0.0)
      : name_(std::move(name)), id_(std::move(id)), score_(score) {}

  // ==================== Getter 方法 ====================
  // 这些方法都是 const 的，表示不会修改对象
  // noexcept 表示不会抛出异常，编译器可以更好地优化
  // [[nodiscard]] 表示返回值不应被忽略

  /**
   * @brief 获取学生姓名
   * @return 姓名的字符串视图（避免拷贝）
   * @note 返回 string_view 是 C++17 特性，比返回 const string& 更灵活
   */
  [[nodiscard]] std::string_view get_name() const noexcept { return name_; }

  /**
   * @brief 获取学号
   * @return 学号的字符串视图
   */
  [[nodiscard]] std::string_view get_id() const noexcept { return id_; }

  /**
   * @brief 获取成绩
   * @return 成绩（double 类型）
   */
  [[nodiscard]] double get_score() const noexcept { return score_; }

  // ==================== Setter 方法 ====================

  /**
   * @brief 设置成绩
   * @param new_score 新成绩（调用者需确保在 0-100 范围内）
   */
  void set_score(double new_score) noexcept { score_ = new_score; }

  /**
   * @brief 验证成绩是否有效
   * @param score 待验证的成绩
   * @return 如果成绩在 0-100 范围内返回 true
   */
  [[nodiscard]] static constexpr bool is_valid_score(double score) noexcept {
    return score >= 0.0 && score <= 100.0;
  }
};

/**
 * @brief 学生管理类
 *
 * 管理多个学生的信息，提供添加、删除、查询、统计等功能。
 * 使用 std::vector 存储学生列表，这是 C++ 标准库中的动态数组。
 *
 * 设计说明：
 * - 使用 std::vector<Student> 存储数据，支持动态增减
 * - 使用 std::optional 返回查找结果，更安全地处理"未找到"情况
 * - 内部使用 std::find_if 算法，代码更简洁
 */
class StudentManager {
 private:
  std::vector<Student> students_;  ///< 学生列表

 public:
  // ==================== 类型别名 ====================
  using value_type = Student;
  using size_type = std::vector<Student>::size_type;
  using const_iterator = std::vector<Student>::const_iterator;

  // ==================== 容量相关 ====================

  /**
   * @brief 检查学生列表是否为空
   * @return 如果没有学生返回 true
   */
  [[nodiscard]] bool empty() const noexcept { return students_.empty(); }

  /**
   * @brief 获取学生总数
   * @return 当前学生数量
   */
  [[nodiscard]] int get_student_count() const noexcept {
    return static_cast<int>(students_.size());
  }

  // ==================== 迭代器支持 ====================

  /**
   * @brief 获取指向第一个学生的常量迭代器
   */
  [[nodiscard]] const_iterator begin() const noexcept {
    return students_.begin();
  }

  /**
   * @brief 获取指向最后一个学生之后的常量迭代器
   */
  [[nodiscard]] const_iterator end() const noexcept { return students_.end(); }

  // ==================== 学生管理操作 ====================

  /**
   * @brief 添加学生
   * @param student 要添加的学生对象
   * @return 添加成功返回 true，学号已存在返回 false
   *
   * @note 时间复杂度: O(n)，需要检查学号是否重复
   */
  bool add_student(const Student& student);

  /**
   * @brief 添加学生（移动语义版本）
   * @param student 要添加的学生对象（右值引用）
   * @return 添加成功返回 true，学号已存在返回 false
   *
   * @note 使用移动语义可以避免不必要的拷贝
   */
  bool add_student(Student&& student);

  /**
   * @brief 根据学号删除学生
   * @param student_id 要删除的学生学号
   * @return 删除成功返回 true，学号不存在返回 false
   *
   * @note 时间复杂度: O(n)
   */
  bool remove_student(std::string_view student_id);

  /**
   * @brief 根据学号查找学生
   * @param student_id 要查找的学生学号
   * @return 找到返回包含 Student 引用的 optional，未找到返回 std::nullopt
   *
   * @note 返回引用允许调用者修改找到的学生信息
   * @note 使用 std::optional 比 return nullptr 更清晰地表达"可能没有结果"
   *
   * @example
   * @code
   * if (auto result = manager.find_student("001")) {
   *     result->get().set_score(100.0);
   * }
   * @endcode
   */
  [[nodiscard]] std::optional<std::reference_wrapper<Student>> find_student(
      std::string_view student_id);

  /**
   * @brief 根据学号查找学生（const 版本）
   * @param student_id 要查找的学生学号
   * @return 找到返回包含 const Student 引用的 optional，未找到返回 std::nullopt
   */
  [[nodiscard]] std::optional<std::reference_wrapper<const Student>> find_student(
      std::string_view student_id) const;

  // ==================== 统计功能 ====================

  /**
   * @brief 计算所有学生的平均成绩
   * @return 平均成绩，如果没有学生返回 0.0
   *
   * @note 时间复杂度: O(n)
   */
  [[nodiscard]] double calculate_average_score() const noexcept;

  /**
   * @brief 获取最高分
   * @return 最高分，如果没有学生返回 std::nullopt
   */
  [[nodiscard]] std::optional<double> get_max_score() const noexcept;

  /**
   * @brief 获取最低分
   * @return 最低分，如果没有学生返回 std::nullopt
   */
  [[nodiscard]] std::optional<double> get_min_score() const noexcept;

  // ==================== 数据访问 ====================

  /**
   * @brief 获取所有学生列表
   * @return 学生列表的常量引用（只读）
   *
   * @note 返回 const 引用避免拷贝，调用者只能读取不能修改
   */
  [[nodiscard]] const std::vector<Student>& get_all_students() const noexcept {
    return students_;
  }

  /**
   * @brief 清空所有学生数据
   */
  void clear() noexcept { students_.clear(); }
};

}  // namespace student_manager
