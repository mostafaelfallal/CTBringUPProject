# Server Code Flow (Draft)

## Flow

1. The server is created.
   - A `QTcpServer` instance is created.
   - `QTcpServer::newConnection` is connected to `onNewConnection`.

2. On new connection:
   - The server retrieves the incoming socket.
   - A `ClientContext` is created to track:
     - The client socket
     - The client state (e.g. authentication)
   - `ClientContext::messageReceived` is connected to `Server::onClientMessage`.

3. On client message:
   - The server parses the received command into JSON.
   - A command factory is used to create the appropriate Command object.
   - The command validates the input and checks whether the client is authenticated.
   - The command executes its specific functionality.

---

## Commands

### AUTH
- Reads the first two arguments.
- Validates client authentication.

---

### CREATE
- Uses the `QFile` class.
- Checks the filename (first argument).
- Creates the file using `open()` with `QIODevice::WriteOnly`.

---

### WRITE
- Uses the `QFile` class.
- Checks the filename (first argument).
- Verifies the file exists.
- Opens the file with truncation.
- Writes the second argument to the file using `QTextStream`.

---

### READ
- Uses the `QFile` class.
- Checks the filename (first argument).
- Verifies the file exists.
- Opens the file in read-only mode.
- Reads the contents using `QTextStream`.

---

### APPEND
- Same as WRITE.
- Opens the file using the append flag instead of truncation.

---

### DELETE
- Uses the `QFile` class.
- Checks the filename (first argument).
- Verifies the file exists.
- Removes the file using `remove()`.

---

### LIST
- Uses `QDir` with the current path.
- Reads directory entries using `entryList()`.

---

### RENAME
- Uses the `QFile` class.
- Checks the filename (first argument).
- Verifies the file exists.
- Renames the file using `rename()`.

---

### INFO
- Uses the `QFile` class.
- Checks the filename (first argument).
- Verifies the file exists.
- Retrieves file information using `QFileInfo`.
