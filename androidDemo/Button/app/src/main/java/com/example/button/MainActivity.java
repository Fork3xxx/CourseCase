package com.example.button;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity implements View.OnClickListener{

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Button btn1 = findViewById(R.id.btn1);
        Button btn2 = findViewById(R.id.btn2);
        Button btn3 = findViewById(R.id.btn3);
        Button btn4 = findViewById(R.id.btn4);
        Button btn5 = findViewById(R.id.btn5);
        Button btn6 = findViewById(R.id.btn6);
        //点击事件的第一种写法
        btn2.setOnClickListener(this);
        btn1.setOnClickListener(this);
        //点击事件的第二种写法
        //这个方法的优点，只用写自己button的方法就行了，适用于只用一个方法的button,太多写不过来
//        btn3.setOnClickListener(new View.OnClickListener() {
//            @Override
//            public void onClick(View v) {
//                Toast.makeText(MainActivity.this,"这是点击事件写法3",Toast.LENGTH_SHORT).show();
//            }
//        });
//        btn4.setOnClickListener(new View.OnClickListener() {
//            @Override
//            public void onClick(View v) {
//                Toast.makeText(MainActivity.this,"这是点击事件写法4",Toast.LENGTH_SHORT).show();
//            }
//        });

         btn3.setOnClickListener(onClickListener);
         btn4.setOnClickListener(onClickListener);
    }
    private View.OnClickListener onClickListener = new View.OnClickListener() {
        //将这种方法另外写出来，就不用重复写
        @Override
        public void onClick(View v) {
            if (v.getId()==R.id.btn3)
                Toast.makeText(MainActivity.this,"这是点击事件写法3",Toast.LENGTH_SHORT).show();
            else if(v.getId()==R.id.btn4)
                Toast.makeText(MainActivity.this,"这是点击事件写法4",Toast.LENGTH_SHORT).show();
        }
    };
    @Override
    public void onClick(View v) {
        //可以通过view的id进行区别不同的view，以便做不同的处理
        if (v.getId()==R.id.btn1)
             Toast.makeText(this, "B_one",Toast.LENGTH_SHORT).show();
        else if(v.getId()==R.id.btn2)
            Toast.makeText(this,"这是Button点击事件2",Toast.LENGTH_SHORT).show();
    }
    public void click5(View v){
        //可以通过view的id进行区别不同的view，以便做不同的处理
        if (v.getId()==R.id.btn5)
            Toast.makeText(this,"这是5",Toast.LENGTH_SHORT).show();
        else if(v.getId()==R.id.btn6)
            Toast.makeText(this,"这是6",Toast.LENGTH_SHORT).show();
    }
}

