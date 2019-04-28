#ifndef HGL_GRAPH_VULKAN_SHADER_MODULE_MANAGE_INCLUDE
#define HGL_GRAPH_VULKAN_SHADER_MODULE_MANAGE_INCLUDE

#include"VK.h"
#include<hgl/type/Map.h>
#include<hgl/type/BaseString.h>
VK_NAMESPACE_BEGIN
class Device;
class ShaderModule;
class VertexShaderModule;
class Material;

/**
 * Shader模块管理器<br>
 * 所有的shader模块均由它创建和释放
 * 该管理器在一个设备下仅有一个，它负责管理所有的shader(仅vs/fs/gs等单个，非组合体)
 */
class ShaderModuleManage
{
    Device *device;

    int shader_count;
    Map<int,ShaderModule *> shader_list;

public:

    ShaderModuleManage(Device *dev)
    {
        device=dev;
        shader_count=0;
    }

    ~ShaderModuleManage();

    const ShaderModule *CreateShader(const VkShaderStageFlagBits shader_stage_bit,const void *spv_data,const uint32_t spv_size);
    const ShaderModule *CreateShader(const VkShaderStageFlagBits shader_stage_bit,const UTF8String &filename);

#define ADD_SHADER_FUNC(sn,vk_name)   const ShaderModule *Create##sn##Shader(const void *spv_data,const uint32_t spv_size){return CreateShader(VK_SHADER_STAGE_##vk_name##_BIT,spv_data,spv_size);}
    ADD_SHADER_FUNC(Vertex,     VERTEX)
    ADD_SHADER_FUNC(Fragment,   FRAGMENT)
    ADD_SHADER_FUNC(Geometry,   GEOMETRY)
    ADD_SHADER_FUNC(TessCtrl,   TESSELLATION_CONTROL)
    ADD_SHADER_FUNC(TessEval,   TESSELLATION_EVALUATION)
    ADD_SHADER_FUNC(Compute,    COMPUTE)
#undef ADD_SHADER_FUNC

#define ADD_NV_SHADER_FUNC(sn,vk_name)   const ShaderModule *Create##sn##Shader(const void *spv_data,const uint32_t spv_size){return CreateShader(VK_SHADER_STAGE_##vk_name##_BIT_NV,spv_data,spv_size);}
    ADD_NV_SHADER_FUNC(Raygen,      RAYGEN);
    ADD_NV_SHADER_FUNC(AnyHit,      ANY_HIT);
    ADD_NV_SHADER_FUNC(ClosestHit,  CLOSEST_HIT);
    ADD_NV_SHADER_FUNC(MissBit,     MISS);
    ADD_NV_SHADER_FUNC(Intersection,INTERSECTION);
    ADD_NV_SHADER_FUNC(Callable,    CALLABLE);
    ADD_NV_SHADER_FUNC(Task,        TASK);
    ADD_NV_SHADER_FUNC(Mesh,        MESH);
#undef ADD_NV_SHADER_FUNC

    const ShaderModule *GetShader       (int);
    bool                ReleaseShader   (const ShaderModule *);

    Material *    CreateMaterial(const VertexShaderModule *vertex_shader_module,const ShaderModule *fragment_shader_module)const;
    Material *    CreateMaterial(const UTF8String &vertex_shader_filename,const UTF8String &fragment_shader_filename)
    {
        const ShaderModule *vs=CreateShader(VK_SHADER_STAGE_VERTEX_BIT,vertex_shader_filename);

        if(!vs)
            return(nullptr);

        const ShaderModule *fs=CreateShader(VK_SHADER_STAGE_FRAGMENT_BIT,fragment_shader_filename);

        if(!fs)
        {
            ReleaseShader(vs);
            return(nullptr);
        }

        return(CreateMaterial((VertexShaderModule *)vs,fs));
    }
};//class ShaderModuleManage
VK_NAMESPACE_END
#endif//HGL_GRAPH_VULKAN_SHADER_MODULE_MANAGE_INCLUDE
