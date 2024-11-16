# Import necessary modules
import string
import getpass
import secrets
import re

# Function to check password strength
def check_pwd(password):
    """
    Checks the strength of a password.

    Args:
        password (str): The password to check.

    Returns:
        dict: A dictionary containing the password's strength and remarks.
    """
    # Initialize variables
    strength = 0
    remarks = []
    lower_count = upper_count = num_count = wspace_count = special_count = 0

    # Iterate through each character in the password
    for char in password:
        # Check for lowercase letters
        if char in string.ascii_lowercase:
            lower_count += 1
        # Check for uppercase letters
        elif char in string.ascii_uppercase:
            upper_count += 1
        # Check for digits
        elif char in string.digits:
            num_count += 1
        # Check for whitespace characters
        elif char == ' ':
            wspace_count += 1
        # Check for special characters
        else:
            special_count += 1

    # Calculate password strength
    if lower_count >= 1: strength += 1
    if upper_count >= 1: strength += 1
    if num_count >= 1: strength += 1
    if wspace_count >= 1: strength += 1
    if special_count >= 1: strength += 1

    # Check for common patterns
    if re.search(r"abc|123|qwerty", password, re.IGNORECASE):
        remarks.append("Password contains common pattern.")

    # Determine password strength remarks
    if strength == 1:
        remarks.append("Very Bad Password!!! Change ASAP")
    elif strength == 2:
        remarks.append("Not A Good Password!!! Change ASAP")
    elif strength == 3:
        remarks.append("It's a weak password, consider changing")
    elif strength == 4:
        remarks.append("It's a hard password, but can be better")
    elif strength == 5:
        remarks.append("A very strong password")

    # Print password analysis
    print('Your password has: ')
    print(f"{lower_count} lowercase characters")
    print(f"{upper_count} uppercase characters")
    print(f"{num_count} numeric characters")
    print(f"{wspace_count} whitespace characters")
    print(f"{special_count} special characters")
    print(f"Password Strength: {strength}")
    for remark in remarks:
        print(f"Hint: {remark}")

    return {"strength": strength, "remarks": remarks}

# Function to generate a strong password
def generate_strong_pwd(length=12):
    """
    Generates a strong password.

    Args:
        length (int): The length of the password.

    Returns:
        str: A strong password.
    """
    alphabet = string.ascii_letters + string.digits + string.punctuation
    while True:
        password = ''.join(secrets.choice(alphabet) for i in range(length))
        if (any(c.islower() for c in password)
                and any(c.isupper() for c in password)
                and any(c.isdigit() for c in password)
                and any(c in string.punctuation for c in password)):
            break
    return password

# Function to ask user if they want to check another password
def ask_pwd(another_pwd=False):
    """
    Asks user if they want to check another password.

    Args:
        another_pwd (bool): Whether to ask for another password.

    Returns:
        bool: True if user wants to check another password, False otherwise.
    """
    valid = False
    if another_pwd:
        choice = input('Do you want to enter another pwd (y/n): ')
    else:
        choice = input('Do you want to check pwd (y), generate strong pwd (g) or quit (q): ')
    
    # Validate user input
    while not valid:
        if choice.lower() == 'y':
            return True
        elif choice.lower() == 'n':
            return False
        elif choice.lower() == 'g':
            print("Generated strong password: ", generate_strong_pwd())
            return False
        elif choice.lower() == 'q':
            return False
        else:
            print('Invalid, Try Again')
            choice = input('Do you want to check pwd (y), generate strong pwd (g) or quit (q): ')

# Main program
if __name__ == '__main__':
    print('+++ welcome to PWD checker +++')
    
    # Ask user if they want to check a password
    ask_pw = ask_pwd()
    
    # Check password strength
    while ask_pw:
        password = getpass.getpass("Enter Password: ")
        check_pwd(password)
        ask_pw = ask_pwd(True)


