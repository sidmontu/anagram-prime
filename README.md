# ANAGRAM CHECKER

Inspired from the Reddit thread: https://www.reddit.com/r/math/comments/6hb0xk/clever_algorithm_to_determine_whether_or_not_two/

## IDEA
Proposed Algorithm to find if two input words are anagrams: Map each of the 26 english characters to a unique prime number. Then calculate the product of the string. Two strings are anagrams if and only if their products are the same.

Current best ways of doing the above, in order of popularity/performance:

1) Count frequency of each letter in each word, and then simply compare. If the strings are anagrams, the frequency bins will be identical.
2) Sort letters in each word. The resultant strings of each word will be exact. [NOT Implemented in this project]

The proposed algorithm is arguably slower, and also susceptible to integer overflow. Will require 128-bit integer arithmetic at least to guarantee all words can be supported [Source](https://www.reddit.com/r/math/comments/6hb0xk/clever_algorithm_to_determine_whether_or_not_two/dix8409/).

But the following optimization might help practical use-case: Map primes efficiently to each letter by frequency of occurrence in the english language.. example, 'e' is the most frequently found alphabet in text, so map 'e' to the smallest prime number, i.e. 'e' = 2.

## RUNNING/COMPILING

You need PAPI library installed for performance profiling. The Makefile is very hacky, so you might have to edit that too, depending on your unix environment. Tested on Ubuntu 16.04 with PAPI 5.5.1.

Type `make`, then run `./anagram_checker <word1> <word2>`
e.g. `./anagram_checker hello olleh`

## TO-DO

1) Some sort of dictionary run to profile performance with increasing/decreasing word lengths?
2) Sorting algorithm described above.
