#include<hgl/graph/vulkan/VKShaderModule.h>
#include<hgl/graph/vulkan/VKVertexAttributeBinding.h>
#include<hgl/graph/vulkan/VKShaderParse.h>

VK_NAMESPACE_BEGIN
ShaderModule::ShaderModule(int id,VkPipelineShaderStageCreateInfo *sci,const ShaderParse *sp)
{
    shader_id=id;
    ref_count=0;

    stage_create_info=sci;

    ParseUBO(sp);
}

ShaderModule::~ShaderModule()
{
    delete stage_create_info;
}

void ShaderModule::ParseUBO(const ShaderParse *parse)
{
    for(const auto &ubo:parse->GetUBO())
    {
        const UTF8String &  name    =parse->GetName(ubo);
        const uint          binding =parse->GetBinding(ubo);

        ubo_map.Add(name,binding);
        ubo_list.Add(binding);
    }
}

void VertexShaderModule::ParseVertexInput(const ShaderParse *parse)
{
    const auto &stage_inputs=parse->GetStageInput();

    attr_count=stage_inputs.size();
    binding_list=new VkVertexInputBindingDescription[attr_count];
    attribute_list=new VkVertexInputAttributeDescription[attr_count];

    VkVertexInputBindingDescription *bind=binding_list;
    VkVertexInputAttributeDescription *attr=attribute_list;

    uint32_t binding_index=0;

    for(const auto &si:stage_inputs)
    {
        const VkFormat                  format  =parse->GetFormat(si);                //ע�������ʽ�п��ܻ����������(�������ѹ����ʽ)
        const UTF8String &              name    =parse->GetName(si);

        bind->binding   =binding_index;                 //binding��Ӧ��vkCmdBindVertexBuffer�����õĻ����������кţ�����������ֱ����0��ʼ�����ҽ������С�
                                                        //��VertexInput���У�buf_list��Ҫ�ϸ��ձ���bindingΪ���к�����
        bind->stride    =GetStrideByFormat(format);
        bind->inputRate =VK_VERTEX_INPUT_RATE_VERTEX;

        //binding��Ӧ���ǵڼ�������������
        //ʵ��ʹ��һ��binding���԰󶨶��attrib
        //������һ�����д���{pos,color}�����������ݣ�����Ҫ����attrib
        //�������ǵ�����У���֧��һ��������һ��attrib

        attr->binding   =binding_index;
        attr->location  =parse->GetLocation(si);                                        //��ֵ��Ӧshader�е�layout(location=
        attr->format    =format;
        attr->offset    =0;

        stage_input_locations.Add(name,attr);

        ++attr;
        ++bind;
        ++binding_index;
    }
}

VertexShaderModule::~VertexShaderModule()
{
    if(vab_sets.GetCount()>0)
    {
        //�������õģ����Ǹ�����
    }

    SAFE_CLEAR_ARRAY(binding_list);
    SAFE_CLEAR_ARRAY(attribute_list);
}

const int VertexShaderModule::GetLocation(const UTF8String &name)const
{
    if(name.IsEmpty())return -1;

    VkVertexInputAttributeDescription *attr;

    if(!stage_input_locations.Get(name,attr))
        return -1;

    return attr->location;
}

const int VertexShaderModule::GetBinding(const UTF8String &name)const
{
    if(name.IsEmpty())return -1;

    VkVertexInputAttributeDescription *attr;

    if(!stage_input_locations.Get(name,attr))
        return -1;

    return attr->binding;
}

VertexAttributeBinding *VertexShaderModule::CreateVertexAttributeBinding()
{
    VertexAttributeBinding *vab=new VertexAttributeBinding(this);

    vab_sets.Add(vab);

    return(vab);
}

bool VertexShaderModule::Release(VertexAttributeBinding *vab)
{
    return vab_sets.Delete(vab);
}
VK_NAMESPACE_END
