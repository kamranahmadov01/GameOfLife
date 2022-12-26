Game Of Life
============

Game of Life project in C

Description
===========

The Game of Life is, in reality, a cellular automaton defined in 1970 by
the English mathematician John Conway in order to try to solve a problem
raised by a mathematician, father of computer science, John Von Neumann.
It is not strictly speaking a game: it does not require the intervention
of a human player, except to fix the initial conditions of the game. It
consists of a universe in which live cells evolve according to rules
precise evolution.

Rules
=====

1.  Any live cell with fewer than two live neighbours dies, as if by
    underpopulation.

2.  Any live cell with two or three live neighbours lives on to the next
    generation.

3.  Any live cell with more than three live neighbours dies, as if by
    overpopulation.

4.  Any dead cell with exactly three live neighbours becomes a live
    cell, as if by reproduction.

The Game of Life rules were carefully chosen by Conway to satisfy three
simple criteria (Gardner, 1970):

-   There should be no initial pattern (configuration) for which there
    is a simple proof that the population can grow without limit.

-   There should be initial patterns that apparently do grow without
    limit.

-   There should be simple initial patterns that grow and change over
    some time, before coming to end in three possible ways: fading away
    completely (from overcrowding or becoming too sparse); settling into
    a stable pattern that remains unchanged thereafter, or entering an
    oscillating phase in which they repeat an endless cycle of two or
    more periods.
