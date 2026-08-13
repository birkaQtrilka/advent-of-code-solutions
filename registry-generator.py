import os
import re

base_class_name = "Challenge"      # Abstract base class
directory = "./Exercices"                  # Root directory to scan
output_file = "generated_registration.cpp"

# Regex to find derived classes
pattern = re.compile(
    rf'class\s+(\w+)\s*:\s*public\s+{base_class_name}'
)

print("Current working directory:", os.getcwd())

# Store unique class names
class_names = set()

# Walk through all source files
for root, dirs, files in os.walk(directory):
    for file in files:
        if file.endswith(('.cpp', '.h')):
            file_path = os.path.join(root, file)
            try:
                with open(file_path, "r", encoding="utf-8") as f:
                    content = f.read()
                    matches = pattern.findall(content)
                    for match in matches:
                        class_names.add(match)
            except UnicodeDecodeError:
                # Skip files with incompatible encoding
                pass

# Helper to extract numeric suffix (Ex_10 -> 10)
def extract_number(name):
    match = re.search(r'\d+', name)
    return int(match.group()) if match else 0

# Sort classes numerically
sorted_classes = sorted(class_names, key=extract_number)

# Generate the output file
with open(output_file, "w", encoding="utf-8") as outfile:
    outfile.write('#include "Registry.h"\n\n')

    # Write includes
    for name in sorted_classes:
        outfile.write(f'#include "./Exercices/{name}.h"\n')

    outfile.write('\nvoid registerClasses() {\n')

    # Write registrations
    for name in sorted_classes:
        outfile.write(
            f'\tREGISTER_DERIVED_CLASS({name}, "Inputs/{name}_input.txt");\n'
        )

    outfile.write('}\n')

print("Generated registration code successfully.")
