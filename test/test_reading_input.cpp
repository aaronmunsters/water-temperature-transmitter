#include <Arduino.h>
#include <unity.h>

// Cfr. official MTP documentation:
// https://web.archive.org/web/20240529091954/https://www.h-tronic.de/media/49/17/ef/1657552422/User%20manual.pdf
String sampleInputString[5] = {"121.1", "1.5", "-11.2", "Err.1", "Err.3"};
char sampleInputHex[5][7] = {
    {0x31, 0x32, 0x31, 0x2E, 0x31, 0x0D, 0x0A}, // "121.1"
    {0x20, 0x20, 0x31, 0x2E, 0x35, 0x0D, 0x0A}, // "1.5"
    {0x2D, 0x31, 0x31, 0x2E, 0x32, 0x0D, 0x0A}, // "-11.2"
    {0x45, 0x72, 0x72, 0x2E, 0x31, 0x0D, 0x0A}, // "Err.1"
    {0x45, 0x72, 0x72, 0x2E, 0x33, 0x0D, 0x0A}, // "Err.3"
};

void setUp(void)
{
    // set stuff up here
}

void tearDown(void)
{
    // clean stuff up here
}

void mock_test()
{
    TEST_ASSERT_TRUE(0);
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();

    // // TODO: remove this empty test stuff
    // for (unsigned int i = 0; i < sizeof(fakeMeasures) / sizeof(SensorMeasurement); i++)
    // {
    //     SensorMeasurement rec = fakeMeasures[i];
    //     measurements.push(&rec);
    // }

    RUN_TEST(mock_test);

    UNITY_END();
}