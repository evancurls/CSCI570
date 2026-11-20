# README

This is the final project for Evan Inrig and Jason Press (and more group members in the future) for CSCI 570: Analysis of Algorithms. This project is making a sequence alignment algorithm. 

# Structure

All materials given are located in `materials/`, including the project description and testing files.

Because we're only allowed to submit `basic.cpp` and `efficient.cpp`, the code from all auxiliary files gets copied over into both `basic.cpp` and `efficient.cpp`. However, keeping versions sucks, so it's easier to have the auxiliary files serve as the "master copy" and `C-c C-v` the code from them into the tops of the submission files.

If I cared harder, I could automate it with some bash with something like

```bash
touch basic.cpp
cat helper.cpp >> basic.cpp
cat basic_algo.cpp >> basic.cpp
# same for efficient.cpp
```

but that sounds like a lot of work.

# Context
 - DNA strand full of bases
 - Define matching as an alignment with no crossing pairs

 - similarity between strings is the minimum cost of an alignment between X and Y

# TO DO

- `efficient.cpp`
- The plots for both basic and efficient to do the paper/summary

