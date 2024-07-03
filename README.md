## Hashmap CLI Program

### Overview
A command-line interface (CLI) program that implements a simple hashmap. This project demonstrates fundamental programming concepts in C, including hash functions, dynamic memory management, and user input processing.

### Features
- **Set Key-Value Pairs**: Add or update entries in the hashmap.
- **Retrieve Values**: Fetch values by their associated keys.
- **Remove Entries**: Delete key-value pairs from the hashmap.
- **Check Size**: Get the number of key-value pairs stored.
- **Command Processing**: Handle various user commands interactively.

### Key Functions
1. **hash**: Computes the hash value for a given key.
2. **set**: Adds or updates a key-value pair.
3. **get**: Retrieves the value for a given key.
4. **remove_entry**: Deletes a key-value pair.
5. **free_map**: Frees all allocated memory.
6. **size**: Returns the count of stored key-value pairs.

### Usage
- **set <key> <value>**: Adds a new key-value pair or updates an existing one.
- **get <key>**: Prints the value associated with the key.
- **remove <key>**: Deletes the key-value pair.
- **size**: Displays the number of entries in the hashmap.
- **quit**: Exits the program.

### Example Commands
```sh
cmd> set 1 Hello
cmd> set 2 World
cmd> get 1
Hello
cmd> get 2
World
cmd> size
2
cmd> remove 1
cmd> size
1
cmd> quit
```

### Main Function
The program continuously reads and processes user commands, updating the hashmap and printing results or error messages accordingly. It ensures efficient and dynamic handling of key-value pairs within a fixed-size hash table.

---

This project illustrates the application of basic data structures and algorithms in C, providing a practical example of managing dynamic data efficiently using hashmaps.
