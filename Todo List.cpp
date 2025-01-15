#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Task {
public:
    string title;
    string description;
    bool isCompleted;

    Task(const string& t, const string& d) : title(t), description(d), isCompleted(false) {}

    void markComplete() {
        isCompleted = true;
    }
};

class TaskManager {
private:
    vector<Task> tasks;

public:
    void addTask(const string& title, const string& description) {
        tasks.emplace_back(title, description);
        cout << "Task added successfully." << endl;
    }

    void listTasks() {
        if (tasks.empty()) {
            cout << "No tasks available." << endl;
            return;
        }

        cout << "Task List:" << endl;
        for (size_t i = 0; i < tasks.size(); ++i) {
            cout << i + 1 << ". [" << (tasks[i].isCompleted ? "X" : " ") << "] "
                << tasks[i].title << " - " << tasks[i].description << "\n";
        }
    }

    void markTaskComplete(int index) {
        if (index < 1 || index > tasks.size()) {
            cout << "Invalid task number." << endl;
            return;
        }

        tasks[index - 1].markComplete();
        cout << "Task marked as complete." << endl;
    }

    void deleteTask(int index) {
        if (index < 1 || index > tasks.size()) {
            cout << "Invalid task number." << endl;
            return;
        }

        tasks.erase(tasks.begin() + index - 1);
        cout << "Task deleted successfully." << endl;
    }

    void saveToFile(const string& filename) {
        ofstream file(filename);
        if (!file) {
            cout << "Error opening file for saving." << endl;
            return;
        }

        for (const auto& task : tasks) {
            file << task.title << "|" << task.description << "|" << task.isCompleted << "\n";
        }
        file.close();
        cout << "Tasks saved to " << filename << "." << endl;
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cout << "Error opening file for loading." << endl;
            return;
        }

        tasks.clear();
        string title, description, isCompletedStr;
        while (getline(file, title, '|') && getline(file, description, '|') && getline(file, isCompletedStr)) {
            Task task(title, description);
            task.isCompleted = (isCompletedStr == "1");
            tasks.push_back(task);
        }
        file.close();
        cout << "Tasks loaded from " << filename << "." << endl;
    }
};

int main() {
    TaskManager manager;
    int choice;

    do {
        cout << "\nTask Manager" << endl;
        cout << "1. Add Task" << endl;
        cout << "2. List Tasks" << endl;
        cout << "3. Mark Task Complete" << endl;
        cout << "4. Delete Task" << endl;
        cout << "5. Save Tasks to File" << endl;
        cout << "6. Load Tasks from File" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        cin.ignore(); 

        if (choice == 1) {
            string title, description;
            cout << "Enter task title: ";
            getline(cin, title);
            cout << "Enter task description: ";
            getline(cin, description);
            manager.addTask(title, description);
        }
        else if (choice == 2) {
            manager.listTasks();
        }
        else if (choice == 3) {
            int taskNum;
            cout << "Enter task number to mark complete: ";
            cin >> taskNum;
            manager.markTaskComplete(taskNum);
        }
        else if (choice == 4) {
            int taskNum;
            cout << "Enter task number to delete: ";
            cin >> taskNum;
            manager.deleteTask(taskNum);
        }
        else if (choice == 5) {
            manager.saveToFile("tasks.txt");
        }
        else if (choice == 6) {
            manager.loadFromFile("tasks.txt");
        }
        else if (choice != 7) {
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 7);

    cout << "See you next time!" << endl;
    return 0;
}
