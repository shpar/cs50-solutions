#Python implementation of the caesar cipher
#usage: python caesar.py key


import cs50
import sys

def main():
    if len(sys.argv) != 2:
        exit(1)
    else:
        print("Plain text:", end=" ")
        plain = cs50.get_string()
        text = [i for i in plain]
        for i in range(len(text)):
            if text[i].isupper():
                text[i] = chr((ord(text[i]) - ord("A") + int(sys.argv[1])) % (ord("Z") - ord("A") + 1) + ord("A")) 
            elif text[i].islower():
                text[i] = chr((ord(text[i]) - ord("a") + int(sys.argv[1])) % (ord("z") - ord("a") + 1) + ord("a"))
            else:
                exit(2)
        print("Ciphered text: {}".format(''.join(text)))

if __name__ == "__main__":
    main()