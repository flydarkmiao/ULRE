#ifndef HGL_GRAPH_VULKAN_VERTEX_ATTRIBUTE_BINDING_INCLUDE
#define HGL_GRAPH_VULKAN_VERTEX_ATTRIBUTE_BINDING_INCLUDE

#include"VK.h"
#include<hgl/type/BaseString.h>
VK_NAMESPACE_BEGIN
class VertexBuffer;
class IndexBuffer;
class Shader;

/**
* ��������״̬ʵ��<br>
* ���������ڴ��ݸ�MaterialInstance,�����Ѿ�ȷ���ö����ʽ������£���Ȼ���޸Ĳ����趨(��instance)��
*/
class VertexAttributeBinding
{
    Shader *shader;
    VkVertexInputBindingDescription *binding_list;

private:

    friend class Shader;

    VertexAttributeBinding(Shader *);

public:

    ~VertexAttributeBinding();

    bool SetInstance(const uint index,bool instance);
    bool SetInstance(const UTF8String &name,bool instance);

    void Write(VkPipelineVertexInputStateCreateInfo &vis)const;
};//class VertexAttributeBinding
VK_NAMESPACE_END
#endif//HGL_GRAPH_VULKAN_VERTEX_ATTRIBUTE_BINDING_INCLUDE
