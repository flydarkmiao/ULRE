﻿#ifndef HGL_GRAPH_INLINE_GEOMETRY_INCLUDE
#define HGL_GRAPH_INLINE_GEOMETRY_INCLUDE

#include<hgl/graph/vulkan/VK.h>
#include<hgl/math/Vector.h>
#include<hgl/type/RectScope.h>
namespace hgl
{
    namespace graph
    {
        class SceneDB;

        /**
         * 矩形创建信息
         */
        struct RectangleCreateInfo
        {
            RectScope2f scope;
        };

        vulkan::Renderable *CreateRectangle(SceneDB *db,vulkan::Material *mtl,const RectangleCreateInfo *rci);

        /**
         * 圆角矩形创建信息
         */
        struct RoundRectangleCreateInfo:public RectangleCreateInfo
        {
            float radius;           //圆角半径
            uint32_t round_per;     //圆角精度
        };

        vulkan::Renderable *CreateRoundRectangle(SceneDB *db,vulkan::Material *mtl,const RoundRectangleCreateInfo *rci);

        /**
         * 圆形创建信息
         */
         struct CircleCreateInfo
         {
            Vector2f center;            //圆心坐标
            Vector2f radius;            //半径
            uint field_count;           //分段次数
         };

         vulkan::Renderable *CreateCircle(SceneDB *db,vulkan::Material *mtl,const CircleCreateInfo *rci);
    }//namespace graph
};//namespace hgl
#endif//HGL_GRAPH_INLINE_GEOMETRY_INCLUDE
