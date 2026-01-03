# Qt 6 TCP File Management System

A multi-threaded Client-Server application written in C++ using the **Qt 6** framework. This system allows clients to connect to a remote server to perform file system operations (create, read, write, delete) using a custom JSON-based command protocol.

## Features

* **Qt 6 Architecture:** Built and optimized for the latest Qt 6 ecosystem.
* **TCP Communication:** Persistent socket connection between multiple clients and a central server.
* **JSON Protocol:** All data exchange uses JSON for structured command and response handling.
* **Authentication:** Basic username/password protection for sensitive file operations.
* **Multi-threading:**
    * **Server:** Handles each client connection asynchronously.
    * **Client:** Uses a dedicated worker thread for non-blocking console input.
* **Unit Testing:** Integrated Google Test (GTest) suite for parsers, commands, and factories.

## Supported Commands

The client communicates with the server using the following text commands. Arguments are separated by spaces or semicolons.

| Command | Syntax | Description | Auth Required |
| :--- | :--- | :--- | :--- |
| **AUTH** | `AUTH <user>;<pass>` | Authenticate with the server. | No |
| **CREATE** | `CREATE <filename>` | Create a new empty file. | Yes |
| **WRITE** | `WRITE <filename>;<text>` | Overwrite a file with new content. | Yes |
| **APPEND** | `APPEND <filename>;<text>` | Append text to the end of a file. | Yes |
| **READ** | `READ <filename>` | Read and display file contents. | Yes |
| **DELETE** | `DELETE <filename>` | Delete a file permanently. | Yes |
| **RENAME** | `RENAME <old>;<new>` | Rename a file. | Yes |
| **INFO** | `INFO <filename>` | Get file size and modification date. | Yes |
| **LIST** | `LIST` | List all files in the server directory. | Yes |

## Prerequisites

* **C++ Compiler:** GCC, Clang, or MSVC supporting C++17.
* **Qt Framework:** **Qt 6** (Core, Network, Concurrent modules).
* **Google Test:** Required for building the Test suite (`libgtest-dev`).

## Build Instructions

This project uses **QMake** (or `qmake6`).

1.  **Navigate to the project root:**
    ```bash
    cd /path/to/ProjectRoot
    ```

2.  **Generate Makefiles:**
    ```bash
    /path/to/qmake6 -r
    ```

3.  **Build All Modules:**
    ```bash
    make
    ```
    *Binaries will be generated in the `build/bin/` directory.*

## Usage

**Important:** All commands should be executed from the `Workspace` directory to ensure file paths and logs are managed correctly.

### 1. Starting the Server
The server must be started first.
```bash
cd Workspace
../build/bin/Server
```

### 2. Starting the Client
Open a new terminal, navigate to Workspace, and run the client.
```bash
cd Workspace
../build/bin/Client
```

Once connected, type commands directly into the console:

```
AUTH admin;admin
CREATE test.txt
WRITE test.txt;Hello World
READ test.txt
```

### Running Unit Tests
Run the Google Test suite to verify logic.
```bash
cd Workspace
../build/bin/Tests
```

## Project Structure

```
Root/
├── Client
│   ├── Client.cpp
│   ├── Client.h
│   ├── Client.pro
│   ├── InputWorker.h
│   ├── Makefile
│   └── main.cpp
├── Common.h
├── Makefile
├── Project.pro
├── README.md
├── Server
│   ├── ClientContext.cpp
│   ├── ClientContext.h
│   ├── Command.cpp
│   ├── Command.h
│   ├── Factory.cpp
│   ├── Factory.h
│   ├── ICommand.h
│   ├── Makefile
│   ├── Parser.cpp
│   ├── Parser.h
│   ├── Server.cpp
│   ├── Server.h
│   ├── Server.pro
│   └── main.cpp
├── Tests
│   ├── Command_Test.cpp
│   ├── Makefile
│   ├── Parser_Test.cpp
│   ├── Tests.pro
│   └── main.cpp
├── Workspace
│   ├── file
│   └── m.txt
├── build
│   └── bin
│       ├── Client
│       ├── Server
│       └── Tests
└── defaults.pri
```

## License
This project is open-source software.