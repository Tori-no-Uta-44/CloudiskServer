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

    explicit Sample(int val) {
        std::cout << "二" << std::endl;
        i = val;
    }

    void display() const {
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
	int _id;
	std::string* name;  // 使用指针，将 std::string 放在堆区
	int age;
	double weight;
	double height;
	
	Student()=default;
	
	Student(int id, const std::string &name, int age, double weight, double height)
			: _id(id), name(new std::string(name)), age(age), weight(weight), height(height) {}
			
	Student(const Student &student)
			: _id(student._id), name(new std::string(*student.name)), age(student.age), weight(student.weight), height(student.height) {}
			
	Student &operator=(const Student &student) {
		if (this != &student) {
			delete name;  // 释放旧内存
			name = new std::string(*student.name);  // 分配新内存并复制内容
			_id = student._id;
			age = student.age;
			weight = student.weight;
			height = student.height;
		}
		return *this;
	}
	
	[[nodiscard]] int getId() const {
		return _id;
	}
	
	void setId(int id) {
		this->_id = id;
	}
	
	[[nodiscard]] std::string getName() const {
		return *name;
	}
	
	void setName(const std::string &newName) const {
		*(this->name) = newName;
	}
	
	[[nodiscard]] int getAge() const {
		return age;
	}
	
	void setAge(int newAge) {
		this->age = newAge;
	}
	
	[[nodiscard]] double getWeight() const {
		return weight;
	}
	
	void setWeight(double newWeight) {
		this->weight = newWeight;
	}
	
	[[nodiscard]] double getHeight() const {
		return height;
	}
	
	void setHeight(double newHeight) {
		this->height = newHeight;
	}
	
	void toString() const {
		std::cout << "id:" << _id << " name:" << *name << " age:" << age
		          << " weight:" << weight << " height:" << height << std::endl;
	}
	
	~Student() {
		delete name;
	}
};

void test04_02() {
	Student student1 = Student(1, "张三", 18, 180, 180);
	student1.toString();
	Student student2 = Student(student1);
	student2.setId(2);
	student2.toString();
	Student student3 = Student();
	student3.setId(3);
	student3.setName("李四");
	student3.setAge(19);
	student3.setWeight(190);
	student3.setHeight(190);
	student3.toString();
}
