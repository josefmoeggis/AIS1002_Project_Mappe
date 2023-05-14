### Candidate number: 
## AIS1002_Mappe Josef Møgster

Welcome to this visualization of aerodynamic forces acting on an aircraft.
First and foremost, you must understand the concept of this model to learn to appreciate it.
The two forces being simulated on the 3D graph are Lift and Drag, which, although they often are dependant
on the same variables can have varying characteristics.

#### Goal
The main goal of this project was my personal growth of knowledge in the field of
objectoriented programming while creating an interactive visualization using the threepp library.
More specifically I decided that the project would be a fancy looking, but simple,
interactive aerodynamic force simulation. It would take in different physical parameters and plot
the calculated lift and drag onto a 3D graph to give better understanding of how these forces are
affected.

#### Planning Phase
It took some time before I landed on this idea as I fist wanted to see what was possible to
using the threepp library. As I discovered you could do pretty much anything as long as you had time,
I landed on this idea considering it was quite different from most other projects, which were mainly games.
In addition, this project, although not useful or accurate enough for real world simulations, seemed
like something on the more educational side.

### What has been added

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

- https://www.grc.nasa.gov/WWW/K-12/FoilSim/Manual/fsim0007.htm