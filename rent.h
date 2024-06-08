/** @file rent.h
 *  @brief Rent data structure definition and its constructor / destructor.
 */
#ifndef RENT_H
#define RENT_H

#include "car.h"
#include "carlist.h"
#include "client.h"
#include "clientlist.h"
#include <stdbool.h>

/**
 * @struct Rent
 * @brief Represents a rental transaction in the system.
 */
struct Rent {
  unsigned id;          /**< Rent identifier. */
  unsigned car_id;      /**< Identifier of the rented car. */
  unsigned client_id;   /**< Identifier of the client. */
  bool finished;        /**< Status of the rent (finished or not). */
  char *date_start;     /**< Start date of the rent. */
  char *date_end;       /**< End date of the rent. */
};

typedef struct Rent Rent;

/** 
 * Sets the auto increment value for automatic rent ids
 * @param inc increment value to set.
 */
void set_rent_auto_increment(unsigned inc);
/** 
 * Gets the auto increment value for automatic rent ids
 * @returns The current auto increment value for the automatic rent ids.
 */
unsigned get_rent_auto_increment();


/**
 * @brief Creates a new rent data instance.
 * 
 * @param id Rent identifier. (leave 0 for auto increment)
 * @param car_id Identifier of the rented car.
 * @param client_id Identifier of the client.
 * @param date_start Start date of the rent.
 * @param date_end End date of the rent.
 * @param finished Status of the rent (finished or not).
 * @return Pointer to the newly created Rent instance.
 */
Rent *make_rent_data(unsigned id, unsigned car_id, unsigned client_id, char *date_start, char *date_end, bool finished);

/**
 * @brief Frees the memory allocated for a Rent instance.
 * 
 * @param rent Pointer to the Rent instance to be freed.
 */
void free_rent_data(Rent *rent);

/**
 * @brief Marks a rent as finished.
 * 
 * @param rent Pointer to the Rent instance to be finished.
 * @param cars Pointer to the car list.
 * @param km_driven kilometers driven by client during rent.
 * @returns cost of the rent (0 if rent was already finished)
 */
unsigned rent_finish(Rent *rent, CarNode *cars, int km_driven);

/**
 * @brief Fetches the car associated with a rent.
 * 
 * @param rent Pointer to the Rent instance.
 * @param cars Pointer to the list of cars.
 * @return Pointer to the associated Car instance.
 */
Car *fetch_car(Rent *rent, CarNode *cars);


/**
 * @brief Fetches the client associated with a rent.
 * 
 * @param rent Pointer to the Rent instance.
 * @param clients Pointer to the list of clients.
 * @return Pointer to the associated Client instance.
 */
Client *fetch_client(Rent *rent, ClientNode *clients);

#endif // RENT_H
