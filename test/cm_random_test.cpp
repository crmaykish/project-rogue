#include "gtest/gtest.h"
#include "cm_random.h"

TEST(RandomTest, RandomIntMinMaxTest)
{
    int iterations = 1000;

    bool minGenerated = false;
    bool maxGenerated = false;

    for (int i = 0; i < iterations; i++)
    {
        int t = cm::RandomInt(1, 10);

        if (t == 1)
        {
            minGenerated = true;
        }
        else if (t == 10)
        {
            maxGenerated = true;
        }
    }

    EXPECT_TRUE(minGenerated);
    EXPECT_TRUE(maxGenerated);
}