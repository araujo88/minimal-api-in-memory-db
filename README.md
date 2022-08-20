# minimal-api-in-memory-db

In-memory database RESTful API with in-memory database implemented via linked lists implemented in C language using Unix websockets for networking and POSIX for multithreading.

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

The endpoints are defined in the `routes.h` file.

`GET /` - root with "Hello world" message <br>
`GET /users` - lists all users in .json format <br>
`GET /users/<id>` - list user data by its id <br>
`PUT /users/<id>` - update user data by its id <br>
`DELETE /users/<id>` delete user by its id <br>
`POST /users` - creates a new user <br>

### Tests

A simple Python file located in `tests/tests.py` can be used to test each endpoint.
