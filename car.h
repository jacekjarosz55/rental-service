/** @file car.h
 *  @brief Car structure definition, and it's constructor / destructor
 */
#ifndef CAR_H
#define CAR_H

/**
 * @struct Car
 * @brief Represents a car in the system.
 */
struct Car {
  unsigned id;          /**< Car identifier. */
  char *model;          /**< Model of the car. */
  char *make;           /**< Make of the car. */
  unsigned year;        /**< Manufacture year of the car. */
  unsigned cost;        /**< Cost of the car (per kilometer). */
  unsigned km_driven;   /**< Car mileage (in kilometers) */
};

typedef struct Car Car;

/** 
 * Sets the auto increment value for automatic car ids
 * @param inc increment value to set.
 */
void set_car_auto_increment(unsigned inc);
/** 
 * Gets the auto increment value for automatic car ids
 * @returns The current auto increment value for the automatic car ids.
 */
unsigned get_car_auto_increment();


/**
 * @brief Creates a new car data instance.
 * 
 * @param id Car identifier.
 * @param make Make of the car.
 * @param model Model of the car.
 * @param year Manufacture year of the car.
 * @param cost Cost of the car (per kilometer).
 * @param km_driven Car mileage (in kilometers)
 * @return Pointer to the newly created Car instance.
 */
Car *make_car_data(unsigned id, char *make, char *model, unsigned year, unsigned cost, unsigned km_driven);

/**
 * @brief Frees the memory allocated for a Car instance.
 * 
 * @param car Pointer to the Car instance to be freed.
 */
void free_car_data(Car *car);

#endif // CAR_H
