# 42-Filler
Simple 'AI' bot for 42-Filler game written in C

Compilation:
```
git clone https://github.com/rearming/42-Filler
cd 42-Filler
make
```
To run filler_vm you must have Ruby installed.
Notice, that other filler players (located in resources/players) were compiled on Mac OS X, so it is impossible to run them on Linux.

Usage (Mac OS):
```
cd resources
./filler_vm -f maps/map*.txt -p1 ../sleonard.filler -p2 players/*.filler
```
Usage (Linux):
```
./filler_vm -f maps/map*.txt -p1 ../sleonard.filler -p2 ../sleonard.filler
```

If you want to try it with my graphical visualizer, clone it from [here](https://github.com/rearming/42-filler-graphic-visualizer).
Than simply redirect input of game to it:
```
./filler_vm -f maps/map*.txt -p1 ../sleonard.filler -p2 ../sleonard.filler | python3.7 visualizer.py
```
Example of visualization:
![Image alt](https://github.com/rearming/42-filler-graphic-visualizer/raw/master/screenshots/game2.png)

Hope you enjoy!
