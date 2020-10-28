package com.example.activitydemo;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.os.PersistableBundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

public class ThirdActivity extends Activity{

    private EditText et_phone ;
    private EditText et_psw;
    public static int RESULT_OK = 1;
    public static int RESULT_NO = 2;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_third);

        et_phone = findViewById(R.id.et_Phone);
        et_psw = findViewById(R.id.et_Psw);

        Button btn_confirm = findViewById(R.id.btn_confirm);
        Button btn_concel = findViewById(R.id.btn_concel);

        btn_confirm.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                //获取用户输入注册信息
                String phone = et_phone.getText().toString();
                String psw = et_psw.getText().toString();

                //设置结果
                Intent intent = new Intent();
                intent.putExtra("phone", phone);
                intent.putExtra("psw", psw);
                setResult(RESULT_OK, intent);

                //结束当前activity
                finish();
                //activity切换动画,使用自定义动画
                overridePendingTransition(R.anim.zoomin,R.anim.zoomout);
            }
        });




        btn_concel.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //结束当前activity
                finish();
                //activity切换动画,使用自定义动画
                overridePendingTransition(R.anim.zoomin,R.anim.zoomout);
            }
        });
    }



}
