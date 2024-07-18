# myFTP - FTP Server

## Overview

**myFTP** is an FTP server project implemented in C, which supports multiple clients simultaneously using `select` for command management and `fork` for data transfer. The server adheres to the given protocol and is designed to be RFC959 compliant. This project includes the server-side implementation and aims to support both active and passive data transfer modes.

## Features

- **Authentication**: Supports an Anonymous account with an empty password.
- **Multi-client Handling**: Uses `select` for managing commands and `fork` for data transfers to handle multiple clients concurrently.
- **Data Transfer Modes**: Supports both active and passive modes for data transfers.

## Compilation and Execution

The project is compiled via a `Makefile` which includes the following rules:
- `make re`: Recompiles the project.
- `make clean`: Removes temporary and object files.
- `make fclean`: Cleans up all compiled files and binaries.

### Compilation

To compile the project, navigate to the project directory and run:
```sh
make
```

### Execution

To run the FTP server, use the following command:
```sh
./myftp <port> <path>
```
- `port`: The port number on which the server socket listens.
- `path`: The path to the home directory for the Anonymous user.

Example:
```sh
./myftp 2121 /home/anonymous
```

### Usage

To see the help message, use:
```sh
./myftp --help
```
Output:
```
USAGE: ./myftp port path
port is the port number on which the server socket listens
path is the path to the home directory for the Anonymous user
```

## Error Handling

All error messages are written to the error output, and the program exits with code `84` for errors (or `0` if there is no error).

## Directory Structure

- **src/**: Contains all the source files.
- **include/**: Contains all the header files.
- **tests/**: Contains test cases and testing utilities for the project.
- **RFC/**: Contains documentation and notes related to RFC959 compliance.
- **Makefile**: The makefile for compiling the project.

## Protocol and RFC Compliance

The server follows the protocol described in the project requirements and aims to be compliant with RFC959. Request sequences are implemented according to the protocol, ensuring correct communication and data transfer processes.
