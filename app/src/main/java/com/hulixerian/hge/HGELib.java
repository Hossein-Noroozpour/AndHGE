package com.hulixerian.hge;
public class HGELib
{
	static
	{
		System.loadLibrary("hge");
	}
	public static native boolean init();
	public static native boolean resize(int width, int height);
	public static native boolean render();
	public static native boolean setFingerPosition(int fingerIndex, float x, float y);
	public static native boolean setFingerMovement(int fingerIndex, float deltaX, float deltaY);
}
