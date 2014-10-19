package com.utils.water;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Paint;

public class Water {
	int mPtr;
	int mRadius;
	int mHeight;
	
	Bitmap mTarget;
	Bitmap mSource;
	
	Paint mPaint = new Paint();
	
	public Water(Bitmap source){
		mRadius = 4;
		mHeight = 100;
		mSource = source;
	}
	
	public Water(int radius, int height, Bitmap source){
		mRadius = radius;
		mHeight = height;
		mSource = source;
	}
	
	public void start(){
		mTarget = mSource.copy(mSource.getConfig(), true);
		mPtr = doStart(mSource, mTarget);
	}
	
	public void render(Canvas canvas){
		if (mTarget != null)
			canvas.drawBitmap(mTarget, 0, 0, mPaint);
		else {
			canvas.drawBitmap(mSource, 0, 0, mPaint);
		}
	}
	
	public void Free(){
		if (mPtr == 0)
			return;
			
		doFree(mPtr);
		mPtr = 0;
	}
	
	public void HeightBlob(int x, int y, float scale){
		int radius = (int)(mRadius*scale);
		int height = (int)(mHeight*scale);
		doHeightBlob(mPtr, x, y, radius, height);
	}
	
	private native void doHeightBlob(int ptr, int x, int y, int radius, int height);
	private native void doFree(int ptr);
	private native int doStart(Object source, Object target);
	public native void flush();
//	private native void doRenderBitmap(int ptr, Object src, Object taget);
//	private native void doRenderArray(int ptr, int [] src, int [] taget, int count);
	
    static {
    	System.loadLibrary("utilswater");
    }
}
