package com.example.test;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TextView tv0=findViewById(R.id.tv0);
        tv0.setText("如何在程序里面动态赋值");

        TextView tv1=findViewById(R.id.tv1);
//        tv1.setText(R.string.testing);
        tv1.setText(getString(R.string.testing, new Integer[]{11,21,31}));

        TextView tv4=findViewById(R.id.tv4);
        tv4.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Toast.makeText(MainActivity.this,"点击了TextView4",Toast.LENGTH_LONG).show();
            }
        });

    }
}
