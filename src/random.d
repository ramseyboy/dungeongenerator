import std.random;

/**
* computes a random integer within the provided bounds inclusive
* Params:
*  lower = lower bound
*  upper = upper bound
* Returns: random integer
*/
extern (C) 
{
    int generate(int lower, int upper)
    {
        Random gen;
        auto r = uniform(lower, upper + 1, gen);
        return r;
    }
}
