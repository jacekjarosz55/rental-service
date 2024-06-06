/** @file rentlist.h
 *  @brief RentNode structure definiton and rent list related functions.
 */
#ifndef RENTLIST_H
#define RENTLIST_H

#include <stdbool.h>
#include "rent.h"

/**
 * @struct RentNode
 * @brief Represents a node in a linked list of rents.
 */
struct RentNode {
  struct RentNode *next; /**< Pointer to the next node. */
  struct Rent *data;     /**< Pointer to the rent data. */
};

typedef struct RentNode RentNode;

/**
 * @brief Adds a new rent to the list.
 * 
 * @param list Pointer to the head of the list.
 * @param data Pointer to the rent data to be added.
 * @return Pointer to the added RentNode, or NULL if failed.
 */
RentNode *add_rent(RentNode **list, Rent *data);

/**
 * @brief Updates a rent in the list by its ID.
 * 
 * @param head Pointer to the head of the list.
 * @param id Identifier of the rent to be updated.
 * @param new_data Pointer to the new rent data.
 * @return True if the rent was updated, false otherwise.
 */
bool update_rent(RentNode *head, unsigned id, Rent *new_data);

/**
 * @brief Retrieves a rent from the list by its ID.
 * 
 * @param head Pointer to the head of the list.
 * @param id Identifier of the rent to be retrieved.
 * @return Pointer to the RentNode containing the rent, or NULL if not found.
 */
RentNode *get_rent_by_id(RentNode *head, unsigned id);

/**
 * @brief Removes a rent from the list by its ID.
 * 
 * @param head Pointer to the head of the list.
 * @param id Identifier of the rent to be removed.
 * @return True if the rent was removed, false otherwise.
 */
bool remove_rent_by_id(RentNode **head, unsigned id);

/**
 * @brief Finds a rent in the list by car and client IDs.
 * 
 * @param head Pointer to the head of the list.
 * @param car_id Identifier of the car.
 * @param client_id Identifier of the client.
 * @return Pointer to the RentNode containing the rent, or NULL if not found.
 */
RentNode *find_rent(RentNode *head, unsigned car_id, unsigned client_id);

/**
 * @brief Applies a function to each rent in the list.
 * 
 * @param head Pointer to the head of the list.
 * @param func Function to be applied to each rent.
 */
void foreach_rent(RentNode *head, void(*func)(Rent*));

/**
 * @brief Frees the memory allocated for a RentNode.
 * 
 * @param rent Pointer to the RentNode to be freed.
 */
void free_rent(RentNode *rent);

/**
 * @brief Frees the memory allocated for the entire rent list.
 * 
 * @param head Pointer to the head of the list.
 */
void free_rent_list(RentNode *head);

/**
 * @brief Saves the rent list to a file.
 * 
 * @param head Pointer to the head of the list.
 * @param filename Name of the file.
 * @return True if the list was saved successfully, false otherwise.
 */
bool rent_list_save_to_file(RentNode *head, char *filename);

/**
 * @brief Loads a rent list from a file.
 * 
 * @param filename Name of the file.
 * @return Pointer to the head of the newly loaded list.
 */
RentNode* rent_list_new_from_file(char *filename);

#endif // RENTLIST_H

