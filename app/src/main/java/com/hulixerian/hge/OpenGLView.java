package com.hulixerian.hge;
import android.opengl.GLSurfaceView;
import android.content.Context;
//import android.graphics.PixelFormat;
//import android.util.AttributeSet;
//import android.util.Log;
//import android.view.KeyEvent;
//import android.view.MotionEvent;
//import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGLConfig;
//import javax.microedition.khronos.egl.EGLContext;
//import javax.microedition.khronos.egl.EGLDisplay;
import javax.microedition.khronos.opengles.GL10;
public class OpenGLView extends GLSurfaceView
{
//	private static final String TAG = "GLES3JNI";
//    private static final boolean DEBUG = true;
	
    public OpenGLView(Context context)
    {
        super(context);
        setEGLConfigChooser(8, 8, 8, 8, 16, 8);
        setEGLContextClientVersion(2);
        setRenderer(new Renderer());
    }

	private static class Renderer implements GLSurfaceView.Renderer
    {
        public void onDrawFrame(GL10 gl)
        {
        	HGELib.render();
        }

        public void onSurfaceChanged(GL10 gl, int width, int height)
        {
            HGELib.resize(width, height);
        }

        public void onSurfaceCreated(GL10 gl, EGLConfig config)
        {
            HGELib.init();
        }
    }
}
