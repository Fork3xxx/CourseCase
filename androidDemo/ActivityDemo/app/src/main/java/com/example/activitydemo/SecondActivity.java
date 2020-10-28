package com.example.activitydemo;

import android.app.Activity;
import android.os.Bundle;
import android.os.PersistableBundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class SecondActivity extends Activity{
    //重写选择onCreate第一个方法
    @Override
    public void onCreate( Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_second);


        //接收mainActivity传过来的数据
        String phone = getIntent().getStringExtra("phone");
        TextView tv_phone = findViewById(R.id.tv_phone);
        tv_phone.setText("Hello, "+phone);        //动态设置TextView的内容

        Button btn = findViewById(R.id.btn_finishactivity2);
        btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //结束当前activity
                finish();
                //设置activity切换动画，这里用android自带的
                overridePendingTransition(android.R.anim.slide_in_left,android.R.anim.slide_out_right);
            }
        });
        Log.i("test","22222");
    }
}
