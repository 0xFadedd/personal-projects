import re
import itertools

# Define the regular expressions
regex_list = [
    r".{21}",
    r"...........ba........",
    r"^g.t",
    r"to",
    r"[^m]*mob",
    r"b.l",
    r"^[^t]+t t[^t] t[^t]{2} [^t]{3}t[^t]+$",
    r".............[psnzqj][blrvt][okhzmb].....",
    r".............[riwynk][ftwjp][mcgjwpx]....."
]

# Generate all possible combinations of characters
all_chars = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789'
flag_length = 21  # Adjust the flag length as needed

combinations = itertools.product(all_chars, repeat=flag_length)

# Check each combination against all regular expressions
for flag_candidate in combinations:
    flag_line = "".join(flag_candidate)
    
    # Check if the flag line matches all regular expressions
    if all(re.match(regex, flag_line) for regex in regex_list):
        print("Flag found:", flag_line)
        break

