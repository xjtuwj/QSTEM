#include <stdio.h>	/*  ANSI-C libraries */
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include <fstream>

#include <stdexcept>
#include <map>

//#include "boost/shared_ptr.hpp"

#include "stemtypes_fftw3.hpp"
#include "imagelib_fftw3.hpp"
#include "memory_fftw3.hpp"	/* memory allocation routines */

#define _CRTDBG_MAP_ALLOC
#include <stdio.h>	/* ANSI C libraries */
#include <stdlib.h>
#ifdef WIN32
#if _DEBUG
#include <crtdbg.h>
#endif
#endif

CImageIO::CImageIO(int nx, int ny, std::string input_extension, std::string output_extension) :
m_nx(nx),
m_ny(ny)
{
  m_imageReader=GetDataReader(input_extension);
  m_imageWriter=GetDataWriter(output_extension);
};


void CImageIO::WriteRealImage(void **pix, const char *fileName, std::map<std::string, double> &params,
                              std::string comment, std::vector<unsigned> position) {
  m_imageWriter->WriteRealImage((float_tt **)pix, GetShapeVector(), std::string(fileName),
                                position, comment, params);
}

void CImageIO::WriteComplexImage(void **pix, const char *fileName, std::map<std::string, double> &params,
                                 std::string comment, std::vector<unsigned> position) {
  m_imageWriter->WriteComplexImage((complex_tt **)pix, GetShapeVector(), std::string(fileName),
                                   position, comment, params);
}

void CImageIO::ReadImage(void **pix, const char *fileName, std::map<std::string, double> &params,
                         std::string &comment, std::vector<unsigned> position)
{
  
  m_imageReader->ReadImage(pix, fileName, params, comment, position);
}

/*****************************************************************
 * Image header routines
 ****************************************************************/

std::vector<unsigned> CImageIO::GetShapeVector()
{
  std::vector<unsigned> size(2);
  size[0]=m_nx;
  size[1]=m_ny;
  return size;
}
