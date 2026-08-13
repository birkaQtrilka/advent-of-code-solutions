Build only: Ctrl+Shift+B (or Cmd+Shift+B on Mac)

Build and run: Ctrl+Shift+P > "Run Task" > "Build and Run"

Debug: F5 (will build first if preLaunchTask is set)

Run without debugging: Ctrl+F5

# MyConfig

## testFile <filename: str>
File to read the input from. For current running exercise

## drawMode <draw: bool>
Inform exercise that it should draw. Only works if I implemented any drawing

# Registry-config
-selected year: the current year exercises are being added to

## addEx

Generates boilerplate `.cpp` and `.h` files for exercises in `./Exercices/<year>/`.

### Usage

**Specify year and number:**
```bash
python addEx.py 2025 2
```
Creates `./Exercices/2025/Ex_25_2.cpp` and `.h`. Updates `config.json` to set `selected_year` to 2025.

**Specify number only:**
```bash
python addEx.py 3
```
Reads `selected_year` from `config.json` (e.g., 2025) and creates `./Exercices/2025/Ex_25_3.cpp` and `.h`.

### Configuration & Templates

On first run, the script automatically creates:
* `config.json`: Stores the active year.
* `template_h.txt` & `template_cpp.txt`: File templates.

You can edit the template files. Insert exactly `{filename}` anywhere in the text files, and the script will replace it with the generated file name (e.g., `Ex_25_2`).
