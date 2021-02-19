#ifndef UNFORM_RANDOM
#define UNFORM_RANDOM

#include <random>
#include <chrono>

class Random48
{
private:
	static long long currentTimeMicroSeconds()
	{
		auto now = std::chrono::high_resolution_clock::now().time_since_epoch();
		return (std::chrono::duration_cast<std::chrono::microseconds>(now).count());
	}

public:
	Random48(long long initialValue = currentTimeMicroSeconds())
	{
		state = initialValue & MASK;
	}

	int nextInt()
	{
		return next(32);
	}

	int nextInt(int high)
	{
		return static_cast<int>(abs(nextLong() % high));
	}

	double nextDouble()
	{
		return ((static_cast<long long>((next(26))) << 27) + next(27))
			/ static_cast<double>(1LL << 53);
	}

	int nextInt(int low, int high)
	{
		return nextInt(high - low + 1) + low;
	}

	long long nextLong()
	{
		return ((static_cast<long long>(next(32))) << 32) + next(32);
	}

private:
	long long state;

	static const long long A = 25214903917LL;
	static const long long C = 11;
	static const long long M = (1LL << 48);
	static const long long MASK = M - 1;

	int next(int bits)
	{
		state = (A * state + C) & MASK;
		return state >> (48 - bits);
	}
};


static int currentTimeSecond()
{
	auto now = std::chrono::high_resolution_clock::now().time_since_epoch();
	return std::chrono::duration_cast<std::chrono::seconds>(now).count();
}

class UniformRandom
{
public:
	UniformRandom(int seed = currentTimeSecond()) : generator{seed} {}

	int nextInt()
	{
		static std::uniform_int_distribution<unsigned int> dis;
		return dis(generator);
	}

	int nextInt(int high)
	{
		return nextInt(0, high - 1);
	}

	double nextDouble()
	{
		static std::uniform_real_distribution<double> distribution(0, 1);
		return distribution(generator);
	}

	int nextInt(int low, int high)
	{
		std::uniform_int_distribution<int> distribution(low, high);
		return distribution(generator);
	}

private:
	std::mt19937 generator;
};

#endif
