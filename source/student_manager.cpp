/**
 * @file student_manager.cpp
 * @brief 学生成绩管理系统 - 核心实现文件
 */

#include "student_manager/student_manager.h"
#include <algorithm>  // 用于 std::find_if

namespace student_manager {

// ==================== Student 类实现 ====================

Student::Student(const std::string& student_name,
                 const std::string& student_id,
                 double student_score)
    : name(student_name), id(student_id), score(student_score) {
    // 构造函数使用成员初始化列表，比在函数体内赋值更高效
}

std::string Student::get_name() const {
    return name;
}

std::string Student::get_id() const {
    return id;
}

double Student::get_score() const {
    return score;
}

void Student::set_score(double new_score) {
    score = new_score;
}

// ==================== StudentManager 类实现 ====================

bool StudentManager::add_student(const Student& student) {
    // 先检查学号是否已存在，避免重复添加
    for (const auto& s : students) {
        if (s.get_id() == student.get_id()) {
            return false;  // 学号已存在，添加失败
        }
    }
    students.push_back(student);  // 将学生添加到列表末尾
    return true;
}

bool StudentManager::remove_student(const std::string& student_id) {
    // 遍历查找要删除的学生
    for (auto it = students.begin(); it != students.end(); ++it) {
        if (it->get_id() == student_id) {
            students.erase(it);  // 找到后删除
            return true;
        }
    }
    return false;  // 未找到该学号
}

Student* StudentManager::find_student(const std::string& student_id) {
    // 返回指针以便调用者可以修改找到的学生信息
    for (auto& s : students) {
        if (s.get_id() == student_id) {
            return &s;
        }
    }
    return nullptr;  // 未找到返回空指针
}

double StudentManager::calculate_average_score() const {
    if (students.empty()) {
        return 0.0;  // 没有学生时返回 0，避免除零错误
    }
    
    double total = 0.0;
    for (const auto& s : students) {
        total += s.get_score();
    }
    return total / students.size();
}

int StudentManager::get_student_count() const {
    // size() 返回 size_t 类型，强制转换为 int 以匹配返回类型
    return static_cast<int>(students.size());
}

const std::vector<Student>& StudentManager::get_all_students() const {
    return students;
}

}  // namespace student_manager
