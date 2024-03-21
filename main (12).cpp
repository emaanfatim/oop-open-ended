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
class Teacher {
private:
    string teacherID;

public:
    string name;
    string email;
    ListNode* coursesTaught; 

    // Constructor
    Teacher() : coursesTaught(nullptr) {}

   
    ~Teacher() {
        while (coursesTaught != nullptr) {
            ListNode* temp = coursesTaught;
            coursesTaught = coursesTaught->next;
            delete temp;
        }
    }

    void getInformation() {
        cout << "^^^^^^^^^^^Teacher's information^^^^^^^^^^^^" << endl;
        cout << "Enter Teacher ID: ";
        cin.ignore();
        getline(cin, teacherID);
        cout << "Enter Teacher Name: ";
        getline(cin, name);
        cout << "Enter Teacher Email: ";
        getline(cin, email);
        cout << endl; // Add an extra newline for better formatting
    }

    void enrollCourse(const string& course) {
        ListNode* newNode = new ListNode(course);
        newNode->next = coursesTaught;
        coursesTaught = newNode;
    }

    void assignCourses() {
        // Define available courses
        vector<string> courses = { "OOP", "Linear Algebra", "Discrete Structure", "ISE", "ECS", "OOP Lab", "Islamiyat" };

        cout << "Available courses:\n";
        for (int i = 0; i < courses.size(); ++i) {
            cout << i + 1 << ". " << courses[i] << endl;
        }

        cout << "Enter the numbers corresponding to the courses you want to teach (Max 3): ";
        int choice;
        vector<int> selectedCourses; // Use vector to store selected course indices

        for (int i = 0; i < 3; ++i) {
            cin >> choice;
            bool isValid = choice >= 1 && choice <= courses.size();
            bool isUnique = true;

        
            if (!isValid) {
                cout << "Invalid course number. Please enter a valid number between 1 and " << courses.size() << endl;
                i--; 
                continue;
            }

            // Check if choice is unique
            for (int courseIndex : selectedCourses) {
                if (courseIndex == choice) {
                    isUnique = false;
                    break;
                }
            }

            if (isUnique) {
                selectedCourses.push_back(choice); // Insert course index into vector
            }
            else {
                cout << "Course already selected. Please enter a unique number." << endl;
                i--; // Decrement i to allow the user to enter the number again
            }
        }

        cin.ignore(); // clear input buffer

        cout << "Courses assigned to " << name << " are: ";
        for (int i = 0; i < selectedCourses.size(); ++i) {
            cout << courses[selectedCourses[i] - 1];
            if (i != selectedCourses.size() - 1) { // Check if not the last course
                cout << ", ";
            }
            enrollCourse(courses[selectedCourses[i] - 1]); 
        }
        cout << endl;
    }

    void viewCourses(bool displayDetails = true) {
        if (name.empty()) {
            cout << "No courses assigned." << endl;
            return;
        }

        if (displayDetails) {
            cout << "Courses assigned to " << name << " are: " << endl;
            ListNode* current = coursesTaught;
            while (current != nullptr) {
                cout << "Course: " << current->course << endl;
                cout << "Teacher ID: " << teacherID << endl;
                cout << "Teacher Name: " << name << endl;
                cout << "Teacher Email: " << email << endl;
                cout << "-----------------------------------------" << endl;
                current = current->next;
            }
        }
        else {
            cout << "Courses assigned to " << name << " are: ";
            ListNode* current = coursesTaught;
            while (current != nullptr) {
                cout << current->course;
                if (current->next != nullptr) {
                    cout << ", ";
                }
                current = current->next;
            }
            cout << endl;
        }
    }

    // Function to remove courses assigned to the teacher
    void removeTeacherCourse() {
        if (coursesTaught == nullptr) {
            cout << "No courses assigned to " << name << "." << endl;
            return;
        }

        cout << "Courses removed for " << name << ":" << endl;
        while (coursesTaught != nullptr) {
            ListNode* temp = coursesTaught;
            coursesTaught = coursesTaught->next;
            cout << "Removed Course: " << temp->course << endl;
            delete temp;
        }
    }

    void saveToFile(const string& filename) {
        ofstream file(filename);
        if (file.is_open()) {
            file << name << endl;
            file << email << endl;
            file << teacherID << endl;
            ListNode* current = coursesTaught;
            while (current != nullptr) {
                file << current->course << endl;
                current = current->next;
            }
            file.close();
        }
        else {
            cout << "Unable to open file for writing." << endl;
        }
    }

    // Function to load teacher information from a file
    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            string line;
            getline(file, name);
            getline(file, email);
            getline(file, teacherID);
            while (getline(file, line)) {
                enrollCourse(line);
            }
            file.close();
        }
        else {
            cout << "Unable to open file for reading." << endl;
        }
    }
};
class Course {
private:
    string courseCode;
    string courseName;
    Teacher teacher;
    vector<Student*> studentsEnrolled; // Use a vector to store enrolled students

public:
    Course(string code, string name, Teacher t) : courseCode(code), courseName(name), teacher(t) {}

    // You can add member functions for managing students enrolled, such as:
    void addStudent(Student* s) {
        studentsEnrolled.push_back(s);
    }

    void removeStudent(Student* s) {
        for (auto it = studentsEnrolled.begin(); it != studentsEnrolled.end(); ++it) {
            if (*it == s) {
                studentsEnrolled.erase(it);
                return;
            }
        }
        cout << "Student not found in the enrolled list." << endl;
    }

    void viewStudents() {
        if (studentsEnrolled.size() == 0) {
            cout << "No students enrolled in this course." << endl;
        }
        else {
            cout << "Enrolled Students:" << endl;
            for (Student* s : studentsEnrolled) {
                cout << s->name << endl;
            }
        }
    }
    // Function to save course information to a file
    void saveToFile(const string& filename) {
        ofstream file(filename);
        if (file.is_open()) {
            file << courseCode << endl;
            file << courseName << endl;
            
            teacher.saveToFile(filename + "_teacher.txt");
           
            for (Student* s : studentsEnrolled) {
                file << s->name << endl;
            }
            file.close();
        }
        else {
            cout << "Unable to open file for writing." << endl;
        }
    }

    // Function to load course information from a file
    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            getline(file, courseCode);
            getline(file, courseName);
            // Load teacher information
            teacher.loadFromFile(filename + "_teacher.txt");
            // Load enrolled student names
            string studentName;
            while (getline(file, studentName)) {
                // Assuming Student objects are managed elsewhere
                // Create Student objects using names and add them to studentsEnrolled vector
            }
            file.close();
        }
        else {
            cout << "Unable to open file for reading." << endl;
        }
    }
};
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
        else if (p == 2) {
    Teacher teacher;
    int choice;
    bool continueLoop = true; // Flag to control the loop

    while (continueLoop) { // Loop until the user chooses to exit
        cout << "Select one from the following\n1. Enter Teacher Information\n2. Assign Courses\n3. View Courses\n4. Remove Courses\n5. Exit\n";
        cin >> choice;

        switch (choice) {
        case 1:
            teacher.getInformation();
            cout << "--------------------------------------------------" << endl;
            break;
        case 2:
            teacher.assignCourses();
            cout << "--------------------------------------------------" << endl;
            teacher.viewCourses(false); 
            cout << "--------------------------------------------------" << endl;
            break;
        case 3:
            teacher.viewCourses(); 
            cout << "--------------------------------------------------" << endl;
            break;
        case 4:
            teacher.removeTeacherCourse();
            cout << "--------------------------------------------------" << endl;
            teacher.viewCourses(); 
            cout << "--------------------------------------------------" << endl;
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
else if (p == 3) {

    Teacher teacher;
    teacher.getInformation(); // Assuming you want to get teacher information here

  
    Course course("CSE101", "Introduction to Computer Science", teacher);

    int choice;
    bool continueLoop = true; // Flag to control the loop

    while (continueLoop) { 
        cout << "Select one from the following:\n1. Add Student\n2. Remove Student\n3. View Enrolled Students\n4. Save Course Information\n5. Load Course Information\n6. Exit\n";
        cin >> choice;

        switch (choice) {
        case 1: {
            // Add student to the course
            Student* newStudent = new Student();
            newStudent->getID();
            course.addStudent(newStudent);
            cout << "Student added to the course." << endl;
            break;
        }
        case 2: {
            // Remove student from the course
            string studentName;
            cout << "Enter the name of the student you want to remove: ";
            cin.ignore();
            getline(cin, studentName);
            break;
        }
        case 3:
            // View enrolled students in the course
            course.viewStudents();
            break;
        case 4: {
            // Save course information to a file
            string filename;
            cout << "Enter the filename to save course information: ";
            cin >> filename;
            course.saveToFile(filename);
            cout << "Course information saved successfully." << endl;
            break;
        }
        case 5: {
            // Load course information from a file
            string filename;
            cout << "Enter the filename to load course information: ";
            cin >> filename;
            course.loadFromFile(filename);
            cout << "Course information loaded successfully." << endl;
            break;
        }
        case 6:
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
