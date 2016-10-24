/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
 ** Copyright (c) 2008, UCAR
 ** University Corporation for Atmospheric Research(UCAR)
 ** National Center for Atmospheric Research(NCAR)
 ** Research Applications Program(RAP)
 ** P.O.Box 3000, Boulder, Colorado, 80307-3000, USA
 *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/

/////////////////////////////////////////////////////////////
// Mdv2NcfTrans.hh
//
// Sue Dettling, RAP, NCAR
// P.O.Box 3000, Boulder, CO, 80307-3000, USA
//
// April 2008 
//
///////////////////////////////////////////////////////////////
//
// Mdv2NcfTrans class.
// Translate an MDV file, write out as netCDF.
//
// Holds vectors of FieldData, GridInfo and VlevelInfo.
// 
///////////////////////////////////////////////////////////////////////

#ifndef MDV2NCF_TRANS_HH
#define MDV2NCF_TRANS_HH

#include <string>
#include <vector>
#include <set>
#include <Mdv/DsMdvx.hh>
#include <NcfMdv/NcfMdv.hh>
#include <NcfMdv/GridInfo.hh>
#include <NcfMdv/FieldData.hh>
#include <NcfMdv/VlevelInfo.hh>
#include <netcdfcpp.h>
#include <Radx/RadxFile.hh>
#include <Radx/RadxRay.hh>

#define SMALL_DBL .0000001

using namespace std;

class RadxVol;
class MdvxRadar;

////////////////////////
// 
// Mdv2NcfTrans object extracts data from DsMdvx object and stores
// in objects including GridInfo, FieldData, VlevelInfo.
//
// GridInfo stores projection meta data for a netCDF projection information
// variable, as well as 2D grid information for field datasets.
// and is used to define netCDF dimensions,  coordinate variables, and auxiliary 
// coordinate variables for field datasets.
//
// VlevelInfo objects contain vertical 
// level information and are used to define dimensions and coordinate variables 
// for vertical coordinates.
//
// FieldData objects contain the mdv field data and associate 
// the data to relevant grid,vertical level, and projection information. 

class Mdv2NcfTrans {
  
public:

  /// constructor

  Mdv2NcfTrans();
  
  /// destructor

  ~Mdv2NcfTrans();
 
  /// set global attributes

  void setDebug(bool debug) { _debug = debug; }

  /// perform translation, write file to path
  /// returns 0 on success, -1 on failure
  
  int translate(const DsMdvx &mdv, const string &ncFilePath);
  
  /// perform translation to CfRadial, write file to dir
  /// returns 0 on success, -1 on failure
  /// Use getNcFilePath() to get path of file written
  
  int translateToCfRadial(const DsMdvx &mdv, const string &dir);

  // Convert to Radx volume
  // returns 0 on success, -1 on failure
  
  int convertToRadxVol(const DsMdvx &mdv, RadxVol &vol);
  
  /// set the output file type for polar radar data
  /// default is CF

  void setRadialFileType(DsMdvx::radial_file_type_t val) {
    _radialFileType = val;
  }

  /// after translation, get reference to NcFile object etc

  const NcFile *getNcFile() { return _ncFile; }
  const string &getNcFilePath() { return _ncFilePath; }
  
  /// Clear the data, ready for reuse
  
  void clearData();
    
  /// clear error string
  
  void clearErrStr();

  /// Get the Error String. This has contents when an error is returned.
  
  string getErrStr() const { return _errStr; }

protected:  

  bool _debug;
  const DsMdvx *_mdv;
  
  string _ncFilePath;
  NcFile *_ncFile;
  NcFile::FileFormat _ncFormat;
  RadxFile::netcdf_format_t _radxNcFormat;
  NcError *_ncErr;
  bool _isXSect;
  bool _isPolar;
  bool _isRhi;

  /// error string

  string _errStr;

  /// grid info, vert level info and field data

  vector <GridInfo*> _gridInfo;
  vector <VlevelInfo*> _vlevelInfo;
  vector <FieldData*> _fieldData;

  /// times

  time_t  _timeBegin;
  time_t  _timeEnd;
  time_t  _timeCentroid;
  time_t  _timeExpire;
  time_t  _timeGen;
  time_t  _timeValid;
  time_t _forecastTime;
  time_t _leadTime;
  bool _isForecast;

  /// mdv strings

  string _datasetInfo;
  string _datasetName;
  string _datasetSource;
  
  /// netCDF variables

  NcDim *_timeDim;
  NcDim *_boundsDim;
  vector<NcDim*> _chunkDims;

  NcVar *_timeVar;
  NcVar *_forecastRefTimeVar;
  NcVar *_forecastPeriodVar;
  NcVar *_startTimeVar;
  NcVar *_stopTimeVar;
  NcVar *_timeBoundsVar;
  vector<NcVar*> _chunkVars;

  bool _outputLatlonArrays;

  /// File type for polar radar and lidar

  DsMdvx::radial_file_type_t _radialFileType;

  /// CfRadial-specific support

  vector<int> _uniformFieldIndexes; /* for CfRadial, can only convert fields
                                     * with uniform geometry */
  /// init variables
  
  void _initVars();

  /// set translation parameters

  void _setTransParams();

  /// Parse Mdv data and record time information and create 
  /// unique FieldData, GridInfo, and VlevelInfo
  /// objects as necessary. 

  int _parseMdv();

  /// open netcdf file
  /// create error object so we can handle errors
  /// Returns 0 on success, -1 on failure

  int _openNcFile(const string &path);

  /// close netcdf file if open
  /// remove error object if it exists
  
  void _closeNcFile();

  /// write data to netCDF file
  /// Returns 0 on success, -1 on failure

  int _writeNcFile();
  
  /// add variables and attributes for projection

  int _addGlobalAttributes();

  /// Add NcDims to the NetCDF file. We loop through the
  /// GridInfo objects and record the dimensions of the
  /// x and y coordinates. Then we loop through the VlevelInfo
  /// objects and record the dimensions of the vertical coordinates
  
  int _addDimensions();

  /// add variables and attributes for coordinates
  
  int _addCoordinateVariables();
  int _addVsectCoordinateVariables();

  /// add variables and attributes for projection
  
  int _addProjectionVariables();

  /// add time variables

  int _addTimeVariables();

  /// add field data variables

  int _addFieldDataVariables();

  /// add variable for MDV master header
  
  int _addMdvMasterHeaderVariable();

  /// add MDV chunk variables

  int _addMdvChunkVariables();

  /// add radar global attributes

  int _addRadarGlobalAttributes(const MdvxRadar &radar);

  /// write variables to the NcFile
  
  int  _putCoordinateVariables();
  int  _putFieldDataVariables();
  int  _putTimeVariables();
  int  _putMdvChunkVariables();

  /// CfRadial support

  void _cfRadialSetVolParams(RadxVol &vol);
  void _findFieldsWithUniformGeom();
  void _cfRadialSetRadarParams(RadxVol &vol);
  void _cfRadialSetCalib(RadxVol &vol);
  void _cfRadialAddFields(RadxVol &vol);
  void _cfRadialAddRays(RadxVol &vol);
  void _addFieldsToRays(RadxVol &vol, vector<RadxRay *> rays);
  void _cfRadialAddSweeps(RadxVol &vol);

  Radx::SweepMode_t _getRadxSweepMode(int dsrScanMode);
  Radx::PolarizationMode_t _getRadxPolarizationMode(int dsrPolMode);
  Radx::FollowMode_t _getRadxFollowMode(int dsrMode);
  Radx::PrtMode_t _getRadxPrtMode(int dsrMode);

private:

  set<string, less<string> > _fieldNameSet;

  string _getCfCompliantName(const string &requestedName);
  string _getUniqueFieldName(const string &requestedName);

};

#endif
