/**
 * @file student_manager.cpp
 * @brief 学生成绩管理系统 - 核心实现文件
 */

#include "student_manager/student_manager.h"

#include <algorithm>  // std::find_if, std::max_element, std::min_element
#include <numeric>    // std::accumulate

namespace student_manager {

  // ==================== StudentManager 类实现 ====================
  // 注意：Student 类的方法已在头文件中内联实现

  bool StudentManager::add_student(const Student& student) {
    if (find_student(student.get_id())) {
      return false;  // 学号已存在
    }
    students_.push_back(student);
    return true;
  }

  bool StudentManager::add_student(Student&& student) {
    if (find_student(student.get_id())) {
      return false;  // 学号已存在
    }
    students_.push_back(std::move(student));
    return true;
  }

  bool StudentManager::remove_student(std::string_view student_id) {
    auto it = std::find_if(students_.begin(), students_.end(),
                           [student_id](const Student& s) { return s.get_id() == student_id; });
    if (it != students_.end()) {
      students_.erase(it);
      return true;
    }
    return false;
  }

  std::optional<std::reference_wrapper<Student>> StudentManager::find_student(
      std::string_view student_id) {
    auto it = std::find_if(students_.begin(), students_.end(),
                           [student_id](const Student& s) { return s.get_id() == student_id; });
    if (it != students_.end()) {
      return std::ref(*it);
    }
    return std::nullopt;
  }

  std::optional<std::reference_wrapper<const Student>> StudentManager::find_student(
      std::string_view student_id) const {
    auto it = std::find_if(students_.begin(), students_.end(),
                           [student_id](const Student& s) { return s.get_id() == student_id; });
    if (it != students_.end()) {
      return std::cref(*it);
    }
    return std::nullopt;
  }

  double StudentManager::calculate_average_score() const noexcept {
    if (students_.empty()) {
      return 0.0;
    }
    double total
        = std::accumulate(students_.begin(), students_.end(), 0.0,
                          [](double sum, const Student& s) { return sum + s.get_score(); });
    return total / static_cast<double>(students_.size());
  }

  std::optional<double> StudentManager::get_max_score() const noexcept {
    if (students_.empty()) {
      return std::nullopt;
    }
    auto it = std::max_element(
        students_.begin(), students_.end(),
        [](const Student& a, const Student& b) { return a.get_score() < b.get_score(); });
    return it->get_score();
  }

  std::optional<double> StudentManager::get_min_score() const noexcept {
    if (students_.empty()) {
      return std::nullopt;
    }
    auto it = std::min_element(
        students_.begin(), students_.end(),
        [](const Student& a, const Student& b) { return a.get_score() < b.get_score(); });
    return it->get_score();
  }

}  // namespace student_manager
