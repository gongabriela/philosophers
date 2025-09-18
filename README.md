# Philosophers

This project is part of the 42 curriculum and focuses on solving the classic **Dining Philosophers Problem** using multithreading in C. The goal is to simulate philosophers sitting at a table, thinking and eating, while avoiding deadlocks and ensuring synchronization.

## Table of Contents

- [About](#about)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)

## About

The Dining Philosophers Problem is a classic synchronization problem in computer science. It involves a group of philosophers who do only three things: think, eat, and sleep. However, they share a limited number of forks, and the challenge is to design a protocol that allows them to eat without causing deadlock or starvation.

In this project, we implement a solution using **POSIX threads (pthreads)** and **mutexes** to manage shared resources (the forks) and ensure that philosophers can eat without conflicts.

## Requirements

- C compiler (e.g., `gcc`)
- POSIX threads library
- Makefile utility

## Installation

Clone the repository:

```bash
git clone https://github.com/gongabriela/philosophers.git
cd philosophers
````

Build the project:

```bash
make
```

## Usage

Run the program with the following syntax:

```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

### Arguments:

* `number_of_philosophers`: The number of philosophers (and forks).
* `time_to_die`: Time in milliseconds before a philosopher dies from starvation.
* `time_to_eat`: Time in milliseconds a philosopher spends eating.
* `time_to_sleep`: Time in milliseconds a philosopher spends sleeping.
* `number_of_times_each_philosopher_must_eat` *(optional)*: Number of times each philosopher must eat before the simulation ends.

Example:

```bash
./philo 5 800 200 200 7
```

This command simulates 5 philosophers, each having 7 meals, with 800ms to die, 200ms to eat, and 200ms to sleep.
