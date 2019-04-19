﻿#include"Window.h"
#include<xcb/xcb.h>
#include<xcb/xcb_atom.h>
#include"VK.h"
#include<vulkan/vk_sdk_platform.h>
#include<vulkan/vulkan.h>
#include<vulkan/vulkan_xcb.h>
namespace hgl
{
    namespace graph
    {
        class XCBWindow:public Window
        {
            xcb_connection_t *connection;
            xcb_screen_t *screen;
            xcb_window_t window;
            xcb_intern_atom_reply_t *atom_wm_delete_window;

        private:

            bool InitConnection()
            {
                int scr;

                connection=xcb_connect(nullptr,&scr);

                if(!connection||xcb_connection_has_error(connection))
                    return(false);

                const xcb_setup_t *setup=xcb_get_setup(connection);
                xcb_screen_iterator_t iter=xcb_setup_roots_iterator(setup);

                while(scr-->0)xcb_screen_next(&iter);

                screen=iter.data;
                return(true);
            }

        public:

            XCBWindow(const UTF8String &wn):Window(wn)
            {
                connection=nullptr;
                screen=nullptr;
                atom_wm_delete_window=nullptr;
            }

            ~XCBWindow()
            {
            }

            bool Create(uint w,uint h) override
            {
                if(w<=0||h<=0)return(false);
                if(!InitConnection())return(false);

                window=xcb_generate_id(connection);

                uint32_t value_mask,value_list[32];

                value_mask=XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
                value_list[0] = screen->black_pixel;
                value_list[1] = XCB_EVENT_MASK_KEY_RELEASE | XCB_EVENT_MASK_EXPOSURE;

                width=w;
                height=h;

                xcb_create_window(connection, XCB_COPY_FROM_PARENT, window, screen->root, 0,0, width, height, 0,
                                  XCB_WINDOW_CLASS_INPUT_OUTPUT, screen->root_visual, value_mask, value_list);

                xcb_intern_atom_cookie_t cookie = xcb_intern_atom(connection, 1, 12, "WM_PROTOCOLS");
                xcb_intern_atom_reply_t *reply = xcb_intern_atom_reply(connection, cookie, 0);

                xcb_intern_atom_cookie_t cookie2 = xcb_intern_atom(connection, 0, 16, "WM_DELETE_WINDOW");
                atom_wm_delete_window = xcb_intern_atom_reply(connection, cookie2, 0);

                xcb_change_property(connection, XCB_PROP_MODE_REPLACE, window, (*reply).atom, 4, 32, 1,
                                    &(*atom_wm_delete_window).atom);
                free(reply);

                xcb_change_property (connection, XCB_PROP_MODE_REPLACE, window,XCB_ATOM_WM_NAME, XCB_ATOM_STRING, 8,
                                     win_name.Length(), win_name.c_str());

                xcb_map_window(connection, window);

                const uint32_t coords[] =
                {
                    (screen->width_in_pixels-width)/2,
                    (screen->height_in_pixels-height)/2
                };
                xcb_configure_window(connection, window, XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y, coords);
                xcb_flush(connection);

                xcb_generic_event_t *e;
                while ((e = xcb_wait_for_event(connection))) {
                    if ((e->response_type & ~0x80) == XCB_EXPOSE) break;
                }
            }

            bool Create(uint,uint,uint)override{}
            void Close()override
            {
                xcb_destroy_window(connection, window);
                xcb_disconnect(connection);
            }

            void Show()override{}
            void Hide()override{}

        public:

            xcb_connection_t *GetConnection(){return connection;}
            xcb_window_t GetWindow(){return window;}

        };//class XCBWindow:public Window

        Window *CreateRenderWindow(const UTF8String &win_name)
        {
            return(new XCBWindow(win_name));
        }
    }//namespace graph
}//namespace hgl

VK_NAMESPACE_BEGIN
VkSurfaceKHR CreateRenderDevice(VkInstance vk_inst,Window *win)
{
    XCBWindow *xcb_win=(XCBWindow *)win;

    VkXcbSurfaceCreateInfoKHR createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
    createInfo.pNext = nullptr;
    createInfo.connection = xcb_win->GetConnection();
    createInfo.window = xcb_win->GetWindow();

    VkSurfaceKHR surface;

    VkResult res = vkCreateXcbSurfaceKHR(vk_inst, &createInfo, nullptr, &surface);

    if (res != VK_SUCCESS)
        return(nullptr);

    return(surface);
}
VK_NAMESPACE_END
