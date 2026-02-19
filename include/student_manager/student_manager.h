/**
 * @file student_manager.h
 * @brief 学生成绩管理系统 - 核心头文件
 * 
 * 这个头文件定义了学生类和学生管理类。
 * 适合大一学生学习 C++ 面向对象编程的基础概念。
 */

#pragma once

#include <string>
#include <vector>

namespace student_manager {

/**
 * @brief 学生类
 * 
 * 表示一个学生，包含姓名、学号和成绩。
 * 这是一个简单的数据类，主要用于存储学生信息。
 */
class Student {
private:
    std::string name;    // 学生姓名
    std::string id;      // 学号（使用字符串，支持带前导零的学号）
    double score;        // 成绩（0-100分）

public:
    /**
     * @brief 构造函数
     * @param student_name 学生姓名
     * @param student_id 学号
     * @param student_score 成绩
     */
    Student(const std::string& student_name, 
            const std::string& student_id, 
            double student_score);

    // 获取学生信息的函数
    std::string get_name() const;
    std::string get_id() const;
    double get_score() const;
    
    // 设置成绩的函数
    void set_score(double new_score);
};

/**
 * @brief 学生管理类
 * 
 * 管理多个学生的信息，提供添加、删除、查询等功能。
 * 使用 std::vector 存储学生列表，这是 C++ 标准库中的动态数组。
 */
class StudentManager {
private:
    std::vector<Student> students;  // 学生列表

public:
    /**
     * @brief 添加学生
     * @param student 要添加的学生对象
     * @return 添加成功返回 true，学号已存在返回 false
     */
    bool add_student(const Student& student);

    /**
     * @brief 根据学号删除学生
     * @param student_id 要删除的学生学号
     * @return 删除成功返回 true，学号不存在返回 false
     */
    bool remove_student(const std::string& student_id);

    /**
     * @brief 根据学号查找学生
     * @param student_id 要查找的学生学号
     * @return 找到返回指向学生的指针，未找到返回 nullptr
     */
    Student* find_student(const std::string& student_id);

    /**
     * @brief 计算所有学生的平均成绩
     * @return 平均成绩，如果没有学生返回 0.0
     */
    double calculate_average_score() const;

    /**
     * @brief 获取学生总数
     * @return 当前学生数量
     */
    int get_student_count() const;

    /**
     * @brief 获取所有学生列表
     * @return 学生列表的常量引用（只读）
     */
    const std::vector<Student>& get_all_students() const;
};

}  // namespace student_manager
