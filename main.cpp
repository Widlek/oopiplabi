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

// ������� ����� Employee
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
                cout << "������ �����. ����������, ���������� �����.\n";
            }
        }
    }

public:
    Employee() : id(0), salary(0.0) {}
    virtual ~Employee() = default;

    virtual void display() const {
        cout << "���: " << name
            << ", ID: " << id
            << ", ���������: " << position
            << ", ��������: " << salary << endl;
    }

    virtual void input() {
        cout << "������� ��� ����������: ";
        getline(cin, name);

        safeInput(id, "������� ID ����������: ");

        cout << "������� ��������� ����������: ";
        getline(cin, position);

        safeInput(salary, "������� �������� ����������: ");
    }

    virtual void edit() {
        cout << "�������������� ���������� (�������� ������, ����� �� ��������):\n";

        string newName;
        cout << "����� ���: ";
        getline(cin, newName);
        if (!newName.empty()) name = newName;

        string newId;
        cout << "����� ID: ";
        getline(cin, newId);
        if (!newId.empty()) id = stoi(newId);

        string newPosition;
        cout << "����� ���������: ";
        getline(cin, newPosition);
        if (!newPosition.empty()) position = newPosition;

        string newSalary;
        cout << "����� ��������: ";
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

// ����� Developer
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

        cout << "������� �������� ���� ����������������: ";
        getline(cin, programmingLanguage);

        int levelChoice;
        cout << "�������� ������� ������������:\n";
        cout << "1 - Junior\n";
        cout << "2 - Middle\n";
        cout << "3 - Senior\n";
        cout << "��� �����: ";

        while (true) {
            cin >> levelChoice;
            if (cin.good() && levelChoice >= 1 && levelChoice <= 3) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            else {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "�������� �����. ����������, ������� ����� �� 1 �� 3: ";
            }
        }

        switch (levelChoice) {
        case 1: level = "Junior"; break;
        case 2: level = "Middle"; break;
        case 3: level = "Senior"; break;
        }
    }

    void display() const override {
        cout << "�����������: " << name
            << " (ID: " << id
            << ", �������: " << level
            << ", ����: " << programmingLanguage
            << ", ��������: " << salary << ")" << endl;
    }

    void edit() override {
        Employee::edit();

        string newLang;
        cout << "����� ���� ����������������: ";
        getline(cin, newLang);
        if (!newLang.empty()) programmingLanguage = newLang;

        string newLevel;
        cout << "����� ������� (Junior/Middle/Senior): ";
        getline(cin, newLevel);
        if (!newLevel.empty()) level = newLevel;
    }

    string getProgrammingLanguage() const { return programmingLanguage; }
    string getLevel() const { return level; }

    void setProgrammingLanguage(const string& lang) { programmingLanguage = lang; }
    void setLevel(const string& lvl) { level = lvl; }
};

// ����� Manager
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

        safeInput(completedProjects, "������� ���������� ������� ����������� ��������: ");

        int methodologyChoice;
        cout << "�������� ������������ ����������:\n";
        cout << "1 - Agile\n";
        cout << "2 - Waterfall\n";
        cout << "3 - Scrum\n";
        cout << "4 - Kanban\n";
        cout << "5 - ������\n";
        cout << "��� �����: ";

        while (true) {
            cin >> methodologyChoice;
            if (cin.good() && methodologyChoice >= 1 && methodologyChoice <= 5) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            else {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "�������� �����. ����������, ������� ����� �� 1 �� 5: ";
            }
        }

        switch (methodologyChoice) {
        case 1: methodology = "Agile"; break;
        case 2: methodology = "Waterfall"; break;
        case 3: methodology = "Scrum"; break;
        case 4: methodology = "Kanban"; break;
        case 5:
            cout << "������� �������� ����� ������������: ";
            getline(cin, methodology);
            break;
        }
    }

    void display() const override {
        cout << "�������� ��������: " << name
            << " (ID: " << id
            << ", ����������� �������: " << completedProjects
            << ", ������������: " << methodology
            << ", ��������: " << salary << ")" << endl;
    }

    void edit() override {
        Employee::edit();

        string newProjects;
        cout << "����� ���������� ����������� ��������: ";
        getline(cin, newProjects);
        if (!newProjects.empty()) completedProjects = stoi(newProjects);

        string newMethodology;
        cout << "����� ������������: ";
        getline(cin, newMethodology);
        if (!newMethodology.empty()) methodology = newMethodology;
    }

    int getCompletedProjects() const { return completedProjects; }
    string getMethodology() const { return methodology; }

    void setCompletedProjects(int projects) { completedProjects = projects; }
    void setMethodology(const string& method) { methodology = method; }
};

// ����� Team
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
        cout << "\n--- ������ ������� '" << teamName << "' ---\n";
        if (members.empty()) {
            cout << "������� �����.\n";
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

// ����� Project
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
        cout << "\n=== ���������� � ������� ===\n";
        cout << "��������: " << projectName << "\n";
        cout << "��������: " << description << "\n";

        cout << "���� ������: "
            << put_time(&startDate, "%d.%m.%Y") << "\n";
        cout << "���� ���������: "
            << put_time(&endDate, "%d.%m.%Y") << "\n";

        cout << "������ �������:\n";
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

// ���������� ����������
vector<shared_ptr<Employee>> allEmployees;
vector<Team> allTeams;
vector<Project> allProjects;

// ��������������� �������
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
            cout << "������ �����. ����������, ������� ����� �����." << endl;
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
            cout << "������ �����. ����������, ������� �����." << endl;
        }
    }
    return value;
}

// ������� ��� ������ � ������������
void addDeveloper() {
    cout << "\n--- ���������� ������������ ---" << endl;
    auto dev = make_shared<Developer>();
    dev->input();
    allEmployees.push_back(dev);
    cout << "����������� ������� ��������!" << endl;
}

void addManager() {
    cout << "\n--- ���������� ��������� ---" << endl;
    auto man = make_shared<Manager>();
    man->input();
    allEmployees.push_back(man);
    cout << "�������� ������� ��������!" << endl;
}

void editEmployee() {
    if (allEmployees.empty()) {
        cout << "��� ����������� ��� ��������������." << endl;
        return;
    }

    cout << "\n--- �������������� ���������� ---" << endl;

    // �������� ���� �����������
    for (size_t i = 0; i < allEmployees.size(); i++) {
        cout << i + 1 << ". ";
        allEmployees[i]->display();
    }

    int empIndex = inputInt("�������� ����� ���������� ��� ��������������: ") - 1;
    if (empIndex < 0 || empIndex >= allEmployees.size()) {
        cout << "�������� �����." << endl;
        return;
    }

    allEmployees[empIndex]->edit();
    cout << "��������� ������� ��������������!" << endl;
}

void deleteEmployee() {
    if (allEmployees.empty()) {
        cout << "��� ����������� ��� ��������." << endl;
        return;
    }

    cout << "\n--- �������� ���������� ---" << endl;

    // �������� ���� �����������
    for (size_t i = 0; i < allEmployees.size(); i++) {
        cout << i + 1 << ". ";
        allEmployees[i]->display();
    }

    int empIndex = inputInt("�������� ����� ���������� ��� ��������: ") - 1;
    if (empIndex < 0 || empIndex >= allEmployees.size()) {
        cout << "�������� �����." << endl;
        return;
    }

    // ������� ���������� �� ���� ������
    for (auto& team : allTeams) {
        team.removeMember(allEmployees[empIndex]->getId());
    }

    // ������� ���������� �� ���� ��������
    for (auto& project : allProjects) {
        project.removeTeamMember(allEmployees[empIndex]->getId());
    }

    allEmployees.erase(allEmployees.begin() + empIndex);
    cout << "��������� ������� ������!" << endl;
}

void searchEmployee() {
    if (allEmployees.empty()) {
        cout << "��� ����������� ��� ������." << endl;
        return;
    }

    cout << "\n--- ����� ���������� ---" << endl;
    cout << "1. �� �����" << endl;
    cout << "2. �� ID" << endl;
    cout << "3. �� ���������" << endl;

    int choice = inputInt("�������� �������� ������: ");

    string searchTerm;
    cout << "������� �������� ��� ������: ";
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
        cout << "�������� �����." << endl;
        return;
    }

    if (results.empty()) {
        cout << "���������� �� �������." << endl;
    }
    else {
        cout << "\n--- ���������� ������ ---" << endl;
        for (const auto& emp : results) {
            emp->display();
        }
    }
}

void sortEmployees() {
    if (allEmployees.empty()) {
        cout << "��� ����������� ��� ����������." << endl;
        return;
    }

    cout << "\n--- ���������� ����������� ---" << endl;
    cout << "1. �� �����" << endl;
    cout << "2. �� ID" << endl;
    cout << "3. �� ��������" << endl;

    int choice = inputInt("�������� �������� ����������: ");

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
        cout << "�������� �����." << endl;
        return;
    }

    cout << "���������� ������� �������������!" << endl;
}

// ������� ��� ������ � ���������
void createTeam() {
    cout << "\n--- �������� ������� ---" << endl;
    string teamName;
    cout << "������� �������� �������: ";
    getline(cin, teamName);

    allTeams.emplace_back(teamName);
    cout << "������� '" << teamName << "' ������� �������!" << endl;
}

void editTeam() {
    if (allTeams.empty()) {
        cout << "��� ������ ��� ��������������." << endl;
        return;
    }

    cout << "\n--- �������������� ������� ---" << endl;

    // �������� ��� �������
    for (size_t i = 0; i < allTeams.size(); i++) {
        cout << i + 1 << ". " << allTeams[i].getTeamName() << endl;
    }

    int teamIndex = inputInt("�������� ����� ������� ��� ��������������: ") - 1;
    if (teamIndex < 0 || teamIndex >= allTeams.size()) {
        cout << "�������� �����." << endl;
        return;
    }

    string newName;
    cout << "����� �������� �������: ";
    getline(cin, newName);

    if (!newName.empty()) {
        allTeams[teamIndex].setTeamName(newName);
    }

    cout << "������� ������� ���������������!" << endl;
}

void deleteTeam() {
    if (allTeams.empty()) {
        cout << "��� ������ ��� ��������." << endl;
        return;
    }

    cout << "\n--- �������� ������� ---" << endl;

    // �������� ��� �������
    for (size_t i = 0; i < allTeams.size(); i++) {
        cout << i + 1 << ". " << allTeams[i].getTeamName() << endl;
    }

    int teamIndex = inputInt("�������� ����� ������� ��� ��������: ") - 1;
    if (teamIndex < 0 || teamIndex >= allTeams.size()) {
        cout << "�������� �����." << endl;
        return;
    }

    allTeams.erase(allTeams.begin() + teamIndex);
    cout << "������� ������� �������!" << endl;
}

void addEmployeeToTeam() {
    if (allEmployees.empty()) {
        cout << "��� ��������� �����������." << endl;
        return;
    }

    if (allTeams.empty()) {
        cout << "��� ��������� ������." << endl;
        return;
    }

    cout << "\n--- ���������� ���������� � ������� ---" << endl;

    // �������� ���� �����������
    cout << "������ �����������:" << endl;
    for (size_t i = 0; i < allEmployees.size(); i++) {
        cout << i + 1 << ". ";
        allEmployees[i]->display();
    }

    // ����� ����������
    int empIndex = inputInt("�������� ����� ����������: ") - 1;
    if (empIndex < 0 || empIndex >= allEmployees.size()) {
        cout << "�������� ����� ����������." << endl;
        return;
    }

    // �������� ��� �������
    cout << "������ ������:" << endl;
    for (size_t i = 0; i < allTeams.size(); i++) {
        cout << i + 1 << ". " << allTeams[i].getTeamName() << endl;
    }

    // ����� �������
    int teamIndex = inputInt("�������� ����� �������: ") - 1;
    if (teamIndex < 0 || teamIndex >= allTeams.size()) {
        cout << "�������� ����� �������." << endl;
        return;
    }

    // ���������� ���������� � �������
    allTeams[teamIndex].addMember(allEmployees[empIndex]);
    cout << "��������� ������� �������� � �������!" << endl;
}

void removeEmployeeFromTeam() {
    if (allTeams.empty()) {
        cout << "��� ��������� ������." << endl;
        return;
    }

    cout << "\n--- �������� ���������� �� ������� ---" << endl;

    // �������� ��� �������
    for (size_t i = 0; i < allTeams.size(); i++) {
        cout << i + 1 << ". " << allTeams[i].getTeamName() << endl;
    }

    int teamIndex = inputInt("�������� ����� �������: ") - 1;
    if (teamIndex < 0 || teamIndex >= allTeams.size()) {
        cout << "�������� ����� �������." << endl;
        return;
    }

    // �������� ����������� � ��������� �������
    Team& selectedTeam = allTeams[teamIndex];
    if (selectedTeam.isEmpty()) {
        cout << "������� �����." << endl;
        return;
    }

    cout << "���������� � ������� '" << selectedTeam.getTeamName() << "':" << endl;
    const auto& members = selectedTeam.getAllMembers();
    for (size_t i = 0; i < members.size(); i++) {
        cout << i + 1 << ". ";
        members[i]->display();
    }

    int empIndex = inputInt("�������� ����� ���������� ��� ��������: ") - 1;
    if (empIndex < 0 || empIndex >= members.size()) {
        cout << "�������� ����� ����������." << endl;
        return;
    }

    selectedTeam.removeMember(members[empIndex]);
    cout << "��������� ������� ������ �� �������!" << endl;
}

// ������� ��� ������ � ���������
void createProject() {
    cout << "\n--- �������� ������� ---" << endl;
    string projectName, description;

    cout << "������� �������� �������: ";
    getline(cin, projectName);

    cout << "������� �������� �������: ";
    getline(cin, description);

    allProjects.emplace_back(projectName, description);
    cout << "������ '" << projectName << "' ������� ������!" << endl;
}

void editProject() {
    if (allProjects.empty()) {
        cout << "��� �������� ��� ��������������." << endl;
        return;
    }

    cout << "\n--- �������������� ������� ---" << endl;

    // �������� ��� �������
    for (size_t i = 0; i < allProjects.size(); i++) {
        cout << i + 1 << ". " << allProjects[i].getProjectName() << endl;
    }

    int projectIndex = inputInt("�������� ����� ������� ��� ��������������: ") - 1;
    if (projectIndex < 0 || projectIndex >= allProjects.size()) {
        cout << "�������� �����." << endl;
        return;
    }

    Project& project = allProjects[projectIndex];

    string newName;
    cout << "����� �������� �������: ";
    getline(cin, newName);
    if (!newName.empty()) project.setProjectName(newName);

    string newDescription;
    cout << "����� �������� �������: ";
    getline(cin, newDescription);
    if (!newDescription.empty()) project.setDescription(newDescription);

    cout << "������ ������� ��������������!" << endl;
}

void deleteProject() {
    if (allProjects.empty()) {
        cout << "��� �������� ��� ��������." << endl;
        return;
    }

    cout << "\n--- �������� ������� ---" << endl;

    // �������� ��� �������
    for (size_t i = 0; i < allProjects.size(); i++) {
        cout << i + 1 << ". " << allProjects[i].getProjectName() << endl;
    }

    int projectIndex = inputInt("�������� ����� ������� ��� ��������: ") - 1;
    if (projectIndex < 0 || projectIndex >= allProjects.size()) {
        cout << "�������� �����." << endl;
        return;
    }

    allProjects.erase(allProjects.begin() + projectIndex);
    cout << "������ ������� ������!" << endl;
}

// ������� ��� ����������� ������
void displayAllEmployees() {
    cout << "\n--- ��� ���������� ---" << endl;
    if (allEmployees.empty()) {
        cout << "��� �����������." << endl;
        return;
    }

    // ���������� ����� �������������� ��� ���������� ������
    cout.setf(ios::left);
    cout.width(20);
    cout << "���";
    cout.width(10);
    cout << "ID";
    cout.width(20);
    cout << "���������";
    cout.width(15);
    cout << "��������";
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
    cout << "\n--- ��� ������� ---" << endl;
    if (allTeams.empty()) {
        cout << "��� ������." << endl;
        return;
    }

    for (const auto& team : allTeams) {
        team.displayAllMembers();
    }
}

void displayAllProjects() {
    cout << "\n--- ��� ������� ---" << endl;
    if (allProjects.empty()) {
        cout << "��� ��������." << endl;
        return;
    }

    for (const auto& project : allProjects) {
        project.display();
    }
}

// ������� ��� ���������� � �������� ������
void saveToFile() {
    ofstream file("hr_data.txt");
    if (!file.is_open()) {
        cout << "������ �������� ����� ��� ������." << endl;
        return;
    }

    // ��������� �����������
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

    // ��������� �������
    file << "TEAMS" << endl;
    for (const auto& team : allTeams) {
        file << "NAME:" << team.getTeamName() << endl;
        file << "MEMBERS:" << team.getSize() << endl;
        for (const auto& member : team.getAllMembers()) {
            file << "MEMBER_ID:" << member->getId() << endl;
        }
        file << "---" << endl;
    }

    // ��������� �������
    file << "PROJECTS" << endl;
    for (const auto& project : allProjects) {
        file << "NAME:" << project.getProjectName() << endl;
        file << "DESCRIPTION:" << project.getDescription() << endl;
        file << "TEAM:" << project.getTeam().getTeamName() << endl;
        file << "---" << endl;
    }

    file.close();
    cout << "������ ������� ��������� � ���� 'hr_data.txt'." << endl;
}

void loadFromFile() {
    ifstream file("hr_data.txt");
    if (!file.is_open()) {
        cout << "���� � ������� �� ������." << endl;
        return;
    }

    // ������� ������� ������
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
                // ���������� ������ - ����������, ��� ��� ����� ��������� �� ID
            }
            else if (key == "MEMBER_ID") {
                int id = stoi(value);
                // ������ ���������� �� ID � ������� � �������
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
                // ������ ������� �� ����� � ��������� ��� �������
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
    cout << "������ ������� ��������� �� ����� 'hr_data.txt'." << endl;
}

// ������� ��� ������ ������� � ����
void exportToFile() {
    ofstream file("hr_export.txt");
    if (!file.is_open()) {
        cout << "������ �������� ����� ��� ��������." << endl;
        return;
    }

    // ���������� ����� �������������� ��� ���������� ������ � ����
    file.setf(ios::left);
    file.width(20);
    file << "���";
    file.width(10);
    file << "ID";
    file.width(20);
    file << "���������";
    file.width(15);
    file << "��������";
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
    cout << "������ ������� �������������� � ���� 'hr_export.txt'." << endl;
}

// ������� ����
void displayMainMenu() {
    cout << "\n=== HR-���������� - ������� ���� ===" << endl;
    cout << "1. ���������� ������������" << endl;
    cout << "2. ���������� ���������" << endl;
    cout << "3. ���������� ���������" << endl;
    cout << "4. �������� ���� �����������" << endl;
    cout << "5. �������� ��� �������" << endl;
    cout << "6. �������� ��� �������" << endl;
    cout << "7. ��������� ������ � ����" << endl;
    cout << "8. ��������� ������ �� �����" << endl;
    cout << "9. ������� ������ � ����" << endl;
    cout << "0. �����" << endl;
    cout << "�������� �����: ";
}

void displayEmployeeMenu() {
    cout << "\n=== ���������� ������������ ===" << endl;
    cout << "1. �������� ������������" << endl;
    cout << "2. �������� ���������" << endl;
    cout << "3. ������������� ����������" << endl;
    cout << "4. ������� ����������" << endl;
    cout << "5. ����� ����������" << endl;
    cout << "6. ���������� �����������" << endl;
    cout << "0. �����" << endl;
    cout << "�������� �����: ";
}

void displayTeamMenu() {
    cout << "\n=== ���������� ��������� ===" << endl;
    cout << "1. ������� �������" << endl;
    cout << "2. ������������� �������" << endl;
    cout << "3. ������� �������" << endl;
    cout << "4. �������� ���������� � �������" << endl;
    cout << "5. ������� ���������� �� �������" << endl;
    cout << "0. �����" << endl;
    cout << "�������� �����: ";
}

void displayProjectMenu() {
    cout << "\n=== ���������� ��������� ===" << endl;
    cout << "1. ������� ������" << endl;
    cout << "2. ������������� ������" << endl;
    cout << "3. ������� ������" << endl;
    cout << "0. �����" << endl;
    cout << "�������� �����: ";
}

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "=== ������� HR-����������� ===" << endl;
    cout << "��� ���������� IT-���������" << endl;

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
                    cout << "�������� �����. ���������� �����." << endl;
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
                    cout << "�������� �����. ���������� �����." << endl;
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
                    cout << "�������� �����. ���������� �����." << endl;
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
            cout << "����� �� ���������." << endl;
            break;
        default:
            cout << "�������� �����. ���������� �����." << endl;
        }
    } while (choice != 0);

    return 0;
}