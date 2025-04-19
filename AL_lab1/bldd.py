#!/usr/bin/env python3
import os
import argparse
from collections import defaultdict
from elftools.elf.elffile import ELFFile


# Scan the directory for executable files using the specified library or all libraries
def scan_library(directory, library=None, target_arch=None):

    # A variable for storing results
    results = defaultdict(lambda: defaultdict(list))

    # List of supported architectures
    supported_arches = {
        'x86': 'EM_386',
        'x86_64': 'EM_X86_64',
        'armv7': 'EM_ARM',
        'aarch64': 'EM_AARCH64'
    }

    # Scan the directory
    for root, _, files in os.walk(directory):
        for file in files:
            file_path = os.path.join(root, file)

            # Skip non-executable files
            if not os.access(file_path, os.X_OK):
                continue

            try:
                with open(file_path, 'rb') as f:

                    # Check if the file is an ELF file
                    if f.read(4) != b'\x7fELF':
                        continue
                    f.seek(0)
                    elf = ELFFile(f)

                    # Detect architecture of the ELF file
                    arch = None
                    for arch_name, elf_code in supported_arches.items():
                        if elf['e_machine'] == elf_code:
                            arch = arch_name
                            break

                    # Skip if the architecture is not supported or does not match the target architecture
                    if not arch or (target_arch and arch != target_arch):
                        continue

                    # Skip if there is no ".dynamic" section in the ELF file
                    if not elf.get_section_by_name('.dynamic'):
                        continue

                    # Scan DT_NEEDED
                    for segment in elf.iter_segments():
                        if segment.header.p_type != 'PT_DYNAMIC':
                            continue
                        for tag in segment.iter_tags():
                            if tag.entry.d_tag == 'DT_NEEDED':
                                lib_name = tag.needed

                                # Check if the library name matches the specified library or if a specific library is not specified
                                if (library and lib_name == library) or not library:
                                    results[arch][lib_name].append(file_path)
            except Exception:

                # Continue to the next file
                continue
    return results

# Generate output data (supports the .txt format)
def generate_report(results, library, directory, output=None, target_arch=None):

    # List of supported architectures fot output
    arch_display = {
        'x86': 'i386 (x86)',
        'x86_64': 'x86-64',
        'armv7': 'armv7',
        'aarch64': 'aarch64'
    }

    # Creates a part of the final report
    report = [f"Report on dynamic used libraries by ELF executables in: {directory}"]

    # Determine which architectures should be included
    output_arches = [target_arch] if target_arch else arch_display.keys()

    # Creating a row-by-row report
    for arch in output_arches:
        report.append(f"\n---------- {arch_display[arch]} ----------")

        # Check if there are any results for the current architecture
        if arch not in results or not results[arch]:
            report.append("No executables found.")
            continue

        # Get a library map for the current architecture
        lib_map = results[arch]

        # If a specific library is specified, filter the results by that library
        if library:
            if library in lib_map:
                execs = lib_map[library]
                report.append(f"{library} ({len(execs)} execs):")
                for path in execs:
                    report.append(f"\t -> {path}")
            else:
                report.append(f"No executables found using {library}")
        else:

            # If no specific library is specified, sort all libraries by the number of users
            sorted_libs = sorted(lib_map.items(), key=lambda x: len(x[1]), reverse=True)
            for lib, paths in sorted_libs:
                report.append(f"{lib} ({len(paths)} execs):")
                for path in paths:
                    report.append(f"\t -> {path}")
                report.append("")

    # Combine the reports into one final report
    final_report = '\n'.join(report)

    # Write the report to the specified output file or print it on the console
    if output:
        with open(output, 'w') as f:
            f.write(final_report)
    else:
        print(final_report)


# Main function
def main():

    examples = """
examples:
    
    # Scan for a specific library (if no -l flag it scans all libraries)
    ./bldd.py -l libc.so.6

    # Scan a specific architecture (if no -a flag it scans all architectures: x86, x86_64, armv7, aarch64)
    ./bldd.py -a x86_64

    # Scan a specific directory (if no -d flag it scans "/")
    ./bldd.py -d /home

    # Output to file (txt format)
    ./bldd.py -o output.txt
"""

    parser = argparse.ArgumentParser(description='bldd - Find executables using specified or all shared libraries', formatter_class=argparse.RawDescriptionHelpFormatter, epilog=examples)
    parser.add_argument('-l', '--library', help='library to search (libcef.so, libc.so.6, etc.). If this parameter is skipped, all libraries are scanned')
    parser.add_argument('-d', '--directory', default='/', help='directory to scan (default: /)')
    parser.add_argument('-a', '--arch', choices=['x86', 'x86_64', 'armv7', 'aarch64'], help='architecture to filter (x86, x86_64, armv7, aarch64)')
    parser.add_argument('-o', '--output', help='output file to save the report')
    args = parser.parse_args()
    results = scan_library(args.directory, args.library, args.arch)
    generate_report(results, args.library, args.directory, args.output, args.arch)


if __name__ == '__main__':
    main()