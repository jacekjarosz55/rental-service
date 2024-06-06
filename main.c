#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "carlist.h"
#include "clientlist.h"
#include "rentlist.h"
#include "util.h"
#include <time.h>




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
    
    Car *newCar = make_car_data(0, make, model, year, cost, km_driven);
    add_car(car_list, newCar);
    if(newCar != NULL) {
        printf("\n Car added successfully\n");
    } else {
        printf("\nSomething went wrong... :(\n");
    }
    sleep(2);
}

void removeCar(CarNode **head) {
    unsigned removeId;
    printf("ID of Car to remove:\n");
    scanf("%u", &removeId);
    if (remove_car_by_id(head, removeId)) {
      printf("Removed successfully.\n");
    } else {
      printf("Could not remove.\n");
    }
}

void removeClient(ClientNode **head) {
    unsigned removeId;
    printf("ID of Client to remove:\n");
    scanf("%u", &removeId);
    if (remove_client_by_id(head, removeId)) {
      printf("Removed successfully.\n");
    } else {
      printf("Could not remove.\n");
    }
}

void removeRent(RentNode **head) {
    unsigned removeId;
    printf("ID of Rent to remove:\n");
    scanf("%u", &removeId);
    if (remove_rent_by_id(head, removeId)) {
      printf("Removed successfully.\n");
    } else {
      printf("Could not remove.\n");
    }
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

    Client *newClient = make_client_data(0, first_name, last_name, email, phone_number);
    add_client(client_list, newClient);

    if (newClient != NULL) {
        printf("Client added successfully.\n");
    } else {
        printf("Something went wrong while adding the client.\n");
    }

    sleep(2);
    system("cls");
}
void rentCar() {
    printf("Renting a car...\n");
}

void searchClient(ClientNode *head) {
  char searchTerm[255];
  printf("Provide a search term (max 255 chars):\n");
  fgets(searchTerm, sizeof(searchTerm), stdin);
  client_filtered_list(head, searchTerm, client_search_filter);
}

void sortCars(CarNode **cars) {
    int choice;
    printf("Sort cars by:\n");
    printf("1. Year\n");
    printf("2. Make\n");
    printf("Enter your choice: \n");
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



void print_client(Client *client) {
}
void displayClients(ClientNode *client_list) {
  foreach_client(client_list, print_client);
}
void displayCarsMenu(CarNode **car_list) {
  int choice;
  do {
    printf("1.Add\n2.Remove\n3.List\n4.Sort\n0.Back\nEnter your choice:\n");
    scanf("%d", &choice);
    switch(choice) {
      case 1:
        break;
      case 2:
        removeCar(car_list);
        break;
      case 3:
        foreach_car(*car_list, print_car);
        break;
      case 4:
        sortCars(car_list);
        break;
      case 0: 
        return;
        break;
      default: printf("Invalid choice. Please try again.\n");
    }
  } while(choice != 0);
}

void displayClientsMenu(ClientNode **client_list) {
  int choice;
  do {
    printf("1.Add\n2.Remove\n3.List\n4.Search\n0.Back\nEnter your choice:\n");
    scanf("%d", &choice);
    switch(choice) {
      case 1:
        break;
      case 2:
        break;
      case 3:
        break;
      case 0: 
        return;
        break;
      default: printf("Invalid choice. Please try again.\n");
    }
  } while(choice != 0);
}


void displayRentsMenu(RentNode **rent_list, ClientNode *client_list, CarNode *car_list) {
  int choice;
  do {
    printf("1.Register\n2.Remove\n3.List\n0.Back\nEnter your choice:\n");
    scanf("%d", &choice);
    switch(choice) {
      case 1:
        break;
      case 2:
        break;
      case 3:
        break;
      case 0: 
        return;
        break;
      default: printf("Invalid choice. Please try again.\n");
    }
  } while(choice != 0);
}

void save_all(ClientNode *client_list, CarNode *car_list, RentNode *rent_list) {
    car_list_save_to_file(car_list, "cars.csv");
    client_list_save_to_file(client_list, "clients.csv");
    rent_list_save_to_file(rent_list, "rents.csv");
}


int main() {
    CarNode *car_list = car_list_new_from_file("cars.csv");
    ClientNode *client_list = client_list_new_from_file("clients.csv");
    RentNode *rent_list = rent_list_new_from_file("rents.csv");
    int choice;
    do {
        printf("1.Clients\n2.Cars\n3.Rents\n0.Save and Exit\nEnter your choice:\n");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
              displayClientsMenu(&client_list);
              break;
            case 2:
              displayCarsMenu(&car_list);
              break;
            case 3:
              displayRentsMenu(&rent_list, client_list, car_list);
              break;
            case 0: 
                printf("Exiting...\n");
                save_all(client_list, car_list, rent_list);
                break;
            default: printf("Invalid choice. Please try again.\n");
        }
    } while(choice != 0);
    return 0;
}
