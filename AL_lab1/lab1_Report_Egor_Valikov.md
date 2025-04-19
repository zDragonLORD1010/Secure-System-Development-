# Lab 1 - BLDD

**Student:** Egor Valikov

**Group:** B22-CBS-01

**Email:** e.valikov@innopolis.university

**Telegram:** @EgorValikov

**Github report:** https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/AL_lab1/lab1_Report_Egor_Valikov.md

## Introduction

The `ldd` command outputs a list of dynamic dependencies of executable files. My task was to implement the reverse version (`bldd`), which:

- Finds all executable files

- Works on multiple architectures (x86, x86_64, armv7, aarch64)

- Generates reports

## Implement the `bldd` app

The first thing I did was figure out how `ldd` works, and then I started writing code. I wrote `bldd` in Python. The basic implementation of the `bldd` algorithm is presented in this function (For ease of perception, I have written a few basic comments):

```py
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
```

## `bldd` application functionality

### The application is customizable

I have written some simple functionality for the application. Let's look at everything in order:

**1. `-l` (`--library`) flag:** This flag allows you to select a specific library to scan (If this flag is missing, the application scans all the needed libraries).

**2. `-a` (`--arch`) flag:** This flag allows you to select a specific architecture (If this flag is missing, the application will review all architectures: `x86`, `x86_64`, `armv7`, `aarch64`).

**3. `-d` (`--directory`) flag:** This flag allows you to select the directory to scan (If this flag is missing, the application will scan `/` by default).

**4. `-o` (`--output`) flag:** This flag allows you to create a report.

**5. `-h` (`--help`) flag:** This flag allows you to view the functionality of the application and see usage examples.

### The application generates a report as output (in `txt` format)

- The report is sorted by the number of uses of the executable file. 

- To generate a report, you need to specify the `-o` flag and write the name of the file to which it will be written. 

Here I have provided the code for generating reports (For ease of perception, I have written a few basic comments):

```py
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
```

### Usage examples

In this section, I want to demonstrate and explain some usage examples.

#### Usage of `-h` (`--help`)

Using the `-h` command, you can see the functionality of the application and usage examples, as I described earlier:

```bash
./bldd.py -h
```

![image](https://github.com/user-attachments/assets/510b9273-db35-4ed2-b53e-4b16453f2e21)

#### Usage of `-l` (`--library`) and `-d` (`--directory`)

As I described earlier, this command will allow you to view the files of only one specific library:

```bash
./bldd.py -l <library_name>
```

For target directory:

```bash
./bldd.py -d <directory_name>
```

In this example, you can clearly see the use of this command. It analyzes the `/home` directory, and since there is no `-a` flag, which is a filter to select a specific architecture, the application examines all files associated with the `libc.so.6` library.

![image](https://github.com/user-attachments/assets/31d02e90-5a1a-454a-b0ea-86d995b69c9d)

#### Usage of `-a` (`--arch`)

As I described earlier, these commands allow us to consider only a specific architecture (`x86`, `x86_64`, `armv7`, `aarch64`):

```bash
./bldd.py -a <arch_name>
```

In this example, you can clearly see how this command is used. The program analyzes the "/home" directory, and since there is no "-l" flag in it, the application checks all libraries related to the `x86-64` architecture.

![image](https://github.com/user-attachments/assets/974fd8a0-af28-4f7f-bdc2-41f9390b0cb9)

#### Usage of `-o` (`--output`)

This command allows you to write the output to a specific file:

```bash
./bldd.py -o <output_file.txt>
```
This example shows two commands that analyze all architectures and all libraries. However, the first command scans `/home`, and the second one, due to the lack of the `-d` flag, scans `/`

![image](https://github.com/user-attachments/assets/90b9a49e-242e-462a-840f-111855ab7933)

Example of reports from my computer:

Scan `/home` directory: [`otput.txt`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/AL_lab1/otput.txt)

Scan `/` directory: [`otput2.txt`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/AL_lab1/otput2.txt)

## Used resources

Screenshots: [link](https://github.com/zDragonLORD1010/Secure-System-Development-/tree/main/AL_lab1/img)

Full application code (with comments): [`bldd.py`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/AL_lab1/bldd.py)

Scan `/home` directory: [`otput.txt`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/AL_lab1/otput.txt)

Scan `/` directory: [`otput2.txt`](https://github.com/zDragonLORD1010/Secure-System-Development-/blob/main/AL_lab1/otput2.txt)
