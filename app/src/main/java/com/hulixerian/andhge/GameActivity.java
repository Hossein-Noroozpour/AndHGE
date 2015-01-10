package com.hulixerian.andhge;
import android.app.Activity;
import android.content.pm.ActivityInfo;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.WindowManager;
//import android.util.Log;
import com.hulixerian.hge.AndroidAccess;
import com.hulixerian.hge.OpenGLView;
import com.hulixerian.hge.HGELib;
public class GameActivity extends Activity
{
	private float lastX, lastY;
	//private final static String DEBUG_TAG = "HGE-Debugging";
	OpenGLView mView;
	@Override protected void onCreate(Bundle icicle)
	{
		super.onCreate(icicle);
		setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
		getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
		mView = new OpenGLView(getApplication());
		AndroidAccess.setApplicationContext(getApplication());
		setContentView(mView);
	}
	@Override protected void onPause()
	{
		super.onPause();
		mView.onPause();
	}
	@Override protected void onResume()
	{
		super.onResume();
		mView.onResume();
	}
	@Override
	public boolean onTouchEvent(MotionEvent event)
	{
		int action = event.getActionMasked();
		int fingerIndex = event.getActionIndex();
		int fingerCount = event.getPointerCount();
		switch(action)
		{
			case (MotionEvent.ACTION_DOWN):
				//Log.d(DEBUG_TAG, "Action was DOWN");
				lastX = event.getX(fingerIndex);
				lastY = event.getY(fingerIndex);
		    	return true;
			case (MotionEvent.ACTION_MOVE):
				if(fingerCount == 1)
				{
					float curX = event.getX(fingerIndex);
					float curY = event.getY(fingerIndex);
					float dltX = curX - lastX;
					float dltY = curY - lastY;
					lastX = curX;
					lastY = curY;
					HGELib.setFingerMovement(fingerIndex, dltX, dltY);
				}
				//Log.d(DEBUG_TAG,"Action was MOVE");
				return true;
			case (MotionEvent.ACTION_UP):
				//Log.d(DEBUG_TAG,"Action was UP");
				return true;
			case (MotionEvent.ACTION_CANCEL):
				//Log.d(DEBUG_TAG,"Action was CANCEL");
				return true;
			case (MotionEvent.ACTION_OUTSIDE):
				//Log.d(DEBUG_TAG,"Movement occurred outside bounds of current screen element");
				return true;
			default:
				return super.onTouchEvent(event);
		}      
	}
}
