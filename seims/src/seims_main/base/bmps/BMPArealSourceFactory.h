/*!
 * \file BMPArealSourceFactory.h
 * \brief Areal source pollution and BMP factory
 *
 * Changelog:
 *   - 1. 2016-04-12 - lj - Code reformat.
 *
 * \author Liang-Jun Zhu
 * \date Aug 2016
 */
#ifndef SEIMS_BMP_AREALSOURCE_H
#define SEIMS_BMP_AREALSOURCE_H

#include "basic.h"
#include "data_raster.h"
#include "BMPFactory.h"

using namespace ccgl;
using namespace data_raster;
using namespace bmps;

namespace bmps {
/*!
 * \class bmps::ArealSourceLocations
 * \brief Base class of point BMP, mainly store location related parameters
 *
 */
class ArealSourceLocations: Interface {
public:
    /*!
     * \brief Constructor, read and calculate areal BMP locations related parameters from Raster
     */
    ArealSourceLocations(const bson_t*& bsonTable, bson_iter_t& iter);

    /// load valid cells index
    void SetValidCells(int n, float* mgtFieldIDs);

    /// Output
    void Dump(std::ostream* fs);

    /// Get point source ID
    int GetArealSourceID() { return m_arealSrcID; }

    /// name
    string GetArealSourceName() { return m_name; }

    /// index of valid cells
    vector<int>& GetCellsIndex() { return m_cellsIndex; }

    /// Located subbasin ID
    int GetValidCells() { return m_nCells; }

    /// size
    float GetSize() { return m_size; }

private:
    /// ID of point source
    int m_arealSrcID;
    /// name
    string m_name;
    /// valid cell number
    int m_nCells;
    /// index of valid cells
    vector<int> m_cellsIndex;
    /// size, used to calculate amount of pollutants
    float m_size;
};

/*!
 * \class bmps::ArealSourceMgtParams
 * \brief Point source management parameters
 *
 */
class ArealSourceMgtParams: Interface {
public:
    /*!
     * \brief Constructor, parse areal source management parameters from bson object
     * \param[in] bsonTable Query result from MongoDB
     * \param[in] iter Iterator of bsonTab
     */
    ArealSourceMgtParams(const bson_t*& bsonTable, bson_iter_t& iter);

    /// Destructor
    //~ArealSourceMgtParams() = default;

    /// Output
    void Dump(std::ostream* fs);

    /// Get start date of the current management operation
    time_t GetStartDate() { return m_startDate; }

    /// Get end date
    time_t GetEndDate() { return m_endDate; }

    /// Get sequence number
    int GetSequence() { return m_seqence; }

    /// Get subScenario name
    string GetSubScenarioName() { return m_name; }

    /// Get water volume
    float GetWaterVolume() { return m_waterVolume; }

    /// Get sediment concentration
    float GetSedment() { return m_sedimentConc; }

    /// Get sediment concentration
    float GetTN() { return m_TNConc; }

    /// Get NO3 concentration
    float GetNO3() { return m_NO3Conc; }

    /// Get NH4 concentration
    float GetNH4() { return m_NH4Conc; }

    /// Get OrgN concentration
    float GetOrgN() { return m_OrgNConc; }

    /// Get TP concentration
    float GetTP() { return m_TPConc; }

    /// Get MinP concentration
    float GetMinP() { return m_SolPConc; }

    /// Get OrgP concentration
    float GetOrgP() { return m_OrgPConc; }

    /// Get COD concentration
    float GetCOD() { return m_COD; }

private:
    /// subSecenario name
    string m_name;
    /// Sequence number of management
    int m_seqence;
    /// Start date
    time_t m_startDate;
    /// End date
    time_t m_endDate;
    ///  Q	Water volume	m3/'size'/day ('Size' may be one chicken or so, depends on ARSRC code)
    float m_waterVolume;
    /// Sed	Sediment concentration	kg/'size'/day
    float m_sedimentConc;
    ///	TN	Total Nitrogen concentration	kg/'size'/day
    float m_TNConc;
    ///	NO3	Nitrate Nitrogen concentration	kg/'size'/day
    float m_NO3Conc;
    /// NH4	Ammonium Nitrogen concentration	kg/'size'/day
    float m_NH4Conc;
    ///	ORGN	Organic Nitrogen concentration	kg/'size'/day
    float m_OrgNConc;
    ///	TP	Total phosphorus concentration	kg/'size'/day
    float m_TPConc;
    ///	MINP	Mineral phosphorus concentration	kg/'size'/day
    float m_SolPConc;
    ///	ORGP	Organic phosphorus concentration	kg/'size'/day
    float m_OrgPConc;
    /// cod
    float m_COD;
};

/*!
 * \class bmps::BMPArealSrcFactory
 * \brief Base class of areal source BMPs.
 * Such as chicken farm
 *
 */
class BMPArealSrcFactory: public BMPFactory {
public:
    /// Constructor
    BMPArealSrcFactory(int scenarioId, int bmpId, int subScenario,
                       int bmpType, int bmpPriority, vector<string>& distribution,
                       const string& collection, const string& location);

    /// Destructor
    virtual ~BMPArealSrcFactory();

    /// Load BMP parameters from MongoDB
    void loadBMP(MongoClient* conn, const string& bmpDBName) OVERRIDE;

    /// Output
    void Dump(std::ostream* fs) OVERRIDE;

    /*!
     * \brief Load areal BMP location related parameters from MongoDB
     * \param[in] conn MongoClient instance
     * \param[in] bmpDBName BMP Scenario database
     */
    void ReadArealSourceManagements(MongoClient* conn, const string& bmpDBName);

    /*!
     * \brief Load areal BMP location related parameters from MongoDB
     * \param[in] conn MongoClient instance
     * \param[in] bmpDBName BMP Scenario database
     */
    void ReadArealSourceLocations(MongoClient* conn, const string& bmpDBName);

    /// Set raster data if needed
    void setRasterData(map<string, FloatRaster*>& sceneRsMap) OVERRIDE;

    /// Get management fields data
    float* GetRasterData() OVERRIDE { return m_mgtFieldsRs; }

    string GetArealSrcDistName() { return m_arealSrcDistName; }

    vector<int>& GetArealSrcMgtSeqs() { return m_arealSrcMgtSeqs; }

    map<int, ArealSourceMgtParams*>& GetArealSrcMgtMap() { return m_arealSrcMgtMap; }

    vector<int>& GetArealSrcIDs() { return m_arealSrcIDs; }

    bool GetLocationLoadStatus() { return m_loadedMgtFieldIDs; }

    void SetArealSrcLocsMap(int n, float* mgtField);

    map<int, ArealSourceLocations*>& GetArealSrcLocsMap() { return m_arealSrcLocsMap; }

private:
    /// areal source code
    int m_arealSrc;
    /// Collection of point source management parameters
    string m_arealSrcMgtTab;
    /// Sequences of point source managements
    vector<int> m_arealSrcMgtSeqs;
    /* Map of areal source management parameters
     * Key: Scheduled sequence number, unique
     * Value: Pointer of ArealSourceMgtParams instance
     */
    map<int, ArealSourceMgtParams*> m_arealSrcMgtMap;
    /// core file name of areal source locations, such as MGT_FIELDS
    string m_arealSrcDistName;
    /// distribution data of areal source locations
    float* m_mgtFieldsRs;
    /// areal source distribution table
    string m_arealSrcDistTab;
    /// Field IDs of areal source of current subScenario
    vector<int> m_arealSrcIDs;
    /// flag
    bool m_loadedMgtFieldIDs;
    /* Map of areal source location related parameters
     * Key: ARSRCID, unique
     * Value: Pointer of ArealBMPLocations instance
     */
    map<int, ArealSourceLocations*> m_arealSrcLocsMap;
};
}
#endif /* SEIMS_BMP_AREALSOURCE_H */
