package com.example.ndk;

import com.utils.water.Water;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;


public class WaterImageView extends View{
	
	Water water;
	float scale;
	Handler handler = new Handler(){
		public void handleMessage(Message msg) {
			invalidate();
			
			sendEmptyMessageDelayed(0, 50);
		}
	};
	
	public WaterImageView(Context context) {
		super(context);
		BitmapFactory.Options opts = new BitmapFactory.Options();
		opts.inPreferredConfig = Bitmap.Config.ARGB_8888;
		Bitmap bitmap = BitmapFactory.decodeResource(context.getResources(), R.drawable.bit, opts);
		water = new Water(bitmap);
		scale = context.getResources().getDisplayMetrics().density;
	}
	
	protected void onAttachedToWindow() {
		super.onAttachedToWindow();
		
		water.start();
		
		handler.sendEmptyMessageDelayed(0, 1000);
	}
	
	protected void onDraw(Canvas canvas) {
		water.render(canvas);
		
	}

	public boolean onTouchEvent(MotionEvent event) {
		
		if (event.getAction() == MotionEvent.ACTION_DOWN){
			Log.d("test", "click");
			water.HeightBlob((int)event.getX(), (int)event.getY(), scale);
		}
		
		return true;
	}
}
