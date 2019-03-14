#ifndef SMS_hpp
#define SMS_hpp

#include "AccountList.hpp"
#include "ClassList.hpp"
#include "CourseList.h"
#include "main_menu.h"

class StudentManagementSystem {
private:
    AccountList acclist;
    ClassList classlist;
	string accountLogin;
public:
    void Reload();
    void ImportClass();
    void AddNewStudent();
    void EditExistStudent();
    void RemoveStudent();
    void ChangeClassOfStudent();
    void ViewListClasses();
    void ViewListStudentsOfClass();

	void ImportCourse();
	void Run();
	/*
		show login
		check login
		load data
		perform task
	*/
};
#endif // SMS_hpp