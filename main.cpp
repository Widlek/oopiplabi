#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <memory>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>

using namespace std;

// Базовый класс Employee
class Employee {
protected:
    string name;
    int id;
    string position;
    double salary;

    template<typename T>
    void safeInput(T& value, const string& prompt) {
        while (true) {
            cout << prompt;
            cin >> value;
            if (cin.good()) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            else {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Ошибка ввода. Пожалуйста, попробуйте снова.\n";
            }
        }
    }

public:
    Employee() : id(0), salary(0.0) {}
    virtual ~Employee() = default;

    virtual void display() const {
        cout << "Имя: " << name
            << ", ID: " << id
            << ", Должность: " << position
            << ", Зарплата: " << salary << endl;
    }

    virtual void input() {
        cout << "Введите имя сотрудника: ";
        getline(cin, name);

        safeInput(id, "Введите ID сотрудника: ");

        cout << "Введите должность сотрудника: ";
        getline(cin, position);

        safeInput(salary, "Введите зарплату сотрудника: ");
    }

    virtual void edit() {
        cout << "Редактирование сотрудника (оставьте пустым, чтобы не изменять):\n";

        string newName;
        cout << "Новое имя: ";
        getline(cin, newName);
        if (!newName.empty()) name = newName;

        string newId;
        cout << "Новый ID: ";
        getline(cin, newId);
        if (!newId.empty()) id = stoi(newId);

        string newPosition;
        cout << "Новая должность: ";
        getline(cin, newPosition);
        if (!newPosition.empty()) position = newPosition;

        string newSalary;
        cout << "Новая зарплата: ";
        getline(cin, newSalary);
        if (!newSalary.empty()) salary = stod(newSalary);
    }

    string getName() const { return name; }
    int getId() const { return id; }
    string getPosition() const { return position; }
    double getSalary() const { return salary; }

    void setName(const string& newName) { name = newName; }
    void setId(int newId) { id = newId; }
    void setPosition(const string& newPosition) { position = newPosition; }
    void setSalary(double newSalary) { salary = newSalary; }
};

// Класс Developer
class Developer : public Employee {
private:
    string programmingLanguage;
    string level;

public:
    Developer() : Employee() {
        position = "Developer";
    }

    void input() override {
        Employee::input();

        cout << "Введите основной язык программирования: ";
        getline(cin, programmingLanguage);

        int levelChoice;
        cout << "Выберите уровень разработчика:\n";
        cout << "1 - Junior\n";
        cout << "2 - Middle\n";
        cout << "3 - Senior\n";
        cout << "Ваш выбор: ";

        while (true) {
            cin >> levelChoice;
            if (cin.good() && levelChoice >= 1 && levelChoice <= 3) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            else {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Неверный выбор. Пожалуйста, введите цифру от 1 до 3: ";
            }
        }

        switch (levelChoice) {
        case 1: level = "Junior"; break;
        case 2: level = "Middle"; break;
        case 3: level = "Senior"; break;
        }
    }

    void display() const override {
        cout << "Разработчик: " << name
            << " (ID: " << id
            << ", Уровень: " << level
            << ", Язык: " << programmingLanguage
            << ", Зарплата: " << salary << ")" << endl;
    }

    void edit() override {
        Employee::edit();

        string newLang;
        cout << "Новый язык программирования: ";
        getline(cin, newLang);
        if (!newLang.empty()) programmingLanguage = newLang;

        string newLevel;
        cout << "Новый уровень (Junior/Middle/Senior): ";
        getline(cin, newLevel);
        if (!newLevel.empty()) level = newLevel;
    }

    string getProgrammingLanguage() const { return programmingLanguage; }
    string getLevel() const { return level; }

    void setProgrammingLanguage(const string& lang) { programmingLanguage = lang; }
    void setLevel(const string& lvl) { level = lvl; }
};

// Класс Manager
class Manager : public Employee {
private:
    int completedProjects;
    string methodology;

public:
    Manager() : Employee() {
        position = "Project Manager";
        completedProjects = 0;
    }

    void input() override {
        Employee::input();

        safeInput(completedProjects, "Введите количество успешно завершенных проектов: ");

        int methodologyChoice;
        cout << "Выберите методиологию управления:\n";
        cout << "1 - Agile\n";
        cout << "2 - Waterfall\n";
        cout << "3 - Scrum\n";
        cout << "4 - Kanban\n";
        cout << "5 - Другая\n";
        cout << "Ваш выбор: ";

        while (true) {
            cin >> methodologyChoice;
            if (cin.good() && methodologyChoice >= 1 && methodologyChoice <= 5) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            else {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Неверный выбор. Пожалуйста, введите цифру от 1 до 5: ";
            }
        }

        switch (methodologyChoice) {
        case 1: methodology = "Agile"; break;
        case 2: methodology = "Waterfall"; break;
        case 3: methodology = "Scrum"; break;
        case 4: methodology = "Kanban"; break;
        case 5:
            cout << "Введите название вашей методиологии: ";
            getline(cin, methodology);
            break;
        }
    }

    void display() const override {
        cout << "Менеджер проектов: " << name
            << " (ID: " << id
            << ", Завершенные проекты: " << completedProjects
            << ", Методиология: " << methodology
            << ", Зарплата: " << salary << ")" << endl;
    }

    void edit() override {
        Employee::edit();

        string newProjects;
        cout << "Новое количество завершенных проектов: ";
        getline(cin, newProjects);
        if (!newProjects.empty()) completedProjects = stoi(newProjects);

        string newMethodology;
        cout << "Новая методиология: ";
        getline(cin, newMethodology);
        if (!newMethodology.empty()) methodology = newMethodology;
    }

    int getCompletedProjects() const { return completedProjects; }
    string getMethodology() const { return methodology; }

    void setCompletedProjects(int projects) { completedProjects = projects; }
    void setMethodology(const string& method) { methodology = method; }
};

// Класс Team
class Team {
private:
    string teamName;
    vector<shared_ptr<Employee>> members;

public:
    Team(const string& name = "") : teamName(name) {}
    ~Team() = default;

    void addMember(shared_ptr<Employee> employee) {
        if (find(members.begin(), members.end(), employee) == members.end()) {
            members.push_back(employee);
        }
    }

    bool removeMember(shared_ptr<Employee> employee) {
        auto it = find(members.begin(), members.end(), employee);
        if (it != members.end()) {
            members.erase(it);
            return true;
        }
        return false;
    }

    bool removeMember(int id) {
        auto it = find_if(members.begin(), members.end(),
            [id](const shared_ptr<Employee>& emp) {
                return emp->getId() == id;
            });

        if (it != members.end()) {
            members.erase(it);
            return true;
        }
        return false;
    }

    shared_ptr<Employee> findMember(int id) const {
        auto it = find_if(members.begin(), members.end(),
            [id](const shared_ptr<Employee>& emp) {
                return emp->getId() == id;
            });

        return (it != members.end()) ? *it : nullptr;
    }

    bool contains(shared_ptr<Employee> employee) const {
        return find(members.begin(), members.end(), employee) != members.end();
    }

    void displayAllMembers() const {
        cout << "\n--- Состав команды '" << teamName << "' ---\n";
        if (members.empty()) {
            cout << "Команда пуста.\n";
            return;
        }

        for (const auto& member : members) {
            member->display();
        }
        cout << "--------------------------------\n";
    }

    void sortByName() {
        sort(members.begin(), members.end(),
            [](const shared_ptr<Employee>& a, const shared_ptr<Employee>& b) {
                return a->getName() < b->getName();
            });
    }

    void sortBySalary() {
        sort(members.begin(), members.end(),
            [](const shared_ptr<Employee>& a, const shared_ptr<Employee>& b) {
                return a->getSalary() < b->getSalary();
            });
    }

    void sortById() {
        sort(members.begin(), members.end(),
            [](const shared_ptr<Employee>& a, const shared_ptr<Employee>& b) {
                return a->getId() < b->getId();
            });
    }

    vector<shared_ptr<Employee>> findByPosition(const string& position) const {
        vector<shared_ptr<Employee>> result;
        copy_if(members.begin(), members.end(), back_inserter(result),
            [&position](const shared_ptr<Employee>& emp) {
                return emp->getPosition() == position;
            });
        return result;
    }

    string getTeamName() const { return teamName; }
    void setTeamName(const string& name) { teamName = name; }
    size_t getSize() const { return members.size(); }
    bool isEmpty() const { return members.empty(); }

    const vector<shared_ptr<Employee>>& getAllMembers() const {
        return members;
    }
};

// Класс Project
class Project {
private:
    string projectName;
    string description;
    tm startDate;
    tm endDate;
    Team team;

public:
    Project(const string& name = "", const string& desc = "")
        : projectName(name), description(desc) {
        time_t now = time(nullptr);
        startDate = *localtime(&now);
        endDate = *localtime(&now);
    }

    void setStartDate(int year, int month, int day) {
        startDate.tm_year = year - 1900;
        startDate.tm_mon = month - 1;
        startDate.tm_mday = day;
        mktime(&startDate);
    }

    void setEndDate(int year, int month, int day) {
        endDate.tm_year = year - 1900;
        endDate.tm_mon = month - 1;
        endDate.tm_mday = day;
        mktime(&endDate);
    }

    void display() const {
        cout << "\n=== Информация о проекте ===\n";
        cout << "Название: " << projectName << "\n";
        cout << "Описание: " << description << "\n";

        cout << "Дата начала: "
            << put_time(&startDate, "%d.%m.%Y") << "\n";
        cout << "Дата окончания: "
            << put_time(&endDate, "%d.%m.%Y") << "\n";

        cout << "Состав команды:\n";
        team.displayAllMembers();
        cout << "============================\n";
    }

    void addTeamMember(shared_ptr<Employee> employee) {
        team.addMember(employee);
    }

    bool removeTeamMember(int id) {
        return team.removeMember(id);
    }

    void displayTeam() const {
        team.displayAllMembers();
    }

    string getProjectName() const { return projectName; }
    void setProjectName(const string& name) { projectName = name; }

    string getDescription() const { return description; }
    void setDescription(const string& desc) { description = desc; }

    Team& getTeam() { return team; }
    const Team& getTeam() const { return team; }

    double calculateTotalCost() const {
        double totalCost = 0.0;
        for (const auto& member : team.getAllMembers()) {
            totalCost += member->getSalary();
        }
        return totalCost;
    }

    vector<shared_ptr<Employee>> findTeamMembersByPosition(const string& position) const {
        return team.findByPosition(position);
    }
};

// Глобальные контейнеры
vector<shared_ptr<Employee>> allEmployees;
vector<Team> allTeams;
vector<Project> allProjects;

// Вспомогательные функции
int inputInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.good()) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
        else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка ввода. Пожалуйста, введите целое число." << endl;
        }
    }
    return value;
}

double inputDouble(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.good()) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
        else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка ввода. Пожалуйста, введите число." << endl;
        }
    }
    return value;
}

// Функции для работы с сотрудниками
void addDeveloper() {
    cout << "\n--- Добавление разработчика ---" << endl;
    auto dev = make_shared<Developer>();
    dev->input();
    allEmployees.push_back(dev);
    cout << "Разработчик успешно добавлен!" << endl;
}

void addManager() {
    cout << "\n--- Добавление менеджера ---" << endl;
    auto man = make_shared<Manager>();
    man->input();
    allEmployees.push_back(man);
    cout << "Менеджер успешно добавлен!" << endl;
}

void editEmployee() {
    if (allEmployees.empty()) {
        cout << "Нет сотрудников для редактирования." << endl;
        return;
    }

    cout << "\n--- Редактирование сотрудника ---" << endl;

    // Показать всех сотрудников
    for (size_t i = 0; i < allEmployees.size(); i++) {
        cout << i + 1 << ". ";
        allEmployees[i]->display();
    }

    int empIndex = inputInt("Выберите номер сотрудника для редактирования: ") - 1;
    if (empIndex < 0 || empIndex >= allEmployees.size()) {
        cout << "Неверный выбор." << endl;
        return;
    }

    allEmployees[empIndex]->edit();
    cout << "Сотрудник успешно отредактирован!" << endl;
}

void deleteEmployee() {
    if (allEmployees.empty()) {
        cout << "Нет сотрудников для удаления." << endl;
        return;
    }

    cout << "\n--- Удаление сотрудника ---" << endl;

    // Показать всех сотрудников
    for (size_t i = 0; i < allEmployees.size(); i++) {
        cout << i + 1 << ". ";
        allEmployees[i]->display();
    }

    int empIndex = inputInt("Выберите номер сотрудника для удаления: ") - 1;
    if (empIndex < 0 || empIndex >= allEmployees.size()) {
        cout << "Неверный выбор." << endl;
        return;
    }

    // Удаляем сотрудника из всех команд
    for (auto& team : allTeams) {
        team.removeMember(allEmployees[empIndex]->getId());
    }

    // Удаляем сотрудника из всех проектов
    for (auto& project : allProjects) {
        project.removeTeamMember(allEmployees[empIndex]->getId());
    }

    allEmployees.erase(allEmployees.begin() + empIndex);
    cout << "Сотрудник успешно удален!" << endl;
}

void searchEmployee() {
    if (allEmployees.empty()) {
        cout << "Нет сотрудников для поиска." << endl;
        return;
    }

    cout << "\n--- Поиск сотрудника ---" << endl;
    cout << "1. По имени" << endl;
    cout << "2. По ID" << endl;
    cout << "3. По должности" << endl;

    int choice = inputInt("Выберите критерий поиска: ");

    string searchTerm;
    cout << "Введите значение для поиска: ";
    getline(cin, searchTerm);

    vector<shared_ptr<Employee>> results;

    switch (choice) {
    case 1:
        for (const auto& emp : allEmployees) {
            if (emp->getName().find(searchTerm) != string::npos) {
                results.push_back(emp);
            }
        }
        break;
    case 2:
        for (const auto& emp : allEmployees) {
            if (to_string(emp->getId()).find(searchTerm) != string::npos) {
                results.push_back(emp);
            }
        }
        break;
    case 3:
        for (const auto& emp : allEmployees) {
            if (emp->getPosition().find(searchTerm) != string::npos) {
                results.push_back(emp);
            }
        }
        break;
    default:
        cout << "Неверный выбор." << endl;
        return;
    }

    if (results.empty()) {
        cout << "Сотрудники не найдены." << endl;
    }
    else {
        cout << "\n--- Результаты поиска ---" << endl;
        for (const auto& emp : results) {
            emp->display();
        }
    }
}

void sortEmployees() {
    if (allEmployees.empty()) {
        cout << "Нет сотрудников для сортировки." << endl;
        return;
    }

    cout << "\n--- Сортировка сотрудников ---" << endl;
    cout << "1. По имени" << endl;
    cout << "2. По ID" << endl;
    cout << "3. По зарплате" << endl;

    int choice = inputInt("Выберите критерий сортировки: ");

    switch (choice) {
    case 1:
        sort(allEmployees.begin(), allEmployees.end(),
            [](const shared_ptr<Employee>& a, const shared_ptr<Employee>& b) {
                return a->getName() < b->getName();
            });
        break;
    case 2:
        sort(allEmployees.begin(), allEmployees.end(),
            [](const shared_ptr<Employee>& a, const shared_ptr<Employee>& b) {
                return a->getId() < b->getId();
            });
        break;
    case 3:
        sort(allEmployees.begin(), allEmployees.end(),
            [](const shared_ptr<Employee>& a, const shared_ptr<Employee>& b) {
                return a->getSalary() < b->getSalary();
            });
        break;
    default:
        cout << "Неверный выбор." << endl;
        return;
    }

    cout << "Сотрудники успешно отсортированы!" << endl;
}

// Функции для работы с командами
void createTeam() {
    cout << "\n--- Создание команды ---" << endl;
    string teamName;
    cout << "Введите название команды: ";
    getline(cin, teamName);

    allTeams.emplace_back(teamName);
    cout << "Команда '" << teamName << "' успешно создана!" << endl;
}

void editTeam() {
    if (allTeams.empty()) {
        cout << "Нет команд для редактирования." << endl;
        return;
    }

    cout << "\n--- Редактирование команды ---" << endl;

    // Показать все команды
    for (size_t i = 0; i < allTeams.size(); i++) {
        cout << i + 1 << ". " << allTeams[i].getTeamName() << endl;
    }

    int teamIndex = inputInt("Выберите номер команды для редактирования: ") - 1;
    if (teamIndex < 0 || teamIndex >= allTeams.size()) {
        cout << "Неверный выбор." << endl;
        return;
    }

    string newName;
    cout << "Новое название команды: ";
    getline(cin, newName);

    if (!newName.empty()) {
        allTeams[teamIndex].setTeamName(newName);
    }

    cout << "Команда успешно отредактирована!" << endl;
}

void deleteTeam() {
    if (allTeams.empty()) {
        cout << "Нет команд для удаления." << endl;
        return;
    }

    cout << "\n--- Удаление команды ---" << endl;

    // Показать все команды
    for (size_t i = 0; i < allTeams.size(); i++) {
        cout << i + 1 << ". " << allTeams[i].getTeamName() << endl;
    }

    int teamIndex = inputInt("Выберите номер команды для удаления: ") - 1;
    if (teamIndex < 0 || teamIndex >= allTeams.size()) {
        cout << "Неверный выбор." << endl;
        return;
    }

    allTeams.erase(allTeams.begin() + teamIndex);
    cout << "Команда успешно удалена!" << endl;
}

void addEmployeeToTeam() {
    if (allEmployees.empty()) {
        cout << "Нет доступных сотрудников." << endl;
        return;
    }

    if (allTeams.empty()) {
        cout << "Нет доступных команд." << endl;
        return;
    }

    cout << "\n--- Добавление сотрудника в команду ---" << endl;

    // Показать всех сотрудников
    cout << "Список сотрудников:" << endl;
    for (size_t i = 0; i < allEmployees.size(); i++) {
        cout << i + 1 << ". ";
        allEmployees[i]->display();
    }

    // Выбор сотрудника
    int empIndex = inputInt("Выберите номер сотрудника: ") - 1;
    if (empIndex < 0 || empIndex >= allEmployees.size()) {
        cout << "Неверный выбор сотрудника." << endl;
        return;
    }

    // Показать все команды
    cout << "Список команд:" << endl;
    for (size_t i = 0; i < allTeams.size(); i++) {
        cout << i + 1 << ". " << allTeams[i].getTeamName() << endl;
    }

    // Выбор команды
    int teamIndex = inputInt("Выберите номер команды: ") - 1;
    if (teamIndex < 0 || teamIndex >= allTeams.size()) {
        cout << "Неверный выбор команды." << endl;
        return;
    }

    // Добавление сотрудника в команду
    allTeams[teamIndex].addMember(allEmployees[empIndex]);
    cout << "Сотрудник успешно добавлен в команду!" << endl;
}

void removeEmployeeFromTeam() {
    if (allTeams.empty()) {
        cout << "Нет доступных команд." << endl;
        return;
    }

    cout << "\n--- Удаление сотрудника из команды ---" << endl;

    // Показать все команды
    for (size_t i = 0; i < allTeams.size(); i++) {
        cout << i + 1 << ". " << allTeams[i].getTeamName() << endl;
    }

    int teamIndex = inputInt("Выберите номер команды: ") - 1;
    if (teamIndex < 0 || teamIndex >= allTeams.size()) {
        cout << "Неверный выбор команды." << endl;
        return;
    }

    // Показать сотрудников в выбранной команде
    Team& selectedTeam = allTeams[teamIndex];
    if (selectedTeam.isEmpty()) {
        cout << "Команда пуста." << endl;
        return;
    }

    cout << "Сотрудники в команде '" << selectedTeam.getTeamName() << "':" << endl;
    const auto& members = selectedTeam.getAllMembers();
    for (size_t i = 0; i < members.size(); i++) {
        cout << i + 1 << ". ";
        members[i]->display();
    }

    int empIndex = inputInt("Выберите номер сотрудника для удаления: ") - 1;
    if (empIndex < 0 || empIndex >= members.size()) {
        cout << "Неверный выбор сотрудника." << endl;
        return;
    }

    selectedTeam.removeMember(members[empIndex]);
    cout << "Сотрудник успешно удален из команды!" << endl;
}

// Функции для работы с проектами
void createProject() {
    cout << "\n--- Создание проекта ---" << endl;
    string projectName, description;

    cout << "Введите название проекта: ";
    getline(cin, projectName);

    cout << "Введите описание проекта: ";
    getline(cin, description);

    allProjects.emplace_back(projectName, description);
    cout << "Проект '" << projectName << "' успешно создан!" << endl;
}

void editProject() {
    if (allProjects.empty()) {
        cout << "Нет проектов для редактирования." << endl;
        return;
    }

    cout << "\n--- Редактирование проекта ---" << endl;

    // Показать все проекты
    for (size_t i = 0; i < allProjects.size(); i++) {
        cout << i + 1 << ". " << allProjects[i].getProjectName() << endl;
    }

    int projectIndex = inputInt("Выберите номер проекта для редактирования: ") - 1;
    if (projectIndex < 0 || projectIndex >= allProjects.size()) {
        cout << "Неверный выбор." << endl;
        return;
    }

    Project& project = allProjects[projectIndex];

    string newName;
    cout << "Новое название проекта: ";
    getline(cin, newName);
    if (!newName.empty()) project.setProjectName(newName);

    string newDescription;
    cout << "Новое описание проекта: ";
    getline(cin, newDescription);
    if (!newDescription.empty()) project.setDescription(newDescription);

    cout << "Проект успешно отредактирован!" << endl;
}

void deleteProject() {
    if (allProjects.empty()) {
        cout << "Нет проектов для удаления." << endl;
        return;
    }

    cout << "\n--- Удаление проекта ---" << endl;

    // Показать все проекты
    for (size_t i = 0; i < allProjects.size(); i++) {
        cout << i + 1 << ". " << allProjects[i].getProjectName() << endl;
    }

    int projectIndex = inputInt("Выберите номер проекта для удаления: ") - 1;
    if (projectIndex < 0 || projectIndex >= allProjects.size()) {
        cout << "Неверный выбор." << endl;
        return;
    }

    allProjects.erase(allProjects.begin() + projectIndex);
    cout << "Проект успешно удален!" << endl;
}

// Функции для отображения данных
void displayAllEmployees() {
    cout << "\n--- Все сотрудники ---" << endl;
    if (allEmployees.empty()) {
        cout << "Нет сотрудников." << endl;
        return;
    }

    // Используем флаги форматирования для табличного вывода
    cout.setf(ios::left);
    cout.width(20);
    cout << "Имя";
    cout.width(10);
    cout << "ID";
    cout.width(20);
    cout << "Должность";
    cout.width(15);
    cout << "Зарплата";
    cout << endl;

    cout.unsetf(ios::left);
    cout.setf(ios::fixed);
    cout.precision(2);

    for (const auto& emp : allEmployees) {
        cout.setf(ios::left);
        cout.width(20);
        cout << emp->getName();
        cout.width(10);
        cout << emp->getId();
        cout.width(20);
        cout << emp->getPosition();
        cout.width(15);
        cout << emp->getSalary();
        cout << endl;
    }

    cout.unsetf(ios::left);
}

void displayAllTeams() {
    cout << "\n--- Все команды ---" << endl;
    if (allTeams.empty()) {
        cout << "Нет команд." << endl;
        return;
    }

    for (const auto& team : allTeams) {
        team.displayAllMembers();
    }
}

void displayAllProjects() {
    cout << "\n--- Все проекты ---" << endl;
    if (allProjects.empty()) {
        cout << "Нет проектов." << endl;
        return;
    }

    for (const auto& project : allProjects) {
        project.display();
    }
}

// Функции для сохранения и загрузки данных
void saveToFile() {
    ofstream file("hr_data.txt");
    if (!file.is_open()) {
        cout << "Ошибка открытия файла для записи." << endl;
        return;
    }

    // Сохраняем сотрудников
    file << "EMPLOYEES" << endl;
    for (const auto& emp : allEmployees) {
        file << "TYPE:";
        if (dynamic_cast<Developer*>(emp.get())) {
            file << "DEVELOPER" << endl;
        }
        else if (dynamic_cast<Manager*>(emp.get())) {
            file << "MANAGER" << endl;
        }
        else {
            file << "EMPLOYEE" << endl;
        }

        file << "NAME:" << emp->getName() << endl;
        file << "ID:" << emp->getId() << endl;
        file << "POSITION:" << emp->getPosition() << endl;
        file << "SALARY:" << emp->getSalary() << endl;

        if (auto dev = dynamic_pointer_cast<Developer>(emp)) {
            file << "LANGUAGE:" << dev->getProgrammingLanguage() << endl;
            file << "LEVEL:" << dev->getLevel() << endl;
        }
        else if (auto man = dynamic_pointer_cast<Manager>(emp)) {
            file << "COMPLETED_PROJECTS:" << man->getCompletedProjects() << endl;
            file << "METHODOLOGY:" << man->getMethodology() << endl;
        }

        file << "---" << endl;
    }

    // Сохраняем команды
    file << "TEAMS" << endl;
    for (const auto& team : allTeams) {
        file << "NAME:" << team.getTeamName() << endl;
        file << "MEMBERS:" << team.getSize() << endl;
        for (const auto& member : team.getAllMembers()) {
            file << "MEMBER_ID:" << member->getId() << endl;
        }
        file << "---" << endl;
    }

    // Сохраняем проекты
    file << "PROJECTS" << endl;
    for (const auto& project : allProjects) {
        file << "NAME:" << project.getProjectName() << endl;
        file << "DESCRIPTION:" << project.getDescription() << endl;
        file << "TEAM:" << project.getTeam().getTeamName() << endl;
        file << "---" << endl;
    }

    file.close();
    cout << "Данные успешно сохранены в файл 'hr_data.txt'." << endl;
}

void loadFromFile() {
    ifstream file("hr_data.txt");
    if (!file.is_open()) {
        cout << "Файл с данными не найден." << endl;
        return;
    }

    // Очищаем текущие данные
    allEmployees.clear();
    allTeams.clear();
    allProjects.clear();

    string line;
    string section;
    shared_ptr<Employee> currentEmployee;
    Team currentTeam("");
    Project currentProject("", "");

    while (getline(file, line)) {
        if (line == "EMPLOYEES") {
            section = "EMPLOYEES";
            continue;
        }
        else if (line == "TEAMS") {
            section = "TEAMS";
            continue;
        }
        else if (line == "PROJECTS") {
            section = "PROJECTS";
            continue;
        }
        else if (line == "---") {
            if (section == "EMPLOYEES" && currentEmployee) {
                allEmployees.push_back(currentEmployee);
                currentEmployee.reset();
            }
            else if (section == "TEAMS") {
                allTeams.push_back(currentTeam);
                currentTeam = Team("");
            }
            else if (section == "PROJECTS") {
                allProjects.push_back(currentProject);
                currentProject = Project("", "");
            }
            continue;
        }

        size_t colonPos = line.find(':');
        if (colonPos == string::npos) continue;

        string key = line.substr(0, colonPos);
        string value = line.substr(colonPos + 1);

        if (section == "EMPLOYEES") {
            if (key == "TYPE") {
                if (value == "DEVELOPER") {
                    currentEmployee = make_shared<Developer>();
                }
                else if (value == "MANAGER") {
                    currentEmployee = make_shared<Manager>();
                }
                else {
                    currentEmployee = make_shared<Employee>();
                }
            }
            else if (currentEmployee) {
                if (key == "NAME") currentEmployee->setName(value);
                else if (key == "ID") currentEmployee->setId(stoi(value));
                else if (key == "POSITION") currentEmployee->setPosition(value);
                else if (key == "SALARY") currentEmployee->setSalary(stod(value));
                else if (key == "LANGUAGE") {
                    if (auto dev = dynamic_pointer_cast<Developer>(currentEmployee)) {
                        dev->setProgrammingLanguage(value);
                    }
                }
                else if (key == "LEVEL") {
                    if (auto dev = dynamic_pointer_cast<Developer>(currentEmployee)) {
                        dev->setLevel(value);
                    }
                }
                else if (key == "COMPLETED_PROJECTS") {
                    if (auto man = dynamic_pointer_cast<Manager>(currentEmployee)) {
                        man->setCompletedProjects(stoi(value));
                    }
                }
                else if (key == "METHODOLOGY") {
                    if (auto man = dynamic_pointer_cast<Manager>(currentEmployee)) {
                        man->setMethodology(value);
                    }
                }
            }
        }
        else if (section == "TEAMS") {
            if (key == "NAME") currentTeam.setTeamName(value);
            else if (key == "MEMBERS") {
                // Количество членов - пропускаем, так как будем добавлять по ID
            }
            else if (key == "MEMBER_ID") {
                int id = stoi(value);
                // Найдем сотрудника по ID и добавим в команду
                for (const auto& emp : allEmployees) {
                    if (emp->getId() == id) {
                        currentTeam.addMember(emp);
                        break;
                    }
                }
            }
        }
        else if (section == "PROJECTS") {
            if (key == "NAME") currentProject.setProjectName(value);
            else if (key == "DESCRIPTION") currentProject.setDescription(value);
            else if (key == "TEAM") {
                // Найдем команду по имени и установим для проекта
                for (const auto& team : allTeams) {
                    if (team.getTeamName() == value) {
                        currentProject.getTeam() = team;
                        break;
                    }
                }
            }
        }
    }

    file.close();
    cout << "Данные успешно загружены из файла 'hr_data.txt'." << endl;
}

// Функция для вывода таблицы в файл
void exportToFile() {
    ofstream file("hr_export.txt");
    if (!file.is_open()) {
        cout << "Ошибка открытия файла для экспорта." << endl;
        return;
    }

    // Используем флаги форматирования для табличного вывода в файл
    file.setf(ios::left);
    file.width(20);
    file << "Имя";
    file.width(10);
    file << "ID";
    file.width(20);
    file << "Должность";
    file.width(15);
    file << "Зарплата";
    file << endl;

    file.unsetf(ios::left);
    file.setf(ios::fixed);
    file.precision(2);

    for (const auto& emp : allEmployees) {
        file.setf(ios::left);
        file.width(20);
        file << emp->getName();
        file.width(10);
        file << emp->getId();
        file.width(20);
        file << emp->getPosition();
        file.width(15);
        file << emp->getSalary();
        file << endl;
    }

    file.unsetf(ios::left);
    file.close();
    cout << "Данные успешно экспортированы в файл 'hr_export.txt'." << endl;
}

// Главное меню
void displayMainMenu() {
    cout << "\n=== HR-Менеджмент - Главное меню ===" << endl;
    cout << "1. Управление сотрудниками" << endl;
    cout << "2. Управление командами" << endl;
    cout << "3. Управление проектами" << endl;
    cout << "4. Показать всех сотрудников" << endl;
    cout << "5. Показать все команды" << endl;
    cout << "6. Показать все проекты" << endl;
    cout << "7. Сохранить данные в файл" << endl;
    cout << "8. Загрузить данные из файла" << endl;
    cout << "9. Экспорт данных в файл" << endl;
    cout << "0. Выход" << endl;
    cout << "Выберите опцию: ";
}

void displayEmployeeMenu() {
    cout << "\n=== Управление сотрудниками ===" << endl;
    cout << "1. Добавить разработчика" << endl;
    cout << "2. Добавить менеджера" << endl;
    cout << "3. Редактировать сотрудника" << endl;
    cout << "4. Удалить сотрудника" << endl;
    cout << "5. Поиск сотрудника" << endl;
    cout << "6. Сортировка сотрудников" << endl;
    cout << "0. Назад" << endl;
    cout << "Выберите опцию: ";
}

void displayTeamMenu() {
    cout << "\n=== Управление командами ===" << endl;
    cout << "1. Создать команду" << endl;
    cout << "2. Редактировать команду" << endl;
    cout << "3. Удалить команду" << endl;
    cout << "4. Добавить сотрудника в команду" << endl;
    cout << "5. Удалить сотрудника из команды" << endl;
    cout << "0. Назад" << endl;
    cout << "Выберите опцию: ";
}

void displayProjectMenu() {
    cout << "\n=== Управление проектами ===" << endl;
    cout << "1. Создать проект" << endl;
    cout << "2. Редактировать проект" << endl;
    cout << "3. Удалить проект" << endl;
    cout << "0. Назад" << endl;
    cout << "Выберите опцию: ";
}

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "=== Система HR-Менеджмента ===" << endl;
    cout << "Для управления IT-проектами" << endl;

    int choice;
    do {
        displayMainMenu();
        choice = inputInt("");

        switch (choice) {
        case 1: {
            int empChoice;
            do {
                displayEmployeeMenu();
                empChoice = inputInt("");

                switch (empChoice) {
                case 1:
                    addDeveloper();
                    break;
                case 2:
                    addManager();
                    break;
                case 3:
                    editEmployee();
                    break;
                case 4:
                    deleteEmployee();
                    break;
                case 5:
                    searchEmployee();
                    break;
                case 6:
                    sortEmployees();
                    break;
                case 0:
                    break;
                default:
                    cout << "Неверный выбор. Попробуйте снова." << endl;
                }
            } while (empChoice != 0);
            break;
        }
        case 2: {
            int teamChoice;
            do {
                displayTeamMenu();
                teamChoice = inputInt("");

                switch (teamChoice) {
                case 1:
                    createTeam();
                    break;
                case 2:
                    editTeam();
                    break;
                case 3:
                    deleteTeam();
                    break;
                case 4:
                    addEmployeeToTeam();
                    break;
                case 5:
                    removeEmployeeFromTeam();
                    break;
                case 0:
                    break;
                default:
                    cout << "Неверный выбор. Попробуйте снова." << endl;
                }
            } while (teamChoice != 0);
            break;
        }
        case 3: {
            int projectChoice;
            do {
                displayProjectMenu();
                projectChoice = inputInt("");

                switch (projectChoice) {
                case 1:
                    createProject();
                    break;
                case 2:
                    editProject();
                    break;
                case 3:
                    deleteProject();
                    break;
                case 0:
                    break;
                default:
                    cout << "Неверный выбор. Попробуйте снова." << endl;
                }
            } while (projectChoice != 0);
            break;
        }
        case 4:
            displayAllEmployees();
            break;
        case 5:
            displayAllTeams();
            break;
        case 6:
            displayAllProjects();
            break;
        case 7:
            saveToFile();
            break;
        case 8:
            loadFromFile();
            break;
        case 9:
            exportToFile();
            break;
        case 0:
            cout << "Выход из программы." << endl;
            break;
        default:
            cout << "Неверный выбор. Попробуйте снова." << endl;
        }
    } while (choice != 0);

    return 0;
}