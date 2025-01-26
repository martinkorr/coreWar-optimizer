#include <iostream>
#include <sstream>
#include <fstream>

#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <ga/ga.h>
#include <omp.h>

#define CORESIZE 8000
#define MAX_WARRIOR_LENGTH 100

#define DEFAULT_THREADS 16

class Warrior {
private:
    std::vector<std::string> instructions = {"mov", "add", "sub", "jmp", "djn", 
                                                "cmp", "spl", "slt", "nop", "dat", "mul", 
                                                "div", "mod", "seq", "sne", "ldp", "stp"
                                            }; 
    std::vector<std::string> adressing = {"#", "$", "@", "<", ">", "*", "{", "}"}; // Genome: addressing modes
    const int range = CORESIZE; // Redcode: memory range

public:
    Warrior() {
        std::srand(std::time(nullptr));   
    }

    std::vector<std::string> generateRandomWarrior(const int length ){
        std::vector<std::string> warrior;
        for (int i = 0; i < length; i++) {
            std::string opcode = instructions[rand() % instructions.size()];
            std::string addressA = adressing[rand() % adressing.size()];
            std::string addressB = adressing[rand() % adressing.size()];
            int parameterA = rand() % range;
            int parameterB = rand() % range;
            warrior.push_back(opcode + " " + addressA + std::to_string(parameterA) + ", " + addressB + std::to_string(parameterB));
        }
       
        return warrior;
    }

    void writeToFile(const std::vector<std::string>& warrior, const std::string& filename) {
        std::ofstream outFile(filename);
        if (outFile.is_open()) {
            outFile << ";redcode\n";
            outFile << ";name Random Warrior\n";
            outFile << ";author Robert Martinko\n";
            outFile << ";assert CORESIZE == 8000\n";
            outFile << "\n";
            for(const auto& line : warrior) {
                outFile << line << std::endl;
            }
            outFile << "end";
            outFile.close();
        } else {
            std::cerr << "Error: Could not open file " << filename << std::endl;
        }
    }

    std::vector<std::string> readFromFile(const std::string &filename){
        std::vector<std::string> warrior;
        std::ifstream inFile(filename);

        if(inFile.is_open()){
            std::string line;
            while(std::getline(inFile, line)){
                if (line.empty() || line[0] == ';') continue;
                warrior.push_back(line);
            }
            
            inFile.close();
        } else {
            std::cerr << "Error: Could not open file " << filename << std::endl;
        }
        return warrior;
    }
};

    float evaluateFitness(GAGenome& g) {
        GA1DArrayGenome<std::string>& genome = (GA1DArrayGenome<std::string>&)g;
        Warrior warriorGenerator;
        std::vector<std::string> warrior;

        for (int i = 0; i < genome.length(); ++i) {
            warrior.push_back(genome.gene(i));
        }
        
        warriorGenerator.writeToFile(warrior, "../warriors/current_warrior.red");

        // Liste der Benchmark-Warriors
        std::vector<std::pair<std::string, double>> benchmarkFiles = {
            // {"../warriors/benchmark/BLUEFUNK.RED", 1.5},
            // {"../warriors/benchmark/CANNON.RED", 1.0},
            // {"../warriors/benchmark/FSTORM.RED", 1.0},
            // {"../warriors/benchmark/IRONGATE.RED", 2.0},
            // {"../warriors/benchmark/MARCIA13.RED", 2.0},
            // {"../warriors/benchmark/NOBODY.RED", 1.5},
            // {"../warriors/benchmark/PAPERONE.RED", 1.0},
            // {"../warriors/benchmark/PSWING.RED",1.0},
            // {"../warriors/benchmark/RAVE.RED", 1.5},
            // {"../warriors/benchmark/THERMITE.RED", 3.0},
            // {"../warriors/benchmark/TIME.RED", 1.0},
            {"../warriors/benchmark/TORNADO.RED", 3.0}
            // Weitere Benchmark-Warriors hinzufügen
        };

        double totalFitness = 0.0;

        #pragma omp parallel for reduction(+:totalFitness)
        for (const auto& benchmarkFile : benchmarkFiles) {
            // pMARS ausführen
            std::string command = "../pmars/src/pmars -b -r 10000 ../warriors/current_warrior.red " + benchmarkFile.first +  "> results.txt";
            int result = std::system(command.c_str());
            if (result != 0) {
                std::cerr << "Error: pMARS execution failed for " << benchmarkFile.first << "\n";
                continue;
            }

            // Ergebnisse analysieren
            std::ifstream resultsFile("results.txt");
            if (!resultsFile.is_open()) {
                std::cerr << "Error: Could not open results.txt for " << benchmarkFile.first << "\n";
                continue;
            }

            double benchmarkFitness = 0.0;
            std::string line;
            while (std::getline(resultsFile, line)) {
                if(line.find("Results:") != std::string::npos){
                    int wins, ties, losses;
                    std::sscanf(line.c_str(), "Results: %d %d %d", &wins, &ties, &losses);
                    totalFitness = wins * 3.0 + ties * 1.0;
                    break;
                }
            }
            resultsFile.close();

            benchmarkFitness *= benchmarkFile.second;
            totalFitness += benchmarkFitness;
        }

        return totalFitness;
    }


    void genomeInitializer(GAGenome& g) {
        GA1DArrayGenome<std::string>& genome = (GA1DArrayGenome<std::string>&)g;
        Warrior warrior;

        std::vector<std::string> baseWarrior = warrior.readFromFile("../warriors/random_warrior.red");
        
        if(baseWarrior.empty()){
            std::cerr << "Error: Base warrior is too short. Exiting..." << std::endl;
        }

        #pragma omp parallel for
        for (int i = 0; i < genome.length(); ++i) {
            genome.gene(i, baseWarrior[i]);
            // std::cout << genome.gene(i, baseWarrior[i]) << std::endl;
        }
    }



int main() {
    Warrior warrior;
    GA1DArrayGenome<std::string> genome(MAX_WARRIOR_LENGTH);

    // GA Hyper parameters
    const int populationSize = 100;
    const int nGenerations = 50;
    const float pCrossover = 0.8;
    const float pMutation = 0.5;

    int numThreads = 16;
    std::cout << "How many Threads should be used: ";
    std::string input;
    std::getline(std::cin, input);
    if (!input.empty()) {
        numThreads = std::stoi(input);
    }
    omp_set_num_threads(numThreads);
    std::cout << "Threads been used right now: " << numThreads << std::endl;

    if (!std::ifstream("../warriors/random_warrior.red")) {
        std::vector<std::string> randomWarrior = warrior.generateRandomWarrior(MAX_WARRIOR_LENGTH);
        warrior.writeToFile(randomWarrior, "../warriors/random_warrior.red");
        std::cout << "File created!" << std::endl;
        std::cout << "Optimizing random warrior started..." << std::endl;
    } else {
        std::cout << "File created!" << std::endl;      
        std::cout << "Optimizing random warrior started..." << std::endl;
    }


    genome.evaluator(evaluateFitness);
    genome.initializer(genomeInitializer);

    
    GASimpleGA ga(genome);
    ga.populationSize(populationSize);
    ga.nGenerations(nGenerations);
    ga.pMutation(pMutation);
    ga.pCrossover(pCrossover);

    // Selector Methoden
    ga.selector(GATournamentSelector());
    // ga.selector(GARouletteWheelSelector());
    // ga.selector(GARankSelector());

    ga.evolve();

    // // Log-data after every evolution
    // for (int generation = 0; generation < nGenerations; ++generation) {
    //     ga.step(); // Führt eine Generation aus

    //     // Loggen der Statistiken nach jeder Generation
    //     std::ofstream logFile("fitness_log.txt", std::ios::app);
    //     if (logFile.is_open()) {
    //         logFile << "Final Statistics\n";
    //         logFile << "Total Generations: " << ga.statistics().generation() << "\n";
    //         logFile << "Best Fitness: " << ga.statistics().bestIndividual().score() << "\n";
    //         logFile << "Avg Fitness: " << ga.statistics().Mean << "\n"; // Korrektur hier
    //         logFile.close();
    //     } else {
    //         std::cerr << "Error: Could not open fitness_log.txt for writing.\n";
    //     }
    // }

    GA1DArrayGenome<std::string> &bestGenome = (GA1DArrayGenome<std::string>&)ga.statistics().bestIndividual();
    std::vector<std::string> bestWarrior;

    for(int i=0; i < bestGenome.length(); i++) {
        bestWarrior.push_back(bestGenome.gene(i));
    }

    warrior.writeToFile(bestWarrior, "../warriors/best_warrior.red");
    
    std::cout << "Best Warrior saved to best_warrior.red" << std::endl;
    return 0;
}