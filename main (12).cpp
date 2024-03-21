#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Forward declaration of student class
class Student;

// Node structure for the linked list
struct ListNode {
    string course;
    ListNode* next;

    // Constructor to initialize node with a course
    ListNode(const string& c) : course(c), next(nullptr) {}
};

// Declare removeCourse function
void removeCourse(ListNode*& head, const string& courseToRemove);
// Define the student class
class Student {
private:
    string studentID;
    // Define LinkedList class to manage enrolled courses
    class LinkedList {
    private:
        struct Node {
            string courseName;
            string courseCode;
            Node* next;
            // Constructor
            Node(const string& name, const string& code, Node* nextNode = nullptr) : courseName(name), courseCode(code), next(nextNode) {}
        };
        Node* head;
    public:
        LinkedList() : head(nullptr) {}
        ~LinkedList() {
            while (head) {
                Node* temp = head;
                head = head->next;
                delete temp;
            }
        }
        void addCourse(const string& name, const string& code) {
            if (!head) {
                head = new Node(name, code);
            }
            else {
                Node* temp = head;
                while (temp->next) {
                    temp = temp->next;
                }
                temp->next = new Node(name, code);
            }
        }
        void dropCourse(const string& code) {
            if (!head) {
                cout << "No courses enrolled." << endl;
                return;
            }
            if (head->courseCode == code) {
                Node* temp = head;
                head = head->next;
                delete temp;
                cout << "Course " << code << " dropped successfully." << endl;
                return;
            }
            Node* prev = head;
            Node* curr = head->next;
            while (curr && curr->courseCode != code) {
                prev = curr;
                curr = curr->next;
            }
            if (curr) {
                prev->next = curr->next;
                delete curr;
                cout << "Course " << code << " dropped successfully." << endl;
            }
            else {
                cout << "Course " << code << " not found." << endl;
            }
        }
        void displayCourses() {
            if (!head) {
                cout << "No courses enrolled." << endl;
                return;
            }
            Node* temp = head;
            while (temp) {
                cout << temp->courseName << " (" << temp->courseCode << ")" << endl;
                temp = temp->next;
            }
        }
    };
    LinkedList coursesEnrolled;

public:
    string name, email;
    int n;

    void getID() {
        cout << "Enter your Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter your student ID: ";
        cin >> studentID;
        cout << "Enter your Email ID: ";
        cin >> email;

    }

    void getData() {
        cout << "Name: " << name << endl;
        cout << "Student ID: " << studentID << endl;
        cout << "Email ID: " << email << endl;
    }
    void enrollCourses() {
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
        }
        else if (n > 8) {
            cout << "You can enroll only 8 courses per semester. Enter valid number of courses: ";
            cin >> n;
        }
        else {
            cout << "Invalid number. Enter a valid number: ";
            cin >> n;
        }
    }

    void getInfo() {
        cout << "Number of courses: " << n << endl;
        cout << "Enrolled Courses:" << endl;
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

    // Function to save student information to a file
    void saveToFile(const string& filename) {
        ofstream file(filename);
        if (file.is_open()) {
            file << name << endl;
            file << email << endl;
            file << studentID << endl;
            file << n << endl;
            coursesEnrolled.displayCourses(); // Display courses in the console
            file.close();
        }
        else {
            cout << "Unable to open file for writing." << endl;
        }
    }

    // Function to load student information from a file
    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            string line;
            getline(file, name);
            getline(file, email);
            getline(file, studentID);
            file >> n;
            getline(file, line);
            for (int i = 0; i < n; ++i) {
                getline(file, line);
                // Assuming course details are formatted as "Course Name (Course Code)"
                // Parse course name and code and enroll the course
                // Example: "Discrete Structures (DS)"
                size_t pos = line.find_last_of("("); // Find position of '('
                string courseName = line.substr(0, pos - 1); // Extract course name
                string courseCode = line.substr(pos + 1, line.size() - pos - 2); // Extract course code
                coursesEnrolled.addCourse(courseName, courseCode); // Enroll the course
            }
            file.close();
        }
        else {
            cout << "Unable to open file for reading." << endl;
        }
    }
};
// Declare removeCourse function
void removeCourse(ListNode*& head, const string& courseToRemove) {
    ListNode* current = head;
    ListNode* prev = nullptr;

    while (current != nullptr && current->course != courseToRemove) {
        prev = current;
        current = current->next;
    }

    if (current != nullptr) {
        if (prev == nullptr) {
            head = current->next;
        }
        else {
            prev->next = current->next;
        }
        delete current;
        cout << "Course '" << courseToRemove << "' removed successfully." << endl; // Corrected line
    }
    else {
        cout << "Course '" << courseToRemove << "' not found." << endl;
    }
}
int main() {
    cout << "--------------------------------------------------" << endl;
    cout << "         UNIVERSITY MANAGEMENT SYSTEM             " << endl;
    cout << "--------------------------------------------------" << endl;
    int p;
    cout << "Menu\n1.Student\n2.Teacher\n3.Course\n4.Exit\n";
    cin >> p;

    if (p == 1) {
        Student s1;
        int i;
        bool continueLoop = true; // Flag to control the loop

        while (continueLoop) { // Loop until the user chooses to exit
            cout << "Select one from the following:\n1.Info\n2.Enroll Courses\n3.View courses\n4.Drop courses\n5.Exit\n";
            cin >> i;

            switch (i) {
                case 1:
                    s1.getID();
                    cout<<"--------------------------------------------------"<<endl;
                    s1.getData();
                     cout<<"--------------------------------------------------"<<endl;
                    break;
                case 2:
                    s1.enrollCourses();
                     cout<<"--------------------------------------------------"<<endl;
                    s1.getInfo();
                     cout<<"--------------------------------------------------"<<endl;
                    break;
                case 3:
                    s1.viewCourses();
                     cout<<"--------------------------------------------------"<<endl;
                    break;
                case 4:
                    s1.dropCourses();
                     cout<<"--------------------------------------------------"<<endl;
                    s1.getInfo(); // Display updated enrolled courses list
                     cout<<"--------------------------------------------------"<<endl;
                    break;
                case 5:
                    continueLoop = false; // Exit the loop
                    break;
                default:
                    cout << "Select a valid number." << endl;
                    break;
            }
        }
    }
    else if (p == 4) {
        cout << "Exiting program..." << endl;
        return 0; // Exit the program
    }
    else {
        cout << "Invalid choice. Please select a number from 1 to 4." << endl;
    }

    return 0;
}
