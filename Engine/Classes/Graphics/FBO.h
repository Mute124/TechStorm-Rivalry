#pragma once
#include "../lib/raylib.h"
#include "../lib/rlgl.h"

class FBO
{
public:
    static RenderTexture2D LoadRenderTextureDepthTex(int width, int height)
    {
        RenderTexture2D target = {0};

        target.id = rlLoadFramebuffer(width, height); // Load an empty framebuffer

        if (target.id > 0)
        {
            rlEnableFramebuffer(target.id);

            // Create color texture (default to RGBA)
            target.texture.id = rlLoadTexture(0, width, height, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8, 1);
            target.texture.width = width;
            target.texture.height = height;
            target.texture.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;
            target.texture.mipmaps = 1;

            // Create depth texture buffer (instead of raylib default renderbuffer)
            target.depth.id = rlLoadTextureDepth(width, height, false);
            target.depth.width = width;
            target.depth.height = height;
            target.depth.format = 19; // DEPTH_COMPONENT_24BIT?
            target.depth.mipmaps = 1;

            // Attach color texture and depth texture to FBO
            rlFramebufferAttach(target.id, target.texture.id, RL_ATTACHMENT_COLOR_CHANNEL0, RL_ATTACHMENT_TEXTURE2D, 0);
            rlFramebufferAttach(target.id, target.depth.id, RL_ATTACHMENT_DEPTH, RL_ATTACHMENT_TEXTURE2D, 0);

            // Check if fbo is complete with attachments (valid)
            if (rlFramebufferComplete(target.id))
                TRACELOG(LOG_INFO, "FBO: [ID %i] Framebuffer object created successfully", target.id);

            rlDisableFramebuffer();
        }
        else
            TRACELOG(LOG_WARNING, "FBO: Framebuffer object can not be created");

        return target;
    }

    // Unload render texture from GPU memory (VRAM)
    static void UnloadRenderTextureDepthTex(RenderTexture2D target)
    {
        if (target.id > 0)
        {
            // Color texture attached to FBO is deleted
            rlUnloadTexture(target.texture.id);
            rlUnloadTexture(target.depth.id);

            // NOTE: Depth texture is automatically
            // queried and deleted before deleting framebuffer
            rlUnloadFramebuffer(target.id);
        }
    }
};