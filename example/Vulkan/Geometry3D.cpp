﻿// 4.Geometry3D

#include"VulkanAppFramework.h"
#include<hgl/filesystem/FileSystem.h>
#include<hgl/graph/InlineGeometry.h>
#include<hgl/graph/SceneDB.h>
#include<hgl/graph/RenderableInstance.h>
#include<hgl/graph/RenderList.h>

using namespace hgl;
using namespace hgl::graph;

constexpr uint32_t SCREEN_WIDTH=128;
constexpr uint32_t SCREEN_HEIGHT=128;

class TestApp:public CameraAppFramework
{
private:

    SceneNode   render_root;
    RenderList  render_list;

    vulkan::Material *          material            =nullptr;
    vulkan::DescriptorSets *    descriptor_sets     =nullptr;

    vulkan::Renderable          *ro_plane_grid[3];

    vulkan::Pipeline *          pipeline_line       =nullptr;

private:

    bool InitMaterial()
    {
        material=shader_manage->CreateMaterial(OS_TEXT("PositionColor3D.vert.spv"),
                                               OS_TEXT("FlatColor.frag.spv"));
        if(!material)
            return(false);

        descriptor_sets=material->CreateDescriptorSets();

        db->Add(material);
        db->Add(descriptor_sets);
        return(true);
    }

    void CreateRenderObject()
    {
        struct PlaneGridCreateInfo pgci;

        pgci.coord[0].Set(-100,-100,0);
        pgci.coord[1].Set( 100,-100,0);
        pgci.coord[2].Set( 100, 100,0);
        pgci.coord[3].Set(-100, 100,0);

        pgci.step.u=20;
        pgci.step.v=20;

        pgci.side_step.u=10;
        pgci.side_step.v=10;

        pgci.color.Set(0.75,0,0,1);
        pgci.side_color.Set(1,0,0,1);

        ro_plane_grid[0]=CreateRenderablePlaneGrid(db,material,&pgci);

        pgci.color.Set(0,0.75,0,1);
        pgci.side_color.Set(0,1,0,1);

        ro_plane_grid[1]=CreateRenderablePlaneGrid(db,material,&pgci);

        pgci.color.Set(0,0,0.75,1);
        pgci.side_color.Set(0,0,1,1);
        ro_plane_grid[2]=CreateRenderablePlaneGrid(db,material,&pgci);
    }

    bool InitUBO()
    {
        if(!InitCameraUBO(descriptor_sets,material->GetUBO("world")))
            return(false);

        descriptor_sets->Update();
        return(true);
    }

    bool InitPipeline()
    {
        {
            vulkan::PipelineCreater *pipeline_creater=new vulkan::PipelineCreater(device,material,device->GetRenderPass(),device->GetExtent());
            pipeline_creater->SetDepthTest(true);
            pipeline_creater->SetDepthWrite(true);
            pipeline_creater->CloseCullFace();
            pipeline_creater->Set(PRIM_LINES);

            pipeline_line=pipeline_creater->Create();
            if(!pipeline_line)
                return(false);

            db->Add(pipeline_line);

            delete pipeline_creater;
        }

        return pipeline_line;
    }

    bool InitScene()
    {
        const float rad90=hgl_ang2rad(90);

        render_root.Add(db->CreateRenderableInstance(pipeline_line,descriptor_sets,ro_plane_grid[0]));
        render_root.Add(db->CreateRenderableInstance(pipeline_line,descriptor_sets,ro_plane_grid[1]),rotate(rad90,0,1,0));
        render_root.Add(db->CreateRenderableInstance(pipeline_line,descriptor_sets,ro_plane_grid[2]),rotate(rad90,1,0,0));

        render_root.RefreshMatrix();
        render_root.ExpendToList(&render_list);

        return(true);
    }

public:

    bool Init()
    {
        if(!CameraAppFramework::Init(SCREEN_WIDTH,SCREEN_HEIGHT))
            return(false);

        if(!InitMaterial())
            return(false);

        CreateRenderObject();

        if(!InitUBO())
            return(false);

        if(!InitPipeline())
            return(false);

        if(!InitScene())
            return(false);

        return(true);
    }

    void BuildCommandBuffer(uint32 index)
    {
        VulkanApplicationFramework::BuildCommandBuffer(index,&render_list);
    }
};//class TestApp:public CameraAppFramework

int main(int,char **)
{
    TestApp app;

    if(!app.Init())
        return(-1);

    while(app.Run());

    return 0;
}
