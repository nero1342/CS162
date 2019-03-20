#ifndef SMS_hpp
#define SMS_hpp

#include "AccountList.hpp"
#include "ClassList.hpp"
#include "CourseList.h"
#include "menu.h"
#include "control.h"
#include "login.h"

class StudentManagementSystem {
private:
    AccountList acclist;
    ClassList classlist;
	string accountLogin;
	CourseList courselist;
public:
    void Reload();
    void ImportClass(); // Checked
    void AddNewStudent(); // Checked
    void EditExistStudent();
    void RemoveStudent(); // Checked
    void ChangeClassOfStudent(); // Checked
    void ViewListClasses();
    void ViewListStudentsOfClass();

	void CreateAcademicYear();
	void CreateSemester();
	void DeleteAcademicYear();
	void DeleteSemester();
	void ImportCourse(); 
	/*
		need to add create account for lecturer in file course.h function CreateAccountForLecturer();
	*/
	
	void Do(string & choose);
	void AddACourse();
	void EditCourse(); // NOT TESTED YET :V AND NOT DONE YET :V
	void RemoveCourse();
	void RemoveAStudentFromCourse();

	void Run();
	/*
		show login
		check login
		load data
		perform task
	*/
};
#endif // SMS_hpp