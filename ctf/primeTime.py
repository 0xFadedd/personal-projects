#!/usr/bin/env python3

from telnetlib import Telnet
import sys
import re

HOST = 'primetime.baectf.com'
PORT = 443
PASSWORD = "terminaldisc"

if len(sys.argv) > 1:
    HOST = sys.argv[1]
if len(sys.argv) > 2:
    PORT = int(sys.argv[2])

BUFSIZE = 4096

def is_prime(n):
    """ Determines whether a number is prime"""
    if n <= 1:
        return False
    for divisor in range(2, int(n ** 0.5) + 1):
        if n % divisor == 0:
            return False
    return True

def get_primes(n):
    """Get a list of primes < n"""
    return [x for x in range(3, n) if is_prime(x)]



MAX_PRIME = 10000000  # adjust this as needed
primes = get_primes(MAX_PRIME)

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
            num = int(m.groups()[0])
            print("Finding prime below: %d" % num)
            # Find the largest prime less than num in the pre-calculated list
            prime = next(x for x in reversed(primes) if x < num)
            print("Sending: %d" % prime)
            tn.write(("%s\n" % prime).encode())
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