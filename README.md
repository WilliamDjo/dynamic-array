# Dynamic Array Implementation in C

A educational project demonstrating fundamental concepts of **pointers**, **dynamic memory allocation**, and **arrays** in C programming. This implementation provides a generic dynamic array (similar to C++ vectors or Python lists) that can store pointers to any data type.

## 🎯 Learning Objectives

This project is designed to provide hands-on experience with:

- **Pointer manipulation** and dereferencing
- **Dynamic memory allocation** (`malloc`, `realloc`, `free`)
- **Void pointers** for generic programming
- **Array resizing** and capacity management
- **Memory management** and avoiding leaks
- **Struct usage** and data encapsulation
- **Error handling** in C

## 📋 Features

- **Generic Storage**: Uses `void*` pointers to store any data type
- **Dynamic Resizing**: Automatically doubles capacity when needed
- **Memory Safety**: Includes bounds checking and error handling
- **Standard Operations**: Push, pop, get, set operations
- **Comprehensive Testing**: Built-in test suite with assertions

## 🏗️ Data Structure

```c
typedef struct DA {
    void **items;    // Array of void pointers
    int size;        // Current number of elements
    int capacity;    // Maximum elements before resizing
} DA;
```

**Key Pointer Concepts Demonstrated:**

- `void **items`: Pointer to an array of void pointers
- `void *x`: Generic pointer that can point to any data type
- Dynamic allocation of pointer arrays

## 🔧 API Reference

### Core Functions

| Function                              | Description                      | Pointer Concepts            |
| ------------------------------------- | -------------------------------- | --------------------------- |
| `DA* DA_new(void)`                    | Creates new dynamic array        | Returns pointer to struct   |
| `void DA_push(DA* da, void* x)`       | Adds element to end              | Stores pointer to data      |
| `void* DA_pop(DA* da)`                | Removes and returns last element | Returns stored pointer      |
| `void* DA_get(DA* da, int i)`         | Gets element at index            | Returns pointer at index    |
| `void DA_set(DA* da, void* x, int i)` | Sets element at index            | Stores pointer at index     |
| `int DA_size(DA* da)`                 | Returns current size             | Dereferences struct pointer |
| `void DA_free(DA* da)`                | Frees allocated memory           | Deallocates pointer arrays  |

## 💡 Key Pointer & Memory Concepts

### 1. **Double Indirection (`void **items`)\*\*

```c
void **items;  // Pointer to array of pointers
```

- `items` points to an array
- Each element in the array is itself a pointer (`void*`)
- Access pattern: `items[i]` gives you the `void*` stored at index `i`

### 2. **Generic Programming with Void Pointers**

```c
int x = 5;
float y = 12.4;
DA_push(da, &x);    // Store address of x
DA_push(da, &y);    // Store address of y
```

- Store **addresses** of variables, not the values themselves
- One array can hold pointers to different data types

### 3. **Dynamic Memory Management**

```c
// Initial allocation
arr->items = malloc(sizeof(void*) * arr->capacity);

// Resizing when full
da->items = realloc(da->items, sizeof(void*) * da->capacity);

// Cleanup
free(da->items);
free(da);
```

### 4. **Pointer Arithmetic in Array Access**

```c
da->items[da->size++] = x;  // Equivalent to *(da->items + da->size) = x
```

## 🚀 Usage Examples

### Basic Usage

```c
DA* arr = DA_new();

// Store different data types
int num = 42;
char ch = 'A';
float pi = 3.14;

DA_push(arr, &num);
DA_push(arr, &ch);
DA_push(arr, &pi);

// Retrieve and cast back
int* retrieved_num = (int*)DA_get(arr, 0);
printf("Number: %d\n", *retrieved_num);  // Prints: 42

DA_free(arr);
```

### Working with Strings

```c
char* words[] = {"hello", "world", "pointers"};
DA* string_arr = DA_new();

for(int i = 0; i < 3; i++) {
    DA_push(string_arr, words[i]);
}

char* first_word = (char*)DA_get(string_arr, 0);
printf("%s\n", first_word);  // Prints: hello
```

## 🧪 Testing

The program includes comprehensive tests that demonstrate:

1. **Basic Operations**: Push, pop, size tracking
2. **Pointer Equality**: Verifying stored addresses match original addresses
3. **Dynamic Expansion**: Adding 800 elements (100× initial capacity)
4. **Memory Independence**: Multiple arrays don't interfere with each other
5. **Error Handling**: Bounds checking and empty array handling

### Running Tests

```bash
gcc -o dynamic_array dynamic_array.c
./dynamic_array
```

Expected output: `OK`

## ⚠️ Important Notes

### Memory Management

- **Always call `DA_free()`** to prevent memory leaks
- The array stores **pointers**, not copies of data
- Original data must remain valid while stored in the array

### Pointer Safety

```c
// ❌ WRONG - storing pointer to local variable that goes out of scope
void bad_example() {
    int local_var = 10;
    DA_push(arr, &local_var);  // Danger! local_var dies when function ends
}

// ✅ CORRECT - storing pointer to persistent data
int global_var = 10;
DA_push(arr, &global_var);     // Safe - global_var persists
```

### Type Safety

- No compile-time type checking with `void*`
- Programmer responsible for correct casting:

```c
int x = 5;
DA_push(arr, &x);
int* ptr = (int*)DA_get(arr, 0);  // Must cast back to correct type
```

## 🔍 Advanced Concepts Demonstrated

1. **Function Pointers**: Could be extended to store function pointers
2. **Memory Alignment**: Understanding pointer size consistency
3. **Realloc Behavior**: How memory expansion works under the hood
4. **Pointer Arithmetic**: Array indexing as pointer manipulation

## 🎓 Educational Extensions

Try implementing these features to deepen understanding:

- **Insert/Delete at arbitrary positions**
- **Iterator functions** using function pointers
- **Type-safe wrappers** using macros
- **Custom comparison functions** for sorting
- **Reference counting** for automatic memory management

## 🔧 Compilation

```bash
# Basic compilation
gcc -o dynamic_array dynamic_array.c

# With debugging info
gcc -g -o dynamic_array dynamic_array.c

# With warnings
gcc -Wall -Wextra -o dynamic_array dynamic_array.c
```
