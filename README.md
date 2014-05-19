Solitaire
=========

Final project for CIS 190 at UPenn, by David Xu and Connie Yuan

The game is played through a command-line interface.


Organization of the soltaire board
----------------------------------

```
 _____  _____              _____  _____  _____  _____
|Stock||Talon|            |     ||     ||     ||     |
|     ||     |            |     || Foundation ||     |
|     ||     |            |     ||     ||     ||     |
 -----  -----              -----  -----  -----  -----

 _____  _____  _____  _____  _____  _____  _____
|     ||     ||     ||     ||     ||     ||     |
|     ||     Tableau Piles ||     ||     ||     |
|     ||     ||     ||     ||     ||     ||     |
 -----  -----  -----  -----  -----  -----  -----
```


Interface
---------

```
$> ./solitaire
Please enter the size of the talon (1 or 3): 1

STOCK ---     --- --- --- ---

 9♠ --- --- --- --- --- ---
     J♠ --- --- --- --- ---
         J♥ --- --- --- ---
            10♥ --- --- ---
                 9♣ --- ---
                     7♥ ---
                         K♦


Play Options:
(1) Deal new upturned card(s)
(2) Move card(s)
(3) Get a hint
(4) Restart the game

Select an option:
```