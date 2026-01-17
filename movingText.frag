#version 330

varying highp vec2 vUv;
uniform lowp float qt_Opacity;
uniform highp float uTime;
uniform highp float mouse;
uniform sampler2D uTexture;
void main() {
    highp float time = uTime;
    highp vec2 pos = vUv;
    highp float r = texture2D(uTexture, pos + cos(time * 2.0 - time + pos.x) * 0.01).r;
    highp float g = texture2D(uTexture, pos + tan(time * 0.5 + pos.x - time) * 0.01).g;
    highp float b = texture2D(uTexture, pos - cos(time * 2.0 + time + pos.y) * 0.01).b;
    highp float a = texture2D(uTexture, pos).a;
    gl_FragColor = vec4(r, g, b, a) * qt_Opacity;
}
