# Client Code Flow (Draft)

## Topics 

  - Handles the TCP connection and sending data
  - Listens for user input from `STDIN` using notifier

---

## Flow

1. The client is created.
   - Creating a notifier for user inputs
   - A socket notifier is set up on `STDIN` (read events).
   - connecting TCP socket connection signals to slots for debugging and recovery
   - connecting TCP socket data ready signal to `onServerResponse` slot
   - connecting notifier signal to `onUserInput` slot

2. The client attempts to connect to the server.
   - Server address is set to `localhost` and the port is taken from `common.h`.

4. The `onUserInput` slot
   - reads a line.
   - sends it to the Server using `sendData` method.

5. The `sendData` method
   - if connected, send command directly to Server.
   - else, buffer the command into the Queue and try to connect again.
   - Once connected, any buffered commands are flushed and sent in order.
