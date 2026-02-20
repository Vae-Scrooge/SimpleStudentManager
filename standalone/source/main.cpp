/**
 * @file main.cpp
 * @brief 学生成绩管理系统 - 主程序入口
 *
 * 这是一个简单的命令行交互程序，演示如何使用 StudentManager 库。
 * 大一学生可以通过这个程序学习：
 * 1. 如何使用类和对象
 * 2. 如何处理用户输入
 * 3. 如何使用循环和条件语句构建交互式程序
 */

#include <iostream>   // 用于输入输出
#include <string>     // 用于字符串处理
#include <iomanip>    // 用于格式化输出
#include <limits>     // 用于 numeric_limits

#include "student_manager/student_manager.h"

using namespace student_manager;

/// 清除输入缓冲区中的错误状态和剩余字符
void clear_input_buffer() {
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/// 显示主菜单
void show_menu() {
  std::cout << "\n========== 学生成绩管理系统 ==========\n";
  std::cout << "1. 添加学生\n";
  std::cout << "2. 删除学生\n";
  std::cout << "3. 查询学生\n";
  std::cout << "4. 修改成绩\n";
  std::cout << "5. 显示所有学生\n";
  std::cout << "6. 计算平均分\n";
  std::cout << "7. 显示最高/最低分\n";
  std::cout << "0. 退出系统\n";
  std::cout << "======================================\n";
  std::cout << "请选择操作: ";
}

/// 添加学生
void add_student(StudentManager& manager) {
  std::string name, id;
  double score;

  std::cout << "请输入学生姓名: ";
  if (!(std::cin >> name)) {
    std::cout << "输入错误！\n";
    clear_input_buffer();
    return;
  }

  std::cout << "请输入学号: ";
  if (!(std::cin >> id)) {
    std::cout << "输入错误！\n";
    clear_input_buffer();
    return;
  }

  std::cout << "请输入成绩 (0-100): ";
  if (!(std::cin >> score)) {
    std::cout << "输入错误：请输入有效的数字！\n";
    clear_input_buffer();
    return;
  }

  if (!Student::is_valid_score(score)) {
    std::cout << "错误：成绩必须在 0-100 之间！\n";
    return;
  }

  Student student(name, id, score);
  if (manager.add_student(std::move(student))) {
    std::cout << "添加成功！\n";
  } else {
    std::cout << "添加失败：学号已存在！\n";
  }
}

/// 删除学生
void remove_student(StudentManager& manager) {
  std::string id;

  std::cout << "请输入要删除的学号: ";
  if (!(std::cin >> id)) {
    std::cout << "输入错误！\n";
    clear_input_buffer();
    return;
  }

  if (manager.remove_student(id)) {
    std::cout << "删除成功！\n";
  } else {
    std::cout << "删除失败：学号不存在！\n";
  }
}

/// 查询学生
void find_student(StudentManager& manager) {
  std::string id;

  std::cout << "请输入要查询的学号: ";
  if (!(std::cin >> id)) {
    std::cout << "输入错误！\n";
    clear_input_buffer();
    return;
  }

  auto result = manager.find_student(id);
  if (result) {
    const auto& student = result->get();
    std::cout << "找到学生：\n";
    std::cout << "姓名: " << student.get_name() << "\n";
    std::cout << "学号: " << student.get_id() << "\n";
    std::cout << "成绩: " << student.get_score() << "\n";
  } else {
    std::cout << "未找到该学号的学生！\n";
  }
}

/// 修改学生成绩
void modify_score(StudentManager& manager) {
  std::string id;
  double new_score;

  std::cout << "请输入要修改的学号: ";
  if (!(std::cin >> id)) {
    std::cout << "输入错误！\n";
    clear_input_buffer();
    return;
  }

  auto result = manager.find_student(id);
  if (!result) {
    std::cout << "未找到该学号的学生！\n";
    return;
  }

  auto& student = result->get();
  std::cout << "当前成绩: " << student.get_score() << "\n";
  std::cout << "请输入新成绩 (0-100): ";

  if (!(std::cin >> new_score)) {
    std::cout << "输入错误：请输入有效的数字！\n";
    clear_input_buffer();
    return;
  }

  if (!Student::is_valid_score(new_score)) {
    std::cout << "错误：成绩必须在 0-100 之间！\n";
    return;
  }

  student.set_score(new_score);
  std::cout << "修改成功！\n";
}

/// 显示所有学生
void show_all_students(const StudentManager& manager) {
  const auto& students = manager.get_all_students();

  if (students.empty()) {
    std::cout << "暂无学生数据！\n";
    return;
  }

  std::cout << "\n" << std::left;
  std::cout << std::setw(15) << "姓名" << std::setw(15) << "学号" << std::setw(10)
            << "成绩"
            << "\n";
  std::cout << std::string(40, '-') << "\n";

  for (const auto& student : students) {
    std::cout << std::setw(15) << student.get_name() << std::setw(15)
              << student.get_id() << std::setw(10) << student.get_score() << "\n";
  }

  std::cout << "共 " << manager.get_student_count() << " 名学生\n";
}

/// 计算并显示平均分
void show_average(const StudentManager& manager) {
  if (manager.empty()) {
    std::cout << "暂无学生数据，无法计算平均分！\n";
    return;
  }

  double avg = manager.calculate_average_score();
  std::cout << "平均成绩: " << std::fixed << std::setprecision(2) << avg << "\n";
}

/// 显示最高分和最低分
void show_statistics(const StudentManager& manager) {
  if (manager.empty()) {
    std::cout << "暂无学生数据！\n";
    return;
  }

  auto max_score = manager.get_max_score();
  auto min_score = manager.get_min_score();

  std::cout << std::fixed << std::setprecision(2);
  if (max_score) {
    std::cout << "最高分: " << *max_score << "\n";
  }
  if (min_score) {
    std::cout << "最低分: " << *min_score << "\n";
  }
}

int main() {
  StudentManager manager;
  int choice;

  std::cout << "欢迎使用学生成绩管理系统！\n";

  while (true) {
    show_menu();
    if (!(std::cin >> choice)) {
      std::cout << "输入错误，请输入数字！\n";
      clear_input_buffer();
      continue;
    }

    switch (choice) {
      case 1:
        add_student(manager);
        break;
      case 2:
        remove_student(manager);
        break;
      case 3:
        find_student(manager);
        break;
      case 4:
        modify_score(manager);
        break;
      case 5:
        show_all_students(manager);
        break;
      case 6:
        show_average(manager);
        break;
      case 7:
        show_statistics(manager);
        break;
      case 0:
        std::cout << "感谢使用，再见！\n";
        return 0;
      default:
        std::cout << "无效的选择，请重新输入！\n";
    }
  }

  return 0;
}
