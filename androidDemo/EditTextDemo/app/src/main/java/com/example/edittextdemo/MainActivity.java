package com.example.edittextdemo;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.Editable;
import android.text.TextWatcher;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {
//   private EditText et_phone = findViewById(R.id.et_phone);
//    private EditText et_psw = findViewById(R.id.et_psw);
    //还没加载布局文件，显示空指针异常
    private EditText et_phone;
    private EditText et_psw;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        et_phone = findViewById(R.id.et_phone);
        et_psw = findViewById(R.id.et_psw);
        
     et_phone.addTextChangedListener(new TextWatcher() {
         @Override
         public void beforeTextChanged(CharSequence s, int start, int count, int after) {
             Log.i("Ovis", "内容改变之前：" + s);
         }

         @Override
         public void onTextChanged(CharSequence s, int start, int before, int count) {
             Log.i("Ovis", "内容改变时：" + s);
         }

         @Override
         public void afterTextChanged(Editable s) {
             Log.i("Ovis", "内容改变之后：" + s);
         }
     });
        
        
        Button btn_login = findViewById(R.id.btn_login);

        btn_login.setOnClickListener(this);

    }

    @Override
    public void onClick(View v) {
//        Toast.makeText(this,"您已登录",Toast.LENGTH_SHORT).show();
        //下面的和上面那个重复了，放到外面去
//        EditText et_phone = findViewById(R.id.et_phone);
//        EditText et_psw = findViewById(R.id.et_psw);
        String phone = et_phone.getText().toString();
        String psw = et_psw.getText().toString();
        if (phone.equals("123")&&psw.equals("abc"))
            Toast.makeText(this,"登录成功",Toast.LENGTH_SHORT).show();
        else
            Toast.makeText(this,"登录失败",Toast.LENGTH_SHORT).show();

    }
}
