﻿#ifndef HGL_GRAPH_VULKAN_COMMAND_BUFFER_INCLUDE
#define HGL_GRAPH_VULKAN_COMMAND_BUFFER_INCLUDE

#include<hgl/graph/vulkan/VK.h>
#include<hgl/graph/vulkan/VKPipeline.h>
#include<hgl/graph/vulkan/VKDescriptorSets.h>
VK_NAMESPACE_BEGIN
//push constant 一般只有128/256字节，仅能存在矩阵。
//所以我们将每个对象的独立变换矩阵存在push constant中
class CommandBuffer
{
    VkDevice device;
    VkCommandPool pool;
    VkCommandBuffer cmd_buf;

    uint32_t cv_count;
    VkClearValue *clear_values;
    VkRect2D render_area;
    VkViewport viewport;

    VkPipelineLayout pipeline_layout;

public:

    CommandBuffer(VkDevice dev,const VkExtent2D &extent,const uint32_t att_count,VkCommandPool cp,VkCommandBuffer cb);
    ~CommandBuffer();

    operator VkCommandBuffer(){return cmd_buf;}
    operator const VkCommandBuffer()const{return cmd_buf;}
    operator const VkCommandBuffer *()const{return &cmd_buf;}

    void SetRenderArea(const VkRect2D &ra){render_area=ra;}
    void SetViewport(const VkViewport &vp){viewport=vp;}
    void SetClearColor(int index,float r,float g,float b,float a=1.0f)
    {
        if(index<0||index>cv_count)return;

        VkClearValue *cv=clear_values+index;

        cv->color.float32[0]=r;
        cv->color.float32[1]=g;
        cv->color.float32[2]=b;
        cv->color.float32[3]=a;
    }

    void SetClearDepthStencil(int index,float d=1.0f,float s=0)
    {
        if(index<0||index>cv_count)return;

        VkClearValue *cv=clear_values+index;

        cv->depthStencil.depth=d;
        cv->depthStencil.stencil=s;
    }

    //以上设定在Begin开始后即不可改变

    bool Begin();

    void PipelineBarrier(
        VkPipelineStageFlags                        srcStageMask,
        VkPipelineStageFlags                        dstStageMask,
        VkDependencyFlags                           dependencyFlags,
        uint32_t                                    memoryBarrierCount,
        const VkMemoryBarrier *                     pMemoryBarriers,
        uint32_t                                    bufferMemoryBarrierCount,
        const VkBufferMemoryBarrier *               pBufferMemoryBarriers,
        uint32_t                                    imageMemoryBarrierCount,
        const VkImageMemoryBarrier *                pImageMemoryBarriers)
    {
        vkCmdPipelineBarrier(cmd_buf,srcStageMask,dstStageMask,dependencyFlags,memoryBarrierCount,pMemoryBarriers,bufferMemoryBarrierCount,pBufferMemoryBarriers,imageMemoryBarrierCount,pImageMemoryBarriers);
    }

    void CopyBufferToImage(
        VkBuffer                                    srcBuffer,
        VkImage                                     dstImage,
        VkImageLayout                               dstImageLayout,
        uint32_t                                    regionCount,
        const VkBufferImageCopy *                   pRegions)
    {
        vkCmdCopyBufferToImage(cmd_buf,srcBuffer,dstImage,dstImageLayout,regionCount,pRegions);
    }

    void CopyImageToBuffer( 
        VkImage                                     srcImage,
        VkImageLayout                               srcImageLayout,
        VkBuffer                                    dstBuffer,
        uint32_t                                    regionCount,
        const VkBufferImageCopy *                   pRegions)
    {
        vkCmdCopyImageToBuffer(cmd_buf,srcImage,srcImageLayout,dstBuffer,regionCount,pRegions);
    }

    bool BeginRenderPass(RenderPass *rp,Framebuffer *fb);

    bool Bind(Pipeline *p)
    {
        if(!p)return(false);

        vkCmdBindPipeline(cmd_buf,VK_PIPELINE_BIND_POINT_GRAPHICS,*p);
        return(true);
    }

    bool Bind(DescriptorSets *dsl)
    {
        if(!dsl)return(false);

        pipeline_layout=dsl->GetPipelineLayout();

        vkCmdBindDescriptorSets(cmd_buf,VK_PIPELINE_BIND_POINT_GRAPHICS,pipeline_layout,0,1,dsl->GetDescriptorSets(),0,nullptr);

        return(true);
    }

    void PushConstants(ShaderStage shader_stage,uint32_t offset,uint32_t size,const void *pValues)
    {
        vkCmdPushConstants(cmd_buf,pipeline_layout,(VkShaderStageFlagBits)shader_stage,offset,size,pValues);
    }

    void PushConstants(const PushConstant *pc){vkCmdPushConstants(cmd_buf,pipeline_layout,VK_SHADER_STAGE_VERTEX_BIT,0,sizeof(PushConstant),pc);}

    bool Bind(Renderable *);

    void SetViewport        (uint32_t first,uint32_t count,const VkViewport *vp)    {vkCmdSetViewport(cmd_buf,first,count,vp);}
    void SetScissor         (uint32_t first,uint32_t count,const VkRect2D *sci)     {vkCmdSetScissor(cmd_buf,first,count,sci);}

    void SetLineWidth       (float line_width)                                      {vkCmdSetLineWidth(cmd_buf,line_width);}

    void SetDepthBias       (float constant_factor,float clamp,float slope_factor)  {vkCmdSetDepthBias(cmd_buf,constant_factor,clamp,slope_factor);}
    void SetDepthBounds     (float min_db,float max_db)                             {vkCmdSetDepthBounds(cmd_buf,min_db,max_db);}
    void SetBlendConstants  (const float constants[4])                              {vkCmdSetBlendConstants(cmd_buf,constants);}

    void SetStencilCompareMask  (VkStencilFaceFlags faceMask,uint32_t compareMask)  {vkCmdSetStencilCompareMask(cmd_buf,faceMask,compareMask);}
    void SetStencilWriteMask    (VkStencilFaceFlags faceMask,uint32_t compareMask)  {vkCmdSetStencilWriteMask(cmd_buf,faceMask,compareMask);}
    void SetStencilReference    (VkStencilFaceFlags faceMask,uint32_t compareMask)  {vkCmdSetStencilReference(cmd_buf,faceMask,compareMask);}

    void Draw       (const uint32_t vertex_count){vkCmdDraw(cmd_buf,vertex_count,1,0,0);}
    void DrawIndexed(const uint32_t index_count ){vkCmdDrawIndexed(cmd_buf,index_count,1,0,0,0);}
    
    void Draw       (const uint32_t vertex_count,   const uint32_t instance_count,const uint32_t first_vertex,  const uint32_t first_instance)
    {
        vkCmdDraw(cmd_buf,vertex_count,instance_count,first_vertex,first_instance);
    }

    void DrawIndexed(const uint32_t index_count,    const uint32_t instance_count,const uint32_t first_index,   const uint32_t vertex_offset,const uint32_t first_instance)
    {
        vkCmdDrawIndexed(cmd_buf,index_count,instance_count,first_index,vertex_offset,first_instance);
    }

    void EndRenderPass(){vkCmdEndRenderPass(cmd_buf);}
    bool End(){return(vkEndCommandBuffer(cmd_buf)==VK_SUCCESS);}
};//class CommandBuffer
VK_NAMESPACE_END
#endif//HGL_GRAPH_VULKAN_COMMAND_BUFFER_INCLUDE
