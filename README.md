# Philosophers

A C implementation of the classic **Dining Philosophers** concurrency problem.

The project simulates philosophers sharing forks while eating, sleeping, and thinking.  
The main goal is to practice **threads, mutexes, synchronization, timing, and race-condition prevention**.

---

## Overview

Each philosopher is represented by a thread.

Each fork is protected by a mutex.

A philosopher must take two forks before eating.  
If a philosopher does not eat within `time_to_die`, they die and the simulation stops.

The simulation can also stop when every philosopher has eaten a required number of times.

---

## Usage

```bash
make
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
