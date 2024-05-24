#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "carlist.h"
#include "clientlist.h"
#include "rentlist.h"
#include "util.h"

// Function prototypes
void displayMenu();
void addCar();
void removeCar();
void addClient();
void removeClient();
void rentCar();
void searchClient();
void sortCars();

int main() {
    int choice;
    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addCar(); break;
            case 2: removeCar(); break;
            case 3: addClient(); break;
            case 4: removeClient(); break;
            case 5: rentCar(); break;
            case 6: searchClient(); break;
            case 7: sortCars(); break;
            case 0: printf("Exiting...\n"); break;
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
    printf("0. Exit\n");
}

void addCar() {
    // Implementation to add a car
    printf("Adding a car...\n");
    // Your code to interact with carlist.c
}

void removeCar() {
    // Implementation to remove a car
    printf("Removing a car...\n");
    // Your code to interact with carlist.c
}

void addClient() {
    // Implementation to add a client
    printf("Adding a client...\n");
    // Your code to interact with clientlist.c
}

void removeClient() {
    // Implementation to remove a client
    printf("Removing a client...\n");
    // Your code to interact with clientlist.c
}

void rentCar() {
    // Implementation to rent a car
    printf("Renting a car...\n");
    // Your code to interact with rentlist.c
}

void searchClient() {
    // Implementation to search for a client
    printf("Searching for a client...\n");
    // Your code to interact with clientlist.c
}

void sortCars() {
    int choice;
    printf("Sort cars by:\n");
    printf("1. Year\n");
    printf("2. Make\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Sorting cars by year...\n");
        // Your code to sort cars by year using carlist.c
    } else if (choice == 2) {
        printf("Sorting cars by make...\n");
        // Your code to sort cars by make using carlist.c
    } else {
        printf("Invalid choice.\n");
    }
}

