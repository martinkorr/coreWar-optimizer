import subprocess
import os

def simulation (warrior_file, benchmark_file):
    """
    
    """
    command = ["./pmars/src/pmars", "-b", "-r", "10000", warrior_file, benchmark_file]
    try:
        result = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, check=True)
        return result.stdout.decode('utf-8')  # Decode bytes to string
    except subprocess.CalledProcessError as e:
        raise RuntimeError(f"pMARS failed with error: {e.stderr.decode('utf-8')}")  # Decode stderr to string
    except Exception as e:
        raise RuntimeError(f"Error running battle simulation: {e}")

def save_results(results, output_file):
    try:
        with open(output_file, "a") as file:
            file.write(results + "\n")
    except Exception as e:
        print(f"Error writing results to file: {e}")


def main():
    warriorDir = "warriors/"
    benchmarkDir = "warriors/benchmark/"
    outputDir = "output"
    
    if not os.path.exists(benchmarkDir):
        print(f"Benchmark directory {benchmarkDir} does not exist")
        return
    
    warriorFilename = input("Enter the name of the Warrior to benchmark: ")
    if not warriorFilename.endswith(".red"):
        warriorFilename += ".red"

    warriorFile = os.path.join(warriorDir, warriorFilename)

    if not os.path.exists(warriorFile):
        print(f"Warrior file {warriorFile} does not exist")
        return

    outputFilename = input ("Enter the name of the output file: ")
    if not outputFilename.endswith(".txt"):
        outputFilename += ".txt"

    os.makedirs(outputDir, exist_ok=True)
    outputPath = os.path.join(outputDir, outputFilename)
    
    for file in os.listdir(benchmarkDir):
        if file.endswith(".RED"):
            benchmarkFile = os.path.join(benchmarkDir, file)
            print(f"Running simulation for {file}")
            try:
                output = simulation(warriorFile, benchmarkFile)
                save_results(output, outputPath)
            except RuntimeError as e:
                print(f"Error: {e}")

if __name__ == "__main__":
    main()