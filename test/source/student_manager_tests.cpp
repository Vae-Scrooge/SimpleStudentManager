/**
 * @file student_manager_tests.cpp
 * @brief 学生管理系统单元测试
 * 
 * 单元测试是用来验证代码是否正确工作的小程序。
 * 每个测试用例测试一个具体功能。
 * 
 * doctest 的基本用法：
 * - TEST_CASE("测试名称") 定义一个测试用例
 * - CHECK(条件) 检查条件是否为真，失败会记录但不停止测试
 * - REQUIRE(条件) 检查条件是否为真，失败会停止当前测试
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "student_manager/student_manager.h"

// 使用命名空间简化代码
using namespace student_manager;

// ==================== Student 类测试 ====================

TEST_CASE("Student 构造函数和获取方法") {
    // 创建一个学生对象
    Student student("张三", "2023001", 85.5);
    
    // 验证各个属性是否正确
    CHECK(student.get_name() == "张三");
    CHECK(student.get_id() == "2023001");
    CHECK(student.get_score() == doctest::Approx(85.5));
}

TEST_CASE("Student 设置成绩") {
    Student student("李四", "2023002", 60.0);
    
    // 修改成绩
    student.set_score(95.0);
    
    // 验证成绩已修改
    CHECK(student.get_score() == doctest::Approx(95.0));
}

// ==================== StudentManager 类测试 ====================

TEST_CASE("StudentManager 添加学生") {
    StudentManager manager;
    
    // 添加第一个学生，应该成功
    Student student1("王五", "2023003", 75.0);
    CHECK(manager.add_student(student1) == true);
    CHECK(manager.get_student_count() == 1);
    
    // 添加第二个学生，应该成功
    Student student2("赵六", "2023004", 88.0);
    CHECK(manager.add_student(student2) == true);
    CHECK(manager.get_student_count() == 2);
    
    // 尝试添加相同学号的学生，应该失败
    Student student3("王五2", "2023003", 90.0);
    CHECK(manager.add_student(student3) == false);
    CHECK(manager.get_student_count() == 2);  // 数量不变
}

TEST_CASE("StudentManager 删除学生") {
    StudentManager manager;
    
    // 先添加学生
    manager.add_student(Student("测试1", "2024001", 80.0));
    manager.add_student(Student("测试2", "2024002", 85.0));
    
    // 删除存在的学生
    CHECK(manager.remove_student("2024001") == true);
    CHECK(manager.get_student_count() == 1);
    
    // 删除不存在的学生
    CHECK(manager.remove_student("9999999") == false);
    CHECK(manager.get_student_count() == 1);  // 数量不变
}

TEST_CASE("StudentManager 查找学生") {
    StudentManager manager;
    
    // 添加学生
    manager.add_student(Student("查找测试", "2025001", 92.0));
    
    // 查找存在的学生
    Student* found = manager.find_student("2025001");
    REQUIRE(found != nullptr);  // 必须找到
    CHECK(found->get_name() == "查找测试");
    CHECK(found->get_score() == doctest::Approx(92.0));
    
    // 查找不存在的学生
    Student* not_found = manager.find_student("9999999");
    CHECK(not_found == nullptr);
}

TEST_CASE("StudentManager 计算平均分") {
    StudentManager manager;
    
    // 空管理器，平均分应为 0
    CHECK(manager.calculate_average_score() == doctest::Approx(0.0));
    
    // 添加学生
    manager.add_student(Student("学生A", "2030001", 80.0));
    manager.add_student(Student("学生B", "2030002", 90.0));
    manager.add_student(Student("学生C", "2030003", 70.0));
    
    // 计算平均分：(80 + 90 + 70) / 3 = 80
    CHECK(manager.calculate_average_score() == doctest::Approx(80.0));
}

TEST_CASE("StudentManager 获取所有学生") {
    StudentManager manager;
    
    // 添加学生
    manager.add_student(Student("学生1", "2040001", 60.0));
    manager.add_student(Student("学生2", "2040002", 70.0));
    
    // 获取所有学生
    const auto& students = manager.get_all_students();
    CHECK(students.size() == 2);
    CHECK(students[0].get_id() == "2040001");
    CHECK(students[1].get_id() == "2040002");
}
