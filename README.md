## Othello

A simple othello engine in development written in C.

### Features
- kogge stone move generation
- magic bitboard move generation
- fast perft (bulk counting)

### Build
```
git clone https://github.com/ellxor/othello
cd othello
ninja -C build
./build/othello
```

### Results
```
Table size = 700416 bytes
Table init = 3700 clocks
 1:            4
 2:           12
 3:           56
 4:          244
 5:         1396
 6:         8200
 7:        55092
 8:       390216
 9:      3005288
10:     24571284
11:    212258800
12:   1939886636
13:  18429641748
14: 184042084512
(3.00 Gnps)
```
