﻿#ifndef HGL_GRAPH_VULKAN_FORMAT_INCLUDE
#define HGL_GRAPH_VULKAN_FORMAT_INCLUDE

#include<vulkan/vulkan.h>

#define FMT_UNDEFINED   VK_FORMAT_UNDEFINED

#define FMT_RG4UN       VK_FORMAT_R4G4_UNORM_PACK8
#define FMT_RGBA4       VK_FORMAT_R4G4B4A4_UNORM_PACK16
#define FMT_BGRA4       VK_FORMAT_B4G4R4A4_UNORM_PACK16
#define FMT_RGB565      VK_FORMAT_R5G6B5_UNORM_PACK16
#define FMT_BGR565      VK_FORMAT_B5G6R5_UNORM_PACK16
#define FMT_RGB5A1      VK_FORMAT_R5G5B5A1_UNORM_PACK16
#define FMT_BGR5A1      VK_FORMAT_B5G5R5A1_UNORM_PACK16
#define FMT_A1RGB5      VK_FORMAT_A1R5G5B5_UNORM_PACK16

#define FMT_R8UN        VK_FORMAT_R8_UNORM
#define FMT_R8SN        VK_FORMAT_R8_SNORM
#define FMT_R8U         VK_FORMAT_R8_UINT
#define FMT_R8I         VK_FORMAT_R8_SINT
#define FMT_R8s         VK_FORMAT_R8_SRGB

#define FMT_RG8UN       VK_FORMAT_R8G8_UNORM
#define FMT_RG8SN       VK_FORMAT_R8G8_SNORM
#define FMT_RG8U        VK_FORMAT_R8G8_UINT
#define FMT_RG8I        VK_FORMAT_R8G8_SINT
#define FMT_RG8s        VK_FORMAT_R8G8_SRGB

#define FMT_RGBA8UN     VK_FORMAT_R8G8B8A8_UNORM
#define FMT_RGBA8SN     VK_FORMAT_R8G8B8A8_SNORM
#define FMT_RGBA8U      VK_FORMAT_R8G8B8A8_UINT
#define FMT_RGBA8I      VK_FORMAT_R8G8B8A8_SINT
#define FMT_RGBA8s      VK_FORMAT_R8G8B8A8_SRGB

#define FMT_BGRA8UN     VK_FORMAT_B8G8R8A8_UNORM
#define FMT_BGRA8SN     VK_FORMAT_B8G8R8A8_SNORM
#define FMT_BGRA8U      VK_FORMAT_B8G8R8A8_UINT
#define FMT_BGRA8I      VK_FORMAT_B8G8R8A8_SINT
#define FMT_BGRA8s      VK_FORMAT_B8G8R8A8_SRGB

#define FMT_ABGR8UN     VK_FORMAT_A8B8G8R8_UNORM_PACK32
#define FMT_ABGR8SN     VK_FORMAT_A8B8G8R8_SNORM_PACK32
#define FMT_ABGR8U      VK_FORMAT_A8B8G8R8_UINT_PACK32
#define FMT_ABGR8I      VK_FORMAT_A8B8G8R8_SINT_PACK32
#define FMT_ABGR8s      VK_FORMAT_A8B8G8R8_SRGB_PACK32

#define FMT_A2RGB10UN   VK_FORMAT_A2R10G10B10_UNORM_PACK32
#define FMT_A2RGB10SN   VK_FORMAT_A2R10G10B10_SNORM_PACK32
#define FMT_A2RGB10U    VK_FORMAT_A2R10G10B10_UINT_PACK32
#define FMT_A2RGB10I    VK_FORMAT_A2R10G10B10_SINT_PACK32

#define FMT_A2BGR10UN   VK_FORMAT_A2B10G10R10_UNORM_PACK32
#define FMT_A2BGR10SN   VK_FORMAT_A2B10G10R10_SNORM_PACK32
#define FMT_A2BGR10U    VK_FORMAT_A2B10G10R10_UINT_PACK32
#define FMT_A2BGR10I    VK_FORMAT_A2B10G10R10_SINT_PACK32

#define FMT_R16UN       VK_FORMAT_R16_UNORM
#define FMT_R16SN       VK_FORMAT_R16_SNORM
#define FMT_R16U        VK_FORMAT_R16_UINT
#define FMT_R16I        VK_FORMAT_R16_SINT
#define FMT_R16F        VK_FORMAT_R16_SFLOAT

#define FMT_RG16UN      VK_FORMAT_R16G16_UNORM
#define FMT_RG16SN      VK_FORMAT_R16G16_SNORM
#define FMT_RG16U       VK_FORMAT_R16G16_UINT
#define FMT_RG16I       VK_FORMAT_R16G16_SINT
#define FMT_RG16F       VK_FORMAT_R16G16_SFLOAT

#define FMT_RGBA16UN    VK_FORMAT_R16G16B16A16_UNORM
#define FMT_RGBA16SN    VK_FORMAT_R16G16B16A16_SNORM
#define FMT_RGBA16U     VK_FORMAT_R16G16B16A16_UINT
#define FMT_RGBA16I     VK_FORMAT_R16G16B16A16_SINT
#define FMT_RGBA16F     VK_FORMAT_R16G16B16A16_SFLOAT

#define FMT_R32U        VK_FORMAT_R32_UINT
#define FMT_R32I        VK_FORMAT_R32_SINT
#define FMT_R32F        VK_FORMAT_R32_SFLOAT

#define FMT_RG32U       VK_FORMAT_R32G32_UINT
#define FMT_RG32I       VK_FORMAT_R32G32_SINT
#define FMT_RG32F       VK_FORMAT_R32G32_SFLOAT

#define FMT_RGB32U      VK_FORMAT_R32G32B32_UINT
#define FMT_RGB32I      VK_FORMAT_R32G32B32_SINT
#define FMT_RGB32F      VK_FORMAT_R32G32B32_SFLOAT

#define FMT_RGBA32U     VK_FORMAT_R32G32B32A32_UINT
#define FMT_RGBA32I     VK_FORMAT_R32G32B32A32_SINT
#define FMT_RGBA32F     VK_FORMAT_R32G32B32A32_SFLOAT

#define FMT_R64U        VK_FORMAT_R64_UINT
#define FMT_R64I        VK_FORMAT_R64_SINT
#define FMT_R64F        VK_FORMAT_R64_SFLOAT

#define FMT_RG64U       VK_FORMAT_R64G64_UINT
#define FMT_RG64I       VK_FORMAT_R64G64_SINT
#define FMT_RG64F       VK_FORMAT_R64G64_SFLOAT

#define FMT_RGB64U      VK_FORMAT_R64G64B64_UINT
#define FMT_RGB64I      VK_FORMAT_R64G64B64_SINT
#define FMT_RGB64F      VK_FORMAT_R64G64B64_SFLOAT

#define FMT_RGBA64U     VK_FORMAT_R64G64B64A64_UINT
#define FMT_RGBA64I     VK_FORMAT_R64G64B64A64_SINT
#define FMT_RGBA64F     VK_FORMAT_R64G64B64A64_SFLOAT

#define FMT_B10GR11     VK_FORMAT_B10G11R11_UFLOAT_PACK32
#define FMT_E5BGR9      VK_FORMAT_E5B9G9R9_UFLOAT_PACK32

#define FMT_D16UN       VK_FORMAT_D16_UNORM
#define FMT_X8_D24      VK_FORMAT_X8_D24_UNORM_PACK32
#define FMT_D32F        VK_FORMAT_D32_SFLOAT
#define FMT_S8U         VK_FORMAT_S8_UINT
#define FMT_D16UN_S8U   VK_FORMAT_D16_UNORM_S8_UINT
#define FMT_D24UN_S8U   VK_FORMAT_D24_UNORM_S8_UINT
#define FMT_D32F_S8U    VK_FORMAT_D32_SFLOAT_S8_UINT

#endif//HGL_GRAPH_VULKAN_FORMAT_INCLUDE
