#pragma once
using namespace std;


void printSalesInFile(const Sale& sale,FILE* saleFile,FILE* saleData) {
	fprintf(saleFile, "%s\n", sale.employee.fullName);
	fprintf(saleData, "%s\n", sale.employee.fullName);

	fprintf(saleFile, "%s\n", sale.car.manufacturer);
	fprintf(saleData, "%s\n", sale.car.manufacturer);

	fprintf(saleFile, "%s\n", sale.car.model);
	fprintf(saleData, "%s\n", sale.car.model);

	fprintf(saleFile, "%d.", sale.saleDate.day);
	fprintf(saleData, "%d\n", sale.saleDate.day);

	fprintf(saleFile, "%d.", sale.saleDate.month);
	fprintf(saleData, "%d\n", sale.saleDate.month);

	fprintf(saleFile, "%d\n", sale.saleDate.year);
	fprintf(saleData, "%d\n", sale.saleDate.year);

	fprintf(saleFile, "%d\n\n", sale.factSalePrice);
	fprintf(saleData, "%d\n", sale.factSalePrice);

}


void inputSaleData(Sale* sale) {
	cout << "Enter employee: ";
	cin.getline(sale->employee.fullName, strlen(sale->employee.fullName) - 1);

	cout << "Enter car brand: ";
	cin.getline(sale->car.manufacturer, strlen(sale->car.manufacturer) - 1);

	cout << "Enter car model: ";
	cin.getline(sale->car.model, strlen(sale->car.model) - 1);

	cout << "Enter sale date: ";
	cin >> sale->saleDate.day >> sale->saleDate.month >> sale->saleDate.year;

	cout << "Enter fact car sale price: ";
	cin >> sale->factSalePrice;
}


void printSale(Sale sale) {
	cout << "----------\n";
	cout << "Employee: " << sale.employee.fullName << endl;
	cout << "Car: " << sale.car.manufacturer << " " << sale.car.model << endl;
	cout << "Sale date: " << sale.saleDate.day << "." << sale.saleDate.month << "." << sale.saleDate.year << endl;
	cout << "Fact sale price: " << sale.factSalePrice << endl;

}


void addSale(Sale* ptrSale, int& saleCount,FILE* saleFile,FILE* saleData) {
	cout << "------\n";
	cout << "Add new sale\n";
	cout << " -------\n";
	inputSaleData(&ptrSale[saleCount]);
	printSalesInFile(ptrSale[saleCount], saleFile, saleData);
	saleCount++;

}


void showSale(Sale* ptrSale, int saleCount) {
	for (int i = 0; i < saleCount; i++) {
		printSale(ptrSale[i]);
	}
}



int searchSaleByIndex(Sale* ptrSale, int count, char* employee, char* brand) {
	int index;
	for (int i = 0; i < count; i++) {
		if (strcmp(ptrSale[i].employee.fullName, employee) == 0 && strcmp(ptrSale[i].car.manufacturer, brand) == 0) {
			index = i;
			break;
		}
	}
	return index;
}

void delSale(Sale* sale, int& countSales, char* employee, char* brand) {
	int index = searchSaleByIndex(sale, countSales, employee, brand);

	for (int i = index; i < countSales; i++) {
		sale[i] = sale[i + 1];
	}

	Sale emptySale = { {""},{"",""},{0,0,0},0 };
	sale[countSales - 1] = emptySale;
	countSales--;

	cout << "-----------\n";
	cout << "Sale delete\n";
	cout << "-----------\n";
}


void changeSaleEmp(Sale& sale) {
	const int SIZE = 50;
	char newEmp[SIZE];
	cout << "Current employee: " << sale.employee.fullName << endl;
	cout << "Enter new employee: ";
	cin.getline(newEmp, SIZE);
	for (int i = 0; i < SIZE; i++) {
		sale.employee.fullName[i] = newEmp[i];
		if (newEmp[i] == '\0') {
			sale.employee.fullName[i] = '\0';
			break;
		}
	}
}

void changeSaleBrand(Sale& sale) {
	const int SIZE = 50;
	char newBrand[SIZE];
	
	cout << "Current brand: " << sale.car.manufacturer << endl;
	cin.getline(newBrand, SIZE);
	for (int i = 0; i < SIZE; i++) {
		sale.car.manufacturer[i] = newBrand[i];
		if (newBrand[i] == '\0') {
			sale.car.manufacturer[i] = '\0';
			break;
		}
	}
}


void changeSaleModel(Sale& sale) {
	const int SIZE = 50;
	char newModel[SIZE];

	cout << "Current model: " << sale.car.model << endl;
	cin.getline(newModel, SIZE);
	for (int i = 0; i < SIZE; i++) {
		sale.car.model[i] = newModel[i];
		if (newModel[i] == '\0') {
			sale.car.model[i] == '\0';
			break;
		}
	}
}


void changeSaleDate(Sale& sale) {
	const int SIZE = 50;
	Date newDate;
	cout << "Current date: " << sale.saleDate.day << "." << sale.saleDate.month << "." << sale.saleDate.year << endl;
	cout << "Enter new date: (01 01 2001) ";
	cin >> newDate.day >> newDate.month >> newDate.year;

	sale.saleDate.day = newDate.day;
	sale.saleDate.month = newDate.month;
	sale.saleDate.year = newDate.year;

}



void changeSalePrice(Sale& sale) {
	int newSalePrice;
	cout << "Current sale price: " << sale.factSalePrice << endl;
	cin >> newSalePrice;
	sale.factSalePrice = newSalePrice;
}


void changeSale(Sale& sale) {
	int choice;
	changeSaleMenu();
	cin >> choice;
	cin.ignore();
	switch (choice)
	{
	case 1:
		changeSaleEmp(sale);
		break;
	case 2:
		changeSaleBrand(sale);
		break;
	case 3:
		changeSaleModel(sale);
		break;
	case 4:
		changeSaleDate(sale);
		break;
	case 5:
		changeSalePrice(sale);
		break;
	case 0:
		cout << "Returning.\n";
		break;
	default:
		break;
	}

}


bool isDateRight(const Date* date) {
	const int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	if (date->year <= 0 || date->year > 2100 || date->month <= 0 || date->month > 12 || date->day <= 0) {
		return false;
	}
	int fullMonth = days[date->month - 1];
	return (date->day <= fullMonth);
}


bool isDateInRange(const Date& date, const Date& startDate, const Date& endDate) {
	if (date.year > startDate.year || (date.year == startDate.year && date.month > startDate.month) ||
		(date.year == startDate.year && date.month == startDate.month && date.day >= startDate.day)) {
		if (date.year < endDate.year || (date.year == endDate.year && date.month < endDate.month) ||
			(date.year == endDate.year && date.month == endDate.month && date.day <= endDate.day)) {
			return true;
		}
	}
	return false;
}



void showSaleByDate(Sale* sale, int countSales, const Date date) {
	if (!isDateRight(&date)) {
		cout << "You enter wrong date\n";
		return;
	}
	else {
		for (int i = 0; i < countSales; i++) {
			if ((sale[i].saleDate.day == date.day) && (sale[i].saleDate.month == date.month) && (sale[i].saleDate.year == date.year)) {
				printSale(sale[i]);
			}
		}
	}
}








void showSaleByPeriod(Sale* sale, int countSale, const Date startDate, const Date endDate) {
	int counter = 0;
	if (!isDateRight(&startDate) || !isDateRight(&endDate)) {
		cout << "You enter wrong date!\n";
		return;
	}
	else {
		for (int i = 0; i < countSale; i++) {
			if (isDateInRange(sale[i].saleDate, startDate, endDate)) {
				printSale(sale[i]);
				counter++;
			}
		}
		if (counter == 0) {
			cout << "We can`t find any sales by period\n";
		}

	}
}



int showIncomeByPeriod(Sale* sale, int countSale, const Date startDate, const Date endDate) {
	int totalSum =0 ;

	if(!isDateRight(&startDate) || !isDateRight(&endDate)) {
		cout << "You enter wrong date!\n";
		return 0;
	}
	else {
		for (int i = 0; i < countSale; i++) {
			totalSum += sale[i].factSalePrice;
		}
	}

	return totalSum;
}




void showSaleByEmployee(Sale* sale, int countSale, char* name) {

	int counter = 0;
	for (int i = 0; i < countSale; i++) {
		if (strcmp(sale[i].employee.fullName, name) == 0) {
			printSale(sale[i]);
			counter++;
		}
		
	}

	if (counter == 0) {
		cout << "We can`t find any matches!\n";
	}

}







void showMostSaledCar(Sale* sale, Car* car, int countCar, int countSale) {
	int index = 0;
	int maxSales = 0;
	for (int i = 0; i < countCar; i++) {
		int curCarSales = 0;
		for (int j = 0; j < countSale; j++) {
			if (strcmp(car[i].manufacturer, sale[j].car.manufacturer) == 0) {
				curCarSales++;
			}
		}

		if (curCarSales > maxSales) {
			int temp = maxSales;
			maxSales = curCarSales;
			index = i;
			
		}
	}

	if (index >= 0) {
		cout << "Most saled car: \n" << car[index].manufacturer  << endl;
		cout << "Count of sales: \n" << maxSales+1 << endl;

	}
	
}



void readSaleData(FILE* file, Sale* sale, int& countSale, const int MAXCOUNT) {
	const int MAXSIZE = 50;
	char line[MAXSIZE];
	Sale copySale;

	while (fgets(line, MAXSIZE, file) != nullptr) {
		line[strcspn(line, "\n")] = '\0';
		strcpy_s(copySale.employee.fullName,line);

		if (fgets(line, MAXSIZE, file) == nullptr) {
			cout << "Error read employee name\n";
			break;
		}
		
		line[strcspn(line,"\n")] = '\0';
		strcpy_s(copySale.car.manufacturer, line);

		if (fgets(line, MAXSIZE, file) == nullptr) {
			cout << "Error reading car brand\n";
			break;
		}

		line[strcspn(line, "\n")] = '\0';
		strcpy_s(copySale.car.model, line);

		if (fgets(line, MAXSIZE, file) == nullptr) {
			cout << "Error reading car model\n";
			break;
		}

		

		line[strcspn(line, ".")] = '\0';
		copySale.saleDate.day = atoi(line);

		if (fgets(line, MAXSIZE, file) == nullptr) {
			cout << "Error reading day\n";
			break;
		}

		
		line[strcspn(line, ".")] = '\0';
		copySale.saleDate.month = atoi(line);
		if (fgets(line, MAXSIZE, file) == nullptr) {
			cout << "Error reading month\n";
			break;
		}


		line[strcspn(line, ".")] = '\0';
		copySale.saleDate.year = atoi(line);

		if (fgets(line, MAXSIZE, file) == nullptr) {
			cout << "Error reading year\n";
			break;
		}

		line[strcspn(line, "\n")] = '\0';
		copySale.factSalePrice = atoi(line);

		if (countSale < MAXCOUNT) {
			sale[countSale] = copySale;
			countSale++;
		}

	}
}