#pragma once
using namespace std;

void printEmploye(Employee emp) { // принтит
	cout << "----------\n";
	cout << "Full name: '" << emp.fullName << "'\n";
	cout << "Job function: " << emp.position << endl;
	cout << "Phone number: " << emp.phoneNumber << endl;
	cout << "E-Mail: " << emp.email << endl;
}





void changeNameEmp(Employee& emp) { // для changeEMPL
    const int SIZE = 50;
    char newName[SIZE];
    cout << "Current name: '" << emp.fullName << "'\n";
    cout << "Enter new name: ";
    cin.getline(newName, SIZE);
    for (int i = 0; i < SIZE; i++) {
        emp.fullName[i] = newName[i];
        if (newName[i] == '\0') {
            emp.fullName[i] = '\0';
            break;
        }
    }
}


void changeJobEmp(Employee& emp) { //changeEMPL
    const int SIZE = 50;
    char newJob[SIZE];
    cout << "Current job function: " << emp.position << endl;
    cout << "Enter new job function: ";
    cin.getline(newJob, SIZE);
    for (int i = 0; i < SIZE; i++) {
        emp.position[i] = newJob[i];
        if (newJob[i] == '\0') {
            emp.position[i] = '\0';
            break;
        }
    }
}

void changePhone(Employee& emp) { // chage empl
    const int SIZE = 50;
    char newPhone[SIZE];
    cout << "Current phone number: " << emp.phoneNumber << endl;
    cout << "Enter new phone number";
    cin.getline(newPhone, SIZE);
    for (int i = 0; i < SIZE; i++) {
        emp.phoneNumber[i] = newPhone[i];
        if (newPhone[i] == '\0') {
            emp.phoneNumber[i] = '\0';
            break;
        }
    }
}

void changeMailEmp(Employee& emp) { // change empl
    const int SIZE = 50;
    char newMail[SIZE];
    cout << "Current mail: " << emp.email << endl;
    cout << "Enter new mail: ";
    cin.getline(newMail, SIZE);
    for (int i = 0; i < SIZE; i++) {
        emp.email[i] = newMail[i];
        if (newMail[i] == '\0') {
            emp.email[i] = '\0';
            break;
        }
    }
}

void changeEmployee(Employee& emp) {
    int choice;
    
    changeEmpMenu();
    cin >> choice;
    cin.ignore();

    switch (choice)
    {case 1:
        changeNameEmp(emp);
        break;
    case 2:
        changeJobEmp(emp);
        break;
    case 3:
        changePhone(emp);
        break;
    case 4:
        changeMailEmp(emp);
        break;
    case 0:
        cout << "RETURNING....\n";
        break;
    default:
        break;
    }
}





void inputEmpData(Employee* emp) { // ввод данных эмпл
    cout << "Enter name: ";
    cin.getline(emp->fullName, strlen(emp->fullName) - 1);

    cout << "Enter job function: ";
    cin.getline(emp->position, strlen(emp->position) - 1);

    cout << "Enter phone number: ";
    cin.getline(emp->phoneNumber, strlen(emp->phoneNumber)- 1);

    cout << "Enter E-Mail: ";
    cin.getline(emp->email, strlen(emp->email) - 1);

    
}

void printEmpInFiles(const Employee& emp, FILE* empFile, FILE* empData);





void addEmp(Employee* ptrEmp, int& empCount, FILE* infoFile, FILE* dataFile) {

    cout << "----------------\n";
    cout << "Add new employee\n";
    cout << "----------------\n";
    
    inputEmpData(&ptrEmp[empCount]);
    printEmpInFiles(ptrEmp[empCount], infoFile, dataFile);
    
    empCount++;
}

void showEmploye(Employee* emp, int countEmp) { //вывод из массива всех
    for (int i = 0; i < countEmp; i++) {
        printEmploye(emp[i]);
    }

}

int searchIndex(Employee* ptrEmp, int count, char* name) { // поиск индекса возвр его же
    int index = -1;
    for (int i = 0; i < count; i++) {
        if (strcmp(ptrEmp[i].fullName, name) == 0) {
            index = i;
        }
    }
    if (index >= 0) {
        return index;
    }
    else {
        cout << "We cant find any matches.\n";
    }
}

void delEmployee2(Employee* emp, int& countEmpl, char* name) { // смещает с нужного элемента на i+1 пустой ставит в конец.
    int index = searchIndex(emp, countEmpl, name);

    for (int i = index; i < countEmpl; i++) {
        emp[i] = emp[i + 1];
    }



    Employee emptyEmp = { "","","","" };
    emp[countEmpl - 1] = emptyEmp;
    countEmpl--;

    cout << "-----\n";
    cout << "Employee delete\n";
    cout << "-----\n";
}











//
//void addEmployee(Employee* ptrEmp, int& nEmpl, FILE* infoFile, FILE* dataFile) {
//    cout << "----------------\n";
//    cout << "Add new employee\n";
//    cout << "----------------\n";
//    cout << "Enter name: ";
//    inputEmpData(&ptrEmp[nEmpl]);
//    printEmpInFiles(ptrEmp[nEmpl], infoFile, dataFile);
//    nEmpl++;
//    
//}


void printEmpInFiles(const Employee& emp, FILE* empFile, FILE* empData) {
    fprintf(empFile, "%s\n", emp.fullName);
    fprintf(empData, "%s\n", emp.fullName);
    fprintf(empFile, "%s\n", emp.position);
    fprintf(empData, "%s\n", emp.position);
    fprintf(empFile, "%s\n", emp.phoneNumber);
    fprintf(empData, "%s\n", emp.phoneNumber);
    fprintf(empFile, "%s\n\n", emp.email);
    fprintf(empData, "%s\n", emp.email);


}

void readEmployeeData(FILE* file, Employee *emp, int& numEmpl,const int MAXCOUNT) { 
    const int MAXSIZE = 50;
    char line[MAXSIZE];
    Employee copyEmp;

    while (fgets(line, MAXSIZE, file) != nullptr) {
        line[strcspn(line, "\n")] = '\0';  
        strcpy_s(copyEmp.fullName, line);
        
        if (fgets(line, MAXSIZE, file) == nullptr) {
            cout << "Error reading position" << endl;
            break;
        }
        line[strcspn(line, "\n")] = '\0';
        strcpy_s(copyEmp.position, line);

        if (fgets(line, MAXSIZE, file) == nullptr) {
            cout << "Error reading phone number" << endl;
            break;
        }
        line[strcspn(line, "\n")] = '\0';
        strcpy_s(copyEmp.phoneNumber, line);

        if (fgets(line, MAXSIZE, file) == nullptr) {
            cout << "Error reading email" << endl;
            break;
        }
        line[strcspn(line, "\n")] = '\0';
        strcpy_s(copyEmp.email, line);

        
        if (numEmpl < MAXCOUNT) {
            emp[numEmpl] = copyEmp;
            numEmpl++;
        }
        else {
            cout << "Maximum number of employees reached" << endl;
            break;
        }
    }
    
   
}





//void delEmploye(Employee* emp, int& numEmp,int index) {
//    if (index > 0 && index < numEmp) {
//        for (int i = index; i < numEmp; i++) {
//            emp[i] = emp[i + 1];
//        }
//        numEmp--;
//        cout << "Employee deleted.";
//    }
//    else {
//        cout << "We cant find any matches\n";
//    }
//
//    
//}


//void searchEmpForDel(Employee* emp,int& numEmp) {
//    const char SIZE = 50;
//    char searchedName[SIZE];
//    cout << "Enter name: ";
//    cin.getline(searchedName, SIZE);
//    int index = -1;
//    for (int i = 0; i < numEmp; i++) {
//        if (strcmp(emp[i].fullName, searchedName) == 0) {
//            index = i;
//        }
//    }
//
//    cout << index;
//
//    delEmploye(emp, numEmp, index);
//}



