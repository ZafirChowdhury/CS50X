def main():
    card_number = get_number()

    if checksum(card_number):
        ae_starts_with = ["34", "37"]
        master_card_starts_with = ["51", "52", "53", "54", "55"]
        visa_starts_with = ["4"]

        size = len(card_number)

        if size == 15 and card_number[:2]  in ae_starts_with:
            print("AMEX")
            return

        elif size == 16 and card_number[:2]  in master_card_starts_with:
            print("MASTERCARD")
            return

        elif (size == 13 or size == 16) and card_number[0]  in visa_starts_with:
            print("VISA")
            return

        else:
            print("INVALID")

    else:
        print("INVALID")


def checksum(s):
    s = s[::-1]
    size = len(s)

    sum_odd_2x = 0
    sum_even = 0
    for i in range(size):
        if (i%2) != 0:
            digit = (int(s[i])*2)
            while digit > 0:
                last_digit = digit % 10
                sum_odd_2x = sum_odd_2x + last_digit
                digit = digit // 10
        else:
            sum_even = sum_even + int(s[i])

    return (sum_odd_2x + sum_even) % 10 == 0


def get_number():
    while True:
        user_input = input("Number: ")
        if user_input.isnumeric():
            return user_input


if __name__ == "__main__":
    main()
