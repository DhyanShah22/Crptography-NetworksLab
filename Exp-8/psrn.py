import matplotlib.pyplot as plt

# LCG parameters
a = 1664525
c = 1013904223
m = 2**32

# Seed value
seed = 42  

def lcg(seed, n):
    """Generate n pseudo-random numbers using LCG."""
    numbers = []
    x = seed
    for _ in range(n):
        x = (a * x + c) % m
        numbers.append(x)
    return numbers

def scale_to_range(numbers, min_val, max_val):
    """Scale a list of numbers to a specified range [min_val, max_vzal]."""
    return [min_val + (num / m) * (max_val - min_val) for num in numbers]

# Generate 10,000 pseudo-random numbers
n = 10000
random_numbers = lcg(seed, n)

# Scale numbers to the range [-500, 2000]
scaled_numbers = scale_to_range(random_numbers, -500, 2000)

# Plotting the histogram
plt.hist(scaled_numbers, bins=50, edgecolor='black')
plt.axvline(x=seed, color='red', linestyle='dotted', linewidth=2, label=f'Seed Value ({seed})')

# Labels and title
plt.title('Frequency Distribution of LCG-Generated Numbers in [-500, 2000]')
plt.xlabel('Value')
plt.ylabel('Frequency')
plt.legend()
plt.grid(True)

# Show the plot
plt.show()
