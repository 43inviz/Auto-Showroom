#pragma once


    struct Date {
        int day;
        int month;
        int year;
    };

    struct Employee {
        
        char fullName[50];
        char position[50];
        char phoneNumber[20];
        char email[50];
    };

    struct Car {
        
        char manufacturer[20];
        char year[5];
        char model[20];
        int costPrice;
        int potSalePrice;
    };

    struct Sale {
        Employee employee;
        Car car;
        Date saleDate;
        int factSalePrice;
        
    };