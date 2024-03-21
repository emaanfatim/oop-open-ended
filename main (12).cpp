#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Define a struct for a course
struct Course {
    string coursename;
    string code;
    
    Course(string n, string c): coursename(n), code(c) {}
};

// Define a LinkedList class to manage courses
class LinkedList {
private:
    vector<Course*> courses; // Use vector instead of linked list

public: 
    LinkedList() {}

    // Function to add a course to the linked list
    void addCourse(string coursename, string code) {
        courses.push_back(new Course(coursename, code));
    }
  
    // Function to display all courses in the linked list
    void displayCourses() {
        cout << "Courses:" << endl;
        for (Course* course : courses) {
            cout << "Course Name: " << course->coursename << ", Course Code: " << course->code << endl;
        }
    }

    // Function to drop a course from the linked list
    void dropCourse(string courseCode) {
        for (auto it = courses.begin(); it != courses.end(); ++it) {
            if ((*it)->code == courseCode) {
                delete *it;
                courses.erase(it);
                cout << "Course " << courseCode << " dropped successfully." << endl;
                return;
            }
        }
        cout << "Course " << courseCode << " not found in your enrolled courses." << endl;
    }
};

class student {
private:
    string studentID;
    LinkedList coursesEnrolled;

public:
    string name, email;
    int n;

    void getID() {
        cout << "Enter your Name: ";
        getline(cin, name);
        cout << "Enter your student ID: ";
        cin >> studentID;
        cout << "Enter your Email ID: ";
        cin >> email;
        cout << "Enter the number of courses in which you want to enroll: ";
        cin >> n;
        cin.ignore(); // Ignore newline character
        if (n <= 8 && n > 0) {
            cout << "Courses Offered\n 1. Discrete Structures(DS)\n2. Introduction to Software Engineering(ISE)\n3. Islamic Studies(IS)\n4. Effective Communication Skills(ECS)\n5. Understanding Quran\n6. Object-Oriented Programming(OOP)\n7. Object-Oriented Programming Lab(OOP Lab)\n8. Linear Algebra(LA)\n" << endl;

            for (int i = 0; i < n; i++) {
                cout << "Select the course from the list in which you want to get enrolled: ";
                int choice;
                cin >> choice;

                switch (choice) {
                    case 1:
                        coursesEnrolled.addCourse("Discrete Structures", "DS");
                        break;
                    case 2:
                        coursesEnrolled.addCourse("Introduction to Software Engineering", "ISE");
                        break;
                    case 3:
                        coursesEnrolled.addCourse("Effective Communication Skills", "ECS");
                        break;
                    case 4:
                        coursesEnrolled.addCourse("Islamic Studies", "IS");
                        break;
                    case 5:
                        coursesEnrolled.addCourse("Understanding Quran", "UQuran");
                        break;
                    case 6:
                        coursesEnrolled.addCourse("Object-Oriented Programming", "OOP");
                        break;
                    case 7:
                        coursesEnrolled.addCourse("Object-Oriented Programming Lab", "OOP Lab");
                        break;
                    case 8:
                        coursesEnrolled.addCourse("Linear Algebra", "LA");
                        break;
                    default:
                        cout << "Invalid choice! Please select from 1 to 8." << endl;
                        i--; // Decrement i to re-prompt for the same course slot
                        break;
                }
            }
        } else if (n > 8) {
            cout << "You can enroll only 8 courses per semester. Enter valid number of courses: ";
            cin >> n;
        } else {
            cout << "Invalid number. Enter a valid number: ";
            cin >> n;
        }
    }

    void getData() {
        cout << "Name: " << name << endl;
        cout << "Student ID: " << studentID << endl;
        cout << "Email ID: " << email << endl;
        cout << "Number of courses: " << n << endl;
        coursesEnrolled.displayCourses();
    } 

    void dropCourses() {
        int numCoursesToDrop;
        cout << "Enter the number of courses you want to drop: ";
        cin >> numCoursesToDrop;

        for (int i = 0; i < numCoursesToDrop; ++i) {
            string courseCode;
            cout << "Enter the code of the course you want to drop: ";
            cin >> courseCode;
            coursesEnrolled.dropCourse(courseCode);
        }
    }

    void viewCourses() {
        cout << "Enrolled Courses:" << endl;
        coursesEnrolled.displayCourses();
    }
};

int main() {
    student s1;
    s1.getID();
    s1.getData();
    s1.viewCourses();
    s1.dropCourses();
    s1.getData(); // Display updated enrolled courses list
    return 0;
}
