﻿#ifndef HGL_GRAPH_VULKAN_INCLUDE
#define HGL_GRAPH_VULKAN_INCLUDE

#include<hgl/type/List.h>
#include<vulkan/vulkan.h>
#include<hgl/math/Math.h>
#include<iostream>
#include<hgl/graph/vulkan/VKFormat.h>
#include<hgl/graph/vulkan/VKPrimivate.h>

#define VK_NAMESPACE hgl::graph::vulkan
#define VK_NAMESPACE_BEGIN  namespace hgl{namespace graph{namespace vulkan{
#define VK_NAMESPACE_END    }}}

VK_NAMESPACE_BEGIN

class Instance;
class PhysicalDevice;
class Device;
class ImageView;
class Framebuffer;

class Texture;
class Texture1D;
class Texture1DArray;
class Texture2D;
class Texture2DArray;
class Texture3D;
class TextureCubemap;
class TextureCubemapArray;

class Sampler;

class Buffer;
class VertexBuffer;
class IndexBuffer;

class CommandBuffer;
class RenderPass;
class Fence;
class Semaphore;

class ShaderModule;
class ShaderModuleManage;
class VertexShaderModule;
class Material;
class PipelineLayout;
class Pipeline;
class DescriptorSets;
class VertexAttributeBinding;

class Renderable;

using CharPointerList=hgl::List<const char *>;

enum class ShaderType
{
    Vertex      =VK_SHADER_STAGE_VERTEX_BIT,
    TessControl =VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT,
    TessEval    =VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT,
    Geometry    =VK_SHADER_STAGE_GEOMETRY_BIT,
    Fragment    =VK_SHADER_STAGE_FRAGMENT_BIT,
    Compute     =VK_SHADER_STAGE_COMPUTE_BIT
};//

struct PushConstant256
{
    Matrix4f projection;
    Matrix4f modelview;
    Matrix4f mvp;
    Matrix3f normal;
};//

struct PushConstant128
{
    Matrix4f projection;
    Matrix4f modelview;
};//

#ifdef _DEBUG
bool CheckStrideBytesByFormat();                ///<检验所有数据类型长度数组是否符合规则
#endif//_DEBUG

uint32_t GetStrideByFormat(const VkFormat &);   ///<根据数据类型获取访类型单个数据长度字节数

inline void debug_out(const hgl::List<VkLayerProperties> &layer_properties)
{
    const int property_count=layer_properties.GetCount();

    if(property_count<=0)return;

    const VkLayerProperties *lp=layer_properties.GetData();

    for(int i=0;i<property_count;i++)
    {
        std::cout<<"Layer Propertyes ["<<i<<"] : "<<lp->layerName<<" desc: "<<lp->description<<std::endl;
        ++lp;
    }
}

inline void debug_out(const hgl::List<VkExtensionProperties> &extension_properties)
{
    const int extension_count=extension_properties.GetCount();

    if(extension_count<=0)return;

    VkExtensionProperties *ep=extension_properties.GetData();
    for(int i=0;i<extension_count;i++)
    {
        std::cout<<"Extension Propertyes ["<<i<<"] : "<<ep->extensionName<<" ver: "<<ep->specVersion<<std::endl;
        ++ep;
    }
}
VK_NAMESPACE_END
#endif//HGL_GRAPH_VULKAN_INCLUDE
