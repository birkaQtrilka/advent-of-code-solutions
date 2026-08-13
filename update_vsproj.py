import os
import xml.etree.ElementTree as ET

def get_relative_path(file_path, project_dir):
    """Get the relative path of file_path to project_dir, using backslashes."""
    rel_path = os.path.relpath(file_path, project_dir)
    return rel_path.replace('/', '\\')

def update_vcxproj(project_path, source_dirs):
    # Register MSBuild namespace to preserve standard vcxproj formatting
    ns_url = 'http://schemas.microsoft.com/developer/msbuild/2003'
    ET.register_namespace('', ns_url)
    ns = {'msbuild': ns_url}

    tree = ET.parse(project_path)
    root = tree.getroot()

    project_dir = os.path.dirname(os.path.abspath(project_path))

    # Find ItemGroups for ClCompile (.cpp), ClInclude (.h), and Text (.txt)
    clcompile_group = None
    clinclude_group = None
    text_group = None

    for ig in root.findall('msbuild:ItemGroup', ns):
        if clcompile_group is None and ig.find('msbuild:ClCompile', ns) is not None:
            clcompile_group = ig
        if clinclude_group is None and ig.find('msbuild:ClInclude', ns) is not None:
            clinclude_group = ig
        if text_group is None and ig.find('msbuild:Text', ns) is not None:
            text_group = ig

    # Create ItemGroups if they don't exist
    if clcompile_group is None:
        clcompile_group = ET.SubElement(root, 'ItemGroup')
        clcompile_group.text = '\n    '
        clcompile_group.tail = '\n  '
        
    if clinclude_group is None:
        clinclude_group = ET.SubElement(root, 'ItemGroup')
        clinclude_group.text = '\n    '
        clinclude_group.tail = '\n  '

    if text_group is None:
        text_group = ET.SubElement(root, 'ItemGroup')
        text_group.text = '\n    '
        text_group.tail = '\n  '

    removed_count = 0
    added_count = 0

    existing_cpp = set()
    existing_h = set()
    existing_txt = set()

    # 1. Remove non-existing .cpp files and log existing ones
    for elem in list(clcompile_group.findall('msbuild:ClCompile', ns)):
        include_path = elem.get('Include')
        if include_path:
            abs_path = os.path.join(project_dir, include_path)
            if not os.path.exists(abs_path):
                clcompile_group.remove(elem)
                removed_count += 1
                print(f"Removed missing source file: {include_path}")
            else:
                existing_cpp.add(include_path.lower())

    # 2. Remove non-existing .h files and log existing ones
    for elem in list(clinclude_group.findall('msbuild:ClInclude', ns)):
        include_path = elem.get('Include')
        if include_path:
            abs_path = os.path.join(project_dir, include_path)
            if not os.path.exists(abs_path):
                clinclude_group.remove(elem)
                removed_count += 1
                print(f"Removed missing header file: {include_path}")
            else:
                existing_h.add(include_path.lower())

    # 3. Remove non-existing .txt files and log existing ones
    for elem in list(text_group.findall('msbuild:Text', ns)):
        include_path = elem.get('Include')
        if include_path:
            abs_path = os.path.join(project_dir, include_path)
            if not os.path.exists(abs_path):
                text_group.remove(elem)
                removed_count += 1
                print(f"Removed missing text file: {include_path}")
            else:
                existing_txt.add(include_path.lower())

    # Find files in directories on disk
    found_cpp = []
    found_h = []
    found_txt = []

    for source_dir in source_dirs:
        abs_source_dir = os.path.abspath(source_dir)
        for root_dir, dirs, files in os.walk(abs_source_dir):
            # Skip hidden directories (like .git, .vs) and common build folders
            dirs[:] = [d for d in dirs if not d.startswith('.') and d.lower() not in ('x64', 'debug', 'release', 'out', 'build')]
            
            for file in files:
                abs_path = os.path.join(root_dir, file)
                if file.endswith('.cpp'):
                    found_cpp.append(get_relative_path(abs_path, project_dir))
                elif file.endswith('.h'):
                    found_h.append(get_relative_path(abs_path, project_dir))
                elif file.endswith('.txt'):
                    found_txt.append(get_relative_path(abs_path, project_dir))

    # Helper to append elements while preserving XML indentation
    def add_element(group, tag, include_path):
        if len(group) > 0:
            group[-1].tail = '\n    '
        else:
            group.text = '\n    '
            
        elem = ET.SubElement(group, tag, Include=include_path)
        elem.tail = '\n  '
        return elem

    # 4. Add missing .cpp files to ClCompile
    for cpp_file in sorted(found_cpp):
        if cpp_file.lower() not in existing_cpp:
            add_element(clcompile_group, 'ClCompile', cpp_file)
            existing_cpp.add(cpp_file.lower())
            added_count += 1
            print(f"Added source file: {cpp_file}")

    # 5. Add missing .h files to ClInclude
    for h_file in sorted(found_h):
        if h_file.lower() not in existing_h:
            add_element(clinclude_group, 'ClInclude', h_file)
            existing_h.add(h_file.lower())
            added_count += 1
            print(f"Added header file: {h_file}")

    # 6. Add missing .txt files to Text
    for txt_file in sorted(found_txt):
        if txt_file.lower() not in existing_txt:
            add_element(text_group, 'Text', txt_file)
            existing_txt.add(txt_file.lower())
            added_count += 1
            print(f"Added text file: {txt_file}")

    # Save if anything changed
    if added_count > 0 or removed_count > 0:
        tree.write(project_path, encoding='utf-8', xml_declaration=True)
        print(f"\nSuccessfully updated the vcxproj! Added {added_count} file(s), removed {removed_count} file(s).")
    else:
        print("\nNo changes needed. The vcxproj is up-to-date.")


if __name__ == '__main__':
    # Update these paths for your project
    project_path = r'C:\Saxion\Courses\AdventOfCode\TriumphIntake.vcxproj'
    source_dirs = [
        r'C:\Saxion\Courses\AdventOfCode',  # Project root
    ]
    
    update_vcxproj(project_path, source_dirs)