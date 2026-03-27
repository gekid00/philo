# Philosophers

A multithreaded simulation of the classic Dining Philosophers problem,
implemented in C using POSIX threads and mutexes. This project explores
concurrency, synchronization, and resource-sharing constraints.

## Technologies

- C (compiled with `cc`)
- POSIX Threads (`pthread`)
- Mutexes for synchronization
- `gettimeofday` for millisecond-precision timestamps

## Build

```bash
make        # Compile the project
make clean  # Remove object files
make fclean # Remove object files and binary
make re     # Full recompile
```

## Usage

```bash
./philo <nb_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [nb_meals]
```

| Argument           | Description                                         |
|--------------------|-----------------------------------------------------|
| `nb_philosophers`  | Number of philosophers (and forks) at the table      |
| `time_to_die`      | Time in ms before a philosopher dies without eating  |
| `time_to_eat`      | Time in ms a philosopher spends eating               |
| `time_to_sleep`    | Time in ms a philosopher spends sleeping             |
| `nb_meals`         | (Optional) Simulation stops after each philosopher eats this many times |

### Examples

```bash
./philo 5 800 200 200        # 5 philosophers, no meal limit
./philo 4 410 200 200 10     # 4 philosophers, stops after 10 meals each
./philo 1 800 200 200        # Single philosopher (will die)
```

## Key Concepts

- **Deadlock prevention**: Forks are always locked in ascending order to avoid
  circular wait conditions.
- **Death monitoring**: A dedicated monitoring loop checks each philosopher's
  time since last meal and terminates the simulation on starvation.
- **Thread-safe output**: A print mutex ensures log messages are not interleaved
  across threads.
- **Precision timing**: A busy-wait `ft_usleep` with `usleep(100)` polling
  provides sub-millisecond accuracy for action durations.
