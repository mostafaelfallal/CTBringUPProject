# Client Code Flow (Draft)

## Threads

The client uses **two threads**:

- **Network thread**
  - Runs in the main application thread
  - Handles the TCP connection and sending data

- **User input thread**
  - Runs as a worker thread
  - Listens for user input from `STDIN`

---

## Flow

1. The client is created.
   - TCP socket signals are connected to debug/logging slots.
   - Server address is set to `localhost` and the port is taken from `common.h`.

2. The client attempts to connect to the server.

3. The user input worker thread is started.
   - A socket notifier is set up on `STDIN` (read events).
   - When input is available, `onReadyRead` is triggered.
   - The input line is read and a `userInputReceived` signal is emitted.

4. The `userInputReceived` signal is connected to the network thread’s `sendData` slot.
   - If the client is connected, `sendData` writes the command directly to the TCP socket.
   - If the client is disconnected, the command is buffered in a queue.

5. After each user input:
   - The client checks the connection state.
   - If disconnected, it tries to reconnect.
   - Once connected, any buffered commands are flushed and sent in order.
