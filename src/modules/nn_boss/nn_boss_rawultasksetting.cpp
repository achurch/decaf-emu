#include "nn_boss.h"
#include "nn_boss_rawultasksetting.h"
#include "nn_boss_result.h"

namespace nn
{

namespace boss
{

ghs::VirtualTableEntry *
RawUlTaskSetting::VirtualTable = nullptr;

ghs::TypeDescriptor *
RawUlTaskSetting::TypeInfo = nullptr;

RawUlTaskSetting::RawUlTaskSetting()
{
   mVirtualTable = RawUlTaskSetting::VirtualTable;

   mRawUlUnk1 = 0;
   mRawUlUnk2 = 0;
   mRawUlUnk3 = 0;
   std::memset(mRawUlData, 0, 0x200);
}

RawUlTaskSetting::~RawUlTaskSetting()
{
}

nn::Result
RawUlTaskSetting::RegisterPreprocess(uint32_t, nn::boss::TitleID *id, const char *)
{
   return nn::boss::Success;
}

void
RawUlTaskSetting::RegisterPostprocess(uint32_t, nn::boss::TitleID *id, const char *, nn::Result *)
{
}

void Module::registerRawUlTaskSettingFunctions()
{
   RegisterKernelFunctionConstructor("__ct__Q3_2nn4boss16RawUlTaskSettingFv", RawUlTaskSetting);
   RegisterKernelFunctionDestructor("__dt__Q3_2nn4boss16RawUlTaskSettingFv", RawUlTaskSetting);
   RegisterKernelFunctionName("RegisterPreprocess__Q3_2nn4boss16RawUlTaskSettingFUiQ3_2nn4boss7TitleIDPCc", &RawUlTaskSetting::RegisterPreprocess);
   RegisterKernelFunctionName("RegisterPostprocess__Q3_2nn4boss16RawUlTaskSettingFUiQ3_2nn4boss7TitleIDPCcQ2_2nn6Result", &RawUlTaskSetting::RegisterPostprocess);
}

void Module::initialiseRawUlTaskSetting()
{
   RawUlTaskSetting::TypeInfo = ghs::internal::makeTypeDescriptor("nn::boss::RawUlTaskSetting", {
      { NetTaskSetting::TypeInfo, 0x1600 },
   });

   RawUlTaskSetting::VirtualTable = ghs::internal::makeVirtualTable({
      { 0, RawUlTaskSetting::TypeInfo },
      { 0, findExport("__dt__Q3_2nn4boss16RawUlTaskSettingFv") },
      { 0, findExport("RegisterPreprocess__Q3_2nn4boss16RawUlTaskSettingFUiQ3_2nn4boss7TitleIDPCc") },
      { 0, findExport("RegisterPostprocess__Q3_2nn4boss16RawUlTaskSettingFUiQ3_2nn4boss7TitleIDPCcQ2_2nn6Result") },
   });
}

}  // namespace boss

}  // namespace nn
