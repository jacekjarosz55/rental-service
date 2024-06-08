/** @file carlist.h
 *  @brief CarNode definition and car list related functions.
 */
#ifndef CARLIST_H
#define CARLIST_H

#include "car.h"
#include <stdbool.h>

/**
 * @struct CarNode
 * @brief Represents a node in a linked list of cars.
 */
struct CarNode {
  struct CarNode *next; /**< Pointer to the next node. */
  struct Car *data;     /**< Pointer to the car data. */
};

typedef struct CarNode CarNode;

/**
 * @brief Adds a new car to the list.
 * 
 * @param list Pointer to the head of the list.
 * @param data Pointer to the car data to be added.
 * @return Pointer to the added CarNode, or NULL if failed.
 */
CarNode *add_car(CarNode **list, Car *data);

/**
 * @brief Updates a car in the list by its ID.
 * 
 * @param head Pointer to the head of the list.
 * @param id Identifier of the car to be updated.
 * @param new_data Pointer to the new car data.
 * @return True if the car was updated, false otherwise.
 */
bool update_car(CarNode *head, unsigned id, Car *new_data);

/**
 * @brief Retrieves a car from the list by its ID.
 * 
 * @param head Pointer to the head of the list.
 * @param id Identifier of the car to be retrieved.
 * @return Pointer to the CarNode containing the car, or NULL if not found.
 */
CarNode *get_car_by_id(CarNode *head, unsigned id);

/**
 * @brief Retrieves a car from the list by make and model.
 * 
 * @param head Pointer to the head of the list.
 * @param make Make of the car.
 * @param model Model of the car.
 * @return Pointer to the CarNode containing the car, or NULL if not found.
 */
CarNode *get_car_by_make_model(CarNode *head, char *make, char *model);

/**
 * @brief Removes a car from the list by its ID.
 * 
 * @param head Pointer to the head of the list.
 * @param id Identifier of the car to be removed.
 * @return True if the car was removed, false otherwise.
 */
bool remove_car_by_id(CarNode **head, unsigned id);

/**
 * @brief Sorts the car list using a comparator function.
 * 
 * @param head Pointer to the head of the list.
 * @param comparator Function to compare two cars.
 * @param descending Sort order (true for descending, false for ascending).
 */
void sort_car_list(CarNode **head, bool(*comparator)(Car*, Car*), bool descending);

/**
 * @brief Comparator function for comparing cars by make.
 * 
 * @param a Pointer to the first car.
 * @param b Pointer to the second car.
 * @return True if car 'a' should come before car 'b'.
 */
bool car_make_comparator(Car* a, Car* b);

/**
 * @brief Comparator function for comparing cars by year.
 * 
 * @param a Pointer to the first car.
 * @param b Pointer to the second car.
 * @return True if car 'a' should come before car 'b'.
 */
bool car_year_comparator(Car* a, Car* b);

/**
 * @brief Comparator function for comparing cars by kilometers driven.
 * 
 * @param a Pointer to the first car.
 * @param b Pointer to the second car.
 * @return True if car 'a' should come before car 'b'.
 */
bool car_km_driven_comparator(Car* a, Car* b);

/**
 * @brief Applies a function to each car in the list.
 * 
 * @param head Pointer to the head of the list.
 * @param func Function to be applied to each car.
 */
void foreach_car(CarNode *head, void(*func)(Car*));

/**
 * @brief Saves the car list to a file.
 * 
 * @param head Pointer to the head of the list.
 * @param filename Name of the file.
 * @return True if the list was saved successfully, false otherwise.
 */
bool car_list_save_to_file(CarNode *head, char *filename);

/**
 * @brief Loads a car list from a file.
 * 
 * @param filename Name of the file.
 * @return Pointer to the head of the newly loaded list.
 */
CarNode* car_list_new_from_file(char *filename);

/**
 * @brief Frees the memory allocated for a CarNode.
 * 
 * @param car Pointer to the CarNode to be freed.
 */
void free_car(CarNode *car);

/**
 * @brief Frees the memory allocated for the entire car list.
 * 
 * @param head Pointer to the head of the list.
 */
void free_car_list(CarNode *head);

/**
 * @brief Filters the car list based on a search term and a filter function.
 * 
 * @param head Pointer to the head of the list.
 * @param searchTerm The term to search for.
 * @param filter_func The function used to filter the clients.
 * @return Pointer to the head of the filtered list.
 */
CarNode *car_filtered_list(CarNode *head, char* searchTerm, bool(*filter_func)(Car*, char*));

/**
 * @brief Default filter function for searching cars.
 * 
 * @param car Pointer to the car data.
 * @param searchTerm The term to search for.
 * @return True if the car matches the search term, false otherwise.
 */
bool car_search_filter(Car* car, char *searchTerm);

#endif // CARLIST_H

