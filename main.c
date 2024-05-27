#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "carlist.h"
#include "clientlist.h"
#include "rentlist.h"
#include "util.h"
#include <time.h>

// Function prototypes
void displayMenu();
void addCar(CarNode **car_list);
void removeCar();
void addClient(ClientNode **client_list);
void removeClient();
void rentCar();
void searchClient();
void sortCars();
int generate_id();
void displayCars(CarNode *car_list);
void save_all(ClientNode *client_list, CarNode *car_list);

int main() {
    CarNode *car_list = car_list_new_from_file("cars.csv");
    ClientNode *client_list = client_list_new_from_file("clients.csv");
    int choice;
    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addCar(&car_list); break;
            case 2: removeCar(); break;
            case 3: addClient(&client_list); break;
            case 4: removeClient(); break;
            case 5: rentCar(); break;
            case 6: searchClient(); break;
            case 7: sortCars(); break;
            case 8: displayCars(car_list); break;
            case 0: printf("Exiting...\n"); save_all(client_list, car_list); break;
            default: printf("Invalid choice. Please try again.\n");
        }
    } while(choice != 0);

    return 0;
}

void displayMenu() {
    printf("\nRental Service Menu:\n");
    printf("1. Add Car\n");
    printf("2. Remove Car\n");
    printf("3. Add Client\n");
    printf("4. Remove Client\n");
    printf("5. Rent Car\n");
    printf("6. Search Client\n");
    printf("7. Sort Cars\n");
    printf("8. Display Cars\n");
    printf("0. Save and Exit\n");
}

void addCar(CarNode **car_list) {
    char make[20];
    char model[20];
    unsigned year;
    unsigned cost;
    unsigned km_driven;
    printf("Enter make: \n");
    scanf("%s", make);
    printf("Enter model name: \n");
    scanf("%s", model);
    printf("Enter year of production: \n");
    scanf("%u", &year);
    printf("Enter cost of rent (per kilometer driven): \n");
    scanf("%u", &cost);
    printf("Enter car's mileage [km]\n");
    scanf("%u", &km_driven);
    
    system("cls");
    Car *newCar = make_car_data(generate_id(), make, model, year, cost, km_driven);
    add_car(car_list, newCar);
    if(newCar != NULL) {
        printf("\n Car added successfully\n");
    } else {
        printf("\nSomething went wrong... :(\n");
    }
    sleep(2);
    system("cls");
}

void removeCar() {
    printf("Removing a car...\n");
}

void addClient(ClientNode **client_list) {
    char first_name[20];
    char last_name[20];
    char email[50];
    char phone_number[20];

    printf("Enter first name: ");
    scanf("%s", first_name);
    printf("Enter last name: ");
    scanf("%s", last_name);
    printf("Enter email address: ");
    scanf("%s", email);
    printf("Enter phone number: ");
    scanf("%s", phone_number);

    Client *newClient = make_client_data(generate_id(), first_name, last_name, email, phone_number);
    add_client(client_list, newClient);

    if (newClient != NULL) {
        printf("Client added successfully.\n");
    } else {
        printf("Something went wrong while adding the client.\n");
    }

    sleep(2);
    system("cls");
}

void removeClient() {
    printf("Removing a client...\n");
}

void rentCar() {
    printf("Renting a car...\n");
}

void searchClient() {
    printf("Searching for a client...\n");
}

void sortCars(CarNode **cars) {
    int choice;
    printf("Sort cars by:\n");
    printf("1. Year\n");
    printf("2. Make\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Sorting cars by year...\n");
        sort_car_list(cars, car_year_comparator, true);
    } else if (choice == 2) {
        printf("Sorting cars by make...\n");
        sort_car_list(cars, car_make_comparator, false);
    } else {
        printf("Invalid choice.\n");
    }
}

void print_car(Car *car) {
  printf("#%u Car: %s %s - rok: %u\n",car->id, car->make, car->model, car->year);
}

void displayCars(CarNode *car_list) {
  foreach_car(car_list, print_car);
}

int generate_id() {
    srand(time(NULL));
    return rand() % 1000000000;
}

void save_all(ClientNode *client_list, CarNode *car_list) {
    car_list_save_to_file(car_list, "cars.csv");
    client_list_save_to_file(client_list, "clients.csv");
}
