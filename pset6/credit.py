#Python implementation of the creadit card checker

import cs50

def main():
    while True:
        print("Credit card number:", end=" ")
        card = cs50.get_string()
        if int(card) >= 0:
            break

    number = [int(i) for i in card]
    sum = 0
    number.reverse()

    for i in range(len(number)):
        if i % 2 == 0:
            sum += number[i]
        else:
            if 2*number[i] < 9:
                sum += 2*number[i]
            else:
                sum += 2*number[i]//10 + 2*number[i]%10

    if sum % 10 == 0:
        if number[-1] == 3 and number[-2] == 4 and len(number) == 15: 
            print("AMEX")
        elif number[-1] == 3 and number[-2] == 7 and len(number) == 15: 
            print("AMEX")
        elif number[-1] == 5 and (number[-2] < 6 or number[-2] > 0) and len(number) == 16: 
            print("MASTERCARD")
        elif number[-1] == 4 and len(number) == 13: 
            print("VISA")
        elif number[-1] == 4 and len(number) == 16: 
            print("VISA")
        else: 
            print("INVALID")
    else: 
        print("INVALID")
    


if __name__ == "__main__":
    main()

