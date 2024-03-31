#pragma once

void inputCarData(Car* car) {
	cout << "Enter brand: ";
	cin.getline(car->manufacturer, strlen(car->manufacturer) - 1);

	cout << "Enter model: ";
	cin.getline(car->model, strlen(car->model) - 1);
	
	cout << "Enter year: ";
	cin.getline(car->year, strlen(car->year) - 1);

	cout << "Enter cost price: ";
	cin >> car->costPrice;

	cout << "Enter potential price: ";
	cin >> car->potSalePrice;
}

void printCar(Car car) {
	cout << "-----\n";
	cout << "Brand name: " << car.manufacturer << endl;
	cout << "Model: " << car.model << endl;
	cout << "Year: " << car.year << endl;
	cout << "Cost price: " << car.costPrice << endl;
	cout << "Potential sale price: " << car.potSalePrice << endl;
}


void printCarInFile(const Car& car, FILE* carFile, FILE* carData) {
	fprintf(carFile, "%s\n", car.manufacturer);
	fprintf(carData, "%s\n", car.manufacturer);

	fprintf(carFile, "%s\n", car.model);
	fprintf(carData, "%s\n", car.model);

	fprintf(carFile, "%s\n", car.year);
	fprintf(carData, "%s\n", car.year);

	fprintf(carFile, "%d\n", car.costPrice);
	fprintf(carData, "%d\n", car.costPrice);

	fprintf(carFile, "%d\n\n", car.potSalePrice);
	fprintf(carData, "%d\n", car.potSalePrice);
}


void addCar(Car* ptrCar, int& carCount,FILE* carFile,FILE* carData) {
	cout << "---------\n";
	cout << "Add new car\n";
	cout << "----------\n";

	inputCarData(&ptrCar[carCount]);
	printCarInFile(ptrCar[carCount], carFile, carData);
	carCount++;
}


void showCar(Car* ptrCar, int carCount) {
	for (int i = 0; i < carCount; i++) {
		printCar(ptrCar[i]);
	}
}



int searchCarIndex(Car* ptrCar, int count, char* brand, char* model) {
	int index;
	for (int i = 0; i < count; i++) {
		if (strcmp(ptrCar[i].manufacturer, brand) == 0 && strcmp(ptrCar[i].model, model) == 0) {
			index = i;
			break;
		}
	}
	return index;
}


void delCar(Car* car, int& countCar,char* brand, char* model) {
	int index = searchCarIndex(car, countCar, brand, model);

	for (int i = index; i < countCar; i++) {
		car[i] = car[i + 1];
	}

	Car emptyCar = { "","","",0,0 };
	car[countCar - 1] = emptyCar;
	countCar--;

	cout << "--------\n";
	cout << "Car deleted!\n";
	cout << "---------\n";
}

void changeCarBrand(Car& car) {
	const int SIZE = 50;
	char newBrand[SIZE];
	cout << "Current brand: " << car.manufacturer << endl;
	cout << "Enter new brand: ";
	cin.getline(newBrand,SIZE);
	for (int i = 0; i < SIZE; i++) {
		car.manufacturer[i] = newBrand[i];
		if (newBrand[i] == '\0') {
			break;
		}
	}
}


void changeCarModel(Car& car) {
	const int SIZE = 50;
	char newModel[SIZE];
	cout << "Current model: " << car.model << endl;
	cout << "Enter new model: ";
	cin.getline(newModel, SIZE);
	for (int i = 0; i < SIZE; i++) {
		car.model[i] = newModel[i];
		if (newModel[i] == '\0') {
			break;

		}
	}
}


void cahngeCarYear(Car& car) {
	const int SIZE = 50;
	char newYear[SIZE];
	cout << "Current year: " << car.year << endl;
	cout << "Enter new year: ";
	cin.getline(newYear, SIZE);
	for (int i = 0; i < SIZE; i++) {
		car.year[i] = newYear[i];
		if (newYear[i] == '\0') {
			break;
		}
	}
}


void changeCarCostPrice(Car& car) {
	int newPrice;
	cout << "Current price: " << car.costPrice << endl;
	cout << "Enter new cost price: ";
	cin >> newPrice;
	car.costPrice = newPrice;
	
}

void changeCarSalePrice(Car& car) {
	int newSalePrice;
	cout << "Current sale price: " <<car.potSalePrice <<endl;

	cout << "Enter new sale price: ";
	cin >> newSalePrice;

	car.potSalePrice = newSalePrice;
}

void changeCar(Car& car) {
	int choice;
	changeCarMenu();
	cin >> choice;
	cin.ignore();

	switch (choice)
	{
	case 1:
		changeCarBrand(car);
		break;
	case 2:
		changeCarModel(car);
		break;
	case 3:
		cahngeCarYear(car);
		break;
	case 4:
		changeCarCostPrice(car);
		break;
	case 5:
		changeCarSalePrice(car);
		break;
	case 0:
		cout << "Bye!\n";
		break;
	default:
		break;
	}
}

void readCarData(FILE* file, Car* car, int& countCar, const int MAXCOUNT) {
	const int MAXSIZE = 20;
	char line[MAXSIZE];
	Car copyCar;

	while (fgets(line, MAXSIZE, file) != nullptr) {
		line[strcspn(line, "\n")] = '\0';
		strcpy_s(copyCar.manufacturer, line);

		if (fgets(line, MAXSIZE, file) == nullptr) {
			cout << "Error reading brand name" << endl;
			break;
		}



		line[strcspn(line, "\n")] = '\0';
		strcpy_s(copyCar.model, line);

		if (fgets(line, MAXSIZE, file) == nullptr) {
			cout << "Error reading model" << endl;
			break;
		}




		line[strcspn(line, "\n")] = '\0';
		strcpy_s(copyCar.year, line);

		if (fgets(line, MAXSIZE, file) == nullptr) {
			cout << "Error reading year" << endl;
			break;

		}




		line[strcspn(line, "\n")] = '\0';
		
		copyCar.costPrice = atoi(line);

		
		if (fgets(line, MAXSIZE, file) == nullptr) {
			cout << "Error cost price" << endl;
			break;
		}

	
		line[strcspn(line, "\n")] = '\0';
		copyCar.potSalePrice = atoi(line); // по кодам аскии преобразует в число 

		if (countCar < MAXCOUNT) {
			car[countCar] = copyCar;
			countCar++;
		}

		
	}
}