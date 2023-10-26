import os

def check_file_structure(root_dir):
    """
    Check that the paths of all files under the `lambdas` and `layers` directories match a specific layout.
    The layout they should follow is:
    lambdas
    --------${lambda name}
    -----------------------src
    -----------------------template.yml
    --------${lambda name}
    -----------------------src
    -----------------------template.yml

    layer
    --------${layer name}
    -----------------------src
    -----------------------template.yml
    --------${layer name}
    -----------------------src
    -----------------------template.yml

    Also check that the contents of the src folder in each subdirectory has files present in them.
    """
    for dirpath, dirnames, filenames in os.walk(root_dir):
        if dirpath.endswith('lambdas') or dirpath.endswith('layers'):
            for dirname in dirnames:
                if not os.path.isdir(os.path.join(dirpath, dirname, 'src')):
                    print(f"Error: {os.path.join(dirpath, dirname)} does not have a 'src' directory")
                if not os.path.isfile(os.path.join(dirpath, dirname, 'template.yml')):
                    print(f"Error: {os.path.join(dirpath, dirname)} does not have a 'template.yml' file")
                for subdirname in os.listdir(os.path.join(dirpath, dirname)):
                    if subdirname != 'src' and subdirname != 'template.yml':
                        print(f"Error: {os.path.join(dirpath, dirname, subdirname)} is not a valid subdirectory")
                if len(os.listdir(os.path.join(dirpath, dirname, 'src'))) == 0:
                    print(f"Error: {os.path.join(dirpath, dirname, 'src')} does not have any files")
