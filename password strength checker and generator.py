import string
import secrets
import re
import tkinter as tk
from tkinter import messagebox

# Function to check password strength
def check_pwd(password):
    strength = 0
    remarks = []
    lower_count = upper_count = num_count = wspace_count = special_count = 0

    for char in password:
        if char in string.ascii_lowercase:
            lower_count += 1
        elif char in string.ascii_uppercase:
            upper_count += 1
        elif char in string.digits:
            num_count += 1
        elif char == ' ':
            wspace_count += 1
        else:
            special_count += 1

    if lower_count >= 1: strength += 1
    if upper_count >= 1: strength += 1
    if num_count >= 1: strength += 1
    if wspace_count >= 1: strength += 1
    if special_count >= 1: strength += 1

    if re.search(r"abc|123|qwerty", password, re.IGNORECASE):
        remarks.append("⚠️ Common pattern detected.")

    if strength == 1:
        remarks.append("❌ Very Bad Password! Change ASAP.")
    elif strength == 2:
        remarks.append("⚠️ Not a Good Password! Change ASAP.")
    elif strength == 3:
        remarks.append("🟡 Weak Password. Consider changing.")
    elif strength == 4:
        remarks.append("🟠 Decent Password. Could be stronger.")
    elif strength == 5:
        remarks.append("✅ Very Strong Password!")

    result = (
        f"Lowercase: {lower_count}\n"
        f"Uppercase: {upper_count}\n"
        f"Digits: {num_count}\n"
        f"Whitespace: {wspace_count}\n"
        f"Special: {special_count}\n"
        f"Strength Score: {strength}/5\n"
        + "\n".join(remarks)
    )
    return result

# Function to generate a strong password
def generate_strong_pwd(length=12):
    alphabet = string.ascii_letters + string.digits + string.punctuation
    while True:
        password = ''.join(secrets.choice(alphabet) for _ in range(length))
        if (any(c.islower() for c in password)
                and any(c.isupper() for c in password)
                and any(c.isdigit() for c in password)
                and any(c in string.punctuation for c in password)):
            return password

# GUI setup
def analyze_password():
    pwd = entry.get()
    if not pwd:
        messagebox.showwarning("Input Error", "Please enter a password.")
        return
    result = check_pwd(pwd)
    output.config(state='normal')
    output.delete(1.0, tk.END)
    output.insert(tk.END, result)
    output.config(state='disabled')

def generate_password():
    pwd = generate_strong_pwd()
    entry.delete(0, tk.END)
    entry.insert(0, pwd)
    output.config(state='normal')
    output.delete(1.0, tk.END)
    output.insert(tk.END, "Generated Password:\n" + pwd)
    output.config(state='disabled')

# Main window
root = tk.Tk()
root.title("🔐 Password Checker & Generator")
root.geometry("400x400")
root.resizable(False, False)

# Widgets
tk.Label(root, text="Enter Password:", font=("Arial", 12)).pack(pady=10)
entry = tk.Entry(root, show="*", width=30, font=("Arial", 12))
entry.pack()

tk.Button(root, text="Check Strength", command=analyze_password, bg="#4CAF50", fg="white").pack(pady=10)
tk.Button(root, text="Generate Strong Password", command=generate_password, bg="#2196F3", fg="white").pack(pady=5)

output = tk.Text(root, height=10, width=45, state='disabled', wrap='word', font=("Arial", 10))
output.pack(pady=10)

# Run the GUI
root.mainloop()
