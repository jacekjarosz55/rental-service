/** @file clientlist.h
 *  @brief ClientNode data structure definitons and related functions 
 */
#ifndef CLIENTLIST_H
#define CLIENTLIST_H

#include <stdbool.h>
#include "client.h"

/**
 * @struct ClientNode
 * @brief Represents a node in a linked list of clients.
 */
struct ClientNode {
  struct ClientNode *next; /**< Pointer to the next node. */
  struct Client *data;     /**< Pointer to the client data. */
};

typedef struct ClientNode ClientNode;

/**
 * @brief Adds a new client to the list.
 * 
 * @param list Pointer to the head of the list.
 * @param data Pointer to the client data to be added.
 * @return Pointer to the added ClientNode, or NULL if failed.
 */
ClientNode *add_client(ClientNode **list, Client *data);

/**
 * @brief Updates a client in the list by its ID.
 * 
 * @param head Pointer to the head of the list.
 * @param id Identifier of the client to be updated.
 * @param new_data Pointer to the new client data.
 * @return True if the client was updated, false otherwise.
 */
bool update_client(ClientNode *head, unsigned id, Client *new_data);

/**
 * @brief Retrieves a client from the list by its ID.
 * 
 * @param head Pointer to the head of the list.
 * @param id Identifier of the client to be retrieved.
 * @return Pointer to the ClientNode containing the client, or NULL if not found.
 */
ClientNode *get_client_by_id(ClientNode *head, unsigned id);

/**
 * @brief Retrieves a client from the list by full name.
 * 
 * @param head Pointer to the head of the list.
 * @param first_name First name of the client.
 * @param last_name Last name of the client.
 * @return Pointer to the ClientNode containing the client, or NULL if not found.
 */
ClientNode *get_client_by_full_name(ClientNode *head, char *first_name, char *last_name);

/**
 * @brief Removes a client from the list by its ID.
 * 
 * @param head Pointer to the head of the list.
 * @param id Identifier of the client to be removed.
 * @return True if the client was removed, false otherwise.
 */
bool remove_client_by_id(ClientNode *head, unsigned id);

/**
 * @brief Applies a function to each client in the list.
 * 
 * @param head Pointer to the head of the list.
 * @param func Function to be applied to each client.
 */
void foreach_client(ClientNode *head, void(*func)(Client*));

/**
 * @brief Frees the memory allocated for a ClientNode.
 * 
 * @param client Pointer to the ClientNode to be freed.
 */
void free_client(ClientNode *client);

/**
 * @brief Frees the memory allocated for the entire client list.
 * 
 * @param head Pointer to the head of the list.
 */
void free_client_list(ClientNode *head);

/**
 * @brief Frees the memory allocated for the client list, but not the client data.
 * 
 * @param head Pointer to the head of the list.
 */
void free_client_list_only(ClientNode *head);

/**
 * @brief Saves the client list to a file.
 * 
 * @param head Pointer to the head of the list.
 * @param filename Name of the file.
 * @return True if the list was saved successfully, false otherwise.
 */
bool client_list_save_to_file(ClientNode *head, char *filename);

/**
 * @brief Loads a client list from a file.
 * 
 * @param filename Name of the file.
 * @return Pointer to the head of the newly loaded list.
 */
ClientNode* client_list_new_from_file(char *filename);

/**
 * @brief Filters the client list based on a search term and a filter function.
 * 
 * @param head Pointer to the head of the list.
 * @param searchTerm The term to search for.
 * @param filter_func The function used to filter the clients.
 * @return Pointer to the head of the filtered list.
 */
ClientNode *client_filtered_list(ClientNode *head, char *searchTerm, bool(*filter_func)(Client*,char*));

/**
 * @brief Default filter function for searching clients.
 * 
 * @param client Pointer to the client data.
 * @param searchTerm The term to search for.
 * @return True if the client matches the search term, false otherwise.
 */
bool client_search_filter(Client* client, char *searchTerm);

#endif // CLIENTLIST_H

