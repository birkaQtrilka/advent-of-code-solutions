import os
import re

directory = './'

for root, dirs, files in os.walk(directory):
    for file in files:
        if file.startswith('25_'):
            path = os.path.join(root, file)
            with open(path, 'r') as f:
                content = f.read()
            new_content = re.sub(r'#include "Ex', '#include "25_Ex', content)
            with open(path, 'w') as f:
                f.write(new_content)
            print(f"Updated: {file}")
            # name = "25_" + file
            # new_path = os.path.join(root, name)
            # os.rename(old_path, new_path)