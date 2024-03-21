#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Node structure for the linked list
struct ListNode {
    string course;
    ListNode* next;

    // Constructor to initialize node with a course
    ListNode(const string& c) : course(c), next(nullptr) {}
};

// Function to remove a course from the linked list
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
        cout << "Course '" << courseToRemove << "' removed successfully." << endl;
    }
    else {
        cout << "Course '" << courseToRemove << "' not found." << endl;
    }
}

class Teacher {
private:
    string TeacherID;

public:
    string name;
    string email;
    ListNode* coursesTaught; // Head of the linked list

    // Constructor
    Teacher() : coursesTaught(nullptr) {}

    // Destructor to deallocate memory
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
        getline(cin, TeacherID);
        cout << "Enter Teacher Name: ";
        getline(cin, name);
        cout << "Enter Teacher Email: ";
        getline(cin, email);
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

            // Check if choice is within valid range
            if (!isValid) {
                cout << "Invalid course number. Please enter a valid number between 1 and " << courses.size() << endl;
                i--; // Decrement i to allow the user to enter the number again
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
            enrollCourse(courses[selectedCourses[i] - 1]); // Enroll the course
        }
        cout << endl;
    }

    void viewCourses(bool displayDetails = true) {
        if (displayDetails) {
            cout << "Courses assigned to " << name << " are: " << endl;
            ListNode* current = coursesTaught;
            while (current != nullptr) {
                cout << "Course: " << current->course << endl;
                cout << "Teacher ID: " << TeacherID << endl;
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
        cout << "How many courses do you want to remove? ";
        int numToRemove;
        cin >> numToRemove;

        for (int i = 0; i < numToRemove; ++i) {
            cout << "Enter the name of course " << i + 1 << " you want to remove: ";
            string courseToRemove;
            cin.ignore(); // clear input buffer
            getline(cin, courseToRemove);

            // Call the global removeCourse function
            removeCourse(coursesTaught, courseToRemove);
        }
    }
};

int main() {
    Teacher teacher;
    teacher.getInformation();
    teacher.assignCourses();
    teacher.viewCourses(false); // Display only course names

    teacher.removeTeacherCourse();
    teacher.viewCourses(); // Display complete details

    return 0;
}
