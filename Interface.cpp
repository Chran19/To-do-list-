#include <GL/glut.h>
#include <vector>
#include <string>
#include <iostream>
#include <map>

using namespace std;

class Task {
private:
    string name;
    string description;
    string dueDate;
    bool completed;
    string priority;
    string category;

public:
    Task(const string& name, const string& description, const string& dueDate, const string& priority, const string& category)
        : name(name), description(description), dueDate(dueDate), completed(false), priority(priority), category(category) {}

    string getName() const { return name; }
    string getDescription() const { return description; }
    string getDueDate() const { return dueDate; }
    bool isCompleted() const { return completed; }
    string getPriority() const { return priority; }
    string getCategory() const { return category; }

    void setName(const string& name) { this->name = name; }
    void setDescription(const string& description) { this->description = description; }
    void setDueDate(const string& dueDate) { this->dueDate = dueDate; }
    void markCompleted() { completed = true; }
    void setPriority(const string& priority) { this->priority = priority; }
    void setCategory(const string& category) { this->category = category; }

    void display() const {
        cout << name << " (" << (completed ? "Completed" : "Pending") << ") - Due: " << dueDate 
             << " - Priority: " << priority << " - Category: " << category << endl
             << "   Description: " << description << endl;
    }
};

class ToDoList {
private:
    vector<Task> tasks;
    map<string, vector<Task>> categories;

    void displayMenu() const {
        cout << "\n---------- To-Do List Menu -----------\n"
             << "1. Add Task\n"
             << "2. Delete Task\n"
             << "3. Display Tasks\n"
             << "4. Mark Task as Completed\n"
             << "5. Edit Task\n"
             << "6. Search Tasks\n"
             << "7. Filter by Category\n"
             << "8. Set Recurring Tasks\n"
             << "9. Exit\n"
             << "-----------------------------------------\n";
    }

    void displayTasks() const {
        if (tasks.empty()) {
            cout << "No tasks to display!" << endl;
            return;
        }
        cout << "Tasks:" << endl;
        for (size_t i = 0; i < tasks.size(); ++i) {
            cout << i + 1 << ". ";
            tasks[i].display();
        }
    }

public:
    vector<Task>& getTasks() { return tasks; }

    void handleAddTask() {
        string name, description, dueDate, priority, category;
        cout << "Enter task name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter task description: ";
        getline(cin, description);
        cout << "Enter task due date (YYYY-MM-DD): ";
        getline(cin, dueDate);
        cout << "Enter task priority (High/Medium/Low): ";
        getline(cin, priority);
        cout << "Enter task category: ";
        getline(cin, category);

        Task newTask(name, description, dueDate, priority, category);
        tasks.push_back(newTask);
        categories[category].push_back(newTask);
        cout << "Task added successfully!" << endl;
    }

    void handleDeleteTask() {
        if (tasks.empty()) {
            cout << "No tasks to delete!" << endl;
            return;
        }
        displayTasks();
        size_t taskNumber;
        cout << "Enter the task number to delete: ";
        cin >> taskNumber;
        if (taskNumber > 0 && taskNumber <= tasks.size()) {
            string category = tasks[taskNumber - 1].getCategory();
            tasks.erase(tasks.begin() + taskNumber - 1);
            auto& categoryTasks = categories[category];
            categoryTasks.erase(categoryTasks.begin() + taskNumber - 1);
            if (categoryTasks.empty()) {
                categories.erase(category);
            }
            cout << "Task deleted successfully!" << endl;
        } else {
            cout << "Invalid task number!" << endl;
        }
    }

    void handleMarkTaskCompleted() {
        if (tasks.empty()) {
            cout << "No tasks to mark as completed!" << endl;
            return;
        }
        displayTasks();
        size_t taskNumber;
        cout << "Enter the task number to mark as completed: ";
        cin >> taskNumber;
        if (taskNumber > 0 && taskNumber <= tasks.size()) {
            tasks[taskNumber - 1].markCompleted();
            cout << "Task marked as completed!" << endl;
        } else {
            cout << "Invalid task number!" << endl;
        }
    }

    void handleEditTask() {
        if (tasks.empty()) {
            cout << "No tasks to edit!" << endl;
            return;
        }
        displayTasks();
        size_t taskNumber;
        cout << "Enter the task number to edit: ";
        cin >> taskNumber;
        if (taskNumber > 0 && taskNumber <= tasks.size()) {
            Task& task = tasks[taskNumber - 1];
            string name, description, dueDate, priority, category;
            cout << "Enter new task name (current: " << task.getName() << "): ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter new task description (current: " << task.getDescription() << "): ";
            getline(cin, description);
            cout << "Enter new task due date (current: " << task.getDueDate() << "): ";
            getline(cin, dueDate);
            cout << "Enter new task priority (current: " << task.getPriority() << "): ";
            getline(cin, priority);
            cout << "Enter new task category (current: " << task.getCategory() << "): ";
            getline(cin, category);

            task.setName(name);
            task.setDescription(description);
            task.setDueDate(dueDate);
            task.setPriority(priority);
            task.setCategory(category);

            cout << "Task updated successfully!" << endl;
        } else {
            cout << "Invalid task number!" << endl;
        }
    }

    void handleSearchTasks() const {
        string searchTerm;
        cout << "Enter search term: ";
        cin.ignore();
        getline(cin, searchTerm);

        cout << "Search Results:" << endl;
        bool found = false;
        for (size_t i = 0; i < tasks.size(); ++i) {
            if (tasks[i].getName().find(searchTerm) != string::npos ||
                tasks[i].getDescription().find(searchTerm) != string::npos ||
                tasks[i].getCategory().find(searchTerm) != string::npos) {
                cout << i + 1 << ". ";
                tasks[i].display();
                found = true;
            }
        }
        if (!found) {
            cout << "No tasks found with the term: " << searchTerm << endl;
        }
    }

    void handleFilterByCategory() const {
        string filterCategory;
        cout << "Enter category to filter by: ";
        cin.ignore();
        getline(cin, filterCategory);

        auto it = categories.find(filterCategory);
        if (it != categories.end()) {
            cout << "Tasks in category " << filterCategory << ":" << endl;
            for (size_t i = 0; i < it->second.size(); ++i) {
                cout << i + 1 << ". ";
                it->second[i].display();
            }
        } else {
            cout << "No tasks found in category: " << filterCategory << endl;
        }
    }

    void handleSetRecurringTasks() {
        cout << "This feature is not yet implemented in this example." << endl;
    }
};

ToDoList toDoList;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    for (size_t i = 0; i < toDoList.getTasks().size(); ++i) {
        string taskStr = toDoList.getTasks()[i].getName() + " - " + toDoList.getTasks()[i].getDueDate();
        glRasterPos2f(-0.9, 0.9 - i * 0.1);
        for (char c : taskStr) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
        }
    }

    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int screenWidth = glutGet(GLUT_WINDOW_WIDTH);
        int screenHeight = glutGet(GLUT_WINDOW_HEIGHT);
        float normalizedX = (float)x / (screenWidth / 2) - 1.0f;
        float normalizedY = 1.0f - (float)y / (screenHeight / 2);

        if (normalizedX >= -0.9 && normalizedX <= -0.7 && normalizedY >= 0.8 && normalizedY <= 0.9) {
            toDoList.handleAddTask();
            glutPostRedisplay();
        }
    }
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'a':
            toDoList.handleAddTask();
            break;
        case 'd':
            toDoList.handleDeleteTask();
            break;
        case 'm':
            toDoList.handleMarkTaskCompleted();
            break;
        case 'e':
            toDoList.handleEditTask();
            break;
        case 's':
            toDoList.handleSearchTasks();
            break;
        case 'f':
            toDoList.handleFilterByCategory();
            break;
        case 27:
            exit(0);
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void initOpenGL() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("To-Do List");

    initOpenGL();

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}
