# Little chat app

## What goes with what

- For the client, you need:
  - client.cpp (contains the main)
  - queue.h
  - receiver.cpp/h
  - util.h
- For the server, you need:
  - accepter.cpp/h
  - list.h
  - queue.h
  - receiver.cpp/h
  - server.cpp (contains the main)
  - util.h

Things can be factorised: most things can fit within a single class.

## Threads

We need a thread for the client, the server, the accepter and the receivers,
but they don't need to be in individual classes.
