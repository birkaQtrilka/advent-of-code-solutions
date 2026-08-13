import os
import sys

from config_manager import load_config, save_config

TEMPLATE_H_FILE = "template_h.txt"
TEMPLATE_CPP_FILE = "template_cpp.txt"


def ensure_templates_exist():
    """Creates default template files if they are missing so the script works out of the box."""
    if not os.path.exists(TEMPLATE_H_FILE):
        with open(TEMPLATE_H_FILE, 'w') as f:
            f.write("""#pragma once
#include "../Challenge.h"
#include <iostream>
#include <fstream>
#include <limits.h>
#include <vector>
#include <string>

class {filename} : public Challenge
{
public:

\tvoid Run1(ifstream& input) override;
\tvoid Run2(ifstream& input) override;
};
""")
    
    if not os.path.exists(TEMPLATE_CPP_FILE):
        with open(TEMPLATE_CPP_FILE, 'w') as f:
            f.write("""#include "{filename}.h"

void {filename}::Run1(ifstream& input)
{

}

void {filename}::Run2(ifstream& input)
{
  
}
""")

def main():
    args = sys.argv[1:]
    
    # Validate arguments length
    if len(args) == 0 or len(args) > 2:
        print("Usage:")
        print("  python generate.py <number>          -> Uses selected_year from config.json")
        print("  python generate.py <year> <number>   -> Updates config.json and uses the provided year")
        sys.exit(1)
        
    config = load_config()
    
    if len(args) == 1:
        # Only number is provided, use year from config
        try:
            number = int(args[0])
            year = config.get("selected_year")
            if year is None:
                print("Error: No 'selected_year' found in config.json. Please provide a year as the first argument.")
                sys.exit(1)
        except ValueError:
            print("Error: Number must be an integer.")
            sys.exit(1)
    else:
        # Both year and number are provided
        try:
            year = int(args[0])
            number = int(args[1])
            
            # Update and save the config file with the newly provided year
            config["selected_year"] = year
            save_config(config)
            print(f"Updated config.json selected_year to {year}.")
        except ValueError:
            print("Error: Both Year and Number must be integers.")
            sys.exit(1)
            
    # Ensure template text files exist before attempting to read them
    ensure_templates_exist()
    
    # Read templates
    with open(TEMPLATE_H_FILE, 'r') as f:
        h_template = f.read()
    with open(TEMPLATE_CPP_FILE, 'r') as f:
        cpp_template = f.read()
        
    # Generate the filename and paths
    year_str = str(year)
    last_two_digits = year_str[-2:]
    filename = f"Ex_{last_two_digits}_{number}"
    
    directory = os.path.join(".", "Exercices", year_str)
    os.makedirs(directory, exist_ok=True)
    
    h_file_path = os.path.join(directory, f"{filename}.h")
    cpp_file_path = os.path.join(directory, f"{filename}.cpp")
    
    # Replace {filename} marker with the actual filename. 
    # We use .replace() instead of Python's standard string formatting so that 
    # normal C++ curly braces in your templates don't cause format errors.
    h_content = h_template.replace("{filename}", filename)
    cpp_content = cpp_template.replace("{filename}", filename)
    
    # Write the contents to the files
    with open(h_file_path, 'w') as h_file:
        h_file.write(h_content)
        
    with open(cpp_file_path, 'w') as cpp_file:
        cpp_file.write(cpp_content)

    print(f"Successfully generated Challenge files for Year {year}:")
    print(f"  - {h_file_path}")
    print(f"  - {cpp_file_path}")

if __name__ == "__main__":
    main()