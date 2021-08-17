#include "api.h"

#include "SUR_MR.h"
#include "text.h"
#include "MetadataInfo.h"

extern "C" SEIMS_MODULE_API SimulationModule* GetInstance() {
    return new SUR_MR();
}

extern "C" SEIMS_MODULE_API const char* MetadataInformation() {
    MetadataInfo mdi;

    // set the information properties
    mdi.SetAuthor("Junzhi Liu, Zhiqiang Yu, Liangjun Zhu");
    mdi.SetClass(MCLS_SUR_RUNOFF, MCLSDESC_SUR_RUNOFF);
    mdi.SetDescription(MDESC_SUR_MR);
    mdi.SetEmail(SEIMS_EMAIL);
    mdi.SetHelpfile("");
    mdi.SetID(MID_SUR_MR);
    mdi.SetName(MID_SUR_MR);
    mdi.SetVersion("1.5");
    mdi.SetWebsite(SEIMS_SITE);

    mdi.AddParameter(Tag_HillSlopeTimeStep, UNIT_SECOND, DESC_DT_HS, File_Input, DT_Single);
    mdi.AddParameter(VAR_T_SOIL, UNIT_TEMP_DEG, DESC_T_SOIL, Source_ParameterDB, DT_Single);
    mdi.AddParameter(VAR_K_RUN, UNIT_NON_DIM, DESC_K_RUN, Source_ParameterDB, DT_Single);
    mdi.AddParameter(VAR_P_MAX, UNIT_DEPTH_MM, DESC_P_MAX, Source_ParameterDB, DT_Single);
    mdi.AddParameter(VAR_S_FROZEN, UNIT_WAT_RATIO, DESC_S_FROZEN, Source_ParameterDB, DT_Single);

    mdi.AddParameter(VAR_RUNOFF_CO, UNIT_NON_DIM, DESC_RUNOFF_CO, Source_ParameterDB, DT_Raster1D);
    mdi.AddParameter(VAR_MOIST_IN, UNIT_PERCENT, DESC_MOIST_IN, Source_ParameterDB, DT_Raster1D);
    mdi.AddParameter(VAR_SOILLAYERS, UNIT_NON_DIM, DESC_SOILLAYERS, Source_ParameterDB, DT_Raster1D);
    mdi.AddParameter(VAR_SOL_AWC, UNIT_DEPTH_MM, DESC_SOL_AWC, Source_ParameterDB, DT_Raster2D);
    mdi.AddParameter(VAR_SOL_UL, UNIT_DEPTH_MM, DESC_SOL_UL, Source_ParameterDB, DT_Raster2D);
    mdi.AddParameter(VAR_SOL_SUMSAT, UNIT_DEPTH_MM, DESC_SOL_SUMSAT, Source_ParameterDB, DT_Raster1D);

    mdi.AddInput(VAR_NEPR, UNIT_DEPTH_MM, DESC_NEPR, Source_Module, DT_Raster1D);
    mdi.AddInput(VAR_TMEAN, UNIT_TEMP_DEG, DESC_TMEAN, Source_Module, DT_Raster1D);
    mdi.AddInput(VAR_DPST, UNIT_DEPTH_MM, DESC_DPST, Source_Module, DT_Raster1D);
    mdi.AddInput(VAR_SOTE, UNIT_TEMP_DEG, DESC_SOTE, Source_Module, DT_Raster1D);
    mdi.AddInput(VAR_IMPOUND_TRIG, UNIT_NON_DIM, DESC_IMPOUND_TRIG, Source_Module_Optional, DT_Raster1D);
    mdi.AddInput(VAR_POT_VOL, UNIT_DEPTH_MM, DESC_POT_VOL, Source_Module_Optional, DT_Raster1D);

    mdi.AddOutput(VAR_EXCP, UNIT_DEPTH_MM, DESC_EXCP, DT_Raster1D);
    mdi.AddOutput(VAR_INFIL, UNIT_DEPTH_MM, DESC_INFIL, DT_Raster1D);
    mdi.AddOutput(VAR_SOL_ST, UNIT_DEPTH_MM, DESC_SOL_ST, DT_Raster2D);
    mdi.AddOutput(VAR_SOL_SW, UNIT_DEPTH_MM, DESC_SOL_SW, DT_Raster1D);

    // write out the XML file.
    string res = mdi.GetXMLDocument();
    char* tmp = new char[res.size() + 1];
    strprintf(tmp, res.size() + 1, "%s", res.c_str());
    return tmp;
}
