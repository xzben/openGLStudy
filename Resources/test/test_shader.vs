#import<common/vs_head.vs>

out vec4 vertexColor;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    vertexColor = vec4(0.5, 0.0, 0.0, 1.0);
}