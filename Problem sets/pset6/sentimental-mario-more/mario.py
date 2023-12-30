def main():
    hight = get_hight()

    print_piramids(hight)


def get_hight():
    while True:
        try:
            user_input = int(input("Hight: "))
            if 1 <= user_input <= 8:
                return user_input
        except (ValueError, NameError):
            pass


def print_piramids(hight):
    x = hight - 1
    for i in range(1, hight+1):
        print(" " * x, end="")
        print("#" * i, end="")

        print("  ", end="")

        print("#" * i, end="")

        x = x - 1
        print()


if __name__ == "__main__":
    main()