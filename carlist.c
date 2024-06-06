#include "carlist.h"
#include "car.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

CarNode *add_car(CarNode **list, Car *data) {
  CarNode *new = (CarNode *)malloc(sizeof(CarNode));
  if (new == NULL) {
    return NULL;
  }
  new->next = NULL;
  new->data = data;

  CarNode *existing = *list;
  if (existing == NULL) {
    *list = new;
    return new;
  }

  while (existing->next) {
    existing = existing->next;
  }
  existing->next = new;
  return new;
}

CarNode *get_car_by_id(CarNode *head, unsigned id) {
  CarNode *cur = head;
  while (cur->next) {
    if(cur->data == NULL) { continue; }
    if (cur->data->id == id) {
      return cur;
    }
    cur = cur->next;
  }
  if (cur->data && cur->data->id == id) {
    return cur;
  }
  return NULL;
}

CarNode *get_car_by_make_model(CarNode *head, char *make, char *model) {
  while(head != NULL) {
    if (strcmp(head->data->make, make) == 0 && strcmp(head->data->model, model) == 0) {
      return head;
    }
    head = head->next;
  }
  return NULL;
}



bool update_car(CarNode *head, unsigned int id, Car *new_data) {
  CarNode *car = get_car_by_id(head, id);
  if(car == NULL) return false;
  free_car_data(car->data);
  car->data = new_data;
  return true;
}

bool car_make_comparator(Car* a, Car* b) {
 return (strcmp(a->make, b->make) > 0);
}

bool car_year_comparator(Car* a, Car* b) {
 return a->year > b->year;
}

bool car_km_driven_comparator(Car* a, Car* b) {
 return a->km_driven > b->km_driven;
}

void sort_car_list(CarNode **head, bool(*comparator)(Car*, Car*), bool descending) {
    if (*head == NULL || (*head)->next == NULL) {
        return;
    }

    bool swapped;
    CarNode *ptr1;
    CarNode *lptr = NULL;

    do {
        swapped = false;
        ptr1 = *head;

        while (ptr1->next != lptr) {
            if (descending ? !comparator(ptr1->data, ptr1->next->data) : comparator(ptr1->data, ptr1->next->data)) {
                Car *temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}


void free_car(CarNode *car) {
  free_car_data(car->data);
  car->data = NULL;
  free(car);
}

bool remove_car_by_id(CarNode **head, unsigned id) {
  if(head == NULL && *head == NULL) return false;
  CarNode *car = get_car_by_id(*head, id);
  if (car == NULL) {
    return false;
  }
  if (car == *head) {
    CarNode *tmp = *head;
    *head = (*head)->next;
    free_car(tmp);
    return true;
  }
  CarNode *cur = *head;
  while (cur->next != car) {
    if (cur->next == NULL)
      return false;
    cur = cur->next;
  }
  cur->next = car->next;
  free_car(car);
  return true;
}

void foreach_car(CarNode *head, void (*func)(Car *)) {
  while (head != NULL) {
    func(head->data);
    head = head->next;
  }
}

bool car_list_save_to_file(CarNode *head, char *filename) {
  FILE *file = fopen(filename, "w");
  if (!file) return false;
  while(head != NULL) {
    if (head->data) {
      fprintf(
        file,
        "%u,%s,%s,%u,%u,%u\n",
        head->data->id,
        head->data->model,
        head->data->make,
        head->data->year,
        head->data->cost,
        head->data->km_driven
      );
    }
    head=head->next;
  }
  fclose(file);
  return true;
}

CarNode* car_list_new_from_file(char *filename) {
  unsigned max_id = 0;


  FILE *file = fopen(filename, "r");
  if(!file) return NULL;

  CarNode *cars = NULL;

  char buf[1024];
  while(fgets(buf,sizeof(buf), file)) {
    unsigned id;
    char model[50];
    char make[50];
    unsigned year;
    unsigned cost;
    unsigned km_driven;

    int res = sscanf(buf, " %u,%49[^,],%49[^,],%u,%u,%u\n", &id, model, make, &year, &cost, &km_driven);
    if (res == 6){
      if (id >= get_car_auto_increment()) {
        set_car_auto_increment(id+1);
      }
      add_car(&cars, make_car_data(id, make, model, year, cost, km_driven));
    } 
  }
  fclose(file);
  return cars;
}

void free_car_list(CarNode *head) {
  if(head->next) {
    free_car_list(head->next);
  }
  free_car(head);
}



