import os
import re

base_class_name = "Challenge"  # Name of the abstract base class
directory = "./"  # Directory to scan for source files

# Regex pattern to find derived classes
pattern = re.compile(r'class (\w+)\s*:\s*public\s*' + base_class_name)
print("Current working directory:", os.getcwd())

# Store found header files to include and registration macros to write
header_files = []
macros = []

# Open a file to write registration code
with open("generated_registration.cpp", "w") as outfile:
    outfile.write('#include "Registry.h"\n')  # Make sure Registry.h is correctly located
    
    # Collect all the derived classes from .cpp and .h files
    for root, dirs, files in os.walk(directory):
        for file in files:
            if file.endswith('.cpp') or file.endswith('.h'):
                with open(os.path.join(root, file), "r") as f:
                    content = f.read()
                    matches = pattern.findall(content)
                    for match in matches:
                        # Collect the header files for each match
                        header_files.append(f'"{match}.h"')
                        # Collect the registration macros for each match
                        macros.append(f'\tREGISTER_DERIVED_CLASS({match}, "Inputs/{match}_input.txt");')
    
    # First write the include files
    for header in header_files:
        outfile.write(f'#include {header};\n')

    outfile.write(f'\n');
    outfile.write('void registerClasses() {\n')
    # Then write the registration macros
    for macro in macros:
        outfile.write(f'{macro}\n')
    outfile.write('\n}\n')

print("Generated registration code.")
