#pragma once

#ifdef __cplusplus
extern "C" {
#endif

	#include "common/api_common.h"

	XVMEXT_API_CALL int32_t BWXML_UnpackW(_In_ const wchar_t* xml_in, _In_ const wchar_t* xml_out);

#ifdef __cplusplus
}
#endif
