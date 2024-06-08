/** 
 * @file main.c 
 * @brief Entry point, user interface logic.
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "carlist.h"
#include "clientlist.h"
#include "rent.h"
#include "rentlist.h"

/**
 * @brief Adds a new car to the car list.
 * 
 * @param car_list Pointer to the head of the car list.
 */
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
}
/**
 * @brief Prints information about a client.
 * 
 * @param client Pointer to the client whose information is to be printed.
 */
void print_client(Client *client) {
    printf("#%u, %s %s, email: %s, phone: %s\n", client->id, client->first_name, client->last_name, client->email, client->phone_number);
}

/**
 * @brief Prints information about a car.
 * 
 * @param car Pointer to the car whose information is to be printed.
 */
void print_car(Car *car) {
    printf("#%u Car: %s %s - year: %u, kilometers: %u\n",car->id, car->make, car->model, car->year, car->km_driven);
}

/**
 * @brief Prints information about a rent.
 * 
 * @param rent Pointer to the rent whose information is to be printed.
 */
void print_rent(Rent *rent) {
    printf("#%u Rent: car: #%u, client: #%u, start: %s, end: %s%s\n",rent->id, rent->car_id, rent->client_id, rent->date_start, rent->date_end, rent->finished ? ", finished" : "");
}


/**
 * @brief Adds a new rent entry to the rent list.
 * 
 * @param rent_list Pointer to the head of the rent list.
 */
void addRent(RentNode **rent_list, CarNode *car_list, ClientNode *client_list) {
    unsigned car_id = 0;
    unsigned client_id = 0;
    char start_date[80];
    char end_date[80];

    do {
        printf("Cars: \n");
        foreach_car(car_list, print_car);
        printf("\nEnter Car Id: \n");
        scanf("%u", &car_id);
    } while(car_id == 0);

    do {
        printf("Clients: \n");
        foreach_client(client_list, print_client);
        printf("\nEnter Client Id: \n");
        scanf("%u", &client_id);
    } while(car_id == 0);

    do {
        printf("Enter starting date:\n");
        scanf("%s", start_date);
    } while(strlen(start_date) < 8);

    do {
        printf("Enter end date:\n");
        scanf("%s", end_date);
    } while(strlen(end_date) < 8);

    if (add_rent(rent_list, make_rent_data(0, car_id, client_id, start_date, end_date, false)) == NULL) {
        printf("An error ocurred.");
    }
}

/**
 * @brief Removes a car from the car list based on its ID.
 * 
 * @param head Pointer to the head of the car list.
 */
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

/**
 * @brief Removes a client from the client list based on its ID.
 * 
 * @param head Pointer to the head of the client list.
 */
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

/**
 * @brief Removes a rent entry from the rent list based on its ID.
 * 
 * @param head Pointer to the head of the rent list.
 */
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

/**
 * @brief Adds a new client to the client list.
 * 
 * @param client_list Pointer to the head of the client list.
 */
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
}


/**
 * @brief Prints detailed information about a rent, including associated car and client details.
 * 
 * @param rent Pointer to the rent whose information is to be printed.
 * @param car_head Pointer to the head of the car list.
 * @param client_head Pointer to the head of the client list.
 */
void print_rent_details(Rent *rent, CarNode *car_head, ClientNode *client_head) {
    Car *car = fetch_car(rent, car_head);
    Client *client = fetch_client(rent, client_head);
    printf("#%u Rent details: car: #%u, client: #%u, start: %s, end: %s%s\n",rent->id, rent->car_id, rent->client_id, rent->date_start, rent->date_end, rent->finished ? ", finished" : "");
    if (car) {
        printf("Car info:\n");
        print_car(car);
    }
    if (client) {
        printf("Client info:\n");
        print_client(client);
    }
}
/**
 * @brief Finishes rent.
 * 
 * @param head Pointer to the head of the rent list.
 * @param car_head Pointer to the head of the car list.
 */
void finishRent(RentNode *head, CarNode *car_head)
{
    unsigned rentId;
    unsigned kmDriven;
    printf("ID of Rent to finish:\n");
    scanf("%u", &rentId);
    RentNode *found = get_rent_by_id(head, rentId);
    if(!found) {
        printf("Can't find this rent ID\n");
        return;
    }
    if (found->data->finished) { 
      printf("Rent already finished.\n");
      return;
    }
    printf("Enter km driven by client:\n");
    scanf("%u", &kmDriven);

    unsigned cost = rent_finish(found->data, car_head, kmDriven);
    printf("Final Cost: %u\n", cost);
}
/**
 * @brief Displays details of a specific rent entry.
 * 
 * @param head Pointer to the head of the rent list.
 * @param car_head Pointer to the head of the car list.
 * @param client_head Pointer to the head of the client list.
 */
void rentDetails(RentNode *head, CarNode *car_head, ClientNode *client_head) {
    unsigned rentId; 
    printf("ID of Rent to detail:\n");
    scanf("%u", &rentId);
    RentNode *found = get_rent_by_id(head, rentId);
    if(!found) {
        printf("Can't find this rent ID\n");
        return;
    }
    print_rent_details(found->data, car_head, client_head) ;
}

/**
 * @brief Searches for clients in the client list based on a provided search term.
 * 
 * @param head Pointer to the head of the client list.
 */
void searchClient(ClientNode *head) {
    char searchTerm[255];
    printf("Provide a search term (max 255 chars):\n");
    scanf("%254s", searchTerm);
    ClientNode *filtered = client_filtered_list(head, searchTerm, client_search_filter);
    if(filtered == NULL) {
        printf("No results.\n");
        return;
    }
    foreach_client(filtered, print_client);
}

/**
 * @brief Sorts the car list based on user-selected criteria.
 * 
 * @param cars Pointer to the head of the car list.
 */
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

/**
 * @brief Displays the list of clients and related operations menu.
 * 
 * @param client_list Pointer to the head of the client list.
 */
void displayClientsMenu(ClientNode **client_list) {
    int choice;
    do {
        printf("1.Add\n2.Remove\n3.List\n4.Search\n0.Back\nEnter your choice:\n");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                addClient(client_list);
                break;
            case 2:
                removeClient(client_list);
                break;
            case 3:
                foreach_client(*client_list, print_client);
                break;
            case 4:
                searchClient(*client_list);
                break;
            case 0: 
                return;
                break;
            default: printf("Invalid choice. Please try again.\n");
        }
    } while(choice != 0);
}

void searchCar(CarNode *head) {
    char searchTerm[255];
    printf("Provide a search term (max 255 chars):\n");
    scanf("%254s", searchTerm);
    CarNode *filtered = car_filtered_list(head, searchTerm, car_search_filter);
    if(filtered == NULL) {
        printf("No results.\n");
        return;
    }
    foreach_car(filtered, print_car);
}

/**
 * @brief Displays the list of cars and related operations menu.
 * 
 * @param car_list Pointer to the head of the car list.
 */
void displayCarsMenu(CarNode **car_list) {
    int choice;
    do {
        printf("1.Add\n2.Remove\n3.List\n4.Sort\n5.Search\n0.Back\nEnter your choice:\n");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                addCar(car_list);
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
            case 5:
                searchCar(*car_list);
            case 0: 
                return;
                break;
            default: printf("Invalid choice. Please try again.\n");
        }
    } while(choice != 0);
}

/**
 * @brief Displays the list of rents and related operations menu.
 * 
 * @param rent_list Pointer to the head of the rent list.
 * @param client_list Pointer to the head of the client list.
 * @param car_list Pointer to the head of the car list.
 */
void displayRentsMenu(RentNode **rent_list, ClientNode *client_list, CarNode *car_list) {
    int choice;
    do {
        printf("1.Register\n2.Remove\n3.List\n4.Details\n5.Finish rent\n0.Back\nEnter your choice:\n");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                addRent(rent_list, car_list, client_list);
                break;
            case 2:
                removeRent(rent_list);
                break;
            case 3:
                foreach_rent(*rent_list, print_rent);
                break;
            case 4:
                rentDetails(*rent_list, car_list, client_list);
                break;
            case 5:
                finishRent(*rent_list, car_list);
            case 0: 
                return;
                break;
            default: printf("Invalid choice. Please try again.\n");
        }
    } while(choice != 0);
}

/**
 * @brief Saves all data (clients, cars, and rents) to respective CSV files.
 * 
 * @param client_list Pointer to the head of the client list.
 * @param car_list Pointer to the head of the car list.
 * @param rent_list Pointer to the head of the rent list.
 */
void save_all(ClientNode *client_list, CarNode *car_list, RentNode *rent_list) {
    car_list_save_to_file(car_list, "cars.csv");
    client_list_save_to_file(client_list, "clients.csv");
    rent_list_save_to_file(rent_list, "rents.csv");
}

/**
 * @brief Main function, entry point of the program.
 * 
 * @return 0 upon successful execution.
 */
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

