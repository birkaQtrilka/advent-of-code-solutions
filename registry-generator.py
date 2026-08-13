import os
import re
from config_manager import load_config
import os
import sys

config = load_config()
active_year = config.get("selected_year")

base_class_name = "Challenge"      # Abstract base class
exercices_base_dir = os.path.join(".", "Exercices")

# 1. Check if the base Exercices directory exists
if not os.path.exists(exercices_base_dir):
    print(f"Error: The directory '{exercices_base_dir}' does not exist.")
    sys.exit(1)

# 2. Get a list of all folders inside ./Exercices/ (sorted alphabetically/numerically)
existing_folders = [f for f in os.listdir(exercices_base_dir) if os.path.isdir(os.path.join(exercices_base_dir, f))]
existing_folders.sort()

# 3. If there are no folders at all, stop the program
if not existing_folders:
    print(f"Error: No year folders found inside '{exercices_base_dir}'. Please create one first.")
    sys.exit(1)

# 4. If the active_year is invalid or doesn't exist, default to the first available folder
if str(active_year) not in existing_folders:
    print(f"Warning: Folder for year '{active_year}' not found. Defaulting to '{existing_folders[0]}'.")
    active_year = existing_folders[0]

# Now safely set the directory to scan
directory = os.path.join(exercices_base_dir, str(active_year))      
output_file = "generated_registration.cpp"

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
def extract_number(name: str):
    name = name[5:] # skipping year tag 'Ex_25_'
    match = re.search(r'\d+', name)
    return int(match.group()) if match else 0

# Sort classes numerically
sorted_classes = sorted(class_names, key=extract_number)

# Generate the output file
with open(output_file, "w", encoding="utf-8") as outfile:
    outfile.write('#include "Registry.h"\n\n')

    # Write includes
    for name in sorted_classes:
        outfile.write(f'#include "{os.path.join(directory, name)}.h"\n')

    outfile.write('\nvoid registerClasses() {\n')

    # Write registrations
    for name in sorted_classes:
        outfile.write(
            f'\tREGISTER_DERIVED_CLASS({name}, "Inputs/{name}_input.txt");\n'
        )

    outfile.write('}\n')

print("Generated registration code successfully.")
