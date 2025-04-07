import matplotlib.pyplot as plt
import numpy as np

def mod_exp(base, exp, mod):
    result = 1
    while exp > 0:
        if exp % 2 == 1:
            result = (result * base) % mod
        base = (base * base) % mod
        exp //= 2
    return result

def is_prime(n):
    if n < 2:
        return False
    for i in range(2, int(n ** 0.5) + 1):
        if n % i == 0:
            return False
    return True

def gcd(a, b):
    while b:
        a, b = b, a % b
    return a

def blum_blum_shub(seed, p, q, num_bits):
    n = p * q
    bits = []
    x = (seed * seed) % n
    for _ in range(num_bits):
        x = mod_exp(x, 2, n)
        bits.append(x % 2)
    return bits

def blum_micali(seed, g, p, num_bits):
    bits = []
    x = seed
    for _ in range(num_bits):
        x = mod_exp(g, x, p)
        bits.append(1 if x > p // 2 else 0)
    return bits

def plot_distribution(numbers, title):
    unique, counts = np.unique(numbers, return_counts=True)
    plt.bar(unique, counts, color='skyblue', edgecolor='black')
    plt.xticks(unique)
    plt.xlabel("Bit Value")
    plt.ylabel("Frequency")
    plt.title(title)
    plt.show()

choice = int(input("Choose PRNG Method:\n1. Blum Blum Shub (BBS)\n2. Blum-Micali\nEnter choice: "))
num_bits = int(input("Enter number of random bits to generate: "))

if choice == 1:
    while True:
        p, q = map(int, input("Enter two prime numbers (p and q): ").split())
        if is_prime(p) and is_prime(q):
            break
        print("Error: Both numbers must be prime!")
    
    n = p * q
    while True:
        seed = int(input(f"Enter seed (must be coprime to {n}): "))
        if gcd(seed, n) == 1:
            break
        print(f"Error: Seed must be coprime to {n}!")
    
    random_bits = blum_blum_shub(seed, p, q, num_bits)
    print("BBS Random Bits:", "".join(map(str, random_bits)))
    plot_distribution(random_bits, "BBS Random Bits Distribution")
    
elif choice == 2:
    while True:
        p = int(input("Enter a prime number (p): "))
        if is_prime(p):
            break
        print("Error: p must be prime!")
    
    g = int(input("Enter a generator (g): "))
    seed = int(input("Enter seed: "))
    
    random_bits = blum_micali(seed, g, p, num_bits)
    print("Blum-Micali Random Bits:", "".join(map(str, random_bits)))
    plot_distribution(random_bits, "Blum-Micali Random Bits Distribution")
    
else:
    print("Invalid choice! Exiting...")