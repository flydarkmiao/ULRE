#pragma once

#include<hgl/graph/vulkan/VK.h>
#include<hgl/type/BaseString.h>

VK_NAMESPACE_BEGIN
struct PhysicalDevice
{
    VkInstance                          instance=nullptr;
    VkPhysicalDevice                    physical_device=nullptr;
    VkPhysicalDeviceFeatures            features;
    VkPhysicalDeviceProperties          properties;
    VkPhysicalDeviceDriverPropertiesKHR driver_properties;
    VkPhysicalDeviceMemoryProperties    memory_properties;
    List<VkLayerProperties>             layer_properties;
    List<VkExtensionProperties>         extension_properties;

public:

    PhysicalDevice(VkInstance,VkPhysicalDevice);
    ~PhysicalDevice()=default;

    const bool              CheckMemoryType(uint32_t,VkFlags,uint32_t *)const;

    VkPhysicalDeviceType    GetDeviceType()const{return properties.deviceType;}
    const char *            GetDeviceName()const{return properties.deviceName;}

    const uint32_t          GetExtensionSpecVersion(const UTF8String &name)const;

    const VkDriverIdKHR     GetDriverId     ()const{return driver_properties.driverID;}
    const char *            GetDriverName   ()const{return driver_properties.driverName;}
    const char *            GetDriverInfo   ()const{return driver_properties.driverInfo;}

    /**
    * ��ȡ���豸�Ƿ����Կ�
    */
    const bool isGPU()const
    {
        if(properties.deviceType==VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)return(true);
        if(properties.deviceType==VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU)return(true);
        if(properties.deviceType==VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU)return(true);

        return(false);
    }

    const bool isDiscreteGPU    ()const{return(properties.deviceType==VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU);}           ///<�Ƿ��Ƕ����Կ�
    const bool isIntegratedGPU  ()const{return(properties.deviceType==VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU);}         ///<�Ƿ��Ǽ����Կ�
    const bool isVirtualGPU     ()const{return(properties.deviceType==VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU);}            ///<�Ƿ��������Կ�

public:

    VkFormatProperties GetFormatProperties(const VkFormat format)const
    {
        VkFormatProperties fp;

        vkGetPhysicalDeviceFormatProperties(physical_device,format,&fp);

        return fp;
    }
};//struct PhysicalDevice
VK_NAMESPACE_END