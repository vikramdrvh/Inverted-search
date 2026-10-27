# Inverted Search in C

This is a custom C implementation of an **Inverted Search** (or inverted index) utility. If you've ever wondered how search engines can instantly tell you which documents contain a specific word, this data structure is the core mechanism behind it. 

Instead of scanning every file from top to bottom every time a search is run, this program pre-processes text files, maps out every unique word, and records exactly which files that word appears in. 

## Core Features
* **File Validation:** Parses command-line inputs and validates text files before processing.
* **Index Creation:** Reads through provided files (like `file1.txt` and `file2.txt`) and builds an in-memory inverted index database.
* **Instant Search:** Queries the database for specific words and instantly retrieves the linked files.
* **State Persistence:** Saves the generated in-memory database to a local file (`database.txt`) so you don't have to rebuild the index from scratch every run.
* **Dynamic Updates:** Loads and modifies an existing saved database with new files.
* **Visualization:** Prints the current state of the database and its word-to-file mappings to the terminal.
