﻿#ifndef HGL_GRAPH_VULKAN_INSTANCE_INCLUDE
#define HGL_GRAPH_VULKAN_INSTANCE_INCLUDE

#include<hgl/type/BaseString.h>
#include<hgl/type/List.h>
#include<hgl/platform/Window.h>
#include<hgl/graph/vulkan/VKPhysicalDevice.h>
#include<hgl/graph/vulkan/VKDebugOut.h>

VK_NAMESPACE_BEGIN
    class Instance
    {
        VkInstance inst;

        VKDebugOut *debug_out;

        CharPointerList ext_list;

        ObjectList<PhysicalDevice> physical_devices;

    private:

        friend Instance *CreateInstance(const UTF8String &app_name,VKDebugOut *do=nullptr);

        Instance(VkInstance,VKDebugOut *,CharPointerList &);

    public:

        virtual ~Instance();

                operator VkInstance (){return inst;}

        const   CharPointerList &           GetExtList          ()const {return ext_list;}
        const   ObjectList<PhysicalDevice> &GetDeviceList       ()const {return physical_devices;}
        const   PhysicalDevice *            GetDevice           (VkPhysicalDeviceType)const;
    };//class Instance

    Instance *CreateInstance(const UTF8String &,VKDebugOut *do=nullptr);                            ///<创建一个Vulkan实例
VK_NAMESPACE_END
#endif//HGL_GRAPH_VULKAN_INSTANCE_INCLUDE
