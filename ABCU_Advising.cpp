//============================================================================
// Name        : ABCU Advising.cpp
// Author      : Terry Christmas
// Version     : 1.0
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

class Course {
public:
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;

    Course(const string& number, const string& title, const vector<string>& prereqs) {
        courseNumber = number;
        courseTitle = title;
        prerequisites = prereqs;
    }
};

class BinarySearchTree {
private:
    struct Node {
        Course course;
        Node* left;
        Node* right;

        Node(const Course& c) : course(c), left(nullptr), right(nullptr) {}
    };

    Node* root;

    // Insert a course into the binary search tree
    void insert(Node*& node, const Course& course) {
        if (node == nullptr) {
            node = new Node(course);
        }
        else if (course.courseNumber < node->course.courseNumber) {
            insert(node->left, course);
        }
        else if (course.courseNumber > node->course.courseNumber) {
            insert(node->right, course);
        }
    }

    // Find a course by its course number
    Course* find(Node* node, const string& courseNumber) {
        if (node == nullptr) {
            return nullptr;
        }
        else if (courseNumber == node->course.courseNumber) {
            return &node->course;
        }
        else if (courseNumber < node->course.courseNumber) {
            return find(node->left, courseNumber);
        }
        else {
            return find(node->right, courseNumber);
        }
    }

    // In-order traversal to print the course list
    void inOrderTraversal(Node* node) {
        if (node != nullptr) {
            inOrderTraversal(node->left);
            cout << node->course.courseNumber << ", " << node->course.courseTitle << endl;
            inOrderTraversal(node->right);
        }
    }

public:
    BinarySearchTree() : root(nullptr) {}

    // Insert a course into the binary search tree
    void insertCourse(const Course& course) {
        insert(root, course);
    }

    // Find a course by its course number
    Course* findCourse(const string& courseNumber) {
        return find(root, courseNumber);
    }

    // Print the course list using in-order traversal
    void printCourseList() {
        inOrderTraversal(root);
    }
};

int main() {
    BinarySearchTree courseTree;
    string fileName;
    int choice;
 
    //Menu
    while (true) {
        cout << "Welcome to the ABCU Advising course planner." << endl;
        cout << "1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "4. Exit" << endl;
        cout << "What would you like to do? ";

        string choiceStr;
        getline(cin, choiceStr);

        if (choiceStr.empty() || choiceStr.find_first_not_of("0123456789") != string::npos) {
            cout << "Invalid input. Please enter a valid option." << endl;
            continue;
        }
        choice = stoi(choiceStr);

        if (choice == 1) {
            cout << "Enter the name of the course data file: ";
            getline(cin, fileName);

            ifstream inputFile(fileName);

            if (!inputFile.is_open()) {
                cerr << "Error: Unable to open the file." << endl;
                continue; // Continue to the main menu
            }

            string line;
            while (getline(inputFile, line)) {
                istringstream iss(line);
                string courseNumber, courseTitle, prerequisitesString;
                vector<string> prerequisites;

                getline(iss, courseNumber, ',');
                getline(iss, prerequisitesString);

                istringstream prereqStream(prerequisitesString);
                getline(prereqStream, courseTitle, ',');
                string prereq;
                while (getline(prereqStream, prereq, ',')) {
                    prerequisites.push_back(prereq);
                }

                Course course(courseNumber, courseTitle, prerequisites);
                courseTree.insertCourse(course);
            }

            cout << "Data structure loaded successfully." << endl;
        }
        else if (choice == 2) {
            cout << "Here is a sample schedule:" << endl;
            courseTree.printCourseList();
        }
        else if (choice == 3) {
            string courseNumber;
            cout << "What course do you want to know about? ";
            cin >> courseNumber;
            cin.ignore();

            Course* foundCourse = courseTree.findCourse(courseNumber);
            if (foundCourse) {
                cout << foundCourse->courseNumber << ", " << foundCourse->courseTitle << endl;
                if (!foundCourse->prerequisites.empty()) {
                    cout << "Prerequisites: ";
                    for (const auto& prereq : foundCourse->prerequisites) {
                        cout << prereq << " ";
                    }
                    cout << endl;
                }
            }
            else {
                cout << "Course not found." << endl;
            }
        }
        else if (choice == 4) {
            cout << "Thank you for using ABCU Advising course planner!" << endl;
            break;
        }
        else {
            cout << "Invalid option. Please enter a valid choice." << endl;
        }
    }

    return 0;
}
