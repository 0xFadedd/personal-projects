import os
import sys

def check_file_structure(filename):
    dirpath = os.path.dirname(filename)

    # We check only if the file is directly inside lambdas or layers.
    # For that, we look for lambdas or layers as the second last item in the path.
    path_parts = dirpath.split(os.sep)
    print (path_parts)
    if len(path_parts) < 2:  # we need at least ["lambdas or layers", "subdir"]
        return

    if path_parts[-2] in ['lambdas', 'layers']:
        # Check for 'src' directory
        if not os.path.isdir(os.path.join(dirpath, 'src')):
            print(f"Error: {dirpath} does not have a 'src' directory")

        # Check for 'template.yml'
        if not os.path.isfile(os.path.join(dirpath, 'template.yml')):
            print(f"Error: {dirpath} does not have a 'template.yml' file")

        # Check for any other files or directories that shouldn't be there
        for subdirname in os.listdir(dirpath):
            if subdirname not in ['src', 'template.yml']:
                print(f"Error: {dirpath} contains an invalid subdirectory or file: {subdirname}")

        # Check if 'src' has at least one file
        if not os.listdir(os.path.join(dirpath, 'src')):
            print(f"Error: {os.path.join(dirpath, 'src')} does not have any files")

if __name__ == "__main__":
    check_file_structure(sys.argv[1])
else:
    print("This file is not meant to be imported")
