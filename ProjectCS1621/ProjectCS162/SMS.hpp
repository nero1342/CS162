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

	void ImportCourse(); 
	void CreateAcademicYear();
	void CreateSemester();
	void DeleteAcademicYear();
	void DeleteSemester();
	void ViewAcademicYear();
	void ViewSemester();
	
	void ImportScoreboard();
	void ExportScoreboard();
	void ExportAttendaceList();
	void ViewScoreboard();

	void AddACourse();
	void EditCourse(); // NOT TESTED YET :V AND NOT DONE YET :V
	void RemoveCourse();
	void RemoveAStudentFromCourse();
	void ViewListCourse();

	void Do(string & choose);

	void Run();
	/*
		show login
		check login
		load data
		perform task
	*/
};
#endif // SMS_hpp