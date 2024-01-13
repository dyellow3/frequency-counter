# Word Frequency Counter

A simple C program counts the frequency of words in a given text file using two different approaches: a naive solution and a hash-based solution.

## Overview

The project provides two solutions for counting word frequencies:

1. **Naive Solution:** Linear scan of the input file, not efficient for large datasets.
2. **Hash Solution:** Utilizes a hash function and hash table for faster word frequency counting.

The goal of this project is to show the extreme difference in run times between the two solutions.

Feel free to play around with the Hash Function to see if you can get better run times!

## Features

- Efficient word frequency counting.
- Options to choose between naive, hash, or both solutions.
- Detailed timing and collision statistics.
- Supports dynamic limit on the most frequent words to display.

## How to Use

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/your-username/word-frequency-counter.git

2. **Compile the Code:**
   ```bash
   ./build.sh
   ```
   Note: The build.sh file is using [clang](https://clang.llvm.org/) to compile, feel free to use the compiler of your choice.

3. **Run the Program:**
   ```bash
   ./frequency_counter your_input_file.txt
   ```
   There are three input files included in the repo: fiftyThousand, twentyThousand, oneHundredTwentyThousand.
   The file names correspond to the lines in each of the files.  
   Each file is text taken from the work of Shakespeare. The oneHundredTwentyThousand is the entirety of Shakespeare work.  
