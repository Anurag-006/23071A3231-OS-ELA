# Chat Application Using Sockets (IPC)

This project demonstrates two types of chat applications: one using **Internet Domain Sockets** and the other using **Unix Domain Sockets**. These applications use **sockets for inter-process communication (IPC)** to facilitate real-time chat between a client and a server.

## Table of Contents

- [Project Overview](#project-overview)
- [Features](#features)
- [Technology Stack](#technology-stack)
- [Prerequisites](#prerequisites)
- [Installation](#installation)
- [Usage](#usage)
  - [Internet Domain Socket](#internet-domain-socket-chat-application)
  - [Unix Domain Socket](#unix-domain-socket-chat-application)
- [Directory Structure](#directory-structure)
- [Code Explanation](#code-explanation)
  - [Internet Domain Socket (TCP)](#internet-domain-socket-tcp)
  - [Unix Domain Socket](#unix-domain-socket)
- [License](#license)
- [Authors](#authors)

## Project Overview

This repository contains two chat applications implemented using **sockets** for communication:

1. **Internet Domain Socket Chat Application**: This chat application uses an Internet Domain Socket (TCP) to communicate over the network.
2. **Unix Domain Socket Chat Application**: This chat application uses Unix Domain Sockets, allowing communication between processes on the same machine.

Both applications are **client-server** architectures, where the server listens for incoming connections, and the client sends messages that the server processes and responds back.

## Features

- Real-time communication between client and server.
- **Unix Domain Socket** implementation for local IPC (inter-process communication).
- **Internet Domain Socket (TCP)** implementation for network-based communication.
- Uses **`poll()`** for non-blocking I/O to handle multiple input/output streams.
- Console-based chat interface with real-time message display.
- Client sends messages to the server and receives responses.

## Technology Stack

- **C Programming Language**: Used to implement the server and client applications.
- **Sockets (Unix & Internet Domain)**: To implement inter-process communication (IPC).
- **Poll**: For non-blocking I/O handling.

## Prerequisites

Before you start using this project, ensure you have the following:

- **A Linux-based OS** (or WSL on Windows).
- **GCC Compiler**: Required for compiling the C programs.
- **Basic understanding of C programming** and **networking concepts**.
- **Basic knowledge of Sockets** and **IPC** (Inter-Process Communication).
- Familiarity with the **client-server architecture**.

## Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/Anurag-006/23071A3231-OS-ELA.git
   cd 23071A3231-OS-ELA
   ```

2. Compile the server and client programs:

   ```bash
   # For Internet Domain Sockets
   gcc -o internet-domain/server internet-domain/server.c
   gcc -o internet-domain/client internet-domain/client.c

   # For Unix Domain Sockets
   gcc -o unix-domain/server unix-domain/server.c
   gcc -o unix-domain/client unix-domain/client.c
   ```

3. You now have the following executables:
   - `internet-domain/server` - The server using Internet Domain Sockets.
   - `internet-domain/client` - The client using Internet Domain Sockets.
   - `unix-domain/server` - The server using Unix Domain Sockets.
   - `unix-domain/client` - The client using Unix Domain Sockets.

## Usage

### Internet Domain Socket Chat Application

1. **Start the server** by running the `server` program from the `internet-domain` directory:

   ```bash
   ./internet-domain/server
   ```

   The server will start and listen for incoming connections on port `9999`.

2. **Start the client** by running the `client` program from the `internet-domain` directory:

   ```bash
   ./internet-domain/client
   ```

   The client will attempt to connect to the server on port `9999` The hardcoded port can be changed as per liking.

3. Start chatting! You can send messages from the client, and the server will reply.

### Unix Domain Socket Chat Application

1. **Start the server** by running the `server` program from the `unix-domain` directory:

   ```bash
   ./unix-domain/server
   ```

   The server will start and listen for incoming connections via the Unix Domain Socket at `/tmp/chat_socket`.

2. **Start the client** by running the `client` program from the `unix-domain` directory:

   ```bash
   ./unix-domain/client
   ```

   The client will attempt to connect to the server using the Unix Domain Socket at `/tmp/chat_socket`.

3. Start chatting! You can send messages from the client, and the server will reply.

## Directory Structure

```plaintext
23071A3231-OS-ELA/
│
├── internet-domain/
│   ├── client.c          # Client implementation for Internet Domain Socket
│   └── server.c          # Server implementation for Internet Domain Socket
│
├── readme.md             # This readme file
│
└── unix-domain/
    ├── client.c          # Client implementation for Unix Domain Socket
    └── server.c          # Server implementation for Unix Domain Socket
```

## Code Explanation

### Internet Domain Socket (TCP)

#### Server (`server.c`):

- **Creating the socket**: The server creates a TCP socket using the `socket(AF_INET, SOCK_STREAM, 0)` function.
- **Binding the socket**: The socket is bound to a specific port (9999) using `bind()`. This binds the server to port `9999`, allowing it to listen for incoming connections.
- **Listening for connections**: The server starts listening for incoming client connections using `listen()`. This means that the server can now accept connections from any client trying to connect to it.
- **Accepting connections**: Once a client connects, the server accepts the connection using `accept()`. This returns a new socket file descriptor for communication with the client.
- **Receiving messages**: The server uses `recv()` to receive messages from the client. It waits for data sent by the client and reads it into a buffer.
- **Sending messages**: The server replies to the client using `send()`. This function sends the server's message back to the client.

#### Client (`client.c`):

- **Creating the socket**: The client creates a TCP socket using `socket(AF_INET, SOCK_STREAM, 0)`.
- **Connecting to the server**: The client connects to the server's IP address and port `9999` using `connect()`.
- **Sending messages**: The client sends messages to the server using `send()`.
- **Receiving responses**: The client waits for the server's response using `recv()` and prints it.

### Unix Domain Socket

#### Server (`server.c`):

- **Creating the socket**: The server creates a Unix Domain Socket using `socket(AF_UNIX, SOCK_STREAM, 0)`.
- **Binding the socket**: The server binds the socket to a local file path (`/tmp/chat_socket`) using `bind()`. This is the address where the server will listen for incoming connections from clients.
- **Listening for connections**: The server listens for incoming client connections using `listen()`.
- **Accepting connections**: The server accepts incoming client connections using `accept()`. It waits for a client to connect to the socket file path.
- **Receiving and sending messages**: The server handles receiving messages using `recv()` and sends responses using `send()`.

#### Client (`client.c`):

- **Creating the socket**: The client creates a Unix Domain Socket using `socket(AF_UNIX, SOCK_STREAM, 0)`.
- **Connecting to the server**: The client connects to the server using the Unix Domain Socket at the local path (`/tmp/chat_socket`) using `connect()`.
- **Sending messages**: The client sends messages to the server with `send()`.
- **Receiving responses**: The client waits for and receives messages from the server using `recv()`.

## Authors

- **Avaneesh (23071A3206)**
- **Datta (23071A3220)**
- **Silpi (23071A3221)**
- **Anurag (23071A3231)**
