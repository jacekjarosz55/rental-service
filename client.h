
/** @file client.h
 *  @brief Client structure definition, and it's constructor / destructor
 */
#ifndef CLIENT_H
#define CLIENT_H

/**
 * @struct Client
 * @brief Represents a client in the system.
 */
struct Client {
  unsigned id;             /**< Client identifier. */
  char *first_name;        /**< First name of the client. */
  char *last_name;         /**< Last name of the client. */
  char *phone_number;      /**< Phone number of the client. */
  char *email;             /**< Email address of the client. */
};

typedef struct Client Client;

/** 
 * Sets the auto increment value for automatic client ids
 * @param inc increment value to set.
 */
void set_client_auto_increment(unsigned inc);
/** 
 * Gets the auto increment value for automatic client ids
 * @returns The current auto increment value for the automatic client ids.
 */
unsigned get_client_auto_increment();


/**
 * @brief Creates a new client data instance.
 * 
 * @param id Client identifier. (leave 0 for auto increment)
 * @param first_name First name of the client.
 * @param last_name Last name of the client.
 * @param phone_number Phone number of the client.
 * @param email Email address of the client.
 * @return Pointer to the newly created Client instance.
 */
Client *make_client_data(unsigned id, char *first_name, char *last_name, char *phone_number, char *email);

/**
 * @brief Frees the memory allocated for a Client instance.
 * 
 * @param client Pointer to the Client instance to be freed.
 */
void free_client_data(Client *client);

#endif // CLIENT_H
