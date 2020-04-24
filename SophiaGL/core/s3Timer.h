#pragma once

class s3Timer
{
public:
    s3Timer(){}

    // start counting time
    double start();

	// end counting time
    double end();

	// difference of counting time between start and end
    double difference();

    double startTime = 0.0, endTime = 0.0;
};