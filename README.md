# CoreWar

A programming game introduced by A. K. Dewdney and D. G. Jones in 1984 where two or more so called "warriors" are put against each other to gain control of a virtual computer. The warriors core is based on an assembly language called Redcode.

## pMARS

The code provides users with the ability to create optimal Core War agents, also known as warriors, for pMARS.

In this process, warriors are generated randomly using a random generation function, with a maximum length of 100 opcodes. These opcodes represent the movements and instructions a warrior can use to gain control of a virtual computer.

Additionally, the randomly generated warriors are optimized using GAlib. To achieve the desired optimizations, the genomes/warriors are made to compete against so-called benchmark warriors. These benchmark warriors also serve to validate the individual Core War agents.

More detailed information can be found under the following links:
- Core-War manuel : https://corewar.co.uk/pmars/pmars_man.htm

- Core-War rules: https://en.wikipedia.org/wiki/Core_War

## Instructions

Before following the instructions below, clone the project into any desired directory using Git:

```bash
    git clone 
```

### Project structur

```bash
 .
├── build/                       # Compiled files
├── include/                     # Include files for GALib 
├── lib/                         # libGAlib.a libary for GALib
├── output/                      # Output from Benchmark tests 
├── pmars/                       # pMARS function
├── warriors/                    # Output for the warriors
    └ benchmark/                 # Benchmark folder include the benchmark warriors 
├── benchmark_test.py
├── main.cpp 
└── README.md
```

### Compile project
To compile the project, you need to navigate to the build folder:

```bash
    cd build/
```
Afterward, execute the following commands:

```bash
    cmake .. 
    make
```
After successfully executing the ```cmake ..``` command, the following message should appear in the terminal:

![Logo](https://i.imgur.com/GN60I0R.png)

If an error message appears indicating that Boost or BoostConfig could not be found, it suggests that the ```library libboost-all-dev``` is missing. In this case, please install it using the following command:

```bash
    sudo apt-get update
    sudo apt install libboost-all-dev
```

After installing the missing library, repeat the process by running the following commands:

```bash
    cmake .. 
    make
```

After successful compilation, the executable file will be created in the ```build/``` folder and can be run directly from there using the following command:

```bash
    ./corewar_optimizer
```

The optimizer will then start and create a ```random_warrior.red``` file in the ```warriors/``` folder, which contains a randomly generated warrior. 
However, before this happens, the number of threads must be defined. If no input is provided, the default setting of 16 threads will be used.

![Logo](https://i.imgur.com/8vLSpsq.png)

By default, only one benchmark file is used for optimizing the random_warrior.red, as the optimization process requires a significant amount of time. 
To increase the number of benchmark files, the following code in main.cpp must be modified, specifically by uncommenting the relevant lines:

![Logo](https://i.imgur.com/gnw6qEH.png)

Locate the section in main.cpp where the benchmark files are defined and uncomment the lines or add additional benchmark file paths as needed. 
This allows the optimizer to use more benchmark files for optimization.
However, keep in mind that increasing the number of benchmark files will significantly increase the optimization time. Proceed with caution and adjust the number of 
benchmark files based on the time you’re willing to allocate for the optimization process.

## Benchmark Test

To showcase a benchmark or comparison between the original randomly generated warrior and the optimized warrior, you can run the simple Python script ```benchmark_test.py```.
After executing the script, you will be prompted to input a warrior file. It's important to ensure that both random_warrior.red and best_warrior.red are located in the ```warriors/``` folder. 
The output, including the results, will be saved in .txt format within the ```output/``` folder.
The script executes the following command ```./pmars/src/pmars -b -r 10000 warrior_file benchmark_file```, pitting the warriors against the benchmark warriors in a direct battle over 10,000 rounds to assess their performance.

### Example

```bash
    python3 benchmark_test.py
```

```bash
    Enter the name of the Warrior to benchmark: random_warrior
    Enter the name of the output file: benchmark_randomWarrior
```
![Logo](https://i.imgur.com/Q8oc0rn.png)

# References

ANDERSEN, David G. The Garden: Evolving Warriors in Core Wars. 2001. [https://www.cs.unm.edu/~htasnim30/files/evolving-core-war.pdf](https://www.cs.unm.edu/~htasnim30/files/evolving-core-war.pdf)

SIDDIQUEE, MOHAMMAD ASHRAF; SURJADIDJAJA, VANESSA. Implementation of a Genetic Algorithm to Simulate the Evolution of CoreWar Warriors Based on Fitness Values. 2016. [https://www.cs.unm.edu/~siddiquee/pdfs/CASProject1.pdf](https://www.cs.unm.edu/~siddiquee/pdfs/CASProject1.pdf)
