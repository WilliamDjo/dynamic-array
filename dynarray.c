#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define STARTING_CAPACITY 8

typedef struct DA {
  void **items; // Array of void pointers
  int size; // Current number of elements
  int capacity; // Maximum number of elements before resizing
} DA;


DA* DA_new (void) {
  // allocate and return a new dynamic array
  DA* arr = malloc(sizeof(DA));
  if (arr == NULL) {
    fprintf(stderr, "Failed to allocate memory for DynamicArray\n");
    exit(EXIT_FAILURE);
  }

  arr->size = 0;
  arr->capacity = STARTING_CAPACITY;
  arr->items = malloc(sizeof(void *) * arr->capacity);
  if (arr->items == NULL) {
      fprintf(stderr, "Failed to allocate memory for items\n");
      free(arr);
      exit(EXIT_FAILURE);
  }

  return arr;
}

int DA_size(DA *da) {
  // return the number of items in the dynamic array
  return da->size;
}

void DA_push (DA* da, void* x) {
  // push to the end
  if (da->size == da->capacity) {
    da->capacity *= 2;
    da->items = realloc(da->items, sizeof(void *) * da->capacity);
  }
  da->items[da->size++] = x;
}

void *DA_pop(DA *da) {
  if (da->size == 0) {
      fprintf(stderr, "Cannot pop from empty array\n");
      return NULL;
  }
  return da->items[--da->size];
}

void DA_set(DA *da, void *x, int i) {
  if (i < 0 || i >= da->size) {
    fprintf(stderr, "Index %d out of bounds for setItem\n", i);
    return;
  }
  da->items[i] = x;
}

void *DA_get(DA *da, int i) {
  if (i < 0 || i >= da->size) {
    fprintf(stderr, "Index %d out of bounds for getItem\n", i);
    return NULL;
  }
  return da->items[i];
}

void DA_free(DA *da) {
  free(da->items);
  free(da);
}

int main() {
    DA* da = DA_new();

    assert(DA_size(da) == 0);

    // basic push and pop test
    int x = 5;
    float y = 12.4;
    DA_push(da, &x);
    DA_push(da, &y);
    assert(DA_size(da) == 2);

    assert(DA_pop(da) == &y);
    assert(DA_size(da) == 1);

    assert(DA_pop(da) == &x);
    assert(DA_size(da) == 0);
    assert(DA_pop(da) == NULL);

    // basic set/get test
    DA_push(da, &x);
    DA_set(da, &y, 0);
    assert(DA_get(da, 0) == &y);
    DA_pop(da);
    assert(DA_size(da) == 0);

    // expansion test
    DA *da2 = DA_new(); // use another DA to show it doesn't get overriden
    DA_push(da2, &x);
    int i, n = 100 * STARTING_CAPACITY, arr[n];
    for (i = 0; i < n; i++) {
      arr[i] = i;
      DA_push(da, &arr[i]);
    }
    assert(DA_size(da) == n);
    for (i = 0; i < n; i++) {
      assert(DA_get(da, i) == &arr[i]);
    }
    for (; n; n--)
      DA_pop(da);
    assert(DA_size(da) == 0);
    assert(DA_pop(da2) == &x); // this will fail if da doesn't expand

    DA_free(da);
    DA_free(da2);
    printf("OK\n");
}
