## Overview

This is my implementation of *Practicum I - Caching* for CS5600 F23. \
This assignment builds upon the previous Memory Hierarchy Simulation assignment. An description of this assignment is as follows:

*Currently, messages are stored on disk (in either a file per message stored in a folder, or a block per message in a single file).\
Finding a message therefore requires access to disk. In this part, you will add a "cache" so that some number of messages are stored\
in a paged structure in memory. Your messages must be a fixed size; the choice of size is yours (but should be a power of 2, e.g.,\
256, 512, or 1024 bytes). Of course, part of the message's bytes are used for "house keeping" such as identification of the sender\
and the receiver, time sent, and perhaps priority, whether it is encrypted, etc. Modify your code from the prior assignment as needed.*

*The size of a message and the number of messages that are cached should be configurable in either global variables set in an include\
file or a configuration file stored on disk that is read upon startup of the program. For testing purposes, a smaller cache and\
message size is recommended, e.g., 1024 bytes per message and 16 message cache. Of course, you should adjust these limits and sizes\
as you see fit for development and testing.*

*Having a cache means that every messages that is stored ("sent") is stored in the cache and also written to disk. When a message is\
read (found), it should first be looked for in cache. If the message cannot be found in the cache, the message needs to be loaded\
from disk and place in the cache.*

*Create appropriate lookup data structures to facilitate finding messages in the cache. In your code, thoroughly describe your\
strategy and design and why you chose it. Mention alternative designs and why you did not consider them. You may discuss your\
caching strategy and implementation approach with your colleagues on Teams, but you may not share code.*

## Design Decisions
For this project I chose to implement my cache using a Doubly Linked List (DLL) data structure. This is a commonly used strategy,\
and one that is simple enough to execute. In my implementation, each node in the DLL contains pointers to the previous and next\
nodes in the list, as well as a pointer to the message struct being stored. For the LRU cache, the order of nodes reflects the access\
history, with the most recently accessed message at the front and the least recently accessed at the end. For the random cache, the\
order of messages is of course random. With the DLL implementation most operations take take O(n) time worst case. However, in the LRU\
implementation, finding the most recently and least recently used messages takes O(1) time. 

A second option I considered was adding a hash table to my implementation in order to make lookups run in O(1) time. The keys of the hash\
map represent message identifiers, and the corresponding values store references to the nodes in the doubly linked list containing the messages.\
This allows for efficient retrieval and updating of messages. However, this design introduces additional space complexity due to the hash map,\
and managing synchronization between the hash map and the linked list requires careful attention. Additionally, this technique proved challenging\
due to the absence of an upper bound on the number of messages that can be created and stored in this assignment. Designing an efficient hash\
algorithm that evenly distributes stored messages across the cache without frequent collisions proved to be difficult in this scenario.

Another potential strategy to implement a cache is employing a combination of an array and a priority queue. The array can store\
messages, and the priority queue can keep track of the order based on access times. While this approach may facilitate quick identification\
of the least recently used item through the priority queue, updating the access times and maintaining consistency between the array and the\
priority queue can lead to increased complexity and potentially higher overhead.

Ultimately, I am satisfied with the implmenetation of the cache using a Doubly Linked List. I believe it provides a good trade off between\
efficienty and simplicity in both the LRU implementation as well as the random implmenetation.

## File Breakdown
- message.h     - message struct definition and function headers
- message.c     - implementation of the message functions
- cache.h       - cache struct definition and function headers
- lruCache.c    - implementation of the cache functions using a LRU replacement strategy
- randCache.c   - implementation of the cache functions using a random replacement strategy
- cacheTest.c   - tests all cache and message functions
- cacheEval.c   - evalutates the cache with random message selection on the three required metrics:
  1. number of cache hits per 1000 random message accesses
  2. number of cache misses per 1000 random message accesses
  3. cache hit ratio per 1000 random message accesses
- cacheEvalLoc.c   - evalutates the cache with semi-random selection (temporal locality introduced) on the three required metrics:
  1. number of cache hits per 1000 random message accesses
  2. number of cache misses per 1000 random message accesses
  3. cache hit ratio per 1000 random message accesses
- dll.h         - doubly linked list definitions and function headers
- dll.c         - implementation of the doubly linked list functions
- dllTest.c     - tests all doublt linked list functions
- genRandWord.h - random word generator function headers
- genRandWord.c - implementation of random word generator function
- messages/     - directory used to store messages
- Makefile      - makefile used to make test and evaluation builds for the project

## Instructions to Run

Running "make" in the project directory will build all test and evaluation executables. The test executables are called dllTest,\
lruTest, and randTest. These are used to test the doubly linked list, LRU Cache, and Random Cache respectivley. The evaluation\
executables are called lruEval and randEval. These are used to evaluate the LRU Cache and Random Cache respectively. In order to build\
just the test files or just the evaluation files, run "make test" or "make eval". Running "make clean" will remove all executables\
and all messages from messages directory.

Finally, it is advised to use a cache size of 3 for testing and 16 for evaluation. The cache size can be set by the global variable\
CACHESIZE found in the cache.h header file.