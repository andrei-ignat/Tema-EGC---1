#version 330

// Input
// TODO(student): Get vertex attributes from each location
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float Time;

// Output
// TODO(student): Output values to fragment shader
out vec3 f_color;

void main()
{
    // TODO(student): Send output to fragment shader

    // TODO(student): Compute gl_Position

    float amplitude = 0.5;
    vec3 animatedPosition = v_position;
    animatedPosition.y += amplitude * sin(Time + v_position.x);

    vec3 normal_Variation = v_color;
    normal_Variation.r += 0.5 * sin(Time);
    normal_Variation.g += 0.5 * cos(Time);

    f_color = normal_Variation;

    gl_Position = Projection * View * Model * vec4(animatedPosition, 1);
}
