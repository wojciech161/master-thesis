#include "filehandler/ConfigurationFileReader.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "rapidxml/rapidxml.hpp"

namespace filehandler
{

ConfigurationFileReader::ConfigurationFileReader( core::ParametersGetter& parameters )
 : parameters_( parameters )
{
    read();
}

ConfigurationFileReader::~ConfigurationFileReader()
{

}
 
void ConfigurationFileReader::read()
{
    const std::string XML_FILENAME = "resources/conf/config.xml";

    // Background detection names
    const std::string BACKGROUND_DETECTION_NODE = "background_detection";
    const std::string BD_ENABLED = "enabled";
    const std::string BD_GAUSSIAN_BLUR_RADIUS = "gaussian_blur_radius";
    const std::string BD_GAUSSIAN_BLUR_STANDARD_DEVIATION = "gaussian_blur_standard_deviation";
    const std::string BD_DIAMETER = "diameter";
    const std::string BD_SIGMA_COLOR = "sigma_color";
    const std::string BD_SIGMA_SPACE = "sigma_space";
    const std::string BD_DILATION_AND_EROSION_SIZE = "dilation_and_erosion_size";
    const std::string BD_DILATION_AND_EROSION_COUNTER = "dilation_and_erosion_counter";
    const std::string BD_WINDOW_WIDTH = "window_width";
    const std::string BD_MAX_NUMBER_OF_COLORS = "max_number_of_colors";

    // Line detection names
    const std::string LINE_DETECTION_NODE = "line_detection";
    const std::string LD_ENABLED = "enabled";
    const std::string LD_THRESHOLD_VALUE = "threshold_value";
    const std::string LD_UNSHARP_MASK_STANDARD_DEV = "unsharp_mask_standard_deviation";
    const std::string LD_DENOISING_FACTOR = "denoising_factor";
    const std::string LD_BILATERAL_FILTER_COUNTER = "bilateral_filter_counter";
    const std::string LD_GAUSSIAN_BLUR_RADIUS = "gaussian_blur_radius";
    const std::string LD_GAUSSIAN_BLUR_STANDARD_DEV = "gaussian_blur_standard_deviation";
    const std::string LD_GAUSSIAN_BLUR_COUNTER = "gaussian_blur_counter";
    const std::string LD_INITIAL_THRESHOLD = "initial_threshold";
    const std::string LD_MAXIMAL_COLOR_AREA = "mimimal_color_area";
    const std::string LD_MAX_NUMBER_OF_COLORS = "max_number_of_colors";
    const std::string LD_DIAMETER = "diameter";
    const std::string LD_SIGMA_COLOR = "sigma_color";
    const std::string LD_SIGMA_SPACE = "sigma_space";

    // Create document
    rapidxml::xml_document<> document;

    // Read XML file
    std::ifstream xmlFile( XML_FILENAME.c_str() );
    std::stringstream buffer;
    buffer << xmlFile.rdbuf();
    xmlFile.close();
    std::string xmlFileContent( buffer.str() );

    // Parse document
    document.parse<0>(&xmlFileContent[0]);

    // Get root element
    rapidxml::xml_node<> *root = document.first_node();

    // Get background detection attributes
    rapidxml::xml_node<> *backgroundDetectionNode = root->first_node( BACKGROUND_DETECTION_NODE.c_str() );
    rapidxml::xml_node<> *bdEnabled
        = backgroundDetectionNode->first_node( BD_ENABLED.c_str() );
    rapidxml::xml_node<> *bdGaussianBlurRadius
        = backgroundDetectionNode->first_node( BD_GAUSSIAN_BLUR_RADIUS.c_str() );
    rapidxml::xml_node<> *bdGaussianBlurStandardDev
        = backgroundDetectionNode->first_node( BD_GAUSSIAN_BLUR_STANDARD_DEVIATION.c_str() );
    rapidxml::xml_node<> *bdDiameter
        = backgroundDetectionNode->first_node( BD_DIAMETER.c_str() );
    rapidxml::xml_node<> *bdSigmaColor
        = backgroundDetectionNode->first_node( BD_SIGMA_COLOR.c_str() );
    rapidxml::xml_node<> *bdSigmaSpace
        = backgroundDetectionNode->first_node( BD_SIGMA_SPACE.c_str() );
    rapidxml::xml_node<> *bdDilationAndErosionSize
        = backgroundDetectionNode->first_node( BD_DILATION_AND_EROSION_SIZE.c_str() );
    rapidxml::xml_node<> *bdDilationAndErosionCounter
        = backgroundDetectionNode->first_node( BD_DILATION_AND_EROSION_COUNTER.c_str() );
    rapidxml::xml_node<> *bdWindowWidth
        = backgroundDetectionNode->first_node( BD_WINDOW_WIDTH.c_str() );
    rapidxml::xml_node<> *bdMaxNumberOfColors
        = backgroundDetectionNode->first_node( BD_MAX_NUMBER_OF_COLORS.c_str() );

    // Fill parameters
    ColorSegmentationParams& colorSegmentation = parameters_.getColorSegmentationParams();
    if( "false" == std::string( bdEnabled->value() ) )
    {
        colorSegmentation.enabled = false;
    }
    else
    {
        colorSegmentation.enabled = true;
    }
    colorSegmentation.gaussianBlurRadius = atoi( bdGaussianBlurRadius->value() );
    colorSegmentation.gaussianBlurStandardDeviation = atoi( bdGaussianBlurStandardDev->value() );
    colorSegmentation.diameter = atoi( bdDiameter->value() );
    colorSegmentation.sigmaColor = atoi( bdSigmaColor->value() );
    colorSegmentation.sigmaSpace = atoi( bdSigmaSpace->value() );
    colorSegmentation.dilationAndErosionSize = atoi( bdDilationAndErosionSize->value() );
    colorSegmentation.dilationAndErosionCounter = atoi( bdDilationAndErosionCounter->value() );
    colorSegmentation.windowWidth = atoi( bdWindowWidth->value() );
    colorSegmentation.maxNumberOfColors = atoi( bdMaxNumberOfColors->value() );

    // Get Line detection attributes
    rapidxml::xml_node<> *lineDetectionNode = root->first_node( LINE_DETECTION_NODE.c_str() );
    rapidxml::xml_node<> *ldEnabled
        = backgroundDetectionNode->first_node( LD_ENABLED.c_str() );
    rapidxml::xml_node<> *ldthresholdValue =
        lineDetectionNode->first_node( LD_THRESHOLD_VALUE.c_str() );
    rapidxml::xml_node<> *ldInsharpMaskStandardDev =
        lineDetectionNode->first_node( LD_UNSHARP_MASK_STANDARD_DEV.c_str() );
    rapidxml::xml_node<> *ldDenoisingFactor =
        lineDetectionNode->first_node( LD_DENOISING_FACTOR.c_str() );
    rapidxml::xml_node<> *ldBilateralFilterCounter =
        lineDetectionNode->first_node( LD_BILATERAL_FILTER_COUNTER.c_str() );
    rapidxml::xml_node<> *ldGaussianBlurRadius =
        lineDetectionNode->first_node( LD_GAUSSIAN_BLUR_RADIUS.c_str() );
    rapidxml::xml_node<> *ldGaussianBlurStandardDev =
        lineDetectionNode->first_node( LD_GAUSSIAN_BLUR_STANDARD_DEV.c_str() );
    rapidxml::xml_node<> *ldGaussianBlurCounter =
        lineDetectionNode->first_node( LD_GAUSSIAN_BLUR_COUNTER.c_str() );
    rapidxml::xml_node<> *ldInitialThreshold =
        lineDetectionNode->first_node( LD_INITIAL_THRESHOLD.c_str() );
    rapidxml::xml_node<> *ldMaximalColorArea =
        lineDetectionNode->first_node( LD_MAXIMAL_COLOR_AREA.c_str() );
    rapidxml::xml_node<> *ldMaxNumberOfColors =
        lineDetectionNode->first_node( LD_MAX_NUMBER_OF_COLORS.c_str() );
    rapidxml::xml_node<> *ldDiameter =
        lineDetectionNode->first_node( LD_DIAMETER.c_str() );
    rapidxml::xml_node<> *ldSigmaColor =
        lineDetectionNode->first_node( LD_SIGMA_COLOR.c_str() );
    rapidxml::xml_node<> *ldSigmaSpace =
        lineDetectionNode->first_node( LD_SIGMA_SPACE.c_str() );

    // Fill parameters
    LineDetectionParams& lineDetectionParams = parameters_.getLineDetectionParams();
    if( "false" == std::string( ldEnabled->value() ) )
    {
        lineDetectionParams.enabled = false;
    }
    else
    {
        lineDetectionParams.enabled = true;
    }
    lineDetectionParams.thresholdValue = atoi( ldthresholdValue->value() );
    lineDetectionParams.unsharpMaskStandardDeviation = atoi( ldInsharpMaskStandardDev->value() );
    lineDetectionParams.denoisingFactor = atoi( ldDenoisingFactor->value() );
    lineDetectionParams.bilateralFilterCounter = atoi( ldBilateralFilterCounter->value() );
    lineDetectionParams.gaussianBlurRadius = atoi( ldGaussianBlurRadius->value() );
    lineDetectionParams.gaussianBlurStandardDeviation = atoi( ldGaussianBlurStandardDev->value() );
    lineDetectionParams.gaussianBlurCounter = atoi( ldGaussianBlurCounter->value() );
    lineDetectionParams.initialThreshold = atoi( ldInitialThreshold->value() );
    lineDetectionParams.mimimalColorArea = atoi( ldMaximalColorArea->value() );
    lineDetectionParams.maxNumberOfColors = atoi( ldMaxNumberOfColors->value() );
    lineDetectionParams.diameter = atoi( ldDiameter->value() );
    lineDetectionParams.sigmaColor = atoi( ldSigmaColor->value() );
    lineDetectionParams.sigmaSpace = atoi( ldSigmaSpace->value() );
}

} // namespace filehandler
