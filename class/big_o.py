import math

times = [10**6]
times.append(times[-1]*60)
times.append(times[-1]*60)
times.append(times[-1]*24)
times.append(times[-1]*30)
times.append(times[-1]*365)
times.append(times[-1]*100)

def inverse_nlogn(n: int) -> int:
    l = int(math.sqrt(n))
    r = n
    while (r-l) > 1:
        mid = (r+l)//2
        aprox = mid*math.log2(mid)
        if aprox > n:
            r = mid
        elif aprox < n:
            l = mid
        else:
            return mid
    return l

def inverse_factorial(n: int) -> int:
    x = 1
    fact = 1
    while n > fact:
        x += 1
        fact*=x
    return x-1

big_o = {
    "log n"     : lambda n: f"2^{n}",
    "sqrt(n)"   : lambda n: f"{n}^2",
    "n"         : lambda n: n,
    "n*log n"   : inverse_nlogn,
    "n^2"       : lambda n: int(math.sqrt(n)),
    "n^3"       : lambda n: int(math.cbrt(n)),
    "2^n"       : lambda n: int(math.log2(n)),
    "n!"        : inverse_factorial,
}

result = [["", "second", "hour", "day", "month", "year", "century"]]

for name, t_complex in big_o.items():
    result.append([name, *(t_complex(t) for t in times)])

for row in result:
    print(row)
