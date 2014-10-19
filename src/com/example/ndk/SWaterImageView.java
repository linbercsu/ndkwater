package com.example.ndk;

import com.utils.water.Water;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;

public class SWaterImageView extends SurfaceView implements
		SurfaceHolder.Callback {

	SurfaceHolder holder;
	Water water;
	float scale;
	Handler handler = new Handler() {
		public void handleMessage(Message msg) {
			//invalidate();

			
			
//			sendEmptyMessageDelayed(0, 80);
		}
	};

	class MyThread implements Runnable {

		Paint mPaint = new Paint();

		@Override
		public void run() {
			try {
				while (true) {
					Canvas canvas = holder.lockCanvas(null);// 获取画布
					canvas.drawColor(Color.BLACK);
					// mPaint.setColor(Color.BLUE);
					//water.flush();
					water.render(canvas);

					// canvas.drawRect(new RectF(40,60,80,80), mPaint);
					holder.unlockCanvasAndPost(canvas);// 解锁画布，提交画好的图像

					Thread.sleep(80);
				}
			} catch (Exception e) {
				e.printStackTrace();
			}
		}

	}

	@Override
	public void surfaceChanged(SurfaceHolder holder, int format, int width,
			int height) {

	}

	@Override
	public void surfaceCreated(SurfaceHolder holder) {
		new Thread(new MyThread()).start();
	}

	@Override
	public void surfaceDestroyed(SurfaceHolder holder) {

	}

	public SWaterImageView(Context context) {
		super(context);
		holder = this.getHolder();// 获取holder
		holder.addCallback(this);

		BitmapFactory.Options opts = new BitmapFactory.Options();
		opts.inPreferredConfig = Bitmap.Config.ARGB_8888;
		Bitmap bitmap = BitmapFactory.decodeResource(context.getResources(),
				R.drawable.bit, opts);
		water = new Water(bitmap);
		scale = context.getResources().getDisplayMetrics().density*2;
	}

	protected void onAttachedToWindow() {
		super.onAttachedToWindow();

		water.start();

//		handler.sendEmptyMessageDelayed(0, 1000);
	}

	/**
	protected void onDraw(Canvas canvas) {
		water.render(canvas);

	}
	*/

	public boolean onTouchEvent(MotionEvent event) {

//		if (event.getAction() == MotionEvent.ACTION_DOWN) {
//			Log.d("test", "click");
			water.HeightBlob((int) event.getX(), (int) event.getY(), scale);
//		}

		return true;
	}
}
