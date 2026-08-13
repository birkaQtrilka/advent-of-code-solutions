import os
import re


def fix_content(path):
    with open(path, 'r') as f:
      content = f.read()
      # new_content = re.sub(r'#include "25_Ex', '#include "Ex', content)
      new_content = re.sub(r'#include "Challenge.h"', '#include "../Challenge.h"', content)
      with open(path, 'w') as f:
          f.write(new_content)

def fix_name(path, root, file):
    name = re.sub(r'25_Ex', 'Ex_25', file)
    new_path = os.path.join(root, name)
    os.rename(path, new_path)

directory = './2025/'

for root, dirs, files in os.walk(directory):
    for file in files:
        # if file.startswith('25_'):
            path = os.path.join(root, file)
            # fix_name(path, root, file)
            fix_content(path)
            print(f"Updated: {file}")
            
