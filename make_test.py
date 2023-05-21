import random

#Tạo 10 bộ dữ liệu ngẫu nhiên gồm 10^6 số
for i in range(10):
    with open(f"test_{i}.txt", "w") as file:
        for _ in range(1000000):
            file.writelines(str(random.randint(1, 1000000)) + '\n')