/**
 * snasken@77k.eu
 */

#include <boost/asio.hpp>
#include <boost/regex.hpp>
#include <string>
#include <stack>
#include <boost/array.hpp>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/logic/tribool.hpp>
#include <signal.h>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <boost/lexical_cast.hpp>

#include "spaces.h"
#include "cubical_complex.h"
//#include "electrodynamics.h"

typedef CubicalSpaceCompressed< 4, SimpleEuklidianMetricFuint32 > Space4;
typedef Space4::Cube Cube4;
typedef Space4::PointT Point4;

int main(int argc, char* argv[])
{
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: cell_test <netlist>" << std::endl;
            throw(std::runtime_error("Not enough arguments!"));
	}
        static const auto buffer_size = 128 * 1024;
        std::ifstream is(argv[1], std::ios::in | std::ios::   binary);
        if(!is) throw(std::runtime_error("Error opening file! "));


        BLIFParser p(argv[1]);
        p << is;

    }
    catch (std::exception& e)
    {
        std::cerr << "exception: " << e.what() << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cerr << "He's Dead Jim" << std::endl;
    }
    return 0;

}
