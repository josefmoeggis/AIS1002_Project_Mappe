<!-- toc -->


### Candidate number: 
## AIS1002 Aerodynamic force simulation

Welcome to this visualization of aerodynamic forces acting upon an aircraft.
First and foremost, you must understand the concept of this model to learn to appreciate it.
The two forces being shown on the 3D graph are Lift and Drag, which, although they are dependent on the same parameters, don't
always correlate. Here you can simulate their characteristics to get a better understanding of how the forces are 
affected by **airspeed**, **angle of attack**, **altitude** and **temperature** at sea level.


### Table of Contents

- [Purpose](#purpose)
- [How it works](#how-it-works)
- [Coding](#coding)
- [Aerodynamics](#aerodynamics)
- [Future improvements](#future-improvements)
- [Sources](#sources)
  
#### Purpose
The main goal of this project was my personal growth of knowledge in the field of
object-oriented programming while creating an interactive visualization using the threepp library.
More specifically I decided that the project would have cool interface, but be a simple,
interactive aerodynamic force simulation. It would take in different physical parameters and plot
the calculated lift and drag onto a 3D graph to give better understanding of how these forces are
affected during flight.

#### How it works
The functionality of this model includes changing the aerodynamic parameters mentioned above in addition to
being able to switch between three preset aircraft: **Boeing 737-800**, **Airbus A320** and a little **Cessna 172**.
As they are preset with different constants based on the aircraft type there will be a slight variation in how these
forces work on each of them.
find
In addition, you have the option of switching between three different aircraft.

![Alt Text](resources/aerodynamics_animation.gif)

### Aerodynamics
**DISCLAIMER!** The aerodynamic characteristics in this model are not accurate but calculated estimations using standard
equations. To get accurate equations you would have to use a wind tunnels and full scale aircraft.

#### Lift
To calculate the lift force in a simple way, this equation can be used:


<img src="https://latex.codecogs.com/svg.image?\Large{\color{Blue}%26space;L%26space;=%26space;\frac{1}{2}C_{L}\rho%26space;S%26space;v^{2}}" />

In this case we already have a few parameters that may vary depending on other variables:

- *C<sub>L</sub>* - The lift coefficient, which is a combined coefficient to calculate lift for a certain aerodynamic
structure, is a simplification, as it can vary depending on other non-structural factors like angle of attack or *AoA*.
- *&rho;* - Is the air density, which varies depending on the *temperature* and the *altitude*.
- *S* - The wing area of the aircraft. As we don't take into account the extension of flaps and other controllablesurfaces,
this will just be a preset value for each aircraft.
- *v* - Seen in the equation, the velocity will be one of the main factors in increasing lift. We will only take into account
direct speed of airflow relative to the aircraft (see it as a wind tunnel).

As we add more elements to the formula, we increase the parameters that can be set. For the *AoA* there is no exact equation for
aircraft in general, but we can estimate formulas as aircraft will act similarly at different angles depending on the aircraft.

<img src ="https://latex.codecogs.com/svg.image?{\color{Emerald}%26space;C_{L}\left%26space;(%26space;\alpha%26space;%26space; \right%26space;)%26space;=%26space;\left\{%26space;C_{0}%26space;&plus;%26space;2\pi%26space;\cdot%26space;\alpha%26space;\right\},%26space;if%26space;-\alpha%26space;_{crit}\leqslant%26space;\alpha%26space;\leqslant%26space;\alpha%26space;_{crit}}" />
<img src ="https://latex.codecogs.com/svg.image?{\color{Emerald}%26space;C_{L}\left%26space;(%26space;\alpha%26space;%26space;\right%26space;)%26space;=C_{Lstall}-\left%26space;(%26space;k%26space;\cdot%26space;\left%26space;(%26space;\alpha%26space;-\alpha%26space;_{crit}%26space;\right%26space;)%26space;\right%26space;)^{2},%26space;if%26space;\alpha%26space;_{crit}%26space;<%26space;\alpha%26space;\leqslant%26space;\alpha%26space;_{stall}}" />
<img src ="https://latex.codecogs.com/svg.image?{\color{Emerald}%26space;C_{L}\left%26space;(%26space;\alpha%26space;%26space;\right%26space;)%26space;=-C_{Lstall}&plus;\left%26space;(%26space;k%26space;\cdot%26space;\left%26space;(%26space;\alpha%26space;-\alpha%26space;_{crit}%26space;\right%26space;)%26space;\right%26space;)^{2},%26space;if%26space;-\alpha%26space;_{stall}%26space;\leq%26space;\alpha%26space;<%26space;-\alpha%26space;_{crit}}" />

The values of all these coefficients and angles would all depend on the specific aircraft and therefore would be preset.

To find *&rho;* the calculations done by the international standard atmosphere

### Code

* Laget klasse for flyene - startet som en underklasse av mesh men gjorde det om til å bare inkludere mesh
* Klasse for graf med grid
* UI som jeg ikke fikk ferdig implementert

### What could be improved

- Alle klassene skal få flere funksjoner
- Skal basere GUI.hpp på pointers etter hvert

### Future additions

1. Logikken slik at det blir mulig å bytte mellom valgt fly
2. Evt. graf med drag
3. Kommunikasjonen mellom UI - control - objektene
4. Øke angrepsvinkel på flyet som også skal gi utslag på grafen
5. Kanskje få inn litt bevegelse av flyet med kraføkning

### List of points to finish
- [ ] Create angular movement
1. -[ ] Make new method for updating angle and returning value depending on elapsed time
2. -[ ] Inhibit set of new angle until reached previous angle


- [ ] Troubleshoot GUI
1. -[ ] Figure out why nothing shows on screen or it crashes
2. -[ ] Fix issues with images
3. -[ ] Try controlling the different states and getting a returned output in terminal
4. -[ ] Add the different states for different selected aircraft


### SOURCES

[//]: # (- https://www.grc.nasa.gov/WWW/K-12/FoilSim/Manual/fsim0007.htm)