#ifndef SMS_hpp
#define SMS_hpp

#include "AccountList.hpp"
#include "ClassList.hpp"
#include "CourseList.h"
#include "menu.h"
#include "control.h"
#include "login.h"
#include <sstream>

class StudentManagementSystem {
private:
    AccountList acclist;
    ClassList classlist;
	Account AccountLogin;
	CourseList courselist;
public:
    void Reload();
	void ChangePassWord();
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
	void CreateNewLecturer();
	void ViewAllLecturers();
	void ImportCourse(); 
	void AddACourse();
	void EditCourse(); // NOT TESTED YET :V AND NOT DONE YET :V
	void RemoveCourse();
	void AddAStudentToCourse();
	void RemoveAStudentFromCourse();
	string ViewListCourse(string year, string semester);
	string ViewCourse(string &year, string &semester);
	string ViewListStudentInCourse();
	void EditGrade();
	void Checkin();
	void EditAttend();
	void ViewCheckinResult();
	void Lecturer_ViewCourse();
	void Student_ViewSchedule();
	void Do(string & choose);

	void Lecturer_ViewAttendance();

	void Lecturer_ViewScoreboard();

	void Student_ViewScore();

	void Menu(menu & x);

	void ViewProfile();

	void Run();
	/*
		show login
		check login
		load data
		perform task
	*/
};
#endif // SMS_hpp