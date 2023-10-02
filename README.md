# Bubble Blast Game

**Bubble Blast** is an exciting matrix-based game where the objective is to make all the bubbles burst with the least possible moves.

## Introduction
The game requires a player to strategically choose a bubble and inflate it. Once a bubble reaches its threshold, it will explode and cause adjacent bubbles to inflate. The goal is to burst all the bubbles in the matrix.

## Features
1. Dynamic matrix generation.
2. Random placement and initial state of bubbles.
3. Propagation logic when a bubble bursts.
4. Minimal move calculation using an algorithm.
5. User-friendly interface to play the game.

## How to Play

1. The game consists of a 5x6 matrix (5 rows and 6 columns).
2. Bubbles can be in one of three states:
   - `1`: About to explode.
   - `2`: Half inflated.
   - `3`: Deflated.
3. On each move, a player selects a row and column of the bubble they wish to inflate.
4. If a bubble is in state `1` and is chosen, it will explode and cause adjacent bubbles to inflate by one state.
5. The explosion propagates up, down, left, and right.
6. The game ends when there are no more bubbles left or when the player runs out of moves.

## Compilation

To compile the program, you need a C compiler like GCC. Run the following command:
gcc bubble_blast.c -o bubble_blast

Then, to play the game:
./bubble_blast


## Functions

- `stampaIntroduzione()`: Prints the introduction and rules of the game.
- `creaMatrice()`: Initializes the game matrix.
- `popolaMatrice()`: Populates the game matrix with a random number and state of bubbles.
- `copiaMatrice()`: Creates a copy of the game matrix for the resolution algorithm.
- `algoritmo()`: Calculates the minimum moves required to win the game.
- `cambiaStato()`: Updates the state of the selected bubble.
- `stampaMatrice()`: Prints the current state of the game matrix.
- `controllaMatrice()`: Checks if there are any bubbles left in the matrix.
- `esitoPartita()`: Prints the result of the game.
- `esplosione()`: Handles the explosion of a bubble and the propagation logic.
- `propagazioneSu()`, `propagazioneGiu()`, `propagazioneDx()`, `propagazioneSx()`: Handle the propagation in the respective directions.

## Contribution

Feel free to fork the repository, make your changes and create a pull request. Let's make this game even more fun together!
