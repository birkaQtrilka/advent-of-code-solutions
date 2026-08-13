import os
import sys

def generate_files(year, number):
    # Extract the last two digits of the year (e.g., '2025' -> '25')
    # Using zfill(4) ensures that even if you type '5' it treats it like '0005' -> '05'
    year_str = str(year)
    last_two_digits = year_str[-2:]
    
    # Construct the filename
    filename = f"Ex_{last_two_digits}_{number}"
    
    # Define the directory path
    directory = os.path.join(".", "Exercices", year_str)
    
    # Create the directory if it does not exist
    os.makedirs(directory, exist_ok=True)
    
    # Define file paths
    h_file_path = os.path.join(directory, f"{filename}.h")
    cpp_file_path = os.path.join(directory, f"{filename}.cpp")
    
    # Template for the .h file
    # Note: double curly braces {{ and }} are used to escape the C++ braces in Python f-strings
    h_content = f"""#pragma once
#include "../Challenge.h"
#include <iostream>
#include <fstream>
#include <limits.h>
#include <vector>
#include <string>

class {filename} : public Challenge
{{
public:

\tvoid Run1(ifstream& input) override;
\tvoid Run2(ifstream& input) override;
}};
"""

    # Template for the .cpp file
    cpp_content = f"""#include "{filename}.h"

void {filename}::Run1(ifstream& input)
{{

}}

void {filename}::Run2(ifstream& input)
{{
  
}}
"""

    # Write the files
    with open(h_file_path, 'w') as h_file:
        h_file.write(h_content)
        
    with open(cpp_file_path, 'w') as cpp_file:
        cpp_file.write(cpp_content)

    print(f"Successfully created files:")
    print(f"  - {h_file_path}")
    print(f"  - {cpp_file_path}")

if __name__ == "__main__":
    # Check if the right number of arguments was passed
    if len(sys.argv) != 3:
        print("Usage: python generate.py <year> <number>")
        print("Example: python generate.py 2025 2")
        sys.exit(1)
        
    try:
        input_year = int(sys.argv[1])
        input_number = int(sys.argv[2])
    except ValueError:
        print("Error: Both year and number must be integers.")
        sys.exit(1)
        
    generate_files(input_year, input_number)