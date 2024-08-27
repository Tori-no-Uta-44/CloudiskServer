//
// Created by 李勃鋆 on 24-8-26.
//
#include "../week03.h"

class Person13_02 {
public:
	char *_name;
	int _age;

	Person13_02(char *name, int age):
		_name(new char[strlen(name) + 1]()), _age(age) {
		strcpy(_name, name);
	}

	void display() const {
		cout << _name << " " << _age << endl;
	}

	Person13_02(const Person13_02 &p):
		_name(new char[strlen(p._name) + 1]()), _age(p._age) {
		strcpy(_name, p._name);
	}

	Person13_02 &operator=(const Person13_02 &p) {
		if (this != &p) {
			delete [] _name;
			_name = new char[strlen(p._name) + 1];
			strcpy(_name, p._name);
			_age = p._age;
		}
		return *this;
	}

	~Person13_02() {
		if (_name != nullptr) {
			delete[] _name;
			_name = nullptr;
		}
	}
};

class Employee13_02 : public Person13_02 {
public:
	char *_department;
	double _salary;

	Employee13_02(char *name, int age, char *department, double salary):
		Person13_02(name, age), _department(new char[strlen(department) + 1]()), _salary(salary) {
		strcpy(_department, department);
	}

	~Employee13_02() {
		if (_department != nullptr) {
			delete[] _department;
			_department = nullptr;
		}
	}

	Employee13_02(const Employee13_02 &rhs):
		Person13_02(rhs), _department(new char[strlen(rhs._department) + 1]()), _salary(rhs._salary) {
		strcpy(_department, rhs._department);
	}

	Employee13_02 &operator=(const Employee13_02 &rhs) {
		if (this != &rhs) {
			Person13_02::operator=(rhs);
			delete[] _department;
			_department = new char[strlen(rhs._department) + 1];
			strcpy(_department, rhs._department);
			_salary=rhs._salary;
		}
		return *this;
	}

	void display() const {
		std::cout << _name << " " << _age << " " << _department << std::endl;
	}
	double salary() const {
		return _salary;
	}
	double average(int totalEmployees,double totalSalary) const {
		if(totalEmployees>0) {
			return _salary/totalEmployees;
		}
		return 0;
	}
};

void testPersonCreation() {
    // 测试创建 Person13_02 对象
    char name[] = "Alice";
    Person13_02 person(name, 25);
    assert(strcmp(person._name, "Alice") == 0);
    assert(person._age == 25);
    cout << "testPersonCreation passed!" << endl;
}

void testEmployeeCreation() {
    // 测试创建 Employee13_02 对象
    char name[] = "Bob";
    char department[] = "Engineering";
    Employee13_02 employee(name, 30, department, 80000.0);
    assert(strcmp(employee._name, "Bob") == 0);
    assert(employee._age == 30);
    assert(strcmp(employee._department, "Engineering") == 0);
    assert(employee._salary == 80000.0);
    cout << "testEmployeeCreation passed!" << endl;
}

void testCopyConstructor1() {
    // 测试拷贝构造函数
    char name[] = "Carol";
    char department[] = "Marketing";
    Employee13_02 employee1(name, 28, department, 60000.0);
    const Employee13_02& employee2 = employee1; // 使用拷贝构造函数
    assert(strcmp(employee2._name, "Carol") == 0);
    assert(employee2._age == 28);
    assert(strcmp(employee2._department, "Marketing") == 0);
    assert(employee2._salary == 60000.0);
    cout << "testCopyConstructor passed!" << endl;
}

void testAssignmentOperator1() {
    // 测试赋值运算符
    char name1[] = "Dave";
    char department1[] = "Sales";
    Employee13_02 employee1(name1, 35, department1, 50000.0);

    char name2[] = "Eve";
    char department2[] = "HR";
    Employee13_02 employee2(name2, 40, department2, 70000.0);

    employee2 = employee1; // 使用赋值运算符

    assert(strcmp(employee2._name, "Dave") == 0);
    assert(employee2._age == 35);
    assert(strcmp(employee2._department, "Sales") == 0);
    assert(employee2._salary == 50000.0);
    cout << "testAssignmentOperator passed!" << endl;
}

void testAverageCalculation() {
    // 测试平均工资计算
    char name[] = "Frank";
    char department[] = "Finance";
    Employee13_02 employee(name, 50, department, 90000.0);

    double totalSalary = 180000.0;
    int totalEmployees = 2;

    double avg = employee.average(totalEmployees, totalSalary);
    assert(avg == 45000.0); // 90000 / 2
    cout << "testAverageCalculation passed!" << endl;
}

void testDisplay() {
    // 测试 display 方法
    char name[] = "Grace";
    char department[] = "IT";
    Employee13_02 employee(name, 32, department, 75000.0);

    employee.display(); // 应该输出 "Grace 32 IT"
    cout << "testDisplay passed!" << endl;
}

void test13_02() {
	testPersonCreation();
	testEmployeeCreation();
	testCopyConstructor1();
	testAssignmentOperator1();
	testAverageCalculation();
	testDisplay();
}