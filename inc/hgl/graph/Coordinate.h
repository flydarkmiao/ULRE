#ifndef HGL_GRAPH_COORDINATE_INCLUDE
#define HGL_GRAPH_COORDINATE_INCLUDE

#include<hgl/math/Math.h>

namespace hgl
{
    namespace graph
    {
        /*
         * OpenGL Coordinate System         Vulkan Coordinate System        My Coordinate System
         *
         *                                         /Z
         *     Y|    /Z                           /                             Z|    /Y
         *      |   /                            /                               |   /        
         *      |  /                            *------------                    |  /         
         *      | /                             |           X                    | /          
         *      |/                              |                                |/           
         *      *------------                   |                                *------------
         *                  X                   | Y                                          X
         */

        extern Matrix4f MATRIX_FROM_OPENGL_COORDINATE;              //OpenGL����ϵ���ݵ��ҷ�����ϵ���ݱ任�þ���

        }//namespace graph
}//namespace hgl
#endif//HGL_GRAPH_COORDINATE_INCLUDE
