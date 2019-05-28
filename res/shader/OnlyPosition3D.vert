﻿#version 450 core

layout(location = 0) in vec3 Vertex;
layout(location = 1) in vec3 Normal;

layout(binding = 0) uniform WorldConfig
{
    mat4 mvp;
} world;

layout(push_constant) uniform SkyLightConsts {
	vec4 sun_color;
	vec4 sun_direction;
} skylight;

layout(location = 0) out vec4 FragmentColor;
layout(location = 1) out vec3 FragmentNormal;

void main()
{
    FragmentColor=vec4(Color,1.0);
    FragmentNormal=Normal;

    gl_Position=vec4(Vertex,1.0)*world.mvp;
}
