#pragma once
struct GLFWwindow;

bool s3ImGuiInit(GLFWwindow* window);
void s3ImGuiShutdown();
void s3ImGuiBeginRender();
void s3ImGuiEndRender();
