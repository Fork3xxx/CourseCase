package com.example.activitydemo;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    private String phone = "123";
    private String psw = "abc";
    public static int RESULT_REGISTER_CODE = 1;

    //为什么这俩控件放外面，而button里面用，取决于用的地方
    private EditText et_phone;
    private EditText et_psw;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        et_phone = findViewById(R.id.et_phone);
        et_psw = findViewById(R.id.et_psw);

        Button btn_login = findViewById(R.id.btn_login);
        Button btn_register = findViewById(R.id.btn_register);

        btn_login.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                //获取用户输入数据
                String phone_input = et_phone.getText().toString();
               String psw_input = et_psw.getText().toString();

                //判断用户输入的是否正确，如果正确，则跳转到第二个activity,否则提示错误
                if (phone_input.equals(phone) && psw_input.equals(psw)){
                    //启动第二个Activity  P142页
                    //显式启动activity，原来的，要启动的
                    Intent intent = new Intent(MainActivity.this,SecondActivity.class);
                    intent.putExtra("phone",phone);//调用一次传一个数据，如果传多个，可以通过多次调用
                    startActivity(intent);
                    //设置activity切换动画，这里用android自带的
                    overridePendingTransition(android.R.anim.slide_in_left,android.R.anim.slide_out_right);

                }
                else
                    Toast.makeText(MainActivity.this,"用户名或密码错误",Toast.LENGTH_SHORT).show();
            }
        });

        btn_register.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //隐式方式启动第三个activity
                Intent intent = new Intent();
                intent.setAction("activity3");
                startActivityForResult(intent,RESULT_REGISTER_CODE);

                //activity切换动画,使用自定义动画
                overridePendingTransition(R.anim.zoomin,R.anim.zoomout);
            }
        });
    }

    @Override
    protected void onActivityResult(int requestCode,int resultCode,Intent data){

        //代表是注册返回的结果
        if(requestCode == RESULT_REGISTER_CODE){
            if (resultCode == ThirdActivity.RESULT_OK){
                //代表注册成功
                String newphone = data.getStringExtra("phone");
                String newpsw = data.getStringExtra("psw");

                //更新用户手机和密码
                phone = newphone;
                psw = newpsw;

//                phone = data.getStringExtra("phone");
//                psw = data.getStringExtra("psw");
//
            }

        }
        super.onActivityResult(requestCode,resultCode,data);

    }
}
