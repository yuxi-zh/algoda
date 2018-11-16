import time
import math
import random

def BTest(A, N):
	S = 0
	T = N - 1

	while T % 2 == 0:
		S += 1
		T //= 2

	X = pow(A, T) % N

	if X == 1 or X == N - 1:
		return True

	for I in range(0, S):
		X = pow(X, 2) % N
		if X == N - 1:
			return True

	return False

def MillRob(N):
	A = random.randint(2, N - 2)
	return BTest(A, N);

def RepeatMillRab(N, K):
	for I in range(1, K + 1):
		if not MillRob(N):
			return False
	return True


def FindPrimesInProbability(V):
	V.append(2);
	V.append(3);

	for M in range(5, 10001, 2):
		if RepeatMillRab(M, math.floor(math.log(M))):
			V.append(M)

def FindPrimesInDeteministic(V):
	V.append(2);
	V.append(3);

	for M in range(5, 10001, 2):
		IsPrime = True
	
		for I in range(2, math.floor(math.sqrt(M)) + 1):
			if M % I== 0:
				IsPrime = False
				break
	
		if IsPrime:
			V.append(M)

def Timing(Target, V):
	Begin = time.time()
	Target(V)
	End = time.time()
	return End - Begin

V1 = []
V2 = []

print(Timing(FindPrimesInDeteministic, V1))
print(Timing(FindPrimesInProbability, V2))

print(len(V1))
print(len(V2))
print((len(V1) - len(V2)) / len(V2))