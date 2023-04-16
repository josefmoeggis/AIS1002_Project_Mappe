## AIS1002_Mappe Josef Møgster

Dette blir dessverre skrevet i siste liten ettersom jeg ikke får prosjektet til å compile disse siste 10 minuttene
Laster opp en branch som kan kjøre (main) med det som er helt basic og en med den nyeste koden (sidebranch)

Målet her er å få en 3D-graf som viser løftkraften på flyet

### Det som har blitt gjort

* Laget klasse for flyene - startet som en underklasse av mesh men gjorde det om til å bare inkludere mesh
* Klasse for graf med grid
* UI som jeg ikke fikk ferdig implementert

### Ting som må forbedres

- Alle klassene skal få flere funksjoner
- Skal basere GUI.hpp på pointers etter hvert

### Det som skal legges til

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