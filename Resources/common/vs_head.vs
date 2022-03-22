#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform vec4 uColor;

uniform mat4 cc_mvp;
uniform vec3 cc_timer;
uniform mat4 cc_model;
uniform mat4 cc_view;
uniform mat4 cc_projection;