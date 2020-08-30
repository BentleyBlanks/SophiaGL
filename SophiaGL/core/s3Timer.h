#pragma once

class s3Timer
{
public:
    s3Timer(){}

    // start/end counting time
    double start();
    double end();

	// difference of counting time between start and end, in seconds
    double difference();

    double startTime = 0.0, endTime = 0.0;
};