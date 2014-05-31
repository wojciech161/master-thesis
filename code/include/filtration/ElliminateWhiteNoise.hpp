#ifndef FILTRATION_ELLIMINATE_WHITE_NOISE_HPP_
#define FILTRATION_ELLIMINATE_WHITE_NOISE_HPP_

#include "IFiltrationAlgorithm.hpp"

namespace filtration
{

class ElliminateWhiteNoise : public IFiltrationAlgorithm
    {
    public:
        ElliminateWhiteNoise( int );
        ~ElliminateWhiteNoise();
    
        boost::shared_ptr<cv::Mat> apply( boost::shared_ptr<cv::Mat> ) const;

    private:
        int denoisingFactor_;
    };    

}

#endif
