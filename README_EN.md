[![Ubuntu Build](https://github.com/Vae-Scrooge/SimpleStudentManager/workflows/Ubuntu/badge.svg)](https://github.com/Vae-Scrooge/SimpleStudentManager/actions/workflows/ubuntu.yml)
[![Windows Build](https://github.com/Vae-Scrooge/SimpleStudentManager/workflows/Windows/badge.svg)](https://github.com/Vae-Scrooge/SimpleStudentManager/actions/workflows/windows.yml)
[![macOS Build](https://github.com/Vae-Scrooge/SimpleStudentManager/workflows/MacOS/badge.svg)](https://github.com/Vae-Scrooge/SimpleStudentManager/actions/workflows/macos.yml)
[![Code Style](https://github.com/Vae-Scrooge/SimpleStudentManager/workflows/Style/badge.svg)](https://github.com/Vae-Scrooge/SimpleStudentManager/actions/workflows/style.yml)
[![codecov](https://codecov.io/gh/Vae-Scrooge/SimpleStudentManager/branch/main/graph/badge.svg)](https://codecov.io/gh/Vae-Scrooge/SimpleStudentManager)
[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.cppreference.com/w/cpp/17)
[![CMake](https://img.shields.io/badge/CMake-3.14+-green.svg)](https://cmake.org/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

# Simple Student Manager 📚

English | **[简体中文](README.md)**

A modern C++ project template designed for CS freshmen to learn programming fundamentals.

## Overview

This is a simplified C++ project based on [ModernCppStarter](https://github.com/TheLartians/ModernCppStarter), specifically designed for first-year students. Through this project, you will learn:

- ✅ **CMake Build System**: The standard build tool for modern C++ projects
- ✅ **Object-Oriented Programming**: Classes, objects, and encapsulation
- ✅ **Unit Testing**: How to test your code properly
- ✅ **Project Structure**: Standard C++ project organization
- ✅ **Git & GitHub**: Version control and code hosting

## Features

- 📝 Add students (name, ID, score)
- 🗑️ Remove students
- 🔍 Search student information
- ✏️ Modify student scores
- 📊 Calculate average score
- 📈 Get max/min scores
- 📋 Display all students

## Requirements

| Tool | Version | Download |
|------|---------|----------|
| CMake | 3.14+ | https://cmake.org/download/ |
| C++ Compiler | C++17 support | See below |

### Compiler Setup

**Windows:**
- **Visual Studio 2019/2022**: Select "Desktop development with C++"
- **MinGW-w64**: https://www.mingw-w64.org/ or MSYS2

**macOS:**
```bash
xcode-select --install
```

**Linux:**
```bash
# Ubuntu/Debian
sudo apt update
sudo apt install build-essential cmake

# Fedora
sudo dnf install gcc-c++ cmake
```

## Quick Start

### 1. Clone the Repository

```bash
git clone https://github.com/Vae-Scrooge/SimpleStudentManager.git
cd SimpleStudentManager
```

### 2. Build and Run

```bash
mkdir build && cd build
cmake ../standalone
cmake --build .

./student_manager        # Linux/macOS
.\student_manager.exe    # Windows
```

### 3. Run Tests

```bash
mkdir build-test && cd build-test
cmake ../test
cmake --build .
ctest --output-on-failure
```

## Core Classes

### Student Class

```cpp
class Student {
 private:
  std::string name_;
  std::string id_;
  double score_;

 public:
  Student(std::string name, std::string id, double score = 0.0);

  std::string_view get_name() const noexcept;
  std::string_view get_id() const noexcept;
  double get_score() const noexcept;
  
  void set_score(double new_score) noexcept;
  static constexpr bool is_valid_score(double score) noexcept;
};
```

### StudentManager Class

```cpp
class StudentManager {
 private:
  std::vector<Student> students_;

 public:
  bool empty() const noexcept;
  int get_student_count() const noexcept;

  bool add_student(const Student& student);
  bool add_student(Student&& student);
  bool remove_student(std::string_view id);

  std::optional<std::reference_wrapper<Student>> find_student(std::string_view id);
  
  double calculate_average_score() const noexcept;
  std::optional<double> get_max_score() const noexcept;
  std::optional<double> get_min_score() const noexcept;

  const std::vector<Student>& get_all_students() const noexcept;
  void clear() noexcept;
};
```

### Usage Example

```cpp
StudentManager manager;

// Add students
manager.add_student(Student("Alice", "2023001", 85.5));
manager.add_student(Student("Bob", "2023002", 92.0));

// Find and modify
if (auto result = manager.find_student("2023001")) {
    result->get().set_score(90.0);
}

// Statistics
std::cout << "Average: " << manager.calculate_average_score() << std::endl;
if (auto max = manager.get_max_score()) {
    std::cout << "Max: " << *max << std::endl;
}
```

## Documentation

- [Contributing Guide](CONTRIBUTING.md)
- [Changelog](CHANGELOG.md)

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

**Happy Learning! Feel free to open an Issue if you have questions.** 🎉
