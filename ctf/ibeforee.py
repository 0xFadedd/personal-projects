#!/usr/bin/env python3

from telnetlib import Telnet
import sys
import re

HOST = 'primetime.baectf.com'
PORT = 443
PASSWORD = "terminaldisc"


import re

def evaluate_expression_with_rules(expression):
    # Helper function to evaluate parts of the expression according to BIDMAS
    def evaluate_bidmas(part):
        # This simplification assumes no parentheses or exponents are in the input,
        # and that division is not used, based on provided examples.
        # For full BIDMAS support, a more complex parser or the eval() function with safety checks would be needed.
        while 'i' in part or 'e' in part:
            # Find the first occurrence of 'i' or 'e' and calculate it
            for op in ['i', 'e']:  # Indices and then Division/Multiplication
                if op in part:
                    i = part.index(op)
                    if op == 'i':
                        result = int(part[i-1]) * int(part[i+1])
                    elif op == 'e':
                        result = int(part[i-1]) + int(part[i+1])
                    part = part[:i-1] + [str(result)] + part[i+2:]
                    break
        return part

    # Split expression on 'c' to handle parts separately
    parts = re.split(r'(c)', expression)
    evaluated_parts = []
    
    for part in parts:
        if part.isdigit() or part in 'cie':  # Skip direct numbers or operators
            evaluated_parts.append(part)
        else:
            # Split part into components and evaluate according to BIDMAS
            components = re.findall(r'\d+|[ie]', part)
            evaluated = evaluate_bidmas(components)
            evaluated_parts += evaluated

    # Process 'c' operations with BIDMAS results
    while 'c' in evaluated_parts:
        i = evaluated_parts.index('c')
        result = int(evaluated_parts[i-1]) - int(evaluated_parts[i+1])
        evaluated_parts = evaluated_parts[:i-1] + [str(result)] + evaluated_parts[i+2:]

    return int(evaluated_parts[0])

# Test the function with the given example
test_expression = "7e2i3e3c8e3"
evaluated_result = evaluate_expression_with_rules(test_expression)
evaluated_result


    


def send_answer(tn):
    """ Attempts to read the question and send the answer.
    Returns True if the question is answered
    """

    answered = False
    try:
        question = tn.read_until(b"\n")
        m = re.search(b": (\d*)", question)
        if m is None:
            print(question.decode())
        else:
            num = str(m.groups()[0])
            print("Finding prime below: %d" % num)
            # Find the largest prime less than num in the pre-calculated list
            res = evaluate_expression_with_rules(num)
            print("Sending: %d" % res)
            tn.write(("%s\n" % res).encode())
            print(tn.read_until(b"\n").decode())
            answered = True
    except EOFError:
        print("Connection closed")
    return answered

tn = Telnet(HOST, PORT)
# Password challenge/response
data = tn.read_until(b": ")
print(data.decode())
tn.write((PASSWORD + "\n").encode())
# Welcome message
print(tn.read_until(b"\n").decode())
print(tn.read_until(b"\n").decode())

# Now solve the challenge
while send_answer(tn):
    pass

tn.close()