package com.example.customized_viewdemo;

import android.annotation.SuppressLint;
import android.content.Context;
import android.content.res.TypedArray;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.RectF;
import android.util.AttributeSet;
import android.view.View;

public class MyView extends View {
    private Paint textPaint;
    private Paint arcPaint;
    private int startAngle=180;//起点
    private int sweepAngle=180;//画的角度大小
    private int arcColor=R.color.colorPurple2;
    private float strokeWidth = 5;
    private String text;
    private int textColor;
    private float textSize;

    public MyView(Context context, AttributeSet attrs) {
        super(context, attrs);
        init( context,attrs);//不要忘记调用init
    }

    @SuppressLint("ResourceAsColor")
    private void init(Context context, AttributeSet attrs){
        //获取布局文件设置的属性值
        TypedArray typedArray = context.obtainStyledAttributes(attrs,R.styleable.customStyleView);
        startAngle = typedArray.getInt(R.styleable.customStyleView_startAngle,0);
        sweepAngle = typedArray.getInt(R.styleable.customStyleView_sweepAngle,90);
        arcColor = typedArray.getColor(R.styleable.customStyleView_arcColor,0);
        strokeWidth = typedArray.getDimension(R.styleable.customStyleView_strokeWidth,5);
        text = typedArray.getString(R.styleable.customStyleView_text);
        textColor = typedArray.getColor(R.styleable.customStyleView_textColor,0);
        textSize = typedArray.getDimension(R.styleable.customStyleView_textSize,0);
        typedArray.recycle();


        arcPaint = new Paint();
        arcPaint.setColor(arcColor);//圆弧颜色
        arcPaint.setStyle(Paint.Style.STROKE);//只画边缘
        arcPaint.setStrokeWidth(strokeWidth);//边缘粗细

        textPaint = new Paint();
        textPaint.setColor(textColor);//文字颜色
        textPaint.setTextSize(textSize);//文字大小
        textPaint.setTextAlign(Paint.Align.CENTER);

    }

    @Override
    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);
        canvas.drawArc(new RectF(100,100,300,300),
                startAngle,sweepAngle,false,arcPaint);  //画圆弧
        canvas.drawText(text,200,200,textPaint);

    }
}
