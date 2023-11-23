import os
import sys

def check_file_structure(basepath):
    for root_folder in ['lambdas', 'layers']:
        root_path = os.path.join(basepath, root_folder)
        if not os.path.exists(root_path):
            print(f"Error: {root_folder} directory is missing")
            continue

        for feature_or_lambda in os.listdir(root_path):
            feature_or_lambda_path = os.path.join(root_path, feature_or_lambda)
            if os.path.isdir(feature_or_lambda_path):
                if root_folder == 'lambdas':
                    # Check that the feature directory does not have a 'src' or 'template.yml'
                    violation = check_no_src_or_template(feature_or_lambda_path)

                    # If there's no violation, proceed to check the lambdas under the feature
                    if not violation:
                        for lambda_folder in os.listdir(feature_or_lambda_path):
                            lambda_path = os.path.join(feature_or_lambda_path, lambda_folder)
                            inspect_lambda_or_layer_structure(lambda_path)
                else:
                    # Directly inspect structure for layers
                    inspect_lambda_or_layer_structure(feature_or_lambda_path)


def check_no_src_or_template(path):
    violation_found = False

    # Check for 'src' directory
    if os.path.isdir(os.path.join(path, 'src')):
        print(f"Error: {path} should not have a 'src' directory")
        violation_found = True

    # Check for 'template.yml'
    if os.path.isfile(os.path.join(path, 'template.yml')):
        print(f"Error: {path} should not have a 'template.yml' file")
        violation_found = True

    return violation_found


def inspect_lambda_or_layer_structure(path):
    # Check for 'src' directory
    if not os.path.isdir(os.path.join(path, 'src')):
        print(f"Error: {path} does not have a 'src' directory")
        return

    # Check for 'template.yml'
    if not os.path.isfile(os.path.join(path, 'template.yml')):
        print(f"Error: {path} does not have a 'template.yml' file")
        return

    # Check for any other files or directories that shouldn't be there
    for subitem in os.listdir(path):
        if subitem not in ['src', 'template.yml']:
            print(f"Error: {path} contains an invalid subdirectory or file: {subitem}")
            return

    # Check if 'src' has at least one file
    if not os.listdir(os.path.join(path, 'src')):
        print(f"Error: {os.path.join(path, 'src')} does not have any files")


if __name__ == "__main__":
    # Assuming script is located in the 'scripts' folder
    base_path = os.path.dirname(os.path.realpath(__file__))
    check_file_structure(base_path)
else:
    print("This file is not meant to be imported")
