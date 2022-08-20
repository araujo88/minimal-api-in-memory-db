# minimal-api-in-memory-db

A minimal RESTful API with in-memory database implemented via linked lists implemented in C language using Unix websockets for networking and POSIX for multithreading.

## Running on Docker

### Requirements

`docker` <br>
`docker compose`

### Running

`docker compose up --build`

## Running locally (Linux)

### Requirements

`make` <br>
`gcc`

### Running

`make clean` <br>
`make`

## Usage

A simple "User" model (`models.h`) with fields "name" and "surname" is implemented in a in-memory database using linked lists. The first user starts with id = 0 and then is incremented when a new user is created. The user data in .json format can then be retrieved via its id.

### Endpoints

The endpoints are defined in the `routes.h` file. The default port is 8001.

`GET /` - root with "Hello world" message <br>
`GET /users` - lists all users in .json format <br>
`GET /users/<id>` - list user data by its id <br>
`PUT /users/<id>` - update user data by its id <br>
`DELETE /users/<id>` delete user by its id <br>
`POST /users` - creates a new user <br>

### Tests

A simple Python file located in `tests/tests.py` can be used to test each endpoint.

## Project structure overview

### settings.h

Contains the server settings. Currently, the only setting is ALLOWED_HOSTS, which contains an array of strings corresponding to the accepted client IP addresses.

### models.h

Contains the database model. On this example, the model consists of a simple "user" table with fields "name" and "surname". Example of an user entry in .json format:

`{"name": "Giga", "surname": "Chad"}`

### routes.h

Contains all the accepted routes and a respective accepted HTTP methods.

### linked_list.h

Contains all functions related to the implementation of single linked lists in C, including creating a node, inserting, deleting, etc.

### database.h

Integrates the requests from the HTTP methods to the linked list module, wrapping its functions and serving as a high level module.

### views.h

The views related to each route and its respective HTTP methods.

### server.h

This module contains functions that implement a multi-threaded server using Unix sockets.
