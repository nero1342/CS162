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
	Account AccountLogin;
	CourseList courselist;
public:
    void Reload();
    void ImportClass(); // Checked
    void AddNewStudent(); // Checked
    void EditExistStudent();
    void RemoveStudent(); // Checked
    void ChangeClassOfStudent(); // Checked
    void ViewListClasses();
  
	void CreateAcademicYear();
	void CreateSemester();
	void DeleteAcademicYear();
	void DeleteSemester();
	string ViewAcademicYear();
	string ViewSemester(string year);
	
	void ImportScoreboard();
	void ExportScoreboard();
	void ExportAttendaceList();
	void ViewScoreboard();
	void ViewAttendanceList();

	void ImportCourse(); 
	void AddACourse();
	void EditCourse(); // NOT TESTED YET :V AND NOT DONE YET :V
	void RemoveCourse();
	void AddAStudentToCourse();
	void RemoveAStudentFromCourse();
	string ViewListCourse(string year, string semester);
	string ViewCourse(string &year, string &semester);
	string ViewListStudentInCourse();
	void Do(string & choose);

	void Menu(menu & x);

	void Run();
	/*
		show login
		check login
		load data
		perform task
	*/
};
#endif // SMS_hpp