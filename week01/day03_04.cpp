//
// Created by 李勃鋆 on 24-8-15.
//
#include "../week01.h"

class Sample {
    int i;
public:
    Sample() {
        std::cout << "一" << std::endl;
        i = 0;
    };

    Sample(int val) {
        std::cout << "二" << std::endl;
        i = val;
    }

    void display() {
        std::cout << i << std::endl;
    }

    ~Sample() {
        std::cout << "零" << std::endl;
    }
};

void test04_01() {
    Sample a = Sample();
    Sample b = Sample(10);
    a.display();
    b.display();
}

class Student {
public:
    int id;
    char *name;
    int age;
    double weight;
    double height;

    Student() {}

    Student(int id, char *name, int age, double weight, double height) : id(id),
                                                                         name(new char[std::strlen(name) + 1]()),
                                                                         age(age), weight(weight), height(height) {
        std::strcpy(this->name, name);
    }

    Student(const Student &student) : id(student.id), name(new char[std::strlen(student.name) + 1]()), age(student.age),
                                      weight(student.weight), height(student.height) {
        std::strcpy(this->name, student.name);
    }

    int getId() const {
        return id;
    }

    void setId(int id) {
        this->id = id;
    }

    char *getName() const {
        return name;
    }

    void setName(char *name) {
//        this->name = name;
        if (this->name != nullptr) {
            delete[] this->name;
        }
        this->name = new char[std::strlen(name) + 1]();
        std::strcpy(this->name, name);
    }

    int getAge() const {
        return age;
    }

    void setAge(int age) {
        this->age = age;
    }

    double getWeight() const {
        return weight;
    }

    void setWeight(double weight) {
        this->weight = weight;
    }

    double getHeight() const {
        return height;
    }

    void setHeight(double height) {
        Student::height = height;
    }

    Student &operator=(const Student &student) {
        if (this != &student) {
            delete[] name;
            name = new char[std::strlen(student.name) + 1]();
            std::strcpy(name, student.name);
            this->id = student.id;
            this->age = student.age;
            this->weight = student.weight;
            this->height = student.height;
        }
        return *this;
    }

    void toString() const {
        std::cout << "id:" << id << " name:" << name << " age:" << age << " weight:" << weight << " height:" << height
                  << std::endl;
    }

    ~Student() {
        if (name != nullptr) {
            delete[] name;
            name = nullptr;
        }
    }
};

void test04_02() {
    Student student1 = Student(01, "张三", 18, 180, 180);
    student1.toString();
    Student student2 = Student(student1);
    student2.setId(02);
    student2.setName("王五");
    student2.toString();
    Student student3 = Student();
    student3.setId(03);
    student3.setName("李四");
    student3.setAge(19);
    student3.setWeight(190);
    student3.setHeight(190);
    student3.toString();
}
