#python implementation of mario pyramid

import cs50

def main():
    while True:
        print("The height of the pyramid:", end=" ")
        height = cs50.get_int()
        if height >= 0 and height < 23:
            break
        
    for i in range(height):
        print(" " * (height-i-1), end="") 
        print("#" *(i+1), end="") 
        print("  ", end="")
        print("#" *(i+1)) 

if __name__ == "__main__":
    main()
