# Find out multiplication of all elements in a tuple

tup = tuple(map(int, input("Enter the tuple: ").split()))
print("The tuple is: ", tup)

product = 1
for i in tup:
    product *= i

print("The product of all elements in the tuple is: ", product)