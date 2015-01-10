package com.hulixerian.hge;
import android.content.Context;
import android.content.res.AssetManager;
import android.graphics.Point;
import android.view.Display;
import android.view.WindowManager;
public class AndroidAccess
{
	private static Context applicationContext;
	private static AssetManager assetManager;
	public static String getAPKPath()
	{
		return applicationContext.getApplicationInfo().sourceDir;
	}
	public static AssetManager getAssetManager()
	{
		return assetManager;
	}
	public static Context getApplicationContext()
	{
		return applicationContext;
	}
	public static void setApplicationContext(Context applicationContext)
	{
		AndroidAccess.applicationContext = applicationContext;
		assetManager = applicationContext.getAssets();
	}
	public static int getScreenWidth()
	{
		WindowManager wm = (WindowManager) applicationContext.getSystemService(Context.WINDOW_SERVICE);
		Display display = wm.getDefaultDisplay();
		Point size = new Point();
		display.getSize(size);
		return size.x;
	}
	public static int getScreenHeight()
	{
		WindowManager wm = (WindowManager) applicationContext.getSystemService(Context.WINDOW_SERVICE);
		Display display = wm.getDefaultDisplay();
		Point size = new Point();
		display.getSize(size);
		return size.y;
	}
}
