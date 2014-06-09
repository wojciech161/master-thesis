#ifndef CORE_PARAMETERS_HPP_
#define CORE_PARAMETERS_HPP_

struct LineDetectionParams
{
    bool enabled;
    int thresholdValue;
    int unsharpMaskStandardDeviation;
    int denoisingFactor;
    int bilateralFilterCounter;
    int gaussianBlurRadius;
    int gaussianBlurStandardDeviation;
    int gaussianBlurCounter;
    int initialThreshold;
    int mimimalColorArea;
    int maxNumberOfColors;
    int diameter;
    int sigmaColor;
    int sigmaSpace;
};

struct ColorSegmentationParams
{
    bool enabled;
    int gaussianBlurRadius;
    int gaussianBlurStandardDeviation;
    int diameter;
    int sigmaColor;
    int sigmaSpace;
    int dilationAndErosionSize;
    int dilationAndErosionCounter;
    int windowWidth;
    int maxNumberOfColors;
};

#endif // CORE_PARAMETERS_HPP_
