# Sampling Large Graphs Using Monte Carlo Methods
*Submitted in partial fulfilment of the Requirements for the award of the Degree of Bachelor of Technology in Computer Science & Engineering by
K. Hitesh Ram (12003344)*

## Introduction
The Project is based on Monte Carlo experiments which are a broad class of computational algorithms that rely on repeated random sampling to obtain numerical results they are often used in physical and mathematical problems and are most useful when it is difficult or impossible to obtain a closed-form expression, or infeasible to apply deterministic algorithm. Monte Carlo methods are mainly used in three distinct problem classes which are optimisation, numerical integration and generation of draws from a probability distribution.

As part of our project we Implemented applications of Monte Carlo methods with parallelization using OMP and MPI and PThread mechanisms, where we determined the temperature at a given point on a 2D plate, performed Integrations and implemented PRNG using GSL Libraries, Implemented Tree Search and Particle Transport is also performed using Monte Carlo Methods.

### Aim
To Implement Monte Carlo Methods with Parallelization using OpenMP and MPI which includes pseudo random number generators with GSL, Monte Carlo Markov Chain and implementation of practical applications like Monte Carlo integration, determination of temperature on 2D plate and simulation of neutron transport.

### Objectives
- Learn about Monte Carlo methods.
- Study Monte Carlo Markov Chains.
- Implement Parallel methods on practical applications of Monte Carlo Methods.
- Experiment with the generation of random numbers using PRNG.
- Understand and apply the GNU Scientific Library.

## Project Overview
A Monte Carlo method is an algorithm which solves a problem through the use of statistical sampling. The name is derived from the resort city in Monaco, famous for its games of chance. While early work in this field began in the nineteenth century, the first important use of Monte Carlo methods came into picture during the atomic bomb development during World War I.

The Monte Carlo method is the only practical way to evaluate integrals of arbitrary functions in six or more dimensions. It has many other uses, including predicting the future level of the Dow Jones Industrial Average, solving partial differential equations, sharpening satellite images, modelling cell populations, and finding approximate solutions to NP-hard problems in polynomial time.

### Temperature inside a 2D Plate
Imagine a very thin plate of homogeneous material. We wish to compute the steady-state temperature at a particular point in the plate. The top and the bottom of the plate are insulated, and the temperature at any point is solely determined by the temperatures surrounding it, except for the temperatures at the edges of the plate, which are fixed.
In this case the temperature at a point is the average of the temperatures of the points above it, below it, to its right. and to its left (which we can think of as "north","south", "east," and "west").We can use a Monte Carlo technique to find the temperature at a particular point S. We compute the temperature of S by randomly choosing one of the four neighbours and adding ilS temperature to an accumulator. After we have sampled a random neighbour’s temperature n times, we divide the sum by n to yield the temperature of S.

### Caluculating Integration using Monte Carlo Method  
It is a technique for numerical integration using random numbers. It is a particular Monte Carlo method that numerically computes a definite integral. Monte Carlo randomly chooses points at which the integrand is evaluated. This method is particularly useful for higher dimensional integrals. There are different methods to perform a Monte Carlo Integration, such as uniform sampling, stratified sampling and importance sampling. We applied the method of uniform sampling by taking uniform samples in the given limits.

### Stratified Sampling Method
In statistics, stratified sampling is a method of sampling from a population. In statistical surveys, when subpopulations within an overall population vary, it is advantageous to sample each subpopulation (stratum) independently. Stratification is the process of dividing members of the population into homogeneous subgroups before sampling. The strata should be mutually exclusive: every element in the population must be assigned to only one stratum. The strata should also be collectively exhaustive: no population element can be excluded. Then simple random sampling or systematic sampling is applied within each stratum. This often improves the representativeness of the sample by reducing sampling error. It can produce a weighted mean that has less variability than the arithmetic mean of a simple random sample of the population. In computational statistics, stratified sampling is a method of variance reduction when Monte Carlo methods are used to estimate population statistics from a known population.

### Deterministic Simpson's Rule 
In numerical analysis, Simpson's rule is a method for numerical integration, the numerical approximation of definite integrals, The method is credited to the mathematician Thomas Simpson (1710–1761) of Leicestershire, England. Kepler used similar formulas over 100 years prior. Initially a points will be selected in the graph and substituted in the function and the value is obtained the points are substituted in the Simpsons rule and the average is obtained.

#### <a href="https://github.com/hiteshram/Sampling-Large-Graphs-Using-Monte-Carlo-Methods/blob/master/pp_documentation.pdf" target="_blank">Results and Source code</a> | <a href="https://github.com/hiteshram/Sampling-Large-Graphs-Using-Monte-Carlo-Methods/blob/master/performance_evaluation.pdf" target="_blank"> Performance Report </a>
