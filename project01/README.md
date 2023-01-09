# Introduction :

Monte Carlo simulation is used to determine the range of outcomes for a series of parameters, each of which has a probability distribution showing how likely each option is to happen. In this project, you will take a scenario and develop a Monte Carlo simulation of it, determining how likely a particular output is to happen.

Clearly, this is very parallelizable -- it is the same computation being run on many permutations of the input parameters. You will run this with OpenMP, testing it on different numbers of threads (1, 2, and 4, but more are OK).

## The Scenario :
A kid with a snowball is waiting for something to throw it at. (Hey you, get off my lawn!) Suddenly, a truck drives by. When the truck is even with the kid, the kid throws the snowball.

The origin for this coordinate system is at the kid's feet. The X direction goes to the right. The Y directiomn goes deeper into the scene.

But, it is hard to estimate when the truck is exactly even with the thrower. And, even though the a truck driving through snow should be going about 20 feet per second, it is hard to estimate the speed of the truck. And, it is hard for a thrower to get the throw velocity and the throw angle consistent from one time to the next.

Ignore the height of the snowball. It's a really tall truck. We are assuming that the only thing that matters are the horizontal positions of the truck and the snowball.

## Use these as the ranges of the input parameters when you choose random parameter values:
Variable	Description	Minimum	Maximum

tx	Truck X starting location in feet	-10.	10.

txv	Truck X velocity in feet/second	10.	30.

ty	Truck Y location in feet	45.	55.

sv	Snowball overall velocity in feet/second	10.	30.

theta	Snowball horizontal launch angle in degrees	10.	90.

I recommend #define'ing or const float'ing all of these minima and maxima at the top of your progra
