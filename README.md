# README

This is the final project for Evan Inrig and Jason Press (and more group members in the future) for CSCI 570: Analysis of Algorithms. This project is making a sequence alignment algorithm. 

# Structure

All materials given are located in `materials/`, including the project description and testing files.

## Input Generator

This is a helper to generate the inputs. The main function is `parse_file(path)`, which parses a path and returns a `vector<string> {s1, s2}` on success. I'd imagine it's better in its own file than duplicated across many files.
