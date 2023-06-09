<div align="center">

  <img src="img/PHILOSOPHERS.png" alt="logo" width="1000" height="auto" />
 
  <p>
   Solving the famous 'dining philosophers' problem using threads and mutexes.     </p>
  
</div>

# About the project

A project made in accordance with the philosophers project which is part of the Codam Core Curriculum. It is a version of the [dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem). One or more philosophers sit at a round table. There is a large bowl of spaghetti in the middle of the table. Philosophers need two forks to eat the spaghetti. There are as many forks as philosophers. The challenge is to write a program that lets the philosophers dine without starving. Each philosopher is a **thread** and the availability of each fork is protected by a **mutex**.




# Getting started

Start by cloning the repository:
```c
git clone https://github.com/fkoolhoven/philosophers.git
```
Go into the philo directory and compile by using make:
```c
make
```


# Usage

```c
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]
```
- number_of_philosophers: the number of philosophers and also the number of forks.
- time_to_die (in milliseconds): if a philosopher didn’t start eating time_to_die milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
- time_to_eat (in milliseconds): the time it takes for a philosopher to eat. During that time, they will need to hold two forks.
- time_to_sleep (in milliseconds): the time a philosopher will spend sleeping.
- number_of_times_each_philosopher_must_eat (optional argument): if all philosophers have eaten at least number_of_times_each_philosopher_must_eat times, the simulation stops. If not specified, the simulation stops when a philosopher dies.

For example:
```c
./philo 6 800 200 200 3 
```
will let 6 philosophers eat 3 times.

Or:
```c
./philo 4 310 200 200
```
will let the simulation run until 1 philosopher starves.

Example output of 
```c
./philo 4 2000 350 800 5
```
Any state change of a philosopher is formatted as follows:
[current timestamp in milliseconds] [philosopher number] [state]

![](https://github.com/fkoolhoven/philosophers/blob/master/img/gif3.gif)

# Important learnings

1. Learned to create and join threads.
2. Learned about what causes race conditions.
3. Learned how to prevent race conditions using mutexes.
4. Additionally I worked on making the output as easy to read as possible, adding colors and appropriate (error) messages.

# Contact

See my profile page for ways to contact me!
