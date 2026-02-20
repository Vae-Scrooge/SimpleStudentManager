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

using namespace student_manager;

// ==================== Student 类测试 ====================

TEST_CASE("Student 构造函数和获取方法") {
  Student student("张三", "2023001", 85.5);

  CHECK(student.get_name() == "张三");
  CHECK(student.get_id() == "2023001");
  CHECK(student.get_score() == doctest::Approx(85.5));
}

TEST_CASE("Student 默认成绩") {
  Student student("李四", "2023002");
  CHECK(student.get_score() == doctest::Approx(0.0));
}

TEST_CASE("Student 设置成绩") {
  Student student("李四", "2023002", 60.0);

  student.set_score(95.0);

  CHECK(student.get_score() == doctest::Approx(95.0));
}

TEST_CASE("Student is_valid_score 静态方法") {
  CHECK(Student::is_valid_score(0.0) == true);
  CHECK(Student::is_valid_score(100.0) == true);
  CHECK(Student::is_valid_score(50.5) == true);
  CHECK(Student::is_valid_score(-0.1) == false);
  CHECK(Student::is_valid_score(100.1) == false);
  CHECK(Student::is_valid_score(-10.0) == false);
  CHECK(Student::is_valid_score(200.0) == false);
}

TEST_CASE("Student string_view 返回值") {
  Student student("王五", "2023003", 75.0);

  std::string_view name = student.get_name();
  std::string_view id = student.get_id();

  CHECK(name == "王五");
  CHECK(id == "2023003");
}

// ==================== StudentManager 类测试 ====================

TEST_CASE("StudentManager 初始状态为空") {
  StudentManager manager;

  CHECK(manager.empty() == true);
  CHECK(manager.get_student_count() == 0);
}

TEST_CASE("StudentManager 添加学生") {
  StudentManager manager;

  Student student1("王五", "2023003", 75.0);
  CHECK(manager.add_student(student1) == true);
  CHECK(manager.get_student_count() == 1);
  CHECK(manager.empty() == false);

  Student student2("赵六", "2023004", 88.0);
  CHECK(manager.add_student(student2) == true);
  CHECK(manager.get_student_count() == 2);

  Student student3("王五2", "2023003", 90.0);
  CHECK(manager.add_student(student3) == false);
  CHECK(manager.get_student_count() == 2);
}

TEST_CASE("StudentManager 添加学生（移动语义）") {
  StudentManager manager;

  CHECK(manager.add_student(Student("移动测试", "2024001", 80.0)) == true);
  CHECK(manager.get_student_count() == 1);
  CHECK(manager.add_student(Student("移动测试2", "2024001", 85.0)) == false);
}

TEST_CASE("StudentManager 删除学生") {
  StudentManager manager;

  manager.add_student(Student("测试1", "2024001", 80.0));
  manager.add_student(Student("测试2", "2024002", 85.0));

  CHECK(manager.remove_student("2024001") == true);
  CHECK(manager.get_student_count() == 1);

  CHECK(manager.remove_student("9999999") == false);
  CHECK(manager.get_student_count() == 1);
}

TEST_CASE("StudentManager 查找学生") {
  StudentManager manager;

  manager.add_student(Student("查找测试", "2025001", 92.0));

  auto result = manager.find_student("2025001");
  REQUIRE(result.has_value());
  CHECK(result->get().get_name() == "查找测试");
  CHECK(result->get().get_score() == doctest::Approx(92.0));

  auto not_found = manager.find_student("9999999");
  CHECK(not_found.has_value() == false);
}

TEST_CASE("StudentManager 查找学生（const 版本）") {
  StudentManager manager;
  manager.add_student(Student("const测试", "2026001", 88.0));

  const StudentManager& const_manager = manager;
  auto result = const_manager.find_student("2026001");

  REQUIRE(result.has_value());
  CHECK(result->get().get_name() == "const测试");
}

TEST_CASE("StudentManager 通过引用修改学生") {
  StudentManager manager;
  manager.add_student(Student("修改测试", "2027001", 70.0));

  auto result = manager.find_student("2027001");
  REQUIRE(result.has_value());

  result->get().set_score(95.0);

  auto verify = manager.find_student("2027001");
  REQUIRE(verify.has_value());
  CHECK(verify->get().get_score() == doctest::Approx(95.0));
}

TEST_CASE("StudentManager 计算平均分") {
  StudentManager manager;

  CHECK(manager.calculate_average_score() == doctest::Approx(0.0));

  manager.add_student(Student("学生A", "2030001", 80.0));
  manager.add_student(Student("学生B", "2030002", 90.0));
  manager.add_student(Student("学生C", "2030003", 70.0));

  CHECK(manager.calculate_average_score() == doctest::Approx(80.0));
}

TEST_CASE("StudentManager 获取最高分和最低分") {
  StudentManager manager;

  CHECK(manager.get_max_score().has_value() == false);
  CHECK(manager.get_min_score().has_value() == false);

  manager.add_student(Student("学生A", "2040001", 60.0));
  manager.add_student(Student("学生B", "2040002", 95.0));
  manager.add_student(Student("学生C", "2040003", 75.0));

  REQUIRE(manager.get_max_score().has_value());
  CHECK(*manager.get_max_score() == doctest::Approx(95.0));

  REQUIRE(manager.get_min_score().has_value());
  CHECK(*manager.get_min_score() == doctest::Approx(60.0));
}

TEST_CASE("StudentManager 获取所有学生") {
  StudentManager manager;

  manager.add_student(Student("学生1", "2040001", 60.0));
  manager.add_student(Student("学生2", "2040002", 70.0));

  const auto& students = manager.get_all_students();
  CHECK(students.size() == 2);
  CHECK(students[0].get_id() == "2040001");
  CHECK(students[1].get_id() == "2040002");
}

TEST_CASE("StudentManager 清空") {
  StudentManager manager;

  manager.add_student(Student("学生1", "2050001", 60.0));
  manager.add_student(Student("学生2", "2050002", 70.0));

  manager.clear();

  CHECK(manager.empty() == true);
  CHECK(manager.get_student_count() == 0);
}

TEST_CASE("StudentManager 迭代器") {
  StudentManager manager;

  manager.add_student(Student("学生1", "2060001", 60.0));
  manager.add_student(Student("学生2", "2060002", 70.0));

  int count = 0;
  for (const auto& student : manager) {
    CHECK(student.get_score() >= 0.0);
    count++;
  }
  CHECK(count == 2);
}

// ==================== 边界条件测试 ====================

TEST_CASE("边界条件：带前导零的学号") {
  StudentManager manager;

  CHECK(manager.add_student(Student("学生", "001234", 80.0)) == true);
  CHECK(manager.add_student(Student("学生2", "1234", 85.0)) == true);

  auto result = manager.find_student("001234");
  REQUIRE(result.has_value());
  CHECK(result->get().get_id() == "001234");
}

TEST_CASE("边界条件：0分和100分") {
  Student student1("零分", "001", 0.0);
  Student student2("满分", "002", 100.0);

  CHECK(student1.get_score() == doctest::Approx(0.0));
  CHECK(student2.get_score() == doctest::Approx(100.0));
}

TEST_CASE("边界条件：单个学生平均分") {
  StudentManager manager;
  manager.add_student(Student("唯一学生", "001", 75.5));

  CHECK(manager.calculate_average_score() == doctest::Approx(75.5));
  CHECK(*manager.get_max_score() == doctest::Approx(75.5));
  CHECK(*manager.get_min_score() == doctest::Approx(75.5));
}
