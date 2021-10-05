#include <vector>

#define LOOPS 10000000
#define REPEATS 20

int
main(void)
{
    for (int repetitions = 0; repetitions < REPEATS; repetitions++) {
        std::vector<int> iv{0};
        std::vector<int> iv2{0};
        iv.reserve(LOOPS+1);
        iv2.reserve(LOOPS+1);

       int sum = 0;

        for (int ii = 0; ii < LOOPS; ii++) {
            iv.push_back(ii);
        }

        for (auto x : iv) {
            iv2.push_back(x * 2);
        }

        std::vector<int> result{0};
        result.reserve(LOOPS+1);

        for (int ii = 0; ii < iv2.size(); ii++) {
            result[ii] = iv[ii] + iv2[ii];
        }

        (void)result[LOOPS];
    }
    return 0;
}
