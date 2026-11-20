# README

This is the final project for Evan Inrig and Jason Press (and more group members in the future) for CSCI 570: Analysis of Algorithms. This project is making a sequence alignment algorithm. 

# Structure

All materials given are located in `materials/`, including the project description and testing files.

## Input Generator

This is a helper to generate the inputs. The main function is `parse_file(path)`, which parses a path and returns a `vector<string> {s1, s2}` on success. I'd imagine it's better in its own file than duplicated across many files.

# Context
 - DNA strand full of bases
 - Define matching as an alignment with no crossing pairs

 - similarity between strings is the minimum cost of an alignment between X and Y

# TO DO
- Make opt formula
    - for alignment, assign gap penalty for each gap, mismatch cost for each mismatch
    - defined as the minimum cost of an alignment between x1, xi and y1, yi

    1) xm, yn is el of M:
        OPT(m,n) = OPT(m-1,n-1) + alpha(xm, yn)
    2) xm is not matched:
        OPT(m,n) = OPT(m-1,n) + delta
    3) yn is not matched, then
        OPT(m, n) = OPT(m,n-1) + delta

    if the strings match:
    OPT(i,j) = min(
        OPT(i - 1, j - 1) + alpha(xi, yi),
        OPT(i - 1, j) + delta,
        OPT(i, j - 1) + delta
    )
    if not:
    OPT(i,j) = min(
        OPT(i - 1, j) + delta,
        OPT(i, j - 1) + delta
    )

