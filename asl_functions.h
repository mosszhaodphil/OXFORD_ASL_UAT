/*   asl_functions.h various functions for the manipulation of ASL data

    Michael Chappell - FMRIB Image Analysis Group

    Moss Zhao - IBME Quantitative Biomedical Inference (QuBIc) Group

    Copyright (C) 2015 University of Oxford  */

/*   CCOPYRIGHT   */

#if !defined(asl_functions_h)
#define asl_functions_h

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "newimage/newimageall.h"
#include "miscmaths/miscmaths.h"

using namespace MISCMATHS;
using namespace NEWIMAGE;

namespace OXASL {
 
  void data2stdform(Matrix& datamtx, vector<Matrix>& asldata, int ntis, bool isblocked, bool ispairs);
  void stdform2data(vector<Matrix>& asldata, Matrix& datareturn, bool outblocked, bool outpairs);

  // separate the pairs in the data (into seprate standard form items)
  void separatepairs(vector<Matrix>& asldata, vector<Matrix>& asldataodd, vector<Matrix>& asldataeven);
  void mergepairs(vector<Matrix>& asldata, vector<Matrix>& asldataodd, vector<Matrix>&asldataeven);

  // mean the data at each TI
  void timeans(vector<Matrix>& asldata, vector<Matrix>& aslmean);
  // output data having taken mean at each TI
  void timeanout(vector<Matrix>& asldata,  volume<float>& mask, string fname, bool outpairs);

  // output data split into individual TIs
  void splitout(vector<Matrix>& asldata, volume<float>& mask, string froot);

  // output epochs of data
  void epochout(vector<Matrix>& asldata, volume<float>& mask, string froot, int epadv, int epol, bool outpairs, bool tiunit=false);
  // generate epochs
  void genepochs(vector<Matrix>& asldata, vector<Matrix>& epochreturn, int epadv, int epol);
  // generate TI epochs
  void gentiepochs(Matrix& asldata, vector<Matrix>& epochreturn, int epadv, int epol);

  //output the result of deconvolution with an AIF
  void deconvout(vector<Matrix>& asldata, volume<float>& mask, Matrix& aif, string fname);
  // do SVD convoloution
  ReturnMatrix SVDdeconv(const Matrix& data, const Matrix& aif);
  // create a (simple) convolution matrix
  ReturnMatrix convmtx(const ColumnVector& invec);

  // function to perform partial volume correction by linear regression
  void pvcorr_LR(const volume4D<float>& data, int ndata_in, const volume<float>& mask, const volume<float>& pv_map_gm, const volume<float>& pv_map_wm, int kernel, volume4D<float>& data_pvcorr);

  // PV correction using linear regression (Asllani's method)
  volume<float> correct_pv_lr(const volume<float>& data_in, const volume<float>& mask, const volume<float>& pv_map_gm, const volume<float>& pv_map_wm, int kernel);

  // Function to correct NaN values
  volume<float> correct_NaN(const volume<float>& data_in);

  // function to covert Phillip PAR REC file to Nifty format
  void convert_par_rec_to_nifti(const string file_par, const string file_rec, volume<float>& mask_nifti, volume4D<float>& data_nifti);

  // function to make default mask
  void create_default_mask(volume<float>& mask_nifti);

  // function to make default data nifti file
  void create_default_data_nifti(volume4D<float>& data_nifti);

  float convert_pixel_value_to_floating_point(int pixel_value, float rescale_slope, float rescale_intercept, float scale_slope);

  // function to extrapolate voxels
  void extrapolate(const volume4D<float>& data, int ndata_in, const volume<float>& mask, int neighbour_size, volume4D<float>& data_extrapolated);

  Matrix extrapolate_avg(Matrix data_in, Matrix mask, int neighbour_size);
}

#endif
