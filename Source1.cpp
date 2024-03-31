#include <iostream>
#include <cstdio>
#include "struct.h"
#include "menu.h"
#include "employeeFunct.h"
#include "carFunct.h"
#include "saleFunct.h"
using namespace std;


/*Створіть додаток для обліку продажу автомобілів в автосалоні. Основне завдання - враховувати процес продажу автомобілів, фіксувати співробітника, який провів операцію, підрахувати прибуток.

Додаток має зберігати таку інформацію:

Співробітник:

П.І.Б.
Посада.
Контактний телефон.
Email.


Автомобіль:

Назва виробника.
Рік випуску.
Модель.
Собівартість.
Потенційна ціна продажу.


Продажі:

Співробітник.
Автомобіль.
Дата продажу.
Реальна ціна продажу.


Необхідно зберігати таку функціональність:

Додавання та видалення інформації про співробітників. +
Додавання та видалення інформації про автомобілі.+
Додавання та видалення інформації про продаж.+

Звіти. Дані можуть виводитися на екран або файл, залежно від вибору користувача:
Повна інформація про співробітників фірми.+
Повна інформація про автомобілі.+
Повна інформація про продаж.+

Усі продажі за певну дату.+
Усі продажі за певний період часу.+
Усі продажі певного співробітника.+

Назва автомобіля, що найбільше продається за вказаний період часу.+
Інформація про найуспішнішого продавця за вказаний період часу.+
Сумарний прибуток за вказаний період часу.+

Збереження даних у файл.
Завантаження даних з файлу.*/


int main() {

	const int MAXCOUNT = 100;
	const int SIZE = 50; // макс длина ввода

	Employee* emp = new Employee[MAXCOUNT];
	Car* car = new Car[MAXCOUNT];
	Sale* sale = new Sale[MAXCOUNT];

	int indexEmp; //индексы для функций change
	int indexCar;
	int indexSale;


	int emplCount = 0;// кол-во сотруд
	int carsCount = 0;
	int saleCount = 0;

	int totalIncome = 0;//прибыль за период

	
	

	////Файлы чистовые
	FILE* empFile = nullptr;
	const char EMPFILE[] = "Employee_info.txt";
	errno_t errEmpFile;

	FILE* carFile = nullptr;
	const char CARFILE[] = "Car_info.txt";
	errno_t errCarFile;

	FILE* saleFile = nullptr;
	const char SALEFILE[] = "Sale_info.txt";
	errno_t errSaleFile;
	
	////


	FILE* empData = nullptr;
	const char EMPDATA[] = "EMPData.txt";
	errno_t errEmpData;

	FILE* carData = nullptr;
	const char CARDATA[] = "CARData.txt";
	errno_t errCarData;

	FILE* saleData = nullptr;
	const char SALEDATA[] = "SALEData.txt";
	errno_t errSaleData;
	
	


	errno_t errEmpRead;// для чтения
	errno_t errCarRead;//
	errno_t errSaleRead;//

	errEmpRead = fopen_s(&empData, EMPDATA, "r"); // Файл должен быть создан
	if (errEmpRead == 0) {
		readEmployeeData(empData, emp, emplCount, MAXCOUNT);
	}
	fclose(empData);
	
	errCarRead = fopen_s(&carData, CARDATA, "r");
	if (errCarRead == 0) {
		readCarData(carData,car,carsCount,MAXCOUNT);
	}
	fclose(carData);
	

	errSaleRead = fopen_s(&saleData, SALEDATA, "r");
	if (errSaleRead == 0) {
		readSaleData(saleData, sale, saleCount, MAXCOUNT);
	}
	fclose(saleData);


	
	
	int mainCh;
	do {
		
		mainMenu();
		cin >> mainCh;
		cin.ignore();
		switch (mainCh)
		{
		case 1:
			int empChoice;
			emplMenu();
			cin >> empChoice;
			cin.ignore();
			switch (empChoice)
			{
			case 1:
				
				
				errEmpFile = fopen_s(&empFile, EMPFILE, "a");
				errEmpData = fopen_s(&empData, EMPDATA, "a");

				if (errEmpFile == 0 && errEmpData == 0) {
					addEmp(emp, emplCount,empFile,empData);
					
				}

				else {
					cout << errEmpFile << endl;
					cout << errEmpData << endl;
					cout << "Something went wrong\n";
				}

				if (errEmpFile == 0) {
					fclose(empFile);
				}
				if (errEmpData == 0) {
					fclose(empData);
				}
				
				
				break;
			case 2:
				
				
				
				

				for (int i = 0; i < emplCount; i++) {
					printEmploye(emp[i]);
				}
				break;
				
				

			
			case 3:
				char name[SIZE];
				cout << "Enter searched name: ";
				cin.getline(name, SIZE - 1);

				delEmployee2(emp, emplCount, name);

				errEmpFile = fopen_s(&empFile, EMPFILE, "w");
				errEmpData = fopen_s(&empData, EMPDATA, "w");
				if (errEmpFile == 0 && errEmpData == 0) {
					
					for (int i = 0; i < emplCount; ++i) {
						printEmpInFiles(emp[i], empFile, empData);
					}
					
					fclose(empFile);
					fclose(empData);
				}
				else {
					cout << "Error opening files for writing." << endl;
				}

				break;
				
			case 4:
				char nameSearch[SIZE];
				cout << "Enter searched name: ";
				cin.getline(nameSearch, SIZE - 1);

				indexEmp = searchIndex(emp, emplCount, nameSearch);
				changeEmployee(emp[indexEmp]);


				errEmpFile = fopen_s(&empFile, EMPFILE, "w");
				errEmpData = fopen_s(&empData, EMPDATA, "w");

				if (errEmpFile == 0 && errEmpData == 0) {

					for (int i = 0; i < emplCount; i++) {
						printEmpInFiles(emp[i], empFile, empData);
					}

					fclose(empFile);
					fclose(empData);
				}
				else {
					cout << "Error opening files for writing" << endl;
				}
				

				

				break;
			case 0:
				cout << "Returning.\n";
				break;
			default:
				break;
			}
			break;
		case 2:
			int carChoice;
			do {
				carMenu();
				cin >> carChoice;
				cin.ignore();

				switch (carChoice)
				{
				case 1:
					errCarFile = fopen_s(&carFile, CARFILE, "a");
					errCarData = fopen_s(&carData, CARDATA, "a");

					if (errCarFile == 0 && errCarData == 0) {
						addCar(car, carsCount,carFile,carData);
					}

					else {
						cout << "Something went wrong!\n";
						cout << "Err Car File: " << errCarFile << endl;
						cout << "Err Car Data: " << errCarData << endl;
					}

					if (errCarFile == 0) {
						fclose(carFile);
					}
					if (errCarData == 0) {
						fclose(carData);
					}
					
					break;
				case 2:
					for (int i = 0; i < carsCount; i++) {
						printCar(car[i]);
					}
					
					break;

				case 3:
					char brand[SIZE];
					char model[SIZE];
					cout << "Enter searched brand: ";
					cin.getline(brand, SIZE);
					cout << "Enter searched model: ";
					cin.getline(model, SIZE);
					delCar(car, carsCount, brand, model);

					errCarFile = fopen_s(&carFile, CARFILE, "w");
					errCarData = fopen_s(&carData, CARDATA, "w");

					if (errCarFile == 0 && errCarData == 0) {
						for (int i = 0; i < carsCount; i++) {
							printCarInFile(car[i], carFile, carData);
						}
						fclose(carFile);
						fclose(carData);
					}
					else {
						cout << "Error opening files for writing.";
						
					}


					break;
				case 4:
					char brandChange[SIZE];
					char modelChange[SIZE];
					cout << "Enter searched brand: ";
					cin.getline(brandChange, SIZE);
					cout << "Enter searched model: ";
					cin.getline(modelChange, SIZE);

					indexCar = searchCarIndex(car, carsCount, brandChange, modelChange);
					changeCar(car[indexCar]);
					break;

					errCarFile = fopen_s(&carFile, CARFILE, "W");
					errCarData = fopen_s(&carFile, CARFILE, "w");

					if (errCarFile == 0 && errCarData == 0) {
						for (int i = 0; i < saleCount; i++) {
							printSalesInFile(sale[i], saleFile, carData);
						}
						fclose(carFile);
						fclose(carData);
					}


				default:
					break;
				}

			} while (carChoice != 0);
			break;
		case 3:
			int saleChoice;
			do {
				saleMenu();
				cin >> saleChoice;
				cin.ignore();
				switch (saleChoice)
				{
				case 1:
					errSaleFile = fopen_s(&saleFile, SALEFILE, "a");
					errSaleData = fopen_s(&saleData, SALEDATA, "a");
					if (errSaleFile == 0 && errSaleData == 0) {

						addSale(sale, saleCount, saleFile, saleData);
					}
					if (errSaleFile == 0) {
						fclose(saleFile);
					}
					if (errSaleData == 0) {
						fclose(saleData);
					}

					break;
				case 2:
					for (int i = 0; i < saleCount; i++) {
						printSale(sale[i]);
					}

					
					break;
				case 3:

					char searchedBrand[SIZE];
					char searchedEmp[SIZE];

					cout << "Enter searched car brand: ";
					cin.getline(searchedBrand, SIZE);

					cout << "Enter searched employee: ";
					cin.getline(searchedEmp, SIZE);

					delSale(sale,saleCount,searchedEmp,searchedBrand);



					errSaleFile = fopen_s(&saleFile, SALEFILE, "w");
					errSaleData = fopen_s(&saleData, SALEDATA, "w");

					if (errSaleFile == 0 && errSaleData == 0) {
						for (int i = 0; i < saleCount; i++) {
							printSalesInFile(sale[i], saleFile, saleData);
						}
						fclose(saleFile);
						fclose(saleData);
					}
					else {
						cout << "Error opening files for writing.";
						
					}

					break;
				case 4:
					char sBrand[SIZE];
					char sEmp[SIZE];

					cout << "Enter searched name: ";
					cin.getline(sBrand, SIZE);
					cout << "Enter searched brand: ";
					cin.getline(sEmp, SIZE);

					indexSale = searchSaleByIndex(sale, saleCount, sEmp, sBrand);
					changeSale(sale[indexSale]);

					errSaleFile = fopen_s(&saleFile, SALEFILE, "w");
					errSaleData = fopen_s(&saleData, SALEDATA, "w");
					if (errSaleFile == 0 && errSaleData == 0) {
						for (int i = 0; i < saleCount; i++) {
							printSalesInFile(sale[i], saleFile, saleData);

						}
						fclose(saleFile);
						fclose(saleData);
					}
					else {
						cout << "Error opening files for writing" << endl;
					}


					break;
				case 0:
					cout << "Returnin...\n";

					break;
				default:
					break;
				}
				
				

			}while (saleChoice != 0);
			break;
		case 4:
			int statChoice;
			do {
				statMenu();
				cin >> statChoice;
				cin.ignore();

				switch (statChoice)
				{
				case 1:
					Date searchSaleDate;
					cout << "Enter searched sale date (dd mm yyyy):";
					cin >> searchSaleDate.day >> searchSaleDate.month >> searchSaleDate.year;
					showSaleByDate(sale,saleCount,searchSaleDate);
					break;
				case 2:
					Date startDate;
					Date endDate;
					cout << "Enter start date (dd mm yyyy): ";
					cin >> startDate.day >> startDate.month >> startDate.year;
					cout << "Enter end date (dd mm yyyy): ";
					cin >> endDate.day >> endDate.month >> endDate.year;
					showSaleByPeriod(sale, saleCount, startDate, endDate);

					break;
				case 3:
					char searchedEmpl[SIZE];
					cout << "Enter employee name for search: ";
					cin.getline(searchedEmpl, SIZE);
					showSaleByEmployee(sale, emplCount, searchedEmpl);
					break;

				case 4:
					Date incomeStartDate;
					Date incomeEndDate;

					cout << "Enter start date (dd mm yyyy): ";
					cin >> incomeStartDate.day >> incomeStartDate.month >> incomeStartDate.year;
					cout << "Enter end date (dd mm yyyy): ";

					cin >> incomeEndDate.day >> incomeEndDate.month >> incomeEndDate.year;
					totalIncome = showIncomeByPeriod(sale, saleCount, incomeStartDate, incomeEndDate);
					cout << "Income by period: " << incomeStartDate.day << "." << incomeStartDate.month << "." << incomeEndDate.year << "-" << incomeEndDate.day <<"."<< incomeEndDate.month << "." << incomeEndDate.year << endl;
					cout << "= " << totalIncome;
					break;
				case 5:
					showMostSaledCar(sale, car, carsCount, saleCount);
					break;
				default:
					break;
				}

			} while (statChoice != 0);
			break;
		case 0:
			
			cout << "Bye!\n";
			break;
		default:
			break;
		}
		
	} while (mainCh != 0);

	delete[] emp;
	delete[] sale;
	delete[] car;
	return 0;
}


